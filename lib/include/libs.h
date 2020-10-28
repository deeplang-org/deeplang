/*
 * For the purpose of include libs when necessary 
 * 
 */

/*===================ANTLR4===============================*/
#ifdef LIB_ANTLR_RUNTIME
#include "antlr_runtime/antlr4-runtime.h"
#endif

#ifdef LIB_OPTION_PARSER
#include "wabt/src/option-parser.h"
#endif


#ifdef LIB_DLPARSER_BASE_VISITOR_H
#include "DLParserBaseVisitor.h"
#endif 

#ifdef LIB_DLPARSER_VISITOR_H
#include "DLParserVisitor.h"
#endif


#ifdef LIB_WABT_TYPE_H
#include "wabt/src/type.h"
#endif


#ifdef LIB_DLLEXER_H
#include "DLLexer.h"
#endif


#ifdef LIB_DLPARSER_H
#include "DLParser.h"
#endif

#ifdef  LIB_DLPARSERVISITOR_H
#include "DLParserVisitor.h"
#endif



/*===================WABT=================================*/
#ifdef LIB_BINARY_H
#include "wabt/src/binary-writer.h"
#endif


#ifdef LIB_ERROR_H
#include "wabt/src/error.h"
#endif

#ifdef LIB_IR_H
#include "wabt/src/ir.h"
#endif


#ifdef LIB_VALIDATOR_H
#include "wabt/src/validator.h"
#endif




