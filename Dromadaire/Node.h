#pragma once



#include <string>
#include <map>

class Node {
public:
	virtual const char* getClassType();
	virtual Node* get_field(const char* chr);
	virtual Node* add(Node* other);
	virtual Node* subtract(Node* other);
	virtual Node* multiply(Node* other);
	virtual Node* divide(Node* other);
	virtual Node* power(Node* other);
	virtual Node* negate();
	virtual Node* get(Node* object);
	virtual Node* evaluate(std::map<std::string, Node*>* ctx);
	virtual std::string toString();
};

class IntNode : public Node {
private:
	int value;
public:
	const char* getClassType();
	int get_value();
	Node* get_field(const char* chr);
	Node* add(Node* other);
	Node* subtract(Node* other);
	Node* multiply(Node* other);
	Node* divide(Node* other);
	Node* power(Node* other);
	Node* negate();
	Node* get(Node* object);
	IntNode(int value);
	std::string toString();
};

class NameNode : public Node {
private:
	std::string value;
public:
	const char* getClassType();
	std::string get_value();
	Node* get_field(const char* chr);
	Node* add(Node* other);
	Node* subtract(Node* other);
	Node* multiply(Node* other);
	Node* divide(Node* other);
	Node* power(Node* other);
	Node* negate();
	Node* get(Node* object);
	Node* evaluate(std::map<std::string, Node*>* ctx);
	NameNode(std::string value);
	std::string toString();
};

class OperatorNode : public Node {
private:
	Node* left;
	Node* right;
	std::string op_string;
public:
	const char* getClassType();
	int get_value();
	Node* get_field(const char* chr);
	Node* add(Node* other);
	Node* subtract(Node* other);
	Node* multiply(Node* other);
	Node* divide(Node* other);
	Node* power(Node* other);
	Node* negate();
	Node* get(Node* object);
	Node* evaluate(std::map<std::string, Node*>* ctx);
	Node* get_left();
	Node* get_right();
	std::string get_op();
	OperatorNode(Node* left, Node* right, std::string op_string); 
	std::string toString();
};

class SetNode : public Node {
private:
	std::string name;
	Node* expr;
public:
	const char* getClassType();
	std::string get_name();
	Node* get_field(const char* chr);
	Node* add(Node* other);
	Node* subtract(Node* other);
	Node* multiply(Node* other);
	Node* divide(Node* other);
	Node* power(Node* other);
	Node* negate();
	Node* get(Node* object);
	Node* evaluate(std::map<std::string, Node*>* ctx);
	Node* get_expr();
	SetNode(std::string name, Node* expr);
	std::string toString();
};

