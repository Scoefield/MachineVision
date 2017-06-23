#include "printmenu.h"
#include "tired_steer_detect_system.h"
#include <time.h>
#include <stdlib.h>
extern "C" {
#include <stdlib.h>
}



#define P  0.93      //0.8为比例系数，伪确定一个疲劳系数。
#define HIGHT 80
#define WIGHT 80
#define M 80

//-------------------- 全局变量定义区 -------------------
int menu1=0,menu2=0;
int do_flag = 0;
int mode2_flag = 1;
char temp[12],temq[12];
char *smenu;char *sm;char *sm2;
float mmenu;
int first_count=0,second_count=0,ignore_count=0,numberdetect=0;
double countsum=0,average;
int flag=0;
int CCD_IMAGE_DEAL[HIGHT][WIGHT];
int frame_black[HIGHT];
int eye_black[HIGHT];

//bool flag = 0;
int myQueue[ M ];  
bool begin_deal_flag = 0;          //处理算法开始标志位
int add_count = 0;
double sumHigh = 0;
double averageHigh = 0;
double finalHigh = 0;
double detectCompare = 0;
double detectHigh = 0;
int befor_count = 0;
int begin_count = 0;
extern int front,rear;                    //定义头尾指针
int menuMode;
int fresh_count = 0;

//--------------- 计算图像面积，黑色像素的百分比 -------------------
double AreaPercent( Mat leyer , Mat reyer )  
{
	double areapercent,leyer_area,reyer_area;
	leyer_area = (leyer.cols)*(leyer.rows);     //leyer_area 为2100左右 leyer.cols：500左右 leyer.rows：40左右
      
    int white_counter = 0;
	int black_counter = 0;
	int area = 0;
	int nrows = leyer.rows;
	int ncols = leyer.cols;
    //迭代器访问像素点（左眼）  
    Mat_<uchar>::iterator it = leyer.begin<uchar>();  
    Mat_<uchar>::iterator itend = leyer.end<uchar>();    
    for (; it!=itend; ++it)  
    {  
        if((*it)>0) white_counter+=1; //二值化后，像素点是0或者255  
		else  black_counter+=1; 
		area+=1;   //总像素点
    }  
	cout << "white_counter=" << white_counter<< " " << "black_counter=" << black_counter << endl;
    return black_counter;    //返回黑色像素点
} 


//------------------ 眼睛开合度计算函数 -----------------
int eyesHigh(Mat topLeftOfFace_thresh, Mat toprightOfFace_thresh, TiredSteerDetectSystemTh *th)
{
	//int eye_high = 0;
	int eyeHigh = 0;
	int nrows = topLeftOfFace_thresh.rows;
	int ncols = topLeftOfFace_thresh.cols;

	int max = 0;

	for (int i=0;i< nrows; i++)  //行循环
	{
		int counter = 0;
		uchar* data = topLeftOfFace_thresh.ptr<uchar>(i);   //获取第i行的首地址  
		for(int j=0;j<ncols;j++) //列循环
		{
			if(data[j] == 0)  //二值化后，像素点是0或者255 ,0表示黑点，255表示白点
			{
				counter+=1;
				CCD_IMAGE_DEAL[i][j] = 0;
			}	
			else 
			    CCD_IMAGE_DEAL[i][j] = 255;
		} 
		frame_black[i] = counter;  //保存该行对应黑点的个数			
	}

	//计算眼睛高度
    for(int m=ncols/2-6; m<ncols/2+6; m++) //列循环
	{
		int blackEyeCount = 0;
        for( int k=5; k<nrows-5; k++)  //行循环
		{
			if( CCD_IMAGE_DEAL[k][m] == 0)
			{
				blackEyeCount++;
				if( CCD_IMAGE_DEAL[k+1][m] == 255 && k>nrows/3 )
					break;
			}
		}
		eye_black[m] = blackEyeCount;
		if( max < eye_black[m] )  
		{
			max = eye_black[m];
		}
	}
	
	eyeHigh = max;
    imageDuilie(eyeHigh, th); //用队列保存眼睛高度数据
    emit th->freshCustomPlot(eyeHigh);
    return eyeHigh;       //返回眼睛高度
}

//---------------- 用队列保存眼睛高度数据 ----------------
void imageDuilie(int frame_high, TiredSteerDetectSystemTh *th)
{	
	addQ( myQueue, &rear, frame_high ); 

	sumHigh += frame_high;
	add_count++;
    fresh_count++;
	if(add_count == M)
	{
        cout << "模式1初始化完成！" <<endl;     //模式1初始化完成
        emit th->showTheInitedDialog("Mode one is initialized!");
		averageHigh = sumHigh/M;  //求平均值作为初始化眼睛高度
        finalHigh = averageHigh*0.95;
		cout << "averageHigh=" << averageHigh << "   finalHigh"<< finalHigh<<endl;

	}
	if( add_count > M ) 
	{
		sumHigh = 0;  //清零防止溢出

		for( int j=0; j<M-1; j++)
		  myQueue[j] = myQueue[j+1];
		myQueue[M-1] = frame_high;

		begin_deal_flag = 1;  
	}
	//方法二：基于眼睛高度判断是否疲劳
	if( begin_deal_flag == 1 )
	{
        if( befor_count<M*3/5 ) befor_count++;
        else
        {
            for( int j=0; j<M; j++)
            {
                if(myQueue[j] < averageHigh)  //低于正常疲劳度
                detectHigh++;
            }
            befor_count = 0;
            detectCompare = detectHigh/M;
        }
	}
//    if( detectHigh > M/2 && detectHigh < M*2/3 )
//    {
//            cout << "detectHigh=" << detectHigh << "你已轻度疲劳，请注意驾驶!" << endl;
//            detectHigh = 0;
//    }
    if( fresh_count == M)    //detectHigh和detectCompare两个值传进来
    {
        fresh_count = 0;

        emit th->freshTableWidget(detectHigh, detectCompare);
    }
    if( detectHigh >=  M*2/3 )
    {
            cout << "detectHigh=" << detectHigh << "你已经严重疲劳，请注意驾驶!" << endl;
            emit th->warnningSignal();
            system("aplay /home/pi/Qt-Project/warnning.wav");
            detectHigh = 0;
    }


}

//------------------- 菜单栏 -------------------------
void printmenu()
{
	int menu;
	printf("----------------------------------------------------------------------\n");
	printf("----------------------- 人眼识别系统菜单选择 ---------------------------\n");
	printf("----------------------------------------------------------------------\n");
	printf("1.你是否已经初始化过吗 ? 如果有, 请输入：1                               \n");
	printf("2.如果你没有初始化过，请先初始化。如果你想现在初始化，请输入：2            \n");
	printf("3.退出                                                                \n");
	printf("----------------------------------------------------------------------\n");
	printf("----------------------------------------------------------------------\n");
	printf("请输入你的选择 :");
    scanf("%d",&menu);
    //getchar();
	if(menu==1)
		printmenu1();
	if(menu==2)
		printmenu2();
	if(menu==3)
		exit(0);
	if(menu!=1&&menu!=2&&menu!=3)
	{
		printf("ERROR INPUT !!!\n");
		getchar();
		exit(0);
	}

}

void printmenu1()
{
	printf("----------------------------------------------------------------------\n");
	printf("--------------------- 获取已经初始化的用户名信息 -----------------------\n");
	printf("----------------------------------------------------------------------\n");
	printf("请输入你的用户名 :");
	menu1=1;
	//scanf("%s",smenu);
    gets(temq);
	smenu=temq;
	mmenu=search(smenu);
	if(mmenu==-1.0)
	{
		printf("这里没有你的初始化数据，请重试 !\n");
		printmenu();
		//exit(0);
	}
	printf("\n 你的用户名是： %s, 清醒状态疲劳值为： %f\n",smenu,mmenu);

}


void printmenu2()
{
	printf("----------------------------------------------------------------------\n");
	printf("----------------------- 用户填写初始化信息 -----------------------------\n");
	printf("----------------------------------------------------------------------\n");
    printf("请输入你想要初始化的用户名 :");
	menu2=1;
	gets(temp);
}

float search(char *s)
  {
	  char p[100];
	  float x=-1.0,y;
	  FILE *fp;
	  fp=fopen("username.txt","r");

	  while(fp)
	  {
          if(feof(fp))
			  break;
		  fscanf(fp,"%s%f",p,&y);
		  if(strcmp(p,s)==0)
			  x=y;
	  }
	  fclose(fp);
	  return x;
  }

//--------------- 眼睛疲劳判断算法函数 ----------------------
void printmenu_deal(Mat leyer, Mat reyer, TiredSteerDetectSystemTh *th)
{		
	//方法一：基于眼睛面积大小变化
	double length;
    if(mode2_flag==1)     //菜单模式2已选择（用户初始化过程）
    {
		if(ignore_count<10) ignore_count++;
        else if(first_count<80)
		{
			length=AreaPercent(leyer,reyer);  //返回黑色像素点个数
			//if(length==0)   break;
            printf("%d    %f\n",first_count,length);
			first_count++;			
			countsum+=length;
		}
    }
    if(first_count==80)     //获取100帧数据取平均值，再乘于疲劳系数作为初始清醒状态疲劳程度
	{
        cout << "模式2初始化完成！" << endl;     //模式2初始化完成
        emit th->showTheInitedDialog("Mode two is initialized!");
		first_count = 0;
		average=countsum/100;
		mmenu=average*P;    //P为疲劳比例系数
		printf("--------------------------------------------------");
		printf("\n\n 初始化清醒状态疲劳程度mmenu=%f\n\n",mmenu);
		printf("--------------------------------------------------\n");
        menu2=0;
		sm2=temp;
        //printf("你的用户名为:%s ",sm2);
        //insertdata(sm2,mmenu); //写入用户名和清醒状态疲劳程度数值
        //printmenu();
        do_flag = 1;
        mode2_flag = 0;
	}

    if(do_flag==1)    //菜单模式1已选择
	{
		if(ignore_count<10) ignore_count++;
		else if(second_count<30)
		{				
			length=AreaPercent(leyer,reyer);   //返回黑色像素点个数
			//if(length==0)  break;
			printf("%d    %f\n",second_count,length);
			second_count++;
			if(length<mmenu)  //低于正常疲劳度
			numberdetect++;  
		}
	}

	if(second_count==30&&flag==0)
	{
		if(numberdetect>10)   
		{
			FILE *fp;//这块也可以继续用变量fp
			fp=fopen("Fatiguedate.txt","ab");
			smenu=temq;
			//	printf("%s",temq);
		    fprintf(fp,"\r\nUser:%s times(<average):%d ",smenu,numberdetect);
			printf("\nnumberdetect=%d\n",numberdetect);
			printf("对不起，你已经疲倦了，为了保证安全，请及时刹车！！！\n");
            emit th->warnningSignal();
            system("aplay /home/pi/Qt-Project/warnning.wav");
			menu1=0;
			//PlaySound("ALARM.wav", NULL, SND_FILENAME | SND_ASYNC);
			time_t rawtime; 
			struct tm * timeinfo; 
			time ( &rawtime ); 
			timeinfo = localtime ( &rawtime ); 
			printf ( "\007The current date/time is: %s", asctime (timeinfo) ); 
            fprintf ( fp,"\r\nThe current date/time is: %s", asctime (timeinfo) );
            fclose(fp);
			flag=1;
			// break;	
		}
	   else
	   {
		 numberdetect=0;
		 second_count=0;
		 cout << endl;
	   }
	}

}

void insertdata(char *s,float m)  //*s: username-用户名  m:mmenu-初始化开合度
{
	char p[12];
	float y;
	FILE *fp;
	int flag00 = 0;
	
	if ( NULL == (fp=fopen("username.txt","rb+")))
	{
		printf("\n不能打开文件。\n退出程序。\n");
		exit(1);
	}
	while(fp)
	{
		if(feof(fp))break;
		fscanf(fp,"%s,%f",p,&y);
		if(strcmp(p,s)==0)
		{
			flag00=1;
			printf("\n您已经注册过了，请不要重复注册！\n");
		}
	}
	
	if(flag00==0)
	{
		fseek(fp,0L,SEEK_CUR); //读写切换
	//	printf("%s",p);
		fprintf(fp,"\r\n%s %f",s,m);
		fclose(fp);
		printf("add success!  \n\n\n");
	}
	fclose(fp);

}

/* 初始化一个队列 */  
void initialQ( int *front, int *rear )
{  
    *front = -1;  
    *rear = -1;  
}  

/* 测试队列是否为空 */  
int isEmpty( int front, int rear )
{  
    return front == rear;  
}  

/* 队列的插入，入队 */  
int addQ( int myQueue[  ], int *rear, int item )
{  
    if( *rear == M-1 )  
        return 0;       /* 队列已满，插入失败，返回0 */  
    else{  
        myQueue[ ++( *rear ) ] = item;  
        return 1;         /* 队列未满，插入成功，返回1 */  
    }  
}  

