#include <iostream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <random>
#include "../include/Interface.h" 
#include "../include/Casella.h" 
#include "../include/Giocatore.h" 

/*
    autore: Leonardo Bertani 
*/

using namespace std;

void show(/**/){}
    /* 
        funzione per visualizzare il menù di gioco
        - visualizza tabellone
        - visualizza lista terreni/case/alberghi posseduti da ogni giocatore
        - visualizza l’ammontare di fiorini posseduto da tutti i giocatori
    */

void stampaTabellone(/**/)
{
    const string SPAZIO_INIZIALE = "     ";
    const string SPAZIO_TRA_NUM = "      ";
    const string SPAZIO_TRA_CASELLE = "  ";
    const string CASELLA_ANGOLARE = "   ";

    const char CASELLA_PARTENZA = 'P';
    const char CASELLA_ECONOMICA = 'E';
    const char CASELLA_STANDARD = 'S';
    const char CASELLA_LUSSO = 'L';

    const char CASA = '*';
    const char ALBERGO = '^';

    // Prima Riga
    cout<<SPAZIO_INIZIALE<<1<<SPAZIO_TRA_NUM<<2<<SPAZIO_TRA_NUM<<3<<SPAZIO_TRA_NUM<<4<<SPAZIO_TRA_NUM
    <<5<<SPAZIO_TRA_NUM<<6<<SPAZIO_TRA_NUM<<7<<SPAZIO_TRA_NUM<<8<<SPAZIO_TRA_CASELLE<<endl<<endl;
} 
    

void stampaListaPossedimenti(/**/){} 
    /*
        fuznione per stampa a schermo la lista terreni/case/alberghi posseduti da ogni giocatore
    */

void stampaLiquiditaGiocatori(/**/){}
    /*
        funzione per stampa a schermo dell’ammontare di fiorini posseduto da tutti i giocatori
    */

std::vector<Casella*> creazioneCaselle()
{
    std::vector<Casella*> caselle;

    // Casella Partenza
    caselle.push_back(new Casella(TipoCasella::P));

    //Caselle Angolari
    caselle.insert(caselle.begin()+7, new Casella(TipoCasella::_U3164));
    caselle.insert(caselle.begin()+14, new Casella(TipoCasella::_U3164));
    caselle.insert(caselle.begin()+21, new Casella(TipoCasella::_U3164));

    std::vector<int> v;

    for(int i=1; i<28; i++)
    {
        if(i!=7 && i!=14 && i!=21)
            v.push_back(i);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(v.begin(), v.end(), g);

    // Caselle Economiche
    for(int i=0; i<8; i++)
    {
        int pos = v.at(i);
        caselle.insert(caselle.begin()+pos, new Casella(TipoCasella::E));
    }

    // Caselle Standard
    for(int i=8; i<18; i++)
    {
        int pos = v.at(i);
        caselle.insert(caselle.begin()+pos, new Casella(TipoCasella::S));
    }

    // Caselle Lusso
    for(int i=18; i<24; i++)
    {
        int pos = v.at(i);
        caselle.insert(caselle.begin()+pos, new Casella(TipoCasella::L));
    }

    
    for(int i=0; i<28; i++)
    {
        // Set Posizione coordinata Y
        switch (i)
        {
        case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:     // provato con case 0 ... 7: ma mi dava errore in compilazione
            caselle[i]->setCoordY('H');
            break;
        case 8: case 27:
            caselle[i]->setCoordY('G');
            break;
        case 9: case 26:
            caselle[i]->setCoordY('F');
            break;
        case 10: case 25:
            caselle[i]->setCoordY('E');
            break;
        case 11: case 24:
            caselle[i]->setCoordY('D');
            break;
        case 12: case 23:
            caselle[i]->setCoordY('C');
            break;
        case 13: case 22:
            caselle[i]->setCoordY('B');
            break;
        default:
            caselle[i]->setCoordY('A');
            break;
        }

        // Set Posizione coordinata Y
        switch (i)
        {
        case 0: case 21: case 22: case 23: case 24: case 25: case 26: case 27:      // provato con case 0: case 21 ... 27: ma mi dava errore in compilazione
            caselle[i]->setCoordX(8);
            break;
        case 1: case 20:
            caselle[i]->setCoordX(7);
            break;
        case 2: case 19:
            caselle[i]->setCoordX(6);
            break;
        case 3: case 18:
            caselle[i]->setCoordX(5);
            break;
        case 4: case 17:
            caselle[i]->setCoordX(4);
            break;
        case 5: case 16:
            caselle[i]->setCoordX(3);
            break;
        case 6: case 15:
            caselle[i]->setCoordX(2);
            break;
        default:
            caselle[i]->setCoordX(1);
            break;
        }
    }

    return caselle;
}

int checkModalita(std::string modalita){
    if(modalita == "computer") return 0;
    else if (modalita == "human") return 1;
    return -1;
}

void benvenuto(std::string modalita){    
    std::cout << std::endl;
    for(int i = 0; i < 47; i++) { std::cout << "*"; }
    std::cout << std::endl;
    std::cout << "*";
    std::cout << " Benvenuti nel fantastico gioco del Monopoly ";
    std::cout << "*";
    std::cout << std::endl; 
    std::cout << "*";
    std::cout << " Modalità: ";
    int modalita_text_lenght = 0;
    int modalita_check = checkModalita(modalita);
    if(modalita_check != -1){
        std::cout << modalita;
        modalita_text_lenght = modalita.length();       
    } 
    else {
        std::cout << "non consentita, riprovare";
        modalita_text_lenght = 25;
    }
    for(int i = 0; i<(47-modalita_text_lenght-13); i++){ std::cout << " "; }
    std::cout << "*" << 
    std::endl; 
    for(int i = 0; i < 47; i++) { std::cout << "*"; }
    std::cout << std::endl << std::endl;  
    if(modalita_check == -1) { exit(0); }  
}




