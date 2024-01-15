/*
    autore: Vanon Lorenzo
*/

#ifndef GIOCATORE_H
#define GIOCATORE_H

#include <vector>
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
    // Tipo di giocatore PC(0), Human (1)
    bool modalita_di_gioco_;
    // Coordinate attuali giocatore
    int coordXgiocatore;
    char coordYGiocatore;

    //COSTANTI
    // Budget iniziale
    constexpr static int kDefaultBudget = 100;
    // Stato di default (in gara)
    constexpr static bool kDefaultStato = 1;
    // Numero di giocatori di default
    
    
public:

    // Funzioni getter/setter
    int getBudget();
    void setBudget(int b);
    int getId();
    void setId(int id);
    bool getStato();
    void setStato(bool s);
    bool getModalitaGioco();
    int getCoordXGiocatore();
    char getCoordYGiocatore();
    void setPosizioneGiocatore(int x, char y);


    void controlloCasella(Casella* c);
    /*
        effettua il controllo sul tipo della casella e chiama le funzioni
        dedicate in base ad esso
    */

    void casellaLaterale(Casella* c);
    /*
        gestisce il caso in cui un giocatore capita su una casella laterale 
        (economica, standard, lusso)
    */

    void casellaPartenza();
    /*
        gestisce il caso in cui un giocatore capita sulla casella di Partenza
        (ritira 20 fiorini)
    */

   void casellaAngolare(Casella* c);
   /*
        gestisce il caso in cui un giocatore capita su una casella Angolare
        (nulla ma salva nel file di log)
   */


    // CLASSI ECCEZIONI
    class InvalidIdException{};
    
    //COSTRUTTORE (non esiste costruttore di default in quanto non ha senso. --> I giocatori vengono creati dopo aver stabilito la modalità e l'ordine di turno)
    Giocatore(int id, bool mode);
    // COSTRUTTORE di copia disabilitato
    Giocatore(const Giocatore& g) = delete;
    // Operatore di copia disabilitato
    Giocatore& operator=(const Giocatore& g) = delete;
    // Distuttore
    //~Giocatore();
};
    

    
struct Record
{
    Giocatore* g;
    int id;

    Record()
        : g{ nullptr }, id{ 0 }{}

    Record(Giocatore* g, int id)
        : g{ g }, id{ id }{}

    Record& operator=(const Record& r);
    Record& operator=(Record&& r);

};

int generaNumeroCasuale(); 
    /* 
        genera numero random nell'intervallo [1,6]
    */


bool probabilita();
/*
        ritorna 1 con la probabilità del 25% (1 su 4) 
*/

int lancioDadi(); 
    /* 
        funzione che restituisce il numero di posizioni di cui spostarsi, 
        ovvero la somma del risultato del lancio di 2 dadi
    */

int findMaxPos(Record* v[], int from, int to);
/*
    trova la posizione dell'oggetto Record con il valore id più alto
    all'interno di un array di struct Record
*/

std::vector<Giocatore*> creazioneTurni(bool modalita);
    /*
        determina l'ordine di turno dei giocatori in base al valore che ogni
        giocatore ottiene con un lancio dei dadi (in ordine decrescente)
    */

#endif