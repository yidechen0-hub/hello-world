#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<graphics.h>



//����ȫ�ֱ���
int width;
int high;
int above;	//�����ƶ������½�
int below;
int dis;		//����ÿ���ƶ��ľ���
int ball_x,ball_y;//С�����������
int radius;//С��İ뾶
int ball_vx,ball_vy;//С����ٶ�
int block_x,block_y;//�������������
int blength,bhigh;//����ĳ��͸�
int exist[3][10];//3*10��ש���Ƿ����
int sqhigh,sqwidth;//squareש��ĸߺͿ�
int score;
int level;//��ǵ��˵ڼ���
int v;//��ʼ��Ϸ�ٶȣ���ֵԽС�ٶ�Խ��
void gameover(){
	//initgraph(width,high);
	//setbkcolor(BLUE);
//	cleardevice();

	printf("score:%d\n",score);
	printf("�����˵�%d��\n",level);
	exit(0);
}
	


void startup(){				//��Ϸ�ĳ�ʼ��
	level=1;
	score=0;//������ʼΪ0
	v=10;
	width=600;//�����ĳߴ�
	high=500;
	above=high*4/5;	//�����ƶ������½�
	below=high-20;
	dis=10;//����ÿ���ƶ��ľ���
	initgraph(width,high);
	// ���ñ���ɫΪ��ɫ
	setbkcolor(BLUE);
	// �ñ���ɫ�����Ļ
	cleardevice();

//	IMAGE image_bk;
//	loadimage(&image_bk,"E:\\bk.jpeg");
//	putimage(0,0,&image_bk);
	//С��ĳ�ʼ��
	ball_x=width/2;
	ball_y=high/2;
	ball_vx=1;
	ball_vy=1;
	radius=10;
	setcolor(YELLOW);
	setfillcolor(YELLOW);
	fillcircle(ball_x,ball_y,radius);
	//����ĳ�ʼ��
	
	block_x=width/2;
	block_y=below;
	blength=80;
	bhigh=10;
	//ש��ĳ�ʼ��
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
//��һ�ص�ש������ֲ�
void next(){
	sqhigh=width/10;
	sqwidth=width/10;
	for(int i=0;i<3;i++){
		for(int j=0;j<10;j++){
			exist[i][j]=rand()%2;
		}
	
	}


}
void show(){				//��Ϸ��������
	int i,j;
	BeginBatchDraw();//��ֹ��˸
	//�ϱ߽�ĺ���
	setcolor(RED);
	line(0,high*4/5,width,high*4/5);
	//��ɫש��
	
	for(i=0;i<3;i++){
		for(j=0;j<10;j++){
			if(exist[i][j]){
				setcolor(WHITE);
				setfillcolor(CYAN);
				fillrectangle(j*sqwidth,i*sqhigh,(j+1)*sqwidth,(i+1)*sqhigh);
			}
		
		}
	
	}
	//��ɫС��
	
	setcolor(YELLOW);
	setfillcolor(YELLOW);
	fillcircle(ball_x,ball_y,radius);
	FlushBatchDraw();
	cleardevice();
				

	//��ɫ����
	setfillcolor(BLACK);
	solidrectangle(block_x-blength/2,block_y+bhigh/2,block_x+blength/2,block_y-bhigh/2);
			
		
	

}
void updatewithinput(){		//�������йصĸ���
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
	//���������Ϸ�ʱ������δ����������δ�䵽�½�belowʱ��������
	if(ball_y>=block_y-bhigh/2-radius&&ball_y<=block_y+bhigh/2-radius&&ball_y<below-radius){
		if(ball_x>=block_x-blength/2&&ball_x<=block_x+blength/2){
			if(ball_vy>0)
			ball_vy=-ball_vy;
		
		}
		
	
	}
	//�����±߽���ת��gameover����
	else if(ball_y>below-radius){
	
			gameover();
			
		
	
	}
	
	if(ball_x<radius||ball_x>width-radius)ball_vx=-ball_vx;//���ұ߽練��
	if(ball_y<radius)ball_vy=-ball_vy;//�ϱ߽練��
	ball_x=ball_x+ball_vx;
	ball_y=ball_y+ball_vy;
	int i,j, sqleft,sqright, sqtop, sqbottom;//ש����ĸ��߽�
	for(i = 0; i < 3; i++){
		for(j = 0; j < 10; j++){
		if(exist[i][j]){//���ש�����
			sqleft = j * sqwidth;
			sqright = (j+1)*sqwidth;
			sqbottom = (i+1)*sqhigh;
			sqtop=i*sqhigh;
			//��ײ��ש���±߽�
			if((ball_y== sqbottom + radius) && (ball_x >= sqleft) && (ball_x<= sqright)&&ball_vy<0){
				exist[i][j]= 0;
				score++;
			//	ball_y += 1;
				ball_vy = -ball_vy;
				}
			//��ײ��ש���ϱ߽�
			if((ball_y== sqtop - radius) && (ball_x >= sqleft) && (ball_x<= sqright)&&ball_vy>0){
				exist[i][j]= 0;
				score++;
			//	ball_y -= 1;
				ball_vy = -ball_vy;
				}
			//��ײ��ש����߽�
			if((ball_x== sqleft - radius) && (ball_y >= sqtop) && (ball_y<= sqbottom)&&ball_vx>0){
				exist[i][j]= 0;
				score++;
				//ball_x -= 1;
				ball_vx = -ball_vx;
				}
			//��ײ��ש���ұ߽�
			if((ball_x== sqright + radius) && (ball_y >= sqtop) && (ball_y<= sqbottom)&&ball_vx<0){
				exist[i][j]= 0;
				score++;
				//ball_x += 1;
				ball_vx = -ball_vx;
				}
			} 
		}
	
	}

	//�жϳ��ϻ���û��ש�����
	int flag=0;
	for(i = 0; i < 3; i++){
		for(j = 0; j < 10; j++){
			if(exist[i][j])flag=1;
		}
	
	}
	//��ש���Ѿ�����������һ��
	if(flag==0){
		level++;
		next();
		
	}
	speed=0;
	}//�ٶ�else
	
	
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