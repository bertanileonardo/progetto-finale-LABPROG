/*
    autore: Vanon Lorenzo
*/

#include "../include/GiocatorePc.h"
#include "../include/Pila.h"
#include "../include/Interface.h"

GiocatorePc::GiocatorePc(int id)
    : Giocatore(id){}

// Estrazione con probabilità del 25%
bool GiocatorePc::probabilita()
{
    int array[4] = {0, 1, 0, 0};
    int n = 3*rand();
    if( array[n] == 1)
        return 1;
    return 0;
}

void GiocatorePc::controlloCasella(Casella c)
{
    if( c.getTipo() == TipoCasella::_U3164 ) 
        GiocatorePc::casellaAngolare();
    if( c.getTipo() == TipoCasella::P )
        GiocatorePc::casellaPartenza();
    else
        GiocatorePc::casellaLaterale(c);
}

void GiocatorePc::casellaLaterale(Casella c)
{
    int budg = GiocatorePc::getBudget();
    // Casella senza proprietario
    if( !(c.isSold()) )
    {
        int prezzo = c.getCostoTerrenoPerTipo();
        if( (budg-prezzo)>=0 && GiocatorePc::probabilita() == 1 )
        {
            c.setProprietario(GiocatorePc::getId());
            c.setSold();
            GiocatorePc::setBudget(budg-prezzo);
            
        }
        else return;
    }

    else
    {
        // Di proprietà del giocatore in turno
        if( c.getProprietario() == GiocatorePc::getId() )
        {
            if( !(c.hasCasa()) )
            {
                int prezzo = c.getCostoCasaPerTipo();
                if( (budg-prezzo)>=0 && GiocatorePc::probabilita() == 1 )
                {
                    c.setHasCasa();
                    Giocatore::setBudget( budg - prezzo);

                }
            }
            else // else if (c.hasCasa())
            {
                int prezzo = c.getCostoMiglioramentoAlbergoPerTipo();
                if( (budg-prezzo)>=0 && GiocatorePc::probabilita() == 1 )
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
                if( (GiocatorePc::getBudget() - prezzo)>=0 )
                    GiocatorePc::setBudget(Giocatore::getBudget() - prezzo);
                else
                {
                    Giocatore::setStato(0);
                    Giocatore::setBudget(0);
                }
            }
            else // else if (c.hasCasa())
            {
                int prezzo = c.getCostoPernottamentoCasaPerTipo();
                if( (GiocatorePc::getBudget() - prezzo)>=0 )
                    GiocatorePc::setBudget(Giocatore::getBudget() - prezzo);
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
                if( (GiocatorePc::getBudget() - prezzo)>=0 )
                    GiocatorePc::setBudget(Giocatore::getBudget() - prezzo);
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

void GiocatorePc::creazioneTurni()
{
    Pila p;
    int turni[Pila::kDefaultNumeroGiocatori];
    for(int i=0; i<Pila::kDefaultNumeroGiocatori; i++)
    {
        int n = Giocatore::lancioDadi();
        GiocatorePc g(n);
        record gioc(&g, n);
        record *giocPtr = &gioc;
        p.push( giocPtr );
    }

    for(int i=1; i<=Pila::kDefaultNumeroGiocatori; i++)
    {
        int maxPos = p.findMaxPos(i,Pila::kDefaultNumeroGiocatori-1);
        p.v[maxPos].g->setId(i);
        p.v[maxPos].id = 0;
    }


}
