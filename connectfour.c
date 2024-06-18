#include <stdio.h>
#include <windows.h>

// 05 mayo 2024
// Edgar Martinez
// Description:
//     	Connect 4:
//	   	input is the column name:
//
//      | A | B | C | D | E | F | G |
//
//      |+++|+++|+++|+++|+++|+++|+++|
//		| X | O | O |	|   |   |   |
//		|+++|+++|+++|+++|+++|+++|+++|

#define ROWS 6
#define COLS 7
#define FOUR 4

// subroutines declarations:
// - - - - - - - - - - - - -

void init_board(char bins[][COLS]);
void print_board(char header[], char separator[], char bins[][COLS]);
void fill_bin(char player, char bins[][COLS]);
void blue();
void yellow();
void reset();
int search_four(char player, char bins[][COLS]);
int check_for_draw(char bins[][COLS]);

// main function or driver function:
// - - - - - - - - - - - - - - - - -

int main()
{
	int gameover = 0;
	int draw = 0;
	int turn = 0;

	char player;

	char bins[ROWS][COLS];
	char header[] = "| A | B | C | D | E | F | G |";
	char separator[] = "|+++|+++|+++|+++|+++|+++|+++|";

	init_board(bins);
	print_board(header, separator, bins);

	while (!gameover)
	{
		// Show who's turn is it
		player = (turn++ % 2 == 0) ? 'O':'X';
		printf("\nPlayer %c's turn: ", player);

		// Fill the corresponding column with player's token
		fill_bin(player, bins);

		// Update the board
		print_board(header, separator, bins);

		// Check if a player has won
		gameover = search_four(player, bins);

		// Check if there is a draw
		draw = check_for_draw(bins);

		// Check termination conditions
		if (gameover)
			printf("\nCongratulations, player %c has won!\n", player);
        else if (draw)
        {
            printf("\nDraw! Game over...\n");
            gameover = 1;
        }

	}

	return 0;
}

// subroutines definitions:
// - - - - - - - - - - - -

void print_board(char header[], char separator[], char bins[][COLS])
{
	int row, col;

	printf("%s\n\n", header);

	for (int row = 0; row < ROWS; ++row)
	{
		printf("%s\n", separator);
		for (int col = 0; col < COLS; ++col)
		{
			printf("| ");
			if (bins[row][col] == 'O')
				blue();
			if (bins[row][col] == 'X')
				yellow();
			printf("%c ", bins[row][col]);

			reset();
		}
		printf("|\n");
	}

	printf("%s\n", separator);
}

void init_board(char bins[][COLS])
{
	int row, col;

	for (int row = 0; row < ROWS; ++row)
		for (int col = 0; col < COLS; ++col)
			bins[row][col] = ' ';
}

void fill_bin(char player, char bins[][COLS])
{
	int row;		// row iterator 0...5
	int col;		// column iterator 0...6

	char column;	// column: A B C D E F G

	int full_column;

	do
	{
		full_column = 0;

		printf("\nChoose column: A B C D E F G: ");
		scanf(" %c", &column);

		switch (column)
		{
			case 'A':
			case 'a':
				col = 0;
				break;
			case 'B':
			case 'b':
				col = 1;
				break;
			case 'C':
			case 'c':
				col = 2;
				break;
			case 'D':
			case 'd':
				col = 3;
				break;
			case 'E':
			case 'e':
				col = 4;
				break;
			case 'F':
			case 'f':
				col = 5;
				break;
			case 'G':
			case 'g':
				col = 6;
				break;
			default:
				printf("\nWrong column! Try again.");
				col = 666;
		}

		// Only if user chooses the right column
		if (col != 666)
		{
			if ((bins[0][col] == 'O') || (bins[0][col] == 'X'))
			{
				printf("\nColumn %c is full!", column);
				full_column = 1;
			}
		}

	} while ((col == 666) || full_column);

	// Search from the bottom to the top
	for (row = ROWS-1; row >= 0; row--)
	{
		if (bins[row][col] == ' ')
		{
			bins[row][col] = player;
			break;
		}
	}

}

void blue()
{
    int color_number = 243;

    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (color_number & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

void yellow()
{
    int color_number = 246;

    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (color_number & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

void reset()
{
    int color_number = 255;

    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (color_number & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

int search_four(char player, char bins[][COLS])
{

	int row, col, count;

	// search horizontal
	for (row = 0; row < ROWS; ++row)
	{
		count = 0;
		for (col = 0; col < COLS; ++col)
		{
			if (bins[row][col] == player)
			{
				count++;
				if (count == FOUR)
					return 1;
			}
			else if (bins[row][col] == ' ')
				count = 0;
			else
				count = 0;
		}

	}	// row for ends

	// search vertical
	for (col = 0; col < COLS; ++col)
	{
		count = 0;
		for (row = 0; row < ROWS; ++row)
		{
			if (bins[row][col] == player)
			{
				count++;
				if (count == FOUR)
					return 1;
			}
			else if (bins[row][col] == ' ')
				count = 0;
			else
				count = 0;
		}
	}	// col for ends

	// search diagonals
	struct point
	{
		int r;
		int c;
		int moves;
	};

	struct point pairs[] =
	{
		{0, 0, 4},
		{0, 0, 5},
		{0, 0, 6},
		{0, 0, 6},
		{0, 0, 5},
		{0, 0, 4}
	};

	int NOPAIRS = 6;
	int p;
	int n;

	// search diagonal -> & v (row++ & col++)

	//      | A | B | C | D | E | F | G |
	//
	//      |+++|+++|+++|+++|+++|+++|+++|
	//		| P | P | P | P	|   |   |   |
	//		|+++|+++|+++|+++|+++|+++|+++|
	//		| P | * | * | *	| * |   |   |
	//		|+++|+++|+++|+++|+++|+++|+++|
	//		| P | * | * | *	| * | * |   |
	//		|+++|+++|+++|+++|+++|+++|+++|
	//		|   | * | * | *	| * | * | * |
	//		|+++|+++|+++|+++|+++|+++|+++|
	//		|   |   | * | *	| * | * | * |
	//		|+++|+++|+++|+++|+++|+++|+++|
	//		|   |   |   | *	| * | * | * |
	//		|+++|+++|+++|+++|+++|+++|+++|

	pairs[0].r = 0;
	pairs[0].c = 3;

	pairs[1].r = 0;
	pairs[1].c = 2;

	pairs[2].r = 0;
	pairs[2].c = 1;

	pairs[3].r = 0;
	pairs[3].c = 0;

	pairs[4].r = 1;
	pairs[4].c = 0;

	pairs[5].r = 2;
	pairs[5].c = 0;

	// iterate through each pair:
	for (p = 0; p < NOPAIRS; ++p)
	{
		// move diagonally
		count = 0;
		for (n = 0; n < pairs[p].moves; ++n)
		{
			if (bins[pairs[p].r + n][pairs[p].c + n] == player)
			{
				count++;
				if (count == FOUR)
					return 1;
			}
			else if (bins[row][col] == ' ')
				count = 0;
			else
				count = 0;
		}
	}

	// search diagonal -> & A (row-- & col++)

	//      | A | B | C | D | E | F | G |
	//
	//      |+++|+++|+++|+++|+++|+++|+++|
	//		|   |   |   | *	| * | * | * |
	//		|+++|+++|+++|+++|+++|+++|+++|
	//		|   |   | * | *	| * | * | * |
	//		|+++|+++|+++|+++|+++|+++|+++|
	//		|   | * | * | *	| * | * | * |
	//		|+++|+++|+++|+++|+++|+++|+++|
	//		| P | * | * | *	| * | * |   |
	//		|+++|+++|+++|+++|+++|+++|+++|
	//		| P | * | * | *	| * |   |   |
	//		|+++|+++|+++|+++|+++|+++|+++|
	//		| P | P | P | P	|   |   |   |
	//		|+++|+++|+++|+++|+++|+++|+++|

	pairs[0].r = 3;
	pairs[0].c = 0;

	pairs[1].r = 4;
	pairs[1].c = 0;

	pairs[2].r = 5;
	pairs[2].c = 0;

	pairs[3].r = 5;
	pairs[3].c = 1;

	pairs[4].r = 5;
	pairs[4].c = 2;

	pairs[5].r = 5;
	pairs[5].c = 3;

	// iterate through each pair:
	for (p = 0; p < NOPAIRS; ++p)
	{
		// move diagonally
		count = 0;
		for (n = 0; n < pairs[p].moves; ++n)
		{
			if (bins[pairs[p].r - n][pairs[p].c + n] == player)
			{
				count++;
				if (count == FOUR)
					return 1;
			}
			else if (bins[row][col] == ' ')
				count = 0;
			else
				count = 0;
		}
	}

	// default condition: four tokens not found
	return 0;

}

int check_for_draw(char bins[][COLS])
{
    int counter = 0;

    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            if ((bins[i][j] == 'O') || (bins[i][j] == 'X'))
                counter++;
        }
    }

    // return true if the board is full, namely 42 tokens are found.
    if (counter >= (ROWS * COLS))
        return 1;
    else
        return 0;
}
