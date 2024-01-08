/*
    autore: Vanon Lorenzo
*/

#include "../include/GiocatorePcHuman.h"

GiocatorePcHuman::GiocatorePcHuman(int id, bool mode)
    : GiocatorePc(id), modalità_di_gioco{ mode } {}


bool GiocatorePcHuman::getModalitàGioco()
{   return modalità_di_gioco; }

void GiocatorePcHuman::CasellaLaterale(CasellaAcquistabile c)
{
    if( !(GiocatorePcHuman::getModalitàGioco()) )
    {
        GiocatorePc::CasellaLaterale(c);    
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
            if( !(c.HasCasa()) )
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
            else // else if (c.HasCasa())
            {
                char risposta;
                do
                {
                    std::cout<<"con una casa costruita: desideri migliorarla in albergo? (S = si, N = no)\nRisposta: ";
                    std::cin>>risposta;
                }
                while( !(risposta!='N' || risposta!='n' || risposta!='S' || risposta!='s') );
                
                int prezzo = c.getCostoMiglioramentoAlbergoPerTipo();
                if( (budg-prezzo)>=0 && GiocatorePcHuman::Probabilità() == 1 )
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
                if( (GiocatorePcHuman::getBudget() - prezzo)>=0 )
                    GiocatorePcHuman::setBudget(Giocatore::getBudget() - prezzo);
                else
                {
                    Giocatore::setStato(0);
                    Giocatore::setBudget(0);
                }
            }
            else // else if (c.HasCasa())
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