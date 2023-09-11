#include "Iterator.h"
#include "LO.h"

//Teta(1)
Iterator::Iterator(const LO& lo) : lista(lo){
    /* de adaugat */
    prim();
}

//Teta(1)
void Iterator::prim() {
    /* de adaugat */
    curent = lista.prim;
}

//Teta(1)
void Iterator::urmator(){
    /* de adaugat */
    if(!valid())
        throw std::runtime_error(std::string("Invalid iterator!"));
    curent = lista.urm[curent];
}

//Teta(1)
bool Iterator::valid() const{
    /* de adaugat */
    return curent >= 0 && curent != NULL_TELEMENT;
}

//Teta(1)
TElement Iterator::element() const{
    /* de adaugat */
    if(!valid())
        throw std::runtime_error(std::string("Invalid iterator!"));
    return lista.e[curent];
}


