/*
    autore: Vanon Lorenzo
*/

#ifndef GIOCATOREPC_H
#define GIOCATOREPC_H

#include "Giocatore.h"

class GiocatorePc : public Giocatore
{
    
public:
    // COSTRUTTORE
    GiocatorePc(int id);

    void CasellaLaterale(Casella c);

    bool Probabilita();

    void CreazioneTurni();

    void ControlloCasella(Casella c);
    
};


#endif