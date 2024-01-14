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

void stampaTabellone(std::vector<Casella*> caselle, std::vector <Giocatore*> giocatori)
{
    const string SPAZIO_INIZIALE = "     ";
    const string SPAZIO_TRA_NUM = "      ";
    const string SPAZIO_TRA_CASELLE = "  ";
    const string CASELLA_VUOTA = "   ";

    // Prima Riga
    cout<<SPAZIO_INIZIALE<<1<<SPAZIO_TRA_NUM<<2<<SPAZIO_TRA_NUM<<3<<SPAZIO_TRA_NUM<<4<<SPAZIO_TRA_NUM
    <<5<<SPAZIO_TRA_NUM<<6<<SPAZIO_TRA_NUM<<7<<SPAZIO_TRA_NUM<<8<<SPAZIO_TRA_CASELLE<<endl<<endl;

    // Seconda Riga
    cout<<"A"<<SPAZIO_TRA_CASELLE;
    for(int i=14; i<=21; i++)
    {
        cout<<SPAZIO_TRA_CASELLE<<toStringCasella(caselle[i], giocatori);
    }
    cout<<endl;

    // Dalla terza alla settima riga

    for(int i=13, j=22, h=66; i>=8, j<=27, h<=71; i--, j++, h++)
    {
        cout<<(char)h<<SPAZIO_TRA_CASELLE<<toStringCasella(caselle[i], giocatori);
        for(int w=0; w<7; w++)
        {
            cout<<SPAZIO_TRA_CASELLE<<CASELLA_VUOTA;
        }
        cout<<SPAZIO_TRA_CASELLE<<toStringCasella(caselle[j], giocatori);
    }

    // Ottava (ultima) riga
    cout<<"H"<<SPAZIO_TRA_CASELLE;
    for(int i=7; i>=0; i--)
    {
        cout<<SPAZIO_TRA_CASELLE<<toStringCasella(caselle[i], giocatori);
    }
    cout<<endl;
}

void stampaTabelloneIniziale(std::vector<Casella*> caselle)
{
    const string SPAZIO_INIZIALE = "     ";
    const string SPAZIO_TRA_NUM = "      ";
    const string SPAZIO_TRA_CASELLE = "  ";
    const string CASELLA_VUOTA = "   ";

    // Prima Riga
    cout<<SPAZIO_INIZIALE<<1<<SPAZIO_TRA_NUM<<2<<SPAZIO_TRA_NUM<<3<<SPAZIO_TRA_NUM<<4<<SPAZIO_TRA_NUM
    <<5<<SPAZIO_TRA_NUM<<6<<SPAZIO_TRA_NUM<<7<<SPAZIO_TRA_NUM<<8<<SPAZIO_TRA_CASELLE<<endl<<endl;

    // Seconda Riga
    cout<<"A"<<SPAZIO_TRA_CASELLE;
    for(int i=14; i<=21; i++)
    {
        cout<<SPAZIO_TRA_CASELLE<<toStringCasellaIniziale(caselle[i]);
    }
    cout<<endl;

    // Dalla terza alla settima riga

    for(int i=13, j=22, h=66; i>=8, j<=27, h<=71; i--, j++, h++)
    {
        cout<<(char)h<<"\t\t"<<toStringCasellaIniziale(caselle[i]);
        for(int w=0; w<7; w++)
        {
            cout<<SPAZIO_TRA_CASELLE<<CASELLA_VUOTA;
        }
        cout<<SPAZIO_TRA_CASELLE<<toStringCasellaIniziale(caselle[j]);
    }

    // Ottava (ultima) riga
    cout<<"H\t";
    for(int i=7; i>=0; i--)
    {
        cout<<SPAZIO_TRA_CASELLE<<toStringCasellaIniziale(caselle[i]);
    }
    cout<<endl;
}
    

void stampaListaPossedimenti(std::vector<Casella*> caselle, std::vector<Giocatore*> giocatori){
    int i=0;
    for (Giocatore* giocatore : giocatori){
        i++;
        std::cout << "\tGiocatore  " << i << " : ";
        int j=0;
        for (Casella* casella : caselle){
            if(casella -> getProprietario() == i){
                j++;
                if(j>1) std::cout << ", ";
                std::cout << casella -> getCoordX() << casella -> getCoordY();
            }
        }
    }
} 

void stampaLiquiditaGiocatori(std::vector<Giocatore*> giocatori){
    std::cout << "\tLiquidit\00E0 giocatori: " << std::endl << std::endl;
    int i=0;
    for (Giocatore* giocatore : giocatori){
        i++;
        std::cout << "\tGiocatore  " << i << " : " << giocatore -> getBudget() << "\0192" << std::endl;
        }
}

std::vector<Casella*> creazioneCaselle()
{
    int len = 28;
    std::vector<Casella*> caselle(len);

    for(int i=0; i<len; i++)
    {
        caselle[i] = new Casella(TipoCasella::_U3164);
    }
    // Casella Partenza
    caselle[0] = new Casella(TipoCasella::P);

    //Caselle Angolari
    caselle[7] = new Casella(TipoCasella::_U3164);
    caselle[14] = new Casella(TipoCasella::_U3164);
    caselle[21] = new Casella(TipoCasella::_U3164);

    std::vector<int> v(len);
    v[0] = -1;
    for(int i=1; i<len; i++)
    {
        if(i==7 || i==14 || i==21)
            v[i] = 0;
        else 
            v[i] = i;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(v.begin(), v.end(), g);

    // Caselle Economiche
    for(int i=1; i<7; i++)
    {
        if(i!=7)
        {
            int pos = v.at(i);
            caselle[pos] = new Casella(TipoCasella::E);
        }
    }

    // Caselle Standard
    for(int i=10; i<21; i++)
    {
        if(i!=14)
        {
            int pos = v.at(i);
            caselle[pos] = new Casella(TipoCasella::S);
        }
    }

    // Caselle Lusso
    for(int i=22; i<28; i++)
    {
        int pos = v.at(i);
        caselle[pos] = new Casella(TipoCasella::L);
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

std::string toStringCasella(Casella* c, vector<Giocatore*> giocatori)
{
    std::string s = "|"+c->getTipoChar();
    if(c->hasCasa())
        s+="*";
    else if(c->hasAlbergo())
        s+="^";
    else
        s+=" ";
  
    for(int i=0; i<kDefaultNumeroGiocatori; i++)
    {
        if(c->getCoordX() == giocatori[i]->getCoordXGiocatore() && c->getCoordY() == giocatori[i]->getCoordYGiocatore() )
            s+=giocatori[i]->getId();
        else
        s+=" ";
    }
    s+="|";
    return s;
}

std::string toStringCasellaIniziale(Casella* c)
{
    std::string s = "|"+c->getTipoChar();
    s+="|";
    return s;
}