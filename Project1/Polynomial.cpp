#include <iostream>
using namespace std;

class node {//다항식의 항을 구성하는 node 클래스
    float coefficient;//계수
    int exp;//지수
    node* link = NULL;//다음 노드를 가리킬 포인터 
public:
    node() { coefficient = 0.0;  exp = 0; link = NULL; }//기본생성자
    node(float coe, int ex);//데이터가 들어가는 생성자
    void node_next(node* next = NULL);//다음 노드를 가리킬 포인터주소를 받는 함수
    friend void node_print(node* nolink);
    friend node* poly_add(node* f, node* g);
};

class Poly {//다항식 class
    node* head;
    node* tail;
    node* newNode;
public:
    Poly() { head = NULL; tail = NULL; newNode = NULL; }//기본생성자
    void insert_node(float coe, int ex);//항 추가 함수
    node* Poly_S() { return head; }//다항식의 시작주소 반환
    friend void node_print(node* nolink);
    friend node* poly_add(node* f, node* g);
};

void Poly::insert_node(float coe, int ex) {//다항식에서 항 추가하는 함수
    node* newNode = NULL;

    newNode = new node(coe, ex);
    newNode->node_next();

    if (head == NULL) {//첫번째 노드일때
        head = newNode;
        tail = newNode;
    }
    else {//첫번째 노드가 아닐때
        tail->node_next(newNode);//새로운 노드가 생성되기 전 마지막 노드의 연결리스트를 새로운 노드의 주소로 할당한 후
        tail = newNode;//마지막 노드의 주소를 새로생성한 노드로 바꾼다. 
    }
}

node::node(float coe, int ex) {
    coefficient = coe;
    exp = ex;
}

void node::node_next(node* next) {
    link = next;
}

node* poly_add(node* f, node* g) {//매개변수: 다항식의 시작주소
    Poly R;//두개의 다항식을 더할 새로운 다항식 선언
    node* fs = f;
    node* gs = g;
    float sum;

    while (fs && gs) {
        if (fs->exp == gs->exp) {//f와 g의 지수가 같을 경우
            sum = fs->coefficient + gs->coefficient;

            if (!sum) continue;//sum이 0인 경우 노드(항)을 추가하지 않고 반복문 진행

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
    return R.Poly_S();//R의 다항식 주소를 반환
}

void node_print(node* nolink) {
    node* start = nolink;//이 코드 없이 그냥 nolink주소로 start처럼 써도 무방한가?

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

    cout << "다항식을 구성하는 항의 개수와 각 항의 계수와 차수를 높은 차수부터 입력해주세요." << endl << endl;

    cout << "첫번째 다항식" << endl;
    cout << "항의 개수 ";
    cin >> num;

    for (int i = 0; i < num; i++) {
        cout << i + 1 << "번째 계수와 차수";
        cin >> coe >> ex;
        P.insert_node(coe, ex);
    }
    cout << endl;

    cout << "두번째 다항식" << endl;
    cout << "항의 개수 ";
    cin >> num;
    for (int i = 0; i < num; i++) {
        cout << i + 1 << "번째 계수와 차수";
        cin >> coe >> ex;
        Q.insert_node(coe, ex);
    }
    cout << endl;

    cout << "첫번째 다항식" << endl << "식 : ";
    node_print(P.Poly_S());
    cout << endl;

    cout << "두번째 다항식" << endl << "식 : ";
    node_print(Q.Poly_S());
    cout << endl << endl;

    cout << "두 식의 합" << endl << "식 : ";
    node_print(poly_add(P.Poly_S(), Q.Poly_S()));
}