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


//关于字符串，数组名与指针的辨析

//输入多个名字
//1.用二维数组
#include<iostream>
#include<string>
using namespace std;

int main() {
    char name[5][10];  //可以定义一个二维数组，存储输入的多个字符串
    for (int i = 0; i < 5; i++) {
        cin >> name[i];  //name[i]是这个字符串的名字（类似于指针）
    }
    for (int i = 0; i < 5; i++) {
        cout << name[i];
    }
    return 0;
}
//2.用cpp里面的string 
#include<iostream>
#include<string>
using namespace std;

int main() {
    string names[5];
    for (int i = 0; i < 5; i++) {
        cin >> names[i];
    }    
    for (int i = 0; i < 5; i++) {
        cout << names[i] << " ";
    }
    return 0;
}
//3.用指针数组（麻烦）
#include<iostream>
#include<string>
using namespace std;
int main() {
    char* name[5]；    
    for (int i = 0; i < 5; i++) {
        char* a = new char[10];//每次得新开辟一块空间，否则都指向一个字符数组char temp[10];
        cin >> a;
        name[i] = a;
    }    
    for (int i = 0; i < 5; i++) {
        cout << name[i] << " ";
        delete[] name[i];  // 记得释放内存
    }
    return 0;
}

//一维数组的数组名和指针的辨析
#include <stdio.h>
int main() {
    char name[10] = "Hello";
    
    printf("name     = %p\n", (void*)name);      // 指向第一个字符的指针
    printf("&name[0] = %p\n", (void*)&name[0]);  // 指向第一个字符的指针 类型是char*

    printf("&name    = %p\n", (void*)&name);     // 指向整个数组的指针 类型是char(*)[10]  (二维数组数组名)

    return 0;
}
//二维数组的数组名和指针的辨析
char arr[3][4]={......};
printf("arr         = %p\n", (void*)arr);          // 指向第一行（第一个一维数组）的指针
printf("&arr[0]     = %p\n", (void*)&arr[0]);      // 同上(类型是char(*)[4])

printf("arr[0]      = %p\n", (void*)arr[0]);       // 指向第一个元素的指针（相当于一维数组数组名）
printf("&arr[0][0]  = %p\n", (void*)&arr[0][0]);   // 同上(类型是char*)

printf("&arr        = %p\n", (void*)&arr);         // 指向整个二维数组的指针(类型是char(*)[3][4])



//形参写法汇总

// 1.
char arr[3][4];
func1(arr);
// 形参写法1：指针数组
void func1(char (*p)[4])  //char(*p)[4]是指向数组的指针，   char *p[4]是指针数组
    
// 形参写法2：数组形式
void func1(char p[][4]) 



// 2.
char arr[3][4];
func3(arr[0]);      // 传递第一行
func3(arr[1]);      // 传递第二行
func3(&arr[2][0]);  // 传递第三行，等价写法
// 形参写法1：指针
void func3(char *p)
// 形参写法2：一维数组
void func3(char p[]) 


//3.
char arr[3][4];
func5(&arr);  // 传递整个数组的地址
// 形参写法：指向整个二维数组的指针
void func5(char (*p)[3][4]) 

//4.
char* arr[5];
func1(arr, 5);
void func1(char** p, int size) //指向指针的指针，所以是二级指针

void func1(char* p[], int size)

void func2(char* p[5]) //知道有几个单词

func3(&arr)
void func3(char* (*p)[5])


//头部插入（倒序输入）
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
        if (p) p->data = i;
        if (p) p->next = head;//避免p是空指针
        head = p;
    }
    return head;
}
int main() {
    Node* p = InsCreate(5);
    cout << (p->next->data);//输出4，实际上链表是5->4->3->2->1
    return 0;
}

//尾部追加（正序输入）
#include<iostream>
#include<string>
using namespace std;

typedef struct Node Node;
struct Node {
    int data;
    Node* next;
};
Node* AppendCreate(int n){
    Node* head = NULL,*tail=NULL;
    for (int i = 1; i <= n; i++) {
        Node* p = new Node;
        p->data = i;
        p->next = NULL;//假设新加的这个就是最后一个节点
        if (head == NULL) {
            head = p;
        }
        else {
            tail->next = p;
        }
        tail = p;
    }
    return head;
}
int main() {
    Node* p = AppendCreate(5);
    cout << (p->data);//输出1，实际上链表是1->2->3->4->5
    return 0;
}

//输出链表
#include<iostream>
#include<string>
using namespace std;

typedef struct Node Node;
struct Node {
    int data;
    Node* next;
};
Node* AppendCreate(int n){
    Node* head = NULL,*tail=NULL;
    for (int i = 1; i <= n; i++) {
        Node* p = new Node;
        p->data = i;
        p->next = NULL;
        if (head == NULL) {
            head = p;
        }
        else {
            tail->next = p;
        }
        tail = p;
    }
    return head;
}
void PrintLink(Node* p) {
    while (p != NULL) {
        cout << (p->data) << "->";
        p = p->next;
    }
    cout << "NULL";
}
int main() {
    Node* p = AppendCreate(5);
    PrintLink(p);
    return 0;
}

//插入节点
void InsertNode(Node* head,int i){
    Node*current=head;
    int j=1;
    while(j<i && head && current->next!=NULL){//担心head为空
        j++;
        current=curtent->next;
    }//结束之后current指向第i个或者最后一个节点
    if(j==i){
        Node*p=new Node;
        int temp;
        cin>>temp;
        p->num=temp;
        p->next=current->next;
        current->next=p;
    }
    else{
        cout<<"没有第"<<i<<"个节点";
    }
}

//删除节点
Node* DeleteNode(Node*head,int i){
    if(i==1){
        Node*current=head;
        head=head->next;
        delete current;
    }
    else{
        Node*previous=head;
        int j=1;
        while(j<i-1 && previous->next!=NULL){
            j++;
            previous=previous->next;
        }//previous指向第i-1个节点
        if(previous->next!=NULL){
            Node*current=previous->next;//current指向第i个节点
            previous->next=current->next;
            delete current;
        }
        else{
            cout<<"没有第"<<i<<"个节点"；
        }
    }
    return head;
}

//整个链表的删除
void DeleteLink(Node*head){
    while(head){
        Node*current=head;
        head=head->next;
        delete current;
    }
}


//链表输入的排序，交并差集的运算。
#include <iostream>
#include <string> 
using namespace std;

typedef struct Node {
    int num;
    Node* next;
} Node;

Node* Create() {
    Node* head = NULL;
    int temp;
    cin >> temp;
    while (temp != -1) {
        Node* prev = NULL;
        Node* curr = head;
        while (curr && curr->num < temp) {
            prev = curr;
            curr = curr->next;
        }
        if (curr && curr->num == temp) {
            cin >> temp;
            continue;
        }
        Node* p = new Node;
        p->num = temp;
        p->next = curr;
        if (prev == NULL) {
            head = p;
        }
        else {
            prev->next = p;
        }
        cin >> temp;
    }
    return head;
}

Node* append(Node* head, int num) {
    Node* temp = head;
    Node* p = new Node;
    p->num = num;
    p->next = NULL;
    if (temp == NULL) {
        return p;
    }
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = p;
    return head;
}

Node* bingji(Node* x, Node* y) {
    Node* head = NULL;

    while (x != NULL && y != NULL) {
        if (x->num < y->num) {
            head = append(head, x->num);
            x = x->next;
        }
        else if (x->num > y->num) {
            head = append(head, y->num);
            y = y->next;
        }
        else { // 相等
            head = append(head, x->num);
            x = x->next;
            y = y->next;
        }
    }
    if (x == NULL) {
        while (y) {
            head = append(head, y->num);
            y = y->next;
        }
    }
    if (y == NULL) {
        while (x) {
            head = append(head, x->num);
            x = x->next;
        }
    }
    return head;
}

Node* jiaoji(Node* x, Node* y) {
    Node* head = NULL;
    while (x != NULL && y != NULL) {
        if (x->num < y->num) {
            x =x->next;
        }
        else if (x->num > y->num) {
            y = y->next;
        }
        else { // 相等
            head = append(head, x->num);
            x = x->next;
            y = y->next;
        }
    }
    return head;
}

Node* chaji(Node* x, Node* y) {
    Node* head = NULL;
    while (x != NULL && y != NULL) {
        if (x->num < y->num) {
            head = append(head, x->num);
            x = x->next;
        }
        else if (x->num > y->num) {
            y = y->next;
        }
        else { // 相等，都不加入结果
            x = x->next;
            y = y->next;
        }
    }
    if (x != NULL) {
        while (x) {
            head = append(head, x->num);
            x = x->next;
        }
    }
    return head;
}

void Print(Node* head) {
    if (head == NULL) {
        return;
    }
    while (head) {
        cout << head->num << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    Node* firstlink = Create();
    Node* secondlink = Create();

    // 创建并集、交集、差集
    Node* jiao = jiaoji(firstlink, secondlink);
    Node* bing = bingji(firstlink, secondlink);
    Node* cha = chaji(firstlink, secondlink);

    Print(jiao);
    Print(bing);   
    Print(cha);

    return 0;
}

//对一个链表排序
Node* Create() {
    Node* head = NULL,*tail=NULL;
    int temp;
    cin >> temp;
    while (temp != -1) {
        Node* p = new Node;
        p->num = temp;
        p->next = NULL;
        if (head == NULL) {
            head = p;
        }
        else {
            tail->next = p;
        }
        tail = p;
        cin >> temp;
    }
    return head;
}
Node* addnode(Node* head, Node* prev) {
    if (prev->num < head->num) {
        prev->next = head;
        return prev;
    }
    Node* p = NULL, * q = head;
    while (q) {
        if (prev->num < q->num)//q是已经排好队的
            break;
        p = q;
        q = q->next;
    }
    prev->next = q;
    p->next = prev;
    return head;

}
Node* sortlist(Node* head) {
    Node* curr = head->next;
    head->next = NULL;
    while (curr) {
        Node* prev = curr;
        curr = curr->next;
        head = addnode(head, prev);
    }
    return head;
}







