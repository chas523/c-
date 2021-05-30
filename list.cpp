#include<iostream>

using namespace std;

template<typename T>
class List {
protected:
    struct Node {
        Node *pNext;
        T data;
        explicit Node(T data = T(), Node *pNext= nullptr):data(data),pNext(pNext){}
    };
    int size;
    Node* head;
public:
    List();
    ~List();
    void push_back(T data); // добавить элемент в конец списка
    int getSize(); // получить размер списка
    void print(); //  отоброзить список
    void pop_front(); //удаляет первый элемент списка
    void clear(); // удаляет список
    void push_front(T data); // добовляет элемент в начало списка
    void insert(T value, int index); // добовляет элемент в список по индексу
    void removeAt(int index); // удаляет элемент по индексу
    T maxValue(); // вернет максимальный элемент
    T& operator[](int index);
    void replaceFirstOnLast(); //ставит первый элемент в конец а последний вперед
};

template<typename T>
List<T>::List() {
    size=0;
    head= nullptr;
}

template<typename T>
List<T>::~List(){
    clear();
}

template<typename T>
void List<T>::push_back(T data) {
    if(head == nullptr) {
         size++;
         head = new Node(data);
    }else{
        Node *current = head;
        while(current->pNext != nullptr) {
            current = current->pNext;
        }
        current->pNext = new Node(data);
        size++;
    }
}
template<typename T>
int List<T>::getSize() {
    return size;
}

template<typename T>
void List<T>::print() {
    Node *current = head;
    for (int i = 0; i < size; i ++) {
        cout<< current->data << " ";
        current = current->pNext;
    }
    cout << endl;
}

template<typename T>
void List<T>::pop_front() {
    size--;
    Node *temp = head;
    head = head->pNext;
    delete (temp);
}

template<typename T>
void List<T>::clear() {
    while(size) {
        pop_front();
    }
}

template<typename T>
T &List<T>::operator[](const int index) {
    Node* current  = head;
    int tmp =0;
    while(current!= nullptr) {
        if(index == tmp) {
            return  current->data;
        }
        current = current->pNext;
        tmp++;
    }

}

template<typename T>
T List<T>::maxValue() {
    T result = head->data;
    Node *current = head;
    for (int i =0 ;i < size; i++) {
        if(current->data > result) {
            result = current->data;
        }
        current = current->pNext;
    }
    return result;
}

template<typename T>
void List<T>::push_front(T data) {
    head  = new Node(data,head);
    size++;
}

template<typename T>
void List<T>::insert(T value, int index) {
    if (index == 0) {
        push_front(value);
    } else {
        if (index <= size)
        {
        Node  *previous = this->head;
        for (int i=0; i < index - 1; i++) {
            previous = previous->pNext;
        }
        Node *newNode = new Node(value, previous->pNext);
        previous->pNext = newNode;
        size++;
        }
        else {
            cout <<"some wrong !"<<endl;
        }
    }
}

template<typename T>
void List<T>::removeAt(int index) {
    if(index==0) {
        pop_front();
    }else {
        Node  *previous = this->head;
        for (int i = 0; i < index - 1; i++) {
            previous = previous->pNext;
        }
        Node *toDelete = previous->pNext;
        previous->pNext = toDelete->pNext;
        delete toDelete;
        size--;
    }
}

template<typename T>
void List<T>::replaceFirstOnLast() {
    T first  = head->data;
    T last = head->data;
    Node *current = head;
    while(current->pNext != nullptr) {
        current = current->pNext;
    }
    last = current->data;
    head->data = last;
    current->data = first;
}


int main() {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.print();
    l.replaceFirstOnLast();
    l.print();



    return 0;
}
