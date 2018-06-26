#include <iostream>
using namespace std;


Feld_Ca::Feld_Ca(){}
Feld_Ca::~Feld_Ca(){}

    int Feld_Ca::get_zustand(){return zustand;}

    std::string Feld_Ca::get_name(){return name;}
    float Feld_Ca::get_sauerstoff(){return sauerstoff;}
    float Feld_Ca::get_eisen(){return eisen;}
    int Feld_Ca::get_zustand_cyanobakterien(){return zustand_cyanobakterien;}
    void Feld_Ca::set_zustand(int z){zustand = z;}
    void Feld_Ca::set_sauerstoff(float s){sauerstoff = s;}
    void Feld_Ca::set_eisen(float e){eisen = e;}
    void Feld_Ca::set_name(std::string n){name = n;}
    void Feld_Ca::set_zustand_cyanobakterien(int z){zustand_cyanobakterien = z;}
    void Feld_Ca::set_landschaft(int l){landschaft = l;}
    int Feld_Ca::get_landschaft(){return landschaft;}     


