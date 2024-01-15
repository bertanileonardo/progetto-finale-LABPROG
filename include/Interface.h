#ifndef Interface_H
#define Interface_H

/*
    autore: Leonardo Bertani 
*/

#include "Casella.h"
#include "Giocatore.h"
#include <string>

// Numero giocatori di default
constexpr static int kDefaultNumeroGiocatori = 4;

// Ammontare di fiorini ritirato passando dalla Partenza
constexpr static int kFioriniPartenza = 20;

// Numero di turni masssimi per partita
constexpr static int kMaxTurni = 5000;

void show(std::vector<Casella*> caselle, std::vector <Giocatore*> giocatori);
    /* 
        funzione per visualizzare il menù di gioco
        - visualizza tabellone
        - visualizza lista terreni/case/alberghi posseduti da ogni giocatore
        - visualizza l’ammontare di fiorini posseduto da tutti i giocatori
    */



void stampaTabellone(std::vector<Casella*> caselle, std::vector <Giocatore*> giocatori); 
    /*
        funzione per stampa a schermo del tabellone di gioco
    */

void stampaTabelloneIniziale(std::vector<Casella*> caselle);
    /*
        stampa a schermo del tabellone di gioco vuoto
    */

void stampaListaPossedimenti(std::vector<Casella*> caselle, std::vector<Giocatore*> giocatori); 
    /*
        funzione per stampa a schermo la lista terreni/case/alberghi posseduti da ogni giocatore
    */

void stampaLiquiditaGiocatori(std::vector<Giocatore*> giocatori);
    /*
        funzione per stampa a schermo dell’ammontare di fiorini posseduto da tutti i giocatori
    */

std::vector<Casella*> creazioneCaselle();


int checkModalita(std::string);
    /*
        funzione restituire -1 se modalità non prevista, 0 se computer, 1 se human
    */
    
void benvenuto(std::string);
    /*
        funzione restituire il messaggio di benvenuto
    */

std::string toStringCasella(Casella* c, std::vector<Giocatore*> giocatori);
std::string toStringCasellaIniziale(Casella* c);

int verificaVincitore(std::vector<Giocatore*> giocatori);
    /*
        Verifica se tra i giocatori vi è un vincitore
    */
int stabilisciVincitore(std::vector<Giocatore*> giocatori);
    /*
        Stabilisce se, raggiunto il numero max di turni
        c'è un vincitore
    */

#endif //Interface_H