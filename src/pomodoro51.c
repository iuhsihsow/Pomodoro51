#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int
sbit we = P2^7;
sbit du = P2^6;
sbit beep = P2^3;
sbit LED1 = P1^0;
uchar counter;
uint time_counter = 1080;
uint rest_counter = 300;
uint status = 0; // 0 for  work, 1 for rest
uint current_counter = 0;
uint beep_times = 2;
uint pause = 0; // 1 for pause, 0 for work


unsigned char code wei[]=
{0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f}; //数码管各位的码表

uchar code leddata[]={ 
 
                0x3F,  //"0"
                0x06,  //"1"
                0x5B,  //"2"
                0x4F,  //"3"
                0x66,  //"4"
                0x6D,  //"5"
                0x7D,  //"6"
                0x07,  //"7"
                0x7F,  //"8"
                0x6F,  //"9"
                0x77,  //"A"
                0x7C,  //"B"
                0x39,  //"C"
                0x5E,  //"D"
                0x79,  //"E"
                0x71,  //"F"
                0x76,  //"H"
                0x38,  //"L"
                0x37,  //"n"
                0x3E,  //"u"
                0x73,  //"P"
                0x5C,  //"o"
                0x40,  //"-"
                0x00,  //熄灭
                0x00  //自定义
 
                         };

void delay(uint z)
{
	uint x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--);
}

void Beeeeeep(uint times)
{
  uint total = 0;
  while( total < times )
  {
   		total ++;
		beep = ~beep;
		delay(200);
		beep = ~beep;
		delay(800);
  }
}

void display(uint i)
{
	uint qian, bai, shi, ge;
	qian = i / 1000;

	bai = i % 1000;
	bai = bai / 100;

	shi = i % 100; 
	shi = shi / 10;

	ge  = i % 10; //求余

	P0 = 0xff;
	we = 1;
	P0 = wei[0]; //点亮第一位数码管
	we = 0;

	du = 1;
	P0 = leddata[qian];
	du = 0;
	delay(1);

	P0 = 0xff;
	we = 1;
	P0 = wei[1];//点亮第二位数码管
	we = 0;

	du = 1;
	P0 = leddata[bai];
	du = 0;
	delay(1);	

	P0 = 0xff;
	we = 1;
	P0 = wei[2];//点亮第3w
	we = 0;

	du = 1;
	P0 = leddata[shi];
	du = 0;
	delay(1);


    P0 = 0xff;
	we = 1;
	P0 = wei[3];//点亮第二位数码管
	we = 0;

	du = 1;
	P0 = leddata[ge];
	du = 0;
	delay(1);
}

void displayLow(uint i)
{
	uint qian, bai, shi, ge;
	qian = i / 1000;

	bai = i % 1000;
	bai = bai / 100;

	shi = i % 100; 
	shi = shi / 10;

	ge  = i % 10; //求余

	P0 = 0xff;
	we = 1;
	P0 = wei[4]; //点亮第一位数码管
	we = 0;

	du = 1;
	P0 = leddata[qian];
	du = 0;
	delay(1);

	P0 = 0xff;
	we = 1;
	P0 = wei[5];//点亮第二位数码管
	we = 0;

	du = 1;
	P0 = leddata[bai];
	du = 0;
	delay(1);	

	P0 = 0xff;
	we = 1;
	P0 = wei[6];//点亮第3w
	we = 0;

	du = 1;
	P0 = leddata[shi];
	du = 0;
	delay(1);


    P0 = 0xff;
	we = 1;
	P0 = wei[7];//点亮第二位数码管
	we = 0;

	du = 1;
	P0 = leddata[ge];
	du = 0;
	delay(1);
}


uchar KeyScan()	//带返回值的子函数
{
	uchar cord_l,cord_h;//声明列线和行线的值的储存变量
	P3 = 0x0f;//0000 1111
	if( (P3 & 0x0f) != 0x0f)//判断是否有按键按下
	{
		delay(5);//软件消抖
		if( (P3 & 0x0f) != 0x0f)//判断是否有按键按下
		{
			  cord_h = P3 & 0x0f;// 储存行线值
			  P3 = cord_l | 0xf0;
			  cord_l = P3 & 0xf0;// 储存列线值
			  while( (P3 & 0xf0) != 0xf0 );//松手检测
			  return (cord_l + cord_h);//返回键值码
		}	
	}
		
}

// Test keys
void KeyPro()
{
	switch( KeyScan() )
	{
	 	//第一行键值码
		case 0xee: P0 = leddata[0];		break;
		case 0xde: P0 = leddata[1];		break;
		case 0xbe: P0 = leddata[2];		break;
		case 0x7e: P0 = leddata[3];		break;
		
		//第二行键值码
		case 0xed: P0 = leddata[4];		break;
		case 0xdd: P0 = leddata[5];		break;
		case 0xbd: P0 = leddata[6];		break;
		case 0x7d: P0 = leddata[7];		break;

		//第三行键值码
		case 0xeb: P0 = leddata[8];		break;
		case 0xdb: P0 = leddata[9];		break;
		case 0xbb: P0 = leddata[10];	break;
		case 0x7b: P0 = leddata[11];	break;

		//第四行键值码
		case 0xe7: P0 = leddata[12];	break;
		case 0xd7: P0 = leddata[13];	break;
		case 0xb7: P0 = leddata[14];	break;
		case 0x77: P0 = leddata[15];	break;
		//独立键盘
		case 0xfe: P0 = leddata[16];	break;
		case 0xfd: P0 = leddata[17];	break;
		case 0xfb: P0 = leddata[18];	break;
		case 0xf7: P0 = leddata[19];	break;
	}	
}



void main()
{
	TMOD = 0x01;//定时器0 工作模式1 16模式定时器
	TH0 = (65536 - 46082)/256;
	TL0 = (65536 - 46082)%256; //定时50ms
	TR0 = 1;
	current_counter = time_counter;

	while(1)
	{
		uchar key = KeyScan();
		if(key == 0xfe)
		{
			Beeeeeep(1);
			if(pause == 0)
			{
				pause = 1;
			}
			else if(pause == 1)
			{
				pause = 0;
			}
		}


		if(TF0 == 1 && pause == 0)
		{
			TF0 = 0;
			TH0 = 0x4b;
			TL0 = 0xfe; //定时50ms
			counter++;
		}
		if(counter == 20 && pause == 0)
		{
			counter = 0;
			//LED1 = ~LED1;
			current_counter--;
		}

		if(current_counter == 0)
		{
			Beeeeeep(beep_times);
			if(status == 1){
			status = 0;}
			else if(status == 0){
			status = 1;}
			if(status == 0){
			current_counter = time_counter;}
			else if(status ==  1){
			current_counter = rest_counter;}
 		}
		if(status == 0){
		display(current_counter);}
		else if(status == 1){
		displayLow(current_counter);}
	}
}