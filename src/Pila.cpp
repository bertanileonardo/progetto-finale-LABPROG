#include "../include/Pila.h"

Pila::Pila()
    : v{ new record[Pila::kDefaultNumeroGiocatori] },
      testa{ 0 }, lunghezza{ Pila::kDefaultNumeroGiocatori } {}
      

record& record::operator=(const record& r)
{
    delete[] g;
    g = r.g;
    id = r.id;
    return *this;
}

record& record::operator=(record&& r)
{
    delete[] g;
    g = r.g;
    id = r.id;
    r.g = nullptr;
    r.id = 0;
    return *this;
}

void Pila::push(record *r)
{
    if(Pila::testa == Pila::lunghezza)
    {
        throw FullStackException();
    }
    Pila::v[Pila::testa++] = *r;
}

record& Pila::pop()
{
    return Pila::v[Pila::testa--];
}

record& Pila::top()
{
    return Pila::v[Pila::testa];
}

int Pila::findMaxPos(int from, int to)
{
    int pos = from;
    for(int i=pos+1; i<to; i++)
    {
        if( v[i].id >= v[pos].id )
            pos = i;
    }
    return pos;
}