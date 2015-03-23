#include "morpion.h"
#include "string.h"
#include "puissance4.h"

void		initialiseGrille(char grille1[3][3])
{
	int		i;
	int		j;

	for (i = 0; i < NB_LIG; i++)
		for (j = 0; j < NB_COL; j++)
			grille1[i][j] = ' ';
}

void dispMove(char m)
{
	enum vga_color fg = terminal_fg_getcolor();

	if (m == 'X')
	{
		terminal_fg_setcolor(COLOR_RED);
		putc('X');
		terminal_fg_setcolor(fg);
	}
	else if (m == 'O')
	{
		terminal_fg_setcolor(COLOR_GREEN);
		putc('O');
		terminal_fg_setcolor(fg);
	}
	else
		putc(' ');
}

void afficherGrille1(char grille1[3][3])
{
	size_t	cnt;
	enum vga_color bgSave = terminal_bg_getcolor();
	
	if (draw_window("TicTacToe", 0, 0, 0, 11, COLOR_LIGHT_GREY, COLOR_BLUE) == -1)
	{
		printf("+-----+\n");
		printf("|%c|%c|%c|\n", make_color(COLOR_GREEN, COLOR_BLACK), grille1[0][0], make_color(COLOR_GREEN, COLOR_BLACK), grille1[0][1], grille1[0][2]);
		printf("+-----+\n");
		printf("|%c|%c|%c|\n", make_color(COLOR_GREEN, COLOR_BLACK), grille1[1][0], make_color(COLOR_GREEN, COLOR_BLACK), grille1[1][1], grille1[1][2]);
		printf("+-----+\n");
		printf("|%c|%c|%c|\n", grille1[2][0], grille1[2][1], grille1[2][2]);
		printf("+-----+\n");
		printf("\n\n\n");
	}
	else
	{
		terminal_bg_setcolor(COLOR_BLUE);
		cnt = 2;
		terminal_setpos(33, cnt++);
		puts_nolf("+---+---+---+");
		terminal_setpos(33, cnt++);
		puts_nolf("| "); dispMove(grille1[0][0]); puts_nolf(" | "); dispMove(grille1[0][1]); puts_nolf(" | "); dispMove(grille1[0][2]); puts_nolf(" |");
		terminal_setpos(33, cnt++);
		puts_nolf("+---+---+---+");
		terminal_setpos(33, cnt++);
		puts_nolf("| "); dispMove(grille1[1][0]); puts_nolf(" | "); dispMove(grille1[1][1]); puts_nolf(" | "); dispMove(grille1[1][2]); puts_nolf(" |");
		terminal_setpos(33, cnt++);
		puts_nolf("+---+---+---+");
		terminal_setpos(33, cnt++);
		puts_nolf("| "); dispMove(grille1[2][0]); puts_nolf(" | "); dispMove(grille1[2][1]); puts_nolf(" | "); dispMove(grille1[2][2]); puts_nolf(" |");
		terminal_setpos(33, cnt++);
		puts_nolf("+---+---+---+");
		terminal_bg_setcolor(bgSave);
		terminal_setpos(0, 12);
	}
}

void		metUnPionSurLaGrille(char grille1[3][3], char *prochainJoueur)
{
	int		ligne;
	int		col;
	Boolean	saisieCorrecte = FALSE;
	char	command[BLOC_SIZE];
	size_t	row = 13;
	uint8_t  saveColor = terminal_getcolor();

	draw_window("Player Zone", 0, 11, 0, 9, COLOR_BLACK, (*prochainJoueur == 'X' ? COLOR_RED : COLOR_GREEN));
	terminal_setcolor(make_color(COLOR_BLACK, (*prochainJoueur == 'X' ? COLOR_RED : COLOR_GREEN)));

	do
	{
		terminal_setpos(2, row++);
		printf("Numeros de ligne :");
		terminal_setpos(2, row++);
		while (get_input_line(command, BLOC_SIZE) == -1); // Do Something to avoig infinity loop
		ligne = my_getnbr(command);

		terminal_setpos(2, row++);
		printf("Numeros de colonne :");
		terminal_setpos(2, row++);
		while (get_input_line(command, BLOC_SIZE) == -1); // Do Something to avoig infinity loop
		col = my_getnbr(command);

		if ((ligne > 0) && (ligne <= NB_LIG) && (col > 0) && (col <= NB_COL))
		{
			ligne--;
			col--;
			if (grille1[ligne][col] != ' ')
			{
				draw_window("Player Zone", 0, 11, 0, 9, COLOR_BLACK, (*prochainJoueur == 'X' ? COLOR_RED : COLOR_GREEN));
				row = 13;
				terminal_setpos(2, row++);
				printf("Cette case a deja ete remplie. Veuillez recommencer");
			}
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
		{
			draw_window("Player Zone", 0, 11, 0, 9, COLOR_BLACK, (*prochainJoueur == 'X' ? COLOR_RED : COLOR_GREEN));
			row = 13;
			terminal_setpos(2, row++);
			printf("Indice de ligne ou de colonne incorrect. Veuillez recommencer");
		}
	} while (!saisieCorrecte);
	
	terminal_setcolor(saveColor);
}

Boolean		testeFinJeu(char grille1[3][3])
{
	int		i;
	int		j;
	int		joueurGagnant;
	Boolean	estFini = FALSE;
	uint8_t  saveColor = terminal_getcolor();

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
		clean();
		terminal_setcolor(make_color(COLOR_BLACK, (joueurGagnant == 'X' ? COLOR_RED : COLOR_GREEN)));
		draw_window("Player Zone", 0, 11, 0, 5, COLOR_BLACK, (joueurGagnant == 'X' ? COLOR_RED : COLOR_GREEN));
		terminal_setpos(2, 13);
		printf("Felicitations au joueur ayant les ");
		if (joueurGagnant == 'O')
			printf("ronds ");
		else
			printf("croix ");
		printf("qui a gagne.\n");
		terminal_setcolor(saveColor);
		return TRUE;
	}

	for (i = 0; i < NB_LIG; i++)
		for (j = 0; j < NB_COL; j++)
			if (grille1[i][j] == ' ')
				return FALSE;

	clean();
	terminal_setcolor(make_color(COLOR_BLACK, (joueurGagnant == 'X' ? COLOR_RED : COLOR_GREEN)));
	draw_window("Player Zone", 0, 11, 0, 5, COLOR_BLACK, (joueurGagnant == 'X' ? COLOR_RED : COLOR_GREEN));
	terminal_setpos(2, 13);
	printf("Egalite !");
	terminal_setcolor(saveColor);

	return TRUE;
}

int	tictactoe(char *args)
{
	char grille1[NB_LIG][NB_COL];
	char prochainJoueur = 'O';

	clean();

	args = args;
	initialiseGrille(grille1);
	do
		{
			afficherGrille1(grille1);
			metUnPionSurLaGrille(grille1, &prochainJoueur);
		}
	while (!testeFinJeu(grille1));
	afficherGrille1(grille1);
	terminal_setpos(0, 16);
	return (0);
}

