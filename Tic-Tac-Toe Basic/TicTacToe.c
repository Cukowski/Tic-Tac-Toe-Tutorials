#include <stdio.h>

#define SIZE 3 // board size

char board[SIZE][SIZE]; // Tic-Tac_toe board

void initializeBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' '; // empty cell
        }
    }
}

void displayBoard() {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|"); // column seperator
        }
        printf("\n");
        if (i < SIZE - 1) printf("---+---+---\n"); // row seperator
    }
    printf("\n");
}

void playerMove(char player) {
    int row, col;
    while (1)
    {
        printf("Player %c, enter a row (1-3) and column (1-3): ", player);
        scanf("%d %d", &row, &col);

        if (row >= 1 && row <= 3 && col >= 1 && col <= 3 && board[row-1][col-1] == ' ') {
            board[row-1][col-1] = player;
            break;
        } else {
            printf("Invalid Move! Try again!\n");
        }
    }
}

char checkWinner() {
    for (int i = 0; i < SIZE; i++) {
        // Check rows and cols
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return board[i][0];
        } 
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            return board[0][i];
        } 
    }
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        return board[0][0];
    }     
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        return board[0][2];
    } 

    return ' '; // no winner yet
}

int isBoardFull() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] ==' ') {
                return 0; // board is not full
            }
        }
    }
    return 1; // board is full
}

int main() {
    char winner = ' ';
    char currentPlayer = 'X';

    initializeBoard();

    while (1)
    {
        displayBoard();
        playerMove(currentPlayer);

        winner = checkWinner(); // ' ' 'X' 'O'

        if (winner != ' ') {
            displayBoard();
            printf("Player %c wins!\n", winner);
            break;
        }

        if (isBoardFull()) {
            displayBoard();
            printf("It's a tie!\n");
            break;
        }

        // Switch players
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0;
}