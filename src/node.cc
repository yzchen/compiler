#include "node.hh"
#include "util.hh"

bool haserror = false;
bool globalflag = true;
/*
void Node::setLoc(Loc* loc) {
    this->loc->first_line   = loc->first_line;
    this->loc->first_column = loc->first_column;
    this->loc->last_line    = loc->last_line;
    this->loc->last_column  = loc->last_column;
}
*/

// ====================================
// append
// ====================================

void BlockItemListNode::append(Node *node)
{
    v.push_back((BlockItemNode *)node);
}

void CompUnitNode::append(Node *node)
{
    v.push_back(node);
}

void ConstDefNode::append(Node *node)
{
    v.push_back((ANode *)node);
}

void ExppNode::append(Node *node)
{
    v.push_back((ExpNode *)node);
}

void VarListNode::append(Node *node)
{
    v.push_back((ExpNode *)node);
}

void ArgsNode::append(Node *node){
    v.push_back((SimpleDeclNode*)node);
}

void IdentListNode::append(Node *node){
    v.push_back((Node*)node);
}

void InnerStructDeclNode::append(Node *node){
    v.push_back((SimpleDeclNode *)node);
}

Node *Error(const char *Str) {
	printf("Error: %s\n", Str);
	return 0;
}

Value *ErrorV(const char *Str) {
	Error(Str);
	return 0;
}

// ====================================
// dump AST
// ====================================
// the result is similar to the command line program 'tree'
// I highly recommend you to learn more about graphviz and DOT

// prefix[] contains current line's prefixs
// Its validating parts are prefix[0..indent-1] (indent is an argument passed
// among the following functions)
// static int prefix[100];

// static void drawprefix(int indent){
//     int i;
//     for (i=0; i<indent; i++){
//         switch (prefix[i]) {
//             case 0:
//                 printf("    ");
//                 break;
//             case 1:
//                 printf("│   ");
//                 break;
//             case 2:
//                 printf("├── ");
//                 break;
//             case 3:
//                 printf("└── ");
//                 break;
//             default:
//                 printf("perr");
//         }
//     }

//     if (indent > 0) // whenever drew a line's prefix, update the last element
//     {
//         if (prefix[indent-1] == 3)
//             prefix[indent-1] = 0;
//         else
//             prefix[indent-1] = 1;
//     }
// }

// void NumNode::printast(FILE *fp, int indent)
// {
//     drawprefix(indent);
//     fprintf(fp, "%d\n", val);
// }

// void VarNode::printast(FILE *fp, int indent)
// {
//     drawprefix(indent);
//     fprintf(fp, "%s\n", name->c_str());
// }

// void BinaryExpNode::printast(FILE *fp, int indent)
// {
//     drawprefix(indent);
//     fprintf(fp, "%c\n", op);
//     prefix[indent] = 2;
//     lhs->printast(fp, indent+1);
//     prefix[indent] = 3;
//     rhs->printast(fp, indent+1);
// }

// void UnaryExpNode::printast(FILE *fp, int indent)
// {
//     drawprefix(indent);
//     fprintf(fp, "%c\n", op);
//     prefix[indent] = 3;
//     operand->printast(fp, indent+1);
// }

// void AssignNode::printast(FILE *fp, int indent)
// {
//     drawprefix(indent);
//     fprintf(fp, "%c\n", '=');
//     prefix[indent] = 2;
//     var->printast(fp, indent+1);
//     prefix[indent] = 3;
//     exp->printast(fp, indent+1);
// }


// void LineNode::printast(FILE *fp, int indent)
// {
//     asgn->printast(fp, indent);
// }

// void InputNode::printast(FILE *fp, int indent)
// {
//     // InputNode is certainly the root of AST
//     // so indent is certainly 0
//     fprintf(fp, "input\n");
//     vector<LineNode*>::iterator i;
//     for (i=lines.begin(); i!=lines.end(); i++)
//     {
//         if (i+1==lines.end())
//             prefix[0] = 3;
//         else
//             prefix[0] = 2;
//         (*i)->printast(fp, 1);
//     }
// }