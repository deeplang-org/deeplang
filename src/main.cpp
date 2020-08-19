#include <iostream>
#include <fstream>
#include "antlr4-runtime.h"
#include "wabt/src/option-parser.h"
// #include "DLLexer.h"
// #include "DLParser.h"
#include "parsing/parsing.h"


// using namespace antlr4;
using namespace wabt;


static std::string s_infile;
static std::string s_outfile;
static bool s_interactive_mode = false;


static const char s_description[] =
R"(  Deeplang compiler
)";

static void parseOptions(int argc, char** argv) {
  OptionParser parser("dp", s_description);

  parser.AddOption('v', "version", "current version: ", []() {
  });
  parser.AddOption(
    'o', "output", "FILENAME",
    "Output file for the compiled wasm file",
    [](const char* argument) {
    s_outfile = argument;
    ConvertBackslashToSlash(&s_outfile);
  });
  parser.AddOption('i', "interactive", "REPL",
    []() { s_interactive_mode = true; });
  parser.AddArgument("filename", OptionParser::ArgumentCount::One,
    [](const char* argument) {
    s_infile = argument;
    ConvertBackslashToSlash(&s_infile);
  });
  parser.Parse(argc, argv);
}


int main(int argc, char **argv) {
  parseOptions(argc, argv);

  if (s_interactive_mode) {
    // repl
    return 0;
  }

  if (!s_infile.size()) {
    return -1;
  }
  
  std::ifstream infile(s_infile);
  if (!infile.is_open()) {
    return -1;
  }

  dp::internal::Parser* parser = new dp::internal::Parser();
  antlr4::ANTLRInputStream input(infile);
  parser->parseModule(input);
  // DLLexer lexer(&input);
  // CommonTokenStream tokens(&lexer);

  // tokens.fill();
  // for (auto token : tokens.getTokens()) {
  //   std::cout << token->toString() << std::endl;
  // }

  // DLParser parser(&tokens);
  // tree::ParseTree *tree = parser.program();

  // std::cout << tree->toStringTree(&parser) << std::endl;

  return 0;
}
