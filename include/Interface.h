#ifndef Interface_H
#define Interface_H

/*
    autore: Leonardo Bertani 
*/

void show(/**/);
    /* 
        funzione per visualizzare il menù di gioco
        - visualizza tabellone
        - visualizza lista terreni/case/alberghi posseduti da ogni giocatore
        - visualizza l’ammontare di fiorini posseduto da tutti i giocatori
    */

void stampaTabellone(/**/); 
    /*
        fuznione per stampa a schermo del tabellone di gioco
    */

void stampaListaPossedimenti(/**/); 
    /*
        fuznione per stampa a schermo la lista terreni/case/alberghi posseduti da ogni giocatore
    */

void stampaLiquiditaGiocatori(/**/);
    /*
        funzione per stampa a schermo dell’ammontare di fiorini posseduto da tutti i giocatori
    */

int checkModalita(std::string);
    /*
        funzione restituire -1 se modalità non prevista, 0 se computer, 1 se human
    */
    
void benvenuto(std::string);
    /*
        funzione restituire il messaggio di benvenuto
    */

#endif //Interface_H