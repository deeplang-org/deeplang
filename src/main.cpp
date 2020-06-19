#include <iostream>
#include "antlr4-runtime.h"
#include "DLLexer.h"
#include "DLParser.h"

using namespace antlr4;
using namespace std;




using namespace std;


string readFileIntoString(const char * filename)
{
  ifstream ifile(filename);
  //将文件读入到ostringstream对象buf中
  ostringstream buf;
  char ch;
  while(buf&&ifile.get(ch))
    buf.put(ch);
  //返回与流对象buf关联的字符串
  return buf.str();
}

int main(int argc, const char **argv) {
  string s = readFileIntoString(argv[1]);

  ANTLRInputStream input(s);
  DLLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  tokens.fill();
  for (auto token : tokens.getTokens()) {
    std::cout << token->toString() << std::endl;
  }

  DLParser parser(&tokens);
  tree::ParseTree *tree = parser.program();


  std::cout << tree->toStringTree(&parser) << std::endl;

  return 0;
}
