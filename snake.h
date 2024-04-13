#ifndef __SNAKE_H__
#define __SNAKE_H__


#define mapSize 15		//��ͼ��С 

typedef struct Block {
	int x;
	int y;
	char type;	//0��ǽ��1�ǳ��أ�2��ͷ��3�����壬4��ʳ�� 
}Block;


typedef struct Snake {
	int lenOfSnake;
	char face;		//0�ϣ�1�£�2��3�� 
	Block body[(mapSize-2)*(mapSize-2)];
}Snake;

//�������� 
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
