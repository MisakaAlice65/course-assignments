#include <iostream>
using namespace std;
template<typename T>
class SingleLinkedList {
    struct Node{
        T data;
        Node* next;
    };
public:

    Node* head;
    Node* currentPos;
    SingleLinkedList() : head(nullptr), currentPos(nullptr) {}
    SingleLinkedList(initializer_list<T> initList) : head(NULL) {  
        for (auto &i : initList) {
            insert(i);
        }
    }  
    // 拷贝构造函数  
    SingleLinkedList(const SingleLinkedList& other) : head(nullptr), currentPos(nullptr) {  
        Node* otherNode = other.head;  
        while (otherNode != nullptr) {  
            insert(otherNode->data);  
            otherNode = otherNode->next;  
        }  
    }  
  
    // 拷贝赋值运算符  
    SingleLinkedList& operator=(const SingleLinkedList& other) {  
        if (this != &other) {  
            // 删除当前链表的所有节点  
            Node* node = head;  
            while (node != nullptr) {  
                Node* next = node->next;  
                delete node;  
                node = next;  
            }  
    
            // 深拷贝 other 链表的所有节点  
            head = nullptr;  
            currentPos = nullptr;  
            Node* otherNode = other.head;  
            while (otherNode != nullptr) {  
                insert(otherNode->data);  
                otherNode = otherNode->next;  
            }  
        }  
    
        return *this;  
    }  



//const只能调用const类函数，绝无改变链表对象的可能
    T getCurrentVal() const{
        if(currentPos==nullptr){
            throw runtime_error("Empty current position! Can't get value!");
        }
        else{
            return currentPos->data;
        }
    }

    void setCurrentVal(const T &_val){
        if(currentPos==nullptr){
            throw runtime_error("Empty current position! Can't set value!");
        }
        else{
            currentPos->data = _val;
        }
    }

    bool isEmpty() const{
        return head == nullptr;
    }

    
    void insert(T _val) {      
        Node* newNode = new Node;      
        newNode->data = _val;      
        newNode->next = nullptr;    
        
        if(head == nullptr){      
            head = newNode;      
            currentPos = head; // 更新 currentPos    
        }      
        else{      
            Node* temp = currentPos->next;      
            currentPos->next = newNode;      
            newNode->next = temp;      
            currentPos = newNode; // 更新 currentPos    
        }      
}    
  
    void remove() {  
        if (currentPos == nullptr) {  
            // 如果当前位置为空，不进行操作  
            return;  
        }  
    
        if (head == currentPos && head->next == nullptr) {  
            // 如果链表只有一个元素，删除这个元素  
            delete head;  
            head = nullptr;  
            currentPos = nullptr;  
        } else if (currentPos->next != nullptr) {  
            // 如果链表有超过一个元素且当前位置不为最后一个，删除后一个元素  
            Node* temp = currentPos->next;  
            currentPos->next = temp->next;  
            delete temp;
        }  
}  
    
    
    

    void printList(){
        Node* temp =head;
        while(temp!=nullptr){
            cout<<temp->data<<' ';
            temp=temp->next;
            }
        cout<<endl;
    }

    bool find(T _val){
        Node* temp = head;
        while(temp!=nullptr){
            if(temp->data==_val){

                return true;
            }
            temp=temp->next;
            currentPos=temp;
        }

        return false;
    }

    ~SingleLinkedList() {  
    Node* node = head;  
    while (node != nullptr) {  
        Node* next = node->next;  
        delete node;  
        node = next;  
    }  
}  
};



int main() {  
    //SingleLinkedList<int> a;
    SingleLinkedList<int> a{1,2,3,4,5};
    int a_get = a.getCurrentVal();
    std::cout << a_get << std::endl; //测试【取值】操作是否正确，包括可能的空链表测试(//部分)，每种情况9分
    //SingleLinkedList<char> b;
    SingleLinkedList<char> b{'a','c','e'};
    b.setCurrentVal('g');
    b.printList(); //测试【定义值】操作是否正确，包括可能的空链表测试(//部分)，每种情况9分
    SingleLinkedList<char> e;
    std::cout << b.isEmpty() << " "
    << e.isEmpty() << std::endl; //测试【空链表判断】操作是否正确，18分
    SingleLinkedList<double> c1;
    SingleLinkedList<double> c2{1.5,2.0,9.0,4.7};
    SingleLinkedList<double> c3;
    c3 = c2;
    c1.insert(3.0);
    c2.insert(8.8);
    bool f_c3 = c3.find(2.0);
    c3.insert(8.8);
    c1.printList();
    c2.printList();
    c3.printList(); //测试【插入】操作是否正确，每种情况6分
    e.remove();
    c1.remove();
    bool f = c2.find(9.0);
    c2.remove();
    e.printList();
    c1.printList();
    c2.printList(); //测试【删除】操作是否正确，每种情况6分
    return 0;
}  