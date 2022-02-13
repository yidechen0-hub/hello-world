#include<graphics.h>
#include<conio.h>
#pragma comment(lib,"Winmm.lib")//调用Windows MultiMedia API来使用mciSendString函数

/*	背景尺寸为350*600
	小鸟尺寸为34*24
	柱子宽处宽度70，长600，窄处宽度50，宽处厚度30

*/

int width,high;//背景的宽高
int bird_x,bird_y;//小鸟的左上角坐标
//int abovepost_x,abovepost_y;//上柱子的左上角坐标
//int belowpost_x,belowpost_y;//下柱子的左上角坐标
int above[2],low[2];//柱子间隙的上下坐标
int gap;//柱子间隙大小
int abovepost_x[2],abovepost_y[2],belowpost_x[2],belowpost_y[2];
IMAGE bkground;//存放背景的变量
IMAGE bird1,bird2;//存放小鸟
//IMAGE post1,post2,post3,post4;//存放柱子的变量
IMAGE post[8];//存放柱子的变量

void startup(){
	width=350;
	high=600;
	gap=120;
	bird_x=50;//小鸟坐标初始化为（50,288）
	bird_y=288;
	//第一根柱子
	above[0]=high/2-gap/2;
	low[0]=high/2+gap/2;
	abovepost_x[0]=width/2;
	abovepost_y[0]=above[0]-600;
	belowpost_x[0]=abovepost_x[0];
	belowpost_y[0]=low[0];
	//第二根柱子
	above[1]=rand()%300+100;
	low[1]=above[1]+gap;
	abovepost_x[1]=width;
	abovepost_y[1]=above[1]-600;
	belowpost_x[1]=abovepost_x[1];
	belowpost_y[1]=low[1];
	initgraph(width,high);
	//初始化背景图片
	
	loadimage(&bkground,"E:\\flappybird\\bkground.jpg");
	putimage(0,0,&bkground);
	//初始化背景音乐并循环播放
	mciSendString("open E:\\flappybird\\bkmusic.mp3 alias bkmusic",NULL,0,NULL);
	mciSendString("play bkmusic repeat",NULL,0,NULL);
	//初始化小鸟
	
	loadimage(&bird1,"E:\\flappybird\\bird1-1.gif");
	loadimage(&bird2,"E:\\flappybird\\bird1-2.gif");
	putimage(bird_x,bird_y,&bird1,NOTSRCERASE);
	putimage(bird_x,bird_y,&bird2,SRCINVERT);
	//初始化第一根柱子

	loadimage(&post[0],"E:\\flappybird\\post_up1.gif");
	loadimage(&post[1],"E:\\flappybird\\post_up2.gif");
	putimage(abovepost_x[0],abovepost_y[0],&post[0],NOTSRCERASE);
	putimage(abovepost_x[0],abovepost_y[0],&post[1],SRCINVERT);
	loadimage(&post[2],"E:\\flappybird\\post_down1.gif");
	loadimage(&post[3],"E:\\flappybird\\post_down2.gif");
	putimage(belowpost_x[0],belowpost_y[0],&post[2],NOTSRCERASE);
	putimage(belowpost_x[0],belowpost_y[0],&post[3],SRCINVERT);

	//初始化第二根柱子

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
	//背景
	putimage(0,0,&bkground);
	//一号柱子
	putimage(abovepost_x[0],abovepost_y[0],&post[0],NOTSRCERASE);
	putimage(abovepost_x[0],abovepost_y[0],&post[1],SRCINVERT);
	putimage(belowpost_x[0],belowpost_y[0],&post[2],NOTSRCERASE);
	putimage(belowpost_x[0],belowpost_y[0],&post[3],SRCINVERT);
	//二号柱子
	putimage(abovepost_x[1],abovepost_y[1],&post[4],NOTSRCERASE);
	putimage(abovepost_x[1],abovepost_y[1],&post[5],SRCINVERT);
	putimage(belowpost_x[1],belowpost_y[1],&post[6],NOTSRCERASE);
	putimage(belowpost_x[1],belowpost_y[1],&post[7],SRCINVERT);
	//小鸟
	putimage(bird_x,bird_y,&bird1,NOTSRCERASE);
	putimage(bird_x,bird_y,&bird2,SRCINVERT);
	FlushBatchDraw();
}
void updatewithinput(){
	//键盘输入空格小鸟往上50
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
	//鼠标左键点击小鸟网上50
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
//若撞柱子则游戏结束
void crash(){
	int k;
	for(k=0;k<2;k++){
	if(bird_x>=belowpost_x[k]-34&&bird_x<=belowpost_x[k]+70){
		if(bird_y>belowpost_y[k]-24||bird_y<belowpost_y[k]-gap){
			cleardevice();
		
			//背景
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
	//小鸟自动下落
	Sleep(100);
	if(bird_y<576)
	bird_y+=10;
	//柱子的移动
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