#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>


#include "cutform.h"
#include "lightwidgetform.h"
#include "shadingform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    CutForm *mCutform;
    LightWidgetForm *lightform;
    ShadingForm *shadingform;

private slots:

void on_CuttoolButton_clicked();
void on_FillingtoolButton_clicked();
void on_OpacitytoolButton_clicked();
void on_LighttoolButton_clicked();
void on_ShadingtoolButton_clicked();
void on_ColortoolButton_clicked();
void on_OpentoolButton_clicked();

void on_SavetoolButton_clicked();
};
#endif // WIDGET_H
