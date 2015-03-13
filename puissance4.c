#include <stdio.h>
#include <stdlib.h>

char	grille[6][7];
int	remplissage[7];

int	dansGrille(int x,int y)
{
  if ((x >= 0) && (x <= 5) && (y >= 0) && (y <= 6))
    return 1;
  else
    return 0;
}

int	jouable(int x)
{
  if (x >=0 && (x < 7) && remplissage[x] >= 0 && remplissage[x] < 6)
    return 1;
  else
    return 0;
}

int	saisircoup()
{
  int	z;

  do
    {
      printf("\t      rentrez une colonne entre <0-6>:\n\t essaies une autre si celle-ci est remplie!\n");
      scanf("%d", &z);
      if (jouable(z) == 1)
	return z;
    }
  while (jouable(z) != 1);
}

void	afficherGrille()
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

int	estRemplieOuNon()
{
  int	x;
  int	comp=0;

  for (x = 0; x <= 6; x++)
    if (jouable(x))
      comp = comp + 1;
  if (comp == 0)
    return 1;
  else
    return 0;
}

int	adjacent(int c, int l,int dirV, int dirH)
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

int partieEstGagneeOuPas(int c,int l)
{

  if ((adjacent(c,l,0,1)+adjacent(c,l,0,-1))>=3 ||
      (adjacent(c,l,1,0)+adjacent(c,l,-1,0))>=3 ||
      (adjacent(c,l,1,1)+adjacent(c,l,-1,-1))>=3 ||
      (adjacent(c,l,1,-1) + adjacent(c,l,-1,1)>=3))
    return 1;
  else
    return 0;
}

main ()
{
  int win = 1;
  int i;
  int j;
  int joueur = 0;
  int colonne;
  int ligne;
  int compt1 = 0;

  afficherGrille();
  for (i = 0;i < 6; i++)
    for (j = 0;j < 7; j++)
      grille[i][j] = ' ';
  for(j = 0;j < 7; j++)
    remplissage[j] = 0;
  while (win)
    {
      if (joueur % 2 == 0)
	{
	  printf("posez votre pion joueur 1\n");
	  colonne=saisircoup();
	  ligne=remplissage[colonne];
	  grille[ligne][colonne] = 'O';
	  remplissage[colonne] = remplissage[colonne] + 1;
	  compt1++;
	  afficherGrille();
	  if (partieEstGagneeOuPas(colonne, ligne) == 1)
	    {
	      printf("joueur 1 gagne au %deme coup\n", compt1 / 2 + 1);
	      win = 0;
	    }
	}
      if(joueur % 2 != 0)
	{
	  printf("posez votre pion joueur 2\n");
	  colonne = saisircoup();
	  ligne = remplissage[colonne];
	  grille[ligne][colonne] = 'X';
	  remplissage[colonne] = remplissage[colonne] + 1;
	  compt1++;
	  afficherGrille();
	  if (partieEstGagneeOuPas(colonne, ligne) == 1)
	    {
	      printf("joueur 2 gagne au %deme coup\n", compt1 / 2);
	      win = 0;
	    }
	}
      joueur = joueur + 1;
    }
}
