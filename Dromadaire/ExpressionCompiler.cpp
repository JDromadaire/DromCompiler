

#include "ExpressionCompiler.h"
#include <map>
#include <vector>
#include <iostream>

std::string add(std::string aVar, std::string bVar, std::string endVar) {
	std::string str = "mov eax, " + aVar;
	str += "\n";
	str += "mov ebx, " + bVar;
	str += "\n";
	str += "add eax, ebx";
	str += "\n";
	str += "mov " + endVar + ", eax\n";
	return str;
};
std::string subtract(std::string aVar, std::string bVar, std::string endVar) {
	std::string str = "mov eax, " + aVar;
	str += "\n";
	str += "mov ebx, " + bVar;
	str += "\n";
	str += "sub eax, ebx";
	str += "\n";
	str += "mov " + endVar + ", eax\n";
	return str;
};
std::string multiply(std::string aVar, std::string bVar, std::string endVar) {
	std::string str = "mov eax, " + aVar;
	str += "\n";
	str += "mov ebx, " + bVar;
	str += "\n";
	str += "mul eax, ebx";
	str += "\n";
	str += "mov " + endVar + ", eax\n";
	return str;
};
std::string divide(std::string aVar, std::string bVar, std::string endVar) {
	std::string str = "mov eax, " + aVar;
	str += "\n";
	str += "mov ebx, " + bVar;
	str += "\n";
	str += "div eax, ebx";
	str += "\n";
	str += "mov " + endVar + ", eax\n";
	return str;
};

std::string ExpressionCompiler::getValue(Node* node) {
	if (node->getClassType() == "int") {
		return std::to_string(static_cast<IntNode*>(node)->get_value());
	}
	else if (node->getClassType() == "name") {
		std::string str0 = "VAR";
		str0 += static_cast<NameNode*>(node)->get_value();
		return str0;
	}
	return std::string();
}

std::string ExpressionCompiler::compile(Node* uk_node) {
	OperatorNode* node = nullptr;
	if (uk_node->getClassType() == "operator") {
		node = static_cast<OperatorNode*>(uk_node);
	}
	else if (uk_node->getClassType() == "setvalue") {
		SetNode* st_node = static_cast<SetNode*>(uk_node);
		if (st_node->get_expr()->getClassType() == "operator") {
			node = static_cast<OperatorNode*>(st_node->get_expr());
		}
		else {
			std::string str = "mov VAR";
			str += st_node->get_name();
			str += ", ";
			str += ExpressionCompiler::getValue(st_node->get_expr());
			str += "\n";
			return str;
		}
	}
	else {
		std::string str = "mov calcVar0, ";
		str += ExpressionCompiler::getValue(uk_node);
		str += "\n";
		return str;
	}

	std::map<std::string, std::string> VariableNameByOperatorToString;
	int var_id = 0;
	std::cout << "Compiling Expression...\n";

	std::vector<OperatorNode*> traced;
	traced.push_back(node);

	for (int i = 0; i < traced.size(); i++) {
		OperatorNode* node = traced.operator[](i);

		Node* left = node->get_left();
		Node* right = node->get_right();

		if (left->getClassType() == "operator")
			traced.push_back(static_cast<OperatorNode*>(left));
		if (right->getClassType() == "operator")
			traced.push_back(static_cast<OperatorNode*>(right));

		std::string operatorToString = node->toString();

		if (VariableNameByOperatorToString.count(operatorToString) == 0) {
			std::string calcVarName = "calcVar";
			calcVarName += std::to_string(var_id);

			VariableNameByOperatorToString.insert_or_assign(operatorToString, calcVarName);

			var_id += 1;
		}
	}

	std::vector<std::string> already_done;

	std::string end_str = "";
	for (int i = traced.size() - 1; i > -1; i--) {
		OperatorNode* node = traced[i];
		if (std::find(already_done.begin(), already_done.end(), node->toString()) != already_done.end())
			continue;
		already_done.push_back(node->toString());

		Node* left = node->get_left();
		Node* right = node->get_right();

		std::string str0 = ExpressionCompiler::getValue(left);
		if (left->getClassType() == "operator") {
			str0 = VariableNameByOperatorToString.find(left->toString())->second;
		}

		std::string str1 = ExpressionCompiler::getValue(right);
		if (right->getClassType() == "operator") {
			str1 = VariableNameByOperatorToString.find(right->toString())->second;
		}

		std::string str2 = VariableNameByOperatorToString.find(node->toString())->second;


		if (node->get_op() == "PLUS") {
			end_str += add(str0, str1, str2);
		}
		if (node->get_op() == "MINUS") {
			end_str += subtract(str0, str1, str2);
		}
		if (node->get_op() == "MULTIPLY") {
			end_str += multiply(str0, str1, str2);
		}
		if (node->get_op() == "DIVIDE") {
			end_str += divide(str0, str1, str2);
		}
	}

	if (uk_node->getClassType() == "setvalue") {
		SetNode* st_node = static_cast<SetNode*>(uk_node);
		end_str += "mov VAR";
		end_str += st_node->get_name();
		end_str += ", calcVar0\n";
	}

	return end_str;
}
