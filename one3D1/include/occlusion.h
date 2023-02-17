#ifndef OCCLUSION_H
#define OCCLUSION_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Occlusion; }
QT_END_NAMESPACE

class Occlusion : public QWidget
{
    Q_OBJECT

public:
    Occlusion(QWidget *parent = nullptr);
    ~Occlusion();

private slots:
    void on_AmbientRadiusSlide_valueChanged(int value);

    void on_AmbientBiasSlider_valueChanged(int value);

    void on_AmbientLernelSlider_valueChanged(int value);

    void on_AmbientBlurSlider_valueChanged(int value);

private:
    Ui::Occlusion *ui;
};
#endif // OCCLUSION_H
