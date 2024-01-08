/*
    autore: Vanon Lorenzo
*/

#ifndef GIOCATORE_H
#define GIOCATORE_H

#include "Interface.h"
#include "Casella.h"

/*
    Classe Giocatore
    - Definisce il giocatore in modo generale (caratteristiche comuni per pc o human)
*/

class Giocatore
{

protected:

// VARIABILI OGGETTO
    // Budget del giocatore
    int budget_giocatore_;
    // Posizione del turno di gioco (id)
    int id_giocatore_;
    // In gara/eliminato
    bool stato_corrente_giocatore_;
    // Budget iniziale
    constexpr static int kDefaultBudget = 100;
    // Stato di default (in gara)
    constexpr static bool kDefaultStato = 1;

public:

    // Funzioni getter/setter
    int getBudget();
    void setBudget(int b);
    int getId();
    void setId(int id);
    bool getStato();
    void setStato(bool s);

    // CLASSI ECCEZIONI
    class InvalidIdException{};
    
    //COSTRUTTORE (non esiste costruttore di default in quanto non ha senso. --> I giocatori vengono creati dopo aver stabilito la modalità e l'ordine di turno)
    Giocatore(int id);
    // COSTRUTTORE di copia disabilitato
    Giocatore(const Giocatore& g) = delete;
    // Operatore di copia disabilitato
    Giocatore& operator=(const Giocatore& g) = delete;

    // Definisce l'ordine di turno dei giocatori
    void CreazioneTurni();

    // Controlla il tipo di casella e chiama le funzioni apposite in base ad esso
    void ControlloCasella(CasellaAcquistabile c);
    // Funzioni basate sulla casella dove capita il giocatore
    // Casella Angolare --> non fa niente
    void CasellaAngolare();
    // Casella Partenza --> riscatta 20 fiorini
    void CasellaPartenza();
    // Casella Laterale --> varie opzioni, virtuale pura dal momento che abbiamo diversi comportamenti tra Pc e Human
    virtual void CasellaLaterale(CasellaAcquistabile c) = 0;

};

#endif