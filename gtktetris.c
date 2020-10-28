#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>
#include "tetris.h"

#define TAILLE_CARRE 16


////////////////////// STRUCTURE DE LA PARTIE LOGIQUE DU JEU
typedef struct {
  Grille g;
  Piece tab[ NB_PIECES ];
  int piece; // la piece "en cours" que l'on cherche à placer.
  int col; // la colonne actuelle pour la pièce que l'on cherche à caser.
  int score; // le score
  int delay; // le delay
} Jeu;


// instancie la fenetre et les labels de manière global
GtkWidget *window;
GtkWidget* label_score;
GtkWidget* label_delay;

int val0 = 17;

////////// Fonction qui fais avancer la piece a gauche
  gboolean Gauche( GtkWidget *widget, gpointer data )
  {
    // Recupère la valeur passée en paramètre.
    int val1 = * ( (int*) data );
    printf( "Gauche, val=%d\n", val1 ); // affichera 17
    return TRUE; // Tout s'est bien passé
  }

////////// Fonction qui fais avancer la piece a droite
  gboolean Droite( GtkWidget *widget, gpointer data )
  {
    // Recupère la valeur passée en paramètre.
    int val1 = * ( (int*) data );
    printf( "Droite, val=%d\n", val1 ); // affichera 17
    return TRUE; // Tout s'est bien passé
  }

////////// Fonction qui fais descendre la piece
  gboolean Bas( GtkWidget *widget, gpointer data )
  {
    // Recupère la valeur passée en paramètre.
    int val1 = * ( (int*) data );
    printf("Bas, val=%d\n", val1 ); // affichera 17
    return TRUE; // Tout s'est bien passé
  }

////////// Fonction qui recommence la partie
  gboolean New( GtkWidget *widget, gpointer data )
  {
    // Recupère la valeur passée en paramètre.
    // int val1 = * ( (int*) data );
    printf("Nouvelle partie\n"); // Nouvelle partie
    return TRUE; // Tout s'est bien passé
  }
//------------------------------------- FONCTIONS DE CREATIONS DES COMPOSANTS -------------------------------- //
/// fonction qui cree un button arrow
GtkWidget *create_arrow_button( GtkArrowType  arrow_type )
{
  // Les boutons sont en fait des conteneurs à un seul élément.
    GtkWidget* button = gtk_button_new ();
    GtkWidget* arrow = gtk_arrow_new (arrow_type, GTK_SHADOW_OUT);
    gtk_container_add (GTK_CONTAINER (button), arrow);
    gtk_widget_show_all( button );
    return button;
}

// Crée des boutons avec labels
GtkWidget *create_button( char* s )
{
  // Les boutons sont en fait des conteneurs à un seul élément.
    GtkWidget* button = gtk_button_new_with_label(s);
    gtk_widget_show_all( button );
    return button;
}

//------------------------------------- GESTION DE LA ZONE DE DESSIN -------------------------------- //

// Dessine le carré de type c à la ligne et colonne spécifiée dans le
// contexte graphique cr.
void dessineCarre( cairo_t* cr, int ligne, int colonne, char c ){

    switch (c) {
      case '|':
        cairo_set_source_rgb (cr, 1, 1, 0);
      case ' ':
        cairo_set_source_rgb (cr, 1, 1, 1);
      default:
        cairo_set_source_rgb (cr, 0, 1, 0);
    }
    cairo_rectangle (cr, ligne, colonne, TAILLE_CARRE, TAILLE_CARRE ); // x, y, largeur, hauteur
    cairo_fill_preserve( cr ); // remplit la forme actuelle (un rectangle)
  // => "_preserve" garde la forme (le rectangle) pour la suite

    // trace les contours
    cairo_set_line_width(cr, 3);
    cairo_set_source_rgb (cr, 0, 0.5, 0);
    cairo_stroke( cr ); // trace la forme actuelle (le même rectangle)
    // => pas de "_preserve" donc la forme (le rectangle) est oublié.
}


gboolean realize_evt_reaction( GtkWidget *widget, gpointer data )
{ // force un événement "expose" juste derrière.
  gtk_widget_queue_draw( widget );
  return TRUE;
}
// c'est la réaction principale qui va redessiner tout.
gboolean expose_evt_reaction( GtkWidget *widget, GdkEventExpose *event, gpointer data )
{

  cairo_t* cr = gdk_cairo_create (widget->window);
  cairo_set_source_rgb (cr, 1, 1, 1); // choisit le blanc.
  cairo_paint( cr ); // remplit tout dans la couleur choisie.

  cairo_set_source_rgb (cr, 1, 0, 1);
  cairo_rectangle (cr, 0, 0, TAILLE_CARRE, TAILLE_CARRE*(HAUTEUR+7) ); // x, y, largeur, hauteur
  cairo_fill_preserve(cr);

  cairo_rectangle (cr, TAILLE_CARRE*(HAUTEUR+8), 0, TAILLE_CARRE, TAILLE_CARRE*(HAUTEUR+7) ); // x, y, largeur, hauteur
  cairo_rectangle (cr, 0, TAILLE_CARRE*(HAUTEUR+6), TAILLE_CARRE*(LARGEUR+4), TAILLE_CARRE ); // x, y, largeur, hauteur
  cairo_fill_preserve(cr);

  // On a fini, on peut détruire la structure.
  cairo_destroy (cr);
  return TRUE;
}


//------------------------------------- DEBUT INTERFACE ET AJOUT COMPOSANTS -------------------------------- //
void creeIHM(Jeu* ptrJeu){

      // instancie les buttons quit et new
  GtkWidget* quit = create_button("Quit");
  GtkWidget* new = create_button("New");

      // instancie les buttons fléchés, left, right, down
  GtkWidget* left = create_arrow_button( GTK_ARROW_LEFT );
  GtkWidget* right = create_arrow_button( GTK_ARROW_RIGHT );
  GtkWidget* down = create_arrow_button( GTK_ARROW_DOWN );

      // Instancie les composants Hbox et Vbow
  GtkWidget* hbox_ligne1 = gtk_hbox_new (FALSE, 10);
  GtkWidget* hbox_btn_quit = gtk_hbox_new (FALSE, 1);
  GtkWidget* hbox_arrow = gtk_hbox_new (FALSE, 1);
  GtkWidget* vbox_draw = gtk_vbox_new (FALSE, 10);
  GtkWidget* vbox_col_btn = gtk_vbox_new (FALSE, 10);
  GtkWidget* vbox_label = gtk_vbox_new (FALSE, 1);
  GtkWidget* mainVb = gtk_vbox_new (FALSE, 1);

      // crées des labels
  GtkWidget* label_score = gtk_label_new( "Score : 0" );
  GtkWidget* label_delay = gtk_label_new( "Delay" );

      // crée la zone de dessin
  GtkWidget* drawing_area = gtk_drawing_area_new ();
      // definie sa taillle
  gtk_widget_set_size_request (drawing_area, TAILLE_CARRE*(LARGEUR+4), TAILLE_CARRE*(HAUTEUR+7));

      // Rajoute la box verticale dans le conteneur window.
  gtk_container_add( GTK_CONTAINER( window ), mainVb);
      // creation des 2 lignes  : hbox_ligne1 ligne du haut
  gtk_container_add( GTK_CONTAINER( mainVb ), hbox_ligne1);
    gtk_container_add( GTK_CONTAINER( hbox_ligne1 ), vbox_draw);

      //                            vbox_col_btn colonne de droite
  gtk_container_add( GTK_CONTAINER( hbox_ligne1 ), vbox_col_btn);
      // grille de jeu
      gtk_container_add( GTK_CONTAINER( vbox_draw ), drawing_area);
  // creation de la hbox des bouttons
  gtk_container_add( GTK_CONTAINER( vbox_col_btn ), hbox_btn_quit);
          // ajout des bouttons a la hbox_btn_quit (haut gauche)
      gtk_container_add( GTK_CONTAINER( hbox_btn_quit ), new);
      gtk_container_add( GTK_CONTAINER( hbox_btn_quit ), quit);

  // creation de la vbox qui contient score et delay
  gtk_container_add( GTK_CONTAINER( vbox_col_btn ), vbox_label);
      gtk_container_add( GTK_CONTAINER( vbox_label ), label_score);
      gtk_container_add( GTK_CONTAINER( vbox_label ), label_delay);

  // creation de la hbox qui contient les fleches
  gtk_container_add( GTK_CONTAINER( mainVb ), hbox_arrow);
      gtk_container_add( GTK_CONTAINER( hbox_arrow ), left);
      gtk_container_add( GTK_CONTAINER( hbox_arrow ), down);
      gtk_container_add( GTK_CONTAINER( hbox_arrow ), right);

  // Connecte la réaction gtk_main_quit à l'événement "clic" sur ce bouton.
  g_signal_connect( quit, "clicked",
                G_CALLBACK( gtk_main_quit ),
        NULL);

  g_signal_connect( left, "clicked",
              G_CALLBACK( Gauche ), &val0 );
  g_signal_connect( right, "clicked",
              G_CALLBACK( Droite ), &val0 );
  g_signal_connect( down, "clicked",
              G_CALLBACK( Bas ), &val0 );
  g_signal_connect( new, "clicked",
              G_CALLBACK( New ), &val0 );

//////////////// DESSINE DANS LA DRAWING AREA ///////////////////////////
    // ... votre zone de dessin s'appelle ici "drawing_area"
  g_signal_connect( G_OBJECT(drawing_area), "realize",
            G_CALLBACK(realize_evt_reaction), ptrJeu );
  g_signal_connect( G_OBJECT (drawing_area), "expose_event",
            G_CALLBACK (expose_evt_reaction), ptrJeu );

      /* Rend visible tout les composants. soit on le fait composants par composants
       ou on rend visible le 1er parent et tous ses sous-composants : */
  gtk_widget_show_all( window );

}
//------------------------------------- FIN INTERFACE ET AJOUT COMPOSANTS -------------------------------- //

int main( int   argc,
          char *argv[] )
{

  Jeu jeu;
  initialiseGrille( jeu.g );
  genererPieces( jeu.tab );
  //Piece p = pieceAlea(jeu.tab);
  jeu.score = 0;
  jeu.delay = 0;

      /* Passe les arguments à GTK, pour qu'il extrait ceux qui le concernent. */
  gtk_init (&argc, &argv);

      /* Crée une fenêtre. */
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  creeIHM(&jeu);
  /* Rentre dans la boucle d'événements. */
  /* Tapez Ctrl-C pour sortir du programme ! */
  gtk_main ();
  return 0;

}
