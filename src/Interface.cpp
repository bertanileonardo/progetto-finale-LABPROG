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

void show(std::vector<Casella*> caselle, std::vector <Giocatore*> giocatori){
    
    std::cout << "Inserire il numero di riferimento delle informazioni richieste:" << 
    std::endl << "1 - Tabellone" <<
    std::endl << "2 - Lista terreni/case/alberghi posseduti" <<
    std::endl << "3 - Liquidita'" <<
    std::endl << std::endl << "> ";
    std::string input;
    std::cin >> input;
    if (input == "1"){
        stampaTabellone(caselle, giocatori);
    }
    else if (input == "2"){
        stampaListaPossedimenti(caselle, giocatori);

    }
    else if (input == "3"){
        stampaLiquiditaGiocatori(giocatori);
    }
    else {
        std::cout << "Input errato, si prega di riprovare!" << std::endl;
        show(caselle,giocatori);
    }

}

void stampaTabellone(std::vector<Casella*> caselle, std::vector <Giocatore*> giocatori)
{
    const string SPAZIO_INIZIALE = "       "; // 7 caratteri vuoti
    const string SPAZIO_TRA_NUM = "        "; // 8 caratteri vuoti
    const string SPAZIO_TRA_CASELLE = "    "; // 4 caratteri vuoti
    const string CASELLA_VUOTA = "     "; // 5 caratteri vuoti


    cout<<endl<<endl;
    // Prima Riga
    cout<<SPAZIO_INIZIALE<<1<<SPAZIO_TRA_NUM<<2<<SPAZIO_TRA_NUM<<3<<SPAZIO_TRA_NUM<<4<<SPAZIO_TRA_NUM
    <<5<<SPAZIO_TRA_NUM<<6<<SPAZIO_TRA_NUM<<7<<SPAZIO_TRA_NUM<<8<<SPAZIO_TRA_CASELLE<<endl<<endl;

    // Seconda Riga
    cout<<"A";
    for(int i=14; i<=21; i++)
    {
        cout<<SPAZIO_TRA_CASELLE<<toStringCasella(caselle[i], giocatori);
    }
    cout<<endl;

    // Dalla terza alla settima riga

    for(int i=13, j=22, h=66; i>=8, j<=27, h<=71; i--, j++, h++)
    {
        cout<<endl<<(char)h<<SPAZIO_TRA_CASELLE<<toStringCasella(caselle[i], giocatori);
        for(int w=0; w<6; w++)
        {
            cout<<SPAZIO_TRA_CASELLE<<CASELLA_VUOTA;
        }
        cout<<SPAZIO_TRA_CASELLE<<toStringCasella(caselle[j], giocatori)<<endl;
    }

    // Ottava (ultima) riga
    cout<<endl<<"H";
    for(int i=7; i>=0; i--)
    {
        cout<<SPAZIO_TRA_CASELLE<<toStringCasella(caselle[i], giocatori);
    }
    cout<<endl;
}

void stampaTabelloneIniziale(std::vector<Casella*> caselle)
{
    const string SPAZIO_TRA_NUM = "      "; // 6 caratteri vuoti
    const string SPAZIO_TRA_CASELLE = "    "; // 4 caratteri vuoti
    const string CASELLA_VUOTA = "   "; // 3 caratteri vuoti

    cout<<endl<<endl;

    // Prima Riga
    cout<<SPAZIO_TRA_NUM<<1<<SPAZIO_TRA_NUM<<2<<SPAZIO_TRA_NUM<<3<<SPAZIO_TRA_NUM<<4<<SPAZIO_TRA_NUM
    <<5<<SPAZIO_TRA_NUM<<6<<SPAZIO_TRA_NUM<<7<<SPAZIO_TRA_NUM<<8<<SPAZIO_TRA_CASELLE<<endl<<endl;

    

    // Seconda Riga
    cout<<"A";
    for(int i=14; i<=21; i++)
    {
        cout<<SPAZIO_TRA_CASELLE<<toStringCasellaIniziale(caselle[i]);
    }
    cout<<endl;

    // Dalla terza alla settima riga

    for(int i=13, j=22, h=66; i>=8, j<=27, h<=71; i--, j++, h++)
    {
        cout<<endl<<(char)h<<SPAZIO_TRA_CASELLE<<toStringCasellaIniziale(caselle[i]);
        for(int w=0; w<6; w++)
        {
            cout<<SPAZIO_TRA_CASELLE<<CASELLA_VUOTA;
        }
        cout<<SPAZIO_TRA_CASELLE<<toStringCasellaIniziale(caselle[j])<<endl;
    }

    // Ottava (ultima) riga
    cout<<endl<<"H";
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
        // Inizializzo tutte le caselle con Tipo Angolare, dividendole tra economiche, standard e lusso rimarrano le 3+1 (partenzas) angolari di regola
        caselle[i] = new Casella(TipoCasella::_U3164);
    }
    // Casella Partenza
    caselle[0] = new Casella(TipoCasella::P);

    std::vector<int> v(len);
    v[0] = 0;
    for(int i=1; i<len; i++)
    {
        v[i] = i;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(v.begin(), v.end(), g);


    int counterEconom = 1;
    int counterStandard = 1;
    int counterLusso = 1;
    int i = 0;

    // Caselle Economiche
    while( counterEconom<9 )
    {
        if( !(v[i] == 0 || v[i] == 7 || v[i] == 14 || v[i] == 21) )
        {
            int pos = v[i];
            caselle[pos] = new Casella(TipoCasella::E);
            counterEconom++;
            i++;
        }
        else
            i++;
    }

    // Caselle Standard
    while( counterStandard<11 )
    {
        if( !(v[i] == 0 || v[i] == 7 || v[i] == 14 || v[i] == 21) )
        {
            int pos = v[i];
            caselle[pos] = new Casella(TipoCasella::S);
            counterStandard++;
            i++;
        }
        else
            i++;
    }

    // Caselle Lusso
    while( counterLusso<7 )
    {
        if( !(v[i] == 0 || v[i] == 7 || v[i] == 14 || v[i] == 21) )
        {
            int pos = v[i];
            caselle[pos] = new Casella(TipoCasella::L);
            counterLusso++;
            i++;
        }
        else
            i++;
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
    int counter = 0;
    std::string s = "|"+std::string(1,c->getTipoChar());
    if(c->hasCasa())
        s+="*";
    else if(c->hasAlbergo())
        s+="^";
    else
        s+=" ";
  
    for(int i=0; i<kDefaultNumeroGiocatori; i++)
    {
        if(c->getCoordX() == giocatori[i]->getCoordXGiocatore() && c->getCoordY() == giocatori[i]->getCoordYGiocatore() )
        {
            char num;
            switch(giocatori[i]->getId())
            {
            case 1:
                num = '1';
                break;
            case 2:
                num = '2';
                break;
            case 3:
                num = '3';
                break;
            case 4:
                num = '4';
                break;
            }

            s+=std::string(1,num);
        }
        else
            counter++;
        if(counter==4)
            s+=" ";
    }
    s+="|";
    return s;
}

std::string toStringCasellaIniziale(Casella* c)
{
    std::string s = "|"+std::string(1,c->getTipoChar())+"|";
    return s;
}

int verificaVincitore(std::vector<Giocatore*> giocatori)
{
    int counter = 0;
    int idVincitore = 0;
    for(int i=0; i<kDefaultNumeroGiocatori; i++)
    {
        if(giocatori[i]->getStato() == 0)
            counter++;
        else
            idVincitore = giocatori[i]->getId();
    }
    if(counter==3)
        return idVincitore;
    else
        return -1;
}

int stabilisciVincitore(std::vector<Giocatore*> giocatori)
{
    int idVincitore = 0;
    int maxBudget = 0;
    for(int i=0; i<kDefaultNumeroGiocatori; i++)
    {
        if(giocatori[i]->getBudget()>=maxBudget)
        {
            idVincitore = giocatori[i]->getId();
            maxBudget = giocatori[i]->getBudget();
        }
    }

    return idVincitore;
}