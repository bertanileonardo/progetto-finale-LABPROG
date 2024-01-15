/*
    autore: Vanon Lorenzo
*/

#include "../include/Giocatore.h"
#include "../include/Interface.h"
#include "../include/Stampa.h"


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
    coordXgiocatore{8},
    coordYGiocatore{'H'}
    {
        //if(!( id>0 && id<5 )) // sostituire con delle costanti casomai
        //    throw InvalidIdException();
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

int Giocatore::getCoordXGiocatore()
{   return Giocatore::coordXgiocatore; }

char Giocatore::getCoordYGiocatore()
{   return Giocatore::coordYGiocatore; }

void Giocatore::setPosizioneGiocatore(int x, char y)
{
    Giocatore::coordXgiocatore = x;
    Giocatore::coordYGiocatore = y;
}

void Giocatore::casellaPartenza()
{
    setBudget(Giocatore::budget_giocatore_ + kFioriniPartenza);
    std::string s = " \00E8 passato dal via e ha ritirato "+std::to_string(kFioriniPartenza)+" \0192 (fiorini)";
    salvaLog(binder(Giocatore::getId(), s));
}

void Giocatore::casellaAngolare(Casella* c)
{
    std::string casella = ""+std::to_string(c->getCoordX())+std::string(1, c->getCoordY());
    std::string s = "e' arrivato alla casella "+casella;
    salvaLog(binder(Giocatore::getId(), s));
}

void Giocatore::casellaLaterale(Casella* c)
{
    std::string casella = ""+std::to_string(c->getCoordX())+std::string(1, c->getCoordY());
    std::string s = "e' arrivato alla casella "+casella;
    salvaLog(binder(Giocatore::getId(), s));

    if( !(Giocatore::getModalitaGioco()) )
    {
        int budg = Giocatore::getBudget();

        // Casella senza proprietario
        if( !(c->isSold()) )
        {
            int prezzo = c->getCostoTerrenoPerTipo();
            if( (budg-prezzo)>=0 && probabilita() == 1 )
            {
                c->setProprietario(Giocatore::getId());
                c->setSold();
                Giocatore::setBudget(budg-prezzo);
                std::string sLog = "ha aquistato il terreno "+casella;
                salvaLog(binder(Giocatore::getId(), sLog));
            }
            else return;
        }

        else
        {
            // Di proprietà del giocatore in turno
            if( c->getProprietario() == Giocatore::getId() )
            {
                if( !(c->hasCasa()) )
                {
                    int prezzo = c->getCostoCasaPerTipo();
                    if( (budg-prezzo)>=0 && probabilita() == 1 )
                    {
                        c->setHasCasa();
                        Giocatore::setBudget( budg - prezzo);
                        std::string sLog = "ha costruito una casa sul terreno "+casella;
                        salvaLog(binder(Giocatore::getId(), sLog));
                    }
                }
                else if (c->hasCasa())
                {
                    int prezzo = c->getCostoMiglioramentoAlbergoPerTipo();
                    if( (budg-prezzo)>=0 && probabilita() == 1 )
                    {
                        c->setHasAlbergo();
                        Giocatore::setBudget( budg - prezzo);
                        std::string sLog = "ha migliorato una casa in albergo sul terreno "+casella;
                        salvaLog(binder(Giocatore::getId(), sLog));
                    }
                }
                else
                {
                    std::cout<<"Possiedi gi\00E0 un albergo su questo terreno"<<std::endl;
                }
                // AGGIUNTO CI STA? aggiungere opzione quando ha l'albergo e quindi non fa nulla

            }
            // Di proprietà di un altro giocatore
            else
            {
                if( !(c->hasCasa()) )
                {
                    std::string sLog ="non paga nulla in quanto sulla casella " + casella +
                    " non sono presenti costruzioni";
                    salvaLog(binder(Giocatore::getId(), sLog));
                }
                else if (c->hasCasa())
                {
                    int prezzo = c->getCostoPernottamentoCasaPerTipo();
                    if( (Giocatore::getBudget() - prezzo)>=0 )
                    {
                        Giocatore::setBudget(Giocatore::getBudget() - prezzo);std::string sLog = "ha pagato" + std::to_string(prezzo) + " fiorini a giocatore " +
                        std::to_string(c->getProprietario()) + "per pernottamento presso la casella " + casella;
                        salvaLog(binder(Giocatore::getId(), sLog));
                    }

                    else
                    {
                        Giocatore::setStato(0);
                        Giocatore::setBudget(0);
                        std::string sLog = "e' stato eliminato in quanto non ha pi\00F9 fiorini.";
                        salvaLog(binder(Giocatore::getId(), sLog));
                    }
                }
                
                else // Ha l'albergo
                {
                    int prezzo = c->getCostoPernottamentoAlbergoPerTipo();
                    if( (Giocatore::getBudget() - prezzo)>=0 )
                    {
                        Giocatore::setBudget(Giocatore::getBudget() - prezzo);
                        std::string sLog = "ha pagato" + std::to_string(prezzo) + " fiorini a giocatore " +
                        std::to_string(c->getProprietario()) + "per pernottamento presso la casella " + casella;
                        salvaLog(binder(Giocatore::getId(), sLog));
                    }
                    else
                    {
                        Giocatore::setStato(0);
                        Giocatore::setBudget(0);
                        std::string sLog = "e' stato eliminato in quanto non ha pi\00F9 fiorini.";
                        salvaLog(binder(Giocatore::getId(), sLog));
                    }
                }
                
            }
        }    
    }
    else
    {
        int budg = Giocatore::getBudget();

        // Casella senza proprietario
        if( !(c->isSold()) )
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
                int prezzo = c->getCostoTerrenoPerTipo();
                if( (budg-prezzo)>=0 )
                {
                    c->setProprietario(Giocatore::getId());
                    c->setSold();
                    Giocatore::setBudget(budg-prezzo);
                    Giocatore::setBudget(budg-prezzo);
                    std::string sLog = "ha aquistato il terreno "+casella;
                    salvaLog(binder(Giocatore::getId(), sLog));
                }
                // else senza soldi? --> come agire
            }
        }

        else
        {
            // Di proprietà del giocatore in turno
            if( c->getProprietario() == Giocatore::getId() )
            {
                std::cout<<"Casella di tua proprietà, ";
                if( !(c->hasCasa()) )
                {
                    char risposta;
                    do
                    {
                        std::cout<<"senza costruzioni: desideri implementare una casa? (S = si, N = no)\nRisposta: ";
                        std::cin>>risposta;
                    }
                    while( !(risposta!='N' || risposta!='n' || risposta!='S' || risposta!='s') );

                    int prezzo = c->getCostoCasaPerTipo();
                    if( (budg-prezzo)>=0 )
                    {
                        c->setHasCasa();
                        Giocatore::setBudget( budg - prezzo);
                        std::string sLog = "ha costruito una casa sul terreno "+casella;
                        salvaLog(binder(Giocatore::getId(), sLog));
                    }
                    // else senza soldi
                }
                else if (c->hasCasa())
                {
                    char risposta;
                    do
                    {
                        std::cout<<"con una casa costruita: desideri migliorarla in albergo? (S = si, N = no)\nRisposta: ";
                        std::cin>>risposta;
                    }
                    while( !(risposta!='N' || risposta!='n' || risposta!='S' || risposta!='s') );
                    
                    int prezzo = c->getCostoMiglioramentoAlbergoPerTipo();
                    if( (budg-prezzo)>=0)
                    {
                        c->setHasAlbergo();
                        Giocatore::setBudget( budg - prezzo);
                        std::string sLog = "ha migliorato una casa in albergo sul terreno "+casella;
                        salvaLog(binder(Giocatore::getId(), sLog));
                    }
                }
                else
                {
                    std::cout<<"Possiedi gi\00E0 un albergo su questo terreno"<<std::endl;
                }
                // AGGIUNTO aggiungere opzione quando ha l'albergo e quindi non fa nulla

            }
            // Di proprietà di un altro giocatore
            else
            {
                if( !(c->hasCasa()) )
                {
                    std::string sLog ="non paga nulla in quanto sulla casella " + casella +
                    " non sono presenti costruzioni";
                    salvaLog(binder(Giocatore::getId(), sLog));
                }
                else if (c->hasCasa())
                {
                    int prezzo = c->getCostoPernottamentoCasaPerTipo();
                    if( (Giocatore::getBudget() - prezzo)>=0 )
                    {
                        Giocatore::setBudget(Giocatore::getBudget() - prezzo);
                        std::string sLog = "ha pagato" + std::to_string(prezzo) + " fiorini a giocatore " +
                        std::to_string(c->getProprietario()) + "per pernottamento presso la casella " + casella;
                        salvaLog(binder(Giocatore::getId(), sLog));                        
                    }
                    else
                    {
                        Giocatore::setStato(0);
                        Giocatore::setBudget(0);
                        std::string sLog = "e' stato eliminato in quanto non ha pi\00F9 fiorini.";
                        salvaLog(binder(Giocatore::getId(), sLog));
                    }
                }
                
                else // Ha l'albergo
                {
                    int prezzo = c->getCostoPernottamentoAlbergoPerTipo();
                    if( (Giocatore::getBudget() - prezzo)>=0 )
                    {
                        Giocatore::setBudget(Giocatore::getBudget() - prezzo);
                        std::string sLog = "ha pagato" + std::to_string(prezzo) + " fiorini a giocatore " +
                        std::to_string(c->getProprietario()) + "per pernottamento presso la casella " + casella;
                        salvaLog(binder(Giocatore::getId(), sLog));
                    }
                    else
                    {
                        Giocatore::setStato(0);
                        Giocatore::setBudget(0);
                        std::string sLog = "e' stato eliminato in quanto non ha pi\00F9 fiorini.";
                        salvaLog(binder(Giocatore::getId(), sLog));
                    }
                }
                
            }
        }
    }
}


void Giocatore::controlloCasella(Casella* c)
{
    if( c->getTipo() == TipoCasella::_U3164 )
        Giocatore::casellaAngolare(c);
    else if( c->getTipo() == TipoCasella::P )
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

int findMaxPos(Record* v[], int from, int to)
{
    int pos = from;
    for(int i=pos; i<=to; i++)
    {
        if( v[i]->id >= v[pos]->id )
            pos = i;
    }
    return pos;
}

std::vector<Giocatore*> creazioneTurni(bool modalita)
{
    std::vector<Giocatore*> giocatori;
    Record* turni[kDefaultNumeroGiocatori];
    for(int i=0; i<kDefaultNumeroGiocatori; i++)
    {
        int n = lancioDadi();
        bool s;
        // Inizializzo i giocatori, tramite questo if controllo: se la modalità di gioco è human
        // e siamo all'ultimo giocatore lo inizializzo a Human
            if(modalita==1 && i==kDefaultNumeroGiocatori-1 )
                s = 1;
            else
                s = 0;
        Giocatore* g = new Giocatore(n, s);
        Record* gioc = new Record(g, n);
        turni[i] = gioc;
    }

    for(int i=0; i<kDefaultNumeroGiocatori; i++)
    {
        int maxPos = findMaxPos(turni, 0, kDefaultNumeroGiocatori-1);
        turni[maxPos]->g->setId(i+1);
        turni[maxPos]->id = 0;
        giocatori.push_back(turni[maxPos]->g);
    }
    return giocatori;
}