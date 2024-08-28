#include <stdio.h>
#include <conio.h>

#define cols 20
#define rows 10
#define food 25
#define SNAKE_MAX_LEN 256;

char screen[cols * rows];

int gameOver = 0;

int snakeX = 5;
int snakeY = 5;
/*
typedef struct{
    int x, y;
}SnakePartStruct, *SnakePart;

typedef struct{
    int length
    SnakePart body[SNAKE_MAX_LEN];
}SnakeStruct, *Snake;

struct Snake snake; */

void fill_screen(){
    int x, y;

    for (y = 0; y < rows; y++){
        for (x = 0; x < cols; x++){
            if(x == 0 ||y == 0 || x == cols-1 || y == rows-1){
                screen[y*cols + x] = '#';
            }else{
                screen[y*cols + x] = ' ';
            }
        } 
    }
}

void print_screen(){
    int x, y;
    for(y = 0; y < rows; y++){
        for(x = 0; x < cols; x++){
            putch(screen[y*cols + x]);
            }        
            putch('\n');
        } 
    }

void draw_snake(){
    screen[snakeY * cols + snakeX] = '@';
    /*for(int i = snake.length-1; i >= 0; i--){
        screen[snakeY * cols + snakeX]
    }*/
}

void move_snake(int deltaX, int deltaY){
    snakeX += deltaX;
    snakeY += deltaY;
}

void read_keyboard(){
    int ch = getch();

    switch(ch){
        case 'w': move_snake(0, -1); break;
        case 's': move_snake(0, 1); break;
        case 'a': move_snake(-1, 0); break;
        case 'd': move_snake(1, 0); break;
        case 'q' : gameOver = 1, printf("Game exited. \n"); break;
    }
}

int main(){
    while(!gameOver){
    fill_screen();
    draw_snake();
    print_screen();
    read_keyboard();
    
    }
    
    return 0;
}