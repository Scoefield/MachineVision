#include "modedialog.h"
#include "ui_modedialog.h"
#include "widget.h"

extern int menuMode;

ModeDialog::ModeDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModeDialog)
{
    ui->setupUi(this);
}

ModeDialog::~ModeDialog()
{
    delete ui;
}

void ModeDialog::on_pushButtonEyeHightMode_clicked()
{
    this->setHidden(true);
    menuMode = 1;    //模式1
    Widget *w = new Widget();
    w->show();
}

void ModeDialog::on_pushButtonEyeAreaMode_clicked()
{
    this->setHidden(true);
    menuMode = 2;    //模式1
    Widget *w = new Widget();
    w->show();
}
