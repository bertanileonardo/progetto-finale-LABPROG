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

    virtual void CasellaLaterale(CasellaAcquistabile c);

    bool Probabilità();
    
};


#endif