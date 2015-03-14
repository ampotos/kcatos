#ifndef _MORPION_H_
# define _MORPION_H_
	
#define NB_LIG 3
#define NB_COL 3

typedef enum {FALSE, TRUE} Boolean;
static char	grille1[NB_LIG][NB_COL];
static char	prochainJoueur = 'O';




void		initialiseGrille();
void afficherGrille1();
int	my_getnbr(char *str);
void		metUnPionSurLaGrille();
Boolean		testeFinJeu();
int	tictactoe(char **args);



#endif /* _MORPION_H_ */

