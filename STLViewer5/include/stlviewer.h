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
<<<<<<< HEAD
#include <QHBoxLayout>
#include <QPushButton>
#include <vtkLightActor.h>
#include <QLabel>
=======
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>

>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088

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
<<<<<<< HEAD
=======
    QSlider* m_LightSlider;
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
    QPushButton* m_Cutbutton;
    QPushButton* m_Openbutton;
    QPushButton* m_Colorbutton;
    QPushButton* m_LightButton;
    QPushButton* m_Sliderbutton; //sliderbutton
    QPushButton* m_AmbientPushButton;
    QPushButton* m_DiffusePushButton;
    QPushButton* m_SpecularPushButton;
    QPushButton* m_SpotPushButton;

<<<<<<< HEAD
    QPushButton* m_LightXMoveButton;
    QPushButton* m_LightYMoveButton;
    QPushButton* m_LightZMoveButton;
    QPushButton* m_LightResetButton;

  //  QHBoxLayout* m_SettingButtonLayout;

    QHBoxLayout* m_Hlayout;
    QHBoxLayout* m_HlayoutLight;
    QHBoxLayout* m_HAmLightSliderLayout;
    QHBoxLayout* m_HDiLightSliderLayout;
    QHBoxLayout* m_HSpLightSliderLayout;
    QVBoxLayout* m_Vlayout;
    QVBoxLayout* m_VlayoutLightSlider;
    QWidget* w;
    QWidget* wLight;
    QWidget* m_WLightSlider;
    

    CustomVTKWidget* m_customVTKWidget;

    QSlider* m_AmbientLightSlider; //AmbientLight
    QSlider* m_DiffuseLightSlider; // DiffuseLight
    QSlider* m_SpecularLightSlider; // SpecularLight

=======
    QHBoxLayout* m_Hlayout;
    QHBoxLayout* m_HlayoutLight;
    QVBoxLayout* m_Vlayout;
    QWidget* w;
    QWidget* wLight;

    CustomVTKWidget* m_customVTKWidget;

>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
    vtkSmartPointer<vtkActor> mActor;
    vtkSmartPointer<vtkLight> m_SpotLight;
    vtkSmartPointer<vtkNamedColors> mcolors;
    QColorDialog* mColorDialog; 
<<<<<<< HEAD
    vtkSmartPointer<vtkLight> mLight;
    vtkSmartPointer<vtkRenderer> m_Renderer;
    vtkSmartPointer<vtkRenderWindow>m_RenderWindow;
    vtkSmartPointer<QVTKInteractor>m_InteractorStyle;
    vtkSmartPointer<QVTKInteractor>m_Interactor;
    vtkSmartPointer<vtkLightActor> m_LightActor;
=======

    vtkSmartPointer<vtkLight> mLight;
    vtkSmartPointer<vtkRenderer> m_Renderer;
    vtkSmartPointer<vtkRenderWindow>m_RenderWindow;
    vtkSmartPointer<QVTKInteractor>m_Interactor;
//signals:
//    void sendButtonEmit();
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088

private slots:
    void on_pushButton_clicked();
    void ClickedOpen();
    void SetColor(QColor);                          // Actor Color Change
    void SetOpacity(int);                           // Acotr Opacity Change
    void cliekedLightButton();
<<<<<<< HEAD
    void on_AmbientButton_clicked();
    void on_DiffusetButton_clicked();
    void on_SpotPushButton_clicked();
    void on_SpecularPushButton_clicked();
    void SetLightAmbientChange(int);
    void SetLightDiffuseChange(int);
    void SetLightSpecularChange(int);
    void SetLigntXMove();
    void SetLightYMove();
    void SetLightZMove();
    void SetResetLight();
=======
    void on_AmbientButton_clicked();                // Ambuent Light;
    void on_DiffusetButton_clicked();               // Diffuset Light;
    void on_SpotPushButton_clicked();               // Spot Light;          
    void on_SpecularPushButton_clicked();           // Specular Light;
    void SetLightChange();
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
};

#endif // STLVIEWER_H
