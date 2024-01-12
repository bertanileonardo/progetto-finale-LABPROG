#include "../include/Casella.h"

/*
  autore Leonardo Gasparoni
*/

TipoCasella Casella::getTipo() const {
  return tipo;
}

Casella::Casella(TipoCasella tipo) : Casella(tipo),
  proprietario(0),
  numeroCase(0),
  venduta(false),
  haCasa(false),
  ACQUISTO_TERRENO(getCostoTerrenoPerTipo()),
  ACQUISTO_CASA(getCostoCasaPerTipo()),
  MIGLIORAMENTO_ALBERGO(getCostoMiglioramentoAlbergoPerTipo()),
  PERNOTTAMENTO_CASA(getCostoPernottamentoCasaPerTipo()),
  PERNOTTAMENTO_ALBERGO(getCostoPernottamentoAlbergoPerTipo()) {}

int Casella::getCostoTerrenoPerTipo() const {
  switch (tipo) {
    case TipoCasella::E:
      return static_cast<int>(Costo::TERRENO_ECONOMICO);
    case TipoCasella::S:
      return static_cast<int>(Costo::TERRENO_STANDARD);
    case TipoCasella::L:
      return static_cast<int>(Costo::TERRENO_LUSSO);
    default:
      std::cout << "Tipo di casella non valido" << std::endl;
  }
  return 0;
}

int Casella::getCostoCasaPerTipo() const {
  switch (tipo) {
    case TipoCasella::E:
      return static_cast<int>(Costo::CASA_ECONOMICA);
    case TipoCasella::S:
      return static_cast<int>(Costo::CASA_STANDARD);
    case TipoCasella::L:
      return static_cast<int>(Costo::CASA_LUSSO);
    default:
      std::cout << "Tipo di casella non valido" << std::endl;
  }
  return 0;
}

int Casella::getCostoMiglioramentoAlbergoPerTipo() const {
  switch (tipo) {
    case TipoCasella::E:
      return static_cast<int>(Costo::MIGLIORAMENTO_ALBERGO_ECONOMICO);
    case TipoCasella::S:
      return static_cast<int>(Costo::MIGLIORAMENTO_ALBERGO_STANDARD);
    case TipoCasella::L:
      return static_cast<int>(Costo::MIGLIORAMENTO_ALBERGO_LUSSO);
    default:
      std::cout << "Tipo di casella non valido" << std::endl;
  }
  return 0;
}

int Casella::getCostoPernottamentoCasaPerTipo() const {
  switch (tipo) {
    case TipoCasella::E:
      return static_cast<int>(Costo::PERNOTTAMENTO_CASA_ECONOMICA);
    case TipoCasella::S:
      return static_cast<int>(Costo::PERNOTTAMENTO_CASA_STANDARD);
    case TipoCasella::L:
      return static_cast<int>(Costo::PERNOTTAMENTO_CASA_LUSSO);
    default:
      std::cout << "Tipo di casella non valido" << std::endl;
  }
  return 0;
}

int Casella::getCostoPernottamentoAlbergoPerTipo() const {
  switch (tipo) {
    case TipoCasella::E:
      return static_cast<int>(Costo::PERNOTTAMENTO_ALBERGO_ECONOMICO);
    case TipoCasella::S:
      return static_cast<int>(Costo::PERNOTTAMENTO_ALBERGO_STANDARD);
    case TipoCasella::L: ;
  }
}

int Casella::getProprietario() const {
  if (tipo == TipoCasella::E || tipo == TipoCasella::S || tipo == TipoCasella::L)
    return proprietario;
  return -1;
}

void Casella::setProprietario(int proprietario) {
  if (tipo == TipoCasella::E || tipo == TipoCasella::S || tipo == TipoCasella::L) {
    this->proprietario = proprietario;
  } else {
    std::cout << "Tipo di casella non valido" << std::endl;
  }
}

int Casella::getNumeroCase() const {
  if (tipo == TipoCasella::E || tipo == TipoCasella::S || tipo == TipoCasella::L) {
    return numeroCase;
  }
  return -1;
}

bool Casella::isSold() const {
  if (tipo == TipoCasella::E || tipo == TipoCasella::S || tipo == TipoCasella::L) {
    return venduta;
  }
  return false;
}

void Casella::setSold() {
  if (tipo == TipoCasella::E || tipo == TipoCasella::S || tipo == TipoCasella::L) {
    venduta = true;
  } else {
    std::cout << "Tipo di casella non valido" << std::endl;
  }
}

bool Casella::HasCasa() const {
  if (tipo == TipoCasella::E || tipo == TipoCasella::S || tipo == TipoCasella::L) {
    return haCasa;
  }
  return false;
}

void Casella::setHasCasa() {
  if (tipo == TipoCasella::E || tipo == TipoCasella::S || tipo == TipoCasella::L) {
    haCasa = true;
  } else {
    std::cout << "Tipo di casella non valido" << std::endl;
  }
}