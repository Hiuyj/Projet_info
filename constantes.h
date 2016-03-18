/*Fichier de constantes pour le labyrinthe
19/01/2015*/

    #ifndef DEF_CONSTANTES
    #define DEF_CONSTANTES

        #define tle_blc 34  //taille d'un bloc en pixels
        #define nb_blc_ht 12  // Nombre de blocs en hauteur
        #define nb_blc_lg 12 // Nombre de blocs en largeur
        #define lg_fnt (tle_blc*nb_blc_lg) // largeur de la fentre
        #define ht_fnt (tle_blc*nb_blc_ht) // Hauteur de la fenetre

        enum {VIDE, MUR, SOURIS, OBJECTIF, SOURIS_GAUCHE};
        enum states
        {
            STATE_MENU = 0,
            STATE_GAME = 1,
        };

    #endif // DEF_CONSTANTES
