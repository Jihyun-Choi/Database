#include <iostream>
#include <string>
#include <stack>
using namespace std;
char Pexp[30] = "";
int index = 0;

void Error() {//경고문 출력을 위한 함수
	cout << endl << "올바른 수식이 아닙니다. 다시 입력해주세요." << endl;
}

int prec(char op) {
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	case '^': return 3;
	}
	return -1;
}

void save(char value) {
	Pexp[index] = value;
	index++;
}

void Print_Infix_change_postfix(string exp) {//중위표기법을 후위표기법으로 출력하는 함수
	stack<char> op;//연산자 stack
	int size = exp.size();

	for (int i = 0; i < size; i++) {
		if ('0' <= exp[i] && exp[i] <= '9') {//한자리수의 연산만 가능한건가?
			cout << exp[i] - '0' << " "; //피연산자일 경우 출력
			save(exp[i]);
			continue;
		}

		switch (exp[i]) {
		case ' ':
			break;
		case '(':
			op.push(exp[i]);
			break;
		case ')':
			while (op.top() != '(') {//여는 괄호가 나올때까지 연산자 출력
				cout << op.top() << " ";
				save(op.top());
				op.pop();
			}
			op.pop();
			break;
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
			if (op.empty() || op.top() == '(') {//만약 op스택이 비어있거나, 마지막이 여는 괄호일 경우
				op.push(exp[i]);
				continue;
			}
			else {
				if (prec(op.top()) < prec(exp[i])) {//스택연산자 < 처리연산자: push(처리연산자) 
					op.push(exp[i]);
				}
				else {
					cout << op.top() << " ";
					save(op.top());
					op.pop();
					op.push(exp[i]);
				}
			}
		}
	}

	while (!op.empty()) {//stack에 메모리가 있는 경우
		cout << op.top() << " ";
		save(op.top());
		op.pop();
	}
}

double Calculation(char exp[]) {//후위표기법 계산 함수
	stack<double> cal;
	int size = strlen(exp);
	double op1, op2, num = 1;

	for (int i = 0; i < size; i++) {
		if ('0' <= exp[i] && exp[i] <= '9') {
			cal.push((double)exp[i] - '0');
			continue;
		}
		else {
			op2 = cal.top();
			cal.pop();
			op1 = cal.top();
			cal.pop();

			switch (exp[i]) {
			case '+':
				cal.push(op1 + op2); break;
			case '-':
				cal.push(op1 - op2); break;
			case '*':
				cal.push(op1 * op2); break;
			case '/':
				cal.push(op1 / op2); break;
			case '^':
				if (op2 == 0) {
					cal.push(num); break;
				}

				for (int i = 0; i < op2; i++) {
					num *= op1;
				}
				cal.push(num); break;
			}
		}
	}
	return cal.top();
}

int main() {
	string exp;

	for (int i = 0; i < 4; i++) {
		cout << "수식을 입력하세요." << endl << endl << "중위표기법: ";
		getline(cin, exp);

		cout << "후위표기법: ";
		Print_Infix_change_postfix(exp);

		cout << endl << "계산: ";
		cout << Calculation(Pexp);

		cout << endl << endl;

		Pexp[0] = '\0';
		index = 0;
	}

	return 0;
}