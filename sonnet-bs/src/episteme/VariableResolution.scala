package episteme

import syntax.*
import scala.collection.mutable.Map
import app.CompilerError
import scala.collection.mutable.ListBuffer
import pprint.pprintln

class EpistemicError(detail: String) extends CompilerError("Semantic Compiler Pass", detail)

case class MapEntry(newName: String, fromCurrentBlock: Boolean, hasLinkage: Boolean)

object VariableResolver {
    private var varCounter = 0

    def makeUnique(orig: String): String = {
        varCounter += 1
        s"${orig}_${varCounter}"
    }

    def resolveProgram(p: Program): Program = {
        val globalVariableMap = Map[String, MapEntry]()
        val resolvedItems = p.items.map {
            case d: Declaration => {
                if (globalVariableMap.contains(d.name)) {
                    val prevEntry = globalVariableMap(d.name)
                    if (prevEntry.fromCurrentBlock) {
                        throw EpistemicError(s"Duplicate declaration of name: ${d.name}")
                    }
                }
                val resolvedInit = d.init.map(e => resolveExpression(e, globalVariableMap))
                globalVariableMap.put(d.name, MapEntry(d.name, true, true))
                Declaration(d.name, d.typ, resolvedInit, d.linkage)
            }
            case other => other
        }
        Program(resolvedItems)
    }

    def resolveStatement(stmt: Statement, variableMap: Map[String, MapEntry]): Statement = {
        stmt match {
            case ExpressionStmt(exp) => ExpressionStmt(resolveExpression(exp, variableMap))
            case VarDeclaration(name, typ, init) => {
                if (variableMap.contains(name) && variableMap(name).fromCurrentBlock) {
                    throw EpistemicError(s"Duplicate variable declaration: $name")
                }
                val uniqueName = makeUnique(name)
                variableMap.put(name, MapEntry(uniqueName, true, false))

                val resolvedInit = init.map(e => resolveExpression(e, variableMap))
                VarDeclaration(uniqueName, typ, resolvedInit)
            }
        }
    }

    def resolveExpression(exp: Expression, variableMap: Map[String, MapEntry]): Expression = {
        exp match {
            case TypedExpr(exp, typ) => TypedExpr(resolveExpression(exp, variableMap), typ)
            case Block(stmts, exp) => {
                val innerMap      = copyVariableMap(variableMap)
                val resolvedStmts = stmts.map(s => resolveStatement(s, innerMap))
                val resolvedExp   = if exp.isDefined then Some(resolveExpression(exp.get, innerMap)) else None
                Block(resolvedStmts, resolvedExp)
            }
            case Function(recBinder, params, retType, body) => {
                val globalOnlyMap = Map[String, MapEntry]()
                variableMap.foreach { case (key, entry) =>
                    if (entry.hasLinkage) {
                        globalOnlyMap.put(key, entry.copy(fromCurrentBlock = false))
                    }
                }
                val uniqueRecBinderOpt = recBinder.map { binder =>
                    val uniqueName = makeUnique(binder)
                    globalOnlyMap.put(binder, MapEntry(uniqueName, true, false))
                    uniqueName
                }

                val resolvedParams = new ListBuffer[Formal]()

                for (param <- params) {
                    val (paramName, paramTypeOpt) = param match {
                        case Var(name)                 => (name, None)
                        case TypedExpr(Var(name), typ) => (name, Some(typ))
                        case other                     => throw EpistemicError(s"Invalid formals in function: $other")
                    }
                    if (globalOnlyMap.contains(paramName) && globalOnlyMap(paramName).fromCurrentBlock) {
                        throw EpistemicError(s"Duplicate parameter declaration: $paramName")
                    }
                    val uniqueParamName = makeUnique(paramName)
                    globalOnlyMap.put(paramName, MapEntry(uniqueParamName, true, false))
                    val resolvedFormal = paramTypeOpt match {
                        case Some(typ) => TypedExpr(Var(uniqueParamName), typ)
                        case None      => Var(uniqueParamName)
                    }
                    resolvedParams.append(resolvedFormal)
                }

                val resolvedBody = resolveExpression(body, globalOnlyMap)
                Function(uniqueRecBinderOpt, resolvedParams.toList, retType, resolvedBody)
            }

            case b @ BuiltinVar(_)      => b
            case e @ Continue(_)        => e
            case e @ Break(_)           => e
            case t @ TrueExpr()         => t
            case f @ FalseExpr()        => f
            case While(cond, exp, l)    => While(resolveExpression(cond, variableMap), resolveExpression(exp, variableMap), l)
            case If(cond, thenB, elseB) => If(resolveExpression(cond, variableMap), resolveExpression(thenB, variableMap), if elseB.isDefined then Some(resolveExpression(elseB.get, variableMap)) else None)
            case Constant(value)        => Constant(value)
            case Cast(exp, typ)         => Cast(resolveExpression(exp, variableMap), typ)
            case Return(exp)            => Return(resolveExpression(exp, variableMap))
            case Var(value) => {
                variableMap.get(value) match {
                    case Some(MapEntry(uniqueName, _, _)) => Var(uniqueName)
                    case None                             => throw EpistemicError(s"Undeclared variable: $value")
                }
            }
            case ArrayLit(values, typ) =>
                ArrayLit(values.map(e => resolveExpression(e, variableMap)), typ)
            case Ref(exp)   => Ref(resolveExpression(exp, variableMap))
            case Deref(exp) => Deref(resolveExpression(exp, variableMap))
            case FunctionCall(BuiltinVar(target), args) =>
                if Builtins.builtinFunctions.contains(target) then FunctionCall(BuiltinVar(target), args.map(resolveExpression(_, variableMap)))
                else throw EpistemicError(s"Builtin $target does not exist.")
            case FunctionCall(target, args) =>
                FunctionCall(resolveExpression(target, variableMap), args.map(resolveExpression(_, variableMap)))
            case Assignment(target, value) => {
                val resolvedTarget = resolveExpression(target, variableMap)
                val resolvedValue  = resolveExpression(value, variableMap)
                Assignment(resolvedTarget, resolvedValue)
            }
        }
    }

    def copyVariableMap(currentMap: Map[String, MapEntry]): Map[String, MapEntry] = {
        val newMap = Map[String, MapEntry]()
        currentMap.foreach { case (key, entry) =>
            newMap.put(key, entry.copy(fromCurrentBlock = false))
        }
        newMap
    }

}
