#ifndef CREATION_LAB_H_INCLUDED
#define CREATION_LAB_H_INCLUDED

#define MUR 0
#define CHEMIN -1

enum{HAUT,BAS,DROITE,GAUCHE};

class Labyrinthe {
private :
    int **m_plan;
    int m_hauteur_utilisateur;
    int m_largeur_utilisateur;
    int m_hauteur_reel;
    int m_largeur_reel;
    bool possible_dir_case(int **tab,int i,int j,int dir_i,int dir_j);
    bool possible_dir(int **tab,int i,int j);
public :
    Labyrinthe(const int hauteur=10,const int largeur=10);
    void affiche();
    void fusion_alea_chemins();
    ~Labyrinthe();
};

#endif // CREATION_LAB_H_INCLUDED
