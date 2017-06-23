#include "widget.h"
#include <QApplication>
#include "modedialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ModeDialog md;

    md.setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap("/home/pi/Qt-Project/background.jpg");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    md.setPalette(palette);

    md.show();         //显示提示用户选择对话框，等待用户选择模式！

    return a.exec();
}
