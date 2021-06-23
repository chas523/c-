#include <iostream>

using namespace std;

template<typename TypDanych>
class Wierzcholek{
public:
    TypDanych dane;
    typedef Wierzcholek <TypDanych> *WskWierzcholka;
    WskWierzcholka lewy,prawy;
    int level;
    Wierzcholek(const TypDanych &d):lewy(nullptr),prawy(nullptr),dane(d),level(1){}
};

template<typename TypDanych>
class Drzewo{
protected:
    typedef Wierzcholek <TypDanych> *WskWierzcholka;
    // Wierzcholek <TypDanych> * korzen;
    WskWierzcholka korzen; // root
public:
    Drzewo(){
        korzen = nullptr;
    } //konstruktor pustego drzewa
    Drzewo(const Drzewo &); //konstruktor kopiujący
    bool Wstaw(const TypDanych &d){
        return WstawPomocnicza(korzen,d);
    } //mogło wstawianie się nie udać
    void PreOrder()const{
        PreOrderPom(korzen);
    }
    void InOrder()const{
        InOrderPom(korzen);
    }
    void PostOrder()const{
        PostOrderPom(korzen);
    }
    virtual bool Usun(const TypDanych &)=0;
    virtual ~Drzewo(){
        if(korzen != nullptr){
            UsunDrzewo(korzen);
            korzen = nullptr;
        }
    }
    protected:
    //f u n k c j e   p o m o c n i c z e
    virtual bool WstawPomocnicza(WskWierzcholka & ,const TypDanych &)=0;
    void InOrderPom(WskWierzcholka wsk) const{
        if(wsk != nullptr){
            InOrderPom(wsk->lewy);
            cout << wsk->dane << ' ';
            InOrderPom(wsk->prawy);
        }
    }
    void PreOrderPom(WskWierzcholka wsk) const{
        if(wsk != nullptr){
            cout << wsk->dane << ' ';
            PreOrderPom(wsk->lewy);
            PreOrderPom(wsk->prawy);
        }
    }
    void PostOrderPom(WskWierzcholka wsk) const{
        if(wsk != nullptr){
            PostOrderPom(wsk->lewy);
            PostOrderPom(wsk->prawy);
            cout << wsk->dane << ' ';
        }
    }
    void UsunDrzewo(WskWierzcholka &w){
        if(w != nullptr){
            UsunDrzewo(w->lewy);
            UsunDrzewo(w->prawy);
            delete w;
        }
    }
    //ewentualnie jeszcze inne metody np. CzyPełne -Czy Brak Pamięci...};
};

template<typename TypDanych>
class DrzewoD : public Drzewo<TypDanych>{
    bool WstawPomocnicza(typename Drzewo<TypDanych>::WskWierzcholka &wsk,  const TypDanych &d){
        if(wsk == nullptr) {
            //drzewo jest puste -próba dołączenia
            Wierzcholek<TypDanych> *pom;
            try{
                pom = new Wierzcholek<TypDanych>(d);
                wsk=pom;
                return true;
            }catch(...){
                return false;
            }
        }
        else if(d < wsk->dane){//drzewo nie jest puste
            //cout << "left " << d << endl;
            return WstawPomocnicza(wsk->lewy,d);
        }
        else if(d>wsk->dane){
            //cout << "right " << d << endl;
            return WstawPomocnicza(wsk->prawy,d);
        }
        else
            return false;//lub coś innego według wymagań
    }
    void InOrderBackPom(typename Drzewo<TypDanych>::WskWierzcholka wsk) const{
        if(wsk != nullptr){
            InOrderBackPom(wsk->prawy);
            cout << wsk->dane << ' ';
            InOrderBackPom(wsk->lewy);
        }
    }
    void PreOrderBackPom(typename Drzewo<TypDanych>::WskWierzcholka wsk) const{
        if(wsk != nullptr){
            cout << wsk->dane << ' ';
            PreOrderBackPom(wsk->prawy);
            PreOrderBackPom(wsk->lewy);
        }
    }
    void PostOrderBackPom(typename Drzewo<TypDanych>::WskWierzcholka wsk) const{
        if(wsk != nullptr){
            PostOrderBackPom(wsk->prawy);
            PostOrderBackPom(wsk->lewy);
            cout << wsk->dane << ' ';
        }
    }
    int wysokoscDrzewa = 0;
    int najkrutszy = 2147483647;
    int iloscLisci = 0;
    int zJednymSynem = 0;
    int ilosc = 0;
    int iloscWewnetrznych = 0;

    void POM(typename Drzewo<TypDanych>::WskWierzcholka v){
        if(v){
            int children = 0;
            if(v->lewy){
                children++;
                v->lewy->level = v->level + 1;
            }
            if(v->prawy){
              children++;
              v->prawy->level = v->level + 1;
            }
            if(v->level > wysokoscDrzewa){
                wysokoscDrzewa = v->level;
            }
            if(!children){
                if(v->level < najkrutszy){
                    najkrutszy = v->level;
                }
                iloscLisci++;
            }
            if(children == 1){
                zJednymSynem++;
            }
            if(v != this->korzen && v->lewy && v->prawy){
                iloscWewnetrznych++;
            }
            ilosc++;
            POM(v->lewy);
            POM(v->prawy);
        }
    }

    void wyswietlWierzcholkiWewnetrznePom(typename Drzewo<TypDanych>::WskWierzcholka v){
        if(v){
            if(v != this->korzen && v->lewy && v->prawy){
                cout << v->dane << endl;
            }
            wyswietlWierzcholkiWewnetrznePom(v->lewy);
            wyswietlWierzcholkiWewnetrznePom(v->prawy);
        }
    }
    void reversePom(typename Drzewo<TypDanych>::WskWierzcholka v){
        if(v){
            typename Drzewo<TypDanych>::WskWierzcholka pom;

            pom = v->lewy;
            v->lewy = v->prawy;
            v->prawy = pom;

            reversePom(v->lewy);
            reversePom(v->prawy);
        }
    }

public:
    void reverse(){
        reversePom(this->korzen);
    }
    void wyswietlWierzcholkiWewnetrzne(){
        wyswietlWierzcholkiWewnetrznePom(this->korzen);
    }
    void wyswietlWyniki(){
        this->POM(this->korzen);
        cout << endl << endl << "Najdluzsza sciezka(wysokosc drzewa): " << wysokoscDrzewa << endl;
        cout << endl << "Najkrutsza sciezka: " << najkrutszy << endl;
        cout << endl << "Ilosc lisci: " << iloscLisci << endl;
        cout << endl << "ilosc wiercholkow majacych tylko jednego syna: " << zJednymSynem << endl;
        cout << endl << "ilosc wierzcholkow: " << ilosc << endl;
        cout << endl << "ilosc wierzcholkow wewnetrznych: " << iloscWewnetrznych << endl;
    }
    void InOrderBack(){
        InOrderBackPom(this->korzen);
    }
    void PreOrderBack(){
        PreOrderBackPom(this->korzen);
    }
    void PostOrderBack(){
        PostOrderBackPom(this->korzen);
    }
    bool Usun(const TypDanych &d){
        Wierzcholek<TypDanych> *rodzic, *usuwany, *zamienny;
        //przygotowanie poszukiwań wierzchołka drzewa zawierającegod
        rodzic = nullptr;
        usuwany = this->korzen;
         while(usuwany != nullptr && usuwany->dane != d){
             rodzic = usuwany;
             if(d < rodzic->dane)
                 usuwany = usuwany->lewy;
             else
                 usuwany = usuwany->prawy;
         }//czy jest d na drzewie
         if(usuwany == nullptr)
             return false; // jest i sprawdzamy jaki to jest przypadek
         //zaczynamy od liścia
         if(usuwany->lewy == nullptr && usuwany->prawy == nullptr){
             //usuwamy liścia
             if(rodzic != nullptr){
                 if(rodzic->lewy == usuwany)
                     rodzic->lewy = nullptr;
                 else
                     rodzic->prawy = nullptr;
             }
             else//usuwany korzeń
                 this->korzen = nullptr;
             delete usuwany;
         }
         else{/* jest przynajmniej jedno poddrzewo wyznaczymy zamiennego do przekazania danych a później do usunięcia*/
             if(usuwany->lewy == nullptr || usuwany->prawy == nullptr){
                 if(usuwany->lewy == nullptr)//prawy jest zamiennym
                     zamienny = usuwany->prawy;
                 else//lewy jest zamiennym
                     zamienny = usuwany->lewy;
                 //przeładujemy wartości z zamiennego do usuwanego/*
                 usuwany->prawy = zamienny->prawy;
                 usuwany->lewy = zamienny->lewy;
                 usuwany->dane = zamienny->dane;
                 // to jest wersja dłuższa a teray będzie krótsza*/
                 *usuwany = *zamienny;
             }
             else{// są oba poddrzewa
                 //wyznaczamy zamiennyz lewej strony
                 rodzic = usuwany;
                 zamienny = usuwany->lewy;
                 while(zamienny->prawy != nullptr){
                     rodzic = zamienny;
                     zamienny = zamienny->prawy;
                 }//mamy wyznaczony zamienny
                 usuwany->dane = zamienny->dane; //zmieniamy powiązania w drzewie przed usunięciem zamiennego
                 if(rodzic == usuwany) //pętla nie ruszyła
                     rodzic->lewy = zamienny->lewy;
                 else
                     rodzic->prawy = zamienny->lewy;
             }
             delete zamienny;
         }
         return true;
    }

    void wyswietlLiscieRosnaco(){
        Drzewo<TypDanych>::InOrder();
    }
};

int main(){

    DrzewoD<int> d;
    int t[] = {40,30,60,20,38,32,35,31,50,80,100};
    for(int i = 0; i < 11; i++)
        d.Wstaw(t[i]);
    cout << "PostOrder: " << endl;
    d.PostOrder();
    cout << endl << endl << "PostOrder Back:" << endl;
    d.PostOrderBack();
    cout << endl << endl << "Inorder:" << endl;
    d.InOrder();
    cout << endl << endl << "Inorder Back:" << endl;
    d.InOrderBack();
    cout << endl << endl << "Preorder:" << endl;
    d.PreOrder();
    cout << endl << endl << "Preorder Back:" << endl;
    d.PreOrderBack();
    d.wyswietlWyniki();
    cout << endl << "Liscie rosnaco: " << endl;
    d.wyswietlLiscieRosnaco();
    cout << endl << endl << "Wierzcholki Wewnetrzne: " << endl;
    d.wyswietlWierzcholkiWewnetrzne();
    d.reverse();
    cout << endl << "Drzewo po odwruceniu: " << endl;
    d.InOrder();

//    d.Usun(40);
//    d.InOrder();

    return 0;
}
















