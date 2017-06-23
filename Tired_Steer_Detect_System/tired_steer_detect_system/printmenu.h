#ifndef  __PRINTMENU__
#define  __PRINTMENU__

#include <stdio.h>
#include <iostream>
#include <vector>

// Include OpenCV's C++ Interface
#include "opencv2/opencv.hpp"
#include "tired_steer_detect_system.h"


using namespace cv;
using namespace std;


//-------------------- 函数声明区 -------------------
void printmenu();
void printmenu1();
void printmenu2();
float search(char *s);
void printmenu_deal(Mat leyer, Mat reyer, TiredSteerDetectSystemTh *th);
double AreaPercent( Mat leyer, Mat reyer);
void insertdata(char *s,float m);
int eyesHigh(Mat topLeftOfFace_thresh, Mat toprightOfFace_thresh, TiredSteerDetectSystemTh *th);

void initialQ( int *front, int *rear );
int isEmpty( int front, int rear );
int addQ( int myQueue[  ], int *rear, int item );
void imageDuilie(int frame_high, TiredSteerDetectSystemTh *th);



#endif
