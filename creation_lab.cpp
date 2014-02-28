#include <iostream>
#include <cstdlib>
#include <ctime>
#include "creation_lab.h"

using namespace std;

Labyrinthe::Labyrinthe(const int hauteur,const int largeur) : m_hauteur_utilisateur(hauteur), m_largeur_utilisateur(largeur)
{
    //Agrandissement du tableau pour intégré des murs
    m_hauteur_reel=m_hauteur_utilisateur*2+1;
    m_largeur_reel=m_largeur_utilisateur*2+1;

    //allocation dynamique
    m_plan= new int*[m_hauteur_reel];
    for(int i=0; i< m_hauteur_reel;i++)
        m_plan[i]= new int[m_largeur_reel];

    //initialisation
    for(int i=0; i< m_hauteur_reel;i++)
    {
        for(int j=0; j< m_largeur_reel;j++)
        {
            //On commence de 1 et on incrémente chaque case
            if( !((j%2==0) || (i%2==0)) )
                m_plan[i][j]=(int)(j/2+i/2*m_largeur_utilisateur+1);
            //Et on met un mur
            else
                 m_plan[i][j]=MUR;
        }
    }
}

bool Labyrinthe::possible_dir_case(int **tab,int i,int j,int dir_i,int dir_j)
{
    bool possible=false;

    //on vérifie qu'on sort pas du tableau
    if( 0<=(j+dir_j) && 0<=(i+dir_i) && m_largeur_utilisateur>(j+dir_j) && m_hauteur_utilisateur>(i+dir_i) )
    {
        //on regarde les case de coordonnée combiné impaire et don la valeur diffère
        if( (dir_i+dir_j)%2==1 && tab[i][j]!=tab[i+dir_i][j+dir_j] )
            possible=true;
    }

    return possible;
}

bool Labyrinthe::possible_dir(int **tab,int i,int j)
{
    bool possible=false;

    for(int dir_i=-1; dir_i< 2 && !(possible);dir_i++)
    {
        for(int dir_j=-1; dir_j< 2 && !(possible);dir_j++)
        {
            if(possible_dir_case(tab,i,j,dir_i,dir_j))
                possible=true;
        }
    }

    return possible;
}
void Labyrinthe::fusion_alea_chemins()
{
    int **tabVal=NULL;

    //allocation dynamique et initialisation
    tabVal= new int*[m_hauteur_utilisateur];
    for(int i=0; i< m_hauteur_utilisateur;i++)
    {
        tabVal[i]= new int[m_largeur_utilisateur];
        for(int j=0;j<m_largeur_utilisateur;j++)
            tabVal[i][j]=(int)(j+i*m_largeur_utilisateur);
    }

    //initialisation des valeurs aléatoires
    srand(time(0));

    int nbAleaCase=0,nbAleaDir=0;
    bool nbAleaCorrect=false,dirAleaCorrect=false;

    //Debut de l'algo
    for(int loop=0;loop<(m_largeur_utilisateur*m_hauteur_utilisateur)-1;loop++)
    {
        do{
            //on cherche une case aléatoire et une direction de mur aléatoire
            nbAleaCase=rand() % (m_largeur_utilisateur*m_hauteur_utilisateur);
            //On retrouve les coordonées de la case
            int i=(int)(nbAleaCase/m_largeur_utilisateur), j=(i) ? nbAleaCase%(i*m_largeur_utilisateur) : nbAleaCase;

            //si une direction est possible
            if(possible_dir(tabVal,i,j))
            {
                int dir_i=0,dir_j=0; //variable de direction
                nbAleaCorrect=true; // Une direction est possible donc le nombre aléatoire est correcte
                do{
                    //On choisi une case au hasard
                    nbAleaDir=rand()%4;
                    switch(nbAleaDir)
                    {
                    case HAUT :
                        dir_i=-1;
                        dir_j=0;
                        break;
                    case BAS :
                        dir_i=1;
                        dir_j=0;
                        break;
                    case DROITE :
                        dir_i=0;
                        dir_j=1;
                        break;
                    case GAUCHE :
                        dir_i=0;
                        dir_j=-1;
                        break;
                    }
                    //Recherche si la direction est bonne
                    dirAleaCorrect=possible_dir_case(tabVal,i,j,dir_i,dir_j);

                }while( !(dirAleaCorrect) ); //Tant que la direction est incorecte

                //On ouvre le mur de la case en fonction de la direction
                m_plan[(i*2+dir_i)+1][(j*2+dir_j)+1]=CHEMIN;
                //On change les nombres du tableau
                for(int n=0;n<m_hauteur_utilisateur;n++)
                {
                    for(int m=0;m<m_largeur_utilisateur;m++)
                    {
                        if(tabVal[n][m]==tabVal[i+dir_i][j+dir_j] && (n!=i+dir_i || m!=j+dir_j) )
                            tabVal[n][m]=tabVal[i][j];
                    }
                }
                tabVal[i+dir_i][j+dir_j]=tabVal[i][j];
            }
            else
                nbAleaCorrect=false;

        }while( !(nbAleaCorrect) ); //Tant qu'un mur d'une case ne peut pas être ouvert
    }

    //destruction du tableau
    for(int i=0; i< m_hauteur_utilisateur;i++)
        delete tabVal[i];
    delete tabVal;

}

void Labyrinthe::affiche()
{
    for(int i=0; i< m_hauteur_reel;i++)
    {
        for(int j=0; j< m_largeur_reel;j++)
        {
            if( m_plan[i][j]==MUR)
                cout << "+";
            else
                cout << ' ';
        }
        cout << endl;
    }
}
Labyrinthe::~Labyrinthe()
{
    for(int i=0; i< m_hauteur_reel;i++)
        delete m_plan[i];
    delete m_plan;
}
