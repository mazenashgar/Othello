//***************************************************
// Filename: othello.c
//
// Author: Jarod Collier, Maz Ashgar, Joe Hartsough
//***************************************************

#include "othello.h"

// Displays the board (as SIZE x SIZE grid) on console
void displayBoard(char board[][SIZE]) {
    
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        printf((i == 0 ? "%5d" : "%3d"), i + 1);
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%2d", i + 1);
        for (int j = 0; j < SIZE; j++) {
            printf("%3c", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Initializes the board with start configuration of discs (see project specs)
void initializeBoard(char board[][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if ((row == 3 && col == 3) || (row == 4 && col == 4)) {
                board[row][col] = BLACK;
            } else if ((row == 3 && col == 4) || (row == 4 && col == 3)) {
                board[row][col] = WHITE;
            } else
                board[row][col] = EMPTY;
        }
    }
}

// Returns true if moving the disc to location row,col is valid; else returns false
bool isValidMove(char board[][SIZE], int row, int col, char disc) {

    if (board[row][col] == EMPTY) {

        bool validDirection = false;

        if (disc == BLACK) {
            if ((board[row][col - 1] == WHITE && board[row][col - 2] != EMPTY) ||
                (board[row - 1][col - 1] == WHITE && board[row - 2][col - 2] != EMPTY) ||
                (board[row - 1][col] == WHITE && board[row - 2][col] != EMPTY) ||
                (board[row - 1][col + 1] == WHITE && board[row - 2][col + 2] != EMPTY) ||
                (board[row][col + 1] == WHITE && board[row][col + 2] != EMPTY) ||
                (board[row + 1][col + 1] == WHITE && board[row + 2][col + 2] != EMPTY) ||
                (board[row + 1][col] == WHITE && board[row + 2][col] != EMPTY) ||
                (board[row + 1][col - 1] == WHITE && board[row + 2][col - 2] != EMPTY)) {
            } else {
                return false;
            }
        } else {
            if ((board[row][col - 1] == BLACK && board[row][col - 2] != EMPTY) ||
                (board[row - 1][col - 1] == BLACK && board[row - 2][col - 2] != EMPTY) ||
                (board[row - 1][col] == BLACK && board[row - 2][col] != EMPTY) ||
                (board[row - 1][col + 1] == BLACK && board[row - 2][col + 2] != EMPTY) ||
                (board[row][col + 1] == BLACK && board[row][col + 2] != EMPTY) ||
                (board[row + 1][col + 1] == BLACK && board[row + 2][col + 2] != EMPTY) ||
                (board[row + 1][col] == BLACK && board[row + 2][col] != EMPTY) ||
                (board[row + 1][col - 1] == BLACK && board[row + 2][col - 2] != EMPTY)) {
            } else {
                return false;
            }
        }

        // Checking for another disc going left
        if (board[row][col - 1] != EMPTY && (col - 1) != 0) {
            for (int temp = col - 1; temp > 0; temp--) {
                if (board[row][temp] == disc) validDirection = true;
            }
            for (int leftCol = col - 1; leftCol > 0; leftCol--) {
                if (board[row][leftCol] != disc && board[row][leftCol - 1] != EMPTY && (leftCol - 1) != 0 && validDirection) {
                    return true;
                }
            }
        }

        // Checking for another disc going right
        validDirection = false;
        if (board[row][col + 1] != EMPTY && (col + 1) != 8) {
            for (int temp = col + 1; temp < 8; temp++) {
                if (board[row][temp] == disc) validDirection = true;
            }
            for (int rightCol = col + 1; rightCol < 8; rightCol++) {
                if (board[row][rightCol] != disc && board[row][rightCol + 1] != EMPTY && (rightCol + 1) != 8 && validDirection) {
                    return true;
                }
            }
        }

        // Checking for another disc going up
        validDirection = false;
        if (board[row - 1][col] != EMPTY && (row - 1) != 0) {
            for (int i = row - 1; i > 0; i--) {
                if (board[i][col] == disc) validDirection = true;
            }
            for (int upRow = row - 1; upRow > 0; upRow--) {
                if (board[upRow][col] != disc && board[upRow - 1][col] != EMPTY && (upRow - 1) != 0 && validDirection) {
                    return true;
                }
            }
        }

        // Checking for another disc going down
        validDirection = false;
        if (board[row + 1][col] != EMPTY && (row + 1) != 8) {
            for (int upRow = row + 1; upRow < 8; upRow++) {
                for (int i = row + 1; i < 8; i++) {
                    if (board[i][col] == disc) validDirection = true;
                }
                if (board[upRow][col] != disc && board[upRow + 1][col] != EMPTY && (upRow + 1) != 8 && validDirection) {
                    return true;
                }
            }
        }

        // Checking for another disc going diagonal up left
        validDirection = false;
        if (board[row - 1][col - 1] != EMPTY && (col - 1) != 0 && (row - 1) != 0) {

            // Checks whether row or col is smaller
            int upDiagLeft, currentLocation = 0, count = 1;
            if (row <= col) upDiagLeft = row;
            else upDiagLeft = col;

            for (int i = upDiagLeft; i > 0; i--) {
                if (board[row - count][col - count] == disc) validDirection = true;
                count++;
            }
            count = 1;
            //for (upDiagLeft; upDiagLeft > 0; upDiagLeft--) {
            if (board[row - count][col - count] != disc && (col - count) != 0 && (row - count) != 0 && validDirection) {
                return true;
            }
            currentLocation++;
            count++;
            //}
        }

        // Checking for another disc going diagonal down right
        validDirection = false;
        if (board[row + 1][col + 1] != EMPTY && (col + 1) != 8 && (row + 1) != 8) {

            // Checks whether row or col is smaller
            int downDiagRight, currentLocation = 0, count = 1;
            if (row >= col) downDiagRight = row;
            else downDiagRight = col;

            for (int i = downDiagRight; i < 8; i++) {
                if (board[row + count][col + count] == disc) validDirection = true;
                count++;
            }
            count = 1;
            //for (downDiagRight; downDiagRight < 8; downDiagRight++) {
            if (board[row + count][col + count] != disc && (col + count) != 8 && (row + count) != 8 && validDirection) {
                return true;
            }
            currentLocation++;
            count++;
            //}
        }

        // Checking for another disc going diagonal down left
        validDirection = false;
        if (board[row + 1][col - 1] != EMPTY && (col - 1) != 0 && (row + 1) != 8) {

            // Checks if row + col is less than 10 to know where the cut off is
            int downDiagLeft, currentLocation = 0, count = 1;
            if (row + col < 10) {
                downDiagLeft = col;
                for (int i = downDiagLeft; i > 0; i--) {
                    if(board[row + count][col - count] == disc) validDirection = true;
                    count++;
                }
                count = 1;
                //for (downDiagLeft; downDiagLeft > 0; downDiagLeft--) {
                if (board[row + count][col - count] != disc && (col - count) != 0 && (row + count) != 8 && validDirection) {
                    return true;
                }
                currentLocation++;
                count++;
                //}

            } else {
                downDiagLeft = row;
                for (int i = downDiagLeft; i < 8; i++) {
                    if(board[row + count][col - count] == disc) validDirection = true;
                    count++;
                }
                count = 1;
                //for (downDiagLeft; downDiagLeft < 8; downDiagLeft++) {
                if (board[row + count][col - count] != disc && (col - count) != 0 && (row + count) != 8 && validDirection) {
                    return true;
                }
                currentLocation++;
                count++;
                //}
            }
        }

        // Checking for another disc going diagonal up right
        validDirection = false;
        if (board[row - 1][col + 1] != EMPTY && (col + 1) != 8 && (row - 1) != 0) {

            // Checks if row + col is less than 10 to know how far to check
            int upDiagRight, currentLocation = 0, count = 1;
            if (row + col < 10) {
                upDiagRight = row;
                for (int i = upDiagRight; i > 0; i--) {
                    if(board[row - count][col + count] == disc) validDirection = true;
                    count++;
                }
                count = 1;
                //for (upDiagRight; upDiagRight > 0; upDiagRight--) {
                if (board[row - count][col + count] != disc && (col + count) != 8 && (row - count) != 0 && validDirection) {
                    return true;
                }
                currentLocation++;
                count++;
                //}

            } else {
                upDiagRight = col;
                for (int i = upDiagRight; i < 8; i++) {
                    if(board[row - count][col + count] == disc) validDirection = true;
                    count++;
                }
                count = 1;
                //for (upDiagRight; upDiagRight < 8; upDiagRight++) {
                if (board[row - count][col + count] != disc && (col + count) != 8 && (row - count) != 0 && validDirection) {
                    return true;
                }
                currentLocation++;
                count++;
                //}
            }
        }
    }
    return false;
}

// Places the disc at location row,col and flips the opponent discs as needed
void placeDiscAt(char board[][SIZE], int row, int col, char disc) {

    //place the disc
    board[row][col] = disc;
    bool validDirection = false;

    // Checking for flips going left
    if (board[row][col - 1] != EMPTY && (col - 1) != 0) {
        for (int temp = col - 1; temp > 0; temp--) {
            if (board[row][temp] == disc) validDirection = true;
        }
        for (int leftCol = col - 1; leftCol > 0; leftCol--) {
            if (board[row][leftCol] != disc && board[row][leftCol] != EMPTY && (leftCol) != 0 && validDirection) {
                board[row][leftCol] = disc;
            } else break;
        }
    }

    validDirection = false;
    // Checking for flips going right
    if (board[row][col + 1] != EMPTY && (col + 1) != 8) {
        for (int temp = col + 1; temp < 8; temp++) {
            if (board[row][temp] == disc) validDirection = true;
        }
        for (int rightCol = col + 1; rightCol < 8; rightCol++) {
            if (board[row][rightCol] != disc && board[row][rightCol] != EMPTY && (rightCol) != 8 && validDirection) {
                board[row][rightCol] = disc;
            } else break;
        }
    }

    validDirection = false;
    // Checking for flips going up
    if (board[row - 1][col] != EMPTY && (row - 1) != 0) {
        for (int i = row - 1; i > 0; i--) {
            if (board[i][col] == disc) validDirection = true;
        }
        for (int upRow = row - 1; upRow > 0; upRow--) {
            if (board[upRow][col] != disc && board[upRow - 1][col] != EMPTY && (upRow) != 0 && validDirection) {
                board[upRow][col] = disc;
            } else break;
        }
    }

    validDirection = false;
    // Checking for flips going down
    if (board[row + 1][col] != EMPTY && (row + 1) != 8) {
        for (int i = row + 1; i < 8; i++) {
            if (board[i][col] == disc) validDirection = true;
        }
        for (int upRow = row + 1; upRow < 8; upRow++) {
            if (board[upRow][col] != disc && board[upRow + 1][col] != EMPTY && (upRow) != 8 && validDirection) {
                board[upRow][col] = disc;
            } else break;
        }
    }

    // Checking for flips going  up left
    validDirection = false;
    if (board[row - 1][col - 1] != EMPTY && (col - 1) != 0 && (row - 1) != 0) {

        // Checks whether row or col is smaller
        int upDiagLeft, currentLocation = 0, count = 1;
        if (row <= col) upDiagLeft = row;
        else upDiagLeft = col;

        for (int i = upDiagLeft; i > 0; i--) {
            if (board[row - count][col - count] == disc) validDirection = true;
            count++;
        }
        count = 1;
        for (upDiagLeft; upDiagLeft > 0; upDiagLeft--) {
            if ((board[row - count][col - count] == disc || board[row - count][col - count] != EMPTY) &&
                (col - count) != 0 && (row - count) != 0 && validDirection) {
                board[row - currentLocation][col - currentLocation] = disc;
                currentLocation++;
                count++;
            } else break;
        }
    }

    // Checking for flips going diagonal down right
    validDirection = false;
    if (board[row + 1][col + 1] != EMPTY && (col + 1) != 8 && (row + 1) != 8) {

        // Checks whether row or col is smaller
        int downDiagRight, currentLocation = 0, count = 1;
        if (row >= col) downDiagRight = row;
        else downDiagRight = col;

        for (int i = downDiagRight; i < 8; i++) {
            if (board[row + count][col + count] == disc) validDirection = true;
            count++;
        }
        count = 1;
        for (downDiagRight; downDiagRight < 8; downDiagRight++) {
            if ((board[row + count][col + count] == disc || board[row + count][col + count] != EMPTY) &&
                (col + count) != 8 && (row + count) != 8 && validDirection) {
                board[row + currentLocation][col + currentLocation] = disc;
                currentLocation++;
                count++;
            } else break;
        }
    }

    // Checking for flips going diagonal down left
    validDirection = false;
    if (board[row + 1][col - 1] != EMPTY && (col - 1) != 0 && (row + 1) != 8) {

        // Checks if row + col is less than 10 to know where the cut off is
        int downDiagLeft, currentLocation = 0, count = 1;
        if (row + col < 10) {
            downDiagLeft = col;
            for (int i = downDiagLeft; i > 0; i--) {
                if(board[row + count][col - count] == disc) validDirection = true;
                count++;
            }
            count = 1;
            for (downDiagLeft; downDiagLeft > 0; downDiagLeft--) {
                if ((board[row + count][col - count] == disc || board[row + count][col - count] != EMPTY) &&
                    (col - count) != 0 && (row + count) != 8 && validDirection) {
                    board[row + currentLocation][col - currentLocation] = disc;
                    currentLocation++;
                    count++;
                } else break;
            }

        } else {
            downDiagLeft = row;
            for (int i = downDiagLeft; i < 8; i++) {
                if(board[row + count][col - count] == disc) validDirection = true;
                count++;
            }
            count = 1;
            for (downDiagLeft; downDiagLeft < 8; downDiagLeft++) {
                if ((board[row + count][col - count] == disc || board[row + count][col - count] != EMPTY) &&
                    (col - count) != 0 && (row + count) != 8 && validDirection) {
                    board[row + currentLocation][col - currentLocation] = disc;
                    currentLocation++;
                    count++;
                } else break;
            }
        }
    }

    // Checking for flips going diagonal up right
    validDirection = false;
    if (board[row - 1][col + 1] != EMPTY && (col + 1) != 8 && (row - 1) != 0) {

        // Checks if row + col is less than 10 to know how far to check
        int upDiagRight, currentLocation = 0, count = 1;
        if (row + col < 10) {
            upDiagRight = row;
            for (int i = upDiagRight; i > 0; i--) {
                if(board[row - count][col + count] == disc) validDirection = true;
                count++;
            }
            count = 1;
            for (upDiagRight; upDiagRight > 0; upDiagRight--) {
                if ((board[row - count][col + count] == disc || board[row - count][col + count] != EMPTY) &&
                    (col + count) != 8 && (row - count) != 0 && validDirection) {
                    board[row - currentLocation][col + currentLocation] = disc;
                    currentLocation++;
                    count++;
                } else break;
            }

        } else {
            upDiagRight = col;
            for (int i = upDiagRight; i < 8; i++) {
                if(board[row - count][col + count] == disc) validDirection = true;
                count++;
            }
            count = 1;
            for (upDiagRight; upDiagRight < 8; upDiagRight++) {
                if ((board[row - count][col + count] == disc || board[row - count][col + count] != EMPTY) &&
                    (col + count) != 8 && (row - count) != 0 && validDirection) {
                    board[row - currentLocation][col + currentLocation] = disc;
                    currentLocation++;
                    count++;
                } else break;
            }
        }
    }
}

// Returns true if a valid move for disc is available; else returns false
bool isValidMoveAvailable(char board[][SIZE], char disc) {

    //Variable to count how many possible moves there are
    int possibleMoves = 0;

    // loops through each space on the board and checks if current disc could be placed
    for (int row = 1; row <= SIZE; row++) {
        for (int col = 1; col <= SIZE; col++) {
            possibleMoves++;
        }
    }
    if (possibleMoves > 0)
        return true;
    else
        return false;
}

// Returns true if the board is fully occupied with discs; else returns false
bool isBoardFull(char board[][SIZE]) {
    for (int row = 1; row <= SIZE; row++) {
        for (int col = 1; col <= SIZE; col++) {
            if (board[row][col] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

// Returns true if either the board is full or a valid move is not available for either disc
bool isGameOver(char board[][SIZE]) {
    if (isBoardFull(board) || !isValidMoveAvailable(board, WHITE) ||
        !isValidMoveAvailable(board, BLACK)) {
        return true;
    }
    return false;
}

// If there is a winner, it returns the disc (BLACK or WHITE) associated with the winner.
// In case of a tie, it returns EMPTY
char checkWinner(char board[][SIZE]) {
    int countBlack = 0;
    int countWhite = 0;

    for (int row = 1; row <= SIZE; row++) {
        for (int col = 1; col <= SIZE; col++) {
            if (board[row][col] == WHITE)
                countWhite++;
            if (board[row][col] == BLACK) {
                countBlack++;
            }
        }
        if (countBlack > countWhite) {
            return BLACK;
        } else if (countBlack < countWhite) {
            return WHITE;
        } else {
            return EMPTY;
        }
    }
}
