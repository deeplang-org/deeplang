#include "ast.h"

namespace dp {
namespace internal {

NodeType ASTNode::retType(){
	return type;
}

void ASTNode::setType(NodeType newType){
	type = newType;
}


}
}