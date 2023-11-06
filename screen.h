void batchGhostNpackMan(){
	packmanMap[pacMan.position.x][pacMan.position.y] = pacMan.symbol;
	packmanMap[ghosts[0].position.x][ghosts[0].position.y] = ghosts[0].symbol;
	packmanMap[ghosts[1].position.x][ghosts[1].position.y] = ghosts[1].symbol;
}

void mapPrint(void){
	COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
	int i = 0;
    int j = 0;
    int caseCount =0;
    // 배열의 내용을 출력
    for (i = 0; i < 30; i++) {
        for (j = 0;j < 30; j++) {
            switch ((int)packmanMap[i][j]) {
                case -1:
                    putchar('#');
                    break;
                case 0:
                	caseCount ++;
                    putchar('.');
                    break;
                case 1:
                    putchar(' ');
                    break;
                case 2:
                    putchar('*');
                    break;
                case 3:
                    putchar('T');
                    break;
                case 4:
                    putchar('E');
                    break;
                default:
                    putchar(' '); 
                    break;
            }
        }
        putchar('\n');
    }
    
    if(caseCount==0){
    	gameOver=2;
    	printf("%d 임 ㅇㅇ",caseCount);
	}
       
}

