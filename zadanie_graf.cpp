#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct wierzcholek {
    int id;
    int krawedzie[20] = {1000};
};

struct krawedzOryginalna{
    int idGrafuSprzezonego;
    int poczatek;
    int koniec;
};

int main() {
    wierzcholek wierzcholki[20];
    int liczbaWierzcholkow = 0;

    for (int i = 0; i < 20; ++i) {
        wierzcholki[i].id = 0;
        for (int j = 0; j < 20; ++j) wierzcholki[i].krawedzie[j] = 1000;
    }

    ifstream plik("graf.txt");
    if (!plik) {
        cout << "Blad otwierania pliku" << endl;
        return 1;
    }

    string linia;
    while(plik) {
        size_t nastepnaKrawedz = 0;

        if (!getline(plik, linia)) break;
        int liczba_krawedzi = 0;

        size_t obecnaPozycja = linia.find(':');
        if (obecnaPozycja == string::npos) continue;
        int wierzcholek = stoi(linia.substr(0, obecnaPozycja));
        wierzcholki[wierzcholek - 1].id = wierzcholek;
        liczbaWierzcholkow++;
        obecnaPozycja += 2;

        while (obecnaPozycja < linia.length()) {
            size_t nastepnaKrawedz = linia.find(' ', obecnaPozycja);
            if (nastepnaKrawedz == string::npos) {
                int krawedz = stoi(linia.substr(obecnaPozycja));
                if(liczba_krawedzi >= 20){
                    cout << "Graf nie jest sprzezony" << endl;
                    return 0;
                }
                wierzcholki[wierzcholek - 1].krawedzie[liczba_krawedzi++] = krawedz;
                break;
            } else {
                int krawedz = stoi(linia.substr(obecnaPozycja, nastepnaKrawedz - obecnaPozycja));
                if(liczba_krawedzi >= 20){
                    cout << "Graf nie jest sprzezony. Krawedzie wielokrotne." << endl;
                    return 0;
                }
                wierzcholki[wierzcholek - 1].krawedzie[liczba_krawedzi++] = krawedz;
                obecnaPozycja = nastepnaKrawedz + 1;
            }
        }

        for (int i = 0; i < 20; i++) {
            for (int j = i + 1; j < 20; j++) {
                if (wierzcholki[wierzcholek - 1].krawedzie[i] > wierzcholki[wierzcholek - 1].krawedzie[j]) {
                    swap(wierzcholki[wierzcholek - 1].krawedzie[i], wierzcholki[wierzcholek - 1].krawedzie[j]);
                }
            }
        }
    }

    
    for(int i =0; i<19; i++){
        if(wierzcholki[i].id == 0) continue;
        for(int j=i+1; j<20; j++){
            bool identyczne = false;
            if(wierzcholki[j].id == 0) continue;
            for(int k=0; k<20; k++){
                if(wierzcholki[i].krawedzie[k] == 1000) {
                    if(identyczne == false || wierzcholki[j].krawedzie[k] == 1000){
                        break;
                    }else{
                        cout << "Graf nie jest sprzezony. Wiecej krawedzi w innym wierzcholku." << endl;
                        return 0;
                    }
                };

                if(k > 0){
                    if(wierzcholki[i].krawedzie[k-1] == wierzcholki[i].krawedzie[k]){
                        cout << "Graf nie jest sprzezony. Krawedzie wielokrotne." << endl;
                        return 0;
                    }
                }

                if(identyczne && wierzcholki[i].krawedzie[k] != wierzcholki[j].krawedzie[k]){
                    cout << wierzcholki[i].krawedzie[k] << " != " << wierzcholki[j].krawedzie[k] << endl;
                    cout << "Graf nie jest sprzezony. Rozne krawedzie, z tym samym poczatkiem." << endl;
                    return 0;
                }

                if(wierzcholki[i].krawedzie[k] == wierzcholki[j].krawedzie[k]){
                    identyczne = true;
                    continue;
                }

                for(int l=0; l<20; l++){
                    if(wierzcholki[j].krawedzie[l] == 1000) {
                        break;
                    }
                   if(wierzcholki[i].krawedzie[k] == wierzcholki[j].krawedzie[l]){
                       cout << "Graf nie jest sprzezony. Rozne krawedzie." << endl;
                       return 0;
                    }
                }
            }
        }
    }

    cout << "Graf jest sprzezony." << endl;





    int liczbaWierzcholkowOryginalnych = 0;
    int liczbaKrawedziOryginalnych = 0;
    krawedzOryginalna krawedzieOryginalne[1000];

    for(int i=0; i<liczbaWierzcholkow; i++){
        krawedzieOryginalne[liczbaKrawedziOryginalnych].idGrafuSprzezonego = wierzcholki[i].id;
        krawedzieOryginalne[liczbaKrawedziOryginalnych].poczatek = i*2;
        krawedzieOryginalne[liczbaKrawedziOryginalnych++].koniec = i*2+1;
    }

    for(int i=0; i<liczbaWierzcholkow; i++){
        for(int j=0; j<20; j++){
            if(wierzcholki[i].krawedzie[j] == 1000) break;
            int wierzcholekDocelowy = wierzcholki[i].krawedzie[j];
            for(int k=0; k<liczbaKrawedziOryginalnych; k++){
                if(krawedzieOryginalne[k].idGrafuSprzezonego == wierzcholekDocelowy){
                    if(krawedzieOryginalne[i].koniec != krawedzieOryginalne[k].poczatek){
                        int poszukiwanaLiczba = krawedzieOryginalne[k].poczatek;
                        int liczbaZmieniona = krawedzieOryginalne[i].koniec;
                        for(int l=0; l<liczbaKrawedziOryginalnych; l++){
                            if(krawedzieOryginalne[l].poczatek == poszukiwanaLiczba){
                                krawedzieOryginalne[l].poczatek = liczbaZmieniona;
                            }
                            if(krawedzieOryginalne[l].koniec == poszukiwanaLiczba){
                                krawedzieOryginalne[l].koniec = liczbaZmieniona;
                            }
                        }
                        break;
                    }
                    else{
                        break;
                    }
                }
            }
        }
    }
    int numerWierzcholka = 1001;

    for(int i=0; i<liczbaKrawedziOryginalnych; i++){
        int szukanyNumer = krawedzieOryginalne[i].poczatek;
        if(szukanyNumer < 1000){
            for(int j=0; j<liczbaKrawedziOryginalnych; j++){
                if(krawedzieOryginalne[j].poczatek == szukanyNumer){
                    krawedzieOryginalne[j].poczatek = numerWierzcholka;
                }
                if(krawedzieOryginalne[j].koniec == szukanyNumer){
                    krawedzieOryginalne[j].koniec = numerWierzcholka;
                }
            }
            numerWierzcholka++;
        }
        szukanyNumer = krawedzieOryginalne[i].koniec;
        if(szukanyNumer < 1000){
            
            for(int j=0; j<liczbaKrawedziOryginalnych; j++){
                if(krawedzieOryginalne[j].poczatek == szukanyNumer){
                    krawedzieOryginalne[j].poczatek = numerWierzcholka;
                }
                if(krawedzieOryginalne[j].koniec == szukanyNumer){
                    krawedzieOryginalne[j].koniec = numerWierzcholka;
                }
            }
            numerWierzcholka++;
        }
    }

    wierzcholek wierzcholkiOryginalne[20];

    for(int i=0; i<20; i++){
        wierzcholkiOryginalne[i].id = 0;
        for(int j=0; j<20; j++) wierzcholkiOryginalne[i].krawedzie[j] = 1000;
    }


    for(int i = 1; i<numerWierzcholka - 1000;i++){
        int nastepnaKrawedz = 0;
        for(int j=0; j<liczbaKrawedziOryginalnych; j++) {
            wierzcholkiOryginalne[i].id = i;
            if(krawedzieOryginalne[j].poczatek == i+1000){
                wierzcholkiOryginalne[i].krawedzie[nastepnaKrawedz] = krawedzieOryginalne[j].koniec - 1000;
                nastepnaKrawedz++;
            }
        }
    }

    // przejdz po wszystkich wierzcholkach i sprawdz czy mają powtarzające się krawędzie

    bool liniowy = true;

    for(int i=0; i<20; i++){
        if(wierzcholkiOryginalne[i].id == 0) continue;
        for(int j=0; j<20; j++){
            if(wierzcholkiOryginalne[i].krawedzie[j] == 1000) break;
            for(int k=j+1; k<20; k++){
                if(wierzcholkiOryginalne[i].krawedzie[k] == 1000) break;
                if(wierzcholkiOryginalne[i].krawedzie[j] == wierzcholkiOryginalne[i].krawedzie[k]){
                    liniowy = false;
                    cout << "Graf nie jest liniowy." << endl;
                    break;
                }
            }
            if(!liniowy) break;
        }
        if(!liniowy) break;
    }
    if(liniowy){
        cout << "Graf jest liniowy." << endl;
    }

    ofstream plikWynik("wynik.txt");
    if (!plikWynik) {
        cout << "Blad otwierania pliku wynikowego" << endl;
        return 1;
    }

    for(int i=0; i<20; i++){
        if(wierzcholkiOryginalne[i].id == 0) continue;
        plikWynik << wierzcholkiOryginalne[i].id << ": ";
        for(int j=0; j<20; j++){
            if(wierzcholkiOryginalne[i].krawedzie[j] == 1000) break;
            plikWynik << wierzcholkiOryginalne[i].krawedzie[j] << " ";
        }
        plikWynik << endl;
    }

    plikWynik.close();
    return 0;
}