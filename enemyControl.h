#pragma once
#include "DQN.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

int epsilon_greedy(int optimal_action) {
	double epsilon = 0.9; 
    int num_actions = 16; // 행동의 총 가짓수 (예: 16가지)
    int selected_action;
    
    double rand_num = (double)rand() / RAND_MAX;
    if (rand_num<= epsilon) {
        selected_action = rand() % num_actions; // 무작위 행동 선택
    } else {
        selected_action = optimal_action; // 최적 행동 선택
    }
    
    return selected_action;
}

double temp1,temp2;
void* enemyControl(){

	
	 srand(time(0));
	 int optimal_action = DQNprocess();
	 int result = epsilon_greedy(optimal_action);
	 switch (result) {
                case 0:
                    if (packmanMap[ghosts[0].position.x][ghosts[0].position.y-1] != -1)
					 ghosts[0].position.y--;
					if (packmanMap[ghosts[1].position.x][ghosts[1].position.y-1] != -1)
					 ghosts[1].position.y--;
                    break;
                case 1:
                    if (packmanMap[ghosts[0].position.x-1][ghosts[0].position.y] != -1) 
					 ghosts[0].position.x--;
					if (packmanMap[ghosts[1].position.x-1][ghosts[1].position.y] != -1) 
					 ghosts[1].position.x--;
                    break;
                case 2:
                    if (packmanMap[ghosts[0].position.x][ghosts[0].position.y+1] != -1) 
					 ghosts[0].position.y++;
					if (packmanMap[ghosts[1].position.x][ghosts[1].position.y+1] != -1) 
					 ghosts[1].position.y++;
                    break;
                case 3:
                    if (packmanMap[ghosts[0].position.x+1][ghosts[0].position.y] != -1) 
                     ghosts[0].position.x++;
                    if (packmanMap[ghosts[1].position.x+1][ghosts[1].position.y] != -1) 
                     ghosts[1].position.x++;
                    break;
                case 4:
                    if (packmanMap[ghosts[0].position.x][ghosts[0].position.y-1] != -1)
					 ghosts[0].position.y--;
					if (packmanMap[ghosts[1].position.x][ghosts[1].position.y+1] != -1)
					 ghosts[1].position.y++;
                    break;
                case 5:
                    if (packmanMap[ghosts[0].position.x][ghosts[0].position.y-1] != -1) 
					 ghosts[0].position.y--;
					if (packmanMap[ghosts[1].position.x-1][ghosts[1].position.y] != -1) 
					 ghosts[1].position.x--;
                    break;
                case 6:
                    if (packmanMap[ghosts[0].position.x][ghosts[0].position.y-1] != -1) 
					 ghosts[0].position.y--;
					if (packmanMap[ghosts[1].position.x+1][ghosts[1].position.y] != -1) 
					 ghosts[1].position.x++;
                    break;
                case 7:
                    if (packmanMap[ghosts[0].position.x+1][ghosts[0].position.y] != -1) 
                     ghosts[0].position.x++;
                    if (packmanMap[ghosts[1].position.x-1][ghosts[1].position.y] != -1) 
                     ghosts[1].position.x--;
                    break;
                case 8:
                    if (packmanMap[ghosts[0].position.x+1][ghosts[0].position.y] != -1)
					 ghosts[0].position.x++;
					if (packmanMap[ghosts[1].position.x][ghosts[1].position.y-1] != -1)
					 ghosts[1].position.y--;
                    break;
                case 9:
                    if (packmanMap[ghosts[0].position.x+1][ghosts[0].position.y] != -1) 
					 ghosts[0].position.x++;
					if (packmanMap[ghosts[1].position.x][ghosts[1].position.y+1] != -1) 
					 ghosts[1].position.y++;
                    break;
                case 10:
                    if (packmanMap[ghosts[0].position.x][ghosts[0].position.y+1] != -1) 
					 ghosts[0].position.y++;
					if (packmanMap[ghosts[1].position.x+1][ghosts[1].position.y] != -1) 
					 ghosts[1].position.x++;
                    break;
                case 11:
                    if (packmanMap[ghosts[0].position.x][ghosts[0].position.y+1] != -1) 
                     ghosts[0].position.y++;
                    if (packmanMap[ghosts[1].position.x-1][ghosts[1].position.y] != -1) 
                     ghosts[1].position.x--;
                    break;
                case 12:
                    if (packmanMap[ghosts[0].position.x][ghosts[0].position.y+1] != -1)
					 ghosts[0].position.y++;
					if (packmanMap[ghosts[1].position.x][ghosts[1].position.y-1] != -1)
					 ghosts[1].position.y--;
                    break;
                case 13:
                    if (packmanMap[ghosts[0].position.x-1][ghosts[0].position.y] != -1) 
					 ghosts[0].position.x--;
					if (packmanMap[ghosts[1].position.x+1][ghosts[1].position.y] != -1) 
					 ghosts[1].position.x++;
                    break;
                case 14:
                    if (packmanMap[ghosts[0].position.x-1][ghosts[0].position.y] != -1) 
					 ghosts[0].position.x--;
					if (packmanMap[ghosts[1].position.x][ghosts[1].position.y+1] != -1) 
					 ghosts[1].position.y++;
                    break;
                case 15:
                    if (packmanMap[ghosts[0].position.x-1][ghosts[0].position.y] != -1) 
                     ghosts[0].position.x--;
                    if (packmanMap[ghosts[1].position.x][ghosts[1].position.y-1] != -1) 
                     ghosts[1].position.y--;
                    break;                    
            }
    temp1 = packmanMap[ghosts[0].position.x][ghosts[0].position.y];
    temp2 = packmanMap[ghosts[1].position.x][ghosts[1].position.y];
    DQNbackward();


}

