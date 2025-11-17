#include "astnode.hpp"
#include <iostream>

void printIndent(int indent) {
    for (int i = 0; i < indent; ++i) std::cout << " ";
}

// ProgramNode implementation
ProgramNode::~ProgramNode() {
    for (auto& decl : declarations) delete decl;
}

void ProgramNode::addDecl(DeclNode* decl) {
    declarations.push_back(decl);
}

void ProgramNode::print(int indent) const {
    printIndent(indent);
    std::cout << "ProgramNode:\n";
    for (auto& decl : declarations) decl->print(indent + 2);
}

// Expression nodes
void IdentifierNode::print(int indent) const {
    printIndent(indent); std::cout << "Identifier: " << name << "\n";
}

void IntegerNode::print(int indent) const {
    printIndent(indent); std::cout << "Integer: " << value << "\n";
}

void FloatNode::print(int indent) const {
    printIndent(indent); std::cout << "Float: " << value << "\n";
}

void BoolNode::print(int indent) const {
    printIndent(indent); std::cout << "Bool: " << (value ? "true" : "false") << "\n";
}

void BinaryOpNode::print(int indent) const {
    printIndent(indent); std::cout << "BinaryOp: " << op << "\n";
    if (left) { printIndent(indent + 2); std::cout << "Left:\n"; left->print(indent + 4); }
    if (right) { printIndent(indent + 2); std::cout << "Right:\n"; right->print(indent + 4); }
}

void UnaryOpNode::print(int indent) const {
    printIndent(indent); std::cout << "UnaryOp: " << op << "\n";
    if (operand) operand->print(indent + 2);
}

void FunctionCallNode::print(int indent) const {
    printIndent(indent); std::cout << "FunctionCall: " << functionName << "\n";
    if (!arguments.empty()) {
        printIndent(indent + 2); std::cout << "Arguments:\n";
        for (auto arg : arguments) arg->print(indent + 4);
    }
}

// Type and Parameter nodes
void TypeNode::print(int indent) const {
    printIndent(indent); std::cout << "Type: " << typeName << "\n";
}

void ParamNode::print(int indent) const {
    printIndent(indent); std::cout << "Parameter: " << paramName << "\n";
    if (type) type->print(indent + 2);
}

// Declaration nodes
void VarDeclNode::print(int indent) const {
    printIndent(indent); std::cout << (isLet ? "LetDeclaration:" : "VarDeclaration:") << "\n";
    printIndent(indent + 2); std::cout << "Variable: " << varName << "\n";
    if (type) type->print(indent + 2);
    if (value) { printIndent(indent + 2); std::cout << "Value:\n"; value->print(indent + 4); }
}

void FunctionDeclNode::print(int indent) const {
    printIndent(indent); std::cout << "FunctionDeclaration: " << functionName << "\n";
    if (!parameters.empty()) {
        printIndent(indent + 2); std::cout << "Parameters:\n";
        for (auto param : parameters) param->print(indent + 4);
    }
    if (returnType) { printIndent(indent + 2); std::cout << "ReturnType:\n"; returnType->print(indent + 4); }
    if (!body.empty()) {
        printIndent(indent + 2); std::cout << "Body:\n";
        for (auto item : body) item->print(indent + 4);
    }
}

// Statement nodes
void AssignmentStmtNode::print(int indent) const {
    printIndent(indent); std::cout << "AssignmentStatement:\n";
    printIndent(indent + 2); std::cout << "Variable: " << varName << "\n";
    if (value) { printIndent(indent + 2); std::cout << "Value:\n"; value->print(indent + 4); }
}

void ReturnStmtNode::print(int indent) const {
    printIndent(indent); std::cout << "ReturnStatement:\n";
    if (value) value->print(indent + 2);
}

void PrintStmtNode::print(int indent) const {
    printIndent(indent); std::cout << "PrintStatement:\n";
    if (expr) expr->print(indent + 2);
}

void IfStmtNode::print(int indent) const {
    printIndent(indent); std::cout << "IfStatement:\n";
    if (condition) { printIndent(indent + 2); std::cout << "Condition:\n"; condition->print(indent + 4); }
    if (!thenBlock.empty()) {
        printIndent(indent + 2); std::cout << "ThenBlock:\n";
        for (auto item : thenBlock) item->print(indent + 4);
    }
    if (!elseBlock.empty()) {
        printIndent(indent + 2); std::cout << "ElseBlock:\n";
        for (auto item : elseBlock) item->print(indent + 4);
    }
}

void WhileStmtNode::print(int indent) const {
    printIndent(indent); std::cout << "WhileStatement:\n";
    if (condition) { printIndent(indent + 2); std::cout << "Condition:\n"; condition->print(indent + 4); }
    if (!body.empty()) {
        printIndent(indent + 2); std::cout << "Body:\n";
        for (auto item : body) item->print(indent + 4);
    }
}