

#include "Node.h"
#include <iostream>

/**
 * Integer
 */

const char * IntNode::getClassType()
{
	return "int";
}

int IntNode::get_value()
{
	return this->value;
}

Node * IntNode::get_field(const char * chr)
{
	return nullptr;
}

Node* IntNode::add(Node* other) {
	if (other->getClassType() == "int") {
		IntNode* node = static_cast<IntNode*>(other);
		int a = node->get_value() + this->get_value();
		return new IntNode(a);
	}
	return nullptr;
}
Node* IntNode::subtract(Node* other) {
	if (other->getClassType() == "int") {
		IntNode* node = static_cast<IntNode*>(other);
		int a = this->get_value() - node->get_value();
		return new IntNode(a);
	}
	return nullptr;
}
Node* IntNode::multiply(Node* other) {
	if (other->getClassType() == "int") {
		IntNode* node = static_cast<IntNode*>(other);
		int a = node->get_value() * this->get_value();
		return new IntNode(a);
	}
	return nullptr;
}
Node* IntNode::divide(Node* other) {
	if (other->getClassType() == "int") {
		IntNode* node = static_cast<IntNode*>(other);
		int a = this->get_value() / node->get_value();
		return new IntNode(a);
	}
	return nullptr;
}
int myPow(int x, int p) {
	if (p == 0) return 1;
	if (p == 1) return x;
	return x * myPow(x, p - 1);
}
Node* IntNode::power(Node* other) {
	if (other->getClassType() == "int") {
		IntNode* node = static_cast<IntNode*>(other);
		int a = myPow(this->get_value(), node->get_value());
		return new IntNode(a);
	}
	return nullptr;
}

Node * IntNode::negate()
{
	return new IntNode(-this->get_value());
}

Node * IntNode::get(Node * object)
{
	return nullptr;
}

IntNode::IntNode(int value)
{
	this->value = value;
}

std::string IntNode::toString()
{
	return std::to_string(this->value);
}

/**
 * Operator Node (a+b | a-b | a*b | a/b | a^b...)
 */

OperatorNode::OperatorNode(Node* left, Node* right, std::string op_string)
{
	this->left = left;
	this->right = right;
	this->op_string = op_string;
}

std::string OperatorNode::toString()
{
	std::string str = "[";
	str += this->left->toString();
	str += " ";
	str += this->op_string;
	str += " ";
	str += this->right->toString();
	str += "]";
	return str;
}

const char * Node::getClassType()
{
	return nullptr;
}

Node * Node::get_field(const char * chr)
{
	return nullptr;
}

Node * Node::add(Node * other)
{
	return nullptr;
}

Node * Node::subtract(Node * other)
{
	return nullptr;
}

Node * Node::multiply(Node * other)
{
	return nullptr;
}

Node * Node::divide(Node * other)
{
	return nullptr;
}

Node * Node::power(Node * other)
{
	return nullptr;
}

Node * Node::negate()
{
	return nullptr;
}

Node * Node::get(Node * object)
{
	return nullptr;
}

Node * Node::evaluate(std::map<std::string, Node*>* ctx)
{
	return this;
}

std::string Node::toString()
{
	return std::string();
}

const char * OperatorNode::getClassType()
{
	return "operator";
}

int OperatorNode::get_value()
{
	return 0;
}

Node * OperatorNode::get_field(const char * chr)
{
	return nullptr;
}

Node * OperatorNode::add(Node * other)
{
	return nullptr;
}

Node * OperatorNode::subtract(Node * other)
{
	return nullptr;
}

Node * OperatorNode::multiply(Node * other)
{
	return nullptr;
}

Node * OperatorNode::divide(Node * other)
{
	return nullptr;
}

Node * OperatorNode::power(Node * other)
{
	return nullptr;
}

Node * OperatorNode::negate()
{
	return nullptr;
}

Node * OperatorNode::get(Node * object)
{
	return nullptr;
}

Node * OperatorNode::evaluate(std::map<std::string, Node*>* ctx)
{
	Node* leval = this->left->evaluate(ctx);
	Node* reval = this->right->evaluate(ctx);
	if (leval == nullptr) {
		if (this->left->getClassType() != "operator") {
			std::cout << "The object ";
			std::cout << this->left->toString();
			std::cout << " could not be evaluated\n";
		}
		return nullptr;
	}
	if (reval == nullptr) {
		if (this->right->getClassType() != "operator") {
			std::cout << "The object ";
			std::cout << this->right->toString();
			std::cout << " could not be evaluated\n";
		}
		return nullptr;
	}

	if (this->op_string == "PLUS")
		return leval->add(reval);
	if (this->op_string == "MINUS")
		return leval->subtract(reval);
	if (this->op_string == "MULTIPLY")
		return leval->multiply(reval);
	if (this->op_string == "DIVIDE")
		return leval->divide(reval);
	if (this->op_string == "POWER")
		return leval->power(reval);

	return nullptr;
}

Node * OperatorNode::get_left()
{
	return this->left;
}

Node * OperatorNode::get_right()
{
	return this->right;
}

std::string OperatorNode::get_op()
{
	return this->op_string;
}



/**
 * NameNode
 */

const char* NameNode::getClassType() {
	return "name";
}


NameNode::NameNode(std::string value) {
	this->value = value;
}

std::string NameNode::toString() {
	std::string str = "VAR_NAME:";
	str += this->value;
	return str;
}

std::string NameNode::get_value() {
	return this->value;
}

Node* NameNode::get_field(const char* chr) {
	return nullptr;
}

Node* NameNode::add(Node* other) { return nullptr; }
Node* NameNode::subtract(Node* other) { return nullptr; }
Node* NameNode::multiply(Node* other) { return nullptr; }
Node* NameNode::divide(Node* other) { return nullptr; }
Node* NameNode::power(Node* other) { return nullptr; }
Node* NameNode::negate() { return nullptr; }
Node* NameNode::get(Node* node) { return nullptr; }

Node* NameNode::evaluate(std::map<std::string, Node*>* ctx) {
	if (ctx->find(this->value) == ctx->end())
		return nullptr;
	return ctx->find(this->value)->second;
}



/**
 * Set Node
 */

SetNode::SetNode(std::string name, Node * expr)
{
	this->name = name;
	this->expr = expr;
}

std::string SetNode::toString()
{
	std::string str = "SET ";
	str += this->name;
	str += " = ";
	str += this->expr->toString();
	return str;
}

const char * SetNode::getClassType()
{
	return "setvalue";
}

std::string SetNode::get_name()
{
	return this->name;
}

Node * SetNode::get_field(const char * chr)
{
	return nullptr;
}

Node* SetNode::add(Node* other) { return nullptr; }
Node* SetNode::subtract(Node* other) { return nullptr; }
Node* SetNode::multiply(Node* other) { return nullptr; }
Node* SetNode::divide(Node* other) { return nullptr; }
Node* SetNode::power(Node* other) { return nullptr; }
Node* SetNode::negate() { return nullptr; }
Node* SetNode::get(Node* node) { return nullptr; }

Node * SetNode::evaluate(std::map<std::string, Node*>* ctx)
{
	Node* val = this->expr->evaluate(ctx);

	ctx->insert_or_assign(this->name, val);
	
	return nullptr;
}

Node * SetNode::get_expr()
{
	return expr;
}
