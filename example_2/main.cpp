#include <cstdlib>
#include <iostream>
#include <string>
#include <array>
#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include "grid.h"
using namespace std;

int main(int argc, char** argv) 
	{
// Da Bild enthält 329*654 Zellen, davon gehören 215.166 Zellen zur Welt, diese können Wasser oder Festland sein
// Von diesen sind 103.048 Zellen Wasser und 112.118 Festland auf welchem keine Bakterien leben können.     
// Dies entspricht einem Prozentualen Anteil von 61% Wasser auf der Welt.
    //Grid definieren    
        Grid grid;
        Grid new_grid;
        grid.set_grid2(329, 654,30);
        new_grid.set_grid2(329, 654,30);
        grid.set_randomizer(false);
        new_grid.set_randomizer(false);
        grid.rand_r();
        grid.set_grid(329, 654);
        new_grid.set_grid(329, 654);
        new_grid.set_random_grid_mit_karte("kenorland.txt",3);
        grid.vector_map.resize(654*329);
        new_grid.set_black_smoker(30);
        new_grid.set_flaeche(168590);
        new_grid.copy_grid2(grid.v2,grid);

    //Anfang: grid in new grid laden
        for (int i1=0; i1<grid.imax; i1++)
            {
                for (int j1=0; j1<grid.jmax; j1++)
                    { 
                        new_grid.v2[i1][j1].sauerstoff = grid.v2[i1][j1].sauerstoff;
                        new_grid.v2[i1][j1].eisen = new_grid.v2[i1][j1].eisen;
                        new_grid.v2[i1][j1].zustand_cyanobakterien = grid.v2[i1][j1].zustand_cyanobakterien;
                        new_grid.v2[i1][j1].zustand_proteobacteria = grid.v2[i1][j1].zustand_proteobacteria;
                    }
            }         
    //Ende: grid in new grid laden

    //Anfang: Array in Datei schreiben
        new_grid.print_grid_in_file_mathematica3("ausgabe/cyanobakterien", [](Feld_Ca & feld ){return feld.zustand_cyanobakterien;});
        new_grid.print_grid_in_file_mathematica3("ausgabe/Proteobacterien", [](Feld_Ca & feld ){return feld.zustand_proteobacteria;}); 
    //Files für Dichte erstellen
        std::cout <<"New" <<"\n";
        grid.make_new_file_proteobacteria("ausgabe/density");
        grid.make_new_file_methan("ausgabe/density");
        grid.make_new_file_cyanobakterien("ausgabe/density");
        grid.make_new_file_sauerstoff_total("ausgabe/density");
        grid.make_new_file_landschaft("ausgabe/density");
        grid.make_new_file("ausgabe/den_sauerstoff_ocean");
        grid.make_new_file("ausgabe/den_eisen_ocean");
        grid.make_new_file("ausgabe/sterberate_proteo");
        for (int i1=0; i1<grid.imax; i1++)
            {
                for (int j1=0; j1<grid.jmax; j1++)
                    {  
                        float d =0;
                        float e = 0;
                        d= grid.diffusion_sauerstoff(i1,j1,[](Feld_Ca & feld ){return feld.sauerstoff;},0.2);            
                        new_grid.set_oxygen(i1,j1,d);
                        e= grid.diffusion(i1,j1,[](Feld_Ca & feld ){return feld.eisen;},0.2);
                        new_grid.set_iron(i1,j1,e);
                    }
            }
        new_grid.print_grid_in_file_mathematica3("Sauerstoff_new", [](Feld_Ca & feld ){return feld.sauerstoff;});
        //Methan setzen    
        grid.set_methan(14580000); //Bitte unten auch verändern in der print_in_density
        grid.set_eisen_ocean(0.3015270000000001);
        //Ende: Array in Datei schreiben

//Beginn eigentliche Schleife    
    for (int a=0;a<2000;a++)
        {  
        //Alle 10 Zeitschritte Rückmeldung geben
            if (0==a%10)
                {
                    std::cout << "Schritt:"<< a << "\n";  
                }
       //Anfang: Print realisieren
            grid.print_density_in_file_proteobacteria("ausgabe/density", a);
            grid.print_density_in_file_methan("ausgabe/density", a,14580000 );
            grid.print_density_in_file_cyanobakterien("ausgabe/density",a);
            grid.print_density_in_file_sauerstoff_total("ausgabe/density", a, 14580000);
            grid.print_density_in_file_landschaft("ausgabe/density", a, 3*29575);
            grid.print_in_file("ausgabe/den_sauerstoff_ocean", a, grid.get_sauerstoff_ocean());
            grid.print_in_file("ausgabe/den_eisen_ocean", a, grid.get_eisen_ocean());
        //Alle 10 Zeitschritte Grid ausgeben                        
            if (0==a%10)
                {                    
                    int k = 0;
                    k= grid.get_methan();
                    std::cout << "Methan" << k <<"\n";
                    int density2 = 0;
                    for (int i1=0; i1<grid.imax; i1++)
                        {
                            for (int j1=0; j1<grid.jmax; j1++)
                                { 
                                    density2 = density2 + grid.v2[i1][j1].landschaft;
                                }
                        }
                    std::cout << "Landschaft" << (1.000*density2/(3*29575)) <<"\n";
                    string p= "ausgabe/Proteobakterien_"+ to_string(a);
                    string c= "ausgabe/Cyanobakterien_"+ to_string(a);
                    grid.set_oxygen(0,0,1);
                    grid.set_oxygen(0,1,0);
                    grid.set_iron(0,0,1);
                    grid.set_iron(0,1,0);                    
                    grid.print_grid_in_file_mathematica3(p, [](Feld_Ca & feld ){return feld.zustand_proteobacteria;});
                    grid.print_grid_in_file_mathematica3(c, [](Feld_Ca & feld ){return feld.zustand_cyanobakterien;});
                }  
        //Ende: Print realisieren

        //Anfang: Cyanobakterien produzieren Sauerstoff
            // Density für Cyanobakterien abfragen
            float den_cyano = 0;
            den_cyano = grid.get_density_cyano();
            int photosynthese = 0;
            int atmosphaere_ausstoss = 0;
            int index1 = 0;
            int index2 = 0;
            float laufindex_photo_cyano = 0;
            if (den_cyano < 0.089)
                {
                    laufindex_photo_cyano= 7581+(94587.4*den_cyano);
                }
            else
               {
                    if (den_cyano < 0.103)
                        {
                            laufindex_photo_cyano= 63678 -(535714*den_cyano);
                        }
                    else
                        {
                            laufindex_photo_cyano = 7294+ (11705*den_cyano);
                        }
                }
            float laufindex_atmosphaere = 0;
            if (den_cyano < 0.088)
                {
                    laufindex_atmosphaere = 0;
                }
            else
               {
                    if (den_cyano < 0.262382)
                        {
                            laufindex_atmosphaere = -24313 + (276285*den_cyano);
                        }
                    else
                        {
                            laufindex_atmosphaere = 36000;
                        }
                }
            float delta_sauerstoff = 0;
            delta_sauerstoff= (0.442231* pow (2.718281828459045, -69.6571*(0.052382 - den_cyano)))/(pow ((68.4494 + pow (2.718281828459045, -69.6571*(0.052382 - den_cyano))), 2));
            for (int i1=0; i1<grid.imax; i1++)
                {
                    for (int j1=0; j1<grid.jmax; j1++)
                        {               
                            if (grid.get_state_cyanobakterien(i1,j1)==1)
                                {
                                    float b=0;
                                    b = grid.get_oxygen(i1,j1);
                                    if (index1< laufindex_photo_cyano)
                                        {
                                            new_grid.set_oxygen(i1,j1,b+0.0222);
                                            if (rand() % 2 == 1)
                                                {
                                                    new_grid.set_new_cyanobacteria_neighbour(i1, j1);
                                                }
                                            photosynthese++;
                                            index1++;
                                            grid.set_sauerstoff_ocean(grid.get_sauerstoff_ocean()+(delta_sauerstoff/laufindex_photo_cyano));
                                        }
                                        if (index2< laufindex_atmosphaere)
                                            {    
                                                if (grid.get_sauerstoff_total()<=14580000)
                                                    {
                                                        new_grid.set_sauerstoff_total(grid.get_sauerstoff_total()+5);
                                                        if (rand() % 2 == 1)
                                                            {
                                                                new_grid.set_new_cyanobacteria_neighbour(i1, j1);
                                                            }
                                                        atmosphaere_ausstoss++;
                                                        index2++;
                                                    }
                                            }              
                                }            
                        }
                }
            new_grid.copy_grid2(grid.v2,grid);
        //Ende: Cyanobakterien produzieren Sauerstoff  

        // Anfang: Fe2+ reagiert mit Sauerstoff
            float redu_eisen = 0;
            if (((grid.get_sauerstoff_ocean())> grid.get_eisen_ocean())&& (grid.get_eisen_ocean() > 0.087))
                {
                    grid.set_sauerstoff_ocean(grid.get_sauerstoff_ocean()-(grid.get_eisen_ocean()));
                    grid.set_eisen_ocean(0);

                }
            else
                {
                    redu_eisen = (pow(2.718281828459045,grid.get_eisen_ocean()*25-0.3))-6;
                    if (grid.get_eisen_ocean()> grid.get_sauerstoff_ocean()&& (grid.get_eisen_ocean() > 0.087))
                        {
                            grid.set_eisen_ocean(grid.get_eisen_ocean()-(redu_eisen*grid.get_sauerstoff_ocean()));
                            grid.set_sauerstoff_ocean(0);
                        }
                }
        // Ende: Fe2+ reagiert mit Sauerstoff

        //Anfang: Proteokbakterien brauchen Eisen für die Photosynthese
            //Überlebenswahrscheinlichkeit Proteobakterien setzen        
            int potosynthese_proteo = 0;
            float den_eisen_ocean2 = 0.000000000000;
            for (int i1=0; i1<grid.imax; i1++)
                {
                    for (int j1=0; j1<grid.jmax; j1++)
                        { 
                            if (grid.get_state_proteobacteria(i1,j1)==1 && grid.get_eisen_ocean()> 0 )
                                {  
                                    den_eisen_ocean2= den_eisen_ocean2+(0.000000000593);
                                    new_grid.set_new_proteobacteria_neighbour(i1,j1);
                                    potosynthese_proteo++;      
                                }
                        }
                }
            grid.set_eisen_ocean(grid.get_eisen_ocean()-den_eisen_ocean2);
            new_grid.copy_grid2(grid.v2,grid);
        //Ende: Proteokbakterien brauchen Eisen für die Photosynthese
   
        //Anfang: Proteokbakterien sterben bei zuviel Sauerstoff
            int sterberate_proteo = 0;
            float laufindex_proteo_sterben = 0;
            if (redu_eisen > 0.086)
                {
                    laufindex_proteo_sterben = (704.798*pow (2.71828182845, (-0.000555556)*pow ((-200) + ((-36.9429)*log(0.0361387*redu_eisen)), 2)))+(8);
                }
            else
                {
                    if (redu_eisen==0 && grid.get_sauerstoff_ocean()==0)
                        {
                            laufindex_proteo_sterben = 130;
                        }
                    else
                        {
                            if (grid.get_sauerstoff_ocean() <0.022)
                                {
                                    laufindex_proteo_sterben=(704.798*pow (2.71828182845, (-0.000555556)*pow ((-200) + ((-4210.53)*(0.0343- grid.get_sauerstoff_ocean())), 2)))+(8);
                                }
                                else
                                    {                                  
                                        laufindex_proteo_sterben =    (704.798*pow (2.71828182845, (-0.000555556)*pow ((-200) + (1111.26 *(0.206873+grid.get_sauerstoff_ocean())), 2)))+(8)-2;
                                    }
                        }
                }
            int index3 = 0;
            for (int i1=0; i1<grid.imax; i1++)
                {
                    for (int j1=0; j1<grid.jmax; j1++)
                        { 
                            if (grid.get_state_proteobacteria(i1,j1)==1 && index3<laufindex_proteo_sterben)
                                {   
                                    new_grid.set_proteobacteria(i1,j1, 0); 
                                    sterberate_proteo++; 
                                    index3++;
                                }
                        }
                }
            new_grid.copy_grid2(grid.v2,grid);
        //Ende: Proteokbakterien sterben bei zuviel Sauerstoff 
        
        //Anfang: Sauerstoff wird vom Methan und anderen Substanzen verbraucht
            int reaktion_atmos = 0;
            float d01 = 0;
            int a01=0;
            d01 = grid.get_sauerstoff_total();
            a01 = grid.get_methan();
            while (a01>0 && d01>0)
                {                          
                    new_grid.set_sauerstoff_total(d01-1);
                    grid.set_methan(a01-1);                               
                    d01 = new_grid.get_sauerstoff_total();
                    a01 = grid.get_methan();
                    reaktion_atmos++;
                }
            new_grid.copy_grid2(grid.v2,grid); 
        //Ende: Sauerstoff wird vom Methan und anderen Substanzen verbraucht

        //Anfang: Vulkanismus
            int vulkanismus = 0;
            vulkanismus = new_grid.volcanism(grid.get_sauerstoff_total(),a);
            new_grid.set_sauerstoff_total(vulkanismus);
            new_grid.copy_grid2(grid.v2,grid); 
        //Ende Vulkanismus

        }
   		std::cout << "Simulation erfolgreich abgeschlossen." << "\n";
    	return 0;
	}