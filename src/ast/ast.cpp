#include "ast.h"

namespace dp {
namespace internal {

std::string ASTNode::retType(){
	return type;
}

void ASTNode::setType(std::string newType){
	type = newType;
}


}
}