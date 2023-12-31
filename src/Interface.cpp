#include <iostream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include "../include/Interface.h"

/*
    Sezione codice di funzioni utili al caso

    autore: Leonardo Bertani 
*/

int generaNumeroCasuale(){
    return rand() % 6 + 1; // correzine dovuta al fatto che rand() restituisce un numero 0 a i-1
}

int lancioDadi(){
    int dado1 = generaNumeroCasuale();
    int dado2 = generaNumeroCasuale();
    return dado1 + dado2; // come da richiesta restituisco la somma delle uscite dei 2 dadi
}

void show(/**/){}
    /* 
        funzione per visualizzare il menù di gioco
        - visualizza tabellone
        - visualizza lista terreni/case/alberghi posseduti da ogni giocatore
        - visualizza l’ammontare di fiorini posseduto da tutti i giocatori
    */

void stampaTabellone(/**/){} 
    /*
        fuznione per stampa a schermo del tabellone di gioco
    */

void stampaListaPossedimenti(/**/){} 
    /*
        fuznione per stampa a schermo la lista terreni/case/alberghi posseduti da ogni giocatore
    */

void stampaLiquiditaGiocatori(/**/){}
    /*
        funzione per stampa a schermo dell’ammontare di fiorini posseduto da tutti i giocatori
    */

char ottieniInputChar(std::string testo){
    char input;
    std::cout << testo << " : ";
    std::cin >> input;
    return input;
}

std::string ottieniInputString(std::string testo){
    std::string input;
    std::cout << testo << " : ";
    std::cin >> input;
    return input;
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




