#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <pthread.h>


#include "character.h"
#include "map.h"
#include "screen.h"
#include "playerControl.h"
#include "enemyControl.h"


int stage =1;

void recursiveGaming(){
	settingGame();
	
    pthread_t thread_0;
    
    /*
    // 스레드 생성 및 실행
    if (pthread_create(&thread_0, NULL, enemyControl, 0) != 0) {
        fprintf(stderr, "Failed to create thread 0\n");
    }*/
    
	while (gameOver==0) {
	 batchGhostNpackMan();
     mapPrint();
    
     playerCheck();
     enemyControl();
     
     if (_kbhit()) {
            char key = _getch();
            
            switch (key) {
                case 'a':
                    if (packmanMap[pacMan.position.x][pacMan.position.y-1] != -1) pacMan.position.y--;
                    break;
                case 'w':
                    if (packmanMap[pacMan.position.x-1][pacMan.position.y] != -1) pacMan.position.x--;
                    break;
                case 'd':
                    if (packmanMap[pacMan.position.x][pacMan.position.y+1] != -1) pacMan.position.y++;
                    break;
                case 's':
                    if (packmanMap[pacMan.position.x+1][pacMan.position.y] != -1) pacMan.position.x++;
                    break;
                case 'q':
                    gameOver = 1;
                    break;

            }
        
        }
    }

    if(gameOver==1){
    	 system("cls");
         printf("게임 오버\n");
         return;
	}
    
    if(gameOver==2){
     system("cls");
     printf("%d 스테이지 승리, 다음스테이지를 기다려주세요\n",stage++);
     printf("%d %d %d %d ",ghosts[0].position.x,ghosts[0].position.y,ghosts[1].position.x,ghosts[1].position.y) ;
     gameOver=0;
     sleep(30);
     return recursiveGaming();
	 }  
}

int main(void) {
    initializeArrays();
    recursiveGaming();
    return 0;
}

