#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "snake.h"
#include <Windows.h>

int end =0;
int main(){
	hideCursor();
	const maxLenOfSnake=(mapSize-2)*(mapSize-2);
	Block map[mapSize][mapSize];
	Snake snake;
	initSnake(5,5,&snake);
	initMap(map,&snake);
	creatSnake(map,&snake);
	creatFood(map);
	int oldTail[2]={0};//用于存放移动前的尾部坐标 
	
	while (1){
		
		moveCursor();
		
		if (snake.lenOfSnake==maxLenOfSnake)endGame();
		getInput(&snake);
		
		//逻辑移动蛇 
		movingSnake(&snake,oldTail);
		
		//碰撞检测 
		switch(map[snake.body[0].x][snake.body[0].y].type){
			case 0:endGame();break;//撞墙
			case 1:movingMap(map,&snake,oldTail);break;//空白
			case 2:endGame();break;//撞头？？？ 
			case 3:endGame();break;//身体
			case 4:eatFood(map,&snake,oldTail);break;//食物
		}
		
		creatMap(map);
		if (end) break;
		Sleep(200);
	}
	printf("游戏结束");

	return 0;
}




//在屏幕上画出画面 
int creatMap (Block map[][mapSize]) {
	int i,j;
	for (i=0;i<mapSize;i++){
		for(j=0;j<mapSize;j++){
			switch(map[i][j].type){
				case 0:printf("■");break;
				case 1:printf("  ");break;
				case 2:printf("◆");break;
				case 3:printf("■");break;
				case 4:printf("●");break;
				default:printf("E");
			}
		}
		printf("\n");	//边缘换行 
	}
	return 0;
}

//初始化场地 
int initMap (Block map[][mapSize],const Snake * snake){
	int i,j;
	for (i=0;i<mapSize;i++){
		for (j=0;j<mapSize;j++){
			map[i][j].x=i;			//初始化坐标 
			map[i][j].y=j;
			if ((i == 0) || (i == mapSize - 1) || (j == 0) || (j == mapSize - 1) ){ //标记墙元素 
				map[i][j].type = 0;
			}else{
				map[i][j].type = 1;
			}
		}
	}
	return 0;
}

int printMsgOfBlock(Block b){
	printf("\n");
	printf("x=%d\n",b.x);
	printf("y=%d\n",b.y);
	printf("type=%d\n",b.type);
	return 0;
}

//初始化蛇对象 
int initSnake(int x,int y,Snake *snake){
	//初始化蛇对象 
	snake->lenOfSnake =2;
	snake->face=3;	//右 
	//初始化头和身体的block属性 
	snake->body[0].type=2;
	snake->body[0].x=x;
	snake->body[0].y=y;
	snake->body[1].type=3;
	snake->body[1].x=x;
	snake->body[1].y=y-1;
	//snake->body[2].type=3;
	//snake->body[2].x=x;
	//snake->body[2].y=y-2;

	return 0; 
}

//创建食物 
int creatFood(Block map[][mapSize]){

	srand(time(NULL));
	while(1){
		int x=rand()%(mapSize-1)+1;
		int y=rand()%(mapSize-1)+1;	//生成范围内随机坐标组 
	
		if (map[x][y].type != 1) continue;
		else {
			map[x][y].type=4;
			return 0;
		}
	}
}


int movingBody(Snake *snake){
	int i;
	for(i=snake->lenOfSnake-1;i>0;i--){
		snake->body[i].x=snake->body[i-1].x;
		snake->body[i].y=snake->body[i-1].y;		
	}
	return 0;
}

int  movingSnake(Snake * snake,int oldTail[2]){
	oldTail[0]=snake->body[snake->lenOfSnake-1].x;
	oldTail[1]=snake->body[snake->lenOfSnake-1].y;
	movingBody(snake);
	switch(snake->face){
		case 0:snake->body[0].x -=1;break;
		case 1:snake->body[0].x +=1;break;
		case 2:snake->body[0].y -=1;break;
		case 3:snake->body[0].y +=1;break;		
	}
	
	return 0;
} 



int movingMap(Block map[][mapSize],const Snake * snake,const int oldTail[2]){
	
	map[oldTail[0]][oldTail[1]].type=1;	//尾部所在坐标变为空白 
	map[snake->body[1].x][snake->body[1].y].type=3;//原来头的位置变为身体 
	map[snake->body[0].x][snake->body[0].y].type=2;	//头部所在坐标变为头 
	
	return 0;
}

int getInput(Snake * snake){
	char input;
	if (kbhit()){
		input =getch();
		switch(input){
			case 'w': snake->face=0;break;
			case 's': snake->face=1;break;
			case 'a': snake->face=2;break;
			case 'd': snake->face=3;break;	
		}
	}
}

int creatSnake (Block map[][mapSize],const Snake *snake){
	int i=0;
	//头
	map[snake->body[i].x][snake->body[i].y].type=2;
	
	//身体 
	for(i=1;i<snake->lenOfSnake;i++){
		map[snake->body[i].x][snake->body[i].y].type=3;
	}
}

void endGame(){
	end=1;
}

int eatFood(Block map[][mapSize],Snake * snake,const int oldTail[2]){

	map[snake->body[1].x][snake->body[1].y].type=3;//原来头的位置变为身体 
	map[snake->body[0].x][snake->body[0].y].type=2;	//头部所在坐标变为头 
	
	snake->lenOfSnake += 1;
	snake->body[snake->lenOfSnake-1].x=oldTail[0];
	snake->body[snake->lenOfSnake-1].y=oldTail[1];
	//生成新豆子 
	creatFood(map); 
	return 0;
}

//隐藏光标 
void hideCursor(){
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize=sizeof(cci);
	cci.bVisible=FALSE;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle,&cci);
}

//移动光标到行首 
void moveCursor(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0}; // 设置光标位置为 (0, 0)，即行首
    SetConsoleCursorPosition(hConsole, coord);
}
