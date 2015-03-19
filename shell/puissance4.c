#include "puissance4.h"
#include "string.h"

int	dansGrille(int x,int y)
{
  if ((x >= 0) && (x <= 5) && (y >= 0) && (y <= 6))
    return 1;
  else
    return 0;
}

int	jouable(int remplissage[7], int x)
{
  if (x >=0 && (x < 7) && remplissage[x] >= 0 && remplissage[x] < 6)
    return 1;
  else
    return 0;
}

int	my_getnbr(char *str)
{
  int	nbr;

  if (*str == '-')
    return (-my_getnbr(str + 1));
  if (*str == '+')
    return (my_getnbr(str + 1));
  nbr = 0;
  while (*str >= '0' && *str <= '9')
    nbr = nbr * 10 + (*(str++) - '0');
  return (nbr);
}

int	saisircoup(int remplissage[7], char *line)
{
  int	z;

  do
    {
      printf("\t      rentrez une colonne entre <0-6>:\n\t essaies une autre si celle-ci est remplie!\n"); // VERT
      line = get_input_line(line);
      z = my_getnbr(line);
      if (jouable(remplissage, z) == 1)
	       return z;
    }
  while (jouable(remplissage, z) != 1);
}

void	afficherGrille(char grille[6][7])
{
  int	i;
  int	j;

  for (i = 0;i < 6; i++)
    {
      printf("\t\t\t");
      printf("+-+-+-+-+-+-+-+");
      printf("\n");
      printf("\t\t\t");
      for (j = 0;j < 7; j++)
	printf("|%c", grille[5-i][j]);
      printf("|%d \n", i);
    }
  if (i == 6)
    printf("\t\t\t");
  printf("+-+-+-+-+-+-+-+");
  printf("\n");
  printf("\t\t\t");
  for (j = 0; j <= 6; j++)
      printf(" %d", j);
  printf("\n\n\t\t");
}

int	adjacent(char grille[6][7],int c, int l,int dirV, int dirH)
{
  int	n = 0;

  if(dirV == 0)
    {
      if (dirH == 1)
	{
	  while ((grille[l][c]) == (grille[l][c+1]) && (grille[l][c] != ' '))
	    {
	      n++;
	      c++;
	    }
	}
      else if (dirH == -1)
	{
	  while ((grille[l][c]) == (grille[l][c-1]) && (grille[l][c] != ' '))
	    {
	      n++;
	      c--;
	    }
	}
    }
  if (dirV == 1)
    {
      if (dirH == 0)
	{
	  while ((grille[l][c]) == (grille[l+1][c]) && (grille[l][c] != ' '))
	    {
	      n++;
	      l++;
	    }
	}
      else if (dirH == 1)
	{
	  while ((grille[l][c]) == (grille[l+1][c+1]) && (grille[l][c] != ' '))
	    {
	      n++;
	      c++;
	      l++;
	    }
	}
      else if (dirH == -1)
	{
	  while ((grille[l][c]) == (grille[l+1][c-1]) && (grille[l][c] != ' '))
	    {
	      n++;
	      c--;
	      l++;
	    }
	}
    }
  if (dirV == -1)
    {
      if (dirH == 0)
	{
	  while ((grille[l][c]) == (grille[l-1][c]) && (grille[l][c] != ' '))
	    {
	      n++;
	      l--;
	    }
	}
      else if (dirH == -1)
	{
	  while ((grille[l][c]) == (grille[l-1][c-1]) && (grille[l][c] != ' '))
	    {
	      n++;
	      c--;
	      l--;
	    }
	}
      else if (dirH == 1)
	{
	  while ((grille[l][c]) == (grille[l-1][c+1]) && (grille[l][c] != ' '))
	    {
	      n++;
	      c++;
	      l--;
	    }
	}
    }
  return (n);

}

int partieEstGagneeOuPas(char grille[6][7], int c,int l)
{

  if ((adjacent(grille, c,l,0,1)+adjacent(grille, c,l,0,-1))>=3 ||
      (adjacent(grille, c,l,1,0)+adjacent(grille, c,l,-1,0))>=3 ||
      (adjacent(grille, c,l,1,1)+adjacent(grille, c,l,-1,-1))>=3 ||
      (adjacent(grille, c,l,1,-1) + adjacent(grille, c,l,-1,1)>=3))
    return 1;
  else
    return 0;
}

int connectFour(char **args, char *line)
{
  int win = 1;
  int i;
  int j;
  int joueur = 0;
  int colonne;
  int ligne;
  int compt1 = 0;
  char  grille[6][7];
  int remplissage[7];

  args = args;
  for (i = 0;i < 6; i++)
    for (j = 0;j < 7; j++)
      grille[i][j] = ' ';
  for(j = 0;j < 7; j++)
    remplissage[j] = 0;
  afficherGrille(grille);
  while (win)
    {
      if (joueur % 2 == 0)
	{
	  printf("posez votre pion joueur 1\n"); // VERT
	  colonne=saisircoup(remplissage, line);
	  ligne=remplissage[colonne];
	  grille[ligne][colonne] = 'O';
	  remplissage[colonne] = remplissage[colonne] + 1;
	  compt1++;
	  afficherGrille(grille);
	  if (partieEstGagneeOuPas(grille, colonne, ligne) == 1)
	    {
	      printf("joueur 1 gagne au %deme coup\n", compt1 / 2 + 1); // VERT
	      win = 0;
	    }
	}
      if(joueur % 2 != 0)
	{
	  printf("posez votre pion joueur 2\n"); // VERT
	  colonne = saisircoup(remplissage, line);
	  ligne = remplissage[colonne];
	  grille[ligne][colonne] = 'X';
	  remplissage[colonne] = remplissage[colonne] + 1;
	  compt1++;
	  afficherGrille(grille);
	  if (partieEstGagneeOuPas(grille, colonne, ligne) == 1)
	    {
	      printf("joueur 2 gagne au %deme coup\n", compt1 / 2); // VERT
	      win = 0;
	    }
	}
      joueur = joueur + 1;
      if (remplissage[0] == 6 && remplissage[1] == 6 && remplissage[2] == 6 && remplissage[3] == 6 && remplissage[4] == 6 && remplissage[5] == 6 && remplissage[6] == 6)
	{
	  printf("égalité\n"); //ROUGE
	  win = 0;
	}
    }
}
