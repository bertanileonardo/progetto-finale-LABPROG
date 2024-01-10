#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include "../include/Interface.h" 
#include "../include/Casella.h" 
#include "../include/Giocatore.h" 
#include "../include/GiocatorePc.h" 
#include "../include/GiocatorePcHuman.h" 

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

    // controllo dell'correttezza argomento e stampa della pagina di benvenuto
    benvenuto(modalita);

    vector<Casella*> caselle;


    if (checkModalita(modalita) == 0 ){
        std::cout << "ss";
    }
    else{
        std::cout << "s";
    }
    
    std::cout << std::endl << std::endl;

    return 0;
}