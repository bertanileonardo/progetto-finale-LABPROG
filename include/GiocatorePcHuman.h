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
    bool getModalitaGioco();
    
    void CasellaLaterale(Casella c);

    void CreazioneTurni();

    void ControlloCasella(Casella c);


private:
    // Giocatore Pc (0) o Human(1)
    bool modalita_di_gioco;

};

#endif