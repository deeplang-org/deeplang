# DeepLang Specification
## 0 Preface
deeplang语言是一种自制编程语言，由来自浙大和中科大的同学共同完成，并由华为的老师指导。该项目来源于浙江大学和华为合作的深度科研计划。

我们致力于将deeplang语言打造为具有鲜明内存安全特性的面向IoT场景的语言，设计过程中参考Rust的安全机制，但又根据IoT场景的特性选择了更合适的解释执行的模式。这是一种静态类型、强类型语言，按照C-style设计语法，同时支持面向对象、过程式和逻辑式的混合范式。

deeplang的独特安全特性帮助其具有一定的竞争力。作者正在持续的开发和迭代中。

## 1 Overview

## 2 Syntactic and Lexical Grammars
### 2.0 Reversed Words and Keywords

#### 2.0.0 Reversed words
``` dp
let  letmut  fun  class  interface  extends  impl
public  private  if  then  else  switch  case  for
while  loop  prop  super  this
new  break  return  mut  sig  constructor
```
#### 2.0.1 Symbols
```g4
ASSIGN_OPERATOR:           '==';
EQUAL_OPERATOR:            '=';
PLUS_OPERATOR:             '+';
MINUS_OPERATOR:            '-';
MULT_OPERATOR:             '*';
DIV_OPERATOR:              '/';
MOD_OPERATOR:              '%';
BITWISE_XOR_OPERATOR:      '^';

LOGICAL_NOT_OPERATOR: '!';
BITWISE_NOT_OPERATOR: '~';

LOGICAL_AND_OPERATOR: '&&';
LOGICAL_OR_OPERATOR:  '||';

BITWISE_AND_OPERATOR: '&';
BITWISE_OR_OPERATOR:  '|';

DOT_SYMBOL:          '.';
COMMA_SYMBOL:        ',';
SEMICOLON_SYMBOL:    ';';
COLON_SYMBOL:        ':';
OPEN_PAR_SYMBOL:     '(';
CLOSE_PAR_SYMBOL:    ')';
OPEN_CURLY_SYMBOL:   '{';
CLOSE_CURLY_SYMBOL:  '}';
OPEN_SQUARE_SYMBOL:  '[';
CLOSE_SQUARE_SYMBOL: ']';

ALIAS_SYMBOL:            '::';
JSON_SEPARATOR_SYMBOL:   '->';
SEPARATOR_SYMBOL:        '=>';
AT_SIGN_SYMBOL:          '@';
PARAM_MARKER:            '?';
DOLLAR_SYMBOL:           '$';

// only for lexer
fragment BACK_TICK:     '`';
fragment SINGLE_QUOTE:  '\'';
fragment DOUBLE_QUOTE:  '"';
```



### 2.1 Comment
单行注释: //

多行注释: /* */

```g4
// 单行注释
fragment DOUBLE_SLASH:  '//';
SLASHSLASH_COMMET: DOUBLE_SLASH ([ \t] (~[\n\r])* | LINEBREAK | EOF) -> channel(HIDDEN);

// 多行注释
BLOCK_COMMENT: ( '/**/' | '/*' ~[!] .*? '*/') -> channel(HIDDEN);
```



### 2.2 Grammar
#### 2.2.1 Constant, String, and Identifier
``` bnf
// CONST
fragment NONZERODIGIT:  [1-9];
fragment DIGIT:         [0-9];
fragment DIGITS:        DIGIT+;

CONST:     	    INTEGERCONST;
INTEGERCONST:   NONZERODIGIT | (NONZERODIGIT DIGITS); 

// STRING
fragment LETTER_WHEN_UNQUOTED: DIGIT | LETTER_WHEN_UNQUOTED_NO_DIGIT；

QUOTED_STRING:
	DOUBLE_QUOTE LETTER_WHEN_UNQUOTED+ DOUBLE_QUOTE
;

// IDENTIFIER
fragment LETTER_WHEN_UNQUOTED_NO_DIGIT: [a-zA-Z_$];

IDENTIFIER:
	LETTER_WHEN_UNQUOTED_NO_DIGIT LETTER_WHEN_UNQUOTED*
;
```




#### 2.2.2 Expression

``` bnf
// TODO: left-recursive eliminate
exp :
    CONST
    | IDENTIFIER
    | QUOTED_STRING
    | OPEN_PAR_SYMBOL exp CLOSE_PAR_SYMBOL
    | arrayExp
    | callExp
    | pointExp
    | opExp
    | newExp
;
```

数组表达式中，可以通过 @ 调用数组模式匹配方法
``` bnf
arrayExp :
    OPEN_SQUARE_SYMBOL expList CLOSE_SQUARE_SYMBOL
    | OPEN_SQUARE_SYMBOL CLOSE_SQUARE_SYMBOL
    | arrayAccessExp
    | arrayPatternMatchExp
;

arrayAccessExp : 
	exp OPEN_SQUARE_SYMBOL exp CLOSE_SQUARE_SYMBOL
;

arrayPatternMatchExp : 
	exp AT_SIGN_SYMBOL IDENTIFIER OPEN_PAR_SYMBOL expList CLOSE_PAR_SYMBOL
;
```

函数调用表达式
``` bnf
callExp :
    exp OPEN_PAR_SYMBOL expList CLOSE_PAR_SYMBOL
    | exp OPEN_PAR_SYMBOL CLOSE_PAR_SYMBOL
;

pointExp :
    exp DOT_SYMBOL IDENTIFIER
;
```

一元表达式和二元表达式
``` bnf
opExp :
    exp aryOp exp
    | unAryOp exp
;

aryOp :
    PLUS_OPERATOR
    | MINUS_OPERATOR
    | MULT_OPERATOR
    | DIV_OPERATOR
    | MOD_OPERATOR
    | ASSIGN_OPERATOR
    | EQUAL_OPERATOR
    | LOGICAL_AND_OPERATOR
    | LOGICAL_OR_OPERATOR
;

unAryOp :
    BITWISE_AND_OPERATOR
    | LOGICAL_NOT_OPERATOR
    | BITWISE_NOT_OPERATOR
;
```

new操作符表达式
``` bnf
newExp :
    NEW_SYMBOL IDENTIFIER OPEN_PAR_SYMBOL CLOSE_PAR_SYMBOL
    | NEW_SYMBOL IDENTIFIER OPEN_PAR_SYMBOL expList CLOSE_PAR_SYMBOL
;

expList :
    exp
    | exp COMMA_SYMBOL expList
;
```


#### 2.2.3 Statement

``` bnf
statement :
    IF_SYMBOL OPEN_PAR_SYMBOL exp CLOSE_PAR_SYMBOL compoundBlock ELSE_SYMBOL compoundBlock
    | IF_SYMBOL OPEN_PAR_SYMBOL exp CLOSE_PAR_SYMBOL compoundBlock
    | FOR_SYMBOL OPEN_PAR_SYMBOL compoundBlock SEMICOLON_SYMBOL exp SEMICOLON_SYMBOL exp CLOSE_PAR_SYMBOL compoundBlock
    | jumpStatement
;

compoundBlock :
    OPEN_CURLY_SYMBOL CLOSE_CURLY_SYMBOL
    | OPEN_CURLY_SYMBOL blockList CLOSE_CURLY_SYMBOL
;

blockList :
    statement SEMICOLON_SYMBOL
    | statement SEMICOLON_SYMBOL blockList
    | exp SEMICOLON_SYMBOL
    | exp SEMICOLON_SYMBOL blockList
    | decl SEMICOLON_SYMBOL
    | decl SEMICOLON_SYMBOL blockList
;

jumpStatement :
    BREAK_SYMBOL
    | RETURN_SYMBOL
    | RETURN_SYMBOL exp
;
```
#### 2.2.4 Type 

类型表达式

``` bnf
// TODO: left-recursive eliminate
type :
    IDENTIFIER
    | refType
    | functionType
    | type COMMA_SYMBOL type
;

functionType :
    type JSON_SEPARATOR_SYMBOL type
;

refType :
    BITWISE_AND_OPERATOR type
    | BITWISE_AND_OPERATOR MUT_SYMBOL type // mut?
;
```
#### 2.2.5 Declaration

Declaration是整个deeplang程序最顶层的部分。由四个部分组成，分别是函数，变量，类，接口。
``` bnf
decl :
    functionDecl
    | varDecl
    | classDecl
    | interfaceDecl
;
```

FunctionDecl有两个部分组成，一是signature用于描述类型，二是FunctionDef描述行为。
``` bnf
functionDecl :
    signature
    | signature functionDef
;

signature :
    | SIG_SYMBOL IDENTIFIER ALIAS_SYMBOL type
;

functionDef :
    FUN_SYMBOL IDENTIFIER OPEN_PAR_SYMBOL CLOSE_PAR_SYMBOL compoundBlock // TODO: space?
    | FUN_SYMBOL IDENTIFIER OPEN_PAR_SYMBOL paramList CLOSE_PAR_SYMBOL compoundBlock
;

paramList :
    IDENTIFIER
    | IDENTIFIER COMMA_SYMBOL paramList
;
```

变量声明
``` bnf
varDecl :
    LET_SYMBOL IDENTIFIER COLON_SYMBOL type
    | LET_SYMBOL IDENTIFIER COLON_SYMBOL type EQUAL_OPERATOR exp
    | LETMUT_SYMBOL IDENTIFIER COLON_SYMBOL type
    | LETMUT_SYMBOL IDENTIFIER COLON_SYMBOL type EQUAL_OPERATOR exp
;
```

class和interface
``` bnf
classDecl :
    classHead OPEN_CURLY_SYMBOL classBody CLOSE_CURLY_SYMBOL
;

classHead :
    CLASS_SYMBOL IDENTIFIER
    | CLASS_SYMBOL IDENTIFIER EXTENDS_SYMBOL IDENTIFIER
    | CLASS_SYMBOL IDENTIFIER IMPL_SYMBOL interfaceList
    | CLASS_SYMBOL IDENTIFIER EXTENDS_SYMBOL IDENTIFIER IMPL_SYMBOL interfaceList
;

classBody :
    accessSpecifier decl SEMICOLON_SYMBOL
    | accessSpecifier decl SEMICOLON_SYMBOL classBody
    | constructor SEMICOLON_SYMBOL
    | constructor SEMICOLON_SYMBOL classBody
;

constructor :
    CONSTRUCTOR_SYMBOL OPEN_PAR_SYMBOL paramList CLOSE_PAR_SYMBOL compoundBlock
    | CONSTRUCTOR_SYMBOL OPEN_PAR_SYMBOL CLOSE_PAR_SYMBOL compoundBlock
;

accessSpecifier :
    PRIVATE_SYMBOL
    | PUBLIC_SYMBOL
;

interfaceList ://TODO: ??
    INTERFACE_SYMBOL
    | INTERFACE_SYMBOL COMMA_SYMBOL interfaceList
;

interfaceDecl :
    interfaceHead OPEN_CURLY_SYMBOL interfaceBody CLOSE_CURLY_SYMBOL
;

interfaceHead :
    INTERFACE_SYMBOL IDENTIFIER
    | INTERFACE_SYMBOL IDENTIFIER EXTENDS_SYMBOL IDENTIFIER
;

interfaceBody :
    decl SEMICOLON_SYMBOL
    | decl SEMICOLON_SYMBOL interfaceBody
;
```

deeplang程序的入口
``` bnf
program :
    decl SEMICOLON_SYMBOL
    | decl SEMICOLON_SYMBOL program
;
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
