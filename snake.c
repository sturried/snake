#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define cols 40
#define rows 20
#define foodnum 25
#define SNAKE_MAX_LEN 256

char screen[cols * rows];

int gameOver = 0;

int snakeX = 5;
int snakeY = 5;

struct SnakePart{
    int x;
    int y;
};

struct Snake{
    int length;
    struct SnakePart body[SNAKE_MAX_LEN];
};

struct Snake snake; 

struct Food{
    int x;
    int y;
    int consumed;
};

struct Food food[foodnum];


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
   // screen[snakeY * cols + snakeX] = '@';
    for(int i = snake.length-1; i >= 0; i--){
        screen[snake.body[i].y * cols + snake.body[i].x] = '*';
    }
    screen[snake.body[0].y * cols + snake.body[0].x] = '@';
}

void move_snake(int deltaX, int deltaY){
    for(int i = snake.length-1; i > 0; i--){
        snake.body[i] = snake.body[i-1];
    }
    snake.body[0].x += deltaX;
    snake.body[0].y += deltaY;
}

void draw_food(){
    for(int i = 0; i < foodnum; i++){
        if(!food[i].consumed){
            screen[food[i].y*cols + food[i].x] = '+';
        }
    }
}

void setup_food(){
    for(int i = 0; i < foodnum; i++){
        food[i].x = 1 + rand() % (cols-2);
        food[i].y = 1 + rand() % (rows-2); 
        food[i].consumed = 0;
    }
}

void setup_snake(){
    snake.length = 1;
    snake.body[0].x = 1 + rand() % (cols-2);
    snake.body[0].y = 1 + rand() % (rows-2);
}

void game_rules(){
    for(int i = 0; i < foodnum; i++){
        if(!food[i].consumed){
            if(food[i].x == snake.body[0].x && food[i].y == snake.body[0].y){
                food[i].consumed = 1;
                snake.length++;
            }
        }
    }

    if(snake.body[0].x == 0 || snake.body[0].x == cols-1 || snake.body[0].y == 0 || snake.body[0].y == rows-1){
        gameOver = 1;
    }

    for(int j = 1; j < snake.length; j++){
        if(snake.body[0].x == snake.body[j].x && snake.body[0].y == snake.body[j].y){
            gameOver = 1;
        }
    }
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
    srand(time(0));
    setup_snake();
    setup_food();

    while(!gameOver){
        fill_screen();
        draw_snake();
        draw_food();
        
        game_rules();
        print_screen();

        read_keyboard();
        printf("Length: %d\n", snake.length);
        printf("Snakehead Position: X: %d  Y: %d\n", snake.body[0].x, snake.body[0].y);
    }
    
    return 0;
}