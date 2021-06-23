#include <iostream>

using namespace std;

template <typename T>
class KolejkaT{
    int n;
    int poczatek = 0;
    T *arr;
public:
    KolejkaT(int n){
        arr = new T[n];
        this->n = n;
//        for(int i = 0; i < n; ++i){
//            arr[i] = 0;
//        }
    }
    bool empty(){
        return poczatek == 0 ? true : false;
    }
    // zadanie 3b)
    bool jednoelementowa(){
        return poczatek == 1 ? true : false;
    }
    void push(T data){
        if(empty()){
            arr[0] = data;
            poczatek++;
        }
        else{
            if(poczatek < n){
                for(int i = poczatek; i >= 0; --i){
                    arr[i + 1] = arr[i];
                }
                arr[0] = data;
                poczatek++;
            }
            else{
                throw out_of_range("Brak miejsc");
            }
        }
    }
    void pop(){
        if(empty()){
            throw out_of_range("Kolejka pusta");
        }
        else{
            poczatek--;
        }
    }
    T top(){
        return arr[poczatek - 1];
    }
    int IleWolnych(){
        return n - poczatek;
    }
    // zadanie 3a)
    int IleElementow(){
        return poczatek;
    }
    // zadanie 3c)
    void zamien_miejscami(){
        T a = arr[0];
        T b = arr[poczatek - 1];
        arr[0] = b;
        arr[poczatek - 1] = a;
    }
    // zadanie 3e)
    void reverse(){
        T *arr_tmp = new T[n];
        int tmp = poczatek - 1;
        for(int i = 0; i < poczatek; ++i){
            arr_tmp[i] = arr[tmp];
            tmp--;
        }
        for(int i = 0; i < poczatek; ++i){
            arr[i] = arr_tmp[i];
        }
    }
    // zadanie 3d)
    void operator+=(KolejkaT &kolejka){
        if(this->n - this->poczatek > this->poczatek + kolejka.poczatek){
            for(int i = kolejka.poczatek - 1; i >= 0; --i){
                this->push(kolejka.top());
                kolejka.pop();
            }
        }
        else{
            throw out_of_range("Brak miejsca dla nowej kolejki");
        }
    }
    // zadanie 5
    int wieksze_od_x(T x){
        int tmp = 0, tmp_2 = poczatek;
        KolejkaT<T> tmp_kol(n);
        for(int i = poczatek - 1; i >= 0; --i){
            if(x+1 > arr[i]){
                tmp_kol.push(arr[i]);
                tmp++;
            }
        }
        for(int i = poczatek - 1; i >= 0; --i){
            this->pop();
        }
        for(int i = 0; i < tmp; ++i){
            this->push(tmp_kol.arr[i]);
        }
        return tmp_2 - tmp_kol.poczatek;
    }
    // zadanie 6
    int mniejsze_od_x(T x){
        int tmp = 0, tmp_2 = poczatek;
        KolejkaT<T> tmp_kol(n);
        for(int i = poczatek - 1; i >= 0; --i){
            if(x-1 < arr[i]){
                tmp_kol.push(arr[i]);
                tmp++;
            }
        }
        for(int i = poczatek - 1; i >= 0; --i){
            this->pop();
        }
        for(int i = 0; i < tmp; ++i){
            this->push(tmp_kol.arr[i]);
        }
        return tmp_2 - tmp_kol.poczatek;
    }
//    void show(){
//        for(int i = poczatek - 1; i >= 0; --i){
//            cout << arr[i] << " ";
//        }
//    }
    ~KolejkaT(){
        delete [] arr;
    }
};

int losowanie( int liczba_poczakotwa, int liczba_koncowa )
{
    int przedzial_liczb = liczba_koncowa - liczba_poczakotwa + 1;
    int c = (rand() % przedzial_liczb) + liczba_poczakotwa;
    return c;
}

struct Kasa{
    int clients_count;
    int how_long;
    int free_time;
    bool is_it_free;
    int klient_czas;
    Kasa(): clients_count(0), how_long(0), free_time(5400), is_it_free(true) {}
};

int main(){

    int a, b;
    cout << "Podaj ilosc kas: ";
    cin >> a;
    Kasa kasa;
    KolejkaT<Kasa> kolejka_kas(a);
    for(int i = 0; i < a; ++i){
        kolejka_kas.push(kasa);
    }


    cout << "Podaj ilosc klientow: ";
    cin >> b;
    KolejkaT<int> kolejka_klientow(b);

    for(int i = 0; i < b; ++i){
        int c = losowanie(1,20);
        try{
            kolejka_klientow.push(c);
        }
        catch(exception &e){
            cout << e.what() << endl;
        }
    }

    cout << endl;

    int czas = 5400;
    while(czas != 0){
        while(!kolejka_klientow.empty()){
            if(kolejka_kas.top().is_it_free){
                Kasa kasa = kolejka_kas.top();
                kasa.is_it_free = false;
                kolejka_kas.pop();
                kasa.klient_czas = kolejka_klientow.top();
                kasa.how_long += kolejka_klientow.top();
                kasa.free_time -= kolejka_klientow.top();
                kasa.clients_count++;
                kolejka_klientow.pop();
                kolejka_kas.push(kasa);
            }
            else{
                Kasa kasa = kolejka_kas.top();
                kasa.klient_czas--;
                if(kasa.klient_czas == 0){
                    kasa.is_it_free = true;
                }
                kolejka_kas.pop();
                kolejka_kas.push(kasa);
                czas--;
            }
        }
        czas--;
    }

    for(int i = 0; i < a; ++i){
        cout << "Ile pracowala " << kolejka_kas.top().how_long << " Wolny czas " <<
            kolejka_kas.top().free_time << " Ile obsluzonych " << kolejka_kas.top().clients_count << endl;
        kolejka_kas.pop();
    }

    return 0;
}