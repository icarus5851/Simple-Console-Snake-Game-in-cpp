#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <sstream>
using namespace std;

    #define KEY_UP 72

    #define KEY_DOWN 80

    #define KEY_LEFT 75

    #define KEY_RIGHT 77

    bool gameover , boundary = false , ateyourself = false;
    const int width = 40;
    const int height = 26 ;
    int score;
    enum edirection {STOP = 0 , LEFT , RIGHT ,UP,DOWN};
    edirection direction;
    int headX ,headY , fruitX ,fruitY;
    int tailX[100] , tailY[100];
    int taillength = 0;

void init(){
    gameover = false;
    headX = width/2;
    headY = height/2;
    srand(time(0));
    fruitX = 1 + (rand() % (width-2)) ;
    fruitY = 1 + (rand() % (height-1));
    direction = STOP;
    score = 0 ; 
}

void draw(){
    system("cls");
    ostringstream buffer;
    buffer<< "Use arrow keys to control the snake.\n";
    for(int i = 0 ; i < width+1 ;i++){
        buffer << "#";
    }
    buffer<<endl;

    for(int  i = 0 ; i < height ; i++){
        for(int  j = 0 ; j < width  ; j++){
            if(j == 0 || j == width-1){
                buffer<<"#";
            }
            if(j == headX && i == headY){
                buffer<<"O";
            }
            else if(j == fruitX && i == fruitY){
                buffer<<"*";
            }
            else{
                bool tailprinted = false;
                for(int k = 0 ; k < taillength ; k++){
                    if(tailX[k] == j && tailY[k] == i){
                        buffer<<"o";
                        tailprinted = true;
                    }
                }
                if(!tailprinted)
                    buffer<<" ";
            }
        }
        buffer<<endl;
    }

    for(int i = 0 ; i < width+1 ;i++){
        buffer << "#";
    }
    buffer<<endl;

    buffer<< "\n \t Score : " << score;
    cout<<buffer.str();
}

void input(){

    if(_kbhit()){
        switch(_getch()){
            case KEY_LEFT:
            case 'a':
                if(direction != RIGHT) direction = LEFT;
                break;
            case KEY_RIGHT:
            case 'd':
                if(direction != LEFT) direction = RIGHT;
                break;
            case KEY_UP:
            case 'w':
                if(direction != DOWN) direction = UP;
                break;
            case KEY_DOWN:
            case 's':
                if(direction != UP) direction = DOWN;
                break;
            case 'x':
                direction = STOP;
                break;
            default:
                break;
        }
    }
}

void logic(){
    
    int prevx = tailX[0];
    int prevy = tailY[0];
    int tempx , tempy;
    tailX[0] = headX;
    tailY[0] = headY;
    for(int i = 1 ; i < taillength ; i++){
        tempx = tailX[i];
        tempy = tailY[i];
        tailX[i] = prevx;
        tailY[i] = prevy;
        prevx = tempx;
        prevy = tempy;
    }


    switch(direction)                 
    {
    case LEFT:
        headX--;
        break;
    case RIGHT:
        headX++;
        break;
    case UP:
        headY--;
        break;
    case DOWN:
        headY++;
        break;
    }
/*
    if (headX < 0 || headX >= width-1 || headY < 0 || headY > height-1) {
        gameover = true;
        boundary = true;
    }*/
   //pass through walls
    if(headX<0){
        headX = width-2;
    }
    else if(headX>=width-1){
        headX = 0;
    }
    if(headY<0){
        headY = height-1;
    }
    else if(headY>height-1){
        headY = 0;
    }

    for (int i = 0; i < taillength; i++) {
        if (tailX[i] == headX && tailY[i] == headY) {
            gameover = true;
            ateyourself = true;
        }
    }

    if(headX == fruitX && headY == fruitY){
        taillength++;
        srand(time(NULL)); 
        fruitX = 1 + (rand() % (width-2)) ;
        fruitY = 1 + (rand() % (height-1));
        if(headX == fruitX && headY == fruitY){
            srand(time(NULL)); 
            fruitX = 1 + (rand() % (width-2)) ;
            fruitY = 1 + (rand() % (height-1));
        }
        for(int i = 0; i < taillength ; i++){
            if(fruitX == tailX[i] && fruitY == tailY[i]){
                srand(time(NULL)); 
                fruitX = 1 + (rand() % (width-2)) ;
                fruitY = 1 + (rand() % (height-1));
            }
        }
        score += 10;
    }



}

int main(){
    init();
    while(!gameover){
        draw();
        input();
        logic();
        Sleep(80);
    }
    if(ateyourself){
        cout<<"\n \t you ate yourself\n";
    }
    if(boundary){
        cout<< "\n \t mapp crossed \n";
    }
    return 0;
}