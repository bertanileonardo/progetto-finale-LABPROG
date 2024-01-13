/*
    autore: Vanon Lorenzo
*/

#include "../include/Giocatore.h"
#include "../include/Interface.h"


Record& Record::operator=(const Record& r)
{
    delete[] g;
    g = r.g;
    id = r.id;
    return *this;
}

Record& Record::operator=(Record&& r)
{
    delete[] g;
    g = r.g;
    id = r.id;
    r.g = nullptr;
    r.id = 0;
    return *this;
}


Giocatore::Giocatore(int id, bool mode)
    : budget_giocatore_{ kDefaultBudget },
    id_giocatore_{ id },
    stato_corrente_giocatore_{ kDefaultStato },
    modalita_di_gioco_{ mode },
    posizione_attuale_{TipoCasella::P}
    {
        if(!( id>0 && id<5 )) // sostituire con delle costanti casomai
            throw InvalidIdException();
    }


int Giocatore::getBudget()
{   return Giocatore::budget_giocatore_; }

void Giocatore::setBudget(int b)
{   Giocatore::budget_giocatore_ = b; }

int Giocatore::getId()
{   return Giocatore::id_giocatore_; }

void Giocatore::setId(int id)
{   Giocatore::id_giocatore_ = id; }

bool Giocatore::getStato()
{   return Giocatore::stato_corrente_giocatore_; }

void Giocatore::setStato(bool s)
{   Giocatore::stato_corrente_giocatore_ = s; }

bool Giocatore::getModalitaGioco()
{   return Giocatore::modalita_di_gioco_; }


void Giocatore::casellaPartenza()
{
    setBudget(Giocatore::budget_giocatore_ + 20);
}

void Giocatore::casellaLaterale(Casella c)
{
    if( !(Giocatore::getModalitaGioco()) )
    {
        int budg = Giocatore::getBudget();

        // Casella senza proprietario
        if( !(c.isSold()) )
        {
            int prezzo = c.getCostoTerrenoPerTipo();
            if( (budg-prezzo)>=0 && probabilita() == 1 )
            {
                c.setProprietario(Giocatore::getId());
                c.setSold();
                Giocatore::setBudget(budg-prezzo);
                
            }
            else return;
        }

        else
        {
            // Di proprietà del giocatore in turno
            if( c.getProprietario() == Giocatore::getId() )
            {
                if( !(c.hasCasa()) )
                {
                    int prezzo = c.getCostoCasaPerTipo();
                    if( (budg-prezzo)>=0 && probabilita() == 1 )
                    {
                        c.setHasCasa();
                        Giocatore::setBudget( budg - prezzo);

                    }
                }
                else if (c.hasCasa())
                {
                    int prezzo = c.getCostoMiglioramentoAlbergoPerTipo();
                    if( (budg-prezzo)>=0 && probabilita() == 1 )
                    {
                        c.setHasAlbergo();
                        Giocatore::setBudget( budg - prezzo);
                    }
                }
                // OPZIONALE aggiungere opzione quando ha l'albergo e quindi non fa nulla

            }
            // Di proprietà di un altro giocatore
            else
            {
                if( !(c.hasCasa()) )
                {
                    int prezzo = c.getCostoTerrenoPerTipo();
                    if( (Giocatore::getBudget() - prezzo)>=0 )
                        Giocatore::setBudget(Giocatore::getBudget() - prezzo);
                    else
                    {
                        Giocatore::setStato(0);
                        Giocatore::setBudget(0);
                    }
                }
                else if (c.hasCasa())
                {
                    int prezzo = c.getCostoPernottamentoCasaPerTipo();
                    if( (Giocatore::getBudget() - prezzo)>=0 )
                        Giocatore::setBudget(Giocatore::getBudget() - prezzo);
                    else
                    {
                        Giocatore::setStato(0);
                        Giocatore::setBudget(0);
                    }
                }
                
                else // Ha l'albergo
                {
                    int prezzo = c.getCostoPernottamentoAlbergoPerTipo();
                    if( (Giocatore::getBudget() - prezzo)>=0 )
                        Giocatore::setBudget(Giocatore::getBudget() - prezzo);
                    else
                    {
                        Giocatore::setStato(0);
                        Giocatore::setBudget(0);
                    }
                }
                
            }
        }    
    }
    else
    {
        int budg = Giocatore::getBudget();

        // Casella senza proprietario
        if( !(c.isSold()) )
        {
            char risposta;
            do
            {
                std::cout<<"Casella senza proprietario: desideri acquistarla? (S = si, N = no)\nRisposta: ";
                std::cin>>risposta;
            }
            while( !(risposta!='N' || risposta!='n' || risposta!='S' || risposta!='s') );

            if(risposta=='S' || risposta=='s')
            {
                int prezzo = c.getCostoTerrenoPerTipo();
                if( (budg-prezzo)>=0 )
                {
                    c.setProprietario(Giocatore::getId());
                    c.setSold();
                    Giocatore::setBudget(budg-prezzo);
                }
                // else senza soldi? --> come agire
            }
        }

        else
        {
            // Di proprietà del giocatore in turno
            if( c.getProprietario() == Giocatore::getId() )
            {
                std::cout<<"Casella di tua proprietà, ";
                if( !(c.hasCasa()) )
                {
                    char risposta;
                    do
                    {
                        std::cout<<"senza costruzioni: desideri implementare una casa? (S = si, N = no)\nRisposta: ";
                        std::cin>>risposta;
                    }
                    while( !(risposta!='N' || risposta!='n' || risposta!='S' || risposta!='s') );

                    int prezzo = c.getCostoCasaPerTipo();
                    if( (budg-prezzo)>=0 )
                    {
                        c.setHasCasa();
                        Giocatore::setBudget( budg - prezzo);
                    }
                    // else senza soldi
                }
                else if (c.hasCasa())
                {
                    char risposta;
                    do
                    {
                        std::cout<<"con una casa costruita: desideri migliorarla in albergo? (S = si, N = no)\nRisposta: ";
                        std::cin>>risposta;
                    }
                    while( !(risposta!='N' || risposta!='n' || risposta!='S' || risposta!='s') );
                    
                    int prezzo = c.getCostoMiglioramentoAlbergoPerTipo();
                    if( (budg-prezzo)>=0 && probabilita() == 1 )
                    {
                        c.setHasAlbergo();
                        Giocatore::setBudget( budg - prezzo);
                    }
                }
                // OPZIONALE aggiungere opzione quando ha l'albergo e quindi non fa nulla

            }
            // Di proprietà di un altro giocatore
            else
            {
                if( !(c.hasCasa()) )
                {
                    int prezzo = c.getCostoTerrenoPerTipo();
                    if( (Giocatore::getBudget() - prezzo)>=0 )
                        Giocatore::setBudget(Giocatore::getBudget() - prezzo);
                    else
                    {
                        Giocatore::setStato(0);
                        Giocatore::setBudget(0);
                    }
                }
                else if (c.hasCasa())
                {
                    int prezzo = c.getCostoPernottamentoCasaPerTipo();
                    if( (Giocatore::getBudget() - prezzo)>=0 )
                        Giocatore::setBudget(Giocatore::getBudget() - prezzo);
                    else
                    {
                        Giocatore::setStato(0);
                        Giocatore::setBudget(0);
                    }
                }
                
                else // Ha l'albergo
                {
                    int prezzo = c.getCostoPernottamentoAlbergoPerTipo();
                    if( (Giocatore::getBudget() - prezzo)>=0 )
                        Giocatore::setBudget(Giocatore::getBudget() - prezzo);
                    else
                    {
                        Giocatore::setStato(0);
                        Giocatore::setBudget(0);
                    }
                }
                
            }
        }
    }
}


void Giocatore::controlloCasella(Casella c)
{
    if( c.getTipo() == TipoCasella::_U3164 );
    else if( c.getTipo() == TipoCasella::P )
        Giocatore::casellaPartenza();
    else
        Giocatore::casellaLaterale(c);
}


int generaNumeroCasuale(){
    return rand() % 6 + 1; // correzione dovuta al fatto che rand() restituisce un numero da 0 a i-1
}

int lancioDadi(){
    int dado1 = generaNumeroCasuale();
    int dado2 = generaNumeroCasuale();
    return dado1 + dado2; // come da richiesta restituisco la somma delle uscite dei 2 dadi
}

bool probabilita()
{
    int array[4] = {0, 1, 0, 0};
    int n = 3*rand();
    if( array[n] == 1)
        return 1;
    return 0;
}

int findMaxPos(Record v[], int from, int to)
{
    int pos = from;
    for(int i=pos+1; i<to; i++)
    {
        if( v[i].id >= v[pos].id )
            pos = i;
    }
    return pos;
}

std::vector<Giocatore*> creazioneTurni(bool modalita)
{
    std::vector<Giocatore*> giocatori;
    Record turni[kDefaultNumeroGiocatori];
    for(int i=0; i<kDefaultNumeroGiocatori; i++)
    {
        int n = lancioDadi();
        bool s;
        // Inizializzo i giocatori, tramite questo if controllo: se la modalità di gioco è human
        // e siamo all'ultimo giocatore lo inizializzo a Human
            if(modalita && i==kDefaultNumeroGiocatori-1 )
                s = 1;
            else
                s = 0;
        Giocatore g(n, s);
        Record gioc(&g, n);
        turni[i] = gioc;
    }

    for(int i=1; i<=kDefaultNumeroGiocatori; i++)
    {
        int maxPos = findMaxPos(turni, i, kDefaultNumeroGiocatori-1);
        turni[maxPos].g->setId(i);
        turni[maxPos].id = 0;
        giocatori.push_back(turni[maxPos].g);
    }
    return giocatori;
}