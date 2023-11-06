
typedef struct {
    int x;
    int y;
} Coordinate;

typedef struct {
    Coordinate position;
    int score;
    int symbol;
} Player;

typedef struct {
    Coordinate position;
    int symbol;
} Ghost;

Ghost ghosts[2];
Player pacMan;
int gameOver =0;

void settingGame(){
	pacMan.position.x =15;
	pacMan.position.y =15;
	pacMan.symbol =3;
	
	ghosts[0].position.x =2;
	ghosts[0].position.y =2;
	ghosts[0].symbol =4;
	
    ghosts[1].position.x =28;
	ghosts[1].position.y =28;
	ghosts[1].symbol =4;
	
}
