#include<graphics.h>
#include<conio.h>
#pragma comment(lib,"Winmm.lib")//����Windows MultiMedia API��ʹ��mciSendString����

/*	�����ߴ�Ϊ350*600
	С��ߴ�Ϊ34*24
	���ӿ����70����600��խ�����50�������30

*/

int width,high;//�����Ŀ��
int bird_x,bird_y;//С������Ͻ�����
//int abovepost_x,abovepost_y;//�����ӵ����Ͻ�����
//int belowpost_x,belowpost_y;//�����ӵ����Ͻ�����
int above[2],low[2];//���Ӽ�϶����������
int gap;//���Ӽ�϶��С
int abovepost_x[2],abovepost_y[2],belowpost_x[2],belowpost_y[2];
IMAGE bkground;//��ű����ı���
IMAGE bird1,bird2;//���С��
//IMAGE post1,post2,post3,post4;//������ӵı���
IMAGE post[8];//������ӵı���

void startup(){
	width=350;
	high=600;
	gap=120;
	bird_x=50;//С�������ʼ��Ϊ��50,288��
	bird_y=288;
	//��һ������
	above[0]=high/2-gap/2;
	low[0]=high/2+gap/2;
	abovepost_x[0]=width/2;
	abovepost_y[0]=above[0]-600;
	belowpost_x[0]=abovepost_x[0];
	belowpost_y[0]=low[0];
	//�ڶ�������
	above[1]=rand()%300+100;
	low[1]=above[1]+gap;
	abovepost_x[1]=width;
	abovepost_y[1]=above[1]-600;
	belowpost_x[1]=abovepost_x[1];
	belowpost_y[1]=low[1];
	initgraph(width,high);
	//��ʼ������ͼƬ
	
	loadimage(&bkground,"E:\\flappybird\\bkground.jpg");
	putimage(0,0,&bkground);
	//��ʼ���������ֲ�ѭ������
	mciSendString("open E:\\flappybird\\bkmusic.mp3 alias bkmusic",NULL,0,NULL);
	mciSendString("play bkmusic repeat",NULL,0,NULL);
	//��ʼ��С��
	
	loadimage(&bird1,"E:\\flappybird\\bird1-1.gif");
	loadimage(&bird2,"E:\\flappybird\\bird1-2.gif");
	putimage(bird_x,bird_y,&bird1,NOTSRCERASE);
	putimage(bird_x,bird_y,&bird2,SRCINVERT);
	//��ʼ����һ������

	loadimage(&post[0],"E:\\flappybird\\post_up1.gif");
	loadimage(&post[1],"E:\\flappybird\\post_up2.gif");
	putimage(abovepost_x[0],abovepost_y[0],&post[0],NOTSRCERASE);
	putimage(abovepost_x[0],abovepost_y[0],&post[1],SRCINVERT);
	loadimage(&post[2],"E:\\flappybird\\post_down1.gif");
	loadimage(&post[3],"E:\\flappybird\\post_down2.gif");
	putimage(belowpost_x[0],belowpost_y[0],&post[2],NOTSRCERASE);
	putimage(belowpost_x[0],belowpost_y[0],&post[3],SRCINVERT);

	//��ʼ���ڶ�������

	loadimage(&post[4],"E:\\flappybird\\post_up1.gif");
	loadimage(&post[5],"E:\\flappybird\\post_up2.gif");
	putimage(abovepost_x[1],abovepost_y[1],&post[4],NOTSRCERASE);
	putimage(abovepost_x[1],abovepost_y[1],&post[5],SRCINVERT);
	loadimage(&post[6],"E:\\flappybird\\post_down1.gif");
	loadimage(&post[7],"E:\\flappybird\\post_down2.gif");
	putimage(belowpost_x[1],belowpost_y[1],&post[6],NOTSRCERASE);
	putimage(belowpost_x[1],belowpost_y[1],&post[7],SRCINVERT);

}
void show(){
	
	cleardevice();
	BeginBatchDraw();
	//����
	putimage(0,0,&bkground);
	//һ������
	putimage(abovepost_x[0],abovepost_y[0],&post[0],NOTSRCERASE);
	putimage(abovepost_x[0],abovepost_y[0],&post[1],SRCINVERT);
	putimage(belowpost_x[0],belowpost_y[0],&post[2],NOTSRCERASE);
	putimage(belowpost_x[0],belowpost_y[0],&post[3],SRCINVERT);
	//��������
	putimage(abovepost_x[1],abovepost_y[1],&post[4],NOTSRCERASE);
	putimage(abovepost_x[1],abovepost_y[1],&post[5],SRCINVERT);
	putimage(belowpost_x[1],belowpost_y[1],&post[6],NOTSRCERASE);
	putimage(belowpost_x[1],belowpost_y[1],&post[7],SRCINVERT);
	//С��
	putimage(bird_x,bird_y,&bird1,NOTSRCERASE);
	putimage(bird_x,bird_y,&bird2,SRCINVERT);
	FlushBatchDraw();
}
void updatewithinput(){
	//��������ո�С������50
	char input;
	if(kbhit()){
		input=getch();
		if(input==' '&&bird_y>=50){
			bird_y-=50;
			mciSendString("close jpmusic",NULL,0,NULL);
			mciSendString("open E:\\flappybird\\jpmusic.mp3 alias jpmusic",NULL,0,NULL);
			mciSendString("play jpmusic",NULL,0,NULL);
		
		}
		else if(input==' '&&bird_y<50){
			bird_y=0;
			mciSendString("close jpmusic",NULL,0,NULL);
			mciSendString("open E:\\flappybird\\jpmusic.mp3 alias jpmusic",NULL,0,NULL);
			mciSendString("play jpmusic",NULL,0,NULL);
		
		
		}
	}
	//���������С������50
	MOUSEMSG m;
	if(MouseHit()){
		m = GetMouseMsg();
		if(m.uMsg==WM_LBUTTONDOWN&&bird_y>=50){
			bird_y-=50;
			mciSendString("close jpmusic",NULL,0,NULL);
			mciSendString("open E:\\flappybird\\jpmusic.mp3 alias jpmusic",NULL,0,NULL);
			mciSendString("play jpmusic",NULL,0,NULL);
	
	
	}
	else if(m.uMsg==WM_LBUTTONDOWN&&bird_y<50){
			bird_y=0;
			mciSendString("close jpmusic",NULL,0,NULL);
			mciSendString("open E:\\flappybird\\jpmusic.mp3 alias jpmusic",NULL,0,NULL);
			mciSendString("play jpmusic",NULL,0,NULL);
		
		
		}
	}
}
//��ײ��������Ϸ����
void crash(){
	int k;
	for(k=0;k<2;k++){
	if(bird_x>=belowpost_x[k]-34&&bird_x<=belowpost_x[k]+70){
		if(bird_y>belowpost_y[k]-24||bird_y<belowpost_y[k]-gap){
			cleardevice();
		
			//����
			putimage(0,0,&bkground);
			IMAGE over1,over2;
			loadimage(&over1,"E:\\flappybird\\gameover1.gif");
			loadimage(&over2,"E:\\flappybird\\gameover2.gif");
			putimage(100,200,&over1,NOTSRCERASE);
			putimage(100,200,&over2,SRCINVERT);
			EndBatchDraw();
			getch();
			exit(0);
		
		}
	
	}
	}

}
void updatewithoutinput(){
	//С���Զ�����
	Sleep(100);
	if(bird_y<576)
	bird_y+=10;
	//���ӵ��ƶ�
	int k;
	for(k=0;k<2;k++){
	if(abovepost_x[k]+70>0){
		abovepost_x[k]-=5;
		belowpost_x[k]-=5;
	
	}
	else{
		above[k]=rand()%300+100;
		low[k]=above[k]+gap;
		abovepost_x[k]=width;
		abovepost_y[k]=above[k]-600;
		belowpost_x[k]=abovepost_x[k];
		belowpost_y[k]=low[k];
	
	}
	}
	 crash();
}

int main(){
	startup();
	while(1){
		show();
		updatewithinput();
		updatewithoutinput();
	
	}
	getch();
	closegraph();

	return 0;
}