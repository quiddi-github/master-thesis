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
 // Das Grid enthält 329*654 Zellen, davon gehören 215.166 Zellen zur Welt, diese können Wasser oder Festland sein.
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
    //Weltkarten laden
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
        grid.make_new_file("ausgabe/density0");
        grid.make_new_file("ausgabe/density1");
        grid.make_new_file("ausgabe/density2");
        grid.make_new_file_sauerstoff("ausgabe/density");
        grid.make_new_file_eisen("ausgabe/density");
        grid.make_new_file_proteobacteria("ausgabe/density");
        grid.make_new_file_methan("ausgabe/density");
        grid.make_new_file_cyanobakterien("ausgabe/density");
        grid.make_new_file_sauerstoff_total("ausgabe/density");
        grid.make_new_file_landschaft("ausgabe/density");
    //Ende: Array in Datei schreiben

    //Anfang: Diffusion für Start    
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
    //Ende: Diffusion für Start

    //Methan detzen    
        grid.set_methan(14580000); //Bitte unten auch verändern in der print_in_density

//Beginn eigentliche Schleife    
     for(int a=0;a<2000;a++)
        {  
            if(0==a%10)
                {
                    std::cout << "Schritt:"<< a << "\n";  
                }

       //Anfang: Print realisieren
            grid.print_density_in_file("ausgabe/density0", a,0);
            grid.print_density_in_file("ausgabe/density1", a,1);
            grid.print_density_in_file("ausgabe/density2", a,2);
            grid.print_density_in_file_sauerstoff("ausgabe/density", a);
            grid.print_density_in_file_eisen("ausgabe/density", a);
            grid.print_density_in_file_proteobacteria("ausgabe/density", a);
            grid.print_density_in_file_methan("ausgabe/density", a,14580000 );
            grid.print_density_in_file_cyanobakterien("ausgabe/density",a);
            grid.print_density_in_file_sauerstoff_total("ausgabe/density", a, 14580000);
            grid.print_density_in_file_landschaft("ausgabe/density", a, 3*29575);
        // Alle 10 Zeitschritte  das Grid abspeichern           
            if(0==a%10)
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
                    string s= "ausgabe/Simulation_Sauerstoff"+ to_string(a);
                    string e= "ausgabe/Simulation_Eisen_"+ to_string(a);
                    string p= "ausgabe/Proteobakterien_"+ to_string(a);
                    string c= "ausgabe/Cyanobakterien_"+ to_string(a);
                    grid.set_oxygen(0,0,1);
                    grid.set_oxygen(0,1,0);
                    grid.set_iron(0,0,1);
                    grid.set_iron(0,1,0);                    
                    
                    grid.print_grid_in_file_mathematica3(s, [](Feld_Ca & feld ){return feld.sauerstoff;});
                    grid.print_grid_in_file_mathematica3(e, [](Feld_Ca & feld ){return feld.eisen;});
                    grid.print_grid_in_file_mathematica3(p, [](Feld_Ca & feld ){return feld.zustand_proteobacteria;});
                    grid.print_grid_in_file_mathematica3(c, [](Feld_Ca & feld ){return feld.zustand_cyanobakterien;});
                    grid.set_oxygen(0,0,new_grid.get_oxygen(0,0));
                    grid.set_oxygen(0,1,new_grid.get_oxygen(0,1));
                    grid.set_iron(0,0,new_grid.get_iron(0,0));
                    grid.set_iron(0,1,new_grid.get_iron(0,1));
                }   
       //Ende: Print realisieren

        //Diffusion für Sauerstoff und Eisen
            for (int i1=0; i1<grid.imax; i1++)
                {
                    for (int j1=0; j1<grid.jmax; j1++)
                        { 
                            float d =0;
                            float e = 0;
                            d= grid.diffusion_sauerstoff(i1,j1,[](Feld_Ca & feld ){return feld.sauerstoff;},0.25000000);
                            new_grid.set_oxygen(i1,j1,d);
                            e= grid.diffusion(i1,j1,[](Feld_Ca & feld ){return feld.eisen;},0.25000000);
                            new_grid.set_iron(i1,j1,e);               
                        }
                }
            new_grid.copy_grid2(grid.v2,grid);
        //Ende: Diffusion für Sauerstoff und Eisen   

        //Anfang: Cyanobakterien produzieren Sauerstoff    
            for (int i1=0; i1<grid.imax; i1++)
                {
                    for (int j1=0; j1<grid.jmax; j1++)
                        {               
                            if (grid.get_state_cyanobakterien(i1,j1)==1)
                                {
                                    float b= grid.get_oxygen(i1,j1);                                      
                                         if(b<0.99)
                                            {
                                                float iro23 = 0;
                                                iro23 = grid.get_iron(i1,j1);
                                                    if(iro23>=0.0001)
                                                        {
                                                            if(rand() % 2 == 1)
                                                                {
                                                                    new_grid.set_iron(i1,j1,iro23-0.0001);//0.0001);
                                                                }
                                                            else
                                                                {
                                                                    new_grid.set_oxygen(i1,j1,b+0.0222);
                                                                }
                                                        }
                                                    else
                                                        {
                                                            new_grid.set_oxygen(i1,j1,b+0.0222);
                                                        }
                                                if(rand() % 2 == 1)
                                                    {
                                                        new_grid.set_new_cyanobacteria_neighbour(i1, j1);
                                                    }
                                            }
                                        else
                                            {    
                                                if(grid.get_sauerstoff_total()<=14580000)
                                                    {
                                                        new_grid.set_sauerstoff_total(grid.get_sauerstoff_total()+5);
                                                        if(rand() % 2 == 1){new_grid.set_new_cyanobacteria_neighbour(i1, j1);}
                                                    }
                                            }              
                                }            
                        }
                }
            new_grid.copy_grid2(grid.v2,grid);
        //Ende: Cyanobakterien produzieren Sauerstoff  

        // Anfang: Fe2+ reagiert mit Sauerstoff
            for (int i1=0; i1<grid.imax; i1++)
                { 
                //Hier Werte für Sauerstoff und Eisen setzen, wie sie pro Zeitintervall abnehmen
                    for (int j1=0; j1<grid.jmax; j1++)
                        { 
                            float sauerstoff = grid.get_oxygen(i1,j1);
                            float eisen = grid.get_iron(i1,j1);
                            if(eisen>0 && sauerstoff > 0)
                                {
                                    if (sauerstoff > eisen)
                                        {
                                            new_grid.set_iron(i1,j1,0);
                                            new_grid.set_oxygen(i1,j1,sauerstoff-eisen);
                                        }
                                    if (eisen > sauerstoff)
                                        {
                                            new_grid.set_iron(i1,j1,eisen-sauerstoff);
                                            new_grid.set_oxygen(i1,j1,0);
                                        }
                                    if (eisen == sauerstoff)
                                        {
                                            new_grid.set_iron(i1,j1,0);
                                            new_grid.set_oxygen(i1,j1,0);
                                        }
                                }
                        }
                }  
            new_grid.copy_grid2(grid.v2,grid);
        // Ende: Fe2+ reagiert mit Sauerstoff

        //Anfang: Proteokbakterien brauchen Eisen für die Photosynthese
            for (int i1=0; i1<grid.imax; i1++)
                {
                    for (int j1=0; j1<grid.jmax; j1++)
                        { 
                            float b=0;
                            b = grid.get_iron(i1,j1);
                            if (grid.get_state_proteobacteria(i1,j1)==1 && b >=0.0001)
                                {  
                                    new_grid.set_iron(i1,j1,b-0.0001);
                                    new_grid.set_new_proteobacteria_neighbour(i1,j1);
                                        
                                }
                        }
                }
            new_grid.copy_grid2(grid.v2,grid);
        //Ende: Proteokbakterien brauchen Eisen für die Photosynthese
    
        //Anfang: Proteokbakterien sterben bei zuviel Sauerstoff
            for (int i1=0; i1<grid.imax; i1++)
                {
                    for (int j1=0; j1<grid.jmax; j1++)
                        { 
                            float b=0;
                            b = grid.get_oxygen(i1,j1);
                            if (grid.get_state_proteobacteria(i1,j1)==1 && b >=0.08)
                                {   
                                    new_grid.set_proteobacteria(i1,j1, 0);  
                                }
                        }
                }
            new_grid.copy_grid2(grid.v2,grid);
        //Ende: Proteokbakterien sterben bei zuviel Sauerstoff 

        //Anfang: Sauerstoff wird vom Methan und anderen Substanzen verbraucht
                    float d01 = 0;
                    int a01=0;
                    d01 = grid.get_sauerstoff_total();
                    a01 = grid.get_methan();
                    while(a01>0 && d01>0)
                        {                        
                                    new_grid.set_sauerstoff_total(d01-2);
                                    grid.set_methan(a01-1);
                                    d01 = new_grid.get_sauerstoff_total();
                                    a01 = grid.get_methan();
                        }
            new_grid.copy_grid2(grid.v2,grid); 
        //Ende: Sauerstoff wird vom Methan und anderen Substanzen verbraucht

        //Anfang: Black Smoker
            new_grid.activate_black_smocker(a, 30);
            new_grid.copy_grid2(grid.v2,grid); 
        //Ende: Black Smoker

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