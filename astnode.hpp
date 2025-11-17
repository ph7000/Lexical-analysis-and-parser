#ifndef ASTNODE_HPP
#define ASTNODE_HPP

#include <vector>
#include <string>

// Base ASTNode class
class ASTNode {
 public:
    virtual ~ASTNode() = default;
    virtual void print(int indent = 0) const = 0;
};

class CodeItemNode : public ASTNode {};
class DeclNode : public CodeItemNode {};

class ProgramNode : public ASTNode {
 public:
    std::vector<DeclNode*> declarations;
    ~ProgramNode();
    void addDecl(DeclNode* decl);
    void print(int indent = 0) const override;
};

// Expression nodes
class ExprNode : public ASTNode { public: virtual ~ExprNode() = default; };

class IdentifierNode : public ExprNode {
 public:
    std::string name;
    IdentifierNode(const std::string& n) : name(n) {}
    void print(int indent = 0) const override;
};

class IntegerNode : public ExprNode {
 public:
    int value;
    IntegerNode(int v) : value(v) {}
    void print(int indent = 0) const override;
};

class FloatNode : public ExprNode {
 public:
    double value;
    FloatNode(double v) : value(v) {}
    void print(int indent = 0) const override;
};

class BoolNode : public ExprNode {
 public:
    bool value;
    BoolNode(bool v) : value(v) {}
    void print(int indent = 0) const override;
};

class BinaryOpNode : public ExprNode {
 public:
    ExprNode* left; std::string op; ExprNode* right;
    BinaryOpNode(ExprNode* l, const std::string& o, ExprNode* r) : left(l), op(o), right(r) {}
    ~BinaryOpNode() { delete left; delete right; }
    void print(int indent = 0) const override;
};

class UnaryOpNode : public ExprNode {
 public:
    std::string op; ExprNode* operand;
    UnaryOpNode(const std::string& o, ExprNode* e) : op(o), operand(e) {}
    ~UnaryOpNode() { delete operand; }
    void print(int indent = 0) const override;
};

class FunctionCallNode : public ExprNode {
 public:
    std::string functionName; std::vector<ExprNode*> arguments;
    FunctionCallNode(const std::string& name) : functionName(name) {}
    ~FunctionCallNode() { for (auto arg : arguments) delete arg; }
    void addArgument(ExprNode* arg) { arguments.push_back(arg); }
    void print(int indent = 0) const override;
};

// Type and Parameter nodes
class TypeNode : public ASTNode {
 public:
    std::string typeName;
    TypeNode(const std::string& name) : typeName(name) {}
    void print(int indent = 0) const override;
};

class ParamNode : public ASTNode {
 public:
    std::string paramName; TypeNode* type;
    ParamNode(const std::string& name, TypeNode* t) : paramName(name), type(t) {}
    ~ParamNode() { delete type; }
    void print(int indent = 0) const override;
};

// Statement nodes
class StmtNode : public DeclNode { public: virtual ~StmtNode() = default; };

class VarDeclNode : public DeclNode {
 public:
    bool isLet; std::string varName; TypeNode* type; ExprNode* value;
    VarDeclNode(bool let, const std::string& name, TypeNode* t, ExprNode* val) : isLet(let), varName(name), type(t), value(val) {}
    ~VarDeclNode() { delete type; delete value; }
    void print(int indent = 0) const override;
};

class FunctionDeclNode : public DeclNode {
 public:
    std::string functionName; std::vector<ParamNode*> parameters; TypeNode* returnType; std::vector<ASTNode*> body;
    FunctionDeclNode(const std::string& name, TypeNode* retType) : functionName(name), returnType(retType) {}
    ~FunctionDeclNode() { for (auto param : parameters) delete param; delete returnType; for (auto item : body) delete item; }
    void addParameter(ParamNode* param) { parameters.push_back(param); }
    void addBodyItem(ASTNode* item) { body.push_back(item); }
    void print(int indent = 0) const override;
};

class AssignmentStmtNode : public StmtNode {
 public:
    std::string varName; ExprNode* value;
    AssignmentStmtNode(const std::string& name, ExprNode* val) : varName(name), value(val) {}
    ~AssignmentStmtNode() { delete value; }
    void print(int indent = 0) const override;
};

class ReturnStmtNode : public StmtNode {
 public:
    ExprNode* value;
    ReturnStmtNode(ExprNode* val) : value(val) {}
    ~ReturnStmtNode() { delete value; }
    void print(int indent = 0) const override;
};

class PrintStmtNode : public StmtNode {
 public:
    ExprNode* expr;
    PrintStmtNode(ExprNode* e) : expr(e) {}
    ~PrintStmtNode() { delete expr; }
    void print(int indent = 0) const override;
};

class IfStmtNode : public StmtNode {
 public:
    ExprNode* condition; std::vector<ASTNode*> thenBlock; std::vector<ASTNode*> elseBlock;
    IfStmtNode(ExprNode* cond) : condition(cond) {}
    ~IfStmtNode() { delete condition; for (auto item : thenBlock) delete item; for (auto item : elseBlock) delete item; }
    void addThenItem(ASTNode* item) { thenBlock.push_back(item); }
    void addElseItem(ASTNode* item) { elseBlock.push_back(item); }
    void print(int indent = 0) const override;
};

class WhileStmtNode : public StmtNode {
 public:
    ExprNode* condition; std::vector<ASTNode*> body;
    WhileStmtNode(ExprNode* cond) : condition(cond) {}
    ~WhileStmtNode() { delete condition; for (auto item : body) delete item; }
    void addBodyItem(ASTNode* item) { body.push_back(item); }
    void print(int indent = 0) const override;
};

#endif // ASTNODE_HPP