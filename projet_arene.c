#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define taille_x 35
#define taille_y 35

// --- FONCTIONS PRINCIPALES ---
void tanks_game_luncher(char map[taille_x][taille_y]);
//Fonctions du jeux officiel. Sans test (test dans le main).
void presentation();
//Presentation du jeux, régles + animation.
void creation_carte(char map[taille_x][taille_y]);
// Création de la carte
void generation_obstacles (int nb_obstacles, char map[taille_x][taille_y]);
// Création des obstacles sur la carte
void affichage_carte(char map[taille_x][taille_y]);
// Affichage de la carte
void affichage_better_map(char map[taille_x][taille_y]);
// Affichage de la carte de manière plus propre
int choix_joueurs();
//Permet de saisir le nombre de joueurs
void generate_tab_scores(int nb_j, int haut, char tab_scores[haut][nb_j]);
//Permet de généré le tableau des scores
void affichage_tab_scores(int nb_j, int haut, char tab_scores[haut][nb_j]);
//Affiche le tableau des scores

// --- FONCTIONS UTILITAIRES ---
void printf_center (const char* str);
//permet d'afficher du texte au centre du terminal
void regles();
//appelez cette fonction pour afficher les régle
void Color(int couleurDuTexte,int couleurDeFond);
//permet d'utiliser des couleurs
void table_ascii();
//appelez cette fonctions pour afficher la table ascii
void printf_ligne1();
//affiche une ligne sur tout le terminal



void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs dans le terminal
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}
/*         Ecrire : Color("couleur de caractere", "couleur de fond");
 Exemple : Color(4, 0);
 Printf("Emeline pue du cul");
 Color(15, 0);
 0 : Noir
 1 : Bleu foncé
 2 : Vert foncé
 3 : Turquoise
 4 : Rouge foncé
 5 : Violet
 6 : Vert caca d'oie
 7 : Gris clair
 8 : Gris foncé
 9 : Bleu fluo
 10 : Vert fluo
 11 : Turquoise
 12 : Rouge fluo
 13 : Violet 2
 14 : Jaune
 15 : Blanc
 */

void presentation()  //Fonction de présentation, contient l'animation le logo et les régles
{
    void chargement() //Pas encore au point...(ou a la virgule, mdr. j'avoue j'ai ri xD)
    {
        printf_center("Ah ...\n");
        printf_center("Oh non pas du temps de chargement ...\n");
        printf_center("On se disait que ca faisait plus badass\n");
        printf_center("D'autant plus qu'on en a pas besoin, vu le truc qu'on fait tourner...\n");
        printf_center("Hein ? Quoi ??\n");
        printf_center("Ah ! tu veux des TIPS !\n");
        printf_center("TIPS : Mettez du sel dans l'eau pour faire cuire vos pates plus rapidement :D\n");
        printf_center("Que 40%... Bon allez ecrit un message gentil et appuie sur 'entree' pour charger le jeu ;)");
    }
    
    void plein_ecran()
    {
        char variable_a_tout_faire = 130;
        Color(14,0);
        printf("\n\n  /!\\ ");
        Color(4,0);
        printf(" --- ");
        Color(12,0);
        printf("Mettez votre terminal en pleine %ccran svp",variable_a_tout_faire);
        Color(4,0);
        printf(" --- ");
        Color(14,0);
        printf(" /!\\ \n\n");
        Color(8,0);
        printf(" Appuyez sur la touche \"entr%ce\" pour continuer et lancer le jeu",variable_a_tout_faire);
        Color(15,0);
        variable_a_tout_faire = getchar();
    }
    
    void animation_tanks(unsigned char ascii_tanks[5][32])
    {
        char variable_a_tout_faire = 174;
        int r, s, ligne_i, colonne_j, nb_espace_avant=27, nb_espace_entre=120;
        printf("\n\n");
        for(s=0; s<(nb_espace_entre+25); s++)
        {
            system("cls");
            for(r=0;r<40;r++)
            {
                printf("\n");
            }
            for(ligne_i=0; ligne_i < 5; ligne_i++)
            {
                for(r=0; r < nb_espace_avant; r++)
                {
                    printf(" ");
                }
                for(colonne_j = 0; colonne_j < 32; colonne_j++)
                {
                    if(ascii_tanks[ligne_i][colonne_j]== 220 && ligne_i == 3)
                    {
                        Color(8,2);
                        printf("%c", ascii_tanks[ligne_i][colonne_j]);
                        Color(15,0);
                    }
                    else
                    {
                        Color(8,0);
                        printf("%c", ascii_tanks[ligne_i][colonne_j]);
                        Color(15,0);
                    }
                }
                for(r=0; r < nb_espace_entre; r++)
                {
                    printf(" ");
                }
                for(colonne_j=31; colonne_j >= 0; colonne_j--)
                {
                    if(ascii_tanks[ligne_i][colonne_j]== 220 && ligne_i == 3)
                    {
                        Color(8,2);
                        printf("%c", ascii_tanks[ligne_i][colonne_j]);
                        Color(15,0);
                    }
                    else if(ascii_tanks[ligne_i][colonne_j]== 93)
                    {
                        Color(8,0);
                        printf("[");
                        Color(15,0);
                    }
                    else if(ascii_tanks[ligne_i][colonne_j]== 175)
                    {
                        Color(8,0);
                        printf("%c",variable_a_tout_faire);
                        Color(15,0);
                    }
                    else
                    {
                        Color(8,0);
                        printf("%c", ascii_tanks[ligne_i][colonne_j]);
                        Color(15,0);
                    }
                }
                printf(" \n ");
            }
            nb_espace_avant= nb_espace_avant+2;
            nb_espace_entre= nb_espace_entre-4;
        }
        
    }
    
    void logo(unsigned char ascii_tanks[5][32])
    {
        int r, ligne_i, colonne_j;
        char variable_a_tout_faire = 130;
        
        system("cls");
        for(r=0;r<50;r++)
        {
            printf("\n");
        }
        Color(12,0);
        printf("\n\n\n\n");
        printf_center("ooooooooooooo       .o.       ooooo      ooo oooo    oooo  .oooooo..o\n");
        printf_center("8'   888   `8      .888.      `888b.     `8' `888   .8P'  d8P'    `Y8\n");
        printf_center("     888          .8\"888.      8 `88b.    8   888  d8'    Y88bo.     \n");
        printf_center("     888         .8' `888.     8   `88b.  8   88888[       `\"Y8888o. \n");
        printf_center("     888        .88ooo8888.    8     88b. 8   88888b.         `\"Y88b \n");
        printf_center("     888       .8'     `888.   8       `888   888  `88b.  oo     .d8P\n");
        printf_center("    o888o     o88o     o8888o o8o        `8  o888o  o888o 8\"\"88888P' \n\n");
        printf_center("       .oooooo.          .o.       ooo        ooooo oooooooooooo     \n");
        printf_center("      d8P'  `Y8b        .888.      `88.       .888' `888'     `8     \n");
        printf_center("     888               .8\"888.      888b     d'888   888             \n");
        printf_center("     888              .8' `888.     8 Y88. .P  888   888oooo8        \n");
        printf_center("     888     ooooo   .88ooo8888.    8  `888'   888   888    \"        \n");
        printf_center("     `88.    .88'   .8'     `888.   8    Y     888   888       o     \n");
        printf_center("      `Y8bood8P'   o88o     o8888o o8o        o888o o888ooooood8     \n");
        Color(15,0);
        printf("\n\n\n");
        
        variable_a_tout_faire = 174;
        for(ligne_i=0; ligne_i < 5; ligne_i++)
        {
            for(r=0; r < 80; r++)
            {
                printf(" ");
            }
            for(colonne_j = 0; colonne_j < 32; colonne_j++)
            {
                if(ascii_tanks[ligne_i][colonne_j]== 220 && ligne_i == 3)
                {
                    Color(8,4);
                    printf("%c", ascii_tanks[ligne_i][colonne_j]);
                    Color(15,0);
                }
                else
                {
                    Color(8,0);
                    printf("%c", ascii_tanks[ligne_i][colonne_j]);
                    Color(15,0);
                }
            }
            switch(ligne_i)
            {
                case 0:
                    Color(14,0);
                    printf("    \\.|./    ");
                    Color(15,0);
                    break;
                case 1:
                    Color(14,0);
                    printf(" - --o-- - ");
                    Color(15,0);
                    break;
                case 2:
                    Color(14,0);
                    printf("    /|\\    ");
                    Color(15,0);
                    break;
                case 3:
                    Color(14,0);
                    printf("  /     \\  ");
                    Color(15,0);
                    break;
                case 4:
                    Color(14,0);
                    printf("           ");
                    Color(15,0);
                    break;
                default:
                    break;
            }
            for(colonne_j=31; colonne_j >= 0; colonne_j--)
            {
                if(ascii_tanks[ligne_i][colonne_j]== 220 && ligne_i == 3)
                {
                    Color(8,1);
                    printf("%c", ascii_tanks[ligne_i][colonne_j]);
                    Color(15,0);
                }
                else if(ascii_tanks[ligne_i][colonne_j]== 93)
                {
                    Color(8,0);
                    printf("[");
                    Color(15,0);
                }
                else if(ascii_tanks[ligne_i][colonne_j]== 175)
                {
                    Color(8,0);
                    printf("%c",variable_a_tout_faire);
                    Color(15,0);
                }
                else
                {
                    Color(8,0);
                    printf("%c", ascii_tanks[ligne_i][colonne_j]);
                    Color(15,0);
                }
            }
            printf(" \n ");
        }
        printf("\n\n\n\n");
    }
    
    unsigned char ascii_tanks[5][32]= {{[12]=124,[16]=95},
        {[7]=95,[9]=176,176,223,219,219,219,219,178,219,219,219,93,220,220,220,220,220,220,220,220,220,220,61},
        {[3]=95,220,220,219,219,219,219,219,219,178,219,178,219,219,219,219,220,220,95,95},
        {[2]=73,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,93,175},
        {250,46,46,248,111,95,111,95,111,95,111,95,111,95,111,95,111,95,111,95,111,248}};
    system("cls");
    plein_ecran();
    //chargement();  //Pas encore au point
    animation_tanks(ascii_tanks);  //mettez cette fonction en commentaire pour enlver l'animation
    logo(ascii_tanks);
    regles();
}

void regles()
{
    printf_center("*** Make Platypus great again ! ***\n\n");
    Color(14,0);
    printf_center("OBJECTIF :\n");
    Color(7,0);
    printf_center("Votre objectif est simple caporal !\n");
    printf_center(" Vous etes aux commandes d'un tout nouveau modele de Tank\n");
    printf_center("et votre objectif est d'aneantir l'ennemie grace a vos obus a tete nucleaire !\n\n");
    Color(14,0);
    printf_center("FONCTIONNEMENT :\n");
    Color(7,0);
    printf_center("-Vous ne pouvez pas vous deplacer dans des murs (obstacle) PS: Reflechissez...\n");
    printf_center("Blablabla\n\n");
    Color(14,0);
    printf_center("REGLES :\n");
    Color(7,0);
    printf_center("Vous devez rester courtois entres camarades ni insultes ni violences ne seront tolerees\n");
    printf_center(" seules les tetes nucleaires sont autorisees\n");
    Color(15,0);
    printf("\n\n\n");
}

//Fonction utilitaire
void printf_center (const char* str)
{
    unsigned int n;
    for (n = 0; n < (237-strlen(str)) / 2; n++)
    {
        putchar(' ');
    }
    printf("%s", str);
}

//Fonction utilitaire
void printf_ligne1()
{
    int n;
    for (n = 0; n < 237; n++)
    {
        printf("%c",176);
    }
    printf("\n");
}

//Fonction utilitaire
void table_ascii()
{
    int r;
    printf("-    Dec  : Char\n-\n");
    for(r=-256; r<256 ;r=r+4)
    {
        printf("-     %d  :  %c    ",r,r);
        printf("-     %d  :  %c    ",r+1,r+1);
        printf("-     %d  :  %c    ",r+2,r+2);
        printf("-     %d  :  %c    \n",r+3,r+3);
    }
}



void creation_carte(char map[taille_x][taille_y])
{
    int i, j;
    for (i = 0; i < taille_x; i++)
    {
        for (j = 0; j < taille_y; j++)
        {
            if ((i == 0)||(i == taille_x - 1)||(j == 0)||(j == taille_y - 1))       // Contour de la carte
            {
                map[i][j] = 178;
            }
            else                                                                    // Intérieur de la carte (Zone jouable)
            {
                map[i][j] = 0;
            }
        }
    }
}


void generation_obstacles (int nb_obstacles, char map[taille_x][taille_y])
{
    srand(time(NULL));
    const int iMAX = taille_x - 1;
    const int jMAX = taille_y - 1;
    const int iMIN = 1;
    const int jMIN = 1;
    int cpt = 0;
    for (cpt = 0; cpt < nb_obstacles; cpt++)                                        // Boucle avec un compteur allant de 0 jusqu'au nombre max d'obstacles
    {
        int i_random = (rand() % (iMAX - iMIN + 1)) + iMIN;                         // Création des coordonnées aléatoires
        int j_random = (rand() % (jMAX - jMIN + 1)) + jMIN;
        if (map[i_random][j_random] == -78)                                            // Si la case est égale à une case contenant un obstacle
        {
            cpt--;                                                                  // On décrémente le compteur
        }
        else
        {
            map[i_random][j_random] = 178;
        }
    }
}

void affichage_carte(char map[taille_x][taille_y])
{
    
    int i, j;
    printf(" ");                     //décale le tableau d'un espace du bord (plus propre): espace pour la premiere ligne
    for(i = 0; i < taille_x; i++)
    {
        for(j = 0; j < taille_y; j++)
        {
            printf("%c", map[i][j]);
        }
        printf("\n ");               ////décale le tableau d'un espace du bord (plus propre): espace apres le \n
    }
}

void affichage_better_map(char map[taille_x][taille_y])
{
    int i, j, r;
    printf("\n");
    for(i=0; i<taille_x; i++)
    {
        for(r=0; r<((237-taille_y-taille_y)/2) ;r++)             //Permet de centrer la carte
        {
            printf(" ");
        }
        for(j=0; j<taille_y; j++)
        {
            if(map[i][j]== -78)
            {
                Color(7,0);
                printf("%c",map[i][j]);
                printf("%c",map[i][j]);
                Color(15,0);
            }
            else if(map[i][j]== 0)
            {
                Color(8,0);
                printf("%c ",250);
                Color(15,0);
            }
            else if(map[i][j]== 79)
            {
                Color(0,2);
                printf("%c%c",91,93);
                Color(15,0);
            }
            else
            {
                printf("%c ",map[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void deplacement_tank(int *coord_x, int *coord_y, int add_coord_x, int add_coord_y, char map[taille_x][taille_y])
{
    //*coordonneeX et *coordonneeY sont les coordonnées en X et Y de tank qui va se déplacer
    if ((*coord_x + add_coord_x) > 0 && (*coord_x + add_coord_x) < taille_x)
    {
        if ((*coord_y + add_coord_y) > 0 && (*coord_x + add_coord_y) < taille_y)
        {
            if(map[*coord_x+add_coord_x][*coord_y+add_coord_y] != 79)
            {
                if(map[*coord_x+add_coord_x][*coord_y+add_coord_y] != -78)
                {
                    printf("prochaine case : %d\n", map[*coord_x+add_coord_x][*coord_y+add_coord_y]);
                    map[*coord_x][*coord_y] = 0;
                    *coord_x = *coord_x + add_coord_x;
                    *coord_y = *coord_y + add_coord_y;
                    map[*coord_x][*coord_y] = 79;
                }
                else
                    printf("Il y a un obstacle sur cette case !\n");
            }
            else
                printf("Il y a un tank sur cette case !\n");
        }
        else
            printf("Limite de carte atteinte (Y) \n");
    }
    else
    {
        printf("Limite de carte atteinte (X) \n");
    }
}

/*
 
 char destruc_obs_tank(map[i][j])
 {
 map[i][j] = '0';
 
 return map[i][j];
 }
 
 char tir_tank(int coord_tank_x, int coord_tank_y, int dit_tir, int taille_map, char map[i][j])
 {
 if (dir_tir == 0){
 for(int i = coord_tank_x; i > 0; i--)
 {
 if(map[i][coord_tank_y] == '79')
 {
 destruc_obs_tank(map[i][coord_tank_y]);
 return map[i][j];            // j'ai un doute pour ici, pas envie que ça retourne la map;
 //il faut peut-être faire un vois et ne rien retourner,
 //la map sera modifiée par la fonction destruc_obs_tank
 
 }
 if(map[i][coord_tank_y] == '-78')
 {
 destruc_obs_tank(map[i][coord_tank_y]);
 return map[i][j];
 }
 }
 }
 if (dir_tir == 90){
 for(int j = coord_tank_y; j > taille_map - 1; j++)
 {
 if (map[coord_tank_x][j] = '79')
 {
 destruc_obs_tank(map[coord_tank_x][j])
 return map[i][j];
 }
 if (map[coord_tank_x][j] = '-78')
 {
 destruc_obs_tank(map[coord_tank_x][j])
 return map[i][j];
 }
 }
 }
 
 
 
 if (dir_tir == 180){
 for(int i = coord_tank_x; i > taille_map - 1; i++)
 {
 if (map[i][coord_tank_y] = '79')
 {
 destruc_obs_tank(map[i][coord_tank_y)
 return map[i][j];
 }
 if (map[i][coord_tank_y] = '-78')
 {
 destruc_obs_tank(map[i][coord_tank_y])
 return map[i][j];
 }
 }
 }
 
 
 if (dir_tir == 240){
 for(int j = coord_tank_y; j > 0; j--)
 {
 if (map[coord_tank_x][j] = '79')
 {
 destruc_obs_tank(map[coord_tank_x][j])
 return map[i][j];
 }
 if (map[coord_tank_x][j] = '-78')
 {
 destruc_obs_tank(map[coord_tank_x][j])
 return map[i][j];
 }
 }
 }
 
 
 }
 
 */

int choix_joueurs(int nb_j)
{
    Color(4,0);
    printf_ligne1();
    Color(12,0);
    printf_center("Veuillez saisir le nombre de joueurs, de 2 a 120.\n");
    printf_center(" ");
    Color(10,0);
    scanf("%d",&nb_j);
    Color(15,0);
    printf("\n\n\n");
    if (nb_j>1 && nb_j<121)
    {
        return nb_j;
    }
    else
    {
        Color(14,0);
        printf_center("Erreur de saisie !\n\n");
        Color(15,0);
        choix_joueurs(nb_j);
    }
}

void generate_tab_scores(int nb_j, int haut, char tab_scores[haut][nb_j])
{
    int i, j;
    for (i = 0; i < haut; i++)
    {
        for (j = 0; j < nb_j; j++)
        {
            if (i=0)
            {
                tab_scores[i][j] = j+1;
            }
            else
            {
                tab_scores[i][j] = 0;
            }
        }
    }
    printf("test");
}

void affichage_tab_scores(int nb_j, int haut, char tab_scores[haut][nb_j])
{
    int i, j;
    printf("\n\n");
    printf_ligne1();
    printf("\n");
    for (i = 0; i < haut; i++)
    {
        for (j = 0; j < nb_j; j++)
        {
            if (j=0)
            {
                printf("%c",178);
                printf(" Joueurs %d ", tab_scores[i][j]);
            }
            else
            {
                printf("%c",178);
                printf("     %d     ", tab_scores[i][j]);
            }
        }
        printf("\n\n");
    }
    printf("\n");
    printf_ligne1();
}

void choix_map()
{
    int variable_a_tout_faire;                      //sers a enregistrer le choix de la map.
    printf("Veuillez choisir votre carte :  (Message a modifié plus tard):JULES");
    
    scanf("%c", variable_a_tout_faire);
    
}

void tanks_game_luncher(char map[taille_x][taille_y])
{
    presentation();                                //mettez cette fonction en commentaire pour passer la presentation
    //choix_map();
    creation_carte(map);
    generation_obstacles (50, map);
    int nb_j = choix_joueurs(&nb_j);
    int haut = 3;
    unsigned char tab_scores[haut][nb_j];
    //generate_tab_scores(nb_j, haut, tab_scores);
    printf("test");
    //affichage_tab_scores(nb_j, haut, tab_scores);
    printf("test\n\n\n\n");
    //generation_tank();
    //gestion_tours();choix_joueurs();
    affichage_carte(map);
    affichage_better_map(map);
}


int main()
{
    unsigned char map[taille_x][taille_y];      //Ne pas retirer cette ligne (initialisation de notre tableau.)
    tanks_game_luncher(map);  //jeux officiel (tout ce que n'es pas test, donc officiel)
    
    //ZONE DE TEST
    srand(time(NULL));
    int coord_tank_x = (rand() % ((taille_x - 2) - 1))+1;
    int coord_tank_y = (rand() % ((taille_y - 2) - 1))+1;
    int add_coord_x = (rand() % 3) - 1;
    int add_coord_y = (rand() % 3) - 1;
    
    map[coord_tank_x][coord_tank_y] = 79;                                             //initialisation poss tank
    
    int i;
    for (i = 0; i < 7 ; i++)
    {
        printf("\n");
        deplacement_tank(&coord_tank_x, &coord_tank_y, add_coord_x, add_coord_y, map);
        //affichage_carte(map);
        //system("cls");
        affichage_better_map(map);
        add_coord_x = (rand() % 3) - 1;
        add_coord_y = (rand() % 3) - 1;
    }
    return 0;
}

/*
 void DeplacementTank(int *CoordoneeX, int *coordonneeY, int addCoordX, int addCoordY, int TailleX, int TailleY){ //addCoordX et addCoordY doivent avoir pour valeur -1, 0, ou 1
 //*coordonneeX et *coordonneeY sont les coordonnées en X et Y de tank qui va se déplacer
 while (addCoordX <= 1 && addcoordX >= 1 || addCoordY <= 1 && addcoordY >= 1) {
 if ((*coordonneeX + addCoordX) > 0 && (*coordonneeX + addCoordX) < TailleX){         //TAILLEX est la taille du tableau en X
 if ((*coordonneeY + addCoordY) > 0 && (*coordonneeY + addCoordY) < TailleY){    //TAILLEY est la taille du tableau en Y
 *CoordoneeX = *coordonneeX + addCoordX;
 *CoordoneY = *coordonneeY + addCoordY;
 }
 }
 else{
 printf("erreur dans la saisit des nouvelles coordonnées, la taille du tableau n'est pas respecté ou la distance à laquelle vous voulez vous déplacer est impossible");
 }
 }
 */

