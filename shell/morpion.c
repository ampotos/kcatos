#include <stdio.h>
#include "morpion.h"
#include "string.h"
#include "puissance4.h"

void		initialiseGrille(char grille1[3][3])
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

void afficherGrille1(char grille1[3][3])
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

void		metUnPionSurLaGrille(char grille1[3][3], char *line, char *prochainJoueur)
{
  int		ligne;
  int		col;
  Boolean	saisieCorrecte = FALSE;

  do
    {
      printf("Numeros de ligne: \n"); // VERT
      line = get_input_line(line);
      ligne = my_getnbr(line);
      printf("Numeros de colonne: \n"); // VERT
      line = get_input_line(line);
      col = my_getnbr(line);
      printf("\n");

      if ((ligne > 0) && (ligne <= NB_LIG) && (col > 0) && (col <= NB_COL))
	{
	  ligne--;
	  col--;
	  if (grille1[ligne][col] != ' ')
	    printf("Cette case a deja ete remplie. Veuillez recommencer: \n"); // ROUGE
	  else
	    {
	      saisieCorrecte = TRUE;
	      grille1[ligne][col] = *prochainJoueur;
	      if (*prochainJoueur == 'O')
		*prochainJoueur = 'X';
	      else
	*prochainJoueur = 'O';
	    }
	}
      else
	printf("Indice de ligne ou de colonne incorrect. Veuillez recommencer:\n"); // ROUGE
    } while (!saisieCorrecte);
}

Boolean		testeFinJeu(char grille1[3][3])
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
      printf("Felicitations au joueur ayant les "); // VERT
      if (joueurGagnant == 'O')
	printf("ronds "); // VERT
      else
	printf("croix "); // VERT
      printf("qui a gagne.\n"); // VERT
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

int	tictactoe(char **args, char *line)
{
  char grille1[NB_LIG][NB_COL];
  char prochainJoueur = 'O';

  args = args;
  initialiseGrille(grille1);
  do
    {
      metUnPionSurLaGrille(grille1, line, &prochainJoueur);
      afficherGrille1(grille1);
    }
  while (!testeFinJeu(grille1));
  return (0);
}

