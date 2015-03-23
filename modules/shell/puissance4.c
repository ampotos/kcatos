#include "puissance4.h"
#include "morpion.h"
#include "string.h"
#include <utils/print.h>

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

int	saisircoup(int remplissage[7], char *line, size_t *row)
{
	int	z;

	terminal_setpos(2, (*row)++);
	printf("Entrez une colonne entre <0-6>:");

	do
		{
			terminal_setpos(2, (*row)++);
			printf("                                                                            ");
			terminal_setpos(2, *row - 1);
			while(get_input_line(line, BLOC_SIZE) == -1);
			z = my_getnbr(line);
			if (jouable(remplissage, z) == 1)
				 return z;
			terminal_setpos(2, (*row)++);
			printf("Essaies une autre, celle-ci est remplie !"); // VERT
			(*row) -= 2;
		}
	while (jouable(remplissage, z) != 1);

	return -1;
}

void	afficherGrille(char grille[6][7])
{
	int	i;
	int	j;
	size_t	row = 2;
	uint8_t	saveColor = terminal_getcolor();


	clean();
	draw_window("Connect Four", 0, 0, 0, 18, COLOR_LIGHT_GREY, COLOR_BROWN);
	terminal_setcolor(make_color(COLOR_LIGHT_GREY, COLOR_BROWN));

	for (i = 0;i < 6; i++)
		{
			terminal_setpos(23, row++);
			printf("+---+---+---+---+---+---+---+");
			terminal_setpos(23, row++);
			for (j = 0;j < 7; j++)
			{
				putc('|');
				putc(' ');
				dispMove(grille[5-i][j]);
				putc(' ');
			}
			printf("| %d", i);
		}
	terminal_setpos(23, row++);
	printf("+---+---+---+---+---+---+---+");
	terminal_setpos(23, row++);
	for (j = 0; j <= 6; j++)
			printf("  %d ", j);

	terminal_setpos(0, row + 2);

	terminal_setcolor(saveColor);
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
	char	grille[6][7];
	int remplissage[7];
	size_t	row = 20;
	uint8_t	saveColor = terminal_getcolor();

	args = args;
	for (i = 0;i < 6; i++)
		for (j = 0;j < 7; j++)
			grille[i][j] = ' ';
	for(j = 0;j < 7; j++)
		remplissage[j] = 0;
	afficherGrille(grille);
	while (win)
	{
		row = 20;
		draw_window("Player Space", 0, 18, 0, 7, COLOR_BLACK, (joueur % 2 != 0 ? COLOR_RED : COLOR_GREEN));
		terminal_setcolor(make_color(COLOR_BLACK, (joueur % 2 != 0 ? COLOR_RED : COLOR_GREEN)));

		if (joueur % 2 == 0)
		{
			colonne = saisircoup(remplissage, line, &row);
			ligne = remplissage[colonne];
			grille[ligne][colonne] = 'O';
			remplissage[colonne] = remplissage[colonne] + 1;
			compt1++;
			afficherGrille(grille);
			if (partieEstGagneeOuPas(grille, colonne, ligne) == 1)
			{
				draw_window("Player Space", 0, 18, 0, 5, COLOR_BLACK, (joueur % 2 != 0 ? COLOR_RED : COLOR_GREEN));
				terminal_setcolor(make_color(COLOR_BLACK, (joueur % 2 != 0 ? COLOR_RED : COLOR_GREEN)));
				terminal_setpos(2, 20);
				printf("joueur 1 gagne au %deme coup", compt1 / 2 + 1); // VERT
				win = 0;
			}
		}

		if(joueur % 2 != 0)
		{	
			colonne = saisircoup(remplissage, line, &row);
			ligne = remplissage[colonne];
			grille[ligne][colonne] = 'X';
			remplissage[colonne] = remplissage[colonne] + 1;
			compt1++;
			afficherGrille(grille);
			if (partieEstGagneeOuPas(grille, colonne, ligne) == 1)
			{
				draw_window("Player Space", 0, 18, 0, 5, COLOR_BLACK, (joueur % 2 != 0 ? COLOR_RED : COLOR_GREEN));
				terminal_setcolor(make_color(COLOR_BLACK, (joueur % 2 != 0 ? COLOR_RED : COLOR_GREEN)));
				terminal_setpos(2, 20);
				printf("joueur 2 gagne au %deme coup", compt1 / 2); // VERT
				win = 0;
			}
		}

		joueur = joueur + 1;

		if (remplissage[0] == 6 && remplissage[1] == 6 && remplissage[2] == 6 && remplissage[3] == 6 && remplissage[4] == 6 && remplissage[5] == 6 && remplissage[6] == 6)
		{
			draw_window("Player Space", 0, 18, 0, 5, COLOR_BLACK, COLOR_BLUE);
			terminal_setcolor(make_color(COLOR_BLACK, COLOR_BLUE));
			terminal_setpos(2, 20);
			printf("egalite"); //ROUGE
			win = 0;
		}

		terminal_setcolor(saveColor);
	}

	terminal_setpos(0, 23);
	return (0);
}
