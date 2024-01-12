/*
    autore: Vanon Lorenzo
*/

#include "../include/GiocatorePcHuman.h"
#include "../include/Pila.h"

GiocatorePcHuman::GiocatorePcHuman(int id, bool mode)
    : GiocatorePc(id), modalita_di_gioco{ mode } {}


bool GiocatorePcHuman::getModalitaGioco()
{   return modalita_di_gioco; }

void GiocatorePcHuman::controlloCasella(Casella c)
{
    if( c.getTipo() == TipoCasella::_U3164 ) 
        GiocatorePcHuman::casellaAngolare();
    if( c.getTipo() == TipoCasella::P )
        GiocatorePcHuman::casellaPartenza();
    else
        GiocatorePcHuman::casellaLaterale(c);
}

void GiocatorePcHuman::casellaLaterale(Casella c)
{
    if( !(GiocatorePcHuman::getModalitaGioco()) )
    {
        GiocatorePc::casellaLaterale(c);    
    }
    else
    {
        int budg = GiocatorePcHuman::getBudget();
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
                c.setProprietario(GiocatorePcHuman::getId());
                c.setSold();
                GiocatorePcHuman::setBudget(budg-prezzo);
            }
            // else senza soldi? --> come agire
        }
    }

    else
    {
        // Di proprietà del giocatore in turno
        if( c.getProprietario() == GiocatorePcHuman::getId() )
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
            else // else if (c.hasCasa())
            {
                char risposta;
                do
                {
                    std::cout<<"con una casa costruita: desideri migliorarla in albergo? (S = si, N = no)\nRisposta: ";
                    std::cin>>risposta;
                }
                while( !(risposta!='N' || risposta!='n' || risposta!='S' || risposta!='s') );
                
                int prezzo = c.getCostoMiglioramentoAlbergoPerTipo();
                if( (budg-prezzo)>=0 && GiocatorePcHuman::probabilita() == 1 )
                {
                    // da aggiungere un setHasAlbergo
                    Giocatore::setBudget( budg - prezzo);
                }
            }
            // aggiungere opzione quando ha l'albergo e quindi non fa nulla

        }
        // Di proprietà di un altro giocatore
        else
        {
            if( !(c.hasCasa()) )
            {
                int prezzo = c.getCostoTerrenoPerTipo();
                if( (GiocatorePcHuman::getBudget() - prezzo)>=0 )
                    GiocatorePcHuman::setBudget(Giocatore::getBudget() - prezzo);
                else
                {
                    Giocatore::setStato(0);
                    Giocatore::setBudget(0);
                }
            }
            else // else if (c.hasCasa())
            {
                int prezzo = c.getCostoPernottamentoCasaPerTipo();
                if( (GiocatorePcHuman::getBudget() - prezzo)>=0 )
                    GiocatorePcHuman::setBudget(Giocatore::getBudget() - prezzo);
                else
                {
                    Giocatore::setStato(0);
                    Giocatore::setBudget(0);
                }
            }
            /*
            else // Ha l'albergo
            {
                int prezzo = c.getCostoPernottamentoAlbergoPerTipo();
                if( (GiocatorePcHuman::getBudget() - prezzo)>=0 )
                    GiocatorePcHuman::setBudget(Giocatore::getBudget() - prezzo);
                else
                {
                    Giocatore::setStato(0);
                    Giocatore::setBudget(0);
                }
            }
            */
        }
    }
    }
}

void GiocatorePcHuman::creazioneTurni()
{
    Pila p;
    int turni[Pila::kDefaultNumeroGiocatori];
    for(int i=0; i<Pila::kDefaultNumeroGiocatori; i++)
    {
        int n = Giocatore::lancioDadi();
        if(i==0)
        {
            GiocatorePcHuman g(n, 1);
            record gioc(&g, n);
            record *giocPtr = &gioc;
            p.push( giocPtr );
        }
        else
        {
            GiocatorePcHuman g(n, 0);
            record gioc(&g, n);
            record *giocPtr = &gioc;
            p.push( giocPtr );
        }
    }

    for(int i=1; i<=Pila::kDefaultNumeroGiocatori; i++)
    {
        int maxPos = p.findMaxPos(i,Pila::kDefaultNumeroGiocatori-1);
        p.v[maxPos].g->setId(i);
        p.v[maxPos].id = 0;
    }
}
