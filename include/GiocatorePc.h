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

    void casellaLaterale(Casella c);

    bool probabilita();

    void creazioneTurni();

    void controlloCasella(Casella c);
    
};


#endif