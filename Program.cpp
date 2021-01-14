#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include <fstream>

using namespace std;

int ile, rozmiar;
clock_t start,stop;
double czas;

void scalanie(int *Tab, int lewy, int srodek, int prawy) // funkcja scalajaca podtablice
{
    int i, j, k; // zmienne iteracyjne do petli "for"
    int lewyRozmiar = srodek-lewy+1; // rozmiar lewej podtablicy
    int prawyRozmiar = prawy-srodek; // rozmiar prawej podtablicy
    int *lewyTab = new int[lewyRozmiar]; // deklaracja lewej podtablicy o odpowiednim rozmiarze
    int *prawyTab = new int[prawyRozmiar]; // deklaracja prawej podtablicy o odpowiednim rozmiarze
    for(i = 0; i<lewyRozmiar; i++)
    {
        lewyTab[i] = Tab[lewy+i]; // wypelnienie lewej podtablicy odpowiednimi liczbami z tablicy
    }
    for(j = 0; j<prawyRozmiar; j++)
    {
        prawyTab[j] = Tab[srodek+1+j];  // wypelnienie prawej podtablicy odpowiednimi liczbami z tablicy
    }
    i = 0;
    j = 0;
    k = lewy; // przypisanie wartosci zmiennym iteracyjnym potrzebnym do petli "for"
    while(i < lewyRozmiar && j<prawyRozmiar)
    {
        if(lewyTab[i] <= prawyTab[j])
        {
            Tab[k] = lewyTab[i];    // scalenie podtablic z tablica glowna
            i++;                    // inkrementacja zmiennej i
        }
        else
        {
            Tab[k] = prawyTab[j];
            j++; // inkrementacja zmiennej j
        }
        k++; // inkrementacja zmiennej k
    }
    while(i<lewyRozmiar)
    {
        Tab[k] = lewyTab[i];    // dodatkowy element z lewej podtablicy
        i++;
        k++;   // inkrementacja zmiennej k i zmiennej i
    }
    while(j<prawyRozmiar)
    {
        Tab[k] = prawyTab[j];   //dodatkowy element z prawej podtablicy
        j++;
        k++; // inkrementacja zmiennej k i zmiennej j
    }
}

void mergesort(int *Tab, int lewy, int prawy) // funkcja realizujaca sortowanie przez scalanie
{
    int srodek; // zmienna przechowujaca srodek tablicy
    if(lewy < prawy)
    {
        srodek = lewy+(prawy-lewy)/2; // wyznaczenie srodka tablicy, potrzebnego do podzialu na 2 tablice,
        mergesort(Tab, lewy, srodek); // sortowanie rekurencyjnie lewej czesci tablicy
        mergesort(Tab, srodek+1, prawy);    // sortowanie rekurencyjnie prawej czesci tablicy
        scalanie(Tab, lewy, srodek, prawy); // scalenie lewej i prawej czesci tablicy
    }
}

//sortowanie quicksort
void quicksort(int *tablica, int lewy, int prawy)  //funkcja realizująca sortowanie metoda quicksort
{
    int v=tablica[(lewy+prawy)/2];  //zmienna v to obrany piwot
    int i,j,x;  //zmienne iteracyjne dla petli while
    i=lewy;
    j=prawy;
    do
    {
        while(tablica[i]<v)  //przeniesienie do lewej tablicy elementow mniejszych od piwota
            i++;
        while(tablica[j]>v)  //przeniesienie do lewej tablicy elementow wiekszych od piwota
            j--;
        if(i<=j)
        {
            x=tablica[i];
            tablica[i]=tablica[j];
            tablica[j]=x;
            i++;
            j--;
        }
    }
    while(i<=j);
    if(j>lewy)
        quicksort(tablica,lewy, j);  // sortowanie rekurencyjnie lewej czesci tablicy
    if(i<prawy)
        quicksort(tablica, i, prawy);  // sortowanie rekurencyjnie prawej czesci tablicy
}

int main()
{
    fstream plik, wyniki;
    // plik.open("tablica.txt", ios::in);  //funkcja do wczytywania tablic do testow
    wyniki.open("wyniki.txt", ios::out);
    cout << "Porownanie czasow sortowania" << endl;

    cout<<"Ile losowych liczb w tablicy: ";
    cin>>ile;

    //dynamiczna alokacja tablicy

    int *tablica;
    tablica=new int [ile];

    int *tablica2;
    tablica2=new int [ile];

    //inicjowanie generatora
    srand(time(NULL));

     //wczytywanie losowych liczb do tablicy
     for(int i=0; i<ile; i++)
    {
        tablica[i] = rand()%100000+1;
    }

/*
    int ile=1000;  //liczba elementow w pliku  //funkcja do wczytywania tablic do testow
    int tablica[ile];  //zadeklarowanie dwoch tablic
    int tablica2[ile];

    for(int i=0; i<ile; i++) //petla wpisujaca elementy z pliku do tablicy
    {
        plik>>tablica[i];
    }
*/

    //przepisanie tablicy do tablicy 2
    for(int i=0; i<ile; i++)
    {
        tablica2[i]=tablica[i];
    }


    //testowe wypisanie losowo wygenerowanej tablicy
    cout<<"Przed posortowaniem: "<<endl;
    wyniki<<"Przed posortowaniem: "<<endl;
        for(int i=0; i<ile; i++)
        {
            cout<<tablica[i]<<" ";   //mozliwosc zmiany na tablica2[i] w celu sprawdzenia poprawnoœci sortowania metoda quicksort
            wyniki<<tablica[i]<<" ";
        }


    cout<<endl<<"Sortowanie  algorytmem przez scalanie."<<endl;
    start = clock();  //zanotowanie liczby cykli procesora w momencie rozpoczecia algorytmu
    mergesort(tablica, 0, ile-1);  //wywolanie funkcji
    stop = clock();  //zatrzymanie pobierania liczby cykli
    czas = (double)(stop-start) / CLOCKS_PER_SEC;  //podzielenie liczby cykli przez stala oraz zrzutowanie na typ double
    cout<<endl<<"Czas sortowania przez scalanie: "<<czas<<" s"<<endl;  //wypisanie czasu sortowania
    wyniki<<"\n"<<endl<<"Czas sortowania przez scalanie: "<<czas<<" s"<<endl;

    cout<<endl<<"Sortowanie algorytmem quicksort."<<endl;
    start = clock();
    quicksort(tablica2, 0, ile-1);
    stop = clock();
    czas = (double)(stop-start) / CLOCKS_PER_SEC;
    cout<<endl<<"Czas sortowania quicksort: "<<czas<<" s"<<endl;
    wyniki<<endl<<"Czas sortowania quicksort: "<<czas<<" s"<<endl;


    //testowe wypisanie posortowanej, losowo wygenerowanej tablicy
    cout<<"Po posortowaniu: "<<endl;
    wyniki<<"\n"<<"Po posortowaniu: "<<endl;
        for(int i=0; i<ile; i++)
        {
            cout<<tablica[i]<<" ";   //mozliwosc zmiany na tablica2[i] w celu sprawdzenia poprawnoœci sortowania metoda quicksort
            wyniki<<tablica[i]<<" ";
        }

    plik.close();
    wyniki.close();

    delete [] tablica;
    delete [] tablica2;

    return 0;
}
