#ifndef TIRED_STEER_DETECT_SYSTEM_H
#define TIRED_STEER_DETECT_SYSTEM_H

#include <QThread>
#include <QWidget>
#include <QString>
/*
 * 该线程负责处理一切，并将所有的输出信息由发送信号的方式通知主线程刷新UI
 */
class TiredSteerDetectSystemTh : public QThread
{
    Q_OBJECT
protected:
    void run();
signals:
    void freshMainVideo(QImage);
    void freshLeftEyeVideo(QImage);
    void freshRightEyeVideo(QImage);
    void freshLeftEyeBiVideo(QImage);
    void freshRightEyeBiVideo(QImage);
    void showTheInitedDialog(QString);
    void freshCustomPlot(double);
    void freshTableWidget(double, double);
    void warnningSignal(void);
};

#endif // TIRED_STEER_DETECT_SYSTEM_H
