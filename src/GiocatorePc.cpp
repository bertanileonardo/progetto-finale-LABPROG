/*
    autore: Vanon Lorenzo
*/

#include "../include/GiocatorePc.h"

GiocatorePc::GiocatorePc(int id)
    : Giocatore(id){}

// Estrazione con probabilità del 25%
bool GiocatorePc::Probabilità()
{
    int array[4] = {0, 1, 0, 0};
    int n = 3*rand();
    if( array[n] == 1)
        return 1;
    return 0;
}

void GiocatorePc::CasellaLaterale(CasellaAcquistabile c)
{
    int budg = GiocatorePc::getBudget();
    // Casella senza proprietario
    if( !(c.isSold()) )
    {
        int prezzo = c.getCostoTerrenoPerTipo();
        if( (budg-prezzo)>=0 && GiocatorePc::Probabilità() == 1 )
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
            if( !(c.HasCasa()) )
            {
                int prezzo = c.getCostoCasaPerTipo();
                if( (budg-prezzo)>=0 && GiocatorePc::Probabilità() == 1 )
                {
                    c.setHasCasa();
                    Giocatore::setBudget( budg - prezzo);

                }
            }
            else // else if (c.HasCasa())
            {
                int prezzo = c.getCostoMiglioramentoAlbergoPerTipo();
                if( (budg-prezzo)>=0 && GiocatorePc::Probabilità() == 1 )
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
            if( !(c.HasCasa()) )
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
            else // else if (c.HasCasa())
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