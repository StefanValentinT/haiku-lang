package episteme

import scala.collection.immutable.Map
import scala.collection.immutable.*
import syntax.*

trait Constraint
case class ConstraintSub(a: Type, b: Type)   extends Constraint
case class ConstraintEqual(a: Type, b: Type) extends Constraint

type Subst = Map[String, Type]
type Env   = Map[String, Type]

case class UnificationProblem(
    freshVars: Set[String],
    constraints: List[Constraint]
)

def ftvType(t: Type): Set[String] = t match {
    case TypeVar(x)                   => Set(x)
    case FunType(params, ret)         => params.foldLeft(Set.empty[String])((acc, elem) => acc | ftvType(elem)) | ftvType(ret)
    case Inter(types)                 => types.foldLeft(Set.empty[String])((acc, elem) => acc | ftvType(elem))
    case Variant(types)               => types.foldLeft(Set.empty[String])((acc, elem) => acc | ftvType(elem))
    case Quantified(binders, typ)     => ftvType(typ).diff(binders)
    case Pointer(typ)                 => ftvType(typ)
    case ArrayType(elem: Type, _size) => ftvType(elem)
    case _                            => Set.empty
}

def ftvEnv(env: Env): Set[String] = env.values.foldLeft(Set.empty)((acc, value) => acc | ftvType(value))

var tCounter = 0
def newTypeVar(used: Set[String]): String = {
    val x = s"t#$tCounter"
    tCounter = tCounter + 1
    x
}

def flattenIntersection(t: Type): Set[Type] = t match {
    case Inter(ts) => ts.flatMap(flattenIntersection)
    case _         => Set(t)
}

def intersect(types: Set[Type]): Type = types match {
    case s if s.isEmpty   => throw EpistemicError("Cannot construct an intersection type of nothing.")
    case s if s.size == 1 => s.head
    case xs               => Inter(xs.flatMap(flattenIntersection).toSet)
}

def flattenVariant(t: Type): Set[Type] = t match {
    case Variant(ts) => ts.flatMap(flattenVariant)
    case _           => Set(t)
}

def makeVariant(types: Set[Type]): Type = types match {
    case s if s.isEmpty   => throw EpistemicError("Cannot construct a variant type of nothing.")
    case s if s.size == 1 => s.head
    case xs               => Variant(xs.flatMap(flattenVariant).toSet)
}

def quantify(binders: Set[String], typ: Type): Type = typ match {
    case Quantified(b2, t) if b2.isEmpty => t
    case Quantified(b2, t)               => Quantified(binders ++ b2, t)
    case t                               => Quantified(binders, t)
}

def addEnv(base: Env, toAdd: Env): Env =
    toAdd.foldLeft(base)((acc, binding) =>
        acc.get(binding._1) match
            case Some(existing) => acc.updated(binding._1, intersect(Set(existing, binding._2)))
            case None           => acc.updated(binding._1, binding._2)
    )

def substitute(subst: Subst, typ: Type): Type = typ match {
    case TypeVar(x)               => subst.getOrElse(x, TypeVar(x))
    case FunType(params, ret)     => FunType(params.map(substitute(subst, _)), substitute(subst, ret))
    case Inter(types)             => intersect(types.map(substitute(subst, _)))
    case Variant(types)           => makeVariant(types.map(substitute(subst, _)))
    case Quantified(binders, typ) => quantify(binders, substitute(subst -- binders, typ))

    case Pointer(ref)       => Pointer(substitute(subst, ref))
    case ArrayType(e, size) => ArrayType(substitute(subst, e), size)
    case t                  => t
}

def applyEnv(subst: Subst, env: Env): Env =
    env.view.mapValues(substitute(subst, _)).toMap

def composeSubstitution(s1: Subst, s2: Subst): Subst =
    s1 ++ s2.view.mapValues(substitute(s1, _))

def generalize(env: Env, t: Type): Type = {
    val envFtv  = ftvEnv(env)
    val tFtv    = ftvType(t)
    val genVars = tFtv.diff(envFtv)
    quantify(genVars, t)
}

def instantiateForall(used: Set[String], typ: Type): Type = typ match {
    case Quantified(bs, t) => {
        val (subst, _) = bs.foldLeft((Map.empty[String, Type], used))((acc, binder) =>
            val (accSubst, accUsed) = acc
            val fresh               = newTypeVar(accUsed)
            val updatedSubst        = accSubst + (binder -> TypeVar(fresh))
            val updatedUsed         = accUsed + fresh
            (updatedSubst, updatedUsed)
        )
        substitute(subst, t)
    }

    case t => t
}

def freshenPair(used: Set[String], principalPair: (Env, Type)): (Subst, Env, Type) = {
    val (env, t)     = principalPair
    val varsToRename = ftvEnv(env) ++ ftvType(t)

    val (subst, _) = varsToRename.foldLeft((Map.empty[String, Type], used)) { case ((accSubst, accUsed), v) =>
        val fresh = newTypeVar(accUsed)
        (accSubst + (v -> TypeVar(fresh)), accUsed + fresh)
    }

    (subst, applyEnv(subst, env), substitute(subst, t))
}

// satisfy σ <= τ
def subtypeSatisfaction(used: Set[String], sigma: Type, tau: Type): UnificationProblem = (sigma, tau) match {
    case (_, Inter(types)) => UnificationProblem(Set(), types.map((t: Type) => ConstraintSub(sigma, t)).toList)

    case (Inter(types), _) => {
        val candidates = types.map((t) => subtypeSatisfaction(used, t, tau))
        val validCandidates = candidates.filter { candidate =>
            try {
                convertToEqualities(used, candidate.constraints)
                unify(convertToEqualities(used, candidate.constraints))
                true
            } catch {
                case _: EpistemicError => false
            }
        }
        validCandidates.headOption match {
            case Some(firstValid) => firstValid
            case None             => UnificationProblem(Set(), List(ConstraintEqual(Inter(types), tau)))
        }
    }

    case (sigma @ Variant(types), tau) => {
        val candidates = types.toList.map(t => (t, subtypeSatisfaction(used, t, tau)))
        val validCandidates = candidates.flatMap { case (t, candidate) =>
            try {
                val sub = unify(convertToEqualities(used, candidate.constraints))
                Some((candidate, sub))
            } catch {
                case _: EpistemicError => None
            }
        }
        validCandidates match {
            case Nil                    => UnificationProblem(Set(), List(ConstraintEqual(sigma, tau)))
            case (singleProb, _) :: Nil => singleProb
            case multiple =>
                val allFresh = multiple.flatMap(_._1.freshVars).toSet
                val allKeys  = multiple.flatMap(_._2.keys).toSet
                val mergedConstraints = allKeys.map { k =>
                    val possibleTypes = multiple.flatMap(_._2.get(k)).toSet
                    ConstraintEqual(TypeVar(k), makeVariant(possibleTypes))
                }.toList
                UnificationProblem(allFresh, mergedConstraints)
        }
    }

    case (sigma, tau @ Variant(types)) => {
        val candidates = types.toList.map(t => (t, subtypeSatisfaction(used, sigma, t)))
        val validCandidates = candidates.flatMap { case (t, candidate) =>
            try {
                val sub = unify(convertToEqualities(used, candidate.constraints))
                Some((candidate, sub))
            } catch {
                case _: EpistemicError => None
            }
        }
        validCandidates match {
            case Nil                    => UnificationProblem(Set(), List(ConstraintEqual(sigma, tau)))
            case (singleProb, _) :: Nil => singleProb
            case multiple =>
                val allFresh = multiple.flatMap(_._1.freshVars).toSet
                val allKeys  = multiple.flatMap(_._2.keys).toSet
                val mergedConstraints = allKeys.map { k =>
                    val possibleTypes = multiple.flatMap(_._2.get(k)).toSet
                    ConstraintEqual(TypeVar(k), makeVariant(possibleTypes))
                }.toList
                UnificationProblem(allFresh, mergedConstraints)
        }
    }

    case (Quantified(binders, sigBody), tau) => {
        val (subst, freshVs, _) = binders.foldLeft((Map.empty[String, Type], Set.empty[String], used)) { case ((m, fVs, u), x) =>
            val fresh = newTypeVar(u)
            val mNew  = m + (x -> TypeVar(fresh))
            (mNew, fVs + fresh, u + fresh)
        }
        val sPrime = substitute(subst, sigBody)
        UnificationProblem(freshVs, List(ConstraintSub(sPrime, tau)))
    }

    case (FunType(params, ret), TypeVar(tv)) => {
        val paramVars = params.foldLeft((List.empty[TypeVar], used)) { case ((vars, u), _) =>
            val fresh = newTypeVar(u)
            (vars :+ TypeVar(fresh), u + fresh)
        }
        val pVars = paramVars._1

        val retName = newTypeVar(paramVars._2)
        val retVar  = TypeVar(retName)

        val freshVarNames = pVars.map(_.name).toSet + retName

        val paramConstraints = pVars.zip(params).map { case (t1, p) => ConstraintSub(t1, p) }

        UnificationProblem(
          freshVarNames,
          paramConstraints ++ List(
            ConstraintSub(ret, retVar),
            ConstraintEqual(TypeVar(tv), FunType(pVars, retVar))
          )
        )
    }

    case (FunType(p1, r1), FunType(p2, r2)) => {
        if (p1.length != p2.length) {
            UnificationProblem(Set.empty, List(ConstraintEqual(FunType(p1, r1), FunType(p2, r2))))
        } else {
            val paramConstraints = p2.zip(p1).map { case (param2, param1) => ConstraintSub(param2, param1) }
            UnificationProblem(
              Set.empty,
              paramConstraints :+ ConstraintSub(r1, r2)
            )
        }
    }

    case (s, t) =>
        UnificationProblem(Set.empty, List(ConstraintEqual(s, t)))
}

def convertToEqualities(used: Set[String], constraints: List[Constraint]): List[Constraint] = constraints match {
    case Nil                               => Nil
    case ConstraintEqual(sigma, tau) :: cs => ConstraintEqual(sigma, tau) :: convertToEqualities(used, cs)
    case ConstraintSub(sigma, tau) :: cs => {
        val prob    = subtypeSatisfaction(used, sigma, tau)
        val newUsed = used.union(prob.freshVars.toSet)
        convertToEqualities(newUsed, prob.constraints ::: cs)
    }
}

def unify(constraints: List[Constraint]): Subst = constraints match {
    case Nil =>
        Map.empty

    case ConstraintEqual(t1, t2) :: cs if t1 == t2 =>
        unify(cs)

    case ConstraintEqual(FunType(p1, r1), FunType(p2, r2)) :: cs =>
        if (p1.length != p2.length) {
            throw EpistemicError(s"Cannot unify multi-parameter functions: $p1 with $p2")
        }
        val paramEqs = p1.zip(p2).map { case (a, b) => ConstraintEqual(a, b) }
        unify(paramEqs ::: ConstraintEqual(r1, r2) :: cs)

    case ConstraintEqual(Pointer(s), Pointer(t)) :: cs =>
        unify(ConstraintEqual(s, t) :: cs)

    case ConstraintEqual(TypeVar(tv), t) :: cs =>
        if (ftvType(t).contains(tv)) {
            throw EpistemicError(s"$tv is infinite.")
        } else {
            val s: Subst = Map(tv -> t)
            def substC(c: Constraint): Constraint = c match {
                case ConstraintEqual(a, b) => ConstraintEqual(substitute(s, a), substitute(s, b))
                case other                 => other
            }
            val u = unify(cs.map(substC))
            composeSubstitution(u, s)
        }

    case ConstraintEqual(t, TypeVar(tv)) :: cs =>
        unify(ConstraintEqual(TypeVar(tv), t) :: cs)

    case ConstraintEqual(t1, t2) :: _ =>
        throw EpistemicError(s"Can not unify $t1 with $t2")

    case ConstraintSub(_, _) :: _ =>
        throw EpistemicError("A subtyping constraint has remained after conversion to unification problem.")
}

def extractVars(c: Constraint): Set[String] = c match {
    case ConstraintSub(a, b)   => ftvType(a) ++ ftvType(b)
    case ConstraintEqual(a, b) => ftvType(a) ++ ftvType(b)
}

def mgs(cs: List[Constraint]): Subst = {
    val initialUsed = cs.map(extractVars).foldLeft(Set.empty[String])(_ ++ _)
    val equalized   = convertToEqualities(initialUsed, cs)
    unify(equalized)
}
