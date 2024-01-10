#ifndef CASELLA_H
#define CASELLA_H

#include <iostream>

/*
  autore Leonardo Gasparoni
*/

// Lista con i vari simboli associati al tipo delle caselle
enum class TipoCasella{
  _U3164, // Casella ANGOLARE 'ㅤ' <-- Carattere Unicode U+3164
  P, // Casella PARTENZA
  E, // Casella ECONOMICA
  S, // Casella STANDARD
  L  // Casella LUSSO
};

// Lista dei vari tipi di costo
enum class Costo {
  TERRENO_ECONOMICO = 6,
  TERRENO_STANDARD = 10,
  TERRENO_LUSSO = 20,
  CASA_ECONOMICA = 3,
  CASA_STANDARD = 5,
  CASA_LUSSO = 10,
  MIGLIORAMENTO_ALBERGO_ECONOMICO = 3,
  MIGLIORAMENTO_ALBERGO_STANDARD = 5,
  MIGLIORAMENTO_ALBERGO_LUSSO = 10,
  PERNOTTAMENTO_CASA_ECONOMICA = 2,
  PERNOTTAMENTO_CASA_STANDARD = 4,
  PERNOTTAMENTO_CASA_LUSSO = 7,
  PERNOTTAMENTO_ALBERGO_ECONOMICO = 4,
  PERNOTTAMENTO_ALBERGO_STANDARD = 8,
  PERNOTTAMENTO_ALBERGO_LUSSO = 14,
};

class Casella {

public:
  // Costruttore generale che inizializza il tipo della casella
  Casella(TipoCasella tipo);
  TipoCasella getTipo() const;

protected:
  const TipoCasella tipo;
};

// Classe derivata che rappresenta le caselle dove si può comprare (E, S, L) 
class CasellaAcquistabile : public Casella {

public:
  // Costruttore della classe derivata
  CasellaAcquistabile(TipoCasella tipo);

  // Metodi per ottenere il costo di acquisto di una casella
  int getCostoTerrenoPerTipo() const;
  int getCostoCasaPerTipo() const;
  int getCostoMiglioramentoAlbergoPerTipo() const;
  int getCostoPernottamentoCasaPerTipo() const;
  int getCostoPernottamentoAlbergoPerTipo() const;

  // Metodi getter, setter e booleani definiti in-class
  int getProprietario() const;
  void setProprietario(int proprietario);
  int getNumeroCase() const;
  bool isSold() const;
  void setSold();
  bool HasCasa() const;
  void setHasCasa();

private:
  int proprietario;
  int numeroCase;
  bool venduta;
  bool haCasa;
  const int ACQUISTO_TERRENO;
  const int ACQUISTO_CASA;
  const int MIGLIORAMENTO_ALBERGO;
  const int PERNOTTAMENTO_CASA;
  const int PERNOTTAMENTO_ALBERGO;
};

#endif // CASELLA_H
