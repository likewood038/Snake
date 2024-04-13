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
	int oldTail[2]={0};//���ڴ���ƶ�ǰ��β������ 
	
	while (1){
		
		moveCursor();
		
		if (snake.lenOfSnake==maxLenOfSnake)endGame();
		getInput(&snake);
		
		//�߼��ƶ��� 
		movingSnake(&snake,oldTail);
		
		//��ײ��� 
		switch(map[snake.body[0].x][snake.body[0].y].type){
			case 0:endGame();break;//ײǽ
			case 1:movingMap(map,&snake,oldTail);break;//�հ�
			case 2:endGame();break;//ײͷ������ 
			case 3:endGame();break;//����
			case 4:eatFood(map,&snake,oldTail);break;//ʳ��
		}
		
		creatMap(map);
		if (end) break;
		Sleep(200);
	}
	printf("��Ϸ����");

	return 0;
}




//����Ļ�ϻ������� 
int creatMap (Block map[][mapSize]) {
	int i,j;
	for (i=0;i<mapSize;i++){
		for(j=0;j<mapSize;j++){
			switch(map[i][j].type){
				case 0:printf("��");break;
				case 1:printf("  ");break;
				case 2:printf("��");break;
				case 3:printf("��");break;
				case 4:printf("��");break;
				default:printf("E");
			}
		}
		printf("\n");	//��Ե���� 
	}
	return 0;
}

//��ʼ������ 
int initMap (Block map[][mapSize],const Snake * snake){
	int i,j;
	for (i=0;i<mapSize;i++){
		for (j=0;j<mapSize;j++){
			map[i][j].x=i;			//��ʼ������ 
			map[i][j].y=j;
			if ((i == 0) || (i == mapSize - 1) || (j == 0) || (j == mapSize - 1) ){ //���ǽԪ�� 
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

//��ʼ���߶��� 
int initSnake(int x,int y,Snake *snake){
	//��ʼ���߶��� 
	snake->lenOfSnake =2;
	snake->face=3;	//�� 
	//��ʼ��ͷ�������block���� 
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

//����ʳ�� 
int creatFood(Block map[][mapSize]){

	srand(time(NULL));
	while(1){
		int x=rand()%(mapSize-1)+1;
		int y=rand()%(mapSize-1)+1;	//���ɷ�Χ����������� 
	
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
	
	map[oldTail[0]][oldTail[1]].type=1;	//β�����������Ϊ�հ� 
	map[snake->body[1].x][snake->body[1].y].type=3;//ԭ��ͷ��λ�ñ�Ϊ���� 
	map[snake->body[0].x][snake->body[0].y].type=2;	//ͷ�����������Ϊͷ 
	
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
	//ͷ
	map[snake->body[i].x][snake->body[i].y].type=2;
	
	//���� 
	for(i=1;i<snake->lenOfSnake;i++){
		map[snake->body[i].x][snake->body[i].y].type=3;
	}
}

void endGame(){
	end=1;
}

int eatFood(Block map[][mapSize],Snake * snake,const int oldTail[2]){

	map[snake->body[1].x][snake->body[1].y].type=3;//ԭ��ͷ��λ�ñ�Ϊ���� 
	map[snake->body[0].x][snake->body[0].y].type=2;	//ͷ�����������Ϊͷ 
	
	snake->lenOfSnake += 1;
	snake->body[snake->lenOfSnake-1].x=oldTail[0];
	snake->body[snake->lenOfSnake-1].y=oldTail[1];
	//�����¶��� 
	creatFood(map); 
	return 0;
}

//���ع�� 
void hideCursor(){
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize=sizeof(cci);
	cci.bVisible=FALSE;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle,&cci);
}

//�ƶ���굽���� 
void moveCursor(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0}; // ���ù��λ��Ϊ (0, 0)��������
    SetConsoleCursorPosition(hConsole, coord);
}
