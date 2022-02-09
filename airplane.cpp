#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
//定义全局变量
#define high 20
#define width 50
#define enemynum 5
int canvas[high][width]={0};//游戏界面的大小
int position_x,position_y;//飞机的位置坐标
int bullet_x,bullet_y;//子弹的位置坐标
int enemy_x[enemynum],enemy_y[enemynum];//敌机的位置
int score;			//得分
int bulletwidth;	//子弹宽度
int left,right;		//子弹的左右边界
int enemymovespeed=100;//值越小，敌机移动速度越快
int t=100;				//记录敌机的初始速度




void gotoxy(int x,int y){	//光标移动到xy
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(handle,pos);
}
void HideCursor() // 用于隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};  // 第二个值为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//函数和结构体都在windows.h中定义。
}
void startup(){				//游戏的初始化
	position_x=width/2;
	position_y=high/2;
	canvas[position_y][position_x]=1;//0代表空格，1代表飞机,2代表子弹
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
	HideCursor();		//隐藏光标
	
}
void show(){				//游戏界面的输出
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

	//system("cls");			//清屏会有闪烁
	gotoxy(0,0);				//清屏无闪烁
	
}
void updatewithinput(){		//与输入有关的更新
	char input;
	
	if(kbhit()){
		input=getch();
		//飞机的上下左右移动
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
				//判断是否击中敌机
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
			//使得子弹可以连续发射
				canvas[i][j]=0;
				if(i>0)
				canvas[i-1][j]=2;
			
			}
		
			}
		}
	static int speedenm=0;//控制敌机速度
	if(speedenm<enemymovespeed)speedenm++;
	else{
		//敌机超过边界
	for(k=0;k<enemynum;k++){
		if(enemy_y[k]>=high){
		canvas[enemy_y[k]][enemy_x[k]]=0;
		enemy_y[k]=0;
		enemy_x[k]=rand()%width;
		canvas[enemy_y[k]][enemy_x[k]]=3;
		score--;
	
		}
	}
	//敌机自动下落
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