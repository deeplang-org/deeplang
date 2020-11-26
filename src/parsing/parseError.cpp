#include "parsing/parseError.h"
#include "antlr4-runtime.h"
#include <string>





namespace dp {
namespace internal {

static std::string RED = "\x1B[31m";
static std::string RST = "\x1B[0m";

void ParseErrorHanler::syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line,
                                   size_t charPositionInLine, const std::string &msg, std::exception_ptr e) {
	abort();
}
void ParseErrorHanler::reportAmbiguity(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, size_t startIndex, size_t stopIndex, bool exact,
                     const antlrcpp::BitSet &ambigAlts, antlr4::atn::ATNConfigSet *configs) {

}
void ParseErrorHanler::reportAttemptingFullContext(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, size_t startIndex, size_t stopIndex,
                                 const antlrcpp::BitSet &conflictingAlts, antlr4::atn::ATNConfigSet *configs) {

}
void ParseErrorHanler::reportContextSensitivity(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, size_t startIndex, size_t stopIndex,
                              size_t prediction, antlr4::atn::ATNConfigSet *configs) {

}

} // internal
} // dp