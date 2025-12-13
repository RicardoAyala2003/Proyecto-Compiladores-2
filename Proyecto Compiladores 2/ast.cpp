/* ast.cpp.  Generated automatically by treecc */
#line 40 "ast.tc"

    #include "ast.hpp"
    
    std::string BinaryOpToString(BinaryOperator op)
    {
        switch(op)
        {
            case BinaryOperator::PLUS: return "+";
            case BinaryOperator::MINUS: return "-";
            case BinaryOperator::MULT: return "*";
            case BinaryOperator::DIV: return "/";
            case BinaryOperator::MOD: return "%";
            case BinaryOperator::LESS_THAN: return "<";
            case BinaryOperator::GREATER_THAN: return ">";
            case BinaryOperator::LESS_EQUAL: return "<=";
            case BinaryOperator::GREATER_EQUAL: return ">=";
            case BinaryOperator::EQUAL: return "==";
            case BinaryOperator::DISTINCT: return "!=";
            case BinaryOperator::AND: return "&&";
            case BinaryOperator::OR: return "||";
            default: return "UNKNOWN";
        }
    }
    
    std::string UnaryOpToString(UnaryOperator op)
    {
        switch(op)
        {
            case UnaryOperator::NOT: return "!";
            case UnaryOperator::NEGATE: return "-";
            default: return "UNKNOWN";
        }
    }
    
    VarMap declaredVars;
    bool usesInputFunction = false;
    
 void checkVarDeclared(const std::string& var, int line, int column) {
    if (declaredVars.find(var) == declaredVars.end()) {
        throw std::runtime_error("Error Semántico [Línea " + std::to_string(line) + 
                               ", Columna " + std::to_string(column) + 
                               "]: Variable '" + var + "' no declarada");
    }
}

void checkVarNotRedeclared(const std::string& var, int line, int column) {
    if (declaredVars.find(var) != declaredVars.end()) {
        throw std::runtime_error("Error Semántico [Línea " + std::to_string(line) + 
                               ", Columna " + std::to_string(column) + 
                               "]: Variable '" + var + "' ya fue declarada");
    }
}
#line 56 "ast.cpp"

#include <cstddef>

#define YYNODESTATE_TRACK_LINES 1
#define YYNODESTATE_USE_ALLOCATOR 1
#line 1 "cpp_skel.cc"
/*
 * treecc node allocation routines for C++.
 *
 * Copyright (C) 2001  Southern Storm Software, Pty Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * As a special exception, when this file is copied by treecc into
 * a treecc output file, you may use that output file without restriction.
 */

#ifndef YYNODESTATE_BLKSIZ
#define	YYNODESTATE_BLKSIZ	2048
#endif

/*
 * Types used by the allocation routines.
 */
struct YYNODESTATE_block
{
	char data__[YYNODESTATE_BLKSIZ];
	struct YYNODESTATE_block *next__;

};
struct YYNODESTATE_push
{
	struct YYNODESTATE_push *next__;
	struct YYNODESTATE_block *saved_block__;
	int saved_used__;
};

/*
 * Initialize the singleton instance.
 */
#ifndef YYNODESTATE_REENTRANT
YYNODESTATE *YYNODESTATE::state__ = 0;
#endif

/*
 * Some macro magic to determine the default alignment
 * on this machine.  This will compile down to a constant.
 */
#define	YYNODESTATE_ALIGN_CHECK_TYPE(type,name)	\
	struct _YYNODESTATE_align_##name { \
		char pad; \
		type field; \
	}
#define	YYNODESTATE_ALIGN_FOR_TYPE(type)	\
	offsetof(_YYNODESTATE_align_##type, field)
#define	YYNODESTATE_ALIGN_MAX(a,b)	\
	((a) > (b) ? (a) : (b))
#define	YYNODESTATE_ALIGN_MAX3(a,b,c) \
	(YYNODESTATE_ALIGN_MAX((a), YYNODESTATE_ALIGN_MAX((b), (c))))
YYNODESTATE_ALIGN_CHECK_TYPE(int, int);
YYNODESTATE_ALIGN_CHECK_TYPE(long, long);
#if defined(WIN32) && !defined(__CYGWIN__)
YYNODESTATE_ALIGN_CHECK_TYPE(__int64, long_long);
#else
YYNODESTATE_ALIGN_CHECK_TYPE(long long, long_long);
#endif
YYNODESTATE_ALIGN_CHECK_TYPE(void *, void_p);
YYNODESTATE_ALIGN_CHECK_TYPE(float, float);
YYNODESTATE_ALIGN_CHECK_TYPE(double, double);
#define	YYNODESTATE_ALIGNMENT	\
	YYNODESTATE_ALIGN_MAX( \
			YYNODESTATE_ALIGN_MAX3	\
			(YYNODESTATE_ALIGN_FOR_TYPE(int), \
		     YYNODESTATE_ALIGN_FOR_TYPE(long), \
			 YYNODESTATE_ALIGN_FOR_TYPE(long_long)), \
  	     YYNODESTATE_ALIGN_MAX3 \
		 	(YYNODESTATE_ALIGN_FOR_TYPE(void_p), \
			 YYNODESTATE_ALIGN_FOR_TYPE(float), \
			 YYNODESTATE_ALIGN_FOR_TYPE(double)))

/*
 * Constructor for YYNODESTATE.
 */
YYNODESTATE::YYNODESTATE()
{
	/* Initialize the allocation state */
	blocks__ = 0;
	push_stack__ = 0;
	used__ = 0;

#ifndef YYNODESTATE_REENTRANT
	/* Register this object as the singleton instance */
	if(!state__)
	{
		state__ = this;
	}
#endif
}

/*
 * Destructor for YYNODESTATE.
 */
YYNODESTATE::~YYNODESTATE()
{
	/* Free all node memory */
	clear();

#ifndef YYNODESTATE_REENTRANT
	/* We are no longer the singleton instance */
	if(state__ == this)
	{
		state__ = 0;
	}
#endif
}

#ifdef YYNODESTATE_USE_ALLOCATOR

/*
 * Allocate a block of memory.
 */
void *YYNODESTATE::alloc(size_t size__)
{
	struct YYNODESTATE_block *block__;
	void *result__;

	/* Round the size to the next alignment boundary */
	size__ = (size__ + YYNODESTATE_ALIGNMENT - 1) &
				~(YYNODESTATE_ALIGNMENT - 1);

	/* Do we need to allocate a new block? */
	block__ = blocks__;
	if(!block__ || (used__ + size__) > YYNODESTATE_BLKSIZ)
	{
		if(size__ > YYNODESTATE_BLKSIZ)
		{
			/* The allocation is too big for the node pool */
			return (void *)0;
		}
		block__ = new YYNODESTATE_block;
		if(!block__)
		{
			/* The system is out of memory.  The programmer can
			   inherit the "failed" method to report the
			   out of memory state and/or abort the program */
			failed();
			return (void *)0;
		}
		block__->next__ = blocks__;
		blocks__ = block__;
		used__ = 0;
	}

	/* Allocate the memory and return it */
	result__ = (void *)(block__->data__ + used__);
	used__ += size__;
	return result__;
}

/*
 * Deallocate a block of memory.
 */
void YYNODESTATE::dealloc(void *ptr__, size_t size__)
{
	/* Nothing to do for this type of node allocator */
}

/*
 * Push the node allocation state.
 */
int YYNODESTATE::push()
{
	struct YYNODESTATE_block *saved_block__;
	int saved_used__;
	struct YYNODESTATE_push *push_item__;

	/* Save the current state of the node allocation pool */
	saved_block__ = blocks__;
	saved_used__ = used__;

	/* Allocate space for a push item */
	push_item__ = (struct YYNODESTATE_push *)
			alloc(sizeof(struct YYNODESTATE_push));
	if(!push_item__)
	{
		return 0;
	}

	/* Copy the saved information to the push item */
	push_item__->saved_block__ = saved_block__;
	push_item__->saved_used__ = saved_used__;

	/* Add the push item to the push stack */
	push_item__->next__ = push_stack__;
	push_stack__ = push_item__;
	return 1;
}

/*
 * Pop the node allocation state.
 */
void YYNODESTATE::pop()
{
	struct YYNODESTATE_push *push_item__;
	struct YYNODESTATE_block *saved_block__;
	struct YYNODESTATE_block *temp_block__;

	/* Pop the top of the push stack */
	push_item__ = push_stack__;
	if(push_item__ == 0)
	{
		saved_block__ = 0;
		used__ = 0;
	}
	else
	{
		saved_block__ = push_item__->saved_block__;
		used__ = push_item__->saved_used__;
		push_stack__ = push_item__->next__;
	}

	/* Free unnecessary blocks */
	while(blocks__ != saved_block__)
	{
		temp_block__ = blocks__;
		blocks__ = temp_block__->next__;
		delete temp_block__;
	}
}

/*
 * Clear the node allocation pool completely.
 */
void YYNODESTATE::clear()
{
	struct YYNODESTATE_block *temp_block__;
	while(blocks__ != 0)
	{
		temp_block__ = blocks__;
		blocks__ = temp_block__->next__;
		delete temp_block__;
	}
	push_stack__ = 0;
	used__ = 0;
}

#endif /* YYNODESTATE_USE_ALLOCATOR */

/*
 * Default implementation of functions which may be overridden.
 */
void YYNODESTATE::failed()
{
}

#ifdef YYNODESTATE_TRACK_LINES

const char *YYNODESTATE::currFilename() const
{
	return (const char *)0;
}

long YYNODESTATE::currLinenum() const
{
	return 0;
}

#endif
#line 337 "ast.cpp"
void *AstNode::operator new(size_t size__)
{
	return YYNODESTATE::getState()->alloc(size__);
}

void AstNode::operator delete(void *ptr__, size_t size__)
{
	YYNODESTATE::getState()->dealloc(ptr__, size__);
}

AstNode::AstNode()
{
	this->kind__ = AstNode_kind;
	this->filename__ = YYNODESTATE::getState()->currFilename();
	this->linenum__ = YYNODESTATE::getState()->currLinenum();
}

AstNode::~AstNode()
{
	// not used
}

int AstNode::isA(int kind) const
{
	if(kind == AstNode_kind)
		return 1;
	else
		return 0;
}

const char *AstNode::getKindName() const
{
	return "AstNode";
}

Program::Program(AstNode * stmts)
	: AstNode()
{
	this->kind__ = Program_kind;
	this->stmts = stmts;
}

Program::~Program()
{
	// not used
}

StdString Program::toCpp(USet & varSet)
#line 209 "ast.tc"
{
    declaredVars.clear();
    usesInputFunction = false;
    std::string output = "";
    std::string statements;

    output += "#include<iostream>\n";
    output += "#include<fstream>\n";
    

    statements += stmts->toCpp(varSet); 
    

    if (usesInputFunction) {
        output += "int input() {\n";
        output += "int x;\n";
        output += "std::cin >> x;\n";
        output += "return x;\n";
        output += "}\n";
    }

    output += "int main() {\n";

    for(const auto &var : varSet){
        output += "int " + var + ";\n";
    }

    output += statements;
    output += "return 0;\n}";
    return output;
}
#line 418 "ast.cpp"

int Program::isA(int kind) const
{
	if(kind == Program_kind)
		return 1;
	else
		return AstNode::isA(kind);
}

const char *Program::getKindName() const
{
	return "Program";
}

Statement::Statement()
	: AstNode()
{
	this->kind__ = Statement_kind;
}

Statement::~Statement()
{
	// not used
}

int Statement::isA(int kind) const
{
	if(kind == Statement_kind)
		return 1;
	else
		return AstNode::isA(kind);
}

const char *Statement::getKindName() const
{
	return "Statement";
}

Expression::Expression()
	: AstNode()
{
	this->kind__ = Expression_kind;
}

Expression::~Expression()
{
	// not used
}

int Expression::isA(int kind) const
{
	if(kind == Expression_kind)
		return 1;
	else
		return AstNode::isA(kind);
}

const char *Expression::getKindName() const
{
	return "Expression";
}

IdentList::IdentList(NodeVector idents)
	: AstNode()
{
	this->kind__ = IdentList_kind;
	this->idents = idents;
}

IdentList::~IdentList()
{
	// not used
}

StdString IdentList::toCpp(USet & varSet)
#line 339 "ast.tc"
{
    std::string result;
    for(auto *ident : idents)
    {
        result += ident->toCpp(varSet);
    }
    return result;
}
#line 503 "ast.cpp"

int IdentList::isA(int kind) const
{
	if(kind == IdentList_kind)
		return 1;
	else
		return AstNode::isA(kind);
}

const char *IdentList::getKindName() const
{
	return "IdentList";
}

IdentDecl::IdentDecl(AstNode * identifier, AstNode * initExpr)
	: AstNode()
{
	this->kind__ = IdentDecl_kind;
	this->identifier = identifier;
	this->initExpr = initExpr;
}

IdentDecl::~IdentDecl()
{
	// not used
}

StdString IdentDecl::toCpp(USet & varSet)
#line 349 "ast.tc"
{
    VarExpression* varExpr = reinterpret_cast<VarExpression*>(identifier);
    std::string varName = varExpr->var;
    
    checkVarNotRedeclared(varName, varExpr->line, varExpr->column);
    
    declaredVars[varName] = true;
    varSet.insert(varName);
    
    std::string result;
    if(initExpr != nullptr) {
        result = varName + "=" + initExpr->toCpp(varSet) + ";";
    } 
    return result;
}
#line 548 "ast.cpp"

int IdentDecl::isA(int kind) const
{
	if(kind == IdentDecl_kind)
		return 1;
	else
		return AstNode::isA(kind);
}

const char *IdentDecl::getKindName() const
{
	return "IdentDecl";
}

StatementList::StatementList(NodeVector stmts)
	: Statement()
{
	this->kind__ = StatementList_kind;
	this->stmts = stmts;
}

StatementList::~StatementList()
{
	// not used
}

StdString StatementList::toCpp(USet & varSet)
#line 242 "ast.tc"
{
    std::string statements;
    for(auto *stmt : stmts)
    {
        statements += stmt->toCpp(varSet) + "\n";
    }
    return statements;
}
#line 585 "ast.cpp"

int StatementList::isA(int kind) const
{
	if(kind == StatementList_kind)
		return 1;
	else
		return Statement::isA(kind);
}

const char *StatementList::getKindName() const
{
	return "StatementList";
}

AssignmentStmt::AssignmentStmt(AstNode * lhs, AstNode * rhs)
	: Statement()
{
	this->kind__ = AssignmentStmt_kind;
	this->lhs = lhs;
	this->rhs = rhs;
}

AssignmentStmt::~AssignmentStmt()
{
	// not used
}

StdString AssignmentStmt::toCpp(USet & varSet)
#line 291 "ast.tc"
{
    VarExpression* varExpr = reinterpret_cast<VarExpression*>(lhs);
    std::string varName = varExpr->var;
    
    if (declaredVars.find(varName) == declaredVars.end()) {
        throw std::runtime_error("Error Semántico [Línea " + std::to_string(varExpr->line) + 
                               ", Columna " + std::to_string(varExpr->column) + 
                               "]: Variable '" + varName + "' usada sin declarar");
    }
    
    varSet.insert(varName);
    return varName + "=" + rhs->toCpp(varSet) + ";";
}
#line 628 "ast.cpp"

int AssignmentStmt::isA(int kind) const
{
	if(kind == AssignmentStmt_kind)
		return 1;
	else
		return Statement::isA(kind);
}

const char *AssignmentStmt::getKindName() const
{
	return "AssignmentStmt";
}

IfStmt::IfStmt(AstNode * condition, AstNode * thenStmt, AstNode * elseStmt)
	: Statement()
{
	this->kind__ = IfStmt_kind;
	this->condition = condition;
	this->thenStmt = thenStmt;
	this->elseStmt = elseStmt;
}

IfStmt::~IfStmt()
{
	// not used
}

StdString IfStmt::toCpp(USet & varSet)
#line 306 "ast.tc"
{
    if(elseStmt == nullptr)
        return "if (" + condition->toCpp(varSet) + ") " + thenStmt->toCpp(varSet) + " ";
    else
        return "if (" + condition->toCpp(varSet) + ") " + thenStmt->toCpp(varSet) + "else " + elseStmt->toCpp(varSet) + " ";
}
#line 665 "ast.cpp"

int IfStmt::isA(int kind) const
{
	if(kind == IfStmt_kind)
		return 1;
	else
		return Statement::isA(kind);
}

const char *IfStmt::getKindName() const
{
	return "IfStmt";
}

WhileStmt::WhileStmt(AstNode * condition, AstNode * body)
	: Statement()
{
	this->kind__ = WhileStmt_kind;
	this->condition = condition;
	this->body = body;
}

WhileStmt::~WhileStmt()
{
	// not used
}

StdString WhileStmt::toCpp(USet & varSet)
#line 314 "ast.tc"
{
    return "while (" + condition->toCpp(varSet) + ") " + body->toCpp(varSet) + " ";
}
#line 698 "ast.cpp"

int WhileStmt::isA(int kind) const
{
	if(kind == WhileStmt_kind)
		return 1;
	else
		return Statement::isA(kind);
}

const char *WhileStmt::getKindName() const
{
	return "WhileStmt";
}

PrintStmt::PrintStmt(AstNode * expr)
	: Statement()
{
	this->kind__ = PrintStmt_kind;
	this->expr = expr;
}

PrintStmt::~PrintStmt()
{
	// not used
}

StdString PrintStmt::toCpp(USet & varSet)
#line 319 "ast.tc"
{
    return "cout << " + expr->toCpp(varSet) + " << endl;";
}
#line 730 "ast.cpp"

int PrintStmt::isA(int kind) const
{
	if(kind == PrintStmt_kind)
		return 1;
	else
		return Statement::isA(kind);
}

const char *PrintStmt::getKindName() const
{
	return "PrintStmt";
}

BlockStmt::BlockStmt(AstNode * stmts)
	: Statement()
{
	this->kind__ = BlockStmt_kind;
	this->stmts = stmts;
}

BlockStmt::~BlockStmt()
{
	// not used
}

StdString BlockStmt::toCpp(USet & varSet)
#line 324 "ast.tc"
{
    return "{\n" + stmts->toCpp(varSet) + "}\n";
}
#line 762 "ast.cpp"

int BlockStmt::isA(int kind) const
{
	if(kind == BlockStmt_kind)
		return 1;
	else
		return Statement::isA(kind);
}

const char *BlockStmt::getKindName() const
{
	return "BlockStmt";
}

VarDeclStmt::VarDeclStmt(AstNode * firstIdent, AstNode * identList)
	: Statement()
{
	this->kind__ = VarDeclStmt_kind;
	this->firstIdent = firstIdent;
	this->identList = identList;
}

VarDeclStmt::~VarDeclStmt()
{
	// not used
}

StdString VarDeclStmt::toCpp(USet & varSet)
#line 329 "ast.tc"
{
    std::string result;
    result += firstIdent->toCpp(varSet);
    if(identList != nullptr) {
        result += identList->toCpp(varSet);
    }
    return result;
}
#line 800 "ast.cpp"

int VarDeclStmt::isA(int kind) const
{
	if(kind == VarDeclStmt_kind)
		return 1;
	else
		return Statement::isA(kind);
}

const char *VarDeclStmt::getKindName() const
{
	return "VarDeclStmt";
}

ArrayDeclStmt::ArrayDeclStmt(AstNode * identifier, AstNode * arrayAccess)
	: Statement()
{
	this->kind__ = ArrayDeclStmt_kind;
	this->identifier = identifier;
	this->arrayAccess = arrayAccess;
}

ArrayDeclStmt::~ArrayDeclStmt()
{
	// not used
}

StdString ArrayDeclStmt::toCpp(USet & varSet)
#line 376 "ast.tc"
{
    VarExpression* varExpr = reinterpret_cast<VarExpression*>(identifier);
    std::string varName = varExpr->var;
    std::string arrayPart = arrayAccess->toCpp(varSet);
    
    checkVarNotRedeclared(varName, varExpr->line, varExpr->column);
    
    declaredVars[varName] = true;
    varSet.insert(varName);
    
    return "int " + varName + arrayPart + ";";
}
#line 842 "ast.cpp"

int ArrayDeclStmt::isA(int kind) const
{
	if(kind == ArrayDeclStmt_kind)
		return 1;
	else
		return Statement::isA(kind);
}

const char *ArrayDeclStmt::getKindName() const
{
	return "ArrayDeclStmt";
}

VarExpression::VarExpression(StdString var, int line, int column)
	: Expression()
{
	this->kind__ = VarExpression_kind;
	this->var = var;
	this->line = line;
	this->column = column;
}

VarExpression::~VarExpression()
{
	// not used
}

StdString VarExpression::toCpp(USet & varSet)
#line 252 "ast.tc"
{
    checkVarDeclared(var, line, column);
    return var;
}
#line 877 "ast.cpp"

int VarExpression::isA(int kind) const
{
	if(kind == VarExpression_kind)
		return 1;
	else
		return Expression::isA(kind);
}

const char *VarExpression::getKindName() const
{
	return "VarExpression";
}

IntegerExpr::IntegerExpr(int value)
	: Expression()
{
	this->kind__ = IntegerExpr_kind;
	this->value = value;
}

IntegerExpr::~IntegerExpr()
{
	// not used
}

StdString IntegerExpr::toCpp(USet & varSet)
#line 258 "ast.tc"
{
    return std::to_string(value);
}
#line 909 "ast.cpp"

int IntegerExpr::isA(int kind) const
{
	if(kind == IntegerExpr_kind)
		return 1;
	else
		return Expression::isA(kind);
}

const char *IntegerExpr::getKindName() const
{
	return "IntegerExpr";
}

FloatExpr::FloatExpr(float value)
	: Expression()
{
	this->kind__ = FloatExpr_kind;
	this->value = value;
}

FloatExpr::~FloatExpr()
{
	// not used
}

StdString FloatExpr::toCpp(USet & varSet)
#line 263 "ast.tc"
{
    return std::to_string(value);
}
#line 941 "ast.cpp"

int FloatExpr::isA(int kind) const
{
	if(kind == FloatExpr_kind)
		return 1;
	else
		return Expression::isA(kind);
}

const char *FloatExpr::getKindName() const
{
	return "FloatExpr";
}

BinaryExpr::BinaryExpr(AstNode * left, BinaryOperator op, AstNode * right)
	: Expression()
{
	this->kind__ = BinaryExpr_kind;
	this->left = left;
	this->op = op;
	this->right = right;
}

BinaryExpr::~BinaryExpr()
{
	// not used
}

StdString BinaryExpr::toCpp(USet & varSet)
#line 268 "ast.tc"
{
    std::string leftCode = left->toCpp(varSet);
    std::string rightCode = right->toCpp(varSet);
    
    if (op == BinaryOperator::DIV || op == BinaryOperator::MOD) {
        return leftCode + " " + BinaryOpToString(op) + " " + rightCode;
    }
    
    return leftCode + " " + BinaryOpToString(op) + " " + rightCode;
}
#line 982 "ast.cpp"

int BinaryExpr::isA(int kind) const
{
	if(kind == BinaryExpr_kind)
		return 1;
	else
		return Expression::isA(kind);
}

const char *BinaryExpr::getKindName() const
{
	return "BinaryExpr";
}

UnaryExpr::UnaryExpr(UnaryOperator op, AstNode * operand)
	: Expression()
{
	this->kind__ = UnaryExpr_kind;
	this->op = op;
	this->operand = operand;
}

UnaryExpr::~UnaryExpr()
{
	// not used
}

StdString UnaryExpr::toCpp(USet & varSet)
#line 280 "ast.tc"
{
    return UnaryOpToString(op) + operand->toCpp(varSet);
}
#line 1015 "ast.cpp"

int UnaryExpr::isA(int kind) const
{
	if(kind == UnaryExpr_kind)
		return 1;
	else
		return Expression::isA(kind);
}

const char *UnaryExpr::getKindName() const
{
	return "UnaryExpr";
}

InputStmt::InputStmt()
	: Expression()
{
	this->kind__ = InputStmt_kind;
}

InputStmt::~InputStmt()
{
	// not used
}

StdString InputStmt::toCpp(USet & varSet)
#line 285 "ast.tc"
{
    usesInputFunction = true;
    return "input()";
}
#line 1047 "ast.cpp"

int InputStmt::isA(int kind) const
{
	if(kind == InputStmt_kind)
		return 1;
	else
		return Expression::isA(kind);
}

const char *InputStmt::getKindName() const
{
	return "InputStmt";
}

ArrayAccess::ArrayAccess(AstNode * index)
	: Expression()
{
	this->kind__ = ArrayAccess_kind;
	this->index = index;
}

ArrayAccess::~ArrayAccess()
{
	// not used
}

StdString ArrayAccess::toCpp(USet & varSet)
#line 366 "ast.tc"
{
    return "[" + index->toCpp(varSet) + "]";
}
#line 1079 "ast.cpp"

int ArrayAccess::isA(int kind) const
{
	if(kind == ArrayAccess_kind)
		return 1;
	else
		return Expression::isA(kind);
}

const char *ArrayAccess::getKindName() const
{
	return "ArrayAccess";
}

ParExpr::ParExpr(AstNode * expr)
	: Expression()
{
	this->kind__ = ParExpr_kind;
	this->expr = expr;
}

ParExpr::~ParExpr()
{
	// not used
}

StdString ParExpr::toCpp(USet & varSet)
#line 371 "ast.tc"
{
    return "(" + expr->toCpp(varSet) + ")";
}
#line 1111 "ast.cpp"

int ParExpr::isA(int kind) const
{
	if(kind == ParExpr_kind)
		return 1;
	else
		return Expression::isA(kind);
}

const char *ParExpr::getKindName() const
{
	return "ParExpr";
}

