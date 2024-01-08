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

void Giocatore::CasellaAngolare()
{}
void Giocatore::CasellaPartenza()
{
    setBudget(Giocatore::budget_giocatore_ + 20);
}

void Giocatore::ControlloCasella(CasellaAcquistabile c)
{
    if( c.getTipo() == TipoCasella::ㅤ )
        Giocatore::CasellaAngolare();
    if( c.getTipo() == TipoCasella::P )
        Giocatore::CasellaPartenza();
    else
        Giocatore::CasellaLaterale(c);
}




void Giocatore::CreazioneTurni()
{
    
}
