#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
//����ȫ�ֱ���
#define high 20
#define width 50
#define enemynum 5
int canvas[high][width]={0};//��Ϸ����Ĵ�С
int position_x,position_y;//�ɻ���λ������
int bullet_x,bullet_y;//�ӵ���λ������
int enemy_x[enemynum],enemy_y[enemynum];//�л���λ��
int score;			//�÷�
int bulletwidth;	//�ӵ����
int left,right;		//�ӵ������ұ߽�
int enemymovespeed=100;//ֵԽС���л��ƶ��ٶ�Խ��
int t=100;				//��¼�л��ĳ�ʼ�ٶ�




void gotoxy(int x,int y){	//����ƶ���xy
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(handle,pos);
}
void HideCursor() // �������ع��
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};  // �ڶ���ֵΪ0��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//�����ͽṹ�嶼��windows.h�ж��塣
}
void startup(){				//��Ϸ�ĳ�ʼ��
	position_x=width/2;
	position_y=high/2;
	canvas[position_y][position_x]=1;//0����ո�1����ɻ�,2�����ӵ�
	bullet_x=-10;
	bullet_y=position_y-1;
	canvas[bullet_y][bullet_x]=2;
	for(int k=0;k<enemynum;k++){
		enemy_x[k]=rand()%width;
		enemy_y[k]=rand()%3;
		canvas[enemy_y[k]][enemy_x[k]]=3;
	}
	bulletwidth=0;
	left=bullet_x-bulletwidth;
	right=bullet_x+bulletwidth;
	score=0;
	HideCursor();		//���ع��
	
}
void show(){				//��Ϸ��������
	int i,j;
	for(i=0;i<high;i++){
		for(j=0;j<width;j++){
			if(canvas[i][j]==1)printf("*");
			else if (canvas[i][j]==2)printf("|");
			else if (canvas[i][j]==3)printf("@");
			else printf(" ");
		
		}
		printf("\n");
	
	}
	printf("score:%d\n",score);

	//system("cls");			//����������˸
	gotoxy(0,0);				//��������˸
	
}
void updatewithinput(){		//�������йصĸ���
	char input;
	
	if(kbhit()){
		input=getch();
		//�ɻ������������ƶ�
		if(input=='a'&&position_x>0){
			canvas[position_y][position_x]=0;
			position_x--;
			canvas[position_y][position_x]=1;
			
		}
	else if(input=='d'&&position_x<width-1){
			canvas[position_y][position_x]=0;
			position_x++;
			canvas[position_y][position_x]=1;
			
		}
	else if(input=='s'&&position_y<high-1){
			canvas[position_y][position_x]=0;
			position_y++;
			canvas[position_y][position_x]=1;
			
		}
	else if(input=='w'&&position_y>0){
			canvas[position_y][position_x]=0;
			position_y--;
			canvas[position_y][position_x]=1;
			
		}
	else if(input==' '){
		int x;
		bullet_y=position_y-1;
		bullet_x=position_x;
		left=bullet_x-bulletwidth;
		if(left<0)left=0;
		right=bullet_x+bulletwidth;
		if(right>width-1)right=width-1;
		for(x=left;x<=right;x++)
		canvas[bullet_y][x]=2;
	
	}
	
	}
	
}
void updatewithoutinput(){
	int i,j,k;

	for(i=0;i<high;i++){		
		for(j=0;j<width;j++){
			if(canvas[i][j]==2){
				//�ж��Ƿ���ел�
				for(k=0;k<enemynum;k++){
					if(enemy_x[k]==j&&enemy_y[k]==i){
					enemy_y[k]=0;
					enemy_x[k]=rand()%width;
					canvas[enemy_y[k]][enemy_x[k]]=3;
					score++;
					if(score!=0&&score%5==0&&bulletwidth<5)bulletwidth++;
					if(score!=0&&score%5==0&&enemymovespeed>20)enemymovespeed=t-score*2;
					}
				}
			//ʹ���ӵ�������������
				canvas[i][j]=0;
				if(i>0)
				canvas[i-1][j]=2;
			
			}
		
			}
		}
	static int speedenm=0;//���Ƶл��ٶ�
	if(speedenm<enemymovespeed)speedenm++;
	else{
		//�л������߽�
	for(k=0;k<enemynum;k++){
		if(enemy_y[k]>=high){
		canvas[enemy_y[k]][enemy_x[k]]=0;
		enemy_y[k]=0;
		enemy_x[k]=rand()%width;
		canvas[enemy_y[k]][enemy_x[k]]=3;
		score--;
	
		}
	}
	//�л��Զ�����
	for(k=0;k<enemynum;k++){
		canvas[enemy_y[k]][enemy_x[k]]=0;
		enemy_y[k]++;
		canvas[enemy_y[k]][enemy_x[k]]=3;
	}
	speedenm=0;

	}		

}
int main(){
	startup();
	while(1){
		show();
		updatewithoutinput();
		updatewithinput();

	}
	return 0;
}