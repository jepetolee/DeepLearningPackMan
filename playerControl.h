
#include "enemyControl.h"

void playerCheck(void){
    packmanMap[pacMan.position.x][pacMan.position.y]=1;
    packmanMap[ghosts[0].position.x][ghosts[0].position.y]=temp1;
    packmanMap[ghosts[1].position.x][ghosts[1].position.y]=temp2;
    
    if (packmanMap[pacMan.position.x][pacMan.position.y] == 4)
	  gameOver = 1;
	  
    if(pacMan.position.y==29)
        pacMan.position.y=1;
    else if(pacMan.position.y==0)
        pacMan.position.y=28;  
    if(pacMan.position.y==29)
        pacMan.position.y=1;
    else if(pacMan.position.y==0)
        pacMan.position.y=28;
        
    if(ghosts[0].position.y==29)
        ghosts[0].position.y=1;
    else if(ghosts[1].position.y==0)
        ghosts[1].position.y=28;
}
