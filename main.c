#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EMPTY 0
#define ZERO 1
#define CROSS 2
#define EMPTY_SYMBOL '_'
#define ZERO_SYMBOL 'O'
#define CROSS_SYMBOL 'X'

struct Field
{
    int field[3][3];
};

void clearScreen(){
    system("cls");
}

void clearField(struct Field *Field){
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            Field->field[y][x] = EMPTY;
        }
    }
}

void printField(struct Field *Field){
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            int value = Field->field[y][x];

            if (value == EMPTY)
                printf("%c ", EMPTY_SYMBOL); 
            if (value == ZERO)
                printf("%c ", ZERO_SYMBOL); 
            if (value == CROSS)
                printf("%c ", CROSS_SYMBOL);
        }
        printf("\n");
    }
}

int getPlayerStep(){
    int step = -1;

    while (free) {
        printf("Your step: ");
        scanf("%d", &step);

        if ((step >= 0) && (step <= 9)) break;
        printf("\nTry again. ");
    }
    
    return step;
}

int getComputerStep(){
    int step = rand() % 9;
    return step;
}

int numberToPosition(int *x, int *y, int number){
    if (number == 0) {
        *x = 0;
        *y = 0;
    }
    if (number == 1) {
        *x = 1;
        *y = 0;
    }
    if (number == 2) {
        *x = 2;
        *y = 0;
    }
    if (number == 3) {
        *x = 0;
        *y = 1;
    }
    if (number == 4) {
        *x = 1;
        *y = 1;
    }
    if (number == 5) {
        *x = 2;
        *y = 1;
    }
    if (number == 6) {
        *x = 0;
        *y = 2;
    }
    if (number == 7) {
        *x = 1;
        *y = 2;
    }
    if (number == 8) {
        *x = 2;
        *y = 2;
    }
}

int isFree(struct Field *Field, int x, int y){
    return Field->field[y][x] == EMPTY;
}

void makeStep(struct Field *Field, int x, int y, int isPlayer){
    if (isPlayer) {
        Field->field[y][x] = CROSS;
    }
    else {
        Field->field[y][x] = ZERO;
    }
}

void makePlayerStep(struct Field *Field){
    int x = 0;
    int y = 0;

    while (free) {
        int player_step = getPlayerStep();
        player_step = numberToPosition(&x, &y, player_step);
        if (isFree(Field, x, y)) {
            makeStep(Field, x, y, 0);
            break;
        }
    }
}

void makeComputerStep(struct Field *Field){
    int x = 0;
    int y = 0;

    while (free) {
        int player_step = getComputerStep();
        player_step = numberToPosition(&x, &y, player_step);
        if(isFree(Field, x, y)){
            makeStep(Field, x, y, 1);
            break;
        }
    }
}

int checkWin(struct Field *Field){
    if ((Field->field[0][0] == CROSS) && (Field->field[0][1] == CROSS) && (Field->field[0][2] == CROSS)) return CROSS;
    if ((Field->field[1][0] == CROSS) && (Field->field[1][1] == CROSS) && (Field->field[1][2] == CROSS)) return CROSS;
    if ((Field->field[2][0] == CROSS) && (Field->field[2][1] == CROSS) && (Field->field[2][2] == CROSS)) return CROSS;
    
    if ((Field->field[0][0] == CROSS) && (Field->field[1][0] == CROSS) && (Field->field[2][0] == CROSS)) return CROSS;
    if ((Field->field[0][1] == CROSS) && (Field->field[1][1] == CROSS) && (Field->field[2][1] == CROSS)) return CROSS;
    if ((Field->field[0][2] == CROSS) && (Field->field[1][2] == CROSS) && (Field->field[2][2] == CROSS)) return CROSS;

    if ((Field->field[0][0] == CROSS) && (Field->field[1][1] == CROSS) && (Field->field[2][2] == CROSS)) return CROSS;
    if ((Field->field[2][0] == CROSS) && (Field->field[1][1] == CROSS) && (Field->field[0][2] == CROSS)) return CROSS;
    
    if ((Field->field[0][0] == ZERO) && (Field->field[0][1] == ZERO) && (Field->field[0][2] == ZERO)) return ZERO;
    if ((Field->field[1][0] == ZERO) && (Field->field[1][1] == ZERO) && (Field->field[1][2] == ZERO)) return ZERO;
    if ((Field->field[2][0] == ZERO) && (Field->field[2][1] == ZERO) && (Field->field[2][2] == ZERO)) return ZERO;
    
    if ((Field->field[0][0] == ZERO) && (Field->field[1][0] == ZERO) && (Field->field[2][0] == ZERO)) return ZERO;
    if ((Field->field[0][1] == ZERO) && (Field->field[1][1] == ZERO) && (Field->field[2][1] == ZERO)) return ZERO;
    if ((Field->field[0][2] == ZERO) && (Field->field[1][2] == ZERO) && (Field->field[2][2] == ZERO)) return ZERO;

    if ((Field->field[0][0] == ZERO) && (Field->field[1][1] == ZERO) && (Field->field[2][2] == ZERO)) return ZERO;
    if ((Field->field[2][0] == ZERO) && (Field->field[1][1] == ZERO) && (Field->field[0][2] == ZERO)) return ZERO;

    return EMPTY;
}

int startGame(struct Field *Field){
    int x = 0;
    int y = 0;

    int winner = -1;

    while (free) {
        makePlayerStep(Field);
        winner = checkWin(Field);
        if ((winner == ZERO) || (winner == CROSS)) return winner;

        makeComputerStep(Field);
        winner = checkWin(Field);
        if ((winner == ZERO) || (winner == CROSS)) return winner;

        clearScreen();
        printField(Field);
    }

    return EMPTY;
}

int main(){
    srand((unsigned int)time(NULL));

    clearScreen();

    struct Field Field;
    struct Field *FieldLink = &Field;

    clearField(FieldLink);

    printField(FieldLink);

    int win = startGame(FieldLink);

    clearScreen();
    printField(FieldLink);

    if(win == EMPTY)
        printf("Nobody wins!");
    if(win == ZERO)
        printf("Player win!");
    if(win == CROSS)
        printf("Computer win!");

    return 0;
}
