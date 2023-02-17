#include "occlusion.h"
#include "ui_occlusion.h"

Occlusion::Occlusion(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Occlusion)
{
    ui->setupUi(this);
}

Occlusion::~Occlusion()
{
    delete ui;
}


void Occlusion::on_AmbientRadiusSlide_valueChanged(int value)
{

}


void Occlusion::on_AmbientBiasSlider_valueChanged(int value)
{

}


void Occlusion::on_AmbientLernelSlider_valueChanged(int value)
{

}


void Occlusion::on_AmbientBlurSlider_valueChanged(int value)
{

}

