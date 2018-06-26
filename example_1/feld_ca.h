//grid.h
/*#include <iostream>


class Grid {
public:
    Grid();
    ~Grid();
    int testfunktion(int a);

private:
}; */


#include <iostream>
using namespace std;





class Feld_Ca {
public:
    Feld_Ca();
    ~Feld_Ca();

    std::string name;
    int zustand;
    int zustand_cyanobakterien;
    int zustand_proteobacteria;
    float sauerstoff;
    float eisen;
    int methan;
    int get_zustand();
    bool randomizer;
    std::string get_name();
    float get_sauerstoff();
    float get_eisen();
    int get_zustand_cyanobakterien();
    void set_zustand(int z);
    void set_sauerstoff(float s);
    void set_eisen(float e);
    void set_name(std::string n);
    void set_zustand_cyanobakterien(int z);
    int zustand_prison;
    bool prison_cooperate;
    int prison_punkte;
    int landschaft;
    void set_landschaft(int l);
    int get_landschaft();
    float eisen_total;
    float sauerstoff_total;



private:

};
#include "feld_ca.cpp"