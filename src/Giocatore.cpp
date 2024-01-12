/*
    autore: Vanon Lorenzo
*/

#include "../include/Giocatore.h"

Giocatore::Giocatore(int id)
    : budget_giocatore_{ kDefaultBudget }, id_giocatore_{ id }, stato_corrente_giocatore_{ kDefaultStato }
    {
        if(!( id>0 && id<5 )) // sostituire con delle costanti casomai
            throw InvalidIdException();
    }

int Giocatore::getBudget()
{   return Giocatore::budget_giocatore_; }

void Giocatore::setBudget(int b)
{   Giocatore::budget_giocatore_ = b; }

int Giocatore::getId()
{   return Giocatore::id_giocatore_; }

void Giocatore::setId(int id)
{   Giocatore::id_giocatore_ = id; }

bool Giocatore::getStato()
{   return Giocatore::stato_corrente_giocatore_; }

void Giocatore::setStato(bool s)
{   Giocatore::stato_corrente_giocatore_ = s; }

int Giocatore::generaNumeroCasuale(){
    return rand() % 6 + 1; // correzione dovuta al fatto che rand() restituisce un numero da 0 a i-1
}

int Giocatore::lancioDadi(){
    int dado1 = generaNumeroCasuale();
    int dado2 = generaNumeroCasuale();
    return dado1 + dado2; // come da richiesta restituisco la somma delle uscite dei 2 dadi
}

void Giocatore::CasellaAngolare()
{}
void Giocatore::CasellaPartenza()
{
    setBudget(Giocatore::budget_giocatore_ + 20);
}

/*
void Giocatore::ControlloCasella(Casella c)
{
    if( c.getTipo() == TipoCasella::_U3164 ) 
        Giocatore::CasellaAngolare();
    if( c.getTipo() == TipoCasella::P )
        Giocatore::CasellaPartenza();
    else
        Giocatore::CasellaLaterale(c);
}
*/