#include <iostream>
#include "creation_lab.h"

using namespace std;

int main()
{
    Labyrinthe test;
    test.affiche();
    test.fusion_alea_chemins();
    cout << endl;
    test.affiche();
    return 0;
}
