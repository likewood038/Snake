#ifndef __SNAKE_H__
#define __SNAKE_H__


#define mapSize 15		//地图大小 

typedef struct Block {
	int x;
	int y;
	char type;	//0是墙，1是场地，2是头，3是身体，4是食物 
}Block;


typedef struct Snake {
	int lenOfSnake;
	char face;		//0上，1下，2左，3右 
	Block body[(mapSize-2)*(mapSize-2)];
}Snake;

//函数声明 
int creatMap (Block map[][mapSize]);
int initMap (Block map[][mapSize],const Snake * snake);
int printMsgOfBlock(Block b);
int initSnake(int x,int y,Snake *snake); 
int creatFood(Block map[][mapSize]);
int getInput(Snake * snake);
int movingSnake(Snake * snake,int oldTail[2]);
int movingBody(Snake *snake);
int movingMap(Block map[][mapSize],const Snake * snake,const int oldTail[2]);
int creatSnake (Block map[][mapSize],const Snake *snake);
void endGame();
int eatFood(Block map[][mapSize],Snake * snake,const int oldTail[2]);
void hideCursor(); 
void moveCursor(); 
#endif
