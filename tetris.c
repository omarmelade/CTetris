#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tetris.h"


// creation de mon tableau de pi�ces
Piece tabPiece[NB_PIECES];


// procedure qui initialise la grille a ' '
void initialiseGrille(Grille g)
{
    for(int i=0; i < HAUTEUR; i++)
    {
        for(int j=0; j < LARGEUR; j++)
        {
            g[i][j] = ' ';
        }
    }
}

// procedure qui affiche la case lue
char lireCase(Grille g, int line, int col)
{
    if(line < HAUTEUR && col < LARGEUR)
    {
        return g[line][col];
    }
    else
    {
        printf("%s", "La case n'existe pas. \n");
        return 'E';
    }
}

bool caseEstVide(Grille g, int line, int col)
{
    if(g[line][col] == ' '){
        return true;
    }
    return false;
}

///////////////////////////////////////////////////
/////////////// PROCEDURE D'AFFICHAGE /////////////
///////////////////////////////////////////////////

//// affiche un separateur
void printseparator()
{
    printf("%s", "-------------------------");
    printcarriage(1);
}

//// affiche un retour chariot
void printcarriage(int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("\n");
    }
}

void printmsg(char* str)
{
    printf("%s\n", str);
}
/////////////////////////////////////
////// affichage de la grille ///////
/////////////////////////////////////

// procedure qui affiche le bas
//  et les chiffre du bas de la grille
void afficheBasGrille(){

    // on affiche le bas de la grille
    printf("%s", "  ");
    // ici le plus 4 est l� pour aligner la grille
    for(int i=0;i<LARGEUR + 4 ;i++)
    {
        printf("%c", '|');
    }

    // on affiche les chiffres du bas de la grille
    printcarriage(1);
    printf("%s", "    ");
    // affiche la ligne des dixaines
    for(int n=0;n <LARGEUR;n++)
    {
        if(n == 0 || n == 10)
        {
            printf("%d", n/10);
        }
        else
        {
            printf("%c", ' ');
        }
    }
    printcarriage(1);
    printf("%s", "    ");
    // affiche la ligne des unit�s
    for(int n=0;n <LARGEUR;n++)
    {
            printf("%d",n%10);
    }
    printcarriage(2);
    printseparator();
}

// procedure qui affiche la grille
// et son contenu
void afficheGrille(Grille g)
{
    printcarriage(1);
    for(int i=0; i < HAUTEUR; i++)
    {
        // on affiche les chiffres de bas en haut
        printf("%d", (9-i%10));
        // on espace les chiffres des bords
        printf("%s", " ");

        // on affiche les bords a gauche
        printf("%s", "||");
        for(int j=0; j < LARGEUR; j++)
        {
            printf("%c", g[i][j]);
        }
        // on affiche les bords a droite
        printf("%s", "||");
        printcarriage(1);
    }

    afficheBasGrille();
}

/////////////////////////////////////
////// affichage de la pi�ce ////////
/////////////////////////////////////

void affichePiece(Piece p){
    printf("\n");
    int h = p.hauteur;
    for(int i = h-1; i >= 0; i--){
        printf("%s\n", p.forme[i]);
    }
    printf("%c", '^');
    printcarriage(1);
}

/////////////////////////////////////
/////////////////////////////////////

void genererPieces()
{

    // piece 1
    tabPiece[0].hauteur = 4;
    tabPiece[0].largeur = 1;
    tabPiece[0].forme[3] = "I";
    tabPiece[0].forme[2] = "I";
    tabPiece[0].forme[1] = "I";
    tabPiece[0].forme[0] = "I";
    // piece 2
    tabPiece[1].hauteur = 2;
    tabPiece[1].largeur = 3;
    tabPiece[1].forme[1] = " @ ";
    tabPiece[1].forme[0] = "@@@";
    // piece 3
    tabPiece[2].hauteur = 2;
    tabPiece[2].largeur = 2;
    tabPiece[2].forme[1] = "%%";
    tabPiece[2].forme[0] = "%%";
    // piece 4
    tabPiece[3].hauteur = 2;
    tabPiece[3].largeur = 3;
    tabPiece[3].forme[1] = "H";
    tabPiece[3].forme[0] = "HHH";
    // piece 5
    tabPiece[4].hauteur = 3;
    tabPiece[4].largeur = 2;
    tabPiece[4].forme[2] = "#";
    tabPiece[4].forme[1] = "#";
    tabPiece[4].forme[0] = "##";
}

void ecrireCase(Grille g, int line, int col, char c)
{
    //printf("%s %d %d\n","voici la ligne :  ", line, col);
    if(line < HAUTEUR && line >= 0 )
    {
        if(col >= 0 && col < LARGEUR)
        {
            g[line][col] = c;
        }
    }
    else
    {
        printf("%s %d\n", "IMPOSSIBLE VOUS ALLEZ AU DELA DE LA GRILLE", line);
    }

}

// retourne la 1ere case vide de la colonne
int premiereLineVideColonne(Grille g, int colonne){

//    int ligne = 0;
//    int fin_grille = HAUTEUR-1;
//    while(caseEstVide(g, ligne, colonne) && ligne < HAUTEUR){
//        ligne++;
//    }
//    if(ligne < fin_grille)
//    {
//        fin_grille = ligne;
//    }
//    return fin_grille;

    int lignemax = HAUTEUR-1;
    int line;
    for(line = 0; line < HAUTEUR; line++)
    {
        if(!caseEstVide(g, line, colonne))
        {
            line = line - 1;
            break;
        }
    }
    if(line < lignemax ){
        lignemax = line;
    }
    //printf("%s\n", "LA COLONNE EST VIDE");
    //printf("%s %d\n", "hauteur exa : ",  lignemax);
    return lignemax;
}



// retourne la 1ere case vide au dessus de la ligne la plus haute de l'interval
//int hauteurPlat(Grille g, int coldebut, int colfin)
//{
//    int lignemax = 0;
//    colfin = coldebut + colfin;
//    for(int i = coldebut; i <= colfin; i++)
//    {
//        printf("colonne fin : %d\n", colfin);
//        if(lignemax < premiereLineVideColonne(g, i)){
//            lignemax = premiereLineVideColonne(g, i);
//        }
//    }
//    return lignemax;
//}

//int hauteurExactev2( Grille g, int col_gauche, Piece piece ){
//
//    int ligne = HAUTEUR-1;
//    int colfin = col_gauche + piece.largeur;
//    for(int i = col_gauche; i < colfin; i++)
//    {
//        printf("colonne fin : %d\n", colfin);
//        ligne = premiereLineVideColonne(g, i);
//    }
//
//    return ligne;
//}

int hauteurExacte( Grille g, int colPrec, int colSuiv ){

    int colonne,ligne;
    int plusBasse = HAUTEUR-1; /* nb de la plus basse ligne vide*/
    for (colonne = colPrec ; colonne < colSuiv ; colonne++){
            for (ligne = 0; ligne < HAUTEUR; ligne++)
            {
                if (g[ligne][colonne] != ' ')
                {
                    ligne = ligne - 1;
                    //printf("colonne fin : %d\n", colPrec+1);
                    break;
                }
            }
            if(ligne < plusBasse){
                plusBasse = ligne;
            }
    }
    return plusBasse;
}

void descendtoutesligne(Grille g, int ligne)
{
    printf("%d\n", ligne);
    for(int i = ligne-1 ; i > 0; i--)
    {
        for(int j = 0; j < LARGEUR; j++)
        {
            ecrireCase(g, i+1, j, lireCase(g, i, j));
            ecrireCase(g, i, j, ' ');
            //printf("%s\n", "suppr");
        }
    }
}

// ne fonctionne pas
void supprimeLigne(Grille g, int ligne)
{
    for(int x = 0; x < LARGEUR; x++)
    {
        ecrireCase(g, ligne, x, ' ');
    }
    descendtoutesligne(g, ligne);
}

// renvoie le nb de lignes nettoyer
int nettoyer(Grille g){

    int nb_lignes_clean = 0;
    for(int i = 0; i < HAUTEUR; i++)
    {
        int nb_case = 0;
        for(int j = 0; j < LARGEUR; j++)
        {
            if(!caseEstVide(g, i, j))
            {
                nb_case++;
            }
            else
            {
                nb_case = 0;
            }
        }
        if(nb_case == LARGEUR)
        {
            supprimeLigne(g, i);
            nb_lignes_clean++;
        }
    }
    return nb_lignes_clean;
}

// ecrit une piece dans la grille
void ecrirePiece(Grille g, Piece p, int col, int hauteur)
{
    // ligne me donne la ligne a laquelle je doit ecrire mon premier char
    int ligne = hauteurExacte(g, col, col+p.largeur);
    // ligne correspond a la hauteur du premier caractère vide
    if(col+p.largeur <= LARGEUR && ligne-p.hauteur+1 >= 0){
        //printf("%s %d\n", "colonne + largeur :", col+p.largeur);
        for(int h = 0; h < hauteur; h++)
        {
            // j'utilise strlen pour connaitre exactement la taille de la chaine
             // je n'ai donc rien a ecrire la ou le caractère n'existe pas.
            for(int l = 0; l < strlen(p.forme[h]); l++)
            {
                ecrireCase(g, ligne-h, l+col, p.forme[h][l]);
            }
        }
    }
    else
    {
        printf("%s", "IMPOSSIBLE D'ALLEZ AU DELA DES LIMITES");
    }

}

// bug dans la fonction alea, qui renvoie le meme entier a chaque fois
int alea(){
    return (int)(((double)rand()/((double)RAND_MAX)) * (NB_PIECES));
}

Piece pieceAlea(Piece tab[])
{
    srand(time(0));
    return tab[alea()];
}

// fonction main d'appel principal du jeu
int main_console()
{

    Grille grille;
    initialiseGrille(grille);
    genererPieces();
    int colonne;
    // compte le nb de pieces du jeu
    int nbPieces = 0;
    while(colonne != -1){
        Piece p = pieceAlea(tabPiece);
        affichePiece(p);
        afficheGrille(grille);
        scanf( "%d", &colonne );
        if(colonne >= 0 && colonne < LARGEUR){
            int hRestant = hauteurExacte(grille, colonne, colonne+p.largeur) - p.hauteur + 1;
            //int hplat = hauteurExacte(grille, colonne, colonne+p.largeur-1);
            //printf("hauteur exacte : %d\n hauteur restante : %d\n", hplat, hRestant);
            if(hRestant >= 0){
                ecrirePiece(grille, p, colonne, p.hauteur);
                nbPieces++;
                printf("%s %d %s\n", "VOUS AVEZ POSE ", nbPieces, " PIECES");
                // après avoir ecrit on nettoie comme un agent de terrain
                nettoyer(grille);
            }
            else
            {
                printcarriage(1);
                printseparator();
                printmsg("VOUS AVEZ DEPASSEZ LES LIMITES DE LA GRILLES. PERDU !");
                printf("%s %d %s\n", "VOUS AVEZ POSE ", nbPieces, " PIECES");
                nbPieces = 0;
                printseparator();
                initialiseGrille(grille);
            }
        }
        else{
            int del;
            printcarriage(1);
            printseparator();
            printmsg("VOUS NE POUVEZ PAS INSERER DE PIECE ICI !");
            printmsg("QUELLE LIGNE VOULEZ VOUS SUPPRIMER : ");
            scanf( "%d", &del );
            supprimeLigne(grille, del);
            printseparator();
            printcarriage(1);
        }


    }
    return 0;
}
