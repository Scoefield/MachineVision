#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QVector>
#include "tired_steer_detect_system.h"
#include "qcustomplot.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    TiredSteerDetectSystemTh *th;
    QVector<double> X;  //坐标轴
    QVector<double> Y;
    //bool *debug;    //这个是原先窗口上的debug按钮，点击debug按钮后，这里赋值为true

private slots:
    void freshMainVideoSlots(QImage);
    void freshLeftEyeVideoSlots(QImage);
    void freshRightEyeVideoSlots(QImage);
    void freshLeftEyeBiVideoSlots(QImage);
    void freshRightEyeBiVideoSlots(QImage);
    void showTheInitedDialogSlots(QString);
    void freshCustomPlotSlots(double);
    void freshTableWidgetSlots(double, double);
    void warnningSignalSlots(void);

    void on_openPushButton_clicked();
    void on_closePushButton_clicked();
    void on_analysisPushButton_clicked();
    void on_savePushButton_clicked();
    void on_facePushButton_clicked();
    void on_eyePushButton_clicked();
    void on_pushButton_reset_clicked();
};


#endif // WIDGET_H
