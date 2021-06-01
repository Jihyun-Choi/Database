#include <iostream>
#include <string>
#include <stack>
using namespace std;
char Pexp[30] = "";
int index = 0;

void Error() {//��� ����� ���� �Լ�
	cout << endl << "�ùٸ� ������ �ƴմϴ�. �ٽ� �Է����ּ���." << endl;
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

void Print_Infix_change_postfix(string exp) {//����ǥ����� ����ǥ������� ����ϴ� �Լ�
	stack<char> op;//������ stack
	int size = exp.size();

	for (int i = 0; i < size; i++) {
		if ('0' <= exp[i] && exp[i] <= '9') {//���ڸ����� ���길 �����Ѱǰ�?
			cout << exp[i] - '0' << " "; //�ǿ������� ��� ���
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
			while (op.top() != '(') {//���� ��ȣ�� ���ö����� ������ ���
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
			if (op.empty() || op.top() == '(') {//���� op������ ����ְų�, �������� ���� ��ȣ�� ���
				op.push(exp[i]);
				continue;
			}
			else {
				if (prec(op.top()) < prec(exp[i])) {//���ÿ����� < ó��������: push(ó��������) 
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

	while (!op.empty()) {//stack�� �޸𸮰� �ִ� ���
		cout << op.top() << " ";
		save(op.top());
		op.pop();
	}
}

double Calculation(char exp[]) {//����ǥ��� ��� �Լ�
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
		cout << "������ �Է��ϼ���." << endl << endl << "����ǥ���: ";
		getline(cin, exp);

		cout << "����ǥ���: ";
		Print_Infix_change_postfix(exp);

		cout << endl << "���: ";
		cout << Calculation(Pexp);

		cout << endl << endl;

		Pexp[0] = '\0';
		index = 0;
	}

	return 0;
}