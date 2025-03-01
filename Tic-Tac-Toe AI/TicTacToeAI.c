#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 3 // board size
#define PLAYER 'X'
#define AI 'O'

char board[SIZE][SIZE]; // 3 * 3 grid, Tic-Tac-Toe board

// Initialize the board with empty spaces
void initializeBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' '; // empty cell
        }
    }
}

// Display the board
void displayBoard() {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("---+---+---\n");
    }
    printf("\n");
}

// Handle player move
void playerMove(char player) {
    int row, col;
    while (1) {
        printf("Player %c, enter a row (1-3) and column (1-3): ", player);
        scanf("%d %d", &row, &col);

        if (row >= 1 && row <= 3 && col >= 1 && col <= 3 && board[row-1][col-1] == ' ') {
            board[row-1][col-1] = player;
            break;
        } else {
            printf("Invalid Move! Try Again!\n");
        }
    }
}

// Evaluate the board to determine the game state
int evaluate() {
    for (int i = 0; i < SIZE; i++) {
        // Check rows and cols
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            if (board[i][0] == AI) {
                return 10;
            } else {
                return -10;
            }
        } 
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            return (board[0][i] == AI) ? 10 : -10;
        }
    }
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        return (board[0][0] == AI) ? 10 : -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        return (board[0][2] == AI) ? 10 : -10;
    }

    return 0; // no winner yet!
}

// Check if any moves are left
int isMovesLeft() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
           if (board[i][j] == ' ') {
            return 1; // moves left
           }
        }
    }
    return 0; // no moves left
}

// Minimax algortihm to find the best move
int minimax(int depth, int isMax) {
    int score = evaluate();
    if (score == 10 || score == -10) return score;
    if (!isMovesLeft()) return 0;

    int best = isMax ? INT_MIN : INT_MAX;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = isMax ? AI : PLAYER;
                int value = minimax(depth + 1, !isMax);
                best = isMax ? ((value > best) ? value : best) : ((value < best) ? value : best);
                board[i][j] = ' ';
            }
        }
    }
    return best;
}

// Find the best move for the AI
void findBestMove(int* bestRow, int* bestCol) {
    int bestVal = INT_MIN;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = AI;
                int moveVal = minimax(0, 0);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    *bestRow = i;
                    *bestCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }
}

int main() {
    char winner = ' ';
    char currentPlayer = PLAYER;
    initializeBoard();

    while (1) {
        displayBoard();
        if (currentPlayer == PLAYER) {
            playerMove(PLAYER);
        } else {
            int bestRow, bestCol;
            findBestMove(&bestRow, &bestCol);
            board[bestRow][bestCol] = AI;
        }

        winner = evaluate();
        if (winner == 10 || winner == -10) {
            displayBoard();
            printf("Player %c wins!\n", (winner == 10) ? AI : PLAYER);
            break;
        }
        if (isMovesLeft() == 0) {
            displayBoard();
            printf("It's a tie!\n");
            break;
        }

        currentPlayer = (currentPlayer == PLAYER) ? AI : PLAYER;
    }
    return 0;
}