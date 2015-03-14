#include <stdio.h>
#include "morpion.h"
#include "string.h"
#include "puissance4.h"

void		initialiseGrille()
{
  int		i;
  int		j;

  for (i = 0; i < NB_LIG; i++)
    {
      for (j = 0; j < NB_COL; j++)
	{
	  grille1[i][j] = ' ';
	}
    }
}

void afficherGrille1()
{
  printf("\n\n\n");
  printf("+-----+\n");
  printf("|%c|%c|%c|\n", grille1[0][0], grille1[0][1], grille1[0][2]);
  printf("+-----+\n");
  printf("|%c|%c|%c|\n", grille1[1][0], grille1[1][1], grille1[1][2]);
  printf("+-----+\n");
  printf("|%c|%c|%c|\n", grille1[2][0], grille1[2][1], grille1[2][2]);
  printf("+-----+\n");
  printf("\n\n\n");
}

void		metUnPionSurLaGrille()
{
  int		ligne;
  int		col;
  Boolean	saisieCorrecte = FALSE;

  do
    {
      printf("Numeros de ligne: \n");
      get_input_line();
      ligne = my_getnbr(line);
      printf("Numeros de colonne: \n");
      get_input_line();
      col = my_getnbr(line);
      printf("\n");

      if ((ligne > 0) && (ligne <= NB_LIG) && (col > 0) && (col <= NB_COL))
	{
	  ligne--;
	  col--;
	  if (grille1[ligne][col] != ' ')
	    printf("Cette case a deja ete remplie. Veuillez recommencer: \n");
	  else
	    {
	      saisieCorrecte = TRUE;
	      grille1[ligne][col] = prochainJoueur;
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

  if (grille1[1][1] != ' ')
    {
      if (((grille1[0][1] == grille1[1][1]) && (grille1[1][1] == grille1[2][1])) ||
	  ((grille1[1][0] == grille1[1][1]) && (grille1[1][1] == grille1[1][2])) ||
	  ((grille1[0][0] == grille1[1][1]) && (grille1[1][1] == grille1[2][2])) ||
	  ((grille1[0][2] == grille1[1][1]) && (grille1[1][1] == grille1[2][0])))
	{
	  joueurGagnant = grille1[1][1];
	  estFini = TRUE;
	}
    }

  if ((!estFini) && (grille1[0][0] != ' '))
    {
      if (((grille1[0][0] == grille1[0][1]) && (grille1[0][1] == grille1[0][2])) ||
	  ((grille1[0][0] == grille1[1][0]) && (grille1[1][0] == grille1[2][0])))
	{
	  joueurGagnant = grille1[0][0];
	  estFini = TRUE;
	}
    }

  if ((!estFini) && (grille1[2][2] != ' '))
    {
      if (((grille1[2][0] == grille1[2][1]) && (grille1[2][1] == grille1[2][2])) ||
	  ((grille1[0][2] == grille1[1][2]) && (grille1[1][2] == grille1[2][2])))
	{
	  joueurGagnant = grille1[2][2];
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
	  if (grille1[i][j] == ' ')
	    return FALSE;
	}
    }
  return TRUE;
}

int	tictactoe(char **args)
{
  args = args;
  initialiseGrille();
  do
    {
      metUnPionSurLaGrille();
      afficherGrille1();
    }
  while (!testeFinJeu());
  return (0);
}

