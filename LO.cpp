#include "Iterator.h"
#include "LO.h"

#include <iostream>
using namespace std;

#include <exception>

//Teta(cap)
LO::LO(Relatie r): r{r}{
    /* de adaugat */
    prim = NULL_TELEMENT;

    urm[0] = 1;
    ant[0] = NULL_TELEMENT;
    for(int i=1; i<cap-1; i++) {
        urm[i] = i + 1;
        ant[i] = i - 1;
    }
    urm[cap-1] = NULL_TELEMENT;
    ant[cap-1] = cap-2;

    primliber = 0;
    cap = 10;
    size = 0;
}

// returnare dimensiune
//Teta(1)
int LO::dim() const {
    /* de adaugat */
    return size;
}

// verifica daca LO e vida
//Teta(1)
bool LO::vida() const {
    /* de adaugat */
    return size==0;
}

// returnare element
//arunca exceptie daca i nu e valid
//O(i)
TElement LO::element(int i) const{
    /* de adaugat */
    if(i<0 || i>=size)
        throw std::runtime_error{std::string("i nu e valid!")};
    int k = prim;
    int poz = 0;
    while(k!= NULL_TELEMENT && poz != i){
        k = urm[k];
        poz++;
    }
    return e[k];
}

// sterge element de pe o pozitie i si returneaza elementul sters
//arunca exceptie daca i nu e valid
//O(size)
TElement LO::sterge(int i) {
    /* de adaugat */
    if(i<0 || i>=size)
        throw std::runtime_error{std::string("i nu e valid!")};

    int k = prim;
    int poz = 0;
    while(k!= NULL_TELEMENT && poz != i){
        k = urm[k];
        poz++;
    }
    TElement te = e[k];

    if(k == prim){
        prim = urm[prim];
        ant[prim] = NULL_TELEMENT;
    }
    else if(urm[k] == NULL_TELEMENT){
        urm[ant[k]] = urm[k];
    }
    else{
        urm[ant[k]] = urm[k];
        ant[urm[k]] = ant[k];
    }
    dealoca(k);
    size--;

    return te;
}

// cauta element si returneaza prima pozitie pe care apare (sau -1)
//O(size)
int LO::cauta(TElement e) const {
    int k = prim;
    int poz=0;

    while(k!= NULL_TELEMENT && this->e[k]!=e) {
        k = urm[k];
        poz++;
    }
    if(this->e[k] == e)
        return poz;
    return -1;
}

// adaugare element in LO
// O(size)
void LO::adauga(TElement e) {
    /* de adaugat */
    int i = creeaza_nod(e);

    if(prim == NULL_TELEMENT) {
        prim = i;
        size++;
        return;
    }

    int k = prim;
    int ante;
    while(k!=NULL_TELEMENT && !r(this->e[i], this->e[k])){
        ante = k;
        k = urm[k];
    }

    if(k == prim) {
        ant[prim] = i;
        urm[i] = prim;
        ant[i] = NULL_TELEMENT;
        prim = i;
        size++;
        return;
    }

    if(k==NULL_TELEMENT){
        urm[ante] = i;
        ant[i] = ante;
        size++;
        return;
    }

    urm[i] = k;
    ant[i] = ant[k];
    urm[ant[k]] = i;
    ant[k] = i;
    size++;
}

// returnare iterator
//Teta(1)
Iterator LO::iterator(){
    return Iterator(*this);
}


//destructor
LO::~LO() {
    /* de adaugat */
}

//Teta(1)
int LO::aloca() {
    int i = primliber;
    primliber = urm[primliber];
    return i;
}

//Teta(1)
void LO::dealoca(int i) {
    urm[i] = primliber;
    ant[i] = NULL_TELEMENT;
    primliber = i;
}

//Teta(1) amortizat
int LO::creeaza_nod(TElement e) {
    if(primliber == NULL_TELEMENT)
        redim();

    int i = aloca();
    this->e[i] = e;
    urm[i] = NULL_TELEMENT;
    ant[i] = NULL_TELEMENT;

    return i;
}

//Teta(1) amortizat
void LO::redim() {
     TElement* aux_e = new TElement[cap*2];
     int* aux_urm = new int[cap*2];
     int* aux_ant = new int[cap*2];

     for(int i=0; i<cap; i++){
         aux_e[i] = e[i];
         aux_urm[i] = urm[i];
         aux_ant[i] = ant[i];
     }
     delete[] e;
     delete[] urm;
     delete[] ant;

     e = aux_e;
     urm = aux_urm;
     ant = aux_ant;

     primliber = cap;
     cap = cap*2;

     urm[primliber] = primliber+1;
     ant[primliber] = NULL_TELEMENT;
     for(int i=primliber+1; i<cap-1; i++) {
         urm[i] = i + 1;
         ant[i] = i - 1;
     }
     urm[cap-1] = NULL_TELEMENT;
     ant[cap-1] = cap-2;
}
//O(k*size)
int LO::eliminaDinKInK(int k) {
    if(k <= 0)
        throw std::runtime_error(std::string("exceptie k negativ"));

    if(size < k)
        return 0;

    int p=0;
    int nr=0;
    while(p<size){
        sterge(p);
        nr++;
        p=p+k-1;
    }
    return nr;
}
