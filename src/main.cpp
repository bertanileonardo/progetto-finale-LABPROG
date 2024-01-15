#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <chrono>
#include "../include/Interface.h" 
#include "../include/Casella.h" 
#include "../include/Giocatore.h" 
#include "../include/Stampa.h"

/*
    autori: Leonardo Bertani, Lorenzo Vanon, Leonardo Gasparoni 
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

    std::vector<Giocatore*> giocatori = creazioneTurni(checkModalita(modalita));

    std::vector<Casella*> caselle = creazioneCaselle();

    stampaTabelloneIniziale(caselle);

    int contatoreTurni = 0;
    do
    {
        for(int i=0; i<kDefaultNumeroGiocatori; i++)
        {
            if(giocatori[i]->getModalitaGioco() == 1)
            {
                std::string input;
                do{
                    std::cout<<std::endl<<"Digita 'show' per vedere le opzioni di visualizzazione, digita 'N' per andare avanti"<<std::endl;
                    std::cin>>input;
                } while(input!="show" && input!="N" && input!= "n");

                if(input=="show")
                {
                    show(caselle, giocatori);
                }
            }
            int lancio = lancioDadi();
            std::string sLog = "ha tirato i dadi ottenenedo un valor di "+std::to_string(lancio);
            salvaLog(binder(giocatori[i]->getId(), sLog));
            //int nuovaPos = (giocatori[i]->getIndicePosizione()+lancioDadi())%28;
            int nuovaPos = 10;
            if(nuovaPos<giocatori[i]->getIndicePosizione())
                giocatori[i]->casellaPartenza();
            giocatori[i]->controlloCasella(caselle[nuovaPos]);
            giocatori[i]->setIndicePosizione(nuovaPos);
        }

        contatoreTurni++;
        
    } while (contatoreTurni<kMaxTurni && verificaVincitore(giocatori) == -1);

    if(verificaVincitore(giocatori) == -1)
        stabilisciVincitore(giocatori);


    stampaTabelloneIniziale(caselle);

    stampaTabellone(caselle, giocatori);


    std::cout << std::endl << std::endl;

    return 0;
}