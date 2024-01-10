#ifndef PILA_H
#define PILA_H

#include "Giocatore.h"

struct record
{
    Giocatore* g;
    int id;

    record()
        : g{ nullptr }, id{ 0 }{}

    record(Giocatore* g, int id)
        : g{ g }, id{ id }{}

    record& operator=(const record& r);
    record& operator=(record&& r);

};

class Pila
{
protected:
    int testa;
    int lunghezza;

public:

    record* v;

    class FullStackException{};

    Pila();

    // ~Pila();

    // Numero default di giocatori
    constexpr static int kDefaultNumeroGiocatori = 4;
    void push(record *r);
    record& pop();
    record& top();

    int findMaxPos(int from, int to);

};


/*
template <typename G>
class Pila
{

protected:
    constexpr static int kDefaultLunghezza = 4;
    G[] g;
    int testa;
    int lunghezza;

public:
    Pila();

    void push(Pila& p, Giocatore& g);
    Giocatore pop(Pila& p);
    Giocatore top(Pila& p);
};*/
#endif