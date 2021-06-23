#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
struct ListElement{
    ListElement *next;
    T element;
};

template <typename T>
class List{
    ListElement<T> *front, *back;
    int counter;
public:
    List(){
        front = back = nullptr;
        counter = 0;
    }
    unsigned size(){
        return counter;
    }
    void push_front(ListElement<T> *p){
        if(counter == 0){
            front = back = p;
            counter++;
        }
        else{
            ListElement<T> *tmp = front;
            front = p;
            p->next = tmp;
            counter++;
        }
    }
    void push_back(ListElement<T> *p){
        if(counter == 0){
            front = back = p;
            counter++;
        }
        else{
            back->next = p;
            back = back->next;
            back->next = nullptr;
            counter++;
        }
    }
    void pop_front(){
        if(counter == 0){
            cout << "Brak elementow do usuwania" << endl;
        }
        else if(counter == 1){
            ListElement<T> *p;
            p = front;
            delete p;
            front = back = nullptr;
            counter--;
        }
        else{
            ListElement<T> *p;
            p = front;
            front = front->next;
            counter--;
        }
    }
    void pop_back(){
        ListElement<T> *p = front;
        if(counter == 0){
            cout << "Brak elementow do usuwania" << endl;
        }
        else if(counter == 1){
            ListElement<T> *p;
            p = front;
            delete p;
            front = back = nullptr;
            counter--;
        }
        else{
            while(p->next->next != nullptr){
                p = p->next;
            }
            ListElement<T> *tmp = p->next;
            back = p;
            back->next = nullptr;
            delete tmp;
            counter--;
        }
    }
    void show(){
        ListElement<T> *p = front;
        if(counter == 0){
            cout << "Lista pusta" << endl;
        }
        else{
            while(p != nullptr){
                cout << p->element << " ";
                p = p->next;
            }
            cout << endl;
        }
    }

    bool removeKty(int k){
        bool result = false;

        ListElement<T> *tmp = front;

        if(k > counter || k < 0){
            cout << "nie ma elementu pod takim indeksem" << endl;
        }
        else if(k == 1){
            pop_front();
        }
        else if(k == counter){
            pop_back();
        }
        else{
            for(int i = 1; i < k - 1; ++i){
                tmp = tmp->next;
            }
            ListElement<T> *p = tmp->next;
            tmp->next = tmp->next->next;
            delete p;
        }

        return result;
    }

    void DaneZPrzedzialuDoPliku(string nazwa_pliku, ListElement<T> *left, ListElement<T> *right){
        fstream plik;
        plik.open(nazwa_pliku, ios::out);

        if(plik.is_open()){
            ListElement<T> *p;
            p = front;
            while(p){
                if(p->element > left->element && p->element < right->element){
                    plik << p->element << " ";
                }
                p = p->next;
            }
        }
        else{
            cout << "Blad" << endl;
        }
    }
    int UsunZPrzedzialu(int left, int right){
        int result = 0;

        if((left > counter || left < 0) || (right < 0 || right > counter)){
            cout << "nie ma elementu pod takim indeksem" << endl;
        }
        else{
            int tmp = (right - left) + 1;
            while(tmp != 0){
                removeKty(left);
                tmp -= 1;
            }
        }

        return result;
    }

    int UsunDuplikaty(){
        int result = 0;

        ListElement<T> *p, *pc;
        pc = front;
        while(pc){
            p = pc;
            while(p->next){
                if(p->next->element == pc->element){
                    p->next = p->next->next;
                    result++;
                }
                else{
                    p = p->next;
                }
            }
            pc = pc->next;
        }

        return result > 0 ? result : -1;
    }

    bool Zawiera(List<T> *list){
        bool result = true;
        bool arr[list->counter];
        int tmp = 0;
        for(int i = 0; i < list->counter; ++i){
            arr[i] = false;
        }
        ListElement<T> *el_2 = list->front;

        while(el_2->next != nullptr){
            ListElement<T> *el_1 = front;
            for(int i = 0; i < counter; ++i){
                if(el_2->element == el_1->element){
                    arr[tmp] = true;
                    tmp++;
                }
            }
            el_2 = el_2->next;
        }
        for(int i = 0; i < list->counter; ++i){
            if(arr[i] == false){
                result = false;
            }
        }
        return result;
    }
    void Polacz(List<T> *list){
        back->next = list->front;
        back = list->back;
    }
};

int main()
{

    List<int> *list = new List<int>;
    for(int i = 0; i < 10; ++i){
        ListElement<int> *p = new ListElement<int>;
        p->element = i+1;
        list->push_back(p);
    }

// Zawiera-------------------------------------------------------------------------------
//    List<int> *list_small = new List<int>;
//    for(int i = 0; i < 5; ++i){
//        ListElement<int> *p = new ListElement<int>;
//        p->element = i;
//        list_small->push_back(p);
//    }
//    cout << list->Zawiera(list_small) << endl;
//---------------------------------------------------------------------------------------

// Polacz--------------------------------------------------------------------------------
//    List<int> *list_small = new List<int>;
//    for(int i = 0; i < 5; ++i){
//        ListElement<int> *p = new ListElement<int>;
//        p->element = i;
//        list_small->push_back(p);
//    }
//    list->Polacz(list_small);
//---------------------------------------------------------------------------------------

// Usun duplikaty: ----------------------------------------------------------------------
//    for(int i = 0; i < 10; ++i){
//        ListElement<int> *p = new ListElement<int>;
//        p->element = 3;
//        list->push_back(p);
//    }
//    for(int i = 0; i < 10; ++i){
//        ListElement<int> *p = new ListElement<int>;
//        p->element = 5;
//        list->push_back(p);
//    }
//    for(int i = 0; i < 10; ++i){
//        ListElement<int> *p = new ListElement<int>;
//        p->element = 7;
//        list->push_back(p);
//    }
//    cout << "Liczba usunietych elementow: " << list->UsunDuplikaty() << endl;
//---------------------------------------------------------------------------------------

// Usun k-ty-----------------------------------------------------------------------------
//    list->removeKty(7);
//---------------------------------------------------------------------------------------

// Usun z przedzialu---------------------------------------------------------------------
//    list->UsunZPrzedzialu(3,7);
//---------------------------------------------------------------------------------------

// Dane z przedzialu do pliku------------------------------------------------------------
//    ListElement<int> *left = new ListElement<int>;
//    ListElement<int> *right = new ListElement<int>;

//    left->element = 1;
//    right->element = 7;

//    list->DaneZPrzedzialuDoPliku("test.txt", left, right);
//---------------------------------------------------------------------------------------

    list->show();

    return 0;
}
