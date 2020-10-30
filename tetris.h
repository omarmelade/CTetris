#ifndef TETRIS_H_INCLUDED
#define TETRIS_H_INCLUDED

#define HAUTEUR 10
#define LARGEUR 15
#define NB_PIECES 5
#define HAUTEUR_MAX_DES_PIECES 4

struct SPiece
{
    int hauteur;
    int largeur;
    char* forme[HAUTEUR_MAX_DES_PIECES];
};
// definition du type Piece
typedef struct SPiece Piece;

// definition du type Grille
typedef char Grille[HAUTEUR][LARGEUR];


void initialiseGrille(Grille g);
char lireCase(Grille g, int line, int col);
void afficheBasGrille();
void afficheGrille(Grille g);

void printcarriage(int n);
void printseparator();

void genererPieces(Piece tab[]);
void ecrireCase(Grille g, int line, int col, char c);
void ecrirePiece(Grille g, Piece p, int col, int hauteur);
Piece pieceAlea(Piece tab[]);

int alea();
int nettoyer(Grille g);
int premiereLineVideColonne(Grille g, int colonne);
int hauteurPlat(Grille g, int coldebut, int colfin);
int hauteurExacte( Grille g, int col_gauche, int colSuiv );
void supprimeLigne(Grille g, int ligne);

#endif // TETRIS_H_INCLUDED
