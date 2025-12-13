/* ast.hpp.  Generated automatically by treecc */
#ifndef __yy_ast_hpp
#define __yy_ast_hpp
#line 3 "ast.tc"

    #include <vector>
    #include <string>
    #include <unordered_set>
    #include <unordered_map>
    #include <stdexcept>
    
    enum class BinaryOperator
    {
        PLUS, MINUS, MULT, DIV, MOD,
        LESS_THAN, GREATER_THAN, LESS_EQUAL, GREATER_EQUAL,
        EQUAL, DISTINCT,
        AND, OR
    };
    
    enum class UnaryOperator
    {
        NOT,
        NEGATE
    };
    
    std::string BinaryOpToString(BinaryOperator op);
    std::string UnaryOpToString(UnaryOperator op);
    
    class AstNode;
    using NodeVector = std::vector<AstNode*>;
    using StdString = std::string;
    using USet = std::unordered_set<std::string>;
    using VarMap = std::unordered_map<std::string, bool>;

struct Location {
    int line;
    int column;
    Location(int l = 0, int c = 0) : line(l), column(c) {}
};
#line 41 "ast.hpp"

#include <new>

const int AstNode_kind = 1;
const int Program_kind = 2;
const int Statement_kind = 3;
const int Expression_kind = 5;
const int IdentList_kind = 18;
const int IdentDecl_kind = 19;
const int StatementList_kind = 4;
const int AssignmentStmt_kind = 12;
const int IfStmt_kind = 13;
const int WhileStmt_kind = 14;
const int PrintStmt_kind = 15;
const int BlockStmt_kind = 16;
const int VarDeclStmt_kind = 17;
const int ArrayDeclStmt_kind = 21;
const int VarExpression_kind = 6;
const int IntegerExpr_kind = 7;
const int FloatExpr_kind = 8;
const int BinaryExpr_kind = 9;
const int UnaryExpr_kind = 10;
const int InputStmt_kind = 11;
const int ArrayAccess_kind = 20;
const int ParExpr_kind = 22;

class AstNode;
class Program;
class Statement;
class Expression;
class IdentList;
class IdentDecl;
class StatementList;
class AssignmentStmt;
class IfStmt;
class WhileStmt;
class PrintStmt;
class BlockStmt;
class VarDeclStmt;
class ArrayDeclStmt;
class VarExpression;
class IntegerExpr;
class FloatExpr;
class BinaryExpr;
class UnaryExpr;
class InputStmt;
class ArrayAccess;
class ParExpr;

class YYNODESTATE
{
public:

	YYNODESTATE();
	virtual ~YYNODESTATE();

#line 1 "cpp_skel.h"
private:

	struct YYNODESTATE_block *blocks__;
	struct YYNODESTATE_push *push_stack__;
	int used__;
#line 104 "ast.hpp"
private:

	static YYNODESTATE *state__;

public:

	static YYNODESTATE *getState()
		{
			if(state__) return state__;
			state__ = new YYNODESTATE();
			return state__;
		}

public:

	void *alloc(size_t);
	void dealloc(void *, size_t);
	int push();
	void pop();
	void clear();
	virtual void failed();
	virtual const char *currFilename() const;
	virtual long currLinenum() const;

};

class AstNode
{
protected:

	int kind__;
	const char *filename__;
	long linenum__;

public:

	int getKind() const { return kind__; }
	const char *getFilename() const { return filename__; }
	long getLinenum() const { return linenum__; }
	void setFilename(const char *filename) { filename__ = filename; }
	void setLinenum(long linenum) { linenum__ = linenum; }

	void *operator new(size_t);
	void operator delete(void *, size_t);

protected:

	AstNode();

public:

	virtual StdString toCpp(USet & varSet) = 0;

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~AstNode();

};

class Program : public AstNode
{
public:

	Program(AstNode * stmts);

public:

	AstNode * stmts;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~Program();

};

class Statement : public AstNode
{
protected:

	Statement();

public:

	virtual StdString toCpp(USet & varSet) = 0;

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~Statement();

};

class Expression : public AstNode
{
protected:

	Expression();

public:

	virtual StdString toCpp(USet & varSet) = 0;

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~Expression();

};

class IdentList : public AstNode
{
public:

	IdentList(NodeVector idents);

public:

	NodeVector idents;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~IdentList();

};

class IdentDecl : public AstNode
{
public:

	IdentDecl(AstNode * identifier, AstNode * initExpr);

public:

	AstNode * identifier;
	AstNode * initExpr;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~IdentDecl();

};

class StatementList : public Statement
{
public:

	StatementList(NodeVector stmts);

public:

	NodeVector stmts;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~StatementList();

};

class AssignmentStmt : public Statement
{
public:

	AssignmentStmt(AstNode * lhs, AstNode * rhs);

public:

	AstNode * lhs;
	AstNode * rhs;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~AssignmentStmt();

};

class IfStmt : public Statement
{
public:

	IfStmt(AstNode * condition, AstNode * thenStmt, AstNode * elseStmt);

public:

	AstNode * condition;
	AstNode * thenStmt;
	AstNode * elseStmt;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~IfStmt();

};

class WhileStmt : public Statement
{
public:

	WhileStmt(AstNode * condition, AstNode * body);

public:

	AstNode * condition;
	AstNode * body;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~WhileStmt();

};

class PrintStmt : public Statement
{
public:

	PrintStmt(AstNode * expr);

public:

	AstNode * expr;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~PrintStmt();

};

class BlockStmt : public Statement
{
public:

	BlockStmt(AstNode * stmts);

public:

	AstNode * stmts;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~BlockStmt();

};

class VarDeclStmt : public Statement
{
public:

	VarDeclStmt(AstNode * firstIdent, AstNode * identList);

public:

	AstNode * firstIdent;
	AstNode * identList;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~VarDeclStmt();

};

class ArrayDeclStmt : public Statement
{
public:

	ArrayDeclStmt(AstNode * identifier, AstNode * arrayAccess);

public:

	AstNode * identifier;
	AstNode * arrayAccess;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~ArrayDeclStmt();

};

class VarExpression : public Expression
{
public:

	VarExpression(StdString var, int line, int column);

public:

	StdString var;
	int line;
	int column;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~VarExpression();

};

class IntegerExpr : public Expression
{
public:

	IntegerExpr(int value);

public:

	int value;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~IntegerExpr();

};

class FloatExpr : public Expression
{
public:

	FloatExpr(float value);

public:

	float value;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~FloatExpr();

};

class BinaryExpr : public Expression
{
public:

	BinaryExpr(AstNode * left, BinaryOperator op, AstNode * right);

public:

	AstNode * left;
	BinaryOperator op;
	AstNode * right;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~BinaryExpr();

};

class UnaryExpr : public Expression
{
public:

	UnaryExpr(UnaryOperator op, AstNode * operand);

public:

	UnaryOperator op;
	AstNode * operand;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~UnaryExpr();

};

class InputStmt : public Expression
{
public:

	InputStmt();

public:

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~InputStmt();

};

class ArrayAccess : public Expression
{
public:

	ArrayAccess(AstNode * index);

public:

	AstNode * index;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~ArrayAccess();

};

class ParExpr : public Expression
{
public:

	ParExpr(AstNode * expr);

public:

	AstNode * expr;

	virtual StdString toCpp(USet & varSet);

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~ParExpr();

};



#endif
