package syntax

import collection.mutable.Map
import tac.Tac

case class Program(items: List[TopLevelItem])

abstract sealed class TopLevelItem
case class Import(path: String)                                                                     extends TopLevelItem
case class Declaration(name: String, typ: Option[Type], init: Option[Expression], linkage: Linkage) extends TopLevelItem

enum Linkage {
    case Public, Private
}

abstract sealed class Statement
case class VarDeclaration(name: String, typ: Option[Type], init: Option[Expression]) extends Statement
case class ExpressionStmt(exp: Expression)                                           extends Statement

trait Formal

abstract sealed class Expression
case class Constant(const: Const)                                                                             extends Expression
case class ArrayLit(values: List[Expression], typ: ArrayType)                                                 extends Expression
case class Function(recBinder: Option[String], params: List[Formal], retType: Option[Type], body: Expression) extends Expression
case class Var(name: String)                                                                                  extends Expression with Formal
case class BuiltinVar(name: String)                                                                           extends Expression
case class Ref(exp: Expression)                                                                               extends Expression
case class Deref(exp: Expression)                                                                             extends Expression
case class TypedExpr(exp: Expression, typ: Type)                                                              extends Expression with Formal
case class Cast(exp: Expression, targetType: Type)                                                            extends Expression
case class Assignment(target: Expression, value: Expression)                                                  extends Expression
case class If(cond: Expression, thenBranch: Expression, elseBranch: Option[Expression])                       extends Expression
case class Return(exp: Expression)                                                                            extends Expression
case class Break(label: String)                                                                               extends Expression
case class Continue(label: String)                                                                            extends Expression
case class While(cond: Expression, body: Expression, label: String)                                           extends Expression
case class TrueExpr()                                                                                         extends Expression
case class FalseExpr()                                                                                        extends Expression
case class FunctionCall(target: Expression, args: List[Expression])                                           extends Expression
// creates a new scope so no circular dependency between expression and statement
case class Block(statements: List[Statement], exp: Option[Expression]) extends Expression

abstract sealed class Type {
    override def toString: String = this match {
        case I8()                  => "i8"
        case I16()                 => "i16"
        case I32()                 => "i32"
        case I64()                 => "i64"
        case U8()                  => "u8"
        case U16()                 => "u16"
        case U32()                 => "u32"
        case U64()                 => "u64"
        case F16()                 => "f16"
        case F32()                 => "f32"
        case F64()                 => "f64"
        case Bool()                => "bool"
        case ArrayType(elem, size) => s"[$size]$elem"
        case Pointer(ref)          => s"*$ref"
        case FunType(params, ret)  => s"${params.mkString(", ")} -> $ret"
        case TypeVar(name)         => name
        case Inter(types)          => types.map(t => s"($t)").mkString(" ∩ ")
        case Quantified(binders, typ) =>
            if (binders.isEmpty) typ.toString
            else s"∀ ${binders.mkString(" ")}. $typ"
    }
}
case class I8()                                        extends Type
case class I16()                                       extends Type
case class I32()                                       extends Type
case class I64()                                       extends Type
case class U8()                                        extends Type
case class U16()                                       extends Type
case class U32()                                       extends Type
case class U64()                                       extends Type
case class F16()                                       extends Type
case class F32()                                       extends Type
case class F64()                                       extends Type
case class Bool()                                      extends Type
case class ArrayType(elem: Type, size: BigInt)         extends Type
case class Pointer(ref: Type)                          extends Type
case class FunType(params: List[Type], ret: Type)      extends Type
case class TypeVar(name: String)                       extends Type
case class Inter(types: Set[Type])                     extends Type
case class Quantified(binders: Set[String], typ: Type) extends Type

object Builtins {

    val binaryArithType: Type = Inter(
      Set(
        FunType(List(I8(), I8()), I8()),
        FunType(List(I16(), I16()), I16()),
        FunType(List(I32(), I32()), I32()),
        FunType(List(I64(), I64()), I64()),
        FunType(List(U8(), U8()), U8()),
        FunType(List(U16(), U16()), U16()),
        FunType(List(U32(), U32()), U32()),
        FunType(List(U64(), U64()), U64()),
        FunType(List(F16(), F16()), F16()),
        FunType(List(F32(), F32()), F32()),
        FunType(List(F64(), F64()), F64())
      )
    )
    val binaryArithPointerType: Type = Quantified(
      Set("t"),
      Inter(
        Set(
          binaryArithType,
          FunType(List(U64(), Pointer(TypeVar("t"))), Pointer(TypeVar("t"))),
          FunType(List(Pointer(TypeVar("t")), U64()), Pointer(TypeVar("t")))
        )
      )
    )
    val unaryArithType: Type = Inter(
      Set(
        FunType(List(I8()), I8()),
        FunType(List(I16()), I16()),
        FunType(List(I32()), I32()),
        FunType(List(I64()), I64()),
        FunType(List(U8()), U8()),
        FunType(List(U16()), U16()),
        FunType(List(U32()), U32()),
        FunType(List(U64()), U64()),
        FunType(List(F16()), F16()),
        FunType(List(F32()), F32()),
        FunType(List(F64()), F64())
      )
    )

    val binaryLogicType: Type = FunType(List(Bool(), Bool()), Bool())
    val unaryLogicType: Type  = FunType(List(Bool()), Bool())

    val eqType: Type = Quantified(Set("t"), FunType(List(TypeVar("t"), TypeVar("t")), Bool()))

    val binaryRelationalType: Type = Inter(
      Set(
        FunType(List(I8(), I8()), Bool()),
        FunType(List(I16(), I16()), Bool()),
        FunType(List(I32(), I32()), Bool()),
        FunType(List(I64(), I64()), Bool()),
        FunType(List(U8(), U8()), Bool()),
        FunType(List(U16(), U16()), Bool()),
        FunType(List(U32(), U32()), Bool()),
        FunType(List(U64(), U64()), Bool()),
        FunType(List(F16(), F16()), Bool()),
        FunType(List(F32(), F32()), Bool()),
        FunType(List(F64(), F64()), Bool())
      )
    )

    val builtinFunctions: scala.collection.immutable.Map[String, Type] = scala.collection.immutable.Map(
      "add"     -> binaryArithPointerType,
      "sub"     -> binaryArithPointerType,
      "mul"     -> binaryArithType,
      "div"     -> binaryArithType,
      "rem"     -> binaryArithType,
      "neg"     -> unaryArithType,
      "eq"      -> eqType,
      "ne"      -> eqType,
      "lt"      -> binaryRelationalType,
      "gt"      -> binaryRelationalType,
      "le"      -> binaryRelationalType,
      "ge"      -> binaryRelationalType,
      "and"     -> binaryLogicType,
      "or"      -> binaryLogicType,
      "not"     -> unaryLogicType,
      "bit_and" -> binaryArithType,
      "bit_or"  -> binaryArithType,
      "bit_xor" -> binaryArithType,
      "bit_not" -> unaryArithType,
      "lshift"  -> binaryArithType,
      "rshift"  -> binaryArithType
    )
}

enum Const {
    case I8Lit(value: BigInt)
    case I16Lit(value: BigInt)
    case I32Lit(value: BigInt)
    case I64Lit(value: BigInt)

    case U8Lit(value: BigInt)
    case U16Lit(value: BigInt)
    case U32Lit(value: BigInt)
    case U64Lit(value: BigInt)

    case F16Lit(value: BigDecimal)
    case F32Lit(value: BigDecimal)
    case F64Lit(value: BigDecimal)

    def isZero: Boolean = this match {
        case I8Lit(n)  => n == 0
        case I16Lit(n) => n == 0
        case I32Lit(n) => n == 0
        case I64Lit(n) => n == 0
        case U8Lit(n)  => n == 0
        case U16Lit(n) => n == 0
        case U32Lit(n) => n == 0
        case U64Lit(n) => n == 0
        case F16Lit(f) => f == BigDecimal(0)
        case F32Lit(f) => f == BigDecimal(0)
        case F64Lit(f) => f == BigDecimal(0)
    }

    def getValueStr: String = this match {
        case I8Lit(n)  => n.toString
        case I16Lit(n) => n.toString
        case I32Lit(n) => n.toString
        case I64Lit(n) => n.toString
        case U8Lit(n)  => n.toString
        case U16Lit(n) => n.toString
        case U32Lit(n) => n.toString
        case U64Lit(n) => n.toString
        case F16Lit(f) => f.toString
        case F32Lit(f) => f.toString
        case F64Lit(f) => f.toString
    }
}

enum Size {
    case Byte1, Byte2, Byte4, Byte8

    def bytes: Int = this match {
        case Byte1 => 1
        case Byte2 => 2
        case Byte4 => 4
        case Byte8 => 8
    }

    def bits: Int = this.bytes * 8
}

object Size {
    def fromTacType(t: Tac.Type): Size =
        t match {
            case Tac.I8() | Tac.U8()               => Byte1
            case Tac.I16() | Tac.U16() | Tac.F16() => Byte2
            case Tac.I32() | Tac.U32() | Tac.F32() => Byte4
            case Tac.I64() | Tac.U64() | Tac.F64() => Byte8
        }
}

def isNumericType(t: Type): Boolean = t match {
    case I8() | I16() | I32() | I64() | U8() | U16() | U32() | U64() | F16() | F32() | F64() => true
    case _                                                                                   => false
}

def isIntegerType(t: Type): Boolean = t match {
    case I8() | I16() | I32() | I64() | U8() | U16() | U32() | U64() => true
    case _                                                           => false
}
