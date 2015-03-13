#include <stdio.h>

#define NB_LIG 3
#define NB_COL 3

typedef enum {FALSE, TRUE} Boolean;
static char	grille[NB_LIG][NB_COL];
static char	prochainJoueur = 'O';

void		initialiseGrille()
{
  int		i;
  int		j;

  for (i = 0; i < NB_LIG; i++)
    {
      for (j = 0; j < NB_COL; j++)
	{
	  grille[i][j] = ' ';
	}
    }
}

void afficherGrille()
{
  printf("\n\n\n");
  printf("+-----+\n");
  printf("|%c|%c|%c|\n", grille[0][0], grille[0][1], grille[0][2]);
  printf("+-----+\n");
  printf("|%c|%c|%c|\n", grille[1][0], grille[1][1], grille[1][2]);
  printf("+-----+\n");
  printf("|%c|%c|%c|\n", grille[2][0], grille[2][1], grille[2][2]);
  printf("+-----+\n");
  printf("\n\n\n");
}

void		metUnPionSurLaGrille()
{
  int		ligne;
  int		col;
  Boolean	saisieCorrecte = FALSE;

  printf("Numeros de ligne et de colonne: ");

  do
    {
      /* ##### A enlever le scanf et faire par la suite un read ##### */
      scanf("%d %d", &ligne, &col);
      printf("\n");

      if ((ligne > 0) && (ligne <= NB_LIG) && (col > 0) && (col <= NB_COL))
	{
	  ligne--;
	  col--;
	  if (grille[ligne][col] != ' ')
	    printf("Cette case a deja ete remplie. Veuillez recommencer: \n");
	  else
	    {
	      saisieCorrecte = TRUE;
	      grille[ligne][col] = prochainJoueur;
	      if (prochainJoueur == 'O')
		prochainJoueur = 'X';
	      else
		prochainJoueur = 'O';
	    }
	}
      else
	printf("Indice de ligne ou de colonne incorrect. Veuillez recommencer:\n");
    } while (!saisieCorrecte);
}

Boolean		testeFinJeu()
{
  int		i;
  int		j;
  int		joueurGagnant;
  Boolean	estFini = FALSE;

  if (grille[1][1] != ' ')
    {
      if (((grille[0][1] == grille[1][1]) && (grille[1][1] == grille[2][1])) ||
	  ((grille[1][0] == grille[1][1]) && (grille[1][1] == grille[1][2])) ||
	  ((grille[0][0] == grille[1][1]) && (grille[1][1] == grille[2][2])) ||
	  ((grille[0][2] == grille[1][1]) && (grille[1][1] == grille[2][0])))
	{
	  joueurGagnant = grille[1][1];
	  estFini = TRUE;
	}
    }

  if ((!estFini) && (grille[0][0] != ' '))
    {
      if (((grille[0][0] == grille[0][1]) && (grille[0][1] == grille[0][2])) ||
	  ((grille[0][0] == grille[1][0]) && (grille[1][0] == grille[2][0])))
	{
	  joueurGagnant = grille[0][0];
	  estFini = TRUE;
	}
    }

  if ((!estFini) && (grille[2][2] != ' '))
    {
      if (((grille[2][0] == grille[2][1]) && (grille[2][1] == grille[2][2])) ||
	  ((grille[0][2] == grille[1][2]) && (grille[1][2] == grille[2][2])))
	{
	  joueurGagnant = grille[2][2];
	  estFini = TRUE;
	}
    }

  if (estFini)
    {
      printf("Felicitations au joueur ayant les ");
      if (joueurGagnant == 'O')
	printf("ronds ");
      else
	printf("croix ");
      printf("qui a gagne.\n");
      return TRUE;
    }

  for (i = 0; i < NB_LIG; i++)
    {
      for (j = 0; j < NB_COL; j++)
	{
	  if (grille[i][j] == ' ')
	    return FALSE;
	}
    }
  return TRUE;
}

int	main()
{
  initialiseGrille();
  do
    {
      metUnPionSurLaGrille();
      afficherGrille();
    }
  while (!testeFinJeu());
  return (0);
}

