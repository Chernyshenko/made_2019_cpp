#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <stdexcept>
#include <string.h>

class Expression {
public:
    Expression(const std::string& element) : element(element) {}
	Expression(const std::string& element, const Expression& e) : element(element)
	{
		expr.push_back(e);
	}
	Expression(const std::string& element, const Expression& left, const Expression& right) : element(element)
	{
		expr.push_back(left);
		expr.push_back(right);
	}

	std::string element;
	std::vector<Expression> expr;
};

class CalcParser {
public:
	CalcParser(const char* cur_) {
		size_t n = strlen(cur_); 
		copy_full = new char[n];
		strcpy(copy_full, cur_);
		cur = copy_full;
	}
	~CalcParser(){
		if (copy_full) delete[] copy_full;
		cur = nullptr;
		copy_full = nullptr;
	}
	Expression Parse(int pr);
private:
	char* copy_full;
	const char* cur;

	std::string ParseElement();
	Expression ParseExpression();
	int Priority(const std::string& operation);
	bool IsNum(char c);
	int IntFromChar(const char c){ return c - '0';}
};

class Calculator{
public:
	Calculator(const char* arg): p(arg) {}
	int Calc(const Expression& e, int& err);
	int Calc(int& err);
private:
	CalcParser p;
};

bool CalcParser::IsNum(char c){
    int n = IntFromChar(c);
    if (n >= 0 && n <= 9) return true;
    return false;
}
std::string CalcParser::ParseElement() {
	const char space = ' ';
	while ( *cur == space) cur++;

	int j = 0;
	std::ostringstream snum;
    while(IsNum(*(cur))) {
    	snum << *(cur);
    	cur++;
    }
    if (!snum.str().empty()){
    	return snum.str();
    }

	std::array<char, 4> operations = {'+', '-', '*', '/'};
	for (auto& op : operations) {
		if ( (*cur) == op) {
			cur++;
			return std::string(1,op);
		}
	}
	return "";
}

Expression CalcParser::ParseExpression() {
	std::string element = ParseElement();
	if (element.empty()) throw std::runtime_error("Error in input");

	if (IsNum(element[0])) return Expression(element);

	return Expression(element, ParseExpression());
}

int CalcParser::Priority(const std::string& operation) {
	if (operation == "+" || operation == "-") return 1;
	if (operation == "*" || operation == "/") return 2;
	return 0;
}

Expression CalcParser::Parse(int pr = 0) {
	auto left_expr = ParseExpression();

	while(true){
		auto operation = ParseElement();
		int priority = Priority(operation);
		if (priority <= pr) {
			cur--;
			return left_expr;
		}

		auto right_expr = Parse(priority);
		left_expr = Expression(operation, left_expr, right_expr);
	}
}
int Calculator::Calc(const Expression& e, int& err) {
	switch (e.expr.size()) {
		case 0:
			return std::stoi(e.element);
		case 1:
		{ 
			int a = Calc(e.expr[0], err);
			if (e.element == "+") return  a;
			if (e.element == "-") return -a;
		}
		case 2: 
		{
			int left = Calc(e.expr[0], err);
			int right = Calc(e.expr[1], err);
			if (e.element == "+") return left + right;
			if (e.element == "-") return left - right;
			if (e.element == "*") return left * right;
			if (e.element == "/") return left / right;
		}
	}
	throw std::runtime_error("Error in input");
}
int Calculator::Calc(int& err){
	int res = 0;
	try{
		res = Calc(p.Parse(), err);
	}
	catch (std::exception& e)
  	{
    	std::cout << e.what() << '\n';
    	err = -1;
  	}

	return res;
}