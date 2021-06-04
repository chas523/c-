#include <iostream>
#include <time.h>
#include <vector>
using namespace  std;

//zadanie 1
// a)[100,44, 88, 33, 43, 72, 66, 22, 32, 38, 5, 19, 70, 60, 1] ; nie jest kopcem typu max
// b)[100,44, 88, 33, 43, 72, 66, 22, 32, 19, 5, 38, 70, 60, 1] ; nie jest kopcem typu max
// c)[100,43, 88, 33, 44, 72, 66, 22, 32, 38, 5, 19, 70, 60, 1] ; jest kopcem typu max


class Lot{
public:
    string iL;
    int iP;
    int pL;
};

//zadanie 4
class Wieza
{
    // Очередь
    Lot * Wait;
    // Приоритет
    int * Pri;
    // Максимальный размер очереди
    int MaxQueueLength;
    // Текущий размер очереди
    int QueueLength;

public:
    // Конструктор
    Wieza(int m);

    //Деструктор
    ~Wieza();

    // Добавление элемента
    void Add(Lot c,int p);

    // Извлечение элемента
    Lot Extract();

    // Очистка очереди
    void Clear();

    // Проверка существования элементов в очереди
    bool IsEmpty();

    // Проверка на переполнение очереди
    bool IsFull();

    // Количество элементов в очереди
    int GetCount();

    //демонстрация очереди
    void Show();
};

void Wieza::Show(){
    cout<<"\n-------------------------------------\n";
    //демонстрация очереди
    for(int i=0;i<QueueLength;i++){
//        cout<<Wait[i]<<" - "<<Pri[i]<<"\n\n";
          cout<<Wait[i].iL <<"| ilosc pasazerow: "<<Wait[i].iP <<" | priorytet:  " << Pri[i]<<"\n\n";
    }
    cout<<"\n-------------------------------------\n";
}

Wieza::~Wieza()
{
    //удаление очереди
    delete[]Wait;
    delete[]Pri;
}

Wieza::Wieza(int m)
{
    //получаем размер
    MaxQueueLength=m;
    //создаем очередь
    Wait=new Lot[MaxQueueLength];
    Pri=new int[MaxQueueLength];
    // Изначально очередь пуста
    QueueLength = 0;
}

void Wieza::Clear()
{
    // Эффективная "очистка" очереди
    QueueLength = 0;
}

bool Wieza::IsEmpty()
{
    // Пуст?
    return QueueLength == 0;
}

bool Wieza::IsFull()
{
    // Полон?
    return QueueLength == MaxQueueLength;
}

int Wieza::GetCount()
{
    // Количество присутствующих в стеке элементов
    return QueueLength;
}

void Wieza::Add(Lot c,int p)
{
    // Если в очереди есть свободное место, то увеличиваем количество
    // значений и вставляем новый элемент
    if(!IsFull()){
        Wait[QueueLength] = c;
        Pri[QueueLength] = p;
        QueueLength++;
    }
}

Lot Wieza::Extract()
{
    // Если в очереди есть элементы, то возвращаем тот,
    // у которого наивысший приоритет и сдвигаем очередь
    if(!IsEmpty()){


        //пусть приоритетный элемент - нулевой
        int max_pri=Pri[0];
        //а приоритетный индекс = 0
        int pos_max_pri=0;

        //ищем приоритет
        for(int i=1;i<QueueLength;i++)
            //если встречен более приоритетный элемент
            if(max_pri<Pri[i]){
                max_pri=Pri[i];
                pos_max_pri=i;
            }

        //вытаскиваем приоритетный элемент
        Lot temp1=Wait[pos_max_pri];
        int temp2=Pri[pos_max_pri];

        //сдвинуть все элементы
        for(int i=pos_max_pri;i<QueueLength-1;i++){
            Wait[i]=Wait[i+1];
            Pri[i]=Pri[i+1];
        }
        //уменьшаем количество
        QueueLength--;
        // возврат извлеченного элемента
        return temp1;

    }

}

int main(void)
{
    // tworzenie bortwo
    Lot b1,b2,b3;
    b1.iL = "b3";
    b1.iP = 100;
    b1.pL = 12;
    b2.iL = "b2";
    b2.iP = 100;
    b2.pL = 55;
    b3.iL = "b3";
    b3.iP = 100;
    b3.pL = 3;

    //создание очереди
    Wieza Swidnik2021(25);

    //заполнение части элементов
    Swidnik2021.Add(b1,b1.pL);
    Swidnik2021.Add(b2,b2.pL);
    Swidnik2021.Add(b3,b3.pL);

    //показ очереди
    Swidnik2021.Show();

    //извлечение элемента
    vector<Lot> extractElemnts;
    extractElemnts.push_back(Swidnik2021.Extract());

    //показ очереди
    Swidnik2021.Show();

    cout << "samoloty ktorzy wyladowali do tej pory na lotnisku" << "\n";
    for(auto le : extractElemnts) {
        cout << le.iL << " ilosc pasazerow "<< le.iP << "\n";
    }
    Swidnik2021.Clear();
    Swidnik2021.Show();



}
