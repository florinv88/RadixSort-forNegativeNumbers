#include <iostream>
using namespace std;

// functie care imi returneaza un vector doar cu valori pozitive/negative
void extractValues(int vec[], int size, int pVector[], bool tip)
{

    int k = 0;
    if (tip == true)
    {
        for (int i = 0; i < size; i++)
            if (vec[i] >= 0)
            {
                pVector[k] = vec[i];
                k++;
            }
    }
    else
    {
        for (int i = 0; i < size; i++)
            if (vec[i] < 0)
            {
                pVector[k] = -vec[i];
                k++;
            }
    }
}

// functie pentru a gasi maximul din vector
int getMax(int vec[], int size)
{
    int maxElement = vec[0];
    for (int i = 1; i < size; i++)
        if (maxElement < vec[i])
            maxElement = vec[i];
    return maxElement;
}

void CountingSort(int vec[], int size, int div)
{
    int vector_iteratie[size];     // vector temporar
    int frecventa_cifre[10] = {0}; // vector de frecventa

    // parcurgem vectorul si incarcam vectorul de frecventa
    // folosindu-ne de puterea lui 10 (div) pentru a compara cifrele care ne intereseaza

    for (int i = 0; i < size; i++)
    {
        int unitate = (vec[i] / div) % 10;
        frecventa_cifre[unitate]++;
    }

    // adaugam acumulativ valorile de pe pozitiile anterioare
    //  ele ne vor arata pozitiile elementelor in vectorul final
    for (int i = 1; i < 10; i++)
    {
        frecventa_cifre[i] += frecventa_cifre[i - 1];
    }

    // ordonarea elementelor in vectorul iteratie tinand cont de vectorul de frecventa
    for (int i = size - 1; i >= 0; i--)
    {
        int pozitie = frecventa_cifre[(vec[i] / div) % 10] - 1;
        vector_iteratie[pozitie] = vec[i];
        frecventa_cifre[(vec[i] / div) % 10]--;
    }

    // copiere in vectorul original
    for (int i = 0; i < size; i++)
    {
        vec[i] = vector_iteratie[i];
    }
}

void RadixSort(int vec[], int size)
{

    // Gandire numere reale
    //-impart vectorul in 2 vectori , nr pozitive / nr negative
    //-consider numerele negative in modul (la sfarsit la fac iar negative cand adaug in vectorul sortat)
    //-apelez getMax si sortez fiecare vector in parte

    // NR POZITIVE

    // Formez vectorul
    int pSize = 0;
    for (int i = 0; i < size; i++)
        if (vec[i] >= 0)
            pSize++;
    int pVector[pSize];
    extractValues(vec, size, pVector, true);

    // apelam functia getMax implementata mai sus
    // pentru a obtine maximul din vector
    // pentru a stii de cate ori trebuie sa apelam countingSort-ul

    int mPoz = getMax(pVector, pSize);
    for (int div = 1; mPoz / div > 0; div = div * 10)
    {
        // apelam countingSort pentru fiecare unitate
        CountingSort(pVector, pSize, div);
    }

    // NR NEGATIVE
    int nSize = size - pSize;
    int nVector[nSize];
    extractValues(vec, size, nVector, false);

    int mNeg = getMax(nVector, nSize);
    for (int div = 1; mNeg / div > 0; div = div * 10)
    {
        // apelam countingSort pentru fiecare unitate
        CountingSort(nVector, nSize, div);
    }

    // FORMEZ UN NOU VECTOR
    // va fi format din cei 2 vectori
    // cel negativ este sortat crescator dar pentru ca am luat valorile in modul v-a trebuie sa il punem de la sfarsit la inceput

    int vec_temp[size];
    for (int i = 0; i < nSize; i++)
    {
        vec_temp[i] = -nVector[nSize - i - 1];
    }
    int k = 0;
    for (int i = nSize; i < size; i++)
    {
        vec_temp[i] = pVector[k];
        k++;
    }

    // Copiem in vectorul original

    for (int i = 0; i < size; i++)
    {
        vec[i] = vec_temp[i];
    }
}

int main()
{
    // declarare & citire vector
    int size;
    cout << "Marimea vectorului este : " << endl;
    cin >> size;
    int vec[size];
    cout << "Introduceti elementele vectorului : " << endl;
    for (int i = 0; i < size; i++)
        cin >> vec[i];

    // afisare vector inainte de sortare
    cout << endl
         << "Vectorul inainte de sortare este : " << endl;
    for (int i = 0; i < size; i++)
        cout << vec[i] << " ";

    RadixSort(vec, size); // Apelare Radix Sort

    cout << endl
         << "Vectorul dupa de sortare este : " << endl;
    for (int i = 0; i < size; i++)
        cout << vec[i] << " ";

    return 0;
}