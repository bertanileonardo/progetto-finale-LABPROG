#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include "../include/Interface.h" 

/*
    autore: Leonardo Bertani 
*/

int main(int argc, char** argv){
    std::string modalita = argv[1];
    benvenuto(modalita);
    return 0;
}