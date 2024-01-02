/*
    Sezione codice di funzioni utili al caso

    autore: Leonardo Bertani 
*/

// funzioni utili nel gioco

int generaNumeroCasuale(); 
    /* 
        genera numero random nell'intervallo [1,6]
    */

int lancioDadi(); 
    /* 
        funzione che restituisce il numero di posizioni di cui spostarsi, 
       ovvero la somma del risultato del lancio di 2 dadi
    */


// gioco 

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

char ottieniInputChar(std::string);
    /*
        funzione restituire un input richiesto, come char, se di un solo carattere
    */

std::string ottieniInputString(std::string);
    /*
        funzione restituire un input richiesto, come stringa
    */

int checkModalita(std::string);
    /*
        funzione restituire -1 se modalità non prevista, 0 se computer, 1 se human
    */
    
void benvenuto(std::string);
    /*
        funzione restituire il messaggio di benvenuto
    */

