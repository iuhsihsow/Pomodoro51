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
uint rest_counter = 300;
uint status = 0; // 0 for  work, 1 for rest
uint current_counter = 0;
uint beep_times = 2;
uint pause = 0; // 1 for pause, 0 for work


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

void displayLow(uint i)
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
	P0 = wei[4]; //������һλ�����
	we = 0;

	du = 1;
	P0 = leddata[qian];
	du = 0;
	delay(1);

	P0 = 0xff;
	we = 1;
	P0 = wei[5];//�����ڶ�λ�����
	we = 0;

	du = 1;
	P0 = leddata[bai];
	du = 0;
	delay(1);	

	P0 = 0xff;
	we = 1;
	P0 = wei[6];//������3w
	we = 0;

	du = 1;
	P0 = leddata[shi];
	du = 0;
	delay(1);


    P0 = 0xff;
	we = 1;
	P0 = wei[7];//�����ڶ�λ�����
	we = 0;

	du = 1;
	P0 = leddata[ge];
	du = 0;
	delay(1);
}


uchar KeyScan()	//������ֵ���Ӻ���
{
	uchar cord_l,cord_h;//�������ߺ����ߵ�ֵ�Ĵ������
	P3 = 0x0f;//0000 1111
	if( (P3 & 0x0f) != 0x0f)//�ж��Ƿ��а�������
	{
		delay(5);//�������
		if( (P3 & 0x0f) != 0x0f)//�ж��Ƿ��а�������
		{
			  cord_h = P3 & 0x0f;// ��������ֵ
			  P3 = cord_l | 0xf0;
			  cord_l = P3 & 0xf0;// ��������ֵ
			  while( (P3 & 0xf0) != 0xf0 );//���ּ��
			  return (cord_l + cord_h);//���ؼ�ֵ��
		}	
	}
		
}

// Test keys
void KeyPro()
{
	switch( KeyScan() )
	{
	 	//��һ�м�ֵ��
		case 0xee: P0 = leddata[0];		break;
		case 0xde: P0 = leddata[1];		break;
		case 0xbe: P0 = leddata[2];		break;
		case 0x7e: P0 = leddata[3];		break;
		
		//�ڶ��м�ֵ��
		case 0xed: P0 = leddata[4];		break;
		case 0xdd: P0 = leddata[5];		break;
		case 0xbd: P0 = leddata[6];		break;
		case 0x7d: P0 = leddata[7];		break;

		//�����м�ֵ��
		case 0xeb: P0 = leddata[8];		break;
		case 0xdb: P0 = leddata[9];		break;
		case 0xbb: P0 = leddata[10];	break;
		case 0x7b: P0 = leddata[11];	break;

		//�����м�ֵ��
		case 0xe7: P0 = leddata[12];	break;
		case 0xd7: P0 = leddata[13];	break;
		case 0xb7: P0 = leddata[14];	break;
		case 0x77: P0 = leddata[15];	break;
		//��������
		case 0xfe: P0 = leddata[16];	break;
		case 0xfd: P0 = leddata[17];	break;
		case 0xfb: P0 = leddata[18];	break;
		case 0xf7: P0 = leddata[19];	break;
	}	
}



void main()
{
	TMOD = 0x01;//��ʱ��0 ����ģʽ1 16ģʽ��ʱ��
	TH0 = (65536 - 46082)/256;
	TL0 = (65536 - 46082)%256; //��ʱ50ms
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
			TL0 = 0xfe; //��ʱ50ms
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