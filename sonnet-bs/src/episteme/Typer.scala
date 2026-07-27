package episteme

import syntax.*
import scala.collection.immutable.Map
import scala.collection.mutable.{Map => MutMap}
import app.CompilerError
import scala.compiletime.ops.boolean

object Typed {
    case class Program(items: List[TopLevelItem])

    abstract sealed class TopLevelItem
    case class Declaration(name: String, typ: Type, init: Option[Expression], linkage: Linkage) extends TopLevelItem

    abstract sealed class Statement
    case class VarDeclaration(name: String, typ: Type, init: Option[Expression]) extends Statement
    case class ExpressionStmt(exp: Expression)                                   extends Statement

    trait Formal

    abstract sealed class Expression
    case class Constant(const: Const, typ: Type)                                                                                extends Expression
    case class ArrayLit(values: List[Expression], typ: ArrayType)                                                               extends Expression
    case class Function(recBinder: Option[String], params: List[(String, Type)], returnType: Type, body: Expression, typ: Type) extends Expression
    case class Var(name: String, typ: Type)                                                                                     extends Expression with Formal
    case class BuiltinVar(name: String)                                                                                         extends Expression
    case class Ref(exp: Expression, typ: Type)                                                                                  extends Expression
    case class Deref(exp: Expression, typ: Type)                                                                                extends Expression
    case class Cast(exp: Expression, targetType: Type)                                                                          extends Expression
    case class Assignment(target: Expression, value: Expression, typ: Type)                                                     extends Expression
    case class If(cond: Expression, thenBranch: Expression, elseBranch: Option[Expression], typ: Type)                          extends Expression
    case class Return(exp: Expression, typ: Type)                                                                               extends Expression
    case class Break(label: String, typ: Type)                                                                                  extends Expression
    case class Continue(label: String, typ: Type)                                                                               extends Expression
    case class While(cond: Expression, body: Expression, label: String, typ: Type)                                              extends Expression
    case class FunctionCall(target: Expression, args: List[Expression], typ: Type)                                              extends Expression
    case class Block(statements: List[Statement], exp: Option[Expression], typ: Type)                                           extends Expression
    case class TrueExpr()                                                                                                       extends Expression
    case class FalseExpr()                                                                                                      extends Expression
}

def getTypedType(expr: Typed.Expression): Type =
    expr match {
        case Typed.Function(_, _, _, _, t) => t
        case Typed.Constant(_, t)          => t
        case Typed.ArrayLit(_, t)          => t
        case Typed.Var(_, t)               => t
        case Typed.BuiltinVar(name) =>
            Builtins.builtinFunctions.get(name) match {
                case Some(t) => instantiateForall(Set.empty, t)
                case None    => throw CheckedError
            }
        case Typed.Ref(_, t)             => t
        case Typed.Deref(_, t)           => t
        case Typed.Cast(_, targetType)   => targetType
        case Typed.Assignment(_, _, t)   => t
        case Typed.If(_, _, _, t)        => t
        case Typed.Return(_, t)          => t
        case Typed.Break(_, t)           => t
        case Typed.Continue(_, t)        => t
        case Typed.While(_, _, _, t)     => t
        case Typed.FunctionCall(_, _, t) => t
        case Typed.Block(_, _, t)        => t
        case Typed.TrueExpr()            => Bool()
        case Typed.FalseExpr()           => Bool()
    }

val CheckedError = EpistemicError("This has been checked in variable resolution pass.")

case class SymbolEntry(typ: Type, isDefined: Boolean)

def formalToName(f: Formal): String = f match {
    case Var(name)               => name
    case TypedExpr(Var(name), _) => name
    case _                       => throw EpistemicError("Invalid function parameter: expected a variable, optionally annotated with `: Type`.")
}

def formalToType(f: Formal): Option[Type] = f match {
    case TypedExpr(Var(_), t) => Some(t)
    case _                    => None
}

def substituteInTypedExpr(subst: Subst, exp: Typed.Expression): Typed.Expression = exp match {
    case Typed.Constant(c, t) =>
        Typed.Constant(c, substitute(subst, t))
    case Typed.ArrayLit(values, t) =>
        Typed.ArrayLit(values.map(substituteInTypedExpr(subst, _)), substitute(subst, t).asInstanceOf[ArrayType])
    case Typed.Function(recBinder, params, ret, body, t) =>
        Typed.Function(
          recBinder,
          params.map { case (n, pT) => (n, substitute(subst, pT)) },
          substitute(subst, ret),
          substituteInTypedExpr(subst, body),
          substitute(subst, t)
        )
    case Typed.Var(name, t) =>
        Typed.Var(name, substitute(subst, t))
    case bv: Typed.BuiltinVar =>
        bv
    case Typed.Ref(e, t) =>
        Typed.Ref(substituteInTypedExpr(subst, e), substitute(subst, t))
    case Typed.Deref(e, t) =>
        Typed.Deref(substituteInTypedExpr(subst, e), substitute(subst, t))
    case Typed.Cast(e, targetType) =>
        Typed.Cast(substituteInTypedExpr(subst, e), substitute(subst, targetType))
    case Typed.Assignment(target, value, t) =>
        Typed.Assignment(substituteInTypedExpr(subst, target), substituteInTypedExpr(subst, value), substitute(subst, t))
    case Typed.If(cond, thenBranch, elseBranch, t) =>
        Typed.If(substituteInTypedExpr(subst, cond), substituteInTypedExpr(subst, thenBranch), elseBranch.map(substituteInTypedExpr(subst, _)), substitute(subst, t))
    case Typed.Return(e, t) =>
        Typed.Return(substituteInTypedExpr(subst, e), substitute(subst, t))
    case Typed.Break(l, t) =>
        Typed.Break(l, substitute(subst, t))
    case Typed.Continue(l, t) =>
        Typed.Continue(l, substitute(subst, t))
    case Typed.While(cond, body, l, t) =>
        Typed.While(substituteInTypedExpr(subst, cond), substituteInTypedExpr(subst, body), l, substitute(subst, t))
    case Typed.FunctionCall(target, args, t) =>
        Typed.FunctionCall(
          substituteInTypedExpr(subst, target),
          args.map(substituteInTypedExpr(subst, _)),
          substitute(subst, t)
        )
    case Typed.Block(statements, e, t) =>
        Typed.Block(statements.map(substituteTypedStatement(subst, _)), e.map(substituteInTypedExpr(subst, _)), substitute(subst, t))
    case Typed.TrueExpr()  => exp
    case Typed.FalseExpr() => exp
}

def substituteTypedStatement(subst: Subst, stmt: Typed.Statement): Typed.Statement = stmt match {
    case Typed.VarDeclaration(name, t, init) =>
        Typed.VarDeclaration(name, substitute(subst, t), init.map(substituteInTypedExpr(subst, _)))
    case Typed.ExpressionStmt(e) =>
        Typed.ExpressionStmt(substituteInTypedExpr(subst, e))
}

def pp(env: Env, exp: Expression): (Env, Typed.Expression) = exp match {

    case TypedExpr(exp, annot) =>
        val (a, typedExp) = ppCheck(addEnv(env, Map.empty), exp, annot)
        (a, typedExp)

    // Trivial cases
    case Constant(Const.I8Lit(value)) =>
        (Map.empty, Typed.Constant(Const.I8Lit(value), I8()))
    case Constant(Const.I16Lit(value)) =>
        (Map.empty, Typed.Constant(Const.I16Lit(value), I16()))
    case Constant(Const.I32Lit(value)) =>
        (Map.empty, Typed.Constant(Const.I32Lit(value), I32()))
    case Constant(Const.I64Lit(value)) =>
        (Map.empty, Typed.Constant(Const.I64Lit(value), I64()))
    case Constant(Const.F16Lit(value)) =>
        (Map.empty, Typed.Constant(Const.F16Lit(value), F16()))
    case Constant(Const.F32Lit(value)) =>
        (Map.empty, Typed.Constant(Const.F32Lit(value), F32()))
    case Constant(Const.F64Lit(value)) =>
        (Map.empty, Typed.Constant(Const.F64Lit(value), F64()))
    case Constant(Const.U8Lit(value)) =>
        (Map.empty, Typed.Constant(Const.U8Lit(value), U8()))
    case Constant(Const.U16Lit(value)) =>
        (Map.empty, Typed.Constant(Const.U16Lit(value), U16()))
    case Constant(Const.U32Lit(value)) =>
        (Map.empty, Typed.Constant(Const.U32Lit(value), U32()))
    case Constant(Const.U64Lit(value)) =>
        (Map.empty, Typed.Constant(Const.U64Lit(value), U64()))
    case TrueExpr() =>
        (Map.empty, Typed.TrueExpr())
    case FalseExpr() =>
        (Map.empty, Typed.FalseExpr())
    case Break(label) =>
        (Map.empty, Typed.Break(label, I32()))
    case Continue(label) =>
        (Map.empty, Typed.Continue(label, I32()))

    case Return(e) => {
        val (a, typedE) = pp(env, e)
        (a, Typed.Return(typedE, I32()))
    }
    case While(cond, body, label) => {
        val (a1, typedCond) = ppCheck(env, cond, Bool())
        val (a2, typedBody) = pp(addEnv(env, a1), body)
        (addEnv(a1, a2), Typed.While(typedCond, typedBody, label, I32()))
    }

    case Ref(e) => {
        val (a, typedE) = pp(env, e)
        // TODO: Do we want array decay to pointer? Think about this.
        val refType = getTypedType(typedE) match {
            case ArrayType(elem, _) => Pointer(elem)
            case t                  => Pointer(t)
        }
        (a, Typed.Ref(typedE, refType))
    }
    case Deref(e) => {
        val (a, typedE) = pp(env, e)
        getTypedType(typedE) match {
            case Pointer(innerType) =>
                (a, Typed.Deref(typedE, innerType))
            case t =>
                throw EpistemicError(s"Cannot dereference non-pointer type: $t")
        }
    }

    case Cast(e, targetType) => {
        val (a, typedE) = pp(env, e)
        // TODO: Which casts should be allowed? Think about this.
        val sourceType = getTypedType(typedE)
        if (!isNumericType(sourceType) || !isNumericType(targetType)) {
            throw EpistemicError(s"Disallowed cast from $sourceType to $targetType.")
        }
        (a, Typed.Cast(typedE, targetType))
    }

    case Assignment(target, value) => {
        target match {
            case Var(_) | Deref(_) => ()
            case _ =>
                throw EpistemicError("Invalid l-value: must be variable or dereferenced pointer")
        }
        val (a1, typedTarget) = pp(env, target)
        val targetType        = getTypedType(typedTarget)
        val (a2, typedValue)  = ppCheck(addEnv(env, a1), value, targetType)
        (addEnv(a1, a2), Typed.Assignment(typedTarget, typedValue, I32()))
    }

    case ArrayLit(values, ArrayType(elemType, size)) => {
        val (reqs, typedValues) = values.foldLeft((Map.empty[String, Type], List[Typed.Expression]())) { case ((a, ts), v) =>
            val (a2, tv) = ppCheck(addEnv(env, a), v, elemType)
            (addEnv(a, a2), ts :+ tv)
        }
        (reqs, Typed.ArrayLit(typedValues, ArrayType(elemType, size)))
    }

    case If(cond, thenBranch, elseBranch) => {
        val (a1, typedCond) = ppCheck(env, cond, Bool())
        val (a2, typedThen) = pp(addEnv(env, a1), thenBranch)
        val thenType        = getTypedType(typedThen)
        val (a3, typedElse) = elseBranch match {
            case Some(e) =>
                val (a3Reqs, typedE) = ppCheck(addEnv(addEnv(env, a1), a2), e, thenType)
                (a3Reqs.asInstanceOf[Env], Some(typedE))
            case None => (Map.empty[String, Type], None)
        }
        (addEnv(addEnv(addEnv(a1, a2), a3), Map.empty), Typed.If(typedCond, typedThen, typedElse, thenType))
    }

    case Block(statements, blockExp) => {
        val (stmtReqs, typedStmts) = statements.foldLeft((Map.empty[String, Type], List[Typed.Statement]())) { case ((a, ts), stmt) =>
            val (a2, ts2) = ppStatement(addEnv(env, a), stmt)
            (addEnv(a, a2), ts :+ ts2)
        }

        val (blockReqs, typedExp, blockType) = blockExp match {
            case Some(e) =>
                val (a3, te) = pp(addEnv(env, stmtReqs), e)
                (addEnv(stmtReqs, a3), Some(te), getTypedType(te))
            case None =>
                (stmtReqs, None, I32())
        }

        (blockReqs, Typed.Block(typedStmts, typedExp, blockType))
    }

    case Var(name) =>
        env.get(name) match {
            case Some(t) => {
                val instT = instantiateForall(ftvEnv(env), t)
                (Map.empty, Typed.Var(name, instT))
            }
            case None =>
                val fresh = TypeVar(newTypeVar(ftvEnv(env)))
                (Map(name -> fresh), Typed.Var(name, fresh))
        }

    case BuiltinVar(name) =>
        (Map.empty, Typed.BuiltinVar(name))

    case Function(recBinderOpt, params, retTypeOpt, body) => {
        val envForBody = params.foldLeft(env) { (currentEnv, formal) =>
            val name = formalToName(formal)
            formalToType(formal) match {
                case Some(t) => currentEnv + (name -> t)
                case None    => currentEnv - name
            }
        }

        val (bodyReqs, typedBodyInit) = pp(envForBody, body)

        case class ParamAcc(reqs: Env, typedBody: Typed.Expression, params: List[(String, Type)])

        val afterParams = params.foldLeft(ParamAcc(bodyReqs, typedBodyInit, Nil)) { (acc, formal) =>
            val name     = formalToName(formal)
            val annotOpt = formalToType(formal)

            acc.reqs.get(name) match {
                case Some(inferredTy) =>
                    val reqsWithoutBinder = acc.reqs - name
                    annotOpt match {
                        case Some(annotTy) =>
                            val u = mgs(List(ConstraintSub(inferredTy, annotTy)))
                            ParamAcc(applyEnv(u, reqsWithoutBinder), substituteInTypedExpr(u, acc.typedBody), acc.params :+ (name, annotTy))
                        case None =>
                            ParamAcc(reqsWithoutBinder, acc.typedBody, acc.params :+ (name, inferredTy))
                    }
                case None =>
                    val paramTy = annotOpt.getOrElse {
                        val used = ftvEnv(acc.reqs) ++ ftvType(getTypedType(acc.typedBody))
                        TypeVar(newTypeVar(used))
                    }
                    ParamAcc(acc.reqs, acc.typedBody, acc.params :+ (name, paramTy))
            }
        }

        val bodyType = getTypedType(afterParams.typedBody)

        val (finalReqs, finalRetType, finalTypedBody) = retTypeOpt match {
            case Some(annotatedRet) =>
                val u = mgs(List(ConstraintSub(bodyType, annotatedRet)))
                (applyEnv(u, afterParams.reqs), annotatedRet, substituteInTypedExpr(u, afterParams.typedBody))
            case None =>
                (afterParams.reqs, bodyType, afterParams.typedBody)
        }

        val funTy = FunType(afterParams.params.map(_._2), finalRetType)

        recBinderOpt match {
            case Some(binder) =>
                finalReqs.get(binder) match {
                    case None =>
                        val genFunTy = generalize(finalReqs, funTy)
                        (finalReqs, Typed.Function(recBinderOpt, afterParams.params, finalRetType, finalTypedBody, genFunTy))

                    case Some(tyB) =>
                        val reqsWithoutBinder = finalReqs - binder
                        val sigma             = generalize(reqsWithoutBinder, funTy)
                        val u                 = mgs(List(ConstraintSub(sigma, tyB)))

                        val mergedReqs = applyEnv(u, reqsWithoutBinder)

                        val substitutedParams = afterParams.params.map { case (n, t) => (n, substitute(u, t)) }
                        val substitutedRet    = substitute(u, finalRetType)
                        val substitutedBody   = substituteInTypedExpr(u, finalTypedBody)

                        val finalGenFunTy = generalize(mergedReqs, substitute(u, funTy))

                        (mergedReqs, Typed.Function(recBinderOpt, substitutedParams, substitutedRet, substitutedBody, finalGenFunTy))
                }
            case None =>
                val genFunTy = generalize(finalReqs, funTy)
                (finalReqs, Typed.Function(recBinderOpt, afterParams.params, finalRetType, finalTypedBody, genFunTy))
        }
    }

    case FunctionCall(target, args) => {
        val (targetReqs, typedTargetRaw) = pp(env, target)

        val targetType = typedTargetRaw match {
            case Typed.BuiltinVar(name) =>
                Builtins.builtinFunctions.get(name) match {
                    case Some(t) => instantiateForall(ftvEnv(env), t)
                    case None    => throw CheckedError
                }
            case other => getTypedType(other)
        }

        case class ArgAcc(reqs: Env, used: Set[String], typedArgs: List[Typed.Expression], argTypes: List[Type])

        val initUsed = ftvEnv(targetReqs) ++ ftvType(targetType)
        val argsAcc = args.foldLeft(ArgAcc(targetReqs, initUsed, Nil, Nil)) { (acc, argExp) =>
            val (argReqsRaw, typedArgRaw)      = pp(env, argExp)
            val (freshSubst, argReqs, argType) = freshenPair(acc.used, (argReqsRaw, getTypedType(typedArgRaw)))
            val typedArg                       = substituteInTypedExpr(freshSubst, typedArgRaw)

            ArgAcc(
              addEnv(acc.reqs, argReqs),
              acc.used ++ ftvEnv(argReqs) ++ ftvType(argType),
              acc.typedArgs :+ typedArg,
              acc.argTypes :+ argType
            )
        }

        val alpha = TypeVar(newTypeVar(argsAcc.used))
        val u     = mgs(List(ConstraintSub(targetType, FunType(argsAcc.argTypes, alpha))))

        val mergedReqs = applyEnv(u, argsAcc.reqs)
        val resultType = substitute(u, alpha)

        val finalTypedTarget = substituteInTypedExpr(u, typedTargetRaw)
        val finalTypedArgs   = argsAcc.typedArgs.map(substituteInTypedExpr(u, _))

        (mergedReqs, Typed.FunctionCall(finalTypedTarget, finalTypedArgs, resultType))
    }

}

def ppCheck(env: Env, exp: Expression, expected: Type): (Env, Typed.Expression) = {
    val (a, typedExp) = pp(env, exp)
    val inferred      = getTypedType(typedExp)

    if (inferred == expected) {
        (a, typedExp)
    } else {
        val cs = List(ConstraintSub(inferred, expected))
        val u  = mgs(cs)
        (applyEnv(u, a), substituteInTypedExpr(u, typedExp))
    }
}

def ppStatement(env: Env, stmt: Statement): (Env, Typed.Statement) = stmt match {
    case ExpressionStmt(exp) =>
        val (a, typedExp) = pp(env, exp)
        if getTypedType(typedExp) != I32() then throw EpistemicError("Statement does not return unit.")
        (a, Typed.ExpressionStmt(typedExp))

    case VarDeclaration(name, typOpt, init) => {
        val (a, declType, typedInit): (Env, Type, Option[Typed.Expression]) = typOpt match {
            case Some(t) =>
                val (a2, ti) = init match {
                    case Some(i) => ppCheck(env, i, t)
                    case None    => (Map.empty[String, Type], Typed.Block(List(), None, I32()))
                }
                (a2, t, Some(ti))

            case None =>
                init match {
                    case Some(i) =>
                        val (a2, te) = pp(env, i)
                        (a2, getTypedType(te), Some(te))
                    case None =>
                        val fresh = TypeVar(newTypeVar(ftvEnv(env)))
                        (Map.empty[String, Type], fresh, None)
                }
        }

        (a.asInstanceOf[Env], Typed.VarDeclaration(name, declType, typedInit))
    }
}

object TypeChecker {
    private val symbols = MutMap[String, Type]()

    def typecheckProgram(p: Program): Typed.Program = {
        symbols.clear()

        val typedItems = p.items.flatMap { item =>
            item match {
                case d: Declaration => {
                    val typed = typecheckDeclaration(d)
                    println(s"${typed.name} : ${typed.typ}")
                    Some(typed)
                }
                case Import(_) => None
            }
        }

        Typed.Program(typedItems)
    }

    private def typecheckDeclaration(v: Declaration): Typed.Declaration = {
        val (resolvedType, typedInitOpt) = (v.typ, v.init) match {
            case (Some(t), Some(init)) =>
                val (_, typedInit) = pp(symbols.toMap, init)
                val inferredType   = getTypedType(typedInit)
                mgs(List(ConstraintSub(inferredType, t)))
                (t, Some(typedInit))

            case (Some(t), None) =>
                (t, None)

            case (None, Some(init)) =>
                val (reqEnv, typedInit) = pp(symbols.toMap, init)
                val inferredType        = getTypedType(typedInit)

                val unboundKeys = reqEnv.keys.filterNot(symbols.contains).toList
                if (unboundKeys.nonEmpty) {
                    throw EpistemicError(s"Undefined variables referenced: ${unboundKeys.mkString(", ")}")
                }

                val compatConstraints = reqEnv.keys
                    .filter(symbols.contains)
                    .map { k =>
                        ConstraintSub(symbols(k), reqEnv(k))
                    }
                    .toList

                val subst     = mgs(compatConstraints)
                val finalTy   = substitute(subst, inferredType)
                val genResult = generalize(reqEnv, finalTy)

                (genResult, Some(typedInit))

            case (None, None) =>
                (TypeVar(newTypeVar(ftvEnv(symbols.toMap))), None)
        }

        symbols.put(v.name, resolvedType)

        Typed.Declaration(v.name, resolvedType, typedInitOpt, v.linkage)
    }

}
