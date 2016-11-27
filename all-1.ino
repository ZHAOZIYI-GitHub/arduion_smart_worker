#include "dht11.h"

dht11 DHT11;

int Weizhigaibian;//�仯Ϊ1

int yuanweizhi;//0Ϊ�ڼң�1Ϊ����

int TOF;//���϶ȿ��أ�1

#define DHT11PIN_IN 2	//����pin

#define DHT11PIN_OUT 8	//����pin

int fengmingqi;

#define fengmingqipin 3//������pin

#define Fengmingqi_Delay 50//��������������ʱ(Ƶ��)

#define QW1 4//�������

#define QW2 5//����Զ��

int B_Getdoor;//��ʵλ��

int QW3[2];//״̬�洢

#define menling 6//����������pin 

#define HuoyanPin A3//����pin

#define HUOYAN_MAX 100

int fine_fengmingqi;

#define fine_fengmingqi_delay 10   //�����������ʱ

#define Guangqiang_Out A0

#define Guangqiang_In  A1

#define GuangqiangMax 200

int D_OpenTolight = 0;//����

int B_OpenTolight = 0;//�仯

#define Turang0shidu A2

#define TurangshiduMax 700

int D_OpenToWater=0;//����

int B_OpenToWater = 0;//�仯

const char chare_temperturer[] = "Temperture";

const char chare_Cr[] = "Mencoming";

const char chare_Cother[] = "Tocother";

const char chare_Zhaoji[] = "Zhaoji";

const char chare_Rumen[] = "Rumen";

const char chare_Gethome[] = "Gethome";

const char chare_Huoyan[] = "Huayan";

void send_data_Tc_Outside()
{
	Serial.print("/1\n");//������
	Serial.println(chare_temperturer);//����key
	Serial.println(Temperaturer(1));//���Ӳ���
	Serial.print("\n");
	Serial.print("/0\n");//�����ӣ���/1����һ��/0Ϊһ�ڣ�
}

void send_data_mencoming()
{
	Serial.print("/1\n");
	Serial.println(chare_Cr);
	Serial.print("/0\n");  
}

void send_data_cothering()
{
	Serial.print("/1\n");
	Serial.println(chare_Cother);
	Serial.print("/0\n"); 
}

void send_data_Zhaoji()
{
	Serial.print("\n/1");
	Serial.println(chare_Zhaoji);
	Serial.print("/0\n");
}

void send_data_Getdoor()
{
	Serial.print("/1\n");
	Serial.println(chare_Rumen);
	Serial.print("/0\n");	
}

void send_data_Gethome()
{
	Serial.print("/1\n");
	Serial.println(chare_Gethome);
	Serial.print("/0\n");
}

void send_data_Fire()
{
	Serial.print("/1\n");
	Serial.println(chare_Huoyan);
	Serial.print("/0\n");
}

void new_Delay(int Delay)//��ʱ����
{
	int i;
	for (i = 0; i<(Delay/Fengmingqi_Delay); i++)
		fengmingqi1();
}

void OpenToWater(int Plantnumber)
{
	D_OpenToWater = 1;
	B_OpenToWater = 1;
}

void CloseToWater(int Plantnumber)
{
	D_OpenToWater = 2;
	B_OpenToWater = 1;
}

int TurangshiduGeter(int Plantnumber)
{
	if (Plantnumber == 0)//һ��ֲ����
		return analogRead(Turang0shidu);
	else
	{

	}
}

//����ǿ��
int GuangqiangGeter(int room_s)
{
	if (room_s == 1)//Outside
		return analogRead(Guangqiang_Out);
	else if (room_s == 0)//����
		return analogRead(Guangqiang_In);
	else
		return 0;
}

void CloseChuanglian()
{
	D_OpenTolight = 1;
	B_OpenTolight = 1;
}

void OpenLight()
{
	D_OpenTolight = 2;
	B_OpenTolight = 1;
}

void QWI()    
{
	QW(digitalRead(QW1), digitalRead(QW2));
}

int QW(int QW4, int QW5)
{
	if (QW4 == 1)
	{
		if (QW5 == 1)//1,1
		{
			QW3[0] = 1;
			QW3[1] = 1;
			//delay(1000); 
			new_Delay(1000);
		}
		else if (QW5 == 0)//1,0
		{
			new_Delay(1000);
			if (QW5 == 1)
			{
				QW3[0] = 0;
				QW3[1] = 0; 
				new_Delay(1000);
			}
		}
		else
		{
		}
	}
	else
	{
		if (QW5 == 1)//0,1
		{
			QW3[0] = 1;
			QW3[1] = 1;
			new_Delay(1000);
			if (QW4 == 1)
			{
				QW3[0] = 0;
				QW3[1] = 2;
			}
		}
		else//0,0
		{
			QW3[0] = 0;
			QW3[1] = 0;
		}
	}
	return 0;
}

void PanduanQW()
{
	QWI();
	if (QW3[0] == 0)//����
		if (yuanweizhi == 0)//�ڼ�
		{
			//λ�ò���
			B_Getdoor = 1;
			//send_data_Getdoor();
		}
		else
		{
			//�ؼ�
			//send_data_Gethome();
			Weizhigaibian = 1;
			yuanweizhi = 1;//�ڼ�
		}
	else
		if (yuanweizhi == 0)
		{
			Weizhigaibian = 1;
			yuanweizhi = 0;//����
		}
		else
		{

		}
}

double Fahrenheit(double celsius)     //�����¶ȶ�ת��Ϊ�����¶�
{
	return 1.8 * celsius + 32;
}

//����1ΪDHT11PIN_IN ��	DHT11PIN_OUT
double Temperature_geter_doublt(int DHT11PIN)
{
	int chk = DHT11.read(DHT11PIN);
	if (TOF == 1)
	{
		return Fahrenheit(DHT11.temperature);
	}
	else
	{
		return DHT11.temperature;
	}
}

double Temperaturer_double(int room_s)
{
	if (room_s == 1)//OUTSIDE
	{
		return Temperature_geter(DHT11PIN_OUT);
	}
	else
	{
		return Temperature_geter(DHT11PIN_IN);
	}
}

double Humidity_double()
{
	int chk = DHT11.read(DHT11PIN_OUT);
	return (float)DHT11.humidity;
}

//����1ΪDHT11PIN_IN ��	DHT11PIN_OUT
int Temperature_geter(int DHT11PIN)
{
	int chk = DHT11.read(DHT11PIN);
	if (TOF == 1)
	{
		return (int)Fahrenheit(DHT11.temperature);
	}
	else
	{
		return (int)DHT11.temperature;
	}
}

int Temperaturer(int room_s)
{
	if (room_s == 1)//OUTSIDE
	{
		return (int)Temperature_geter(DHT11PIN_OUT);
	}
	else
	{
		return (int)Temperature_geter(DHT11PIN_IN);
	}
}

int Humidity()
{
	int chk = DHT11.read(DHT11PIN_OUT);
	return (int)DHT11.humidity;
}

void fengmingqi1() 
{
	if(fine_fengmingqi==1)
	{
		digitalWrite(fengmingqipin, 1);
		delay(fine_fengmingqi_delay / 2);
		digitalWrite(fengmingqipin, 0);
		delay(fine_fengmingqi_delay / 2);
	}
	else if (fengmingqi == 1)
	{
		digitalWrite(fengmingqipin, 1);
		delay(Fengmingqi_Delay/2);
		digitalWrite(fengmingqipin, 0);
		delay(Fengmingqi_Delay/2);
	}
	else 
	{
		digitalWrite(fengmingqipin, 0);
		delay(Fengmingqi_Delay);
	}
}

void setpin()//�˿ڳ�ʼ��
{
	pinMode(QW1, INPUT); //Զ��
	pinMode(QW2, INPUT);  //����
	pinMode(DHT11PIN_IN, INPUT);//�¶ȴ�����
	pinMode(DHT11PIN_OUT, INPUT);//�¶ȴ�����
	pinMode(fengmingqipin,OUTPUT);
	pinMode(menling,INPUT);
	pinMode(Guangqiang_Out, INPUT);
	pinMode(Guangqiang_In, INPUT);
	pinMode(Turang0shidu, INPUT);
}

void panduan()
{
	if (QW3[0] == 1)
	{
		if (Weizhigaibian == 1)
		{
			send_data_Tc_Outside();
			if ((Temperature_geter(DHT11PIN_IN) - Temperature_geter(DHT11PIN_OUT)) >= 10)
			{
				send_data_cothering();
			}
			else if ((Temperature_geter(DHT11PIN_IN) - Temperature_geter(DHT11PIN_OUT)) <= -10)
			{
				send_data_cothering();
			}
			else
			{
			}
		}

	}
	else{
	}
	if (QW3[1] == 2)
	{
		send_data_Zhaoji();
	}
	else{
	}
	if (digitalRead(menling) == 1)
	{
		send_data_mencoming();
	}
	else{
	}
	if (Weizhigaibian == 1)
	{
		//�ж�λ�÷���
		Weizhigaibian = 0;
	}
	else{
	}
	if (digitalRead(fengmingqipin) == 1)
	{
		fengmingqi = 1;
	}
	else
	{
		fengmingqi = 0;
	}
	if (GuangqiangGeter(1) <= GuangqiangMax)
	{
		CloseChuanglian();
	}
	else
	{
		OpenLight();
	}
	if (TurangshiduGeter(0) <= TurangshiduMax)
	{
		OpenToWater(0);
	}
	else
	{
		CloseToWater(0);
	}
	if (analogRead(HuoyanPin) == 1)
	{
		send_data_Fire();
		fine_fengmingqi = 1;
	}
	else
	{
		fengmingqi = 0;
		fine_fengmingqi = 1;
	}
}

void shuju()
{
	PanduanQW();
	fengmingqi1();
}

void NEW_serial()
{
	Serial.print(Temperaturer(0));//����
	Serial.print(" ");
	Serial.print(Temperaturer(1));//����
	Serial.print(" ");
	Serial.print(Humidity());//��
	Serial.print(" ");
	//1horse���ˣ�
	if (digitalRead(menling) == 1)
	{
		Serial.print("1");
		Serial.print(" ");
		fengmingqi=1;
	}
	else
	{
		Serial.print("0");
		Serial.print(" ");
		fengmingqi = 0;
	}
	if (QW3[0] == 1)
	{
		if (Weizhigaibian == 1)
		{
			//send_data_Tc_Outside();
			if ((Temperature_geter(DHT11PIN_IN) - Temperature_geter(DHT11PIN_OUT)) >= 10)
			{
				Serial.print("1");
				Serial.print(" ");
			}
			else if ((Temperature_geter(DHT11PIN_IN) - Temperature_geter(DHT11PIN_OUT)) <= -10)
			{
				Serial.print("1");
				Serial.print(" ");
			}
			else
			{
			}
		}

	}
	else 
	{
		Serial.print("0");
		Serial.print(" ");
	}
	//����
	if (QW3[1] == 2)
	{
		Serial.print("1");
		Serial.print(" ");
	}
	else 
	{
		Serial.print("0");
		Serial.print(" ");
	}
	//�ڼ����˽�����
	if (B_Getdoor == 1)
	{
		Serial.print(1);
		B_Getdoor = 0;
		Serial.print(" ");
	}
	else
	{
		Serial.print(0);
		Serial.print(" ");
	}
	if (analogRead(HuoyanPin)<=HUOYAN_MAX)
	{
		Serial.print(1);
		Serial.print(" ");
		fine_fengmingqi = 1;
	}
	else
	{
		Serial.print(0);
		Serial.print(" ");
		fine_fengmingqi = 0;
	}
	//1.2Ϊ�仯��ˮբ����,ռ1λ
	if (B_OpenToWater == 1)
	{
		B_OpenToWater = 0;
		Serial.print(D_OpenToWater);//1Ϊ��ʼ��ˮ��2Ϊ�ر�,0Ϊ�޶���
		Serial.print(" ");
		D_OpenToWater = 0;

	}
	else
	{
		Serial.print(0);
		Serial.print(" ");
	}
	//1Ϊ�仯��ˮբ����,ռ1λ
	if (B_OpenTolight == 1)
	{
		B_OpenTolight = 0;
		Serial.print(D_OpenTolight);//2Ϊ���ƣ�1Ϊ�ش���,0Ϊ�޶���
		Serial.print(" ");
		D_OpenTolight = 0;

	}
	else
	{
		Serial.print(0);
		Serial.print(" ");
	}
	Serial.println();
	new_Delay(3000);
}

void Debug()
{
	Serial.print("(");
	Serial.print(digitalRead(QW1));
	Serial.print(" ");
	Serial.print(digitalRead(QW2));
	Serial.print(" ");
	Serial.print(analogRead(A0));
	Serial.print(" ");
	Serial.print(analogRead(A3));
	Serial.print(" ");
	Serial.print(analogRead(A2));
	Serial.print(")\n");

}

void setup()
{
	Serial.begin(9600);
	setpin();//��ʼ���˿�

}

void loop()
{
	fengmingqi1();
	shuju();//���ݳ�ʼ��
	//panduan();//�жϲ���
	NEW_serial();//���������
	//Debug();
	
}