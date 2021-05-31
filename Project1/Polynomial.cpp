#include <iostream>
using namespace std;

class node {//���׽��� ���� �����ϴ� node Ŭ����
    float coefficient;//���
    int exp;//����
    node* link = NULL;//���� ��带 ����ų ������ 
public:
    node() { coefficient = 0.0;  exp = 0; link = NULL; }//�⺻������
    node(float coe, int ex);//�����Ͱ� ���� ������
    void node_next(node* next = NULL);//���� ��带 ����ų �������ּҸ� �޴� �Լ�
    friend void node_print(node* nolink);
    friend node* poly_add(node* f, node* g);
};

class Poly {//���׽� class
    node* head;
    node* tail;
    node* newNode;
public:
    Poly() { head = NULL; tail = NULL; newNode = NULL; }//�⺻������
    void insert_node(float coe, int ex);//�� �߰� �Լ�
    node* Poly_S() { return head; }//���׽��� �����ּ� ��ȯ
    friend void node_print(node* nolink);
    friend node* poly_add(node* f, node* g);
};

void Poly::insert_node(float coe, int ex) {//���׽Ŀ��� �� �߰��ϴ� �Լ�
    node* newNode = NULL;

    newNode = new node(coe, ex);
    newNode->node_next();

    if (head == NULL) {//ù��° ����϶�
        head = newNode;
        tail = newNode;
    }
    else {//ù��° ��尡 �ƴҶ�
        tail->node_next(newNode);//���ο� ��尡 �����Ǳ� �� ������ ����� ���Ḯ��Ʈ�� ���ο� ����� �ּҷ� �Ҵ��� ��
        tail = newNode;//������ ����� �ּҸ� ���λ����� ���� �ٲ۴�. 
    }
}

node::node(float coe, int ex) {
    coefficient = coe;
    exp = ex;
}

void node::node_next(node* next) {
    link = next;
}

node* poly_add(node* f, node* g) {//�Ű�����: ���׽��� �����ּ�
    Poly R;//�ΰ��� ���׽��� ���� ���ο� ���׽� ����
    node* fs = f;
    node* gs = g;
    float sum;

    while (fs && gs) {
        if (fs->exp == gs->exp) {//f�� g�� ������ ���� ���
            sum = fs->coefficient + gs->coefficient;

            if (!sum) continue;//sum�� 0�� ��� ���(��)�� �߰����� �ʰ� �ݺ��� ����

            R.insert_node(sum, fs->exp);
            fs = fs->link;
            gs = gs->link;
        }
        else if (fs->exp > gs->exp) {
            R.insert_node(fs->coefficient, fs->exp);
            fs = fs->link;
        }
        else {
            R.insert_node(gs->coefficient, gs->exp);
            gs = gs->link;
        }
    }
    return R.Poly_S();//R�� ���׽� �ּҸ� ��ȯ
}

void node_print(node* nolink) {
    node* start = nolink;//�� �ڵ� ���� �׳� nolink�ּҷ� startó�� �ᵵ �����Ѱ�?

    while (start != NULL) {
        cout << start->coefficient << "x^" << start->exp << " ";

        if (start->link != NULL) {
            start = start->link;
            cout << "+ ";
        }
        else    break;
    }
}


int main() {
    int num, ex;
    float coe;
    Poly P;
    Poly Q;
    node* head3 = NULL;

    cout << "���׽��� �����ϴ� ���� ������ �� ���� ����� ������ ���� �������� �Է����ּ���." << endl << endl;

    cout << "ù��° ���׽�" << endl;
    cout << "���� ���� ";
    cin >> num;

    for (int i = 0; i < num; i++) {
        cout << i + 1 << "��° ����� ����";
        cin >> coe >> ex;
        P.insert_node(coe, ex);
    }
    cout << endl;

    cout << "�ι�° ���׽�" << endl;
    cout << "���� ���� ";
    cin >> num;
    for (int i = 0; i < num; i++) {
        cout << i + 1 << "��° ����� ����";
        cin >> coe >> ex;
        Q.insert_node(coe, ex);
    }
    cout << endl;

    cout << "ù��° ���׽�" << endl << "�� : ";
    node_print(P.Poly_S());
    cout << endl;

    cout << "�ι�° ���׽�" << endl << "�� : ";
    node_print(Q.Poly_S());
    cout << endl << endl;

    cout << "�� ���� ��" << endl << "�� : ";
    node_print(poly_add(P.Poly_S(), Q.Poly_S()));
}