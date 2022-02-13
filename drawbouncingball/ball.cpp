#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<graphics.h>



//定义全局变量
int width;
int high;
int above;	//挡板移动的上下界
int below;
int dis;		//挡板每次移动的距离
int ball_x,ball_y;//小球的中心坐标
int radius;//小球的半径
int ball_vx,ball_vy;//小球的速度
int block_x,block_y;//挡板的中心坐标
int blength,bhigh;//挡板的长和高
int exist[3][10];//3*10个砖块是否存在
int sqhigh,sqwidth;//square砖块的高和宽
int score;
int level;//标记到了第几关
int v;//初始游戏速度，且值越小速度越快
void gameover(){
	//initgraph(width,high);
	//setbkcolor(BLUE);
//	cleardevice();

	printf("score:%d\n",score);
	printf("闯到了第%d关\n",level);
	exit(0);
}
	


void startup(){				//游戏的初始化
	level=1;
	score=0;//分数初始为0
	v=10;
	width=600;//画布的尺寸
	high=500;
	above=high*4/5;	//挡板移动的上下界
	below=high-20;
	dis=10;//挡板每次移动的距离
	initgraph(width,high);
	// 设置背景色为蓝色
	setbkcolor(BLUE);
	// 用背景色清空屏幕
	cleardevice();

//	IMAGE image_bk;
//	loadimage(&image_bk,"E:\\bk.jpeg");
//	putimage(0,0,&image_bk);
	//小球的初始化
	ball_x=width/2;
	ball_y=high/2;
	ball_vx=1;
	ball_vy=1;
	radius=10;
	setcolor(YELLOW);
	setfillcolor(YELLOW);
	fillcircle(ball_x,ball_y,radius);
	//挡板的初始化
	
	block_x=width/2;
	block_y=below;
	blength=80;
	bhigh=10;
	//砖块的初始化
	sqhigh=width/10;
	sqwidth=width/10;
	for(int i=0;i<3;i++){
		for(int j=0;j<10;j++){
			exist[i][j]=1;
		}
	
	}
	setfillcolor(BLACK);
	solidrectangle(block_x-blength/2,block_y+bhigh/2,block_x+blength/2,block_y-bhigh/2);
	
	
}
//下一关的砖块随机分布
void next(){
	sqhigh=width/10;
	sqwidth=width/10;
	for(int i=0;i<3;i++){
		for(int j=0;j<10;j++){
			exist[i][j]=rand()%2;
		}
	
	}


}
void show(){				//游戏界面的输出
	int i,j;
	BeginBatchDraw();//防止闪烁
	//上边界的红线
	setcolor(RED);
	line(0,high*4/5,width,high*4/5);
	//青色砖块
	
	for(i=0;i<3;i++){
		for(j=0;j<10;j++){
			if(exist[i][j]){
				setcolor(WHITE);
				setfillcolor(CYAN);
				fillrectangle(j*sqwidth,i*sqhigh,(j+1)*sqwidth,(i+1)*sqhigh);
			}
		
		}
	
	}
	//黄色小球
	
	setcolor(YELLOW);
	setfillcolor(YELLOW);
	fillcircle(ball_x,ball_y,radius);
	FlushBatchDraw();
	cleardevice();
				

	//黑色挡板
	setfillcolor(BLACK);
	solidrectangle(block_x-blength/2,block_y+bhigh/2,block_x+blength/2,block_y-bhigh/2);
			
		
	

}
void updatewithinput(){		//与输入有关的更新
/*	char input;
	if(kbhit()){
		input=getch();
		if(input=='a'&&block_x-blength/2>dis)block_x=block_x-dis;
		else if(input=='a')block_x=blength/2;
		if(input=='d'&&block_x+blength/2<width-dis)block_x=block_x+dis;
		else if(input=='d')block_x=width-blength/2;
		if(input=='w'&&block_y-bhigh/2>above+dis)block_y=block_y-dis;
		else if(input=='w')block_y=above+bhigh/2;
		if(input=='s'&&block_y+bhigh/2<below-dis)block_y=block_y+dis;
		else if(input=='s')block_y=below-bhigh/2;

	}*/

	MOUSEMSG m;
	if(MouseHit()){
		m=GetMouseMsg();
		if(m.uMsg==WM_MOUSEMOVE){
			if(m.x>=blength/2&&m.x<width-blength/2&&m.y>above+bhigh/2&&m.y<below-bhigh/2){
			block_x=m.x;
			block_y=m.y;
		
			}
		
		}
	
	
	
	}





}
void updatewithoutinput(){
	//Sleep(2);
	static int speed=0;
	if(level>v-5)level=v-5;
	if(speed<v-level)speed++;
	else{
	//碰到挡板上方时反弹，未碰到挡板且未落到下界below时继续下落
	if(ball_y>=block_y-bhigh/2-radius&&ball_y<=block_y+bhigh/2-radius&&ball_y<below-radius){
		if(ball_x>=block_x-blength/2&&ball_x<=block_x+blength/2){
			if(ball_vy>0)
			ball_vy=-ball_vy;
		
		}
		
	
	}
	//碰到下边界则转到gameover（）
	else if(ball_y>below-radius){
	
			gameover();
			
		
	
	}
	
	if(ball_x<radius||ball_x>width-radius)ball_vx=-ball_vx;//左右边界反弹
	if(ball_y<radius)ball_vy=-ball_vy;//上边界反弹
	ball_x=ball_x+ball_vx;
	ball_y=ball_y+ball_vy;
	int i,j, sqleft,sqright, sqtop, sqbottom;//砖块的四个边界
	for(i = 0; i < 3; i++){
		for(j = 0; j < 10; j++){
		if(exist[i][j]){//如果砖块存在
			sqleft = j * sqwidth;
			sqright = (j+1)*sqwidth;
			sqbottom = (i+1)*sqhigh;
			sqtop=i*sqhigh;
			//球撞到砖块下边界
			if((ball_y== sqbottom + radius) && (ball_x >= sqleft) && (ball_x<= sqright)&&ball_vy<0){
				exist[i][j]= 0;
				score++;
			//	ball_y += 1;
				ball_vy = -ball_vy;
				}
			//球撞到砖块上边界
			if((ball_y== sqtop - radius) && (ball_x >= sqleft) && (ball_x<= sqright)&&ball_vy>0){
				exist[i][j]= 0;
				score++;
			//	ball_y -= 1;
				ball_vy = -ball_vy;
				}
			//球撞到砖块左边界
			if((ball_x== sqleft - radius) && (ball_y >= sqtop) && (ball_y<= sqbottom)&&ball_vx>0){
				exist[i][j]= 0;
				score++;
				//ball_x -= 1;
				ball_vx = -ball_vx;
				}
			//球撞到砖块右边界
			if((ball_x== sqright + radius) && (ball_y >= sqtop) && (ball_y<= sqbottom)&&ball_vx<0){
				exist[i][j]= 0;
				score++;
				//ball_x += 1;
				ball_vx = -ball_vx;
				}
			} 
		}
	
	}

	//判断场上还有没有砖块存在
	int flag=0;
	for(i = 0; i < 3; i++){
		for(j = 0; j < 10; j++){
			if(exist[i][j])flag=1;
		}
	
	}
	//若砖块已经消除进入下一关
	if(flag==0){
		level++;
		next();
		
	}
	speed=0;
	}//速度else
	
	
}
int main(){
	startup();
	while(1){
		show();
		updatewithoutinput();
		updatewithinput();

	}
	EndBatchDraw();
	return 0;
}