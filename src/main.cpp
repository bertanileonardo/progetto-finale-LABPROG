#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include "../include/Interface.h" 
#include "../include/Casella.h" 
#include "../include/Giocatore.h" 
#include "../include/Stampa.h"

/*
    autore: Leonardo Bertani 
*/

int main(int argc, char** argv){

    std::string modalita = "";

    // controllo dell'esistenza dell'argomento dal terminale
    if(argc != 2) {
        std::cout << 
        std::endl << "\tConfigurazione errata degli argomenti" << 
        std::endl << "\tda riga di comando, seguire: " <<
        std::endl << 
        std::endl << "\t./a <NomeModalita>" <<
        std::endl << 
        std::endl << "\tdove al posto di <NomeModalita> inserire" <<
        std::endl << "\t- computer ( per giocare tra 4 computer )" <<
        std::endl << "\t- human ( per giocare in prima persona )" << 
        std::endl << std::endl;
        exit(1);
    }
    else{
        modalita = argv[1];
    }
    

    salvaLog("Ciaooooooooooooooooooooooooooooooooooooooo");

    // controllo dell'correttezza argomento e stampa della pagina di benvenuto
    benvenuto(modalita);

    std::vector<Giocatore*> giocatori = creazioneTurni(checkModalita(modalita));

    std::vector<Casella*> caselle = creazioneCaselle();

    /*t contatore = 0;
    do
    {
        
        contatore++;
        
    } while (contatore<kMaxTurni);*/

    giocatori[1]->setPosizioneGiocatore(1, 'A');
    giocatori[2]->setPosizioneGiocatore(8, 'A');

    giocatori[1]->casellaAngolare(caselle[8]);
    giocatori[2]->controlloCasella(caselle[16]);


    stampaTabelloneIniziale(caselle);

    stampaTabellone(caselle, giocatori);


    std::cout << std::endl << std::endl;

    return 0;
}