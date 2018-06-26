#include <iostream>
#include <vector>
using namespace std;
#include <unistd.h>
#include <random>
#include <math.h>


Grid::Grid(){}
Grid::~Grid(){}

    bool Grid::get_randomizer(){return randomizer2;}
    int Grid::methan_total = 0;
    int Grid::sauerstoff_total = 0;   

    void Grid::set_oxygen(int i1, int j1, float d){v2[i1][j1].sauerstoff = d;}
    void Grid::set_iron(int i1, int j1, float d){v2[i1][j1].eisen = d;}
    void Grid::set_proteobacteria(int i1, int j1, int d){v2[i1][j1].zustand_proteobacteria = d;}
    void Grid::set_state_cyanobakterien(int i1, int j1, int d){v2[i1][j1].zustand_cyanobakterien = d;}
    void Grid::set_methan(int z){methan = z;}
    int Grid::get_methan(){return methan;}
    void Grid::set_randomizer(bool a){randomizer2 = a; if (a){rand_r();}}
    int Grid::get_state_cyanobakterien(int i1, int j1){return v2[i1][j1].zustand_cyanobakterien;}
    int Grid::get_state_proteobacteria(int i1, int j1){return v2[i1][j1].zustand_proteobacteria;}
    void Grid::set_state_proteobacteria(int i1, int j1, int s){v2[i1][j1].zustand_proteobacteria = s;}
    float Grid::get_oxygen(int i1, int j1){return v2[i1][j1].sauerstoff;}
    float Grid::get_iron(int i1, int j1){return v2[i1][j1].eisen;}          
    void Grid::set_prison(int i1, int j1, float d){v2[i1][j1].zustand_prison = d;}
    int Grid::get_prison(int i1, int j1){return v2[i1][j1].zustand_prison;}
    void Grid::set_prison_cooperate(int i1, int j1, bool d){v2[i1][j1].prison_cooperate = d;}
    bool Grid::get_prison_cooperate(int i1, int j1){return v2[i1][j1].prison_cooperate;}
    int Grid::get_prison_punkte(int i1, int j1){return v2[i1][j1].prison_punkte;}
    void Grid::set_prison_punkte(int i1, int j1, int d){v2[i1][j1].prison_punkte = d;}
    void Grid::set_sauerstoff_total(int a){sauerstoff_total = a;}
    int Grid::get_sauerstoff_total(){return sauerstoff_total;}
    std::vector<std::vector<Feld_Ca>> Grid::get_v2(){return v2;}
    void Grid::set_v2(std::vector<std::vector<Feld_Ca>> a){v2 = a;}
    void Grid::set_sauerstoff_ocean(float d){sauerstoff_ocean= d;}
    void Grid::set_eisen_ocean(float d){eisen_ocean= d;}
    float Grid::get_sauerstoff_ocean(){return sauerstoff_ocean;}
    float Grid::get_eisen_ocean(){return eisen_ocean;}




    void Grid::rand_r()
    	{
        if (get_randomizer())
          {

          } 
        else
          {
		       time_t seconds;
		       time(&seconds);
		       srand((unsigned int) seconds);                        
          }
    	}    

    void Grid::set_new_proteobacteria_neighbour(int i1, int j1)
      {
        std::random_device rd1;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen1(rd1()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> dis1(0, 3);
        if (i1<=(imax-2) && i1>=1 && j1<=(jmax-2) && j1>=1 && (rand() % 1000<=3) && innerhalb_welt (i1, j1))
    			{ 
            bool ind = true;
            while (ind)
              {
                int nach = 0;
                nach = dis1(gen1);                                      
                if (((get_state_proteobacteria(i1-1,j1)==1)  || (get_state_cyanobakterien(i1-1, j1)==1)) && ((get_state_proteobacteria(i1+1,j1)==1)  || (get_state_cyanobakterien(i1+1, j1)==1)) && ((get_state_proteobacteria(i1,j1+1)==1)  || (get_state_cyanobakterien(i1, j1+1)==1))&& ((get_state_proteobacteria(i1,j1-1)==1)  || (get_state_cyanobakterien(i1, j1-1)==1)))
                  {
                    ind = false;
                  }
                else
                  {
                    if (nach == 3)
                      {
                        if (get_state_proteobacteria(i1-1,j1)==0 && get_state_cyanobakterien(i1-1, j1)==0 && i1<=imax && i1>=1 && j1<=jmax && j1>=0  && (wasser_ja_nein(i1-1, j1, imax, jmax))){set_state_proteobacteria(i1-1, j1, 1); ind = false;}
                      }
                    else
                      {
                        if (nach == 1)
                                  {
                                    if (get_state_proteobacteria(i1+1,j1)==0 && get_state_cyanobakterien(i1+1, j1)==0 && i1<=(imax-1) && i1>=0 && j1<=jmax && j1>=0 && (wasser_ja_nein(i1+1, j1, imax, jmax))){set_state_proteobacteria(i1+1, j1, 1); ind = false;}
                                  }
                        else
                          {
                            if (nach == 2)
                              {
                                if (get_state_proteobacteria(i1,j1-1)==0 && get_state_cyanobakterien(i1, j1-1)==0  && i1<=imax && i1>=0 && j1<=jmax && j1>=1 && (wasser_ja_nein(i1, j1-1, imax, jmax))){set_state_proteobacteria(i1, j1-1, 1); ind = false;}
                              }
                            else
                              {
                                if (nach == 0)
                                  {
                                    if (get_state_proteobacteria(i1,j1+1)==0 &&  get_state_cyanobakterien(i1, j1+1)==0 && i1<=imax && i1>=0 && j1<=(jmax-1) && j1>=0 && (wasser_ja_nein(i1, j1+1, imax, jmax))){set_state_proteobacteria(i1, j1+1, 1); ind = false;}
                                    ind = false;
                                  }
                              }
                          }
                      }
                  }
              }
          }
      }

    void Grid::set_new_cyanobacteria_neighbour(int i1, int j1)
      { 
        std::random_device rd2;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen2(rd2()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> dis2(0, 3);
        if (i1<=(imax-2) && i1>=1 && j1<=(jmax-2) && j1>=1 && (rand() % 1000<=3)&& innerhalb_welt (i1, j1))
          {
            bool ind = true;
            while(ind)
              {
                int nach = 0;
                  nach = dis2(gen2); 
                  if (((get_state_proteobacteria(i1-1,j1)==1)  || (get_state_cyanobakterien(i1-1, j1)==1)) && ((get_state_proteobacteria(i1+1,j1)==1)  || (get_state_cyanobakterien(i1+1, j1)==1)) && ((get_state_proteobacteria(i1,j1+1)==1)  || (get_state_cyanobakterien(i1, j1+1)==1))&& ((get_state_proteobacteria(i1,j1-1)==1)  || (get_state_cyanobakterien(i1, j1-1)==1)))
                    {
                      ind = false;
                    }
                  else
                    {
                      if (nach == 3)
                        {
                          if (get_state_proteobacteria(i1-1,j1)==0 && get_state_cyanobakterien(i1-1, j1)==0 && i1<=imax && i1>=1 && j1<=jmax && j1>=0  && (wasser_ja_nein(i1-1, j1, imax, jmax))){set_state_cyanobakterien(i1-1, j1, 1); ind = false;}
                        }
                      else
                        {
                          if (nach == 1)
                            {
                              if (get_state_proteobacteria(i1+1,j1)==0 && get_state_cyanobakterien(i1+1, j1)==0 && i1<=(imax-1) && i1>=0 && j1<=jmax && j1>=0 && (wasser_ja_nein(i1+1, j1, imax, jmax))){set_state_cyanobakterien(i1+1, j1, 1); ind = false;}
                            }
                          else
                           {
                              if (nach == 2)
                                  {
                                    if (get_state_proteobacteria(i1,j1-1)==0 && get_state_cyanobakterien(i1, j1-1)==0  && i1<=imax && i1>=0 && j1<=jmax && j1>=1 && (wasser_ja_nein(i1, j1-1, imax, jmax))){set_state_cyanobakterien(i1, j1-1, 1); ind = false;}
                                  }
                              else
                                {
                                  if (nach == 0)
                                    {
                                      if (get_state_proteobacteria(i1,j1+1)==0 &&  get_state_cyanobakterien(i1, j1+1)==0 && i1<=imax && i1>=0 && j1<=(jmax-1) && j1>=0 && (wasser_ja_nein(i1, j1+1, imax, jmax))){set_state_cyanobakterien(i1, j1+1, 1); ind = false;}
                                      ind = false;
                                    }
                                }
                            }
                        }
                    }
              }
          }
      }      
    
    int Grid::roundnew(double d)
      {
        return floor(d+0.5);
      }              

    void Grid::set_random_grid_mit_karte(std::string name, int a)
      {
      	state= a;
      	read_map(name);
      // Anfang: Methode 2 zufallszahlen für Eisen:
        std::random_device rd;
        std::default_random_engine generator;
        generator.seed(rd());
        std::normal_distribution<double> distribution(30000,15000);
        std::normal_distribution<double> distribution2(40,10);
        std::normal_distribution<double> distribution3(60,10);
      // Ende: Methode 2 zufallszahlen für Eisen:

      //Anfang: Zufallszahlen von 0-1 z.B. f�r Eisen 
        for (int i1=0; i1<imax; i1++)
          {
            for (int j1=0; j1<jmax; j1++)   
              { 
                float d = 0;//(rand() % 10001 );
                float randxx = 0;
                float randproteo = 0;
                float randcyano = 0;
                if (innerhalb_welt (i1, j1))
                  {
                    randxx = roundnew(distribution(generator));
                    if (randxx>0)
                      {
                        d= randxx/100000;
                      }
                  }
      // Ende: Zufallszahlen von 0-1 z.B. f�r Eisen 
                v2[i1][j1].sauerstoff = 0;
                v2[i1][j1].eisen = d;
                set_prison_cooperate(i1, j1, true);      
              if (wasser_ja_nein (i1,j1, imax, jmax))
            	   {
                    randcyano = roundnew(distribution2(generator));
                    randproteo = roundnew(distribution3(generator));
            		  //Mit einer Wahrscheinlichkeit von xy Proteos und Cyanos auf Wasser setzen
                    if (rand() % 2 == 1)
                      { 
                        if (randcyano < 50)
                          {
                            v2[i1][j1].zustand_cyanobakterien = 0;
                          }
                        else
                          {
                            v2[i1][j1].zustand_cyanobakterien = 1;
                          }
                      }
                    else
                      {
                        if (randproteo < 50)
                          {
                              v2[i1][j1].zustand_proteobacteria = 0;
                          }
                        else
                          {
                            v2[i1][j1].zustand_proteobacteria = 1;
                          }
                      } 
            	    }
              else
                {
                  v2[i1][j1].landschaft = 10;
                }      
              }
      	  }
      }

    bool Grid::wasser_ja_nein (int i, int j, int x, int y)
      {
        int value = (i*y)+j;
        if ((vector_map)[value]==1){return true;}
        else {return false;}
      }

    bool Grid::innerhalb_welt (int i, int j)
      {
        int value = (i*jmax)+j;
        if ((vector_map)[value]==2){return false;}
        else {return true;}
      }

    void Grid::read_map(std::string name) 
      {
        int foo;
        ifstream ifs;
        try
          {
            ifs.open(name);
            while (!ifs.eof())
              {
                ifs >> foo;
                vector_map.push_back(foo);
              }
            (vector_map).resize(jmax*imax);
            fstream f;
            f.open("rueckgabe", ios::out);               
            for (int i1=0; i1<(imax); i1++)
              {  
                for (int j1=0; j1<(jmax); j1++)   
                  { 
                    f<<  (vector_map)[(i1*jmax)+j1] << ",";
                  }
                  if (i1<(imax-1)){f<<  (vector_map)[(i1*jmax)+jmax-1]<< "\n";}
                  if (i1==(imax-1)){f<<  (vector_map)[(i1*jmax)+jmax-1];}
              }              
            f.close();  
          }
        catch (...)
          {
            cout << "Fehler beim Einlesen der Karte";
          }
        ifs.close();
      }

    void Grid::set_random_grid2(std::string name, int a)
      { 
        read_map(name);
          for (int i1=0; i1<imax; i1++)
            {
              for (int j1=0; j1<jmax; j1++)   
                {
                  int value = (i1*jmax)+j1;
                  if (vector_map[value]!=2)
                    {
                      vector_map[value] = rand() % 2 + 0;
                    }
                }
            }      
          std::random_device rd;
          std::default_random_engine generator;
          generator.seed(rd());
          std::normal_distribution<double> distribution(30000,15000);
          std::normal_distribution<double> distribution2(40,10);
          std::normal_distribution<double> distribution3(60,10);
          for (int i1=0; i1<imax; i1++)
            {
              for (int j1=0; j1<jmax; j1++)   
                { 
                  float d = 0;//(rand() % 10001 );
                  float randxx = 0;
                  float randproteo = 0;
                  float randcyano = 0;
                  if (innerhalb_welt (i1, j1))
                    {
                      randxx = roundnew(distribution(generator));
                      if (randxx>0)
                        {
                          d= randxx/100000;
                        }
                    }
                  v2[i1][j1].sauerstoff = 0;
                  v2[i1][j1].eisen = d;
                  set_prison_cooperate(i1, j1, true); 
                  if (wasser_ja_nein (i1,j1, imax, jmax))
                    {
                      randcyano = roundnew(distribution2(generator));
                      randproteo = roundnew(distribution3(generator));
                    //Mit einer Wahrscheinlichkeit von xy Proteos und Cyanos auf Wasser setzen
                      if (rand() % 2 == 1)
                        { 
                          if (randcyano < 50)
                            {
                              v2[i1][j1].zustand_cyanobakterien = 0;
                            }
                          else
                            {
                              v2[i1][j1].zustand_cyanobakterien = 1;
                            }
                        }
                      else
                        {
                          if (randproteo < 50)
                            {
                              v2[i1][j1].zustand_proteobacteria = 0;
                            }
                          else
                            {
                              v2[i1][j1].zustand_proteobacteria = 1;
                            }
                        } 
                    }
                  else
                    {
                      v2[i1][j1].landschaft = 10;
                    }
          	    }
          	}
      }

    template<typename F>
    float Grid::get_universal(int i1, int j1, F func){return func(v2[i1][j1]);}  
    void Grid::copy_grid2(std::vector<std::vector<Feld_Ca>> &x, Grid &b)
    	{
        int value = 0;
        b.anzahl_black_smoker = anzahl_black_smoker;
        b.flaeche_welt = flaeche_welt;
        for (int i1 = 0; i1 < anzahl_black_smoker; ++i1){b.smoker_x[i1] = smoker_x[i1]; b.smoker_y[i1] = smoker_y[i1];}
        for (int j1=0; j1<jmax; j1++)
          {
          	for (int i1=0; i1<imax; i1++)   
            	{ 
                value = (i1*jmax)+j1;
          		  x[i1][j1].sauerstoff= v2[i1][j1].sauerstoff;
          		  x[i1][j1].eisen= v2[i1][j1].eisen;
          		  x[i1][j1].zustand_cyanobakterien = v2[i1][j1].zustand_cyanobakterien;
          		  x[i1][j1].zustand_proteobacteria = v2[i1][j1].zustand_proteobacteria;
                b.set_sauerstoff_total(get_sauerstoff_total());
                b.vector_map[value] = vector_map[value]; 
                x[i1][j1].landschaft = v2[i1][j1].landschaft;
 	            }
      	  }
      }            

   	template<typename F>   
    float Grid::diffusion(int i, int j, F func, float d)
    	{
        if (innerhalb_welt (i, j))
          {          
        	  float concentration=0;
      		  if ((imax-1>i)&&(i>0)&&(jmax-1>j)&&(j>0))
              {
                concentration=d*(-4*func(v2[i][j])+func(v2[i-1][j])+func(v2[i+1][j])+func(v2[i][j-1])+func(v2[i][j+1]));
          		}
      		  if ((imax-1==i)&&(jmax-1>j)&&(j>0))
              {
                concentration=d*(-3*func(v2[i][j])+func(v2[i-1][j])+func(v2[i][j-1])+func(v2[i][j+1]));
          	  }
      	    if ((i==0)&&(jmax-1>j)&&(j>0))
              {
                concentration=d*(-3*func(v2[i][j])+func(v2[i+1][j])+func(v2[i][j-1])+func(v2[i][j+1]));         
          	  }
      		  if ((imax-1>i)&&(i>0)&&(jmax-1==j))
              {
                concentration=d*(-3*func(v2[i][j])+func(v2[i-1][j])+func(v2[i+1][j])+func(v2[i][j-1]));         
          		}
      		  if ((imax-1>i)&&(i>0)&&(j==0))
              {
                concentration=d*(-3*func(v2[i][j])+func(v2[i-1][j])+func(v2[i+1][j])+func(v2[i][j+1]));         
          	  }
      		  if ((imax-1==i)&&(jmax-1==j))
        	   {
              concentration=d*(-2*func(v2[i][j])+func(v2[i-1][j])+func(v2[i][j-1]));        
              }
            if ((0==i)&&(0==j))
       			  {
                concentration=d*(-2*func(v2[i][j])+func(v2[i+1][j])+func(v2[i][j+1]));        
          	  } 
      		  return (concentration + func(v2[i][j]));
          }
        return 0;
      }

    template<typename F>   
    float Grid::diffusion_sauerstoff(int i, int j, F func, float d)
      { 
        if (innerhalb_welt (i, j))
          {
            float concentration=0;
            if ((imax-1>i) && (i>0) && (jmax-1>j) && (j>0) && (wasser_ja_nein(i-1, j, imax, jmax)) && (wasser_ja_nein(i+1, j, imax, jmax)) && (wasser_ja_nein(i, j+1, imax, jmax)) && (wasser_ja_nein(i, j-1, imax, jmax)) )
              {
                concentration=d*(-4*func(v2[i][j])+func(v2[i-1][j])+func(v2[i+1][j])+func(v2[i][j-1])+func(v2[i][j+1]));
              }
            if ((imax-1==i)&&(jmax-1>j)&&(j>0)&& (wasser_ja_nein(i-1, j, imax, jmax)) && (wasser_ja_nein(i, j+1, imax, jmax)) && (wasser_ja_nein(i, j-1, imax, jmax)))
              {
                concentration=d*(-3*func(v2[i][j])+func(v2[i-1][j])+func(v2[i][j-1])+func(v2[i][j+1]));
              }
            if ((i==0)&&(jmax-1>j)&&(j>0) && (wasser_ja_nein(i+1, j, imax, jmax)) && (wasser_ja_nein(i, j+1, imax, jmax)) && (wasser_ja_nein(i, j-1, imax, jmax)))
              {
              concentration=d*(-3*func(v2[i][j])+func(v2[i+1][j])+func(v2[i][j-1])+func(v2[i][j+1]));         
              }
            if ((imax-1>i)&&(i>0)&&(jmax-1==j) && (wasser_ja_nein(i-1, j, imax, jmax)) && (wasser_ja_nein(i+1, j, imax, jmax)) && (wasser_ja_nein(i, j-1, imax, jmax)))
              {
                concentration=d*(-3*func(v2[i][j])+func(v2[i-1][j])+func(v2[i+1][j])+func(v2[i][j-1]));         
              }
            if ((imax-1>i)&&(i>0)&&(j==0)&& (wasser_ja_nein(i-1, j, imax, jmax)) && (wasser_ja_nein(i, j+1, imax, jmax)))
              {
                concentration=d*(-3*func(v2[i][j])+func(v2[i-1][j])+func(v2[i+1][j])+func(v2[i][j+1]));         
              }
            if ((imax-1==i)&&(jmax-1==j) && (wasser_ja_nein(i-1, j, imax, jmax)) && (wasser_ja_nein(i, j-1, imax, jmax)))
              {
                concentration=d*(-2*func(v2[i][j])+func(v2[i-1][j])+func(v2[i][j-1]));        
              }
            if ((0==i)&&(0==j) && (wasser_ja_nein(i+1, j, imax, jmax)) && (wasser_ja_nein(i, j+1, imax, jmax)) )
              {
                concentration=d*(-2*func(v2[i][j])+func(v2[i+1][j])+func(v2[i][j+1]));        
              } 
            return (concentration + func(v2[i][j]));
          }
        return 0;
      }

  	void Grid::set_grid2(int i, int j, int anzahl)
      {   
        v2.reserve(i);
        for(int i1=0;i1<i;i1++) v2[i1].reserve(j);          
        imax = i; jmax = j;
        std::cout << jmax << "\n";
        smoker_x.reserve(anzahl);
        smoker_y.reserve(anzahl);        
      }

    void Grid::print_grid_in_file_mathematica2(std::string dateiname)
    	{     
    		fstream f;
        f.open(dateiname, ios::out);                   
        for (int i1=0; i1<(imax); i1++)
          {  
           	for (int j1=0; j1<(jmax); j1++)   
              { 
                f<<  v2[i1][j1].sauerstoff << ",";
              }
            if (i1<(imax-1)){f<<  v2[i1][jmax-1].sauerstoff << "\n";}
            if (i1==(imax-1)){f<<  v2[i1][jmax-1].sauerstoff;}
          }
                           
        f.close();                              
    	}

    template<typename F> 
    void Grid::print_grid_in_file_mathematica3(std::string dateiname, F func)
    	{
    	  fstream f;
        f.open(dateiname, ios::out);        
        for (int i1=0; i1<(imax); i1++)
          {  
          	for (int j1=0; j1<(jmax-1); j1++)   
              { 
                f<<  func(v2[i1][j1]) << ",";
              }
            if (i1<(imax-1)){f<<  func(v2[i1][jmax-1]) << "\n";}
            if (i1==(imax-1)){f<<  func(v2[i1][jmax-1]);}
          }                           
        f.close();                              
    	}

    int Grid::count_neighbours(int i, int j, int state2)
      { 
        int neighbours=0;
        int i1; int j1;	
      	if ((imax-1>i)&&(i>0)&&(jmax-1>j)&&(j>0))
      		{
        		for (j1=j-1; j1<=j+1; j1++)
        			{
        				for (i1=i-1; i1<=i+1; i1++)   
        					{ 
              			if (v[i1][j1]== state2){neighbours++;}
          				}
          		}
          }
      	if ((imax-1==i)&&(jmax-1>j)&&(j>0))
      		{
          	for (j1=j-1; j1<=j+1; j1++)
              {
          			for (i1=i-1; i1<=i; i1++)   
          				{ 
              			if (v[i1][j1]== state2){neighbours++;}
          				}
          		}
        	}
      	if ((i==0)&&(jmax-1>j)&&(j>0))
      		{
          	for (j1=j-1; j1<=j+1; j1++)
          		{
            		for (i1=0; i1<=i+1; i1++)   
          				{ //std::cout << i1<< j1<< v[i1][j1] << "\n";
            				if (v[i1][j1]== state2){neighbours++;}
          				}
          		}
          }
      	if ((imax-1>i)&&(i>0)&&(jmax-1==j))
      		{
        		for (j1=j-1; j1<=j; j1++)
        			{
        				for (i1=i-1; i1<=i+1; i1++)   
        					{ 
              			if (v[i1][j1]== state2){neighbours++;}
          				}
          		}
          }
      	if ((imax-1>i)&&(i>0)&&(j==0))
      		{
        		for (j1=0; j1<=j+1; j1++)
        			{
        				for (i1=i-1; i1<=i+1; i1++)   
        					{ 
         						if (v[i1][j1]== state2){neighbours++;}
          				}
          		}
          }
      	if ((imax-1==i)&&(jmax-1==j))
      		{
          	for (j1=j-1; j1<=j; j1++)
          		{
          			for (i1=i-1; i1<=i; i1++)   
          				{ 
          					if (v[i1][j1]== state2){neighbours++;}
          				}
          		}
          }
       		if ((0==i)&&(0==j))
       			{
          		for (j1=0; j1<=j+1; j1++)
          			{
          				for (i1=0; i1<=i+1; i1++)   
          					{ 
              				if (v[i1][j1]== state2){neighbours++;}
          					}
          			}
          	}  
          if (i< imax && j<jmax){ if (v[i][j]==state2){neighbours--;}}
      		return neighbours;
      	}

    int Grid::count_neighbours_cyanobacteria(int i, int j)
      { 
        int neighbours=0;    
          if ((imax-1>i)&&(i>0)&&(jmax-1>j)&&(j>0))
            {
              if (v2[i-1][j].zustand_cyanobakterien == 1)
                {
                  neighbours++;
                }
              if (v2[i+1][j].zustand_cyanobakterien == 1)
                {
                  neighbours++;
                }
              if (v2[i][j+1].zustand_cyanobakterien == 1)
                {
                  neighbours++;
                }
              if (v2[i][j-1].zustand_cyanobakterien == 1)
                {
                  neighbours++;
                }
            }
          if ((imax-1==i)&&(jmax-1>j)&&(j>0))
            {
              if (v2[i-1][j].zustand_cyanobakterien == 1)
                {
                  neighbours++;
                }
              if (v2[i][j+1].zustand_cyanobakterien == 1)
                {
                  neighbours++;
                }
              if (v2[i][j-1].zustand_cyanobakterien == 1)
                {
                  neighbours++;
                }                
            }
          if ((i==0)&&(jmax-1>j)&&(j>0))
            {
              if (v2[i+1][j].zustand_cyanobakterien == 1)
                {
                  neighbours++;
                }
              if (v2[i][j+1].zustand_cyanobakterien == 1)
                {
                  neighbours++;
                }
              if (v2[i][j-1].zustand_cyanobakterien == 1)
                {
                  neighbours++;
                }  
            }
          if ((imax-1>i)&&(i>0)&&(jmax-1==j))
            {
              if (v2[i-1][j].zustand_cyanobakterien == 1)
                {
                  neighbours++;
                }
              if (v2[i+1][j].zustand_cyanobakterien == 1)
                {
                  neighbours++;
                }
              if (v2[i][j-1].zustand_cyanobakterien == 1)
                {
                  neighbours++;
                }                
            }
          if ((imax-1>i)&&(i>0)&&(j==0))
            {
              if (v2[i-1][j].zustand_cyanobakterien == 1)
                {
                  neighbours++;
                }
              if (v2[i+1][j].zustand_cyanobakterien == 1)
                {
                  neighbours++;
                }
              if (v2[i][j+1].zustand_cyanobakterien == 1)
                {
                  neighbours++;
                }        
            }
          if ((imax-1==i)&&(jmax-1==j))
            {
              if (v2[i-1][j].zustand_cyanobakterien == 1)
                {
                  neighbours++;
                }
              if (v2[i][j-1].zustand_cyanobakterien == 1)
                {
                  neighbours++;
                }                
            }
          if ((0==i)&&(0==j))
            {
              if (v2[i+1][j].zustand_cyanobakterien == 1)
                {
                  neighbours++;
                }
              if (v2[i][j+1].zustand_cyanobakterien == 1)
                {
                  neighbours++;
                }
            }  
          return neighbours;
        }

    void Grid::speichern(std::string dateiname,std::string daten, std::string header)
    	{   
    		fstream f;
        f.open(dateiname, ios::out);
        f<< header << endl;
        f << daten << endl;
        f.close();                     
      }

    void Grid::set_random_grid(int a)
        { 
       		state= a;
          	for (int j1=0; j1<jmax; j1++)
          		{
          			for (int i1=0; i1<imax; i1++)   
          				{ 
              				v[i1][j1] = rand()% state + 0;
          				}
          		}
      	}

    void Grid::print_grid_terminal()
    	{
    		for (int i1=0; i1<imax; i1++)
        	{
        		for (int j1=0; j1<jmax; j1++)   
        			{ 
        				std::cout << v[i1][j1] << " ";
        			}
         		std::cout << "\n";
        	}
    	}

    void Grid::set_grid(int i, int j)
      { 
      	v.reserve(i);
        for(int i1=0;i1<i;i1++) v[i1].reserve(j);
      	imax = i; jmax = j;
      }

    void Grid::copy_grid(std::vector<std::vector<int>> &x){std::swap(v,x);}

    void Grid::print_grid_in_file(std::string dateiname, std::string header)
    	{   
    		fstream f;
        f.open(dateiname, ios::out);
        f<< header << endl;
        for (int i1=0; i1<imax; i1++)
          {  
           	for (int j1=0; j1<jmax; j1++)   
              { 
                f<<  v[i1][j1] << " ";
              }
            f<< "\n";                           
          }
        f.close();  
    	}

    void Grid::print_grid_in_file_mathematica(std::string dateiname)
      {                       
        fstream f;
        f.open(dateiname, ios::out);                
        for (int i1=0; i1<(imax); i1++)
          {  
            for (int j1=0; j1<(jmax); j1++)   
              { 
                f<<  v[i1][j1] << ",";
              }
            if (i1<(imax-1)){f<<  v[i1][jmax-1] << "\n";}
            if (i1==(imax-1)){f<<  v[i1][jmax-1];}
          }                 
        f.close();  
      }

    void Grid::print_density_in_file(std::string dateiname, int step, int state2)
    	{   
    		int density=0;
    		double b=0;   
        fstream f;
        f.open(dateiname, ios::out|ios::app);
        f << to_string(step) << ",";
        for (int i1=0; i1<imax; i1++)
          {  
           	for (int j1=0; j1<jmax; j1++)   
              { 
                if (v[i1][j1]==state2){density++;}
              }
          }
        b= 1.000000*density/(get_flaeche());
        f<< to_string(b) <<"\n";
        f.close();  
    	}

    void Grid::make_new_file(std::string dateiname)
    	{ 
      	fstream f;
        if ( remove( dateiname.c_str() ) != 0 )
    	   	perror( "Error deleting file" );
  			else
    			puts( "File successfully deleted" );
        f.open(dateiname, ios::out|ios::app);
        f.clear();
        f.close();  
    	}

	void Grid::make_new_file_sauerstoff(std::string dateiname)
    	{ 
        	fstream f;
        	string dateinamesauerstoff = dateiname + "_Sauerstoff";        
            if ( remove( dateinamesauerstoff.c_str() ) != 0 )
          perror( "Error deleting file Sauerstoff" );
          else
            puts( "File successfully deleted Sauerstoff" );
              f.open(dateinamesauerstoff, ios::out|ios::app);
              f.clear();
              f.close();                     
    	}

  void Grid::make_new_file_sauerstoff_total(std::string dateiname)
    { 
      fstream f;
      string dateinamesauerstoff = dateiname + "_Sauerstoff_total";        
        if ( remove( dateinamesauerstoff.c_str() ) != 0 )
      perror( "Error deleting file Sauerstoff total" );
      else
        puts( "File successfully deleted Sauerstoff total" );
          f.open(dateinamesauerstoff, ios::out|ios::app);
          f.clear();
          f.close();                     
    }

  void Grid::make_new_file_landschaft(std::string dateiname)
    { 
      fstream f;
      string dateinamesauerstoff = dateiname + "_Landschaft";        
        if ( remove( dateinamesauerstoff.c_str() ) != 0 )
      perror( "Error deleting file Landschaft" );
      else
        puts( "File successfully deleted Landschaft" );
          f.open(dateinamesauerstoff, ios::out|ios::app);
          f.clear();
          f.close();                     
    }
    
    void Grid::make_new_file_eisen(std::string dateiname)
    	{ 
        fstream f;
        string dateiname2 = dateiname + "_Eisen";                
        if ( remove( dateiname2.c_str() ) != 0 )
    		  perror( "Error deleting file Eisen" );
  			else
    			puts( "File successfully deleted Eisen" );
        f.open(dateiname2, ios::out|ios::app);
        f.clear();
        f.close();                     
    	}

	void Grid::make_new_file_proteobacteria(std::string dateiname)
    	{ 
        	fstream f;
        	string dateiname2 = dateiname + "_Proteobacteria";                
        	if ( remove( dateiname2.c_str() ) != 0 )
            perror( "Error deleting file Proteobacterien" );
          else
            puts( "File successfully deleted Proteobakteria" );
        	f.open(dateiname2, ios::out|ios::app);
        	f.clear();
        	f.close();                     
    	}

	void Grid::make_new_file_methan(std::string dateiname)
    	{ 
        	fstream f;
        	string dateinamemethan = dateiname + "_Methan";        
        	if ( remove( dateinamemethan.c_str() ) != 0 )
            perror( "Error deleting file Methan" );
  			else
    			puts( "File successfully deleted Methan" );                          
        f.open(dateinamemethan, ios::out|ios::app);
        f.clear();
        f.close();                     
    	}

  void Grid::make_new_file_cyanobakterien(std::string dateiname)
    { 
      fstream f;
      string dateinamesauerstoff = dateiname + "_Cyanobakterien";        
      if ( remove( dateinamesauerstoff.c_str() ) != 0 )
        perror( "Error deleting file Cyanobakterien" );
      else
        puts( "File successfully deleted Cyanobakterien" );
      f.open(dateinamesauerstoff, ios::out|ios::app);
      f.clear();
      f.close();                     
    } 

	void Grid::print_density_in_file_sauerstoff(std::string dateiname, int step)
    {   
      float density=0;
    	double b=0;
    	string dateiname2 = dateiname + "_Sauerstoff";
      fstream f;
      f.open(dateiname2, ios::out|ios::app);
      f << to_string(step) << ",";
      for (int i1=0; i1<imax; i1++)
        {  
         	for (int j1=0; j1<jmax; j1++)   
            { 
              density = density + v2[i1][j1].sauerstoff;
            }         
        }
      b= 1.000000*density/(get_flaeche());
      f<< to_string(b) <<"\n";
      f.close();  
    }

  void Grid::print_density_in_file_landschaft(std::string dateiname, int step, int anfang)
    {   
      float density=0;
      double b=0;
      string dateiname2 = dateiname + "_Landschaft";
      fstream f;
      f.open(dateiname2, ios::out|ios::app);
      f << to_string(step) << ",";
      for (int i1=0; i1<imax; i1++)
        {  
          for (int j1=0; j1<jmax; j1++)   
            { 
              density = density + v2[i1][j1].landschaft;
            }         
        }
      b= 1.0000*density/(anfang);
      f<< to_string(b) <<"\n";
      f.close();  
    }

  void Grid::print_density_in_file_sauerstoff_total(std::string dateiname, int step, int anfang)
    {   
      float density=0;
      double b=0;
      string dateiname2 = dateiname + "_Sauerstoff_total";
      fstream f;
      f.open(dateiname2, ios::out|ios::app);
      f << to_string(step) << ",";
      density = sauerstoff_total;
      b= 1.000000*density/(anfang);
      f<< to_string(b) <<"\n";
      f.close();  
    }

	void Grid::print_density_in_file_proteobacteria(std::string dateiname, int step)
    {   
      int density=0;
    	double b=0;
    	string dateiname2 = dateiname + "_Proteobacteria";
      fstream f;
      f.open(dateiname2, ios::out|ios::app);
      f << to_string(step) << ",";
      for (int i1=0; i1<imax; i1++)
        {  
         	for (int j1=0; j1<jmax; j1++)   
            { 
              density = density + v2[i1][j1].zustand_proteobacteria;
            }                                                                   
        }
      b= 1.000000*density/(get_flaeche());
      f<< to_string(b) <<"\n";
      f.close();  
    	}

  void Grid::print_density_in_file_cyanobakterien(std::string dateiname, int step)
    {   
      int density=0;
      double b=0;
      string dateiname2 = dateiname + "_Cyanobakterien";
      fstream f;
      f.open(dateiname2, ios::out|ios::app);
      f << to_string(step) << ",";
      for (int i1=0; i1<imax; i1++)
        {  
          for (int j1=0; j1<jmax; j1++)   
            { 
              density = density + v2[i1][j1].zustand_cyanobakterien;
            }                                                                   
        }
      b= 1.000000*density/(get_flaeche());
      f<< to_string(b) <<"\n";
      f.close();  
    }     

	void Grid::print_density_in_file_eisen(std::string dateiname, int step)
    {   
    	float density=0;
    	double b=0;
    	string dateiname2 = dateiname + "_Eisen";
      fstream f;
      f.open(dateiname2, ios::out|ios::app);
      f << to_string(step) << ",";
      for (int i1=0; i1<imax; i1++)
        {  
         	for (int j1=0; j1<jmax; j1++)   
            { 
              density = density + v2[i1][j1].eisen;
            }                                                                   
        }
      b= 1.000000*density/(get_flaeche());
      f<< to_string(b) <<"\n";
      f.close();  
    }

	void Grid::print_density_in_file_methan(std::string dateiname, int step, int anfang)
    {   
    	double b=0;
   		string dateiname2 = dateiname + "_Methan";
     	fstream f;
      f.open(dateiname2, ios::out|ios::app);
      f << to_string(step) << ",";                         
      b= 1.000000*methan/(anfang);
      f<< to_string(b) <<"\n";
      f.close();  
  	}

  int Grid::volcanism(int atmospheric_oxygen, int timestep)
    {
      int new_oxygen = 0;
      new_oxygen = atmospheric_oxygen;
      double wachstum = 0;
      wachstum = pow(2.7182,atmospheric_oxygen*0.00000083);//0.00000067645
      new_oxygen = atmospheric_oxygen - wachstum;
      return new_oxygen;
      }

  void Grid::set_black_smoker(int anzahl)
    {   
      anzahl_black_smoker = anzahl;
      int index = 0;
      int x1,y1;
      while(index < anzahl)
        {  
          x1 = rand()% imax;
          y1 = rand()% jmax;
          if (wasser_ja_nein(x1, y1, imax, jmax)&& innerhalb_welt (x1, y1))
            {
              if (x1>0 && y1>0 && x1<imax-1 && y1<jmax-1)
                { 
                  smoker_x[index]=x1;
                  smoker_y[index]= y1;
                  index++;
                }
            }
        }
    }

  void Grid::activate_black_smocker(int timestep, int start)
    { 
      int x1,y1;
      if (timestep>start)
        {
          for(int a1=0; a1< anzahl_black_smoker; a1++)
            {   
              x1=smoker_x[a1];
              y1=smoker_y[a1];  
              set_iron(x1,y1,1);
              set_iron(x1+1,y1,1);
              set_iron(x1-1,y1,1);
              set_iron(x1,y1+1,1);
              set_iron(x1,y1-1,1);
              set_iron(x1+1,y1+1,1);
              set_iron(x1-1,y1-1,1);
              set_iron(x1-1,y1+1,1);
              set_iron(x1+1,y1-1,1);
            }
        }
    }

  void Grid::set_flaeche(int a2)
    {
      flaeche_welt = a2;
    }

  int Grid::get_flaeche()
    {
      return flaeche_welt;
    }

  float Grid::get_density_proteo()
    {
      int density=0;
      double b=0;
      for (int i1=0; i1<imax; i1++)
        {  
          for (int j1=0; j1<jmax; j1++)   
            { 
              density = density + v2[i1][j1].zustand_proteobacteria;
            }                                                                   
        }
      b= 1.000000*density/(get_flaeche());
      return b;
    }

  float Grid::get_density_cyano()
    {
      int density=0;
      double b=0;
      for (int i1=0; i1<imax; i1++)
        {  
          for (int j1=0; j1<jmax; j1++)   
            { 
              density = density + v2[i1][j1].zustand_cyanobakterien;
            }                                                                   
        }
      b= 1.000000*density/(get_flaeche());
      return b;
    }

  void Grid::print_in_file(std::string dateiname, int step, float step2)
    {  
      float b=0;   
      fstream f;
      f.open(dateiname, ios::out|ios::app);
      f << to_string(step) << ",";
      b= step2;
      f<< to_string(b) <<"\n";
      f.close();
    }