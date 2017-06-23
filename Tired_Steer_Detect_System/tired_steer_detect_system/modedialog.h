#ifndef MODEDIALOG_H
#define MODEDIALOG_H

#include <QWidget>

namespace Ui {
class ModeDialog;
}

class ModeDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ModeDialog(QWidget *parent = 0);
    ~ModeDialog();

private slots:
    void on_pushButtonEyeHightMode_clicked();

    void on_pushButtonEyeAreaMode_clicked();

private:
    Ui::ModeDialog *ui;
};

#endif // MODEDIALOG_H
