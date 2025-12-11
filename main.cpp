//字符串的反转
#include<iostream>
#include<string>
using namespace std;

void Reverse(char x[]) {
	char* ph = x, * pt;
	for (pt = ph; (*pt) != '\0'; pt++);
	for (--pt; ph < pt; ph++, pt--) {
		char temp = *ph;
		*ph = *pt;
		*pt = temp;
	}
}

int main() {
	char str[] = "hello world";
	Reverse(str);
	cout << str;
	return 0;
}


//字符串的拷贝
//用数组拷贝
#include<iostream>
using namespace std;

void fuzhi(char x[],char y[]) {
    int i = 0;
    while (x[i] != '\0') {
        y[i] = x[i];
        i++;
    }
    y[i] = '\0';
}

int main() {
    char str1[1000];
    char str2[1000];
    cin >> str1;
    fuzhi(str1, str2);
    cout << "str2是" << str2;
    return 0;
}
//用指针拷贝
#include<iostream>
using namespace std;

void fuzhi(char* t, char* s) {
    while ((*s) != '\0') {
        *t = *s;
        ++t;
        ++s;
    }
    *t = *s;
}

int main() {
    
    char str1[1000];
    char str2[1000];
    cin >> str1 ;
    fuzhi(str2, str1);
    cout << str2;
    return 0;
}

//字符串长度
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

int changdu(char x[]) {
    int i = 0;
    while (x[i] != '\0')
        i++;
    return i;
}

int main() {
    char str[] = "hello123";
    int a = changdu(str);
    cout << a;
    return 0;
}

//复制前n个元素
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
void fuzhi(char x[], char y[],int n) {
    int i = 0;
    while (x[i] != '\0' &&i<n) {
        y[i] = x[i];
        i++;
    }
    y[i] = '\0';
}
int main() {
    int n;
    cin >> n;
    char str1[1000];
    char str2[1000];
    cin >> str1;
    fuzhi(str1, str2,n);
    cout << "str2 is" << str2;
    return 0;
}

//字符串的连接
#include<iostream>
using namespace std;

void pinjie(char x[], char y[]) {
    int i = 0;
    while (x[i] != '\0') {
        i++;
    }
    int n = sizeof(y) / sizeof(y[0]);
    for (int j = 0; j < n; j++) {
        x[i + j] = y[j];
    }
    x[i + n] = '\0';
}

int main() {
    
    char str1[1000];
    char str2[1000];
    cin >> str1 >> str2;
    pinjie(str1, str2);
    cout << str1;
    return 0;
}

//头部插入
#include<iostream>
#include<string>
using namespace std;

typedef struct Node Node;
struct Node {
    int data;
    Node* next;
};
Node* InsCreate(int n){
    Node* head = NULL;
    for (int i = 1; i <= n; i++) {
        Node* p = new Node;
        p->data = i;
        p->next = head;
        head = p;
    }
    return head;
}
int main() {
    Node* p = InsCreate(5);
    cout << (p->data);
    return 0;
}