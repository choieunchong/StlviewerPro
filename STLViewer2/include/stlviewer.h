#ifndef STLVIEWER_H
#define STLVIEWER_H

#include <QMainWindow>
#include <vtkSTLReader.h>
#include <vtkMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <QColorDialog.h>
#include "CustomVTKWidget.h"
#include <vtkPolyData.h>
#include <vtkAxesActor.h>
#include <vtkTransform.h>
#include <QSlider>
#include <QResizeEvent>
#include <QLabel>
#include <QFileDialog>
#include <vtkLight.h>
#include <vtkCamera.h>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class STLViewer; }
QT_END_NAMESPACE

class STLViewer : public QWidget
{
    Q_OBJECT

public:
    explicit STLViewer(QWidget *parent = nullptr);
    ~STLViewer();

protected:
    virtual void resizeEvent(QResizeEvent* event) override;
    //void sendLightButton(QPushButton* button);
private:
    Ui::STLViewer* ui;
    QSlider* m_Slider;
    QPushButton* m_Cutbutton;
    QPushButton* m_Openbutton;
    QPushButton* m_Colorbutton;
    QPushButton* m_LightButton;
    QPushButton* m_Sliderbutton; //sliderbutton
    QPushButton* m_AmbientPushButton;
    QPushButton* m_DiffusePushButton;
    QPushButton* m_SpecularPushButton;
    QPushButton* m_SpotPushButton;

    QHBoxLayout* m_Hlayout;
    QHBoxLayout* m_HlayoutLight;
    QVBoxLayout* m_Vlayout;
    QWidget* w;
    QWidget* wLight;

    CustomVTKWidget* m_customVTKWidget;

    vtkSmartPointer<vtkActor> mActor;
    vtkSmartPointer<vtkLight> m_SpotLight;
    vtkSmartPointer<vtkNamedColors> mcolors;
    QColorDialog* mColorDialog; 
    vtkSmartPointer<vtkLight> mLight;
    vtkSmartPointer<vtkRenderer> m_Renderer;
    vtkSmartPointer<vtkRenderWindow>m_RenderWindow;
    vtkSmartPointer<QVTKInteractor>m_Interactor;
//signals:
//    void sendButtonEmit();

private slots:
    void on_pushButton_clicked();
    void ClickedOpen();
    void SetColor(QColor);                          // Actor Color Change
    void SetOpacity(int);                           // Acotr Opacity Change
    void cliekedLightButton();
    void on_AmbientButton_clicked();                // Ambuent Light;
    void on_DiffusetButton_clicked();               // Diffuset Light;
    void on_SpotPushButton_clicked();               // Spot Light;          
    void on_SpecularPushButton_clicked();           // Specular Light;

};

#endif // STLVIEWER_H
