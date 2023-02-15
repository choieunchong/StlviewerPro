#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->openGLWidget->showFullScreen();

    mCutform = new CutForm(0);
    lightform = new LightWidgetForm(0);
    shadingform = new ShadingForm(0);

    connect(ui->CuttoolButton, SIGNAL(clicked()), this,SLOT(on_CuttoolButton_clicked()));
    connect(ui->FillingtoolButton,SIGNAL(clicked()), this,SLOT(on_FillingtoolButton_clicked()));
    connect(ui->OpacitytoolButton, SIGNAL(clicked()), this,SLOT(on_OpacitytoolButton_clicked()));
    connect(ui->LighttoolButton, SIGNAL(clicked()), this,SLOT(on_LighttoolButton_clicked()));
    connect(ui->ShadingtoolButton, SIGNAL(clicked()), this,SLOT(on_ShadingtoolButton_clicked()));
    connect(ui->ColortoolButton, SIGNAL(clicked()), this,SLOT(on_ColortoolButton_clicked()));
    connect(ui->ColortoolButton, SIGNAL(clicked()), this,SLOT(on_OpentoolButton_clicked()));
    connect(ui->ColortoolButton, SIGNAL(clicked()), this,SLOT(on_SavetoolButton_clicked()));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_CuttoolButton_clicked()
{
    mCutform->show();
    mCutform->setWindowFlag(Qt::WindowStaysOnTopHint);
}


void Widget::on_FillingtoolButton_clicked()
{

}


void Widget::on_OpacitytoolButton_clicked()
{

}


void Widget::on_LighttoolButton_clicked()
{
    int width = ui->openGLWidget->sizeHint().width();
    int height =ui->openGLWidget->sizeHint().height();

    lightform->show();
    lightform->setWindowFlag(Qt::WindowStaysOnTopHint);
//    lightform->setGeometry(width,height,10,10);
    qDebug()<<"light" <<lightform->geometry();


}


void Widget::on_ShadingtoolButton_clicked()
{
    shadingform->show();
    shadingform->setWindowFlag(Qt::WindowStaysOnTopHint);
}


void Widget::on_ColortoolButton_clicked()
{

}


void Widget::on_OpentoolButton_clicked()
{

}


void Widget::on_SavetoolButton_clicked()
{

}

