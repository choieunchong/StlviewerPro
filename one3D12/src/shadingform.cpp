#include "shadingform.h"
#include "ui_shadingform.h"

ShadingForm::ShadingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShadingForm)
{
    ui->setupUi(this);
    connect(ui->FlattoolButton, &QToolButton::clicked, this, [this]() {emit flatShading(); });
    connect(ui->GouraudtoolButton, &QToolButton::clicked, this, [this]() {emit gouraudShading(); });
    connect(ui->PhongtoolButton, &QToolButton::clicked, this, [this]() {emit phongShading(); });
    connect(ui->TexturetoolButton, &QToolButton::clicked, this, [this]() {emit textureShading(); });
}

ShadingForm::~ShadingForm()
{
    delete ui;
}
