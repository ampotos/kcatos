#ifndef _PUISSANCE4_H_
# define _PUISSANCE4_H_

char	grille[6][7];
int	remplissage[7];

int	my_getnbr(char *str);
int	dansGrille(int x,int y);
int	jouable(int x);
int	saisircoup();
void	afficherGrille();
int	estRemplieOuNon();
int	adjacent(int c, int l,int dirV, int dirH);
int partieEstGagneeOuPas(int c,int l);
int connectFour(char *args);

#endif /* _PUISSANCE4_H_ */
