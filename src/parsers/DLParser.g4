parser grammar DLParser;

/*
 * Copyright (c) 2012, 2020, Oracle and/or its affiliates. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2.0,
 * as published by the Free Software Foundation.
 *
 * This program is also distributed with certain software (including
 * but not limited to OpenSSL) that is licensed under separate terms, as
 * designated in a particular file or component or in included license
 * documentation. The authors of MySQL hereby grant you an additional
 * permission to link the program and your derivative works with the
 * separately licensed software that they have included with MySQL.
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
 * the GNU General Public License, version 2.0, for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */


//----------------------------------------------------------------------------------------------------------------------

// $antlr-format alignTrailingComments on, columnLimit 130, minEmptyLines 1, maxEmptyLinesToKeep 1, reflowComments off
// $antlr-format useTab off, allowShortRulesOnASingleLine off, allowShortBlocksOnASingleLine on, alignSemicolons ownLine

options {
    superClass = DLBaseRecognizer;
    tokenVocab = DLLexer;
    exportMacro = PARSERS_PUBLIC_TYPE;
}

//----------------------------------------------------------------------------------------------------------------------

@header {/*
 * Copyright (c) 2018, 2019, Oracle and/or its affiliates. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2.0,
 * as published by the Free Software Foundation.
 *
 * This program is also distributed with certain software (including
 * but not limited to OpenSSL) that is licensed under separate terms, as
 * designated in a particular file or component or in included license
 * documentation. The authors of MySQL hereby grant you an additional
 * permission to link the program and your derivative works with the
 * separately licensed software that they have included with MySQL.
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
 * the GNU General Public License, version 2.0, for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */
}

//@postinclude {
//#include "MySQLBaseRecognizer.h"
//}

//----------------------------------------------------------------------------------------------------------------------

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

// 数组表达式中，可以通过 @ 调用数组模式匹配方法
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

// 函数调用表达式

callExp :
    exp OPEN_PAR_SYMBOL expList CLOSE_PAR_SYMBOL
    | exp OPEN_PAR_SYMBOL CLOSE_PAR_SYMBOL
;

pointExp :
    exp DOT_SYMBOL IDENTIFIER
;


// 一元表达式和二元表达式
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


// new操作符表达式
newExp :
    NEW_SYMBOL IDENTIFIER OPEN_PAR_SYMBOL CLOSE_PAR_SYMBOL
    | NEW_SYMBOL IDENTIFIER OPEN_PAR_SYMBOL expList CLOSE_PAR_SYMBOL
;

expList :
    exp
    | exp COMMA_SYMBOL expList
;

// Statement

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

// Type

//type :
//    IDENTIFIER
//    | refType
//    | functionType
//    | type COMMA_SYMBOL type
//;

type :
	IDENTIFIER typeTail
	| refType typeTail
;

typeTail :
	COMMA_SYMBOL typeTail
	| JSON_SEPARATOR_SYMBOL typeTail
;

functionType :
    type JSON_SEPARATOR_SYMBOL type
;

refType :
    BITWISE_AND_OPERATOR type
    | BITWISE_AND_OPERATOR MUT_SYMBOL type // mut?
;

// Declaration

decl :
    functionDecl
    | varDecl
    | classDecl
    | interfaceDecl
;

// FunctionDecl有两个部分组成，一是signature用于描述类型，二是FunctionDef描述行为。
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

// 变量声明

varDecl :
    LET_SYMBOL IDENTIFIER COLON_SYMBOL type
    | LET_SYMBOL IDENTIFIER COLON_SYMBOL type EQUAL_OPERATOR exp
    | LETMUT_SYMBOL IDENTIFIER COLON_SYMBOL type
    | LETMUT_SYMBOL IDENTIFIER COLON_SYMBOL type EQUAL_OPERATOR exp
;

// class和interface

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


// deeplang程序的入口
program :
    decl SEMICOLON_SYMBOL
    | decl SEMICOLON_SYMBOL program
;