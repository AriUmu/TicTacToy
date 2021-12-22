#include <stdio.h>

#define EMPTY ' '
#define NUM_SQUARES 9

typedef struct {
    char cell[NUM_SQUARES];
} board;

void display_instruct() {
    printf(
            "Welcome to Tic-Tac-Toe!\n"
            "You will make your move known by entering a number, 0 - 8.  The number\n"
            "will correspond to the board position as illustrated:\n"
            " 0 | 1 | 2\n"
            " ---------\n"
            " 3 | 4 | 5\n"
            " ---------\n"
            " 6 | 7 | 8\n"
            "The ultimate battle is about to begin! \n"
            "You go the first!\n");
}

board new_board() {
    // Create new game board
    board round_board;
    for (int i = 0; i < NUM_SQUARES; i++) {
        round_board.cell[i] = EMPTY;
    }
    return round_board;
}

void display_board(board *board) {
    printf("\n %c | %c | %c", board->cell[0], board->cell[1], board->cell[2]);
    printf("\n ---------");
    printf("\n %c | %c | %c", board->cell[3], board->cell[4], board->cell[5]);
    printf("\n ---------");
    printf("\n %c | %c | %c \n", board->cell[6], board->cell[7], board->cell[8]);
}

int legal_moves(int num_cell, board *round_board, char sign) {
    if (round_board->cell[num_cell] == ' ') {
        round_board->cell[num_cell] = sign;
        return 0;
    } else {
        return 1;
    }
}

// 1 -neg ; 0 - pos
int human_move(int num_cell, board *round_board) {
    int result = legal_moves(num_cell, round_board, 'X');
    if (result == 1) {
        printf("\n This cell is occupied! Tru again!");
    }
    return result;
}

void computer_move(board *round_board) {
    int best_steps[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
    int res = 1;
    for (int i = 0; i < 9; i++) {
        while (res) {
            res = legal_moves(best_steps[i], round_board, 'O');
            if (res == 0) {
                break;
            }
            i++;
        }
    }
}

int winner(board *round_board) {
    char win = ' ';
    int WAYS_TO_WIN[8][3] = {{0, 1, 2},
                             {3, 4, 5},
                             {6, 7, 8},
                             {0, 3, 6},
                             {1, 4, 7},
                             {2, 5, 8},
                             {0, 4, 8},
                             {2, 4, 6}};

    for (int i = 0; i < 8; i ++){
        if(round_board->cell[WAYS_TO_WIN[i][0]] == round_board->cell[WAYS_TO_WIN[i][1]]
        && round_board->cell[WAYS_TO_WIN[i][1]] == round_board->cell[WAYS_TO_WIN[i][2]]
        && round_board->cell[WAYS_TO_WIN[i][2]] == round_board->cell[WAYS_TO_WIN[i][0]]
        && round_board->cell[WAYS_TO_WIN[i][0]] != ' '){
            win = round_board->cell[WAYS_TO_WIN[i][0]];
            printf("\nWon a player %c !!!", win);
            return 0;
        }
    }
    return 1;
}

int main() {
    display_instruct();
    board rond_board = new_board();
    display_board(&rond_board);
    int flag = 1;
    while (flag) {
        int res = 1;
        while (res) {
            printf("\n Print number of cell it 0:8 :");
            int num_cell = 0;
            scanf("%d", &num_cell);
            res = human_move((int) num_cell, &rond_board);
        }

        display_board(&rond_board);
        flag = winner(&rond_board);

        if(flag == 0){
            return 0;
        }
        computer_move(&rond_board);
        display_board(&rond_board);
        flag = winner(&rond_board);
    }
    return 0;
}
