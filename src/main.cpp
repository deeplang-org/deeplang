#include "antlr_runtime/antlr4-runtime.h"
#include "wabt/src/option-parser.h"

#include "codegen/codegen.h"
#include "parsing/parsing.h"

#include <fstream>
#include <iostream>

//using namespace antlr4;
using namespace dp;
using namespace dp::internal;
using namespace wabt;

static std::string s_infile;
static std::string s_outfile;
static bool        s_interactive_mode = false;

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

int main(int argc, char** argv) {
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

	Parser*                  parser = new Parser();
	antlr4::ANTLRInputStream input(infile);

	auto module = parser->parseModule(input);

	if (!s_outfile.size())
		s_outfile = "a.wasm";

	auto result = CodeGen::GenerateWasmToFile(module, s_outfile);
	if (!result)
		return -1;

	return 0;
}
