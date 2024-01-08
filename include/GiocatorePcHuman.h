/*
    autore: Vanon Lorenzo
*/

#ifndef GIOCATOREPCHUMAN_H
#define GIOCATOREPCHUMAN_H

#include "GiocatorePc.h"

class GiocatorePcHuman : public GiocatorePc
{

public:

    // COSTRUTTORE
    GiocatorePcHuman(int id, bool mode);

    // Get se Giocatore Pc o Human
    bool getModalitàGioco();
    
    void CasellaLaterale(CasellaAcquistabile c);


private:
    // Giocatore Pc (0) o Human(1)
    bool modalità_di_gioco;

};

#endif