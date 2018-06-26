#include <iostream>
#include <vector>
#include "feld_ca.h"
using namespace std;

class Grid {
public:
    Grid();
    ~Grid();

    int imax,jmax, state;
    std::vector<std::vector<int>> v;
    std::vector<std::vector<Feld_Ca>> v2 ;
    std::vector<int> v3;
    int methan;
    bool randomizer2;
    bool get_randomizer();
    std::vector<int> vector_map;
    std::vector<int> smoker_x;
    std::vector<int> smoker_y;
    int anzahl_black_smoker;
    int flaeche_welt;
    std::vector<int> remap_neighbour;

    void set_oxygen(int i1, int j1, float d);
    void set_iron(int i1, int j1, float d);
    void set_proteobacteria(int i1, int j1, int d);
    void set_state_cyanobakterien(int i1, int j1, int d);
    void set_methan(int z);
    int get_methan();
    void set_randomizer(bool a);
    int get_state_cyanobakterien(int i1, int j1);
    int get_state_proteobacteria(int i1, int j1);
    void set_state_proteobacteria(int i1, int j1, int s);
    float get_oxygen(int i1, int j1);
    float get_iron(int i1, int j1);
    void rand_r();
    void set_new_proteobacteria_neighbour(int i1, int j1);
    void set_new_cyanobacteria_neighbour(int i1, int j1);
    void set_random_grid_mit_karte(std::string name, int a);
    bool wasser_ja_nein (int i, int j, int x, int y);
    void read_map(std::string name);
    void set_random_grid2(std::string name, int a);   
	template<typename F>
    float get_universal(int i1, int j1, F func);
    void copy_grid2(std::vector<std::vector<Feld_Ca>> &x, Grid &b);
   	template<typename F>   
    float diffusion(int i, int j, F func, float d);
    template<typename F>   
    float diffusion_sauerstoff(int i, int j, F func, float d);
	void set_grid2(int i, int j, int anzahl);
    void print_grid_in_file_mathematica2(std::string dateiname);
	template<typename F> 
    void print_grid_in_file_mathematica3(std::string dateiname, F func);
    int count_neighbours(int i, int j, int state2);
    void speichern(std::string dateiname,std::string daten, std::string header);
    void set_random_grid(int a);
    void print_grid_terminal();
    void set_grid(int i, int j);
    void copy_grid(std::vector<std::vector<int>> &x);
    void print_grid_in_file(std::string dateiname, std::string header);
    void print_grid_in_file_mathematica(std::string dateiname);
    void print_density_in_file(std::string dateiname, int step, int state2);
    void make_new_file(std::string dateiname);
    void make_new_file_sauerstoff(std::string dateiname);
    void make_new_file_sauerstoff_total(std::string dateiname);
    void make_new_file_cyanobakterien(std::string dateiname);
    void make_new_file_eisen(std::string dateiname);
    void make_new_file_proteobacteria(std::string dateiname);
    void make_new_file_methan(std::string dateiname);
    void print_density_in_file_sauerstoff(std::string dateiname, int step);
    void print_density_in_file_proteobacteria(std::string dateiname, int step);
    void print_density_in_file_eisen(std::string dateiname, int step);
    void print_density_in_file_methan(std::string dateiname, int step, int anfang);
    void print_density_in_file_cyanobakterien(std::string dateiname, int step);
    void print_density_in_file_sauerstoff_total(std::string dateiname, int step, int anfang);
    int count_neighbours_cyanobacteria(int i, int j);
    void set_prison(int i1, int j1, float d);
    int get_prison(int i1, int j1);
    void set_prison_cooperate(int i1, int j1, bool d);
    bool get_prison_cooperate(int i1, int j1);
    int get_prison_punkte(int i1, int j1);
    void set_prison_punkte(int i1, int j1, int d);
    void set_sauerstoff_total(int a);
    int get_sauerstoff_total();
    std::vector<std::vector<Feld_Ca>> get_v2();
    void set_v2(std::vector<std::vector<Feld_Ca>> a);
    int roundnew(double d);
    int volcanism(int atmospheric_oxygen, int timestep);
    void make_new_file_landschaft(std::string dateiname);
    void print_density_in_file_landschaft(std::string dateiname, int step, int anfang);
    void set_black_smoker(int anzahl);
    void activate_black_smocker(int timestep, int start);
    bool innerhalb_welt (int i, int j);
    void set_flaeche(int a2);
    int get_flaeche();
    float sauerstoff_ocean;
    float eisen_ocean;
    void set_sauerstoff_ocean(float d);
    void set_eisen_ocean(float d);
    float get_sauerstoff_ocean();
    float get_eisen_ocean();
    float get_density_proteo();
    float get_density_cyano();
    void print_in_file(std::string dateiname, int step, float step2);

private:
    static int sauerstoff_total;
    static int methan_total;
};	

#include "grid.cpp"