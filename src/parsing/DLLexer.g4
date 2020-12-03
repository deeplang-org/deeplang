lexer grammar DLLexer;

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


//-------------------------------------------------------------------------------------------------

// $antlr-format alignTrailingComments on, columnLimit 150, maxEmptyLinesToKeep 1, reflowComments off, useTab off
// $antlr-format allowShortRulesOnASingleLine on, alignSemicolons ownLine

// TODO: predefined.tokens
options {
    tokenVocab = DLLexer; // Certain tokens in a predefined order for simpler checks.
}

tokens {
    NOT2_SYMBOL,
    CONCAT_PIPES_SYMBOL,

    // Tokens assigned in NUMBER rule.
    INT_NUMBER, // NUM in sql_yacc.yy
    LONG_NUMBER,
    ULONGLONG_NUMBER
}

@postinclude {
}

//-------------------------------------------------------------------------------------------------

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

//-------------------------------------------------------------------------------------------------

// Operators
//
ASSIGN_OPERATOR:           '=';
EQUAL_OPERATOR:            '==';
GREATER_OR_EQUAL_OPERATOR: '>=';
GREATER_THAN_OPERATOR:     '>';
LESS_OR_EQUAL_OPERATOR:    '<=';
LESS_THAN_OPERATOR:        '<';
NOT_EQUAL_OPERATOR:        '!=';
NOT_EQUAL2_OPERATOR:       '<>' -> type(NOT_EQUAL_OPERATOR);

//
PLUS_OPERATOR:  '+';
MINUS_OPERATOR: '-';
MULT_OPERATOR:  '*';
DIV_OPERATOR:   '/';
MOD_OPERATOR: '%';
BITWISE_XOR_OPERATOR: '^';


LOGICAL_NOT_OPERATOR: '!';
BITWISE_NOT_OPERATOR: '~';
/*
SHIFT_LEFT_OPERATOR:  '<<';
SHIFT_RIGHT_OPERATOR: '>>';
*/

//
LOGICAL_AND_OPERATOR: '&&';
BITWISE_AND_OPERATOR: '&';

LOGICAL_OR_OPERATOR:
    '||' 
;
BITWISE_OR_OPERATOR: '|';


//
DOT_SYMBOL:         '.';
COMMA_SYMBOL:       ',';
SEMICOLON_SYMBOL:   ';';
COLON_SYMBOL:       ':';
OPEN_PAR_SYMBOL:    '(';
CLOSE_PAR_SYMBOL:   ')';
OPEN_CURLY_SYMBOL:  '{';
CLOSE_CURLY_SYMBOL: '}';
OPEN_SQUARE_SYMBOL:  '[';
CLOSE_SQUARE_SYMBOL: ']';
// UNDERLINE_SYMBOL:   '_';

ALIAS_SYMBOL:       '::';

//
JSON_SEPARATOR_SYMBOL:          '->';  // MYSQL
SEPARATOR_SYMBOL:          '=>';

// The MySQL server parser uses custom code in its lexer to allow base alphanum chars (and ._$) as variable name.
// For this it handles user variables in 2 different ways and we have to model this to match that behavior.
AT_SIGN_SYMBOL: '@';
// AT_TEXT_SUFFIX: '@' SIMPLE_IDENTIFIER;

// AT_AT_SIGN_SYMBOL: '@@';

// NULL2_SYMBOL: '\\N';
PARAM_MARKER: '?';

DOLLAR_SYMBOL: '$';

fragment A: [aA];
fragment B: [bB];
fragment C: [cC];
fragment D: [dD];
fragment E: [eE];
fragment F: [fF];
fragment G: [gG];
fragment H: [hH];
fragment I: [iI];
fragment J: [jJ];
fragment K: [kK];
fragment L: [lL];
fragment M: [mM];
fragment N: [nN];
fragment O: [oO];
fragment P: [pP];
fragment Q: [qQ];
fragment R: [rR];
fragment S: [sS];
fragment T: [tT];
fragment U: [uU];
fragment V: [vV];
fragment W: [wW];
fragment X: [xX];
fragment Y: [yY];
fragment Z: [zZ];

fragment NONZERODIGIT:  [1-9];
fragment DIGIT:    [0-9];
fragment DIGITS:   DIGIT+;
fragment ZERO: [0];
//fragment HEXDIGIT: [0-9a-fA-F];

CONST:     INTEGERCONST;

INTEGERCONST: ZERO | NONZERODIGIT | (NONZERODIGIT DIGITS);

// Only lower case 'x' and 'b' count for hex + bin numbers. Otherwise it's an identifier.
//HEX_NUMBER: ('0x' HEXDIGIT+) | ('x\'' HEXDIGIT+ '\'');
//BIN_NUMBER: ('0b' [01]+) | ('b\'' [01]+ '\'');

INT_NUMBER: DIGITS {  };

// Float types must be handled first or the DOT_IDENTIIFER rule will make them to identifiers
// (if there is no leading digit before the dot).
DECIMAL_NUMBER: DIGITS? DOT_SYMBOL DIGITS;
FLOAT_NUMBER:   (DIGITS? DOT_SYMBOL)? DIGITS [eE] (MINUS_OPERATOR | PLUS_OPERATOR)? DIGITS;

// Special rule that should also match all keywords if they are directly preceded by a dot.
// Hence it's defined before all keywords.
// Here we make use of the ability in our base lexer to emit multiple tokens with a single rule.
//DOT_IDENTIFIER:
//    DOT_SYMBOL LETTER_WHEN_UNQUOTED_NO_DIGIT LETTER_WHEN_UNQUOTED* { emitDot(); } -> type(IDENTIFIER)
//;

// TODO: SYMBOLS
//    let  letmut  fun  class  interface  extends  impl
//    public  private  if  then  else  switch  case  for
//    while  loop  prop  super  (switch) this
//    new break return mut sig constructor


LETMUT_SYMBOL:      L E T M U T;
LET_SYMBOL:         L E T;
FUN_SYMBOL:         F U N;
CLASS_SYMBOL:       C L A S S;
INTERFACE_SYMBOL:   I N T E R F A C E;
EXTENDS_SYMBOL:     E X T E N D S;
IMPL_SYMBOL:        I M P L;
PUBLIC_SYMBOL:      P U B L I C;
PRIVATE_SYMBOL:     P R I V A T E;
IF_SYMBOL:          I F;
THEN_SYMBOL:        T H E N;
ELSE_SYMBOL:        E L S E;
SWITCH_SYMBOL:      S W I T C H;
CASE_SYMBOL:        C A S E;
FOR_SYMBOL:         F O R;
WHILE_SYMBOL:       W H I L E;
LOOP_SYMBOL:        L O O P;
PROP_SYMBOL:        P R O P;
SUPER_SYMBOL:       S U P E R;
THIS_SYMBOL:        T H I S;
NEW_SYMBOL:         N E W;
BREAK_SYMBOL:       B R E A K;
RETURN_SYMBOL:      R E T U R N;
MUT_SYMBOL:         M U T;
SIG_SYMBOL:         S I G;
CONSTRUCTOR_SYMBOL: C O N S T R U C T O R;


// White space handling
WHITESPACE: [ \t\f\r\n] -> channel(HIDDEN); // Ignore whitespaces.

// Input not covered elsewhere (unless quoted).
//INVALID_INPUT:
//    [\u0001-\u0008]   // Control codes.
//    | '\u000B'        // Line tabulation.
//    | '\u000C'        // Form feed.
//    | [\u000E-\u001F] // More control codes.
//    | '['
//    | ']'
//;

// String and text types.

// The underscore charset token is used to defined the repertoire of a string, though it conflicts
// with normal identifiers, which also can start with an underscore.
// UNDERSCORE_CHARSET: UNDERLINE_SYMBOL [a-z0-9]+ { setType(checkCharset(getText())); };

// Identifiers might start with a digit, even though it is discouraged, and may not consist entirely of digits only.
// All keywords above are automatically excluded.
//IDENTIFIER:
//    DIGITS+ [eE] (LETTER_WHEN_UNQUOTED_NO_DIGIT LETTER_WHEN_UNQUOTED*)? // Have to exclude float pattern, as this rule matches more.
//    | DIGITS+ LETTER_WITHOUT_FLOAT_PART LETTER_WHEN_UNQUOTED*
//    | LETTER_WHEN_UNQUOTED_NO_DIGIT LETTER_WHEN_UNQUOTED* // INT_NUMBER matches first if there are only digits.
//;
//
//NCHAR_TEXT: [nN] SINGLE_QUOTED_TEXT;
IDENTIFIER:
    LETTER_WHEN_UNQUOTED_NO_DIGIT LETTER_WHEN_UNQUOTED*
;

// MySQL supports automatic concatenation of multiple single and double quoted strings if they follow each other as separate
// tokens. This is reflected in the `textLiteral` parser rule.
// Here we handle duplication of quotation chars only (which must be replaced by a single char in the target code).

//
fragment BACK_TICK:    '`';
fragment SINGLE_QUOTE: '\'';
fragment DOUBLE_QUOTE: '"';

// TODO: TEST
//BACK_TICK_QUOTED_ID: BACK_TICK (({!isSqlModeActive(NoBackslashEscapes)}? '\\')? .)*? BACK_TICK;
//
//DOUBLE_QUOTED_TEXT: (
//        DOUBLE_QUOTE (({!isSqlModeActive(NoBackslashEscapes)}? '\\' .)? .)*? DOUBLE_QUOTE
//    )+
//;
//
//SINGLE_QUOTED_TEXT: (
//        SINGLE_QUOTE (({!isSqlModeActive(NoBackslashEscapes)}? '\\')? .)*? SINGLE_QUOTE
//    )+
//;

QUOTED_STRING:
        DOUBLE_QUOTE .*? DOUBLE_QUOTE
;

SINGLE_COMMENT:
     '//' ~[\r\n]* '\r'? '\n' -> skip
;
MULTI_COMMENT: 
     '/*'  .*?  '*/' -> skip
;

// There are 3 types of block comments:
// /* ... */ - The standard multi line comment.
// /*! ... */ - A comment used to mask code for other clients. In MySQL the content is handled as normal code.
// /*!12345 ... */ - Same as the previous one except code is only used when the given number is lower
//                   than the current server version (specifying so the minimum server version the code can run with).
//VERSION_COMMENT_START: ('/*!' DIGITS) (
//        {checkVersion(getText())}? // Will set inVersionComment if the number matches.
//        | .*? '*/'
//    ) -> channel(HIDDEN)
//;

// inVersionComment is a variable in the base lexer.
// TODO: use a lexer mode instead of a member variable.
//MYSQL_COMMENT_START: '/*!' { inVersionComment = true; }                     -> channel(HIDDEN);
//VERSION_COMMENT_END: '*/' {inVersionComment}? { inVersionComment = false; } -> channel(HIDDEN);
BLOCK_COMMENT:       ( '/**/' | '/*' ~[!] .*? '*/')                         -> channel(HIDDEN);

// POUND_COMMENT:    '#' ~([\n\r])*                                   -> channel(HIDDEN);
// DASHDASH_COMMENT: DOUBLE_DASH ([ \t] (~[\n\r])* | LINEBREAK | EOF) -> channel(HIDDEN);
SLASHSLASH_COMMET: DOUBLE_SLASH ([ \t] (~[\n\r])* | LINEBREAK | EOF) -> channel(HIDDEN);

fragment DOUBLE_SLASH:  '//';

// fragment DOUBLE_DASH: '--';
fragment LINEBREAK:   [\n\r];

fragment SIMPLE_IDENTIFIER: (DIGIT | [a-zA-Z_$] | DOT_SYMBOL)+;

fragment ML_COMMENT_HEAD: '/*';
fragment ML_COMMENT_END:  '*/';


fragment NONDIGIT: [a-zA-Z_]; //TODO: define Chars


// As defined in https://dev.mysql.com/doc/refman/8.0/en/identifiers.html.
fragment LETTER_WHEN_UNQUOTED: DIGIT | LETTER_WHEN_UNQUOTED_NO_DIGIT;

fragment LETTER_WHEN_UNQUOTED_NO_DIGIT: [a-zA-Z_$];//\u0080-\uffff];

// Any letter but without e/E and digits (which are used to match a decimal number).
//fragment LETTER_WITHOUT_FLOAT_PART: [a-df-zA-DF-Z_$\u0080-\uffff];
