#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int
sbit we = P2^7;
sbit du = P2^6;
sbit beep = P2^3;
sbit LED1 = P1^0;
uchar counter;
uint time_counter = 1500;

unsigned char code wei[]=
{0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f}; //����ܸ�λ�����

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
                0x00,  //Ϩ��
                0x00  //�Զ���
 
                         };

void delay(uint z)
{
	uint x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--);
}

void display(uint i)
{
	uint qian, bai, shi, ge;
	qian = i / 1000;

	bai = i % 1000;
	bai = bai / 100;

	shi = i % 100; 
	shi = shi / 10;

	ge  = i % 10; //����

	P0 = 0xff;
	we = 1;
	P0 = wei[0]; //������һλ�����
	we = 0;

	du = 1;
	P0 = leddata[qian];
	du = 0;
	delay(1);

	P0 = 0xff;
	we = 1;
	P0 = wei[1];//�����ڶ�λ�����
	we = 0;

	du = 1;
	P0 = leddata[bai];
	du = 0;
	delay(1);	

	P0 = 0xff;
	we = 1;
	P0 = wei[2];//������3w
	we = 0;

	du = 1;
	P0 = leddata[shi];
	du = 0;
	delay(1);


    P0 = 0xff;
	we = 1;
	P0 = wei[3];//�����ڶ�λ�����
	we = 0;

	du = 1;
	P0 = leddata[ge];
	du = 0;
	delay(1);
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

void main()
{
	TMOD = 0x01;//��ʱ��0 ����ģʽ1 16ģʽ��ʱ��
	TH0 = (65536 - 46082)/256;
	TL0 = (65536 - 46082)%256; //��ʱ50ms
	TR0 = 1;

	while(1)
	{
		if(TF0 == 1)
		{
			TF0 = 0;
			TH0 = 0x4b;
			TL0 = 0xfe; //��ʱ50ms
			counter++;
		}
		if(counter == 20)
		{
			counter = 0;
			//LED1 = ~LED1;
			time_counter--;
		}

		if(time_counter == 0)
		{
			Beeeeeep(3);
 		}
		display(time_counter);	
	}
}