#include "../include/Casella.h"

/*
  autore Leonardo Gasparoni
*/


Casella::Casella(TipoCasella tipo) : tipo(tipo) {}

TipoCasella Casella::getTipo() const {
  return tipo;
}

CasellaAcquistabile::CasellaAcquistabile(TipoCasella tipo) : Casella(tipo),
  proprietario(0),
  numeroCase(0),
  venduta(false),
  haCasa(false),
  ACQUISTO_TERRENO(getCostoTerrenoPerTipo()),
  ACQUISTO_CASA(getCostoCasaPerTipo()),
  MIGLIORAMENTO_ALBERGO(getCostoMiglioramentoAlbergoPerTipo()),
  PERNOTTAMENTO_CASA(getCostoPernottamentoCasaPerTipo()),
  PERNOTTAMENTO_ALBERGO(getCostoPernottamentoAlbergoPerTipo()) {}

int CasellaAcquistabile::getCostoTerrenoPerTipo() const {
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

int CasellaAcquistabile::getCostoCasaPerTipo() const {
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

int CasellaAcquistabile::getCostoMiglioramentoAlbergoPerTipo() const {
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

int CasellaAcquistabile::getCostoPernottamentoCasaPerTipo() const {
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

int CasellaAcquistabile::getCostoPernottamentoAlbergoPerTipo() const {
  switch (tipo) {
    case TipoCasella::E:
      return static_cast<int>(Costo::PERNOTTAMENTO_ALBERGO_ECONOMICO);
    case TipoCasella::S:
      return static_cast<int>(Costo::PERNOTTAMENTO_ALBERGO_STANDARD);
    case TipoCasella::L: ;
  }
}

int CasellaAcquistabile::getProprietario() const {
  if (tipo == TipoCasella::E || tipo == TipoCasella::S || tipo == TipoCasella::L)
    return proprietario;
  return -1;
}

void CasellaAcquistabile::setProprietario(int proprietario) {
  if (tipo == TipoCasella::E || tipo == TipoCasella::S || tipo == TipoCasella::L) {
    this->proprietario = proprietario;
  } else {
    std::cout << "Tipo di casella non valido" << std::endl;
  }
}

int CasellaAcquistabile::getNumeroCase() const {
  if (tipo == TipoCasella::E || tipo == TipoCasella::S || tipo == TipoCasella::L) {
    return numeroCase;
  }
  return -1;
}

bool CasellaAcquistabile::isSold() const {
  if (tipo == TipoCasella::E || tipo == TipoCasella::S || tipo == TipoCasella::L) {
    return venduta;
  }
  return false;
}

void CasellaAcquistabile::setSold() {
  if (tipo == TipoCasella::E || tipo == TipoCasella::S || tipo == TipoCasella::L) {
    venduta = true;
  } else {
    std::cout << "Tipo di casella non valido" << std::endl;
  }
}

bool CasellaAcquistabile::HasCasa() const {
  if (tipo == TipoCasella::E || tipo == TipoCasella::S || tipo == TipoCasella::L) {
    return haCasa;
  }
  return false;
}

void CasellaAcquistabile::setHasCasa() {
  if (tipo == TipoCasella::E || tipo == TipoCasella::S || tipo == TipoCasella::L) {
    haCasa = true;
  } else {
    std::cout << "Tipo di casella non valido" << std::endl;
  }
}