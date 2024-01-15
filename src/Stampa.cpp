#include "../include/Stampa.h"
#include <string>
#include <iostream>
#include <fstream>

/*
    autore : Leonardo Gasparoni
*/

void salvaLog(const std::string& messaggio) {
  std::ofstream file_log("log.txt", std::ios::app);
  if (file_log.is_open()) {
    file_log << "- " << messaggio << std::endl;
    file_log.close();
  } 
  else {
    std::cout << "Impossibile aprire il file " << "log.txt" << std::endl;
  }
}

std::string binder(int i, std::string& text){
    std::string messaggio = "Giocatore " + std::to_string(i) + " "+text;
    return messaggio;
}