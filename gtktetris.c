#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>
#include "tetris.h"

#define TAILLE_CARRE 16


// instancie la fenetre et les labels de manière global
GtkWidget *window;
GtkWidget* label_score;
GtkWidget* label_delay;


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


//------------------------------------- DEBUT INTERFACE ET AJOUT COMPOSANTS -------------------------------- //
void creeIHM(){

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
  GtkWidget* vbox_draw = gtk_vbox_new (TRUE, 10);
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
      /* Rend visible tout les composants. soit on le fait composants par composants
       ou on rend visible le 1er parent et tous ses sous-composants : */
  gtk_widget_show_all( window );

}
//------------------------------------- FIN INTERFACE ET AJOUT COMPOSANTS -------------------------------- //

int main( int   argc,
          char *argv[] )
{



  // Grille g;
  // Piece tabPieces[ NB_PIECES ];
  // genererPieces( tabPieces );
  // initialiseGrille( g );
  // afficheGrille( g );
  // return 0;

      /* Passe les arguments à GTK, pour qu'il extrait ceux qui le concernent. */
  gtk_init (&argc, &argv);

      /* Crée une fenêtre. */
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  creeIHM();
  /* Rentre dans la boucle d'événements. */
  /* Tapez Ctrl-C pour sortir du programme ! */
  gtk_main ();
  return 0;

}
