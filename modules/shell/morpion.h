#ifndef _MORPION_H_
# define _MORPION_H_
	
#define NB_LIG 3
#define NB_COL 3

typedef enum {FALSE, TRUE} Boolean;




void		initialiseGrille(char grille1[3][3]);
void 		afficherGrille1(char grille1[3][3]);
int			my_getnbr(char *str);
void		metUnPionSurLaGrille(char grille1[3][3], char *prochainJoueur);
Boolean		testeFinJeu(char grille1[3][3]);
int			tictactoe(char *args);



#endif /* _MORPION_H_ */

