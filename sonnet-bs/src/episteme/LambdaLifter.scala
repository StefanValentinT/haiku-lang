package episteme;

import scala.collection.mutable.ListBuffer
import syntax.Linkage

object LambdaLifter {
    private var counter = 0
    private def freshName(): String = {
        val name = s"lambda#$counter"
        counter += 1
        name
    }

    def liftProgram(prog: Typed.Program): Typed.Program = {
        val liftedItems = ListBuffer[Typed.TopLevelItem]()
        for (item <- prog.items) {
            item match {
                case d: Typed.Declaration =>
                    val (updatedDecl, generatedDecls) = liftDeclaration(d)
                    liftedItems ++= generatedDecls
                    liftedItems += updatedDecl
            }
        }
        Typed.Program(liftedItems.toList)
    }

    def liftDeclaration(d: Typed.Declaration): (Typed.Declaration, List[Typed.Declaration]) = {
        val generated = ListBuffer[Typed.Declaration]()

        val newInit = d.init.map {
            case fn @ Typed.Function(recBinder, params, returnType, body, typ) =>
                val (liftedBody, extraDecls) = liftExpression(body)
                generated ++= extraDecls
                Typed.Function(recBinder, params, returnType, liftedBody, typ)

            case otherExpr =>
                val (liftedExpr, extraDecls) = liftExpression(otherExpr)
                generated ++= extraDecls
                liftedExpr
        }

        (Typed.Declaration(d.name, d.typ, newInit, d.linkage), generated.toList)
    }

    def liftExpression(expr: Typed.Expression): (Typed.Expression, List[Typed.Declaration]) = expr match {
        case Typed.Constant(_, _) | Typed.TrueExpr() | Typed.FalseExpr() | Typed.Var(_, _) | Typed.BuiltinVar(_) | Typed.Break(_, _) | Typed.Continue(_, _) =>
            (expr, Nil)

        case Typed.Function(recBinder, params, returnType, body, typ) => {
            val (liftedBody, bodyDecls) = liftExpression(body)
            val lambdaName              = freshName()
            val liftedFn                = Typed.Function(recBinder, params, returnType, liftedBody, typ)
            (Typed.Var(lambdaName, typ), bodyDecls :+ Typed.Declaration(lambdaName, typ, Some(liftedFn), Linkage.Private))
        }

        case Typed.ArrayLit(values, typ) =>
            values.map(liftExpression).unzip match { case (vs, ds) => (Typed.ArrayLit(vs, typ), ds.flatten) }

        case Typed.Ref(exp, typ) =>
            liftExpression(exp) match { case (e, ds) => (Typed.Ref(e, typ), ds) }

        case Typed.Deref(exp, typ) =>
            liftExpression(exp) match { case (e, ds) => (Typed.Deref(e, typ), ds) }

        case Typed.Cast(exp, targetType) =>
            liftExpression(exp) match { case (e, ds) => (Typed.Cast(e, targetType), ds) }

        case Typed.Return(exp, typ) =>
            liftExpression(exp) match { case (e, ds) => (Typed.Return(e, typ), ds) }

        case Typed.Assignment(target, value, typ) =>
            (liftExpression(target), liftExpression(value)) match { case ((t, td), (v, vd)) => (Typed.Assignment(t, v, typ), td ::: vd) }

        case Typed.While(cond, body, label, typ) =>
            (liftExpression(cond), liftExpression(body)) match { case ((c, cd), (b, bd)) => (Typed.While(c, b, label, typ), cd ::: bd) }

        case Typed.FunctionCall(target, args, typ) =>
            (liftExpression(target), args.map(liftExpression).unzip) match { case ((t, td), (as, ads)) => (Typed.FunctionCall(t, as, typ), td ::: ads.flatten) }

        case Typed.If(cond, thenBranch, elseBranch, typ) =>
            (liftExpression(cond), liftExpression(thenBranch), elseBranch.map(liftExpression)) match {
                case ((c, cd), (t, td), eOpt) => (Typed.If(c, t, eOpt.map(_._1), typ), cd ::: td ::: eOpt.map(_._2).getOrElse(Nil))
            }

        case Typed.Block(statements, exp, typ) => {
            val (liftedStmts, stmtDeclLists) = statements.map(liftStatement).unzip
            val (liftedExp, expDecls) = exp.map(liftExpression) match {
                case Some((le, ds)) => (Some(le), ds)
                case None           => (None, Nil)
            }
            (Typed.Block(liftedStmts, liftedExp, typ), stmtDeclLists.flatten ::: expDecls)
        }
    }

    def liftStatement(stmt: Typed.Statement): (Typed.Statement, List[Typed.Declaration]) = stmt match {
        case Typed.VarDeclaration(name, typ, init) =>
            init.map(liftExpression) match {
                case Some((li, ds)) => (Typed.VarDeclaration(name, typ, Some(li)), ds)
                case None           => (Typed.VarDeclaration(name, typ, None), Nil)
            }
        case Typed.ExpressionStmt(exp) =>
            liftExpression(exp) match { case (le, ds) => (Typed.ExpressionStmt(le), ds) }
    }
}
