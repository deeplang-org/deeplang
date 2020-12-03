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
    tokenVocab = DLLexer;
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

@postinclude {
}

//----------------------------------------------------------------------------------------------------------------------

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


blockExpression :
    OPEN_CURLY_SYMBOL statements CLOSE_CURLY_SYMBOL
    | OPEN_CURLY_SYMBOL CLOSE_CURLY_SYMBOL
;

unblockExpression :
    unblockExpression op=(MULT_OPERATOR | DIV_OPERATOR) unblockExpression
    | unblockExpression op=(PLUS_OPERATOR | MINUS_OPERATOR) unblockExpression
    | unblockExpression op=(GREATER_THAN_OPERATOR | GREATER_OR_EQUAL_OPERATOR | LESS_THAN_OPERATOR | LESS_OR_EQUAL_OPERATOR) unblockExpression
    | unblockExpression op=(EQUAL_OPERATOR | NOT_EQUAL_OPERATOR) unblockExpression
    | unblockExpression OPEN_PAR_SYMBOL expressionList CLOSE_PAR_SYMBOL 
    | QUOTED_STRING
    | CONST
    | IDENTIFIER
;

ifExpression : 
    IF_SYMBOL unblockExpression blockExpression elseExpression
    | IF_SYMBOL unblockExpression blockExpression
;
elseExpression : 
    ELSE_SYMBOL blockExpression
    | ELSE_SYMBOL ifExpression
;

expressionList :
    (expressionStmt (',' expressionStmt)*)?
;


semiexpressionStmt :
    blockExpression SEMICOLON_SYMBOL
    | ifExpression SEMICOLON_SYMBOL
    | unblockExpression SEMICOLON_SYMBOL
;

expressionStmt :
    blockExpression 
    | ifExpression 
    | unblockExpression 
;

tupleType :
    OPEN_PAR_SYMBOL CLOSE_PAR_SYMBOL
;
type :
    tupleType
    | IDENTIFIER
;
localStmt :
    LET_SYMBOL IDENTIFIER COLON_SYMBOL type SEMICOLON_SYMBOL
    | LET_SYMBOL IDENTIFIER COLON_SYMBOL type ASSIGN_OPERATOR blockExpression SEMICOLON_SYMBOL
    | LET_SYMBOL IDENTIFIER COLON_SYMBOL type ASSIGN_OPERATOR unblockExpression SEMICOLON_SYMBOL
    | LET_SYMBOL IDENTIFIER COLON_SYMBOL type ASSIGN_OPERATOR ifExpression SEMICOLON_SYMBOL
;

param :
    IDENTIFIER COLON_SYMBOL type
;
paramList :
    (param (',' param)*)?
;
functionStmt : 
    FUN_SYMBOL IDENTIFIER OPEN_PAR_SYMBOL paramList CLOSE_PAR_SYMBOL JSON_SEPARATOR_SYMBOL type blockExpression
;

statement :
    localStmt
    | functionStmt
    | expressionStmt
    | semiexpressionStmt
;

statements :
    statement
    | statement statements
;

module :
    statements EOF
;
