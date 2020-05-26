# DeepLang Specification
## 0 Preface
deeplang语言是一种自制编程语言，由来自浙大和中科大的同学共同完成，并由华为的老师指导。该项目来源于浙江大学和华为合作的深度科研计划。

我们致力于将deeplang语言打造为具有鲜明内存安全特性的面向IoT场景的语言，设计过程中参考Rust的安全机制，但又根据IoT场景的特性选择了更合适的解释执行的模式。这是一种静态类型、强类型语言，按照C-style设计语法，同时支持面向对象、过程式和逻辑式的混合范式。

deeplang的独特安全特性帮助其具有一定的竞争力。作者正在持续的开发和迭代中。

## 1 Overview

## 2 Syntactic and Lexical Grammars
### 2.0 Reversed words and keywords
``` dp
let  letmut  fun  class  interface  extends  impl

public  private  if  then  else  switch  case  for 

while  loop  prop  super  switch this

=>  ->  =  ==  ;  ,  :  (  )  {  }  [  ]  &  |  &&

‘  ’ “  ” ||  ?  =<   @  $  %  ^  +  -  *  /
```


### 2.1 Comment
- 单行注释: //
- 多行注释: /* */

### 2.2 Grammar
#### 2.2.1 Constant and identifier
``` bnf
Chars ::= SChar
          SChar Chars

SChar ::= any member of the source character set except
                            the double-quote ", backslash \, or new-line character

Identifier ::= IdentifierNondigit
               Identifier IdentifierNondigit
               Identifier Digit

IdentifierNondigit ::= Nondigit

Nondigit ::= one of
            _   a   b   c   d   e   f   g   h   i   j   k   l   m
                n   o   p   q   r   s   t   u   v   w   x   y   z
                A   B   C   D   E   F   G   H   I   J   K   L   M
                N   O   P   Q   R   S   T   U   V   W   X   Y   Z

Digit ::= 0
          NoZeroDigit

NonZeroDigit ::= one of
            1   2   3   4   5   6   7   8   9

Const ::= IntegerConst

IntegerConst ::= NonzeroDigit
                 IntegerConst Digit
```
#### 2.2.2 Expression

``` bnf
Exp ::= Const
        Identifier
        StringLiteral
        ( Exp )
        ArrayExp
        CallExp
        PointExp
        OpExp
        NewExp
```

数组表达式中，可以通过 @ 调用数组模式匹配方法
``` bnf
ArrayExp ::= [ ]
             [ ExpList ]
             ArrayAccessExp
             ArrayPatternMatchExp
                
ArrayAccessExp ::= Exp [ Exp ]

ArrayPatternMatchExp ::= Exp @ identifier ( ExpList )
```

函数调用表达式
``` bnf
CallExp ::= Exp ( )
            Exp ( ExpList )

PointExp ::= Exp . Identifier
```

一元表达式和二元表达式
``` bnf
OpExp ::= Exp AryOp Exp
          UnAryOp Exp

AryOp ::= one of 
            + - * / % = && || ==

UnAryOp ::= one of
            & ~ !
```

new操作符表达式
``` bnf
NewExp ::= new Identifier ( )
           new Identifier ( ExpList )

ExpList ::= Exp
            Exp , ExpList
```

字符串字面量
``` bnf
StringLiteral ::= " "
                  " Chars "
``` 
#### 2.2.3 Statement

``` bnf
Statement ::= if ( Exp ) then CompoundBlock Else CompoundBlock
              if ( Exp ) then CompoundBlock
              for ( CompoundBlock ; Exp ; Exp ) CompoundBlock
              JumpStatement


CompoundBlock ::= { }
                  { BlockList }

BlockList ::= Statement ;
              Statement ; BlockList
              Exp ;
              Exp ; BlockList
              Decl ;
              Decl ; BlockList

JumpStatement ::= break
                  return
                  return Exp
```
#### 2.2.4 Type 

类型表达式

``` bnf
Type ::= typename
         RefType
         FunctionType
         Type , Type

FunctionType ::= Type -> Type

RefType ::= & Type
            &mut Type
```
#### 2.2.5 Declaration

Declaration是整个deeplang程序最顶层的部分。由四个部分组成，分别是函数，变量，类，接口。
``` bnf
Decl ::= FunctionDecl
         VarDecl
         ClassDecl
         InterfaceDecl
```

FunctionDecl有两个部分组成，一是signature用于描述类型，二是FunctionDef描述行为。
``` bnf
FunctionDecl ::= Signature
                 Signature FunctionDef

Signature ::= sig Identifier :: Type

FunctionDef ::= fun Identifier () CompoundBlock
                fun Identifier ( ParamList ) CompoundBlock

ParamList ::= Identifier
              Identifier , ParamList
```

变量声明
``` bnf
VarDecl ::= let Identifier : Type
            let Identifier : Type = Exp
            letmut Identifier : Type
            letmut Identifier : Type = Exp
```

class和interface
``` bnf
ClassDecl ::= ClassHead { ClassBody }

ClassHead ::= class Identifier
              class Identifier extends Identifier
              class Identifier impl InterfaceList
              class Identifier extends Identifier impl InterfaceList

ClassBody ::= AccessSpecifier Decl ;
              AccessSpecifier Decl ; ClassBody
              Constructor ;
              Constructor ; ClassBody

Constructor ::= constructor ( ParamList ) CompoundBlock ;
                constructor ( ) CompoundBlock ;

AccessSpecifier ::= private
                    public

InterfaceDecl ::= InterfaceHead { InterfaceBody }

InterfaceHead ::= interface Identifier
                  interface Identifier extends Identifier

InterfaceBody ::= Decl ;
                  Decl ; InterfaceBody
```

deeplang程序的入口
``` bnf
Program ::= Decl ;
            Decl ; Program
```
## 3 Static Semantics
TODO
### 3.1 Type System
TODO
### 3.2 Scope
TODO
### 3.x
TODO
## 4 Dynamic Semantics
TODO
## 5 Appendix