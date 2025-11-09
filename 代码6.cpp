#include <stdio.h> 
#include <windows.h>
#include <mmsystem.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma comment(lib,"winmm,lib")
#define PI 3.14159265358979323846
#define WIDTH 80
#define HEIGHT 24

int birthdayNotes[]={
	262, 262, 294, 262, 349, 330,
	262, 262, 294, 262, 392, 349, 
	262, 262, 523, 440, 349, 330, 294,
	466, 466, 440, 349, 392, 349 
	};

int noteDurations[]={
	550, 550, 1000, 1000, 1000, 2000,
	500, 500, 1000, 1000, 1000, 2000,
	500, 500, 1000, 1000, 1000, 1000, 2000,
	500, 500, 1000, 1000, 1000, 2000
	};

char buffer[HEIGHT][WIDTH];

void clearBuffer(){
	for (int y=0; y<HEIGHT;y++){
		for (int x=0; x<WIDTH; x++){
			buffer[y][x] =' ';
		}
	}
}
void setPixel(int x, int y, char ch){
	if (x>=0&&x<WIDTH&&y>=0&&y<HEIGHT){
		buffer[y][x]=ch; 
	}
}

void drawCircle(int cx, int cy, int radius,char ch){
	for (int angle=0;angle<360;angle++){
		double rad=angle*PI / 180.0;
		int x=cx+radius*cos(rad);
		int y=cy+radius*sin(rad);
		setPixel(x,y,ch); 
	}
}

void drawHeart(int cx, int cy, int size,char ch){
	for (double t=0; t<=2*PI;t += 0.01){
		int x=cx+size*16*pow(sin(t),3);
		int y=cy-size*(13*cos(t)-5*cos(2*t)-2*cos(3*t)-cos(4*t));
		setPixel(x/4,y/8+HEIGHT/2,ch); 
	} 
}
void drawText(int x,int y,char*text){
	while (*text){
		setPixel(x++,y,*text++);
	} 
}

void drawCake(int cx,int cy){
	for (int i=-15; i<=15; i++){
		for (int j=0; j<8; j++){
			setPixel(cx + i,cy + j,j==0 ?'_':'|'); 
		} 
	}
	for (int i= -10; i<=10; i++){
		for (int j=0; j<8; j++){
			setPixel(cx +i,cy=j,j==0 ?'_':'|');
		}
	}
	
	for (int i=-5; i<=5;i++){
		for (int j=12; j<15; j++){
			setPixel(cx+i,cy+j, j==12?'_':'|');
		} 
	} 
	
	 for (int i=-4;i<=4; i+=2){
	 	setPixel(cx+i, cy+15,'|');
	 	setPixel(cx+i, cy+16,'^');
	 } 
}

void render(){
	system("cls");
	for (int y=0; y<HEIGHT;y++){
		for (int x=0;x<WIDTH;x++){
			putchar(buffer[y][x]);
		}
		putchar('\n');
	}
}

void playBirthdaySong(){
	printf("正在播放生日快乐歌...\n");
	int noteCount=sizeof(birthdayNotes)/sizeof(birthdayNotes[0]);
	for (int i=0;i < noteCount;i++){
		if (birthdayNotes[i]>0){
			Beep(birthdayNotes[i],noteDurations[i]);
		}else{
			Sleep(noteDurations[i]);
		}
	}
}
			
void fireworksAnimation() {
	for (int frame=0; frame<50; frame++){
		clearBuffer();
		
		for (int i=0;i<5;i++){
			int cx= rand()% WIDTH;
			int cy= rand()% (HEIGHT/2);
			int radius =(frame % 10) +5;
			char chars[] ={'*','+','.','o','o'};
			drawCircle(cx,cy,radius,chars[rand()% 5]);				
		}
		
		char* messages[] ={
			"妈妈生日快乐！",
			"永远年轻美丽！" ,
			"健康幸福每一天！", 
		};
		
		drawText(20,HEIGHT -5,messages[frame % 4]);
		drawText(15,HEIGHT -3,"愿这份祝福伴随您每一天！");
		
		render();
		Sleep(200);		
	} 
}

void heartAnimation(){
	for (int size=1;size <=8;size++){
		clearBuffer();
		drawHeart(WIDTH/2,HEIGHT/2,size,'*');
		
		char* messages[] ={
			"妈妈，您辛苦了!",
			"生日快乐！",
			"愿您永远幸福！",
			"感谢您的养育之恩！" 	
	    };
	
	    drawText(25,2,messages[size % 4]);
		drawCake (WIDTH/2, HEIGHT - 8);
	
		render();
		Sleep(400); 
	}
}
void typewriterEffect(char*text,int x,int y,int delayMs){
	for (int i=0; text[i] !='\0';i++){
		setPixel(x+i,y,text[i]);
		render();
		Sleep(delayMs);
	}
}
int main()
{
	srand((unsigned int)time(NULL));
	printf("准备为妈妈播放生日祝福...\n");
	Sleep(1000);
	clearBuffer();
	typewriterEffect("亲爱的妈妈：", 10,2, 100);
	typewriterEffect("在这个特别的日子里",10,4,80);
	typewriterEffect("我用代码编织祝福，",10,6,80);
	typewriterEffect("用程序谱写爱意.",10,8,80);
	typewriterEffect("愿这份特别的礼物带给您惊喜！",10,10,60);
	Sleep(1500);
	
	playBirthdaySong();
	Sleep(1000);
	printf("显示爱心动画...\n");
	heartAnimation();
	Sleep(1000);
	
	printf("烟花表演开始...\n");
	fireworksAnimation();
	Sleep(1000);
	
	clearBuffer();
	drawText(30,2,"生日快乐！"); 
	drawText(22,4,"亲爱的妈妈，愿您："); 
	drawText(15,6,"健康平安 笑口常开 青春永驻"); 
	drawText(15,8,"万事如意 幸福美满 天天开心"); 
	
	drawHeart(0, 0, 3,'*');
	
	drawText(25,HEIGHT -3,"永远爱您的孩子"); 
	drawText(30,HEIGHT -1,"按任意键退出...");
	
	render();
	
	getchar();
	return 0;
}

	
	
	

	
