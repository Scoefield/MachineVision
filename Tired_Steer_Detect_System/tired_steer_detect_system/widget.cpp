#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include <iostream>
#include <QMessageBox>
#include <QIcon>
#include <opencv2/opencv.hpp>
#include "tired_steer_detect_system.h"
#include <time.h>

extern "C" {
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
}

using namespace cv;
using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //ui->label_image2->setPixmap(QPixmap("/home/pi/Qt-Project/line.png"));
    QIcon icon;
    icon.addFile(tr("/home/pi/Qt-Project/reset.png"));
    ui->pushButton_reset->setIcon(icon);

    th = new TiredSteerDetectSystemTh();
    connect(th, SIGNAL(freshMainVideo(QImage)), this, SLOT(freshMainVideoSlots(QImage)));
    connect(th, SIGNAL(freshLeftEyeVideo(QImage)), this, SLOT(freshLeftEyeVideoSlots(QImage)));
    connect(th, SIGNAL(freshRightEyeVideo(QImage)), this, SLOT(freshRightEyeVideoSlots(QImage)));
    connect(th, SIGNAL(freshLeftEyeBiVideo(QImage)), this, SLOT(freshLeftEyeBiVideoSlots(QImage)));
    connect(th, SIGNAL(freshRightEyeBiVideo(QImage)), this, SLOT(freshRightEyeBiVideoSlots(QImage)));
    connect(th, SIGNAL(showTheInitedDialog(QString)), this, SLOT(showTheInitedDialogSlots(QString)));
    connect(th, SIGNAL(freshCustomPlot(double)), this, SLOT(freshCustomPlotSlots(double)));
    connect(th, SIGNAL(freshTableWidget(double, double)), this, SLOT(freshTableWidgetSlots(double, double)));
    connect(th, SIGNAL(warnningSignal(void)), this, SLOT(warnningSignalSlots(void)));

    X.resize(100);
    Y.resize(100);
    // create plot (from quadratic plot example):
    for (int i=0; i<100; ++i)
    {
      X[i] = i;
      Y[i] = 0;
    }
    //customPlot.addGraph();
    //customPlot.graph(0)->setData(x, y);
    //customPlot.xAxis->setLabel("x");
    //customPlot.yAxis->setLabel("y");
    //customPlot.rescaleAxes();
    ui->widgetPlot->addGraph();
    ui->widgetPlot->graph(0)->setData(X, Y);
    ui->widgetPlot->xAxis->setRange(0,100);
    ui->widgetPlot->yAxis->setRange(0, 25);
    ui->widgetPlot->xAxis->setLabel("time");
    ui->widgetPlot->yAxis->setLabel("height");
    //ui->widgetPlot->rescaleAxes();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::freshMainVideoSlots(QImage image)
{
    ui->label_image->clear();
    ui->label_image->setPixmap(QPixmap::fromImage(image)); 
    //ui->label_image->resize(ui->label_image->pixmap()->size());
}

void Widget::freshLeftEyeVideoSlots(QImage image)
{
    ui->label_image_left_eye->clear();
    ui->label_image_left_eye->setPixmap(QPixmap::fromImage(image));
    //ui->label_image_left_eye->resize(ui->label_image_left_eye->pixmap()->size());
}

void Widget::freshRightEyeVideoSlots(QImage image)
{
    ui->label_image_right_eye->clear();
    ui->label_image_right_eye->setPixmap(QPixmap::fromImage(image));
}

void Widget::freshLeftEyeBiVideoSlots(QImage image)
{
    ui->label_image_left_eye_bi->clear();
    ui->label_image_left_eye_bi->setPixmap(QPixmap::fromImage(image));
}

void Widget::freshRightEyeBiVideoSlots(QImage image)
{
    ui->label_image_right_eye_bi->clear();
    ui->label_image_right_eye_bi->setPixmap(QPixmap::fromImage(image));
    //ui->label_image_right_eye_bi->resize(ui->label_image_right_eye_bi->pixmap()->size());
}

void Widget::on_openPushButton_clicked()
{
    //QMessageBox::critical(this, "Warnning！", "The cam is on going!", QMessageBox::Yes);
    th->start();
    QMessageBox::information(this, "Prompt！", "Please click the [Eye Recog] button to init!", QMessageBox::Yes);
}

void Widget::on_closePushButton_clicked()
{
    QMessageBox::information(this, "Hello！", "hahaha!", QMessageBox::Yes);
}

void Widget::on_analysisPushButton_clicked()
{
    QMessageBox::information(this, "Hello！", "hahahaha!", QMessageBox::Yes);
}

void Widget::on_savePushButton_clicked()
{
    QMessageBox::information(this, "Hello！", "hahahahaha!", QMessageBox::Yes);
}

void Widget::freshCustomPlotSlots(double height)
{
   Y.pop_front();
   Y.push_back(height);
   ui->widgetPlot->graph(0)->setData(X, Y);
   ui->widgetPlot->replot();
   cout << "The Slot height: " << height << endl;
}

int myIndex = 0;
void Widget::freshTableWidgetSlots(double detectHigh, double detectCompare)
{
    if (myIndex > 9)
        myIndex = 0;
    //QString date = QString(asctime(timenow));

    QTime time = QTime();
    time = QTime::currentTime();
    ui->tableWidget->setItem(myIndex, 0, new QTableWidgetItem(QString::number(time.hour()) + ":" + QString::number(time.minute()) + ":" + QString::number(time.second())));
    ui->tableWidget->setItem(myIndex, 1, new QTableWidgetItem(QString::number(detectHigh)));
    ui->tableWidget->setItem(myIndex, 2, new QTableWidgetItem("100"));
    ui->tableWidget->setItem(myIndex, 3, new QTableWidgetItem(QString::number(detectCompare)));

    ui->lineEdit_Perclos->setText(QString::number(detectCompare));
    ui->lineEdit_Alarm->setText("None Prompt");

    myIndex++;
}

void Widget::warnningSignalSlots(void)
{
    ui->lineEdit_FatigueStatus->setText(QString("Fatigue"));
    ui->lineEdit_Alarm->setText(QString("Voice Prompt"));
}

void Widget::on_facePushButton_clicked()
{
    QMessageBox::information(this, "Hello！", "hahahahahaha!", QMessageBox::Yes);
}

void Widget::showTheInitedDialogSlots(QString s)
{
    QMessageBox::information(this, "Prompt！", s, QMessageBox::Yes);
}

extern bool m_debug;
void Widget::on_eyePushButton_clicked()
{
    int ret = QMessageBox::information(this, "Prompt！", "Now at the Initialized State, Please look at the camera!", QMessageBox::Yes);
    if (ret == QMessageBox::Yes)
    {
        m_debug = !m_debug;
    }
    //QMessageBox::information(this, "Hello！", "OK!", QMessageBox::Yes);
}


void Widget::on_pushButton_reset_clicked()
{
    int ret = QMessageBox::information(this, "Prompt！", "Please wait for some time to return to the main interface!", QMessageBox::Yes);
    if (ret == QMessageBox::Yes)
    {
        system("sudo shutdown -r now");
    }
}
