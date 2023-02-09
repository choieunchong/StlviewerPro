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
#include <QHBoxLayout>
#include <QPushButton>
#include <vtkLightActor.h>
#include <QLabel>
#include <vtkSTLReader.h>
#include <vtkTexture.h>
#include <vtkSTLWriter.h>
#include <QMessageBox>
#include <vtkWindowToImageFilter.h>
#include <vtkOutlineFilter.h>
#include <vtkTransform.h> // move �̺�Ʈ ���� �ؾ� �� ��


#include <vtkPNGReader.h>
#include <vtkTransformTextureCoords.h>


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

    // ���� ��ư
    QPushButton* m_PhongButton;
    QPushButton* m_GouraudButton;

    // ���� ���� ���� ��ư
    QPushButton* m_BoundingBoxButton;

    QPushButton* m_LightXMoveButton;
    QPushButton* m_LightYMoveButton;
    QPushButton* m_LightZMoveButton;
    QPushButton* m_LightResetButton;

    QPushButton* m_TextButton;
    QPushButton* m_SaveButton;
  //  QHBoxLayout* m_SettingButtonLayout;

    QHBoxLayout* m_Hlayout;
    QHBoxLayout* m_HlayoutLight;
    QHBoxLayout* m_HAmLightSliderLayout;
    QHBoxLayout* m_HDiLightSliderLayout;
    QHBoxLayout* m_HSpLightSliderLayout;
    QVBoxLayout* m_Vlayout;
    QVBoxLayout* m_VlayoutLightSlider;
    QHBoxLayout* m_HToolLayout;
    QHBoxLayout* m_HmaterialLayout;
    QHBoxLayout* m_ConeAngleLayout;

    QWidget* w;
    QWidget* wLight;
    QWidget* m_WLightSlider;
    QWidget* mWTool;
    QWidget* mWMaterial;

    CustomVTKWidget* m_customVTKWidget;
    QSlider* m_AmbientLightSlider; //AmbientLight
    QSlider* m_DiffuseLightSlider; // DiffuseLight
    QSlider* m_SpecularLightSlider; // SpecularLight
    QSlider* m_ConeAngle;  // ConeAngle;

    vtkSmartPointer<vtkActor> mActor;
    vtkSmartPointer<vtkLight> m_SpotLight;
    vtkSmartPointer<vtkNamedColors> mcolors;
    QColorDialog* mColorDialog; 
    vtkSmartPointer<vtkLight> mLight;
    vtkSmartPointer<vtkRenderer> m_Renderer;
    vtkSmartPointer<vtkRenderWindow>m_RenderWindow;
    vtkSmartPointer<QVTKInteractor>m_InteractorStyle;
    vtkSmartPointer<QVTKInteractor>m_Interactor;
    vtkSmartPointer<vtkLightActor> m_LightActor;
    vtkSmartPointer<vtkSTLReader> m_STLReader;
    vtkSmartPointer<vtkPolyData> m_PolyData;

    //vtkSmartPointer <vtkTransform> m_transform;
    //vtkSmartPointer<vtkCamera> m_Camera;

    vtkSmartPointer<vtkProperty> m_OriginProp;
    vtkSmartPointer<vtkActor> m_OutlineActor;
    vtkSmartPointer<vtkPolyDataMapper> mMapper;

private slots:
    void on_pushButton_clicked();
    void ClickedOpen();
    void SetColor(QColor);                          // Actor Color Change
    void SetOpacity(int);                           // Acotr Opacity Change
    void cliekedLightButton();
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
    void SetTexture();
    int SaveFile();            // STL ������ �����Ѵ�.
    void BoundingBox();        // ������ �簢���� �׵θ��� �����.
    void SetPhongChange();     // �� ������ ����
    void SetGouraudChange();   // ���� ������ ����
    void SetConeAngleChange(int); // cone �� ������ ���� �Ѵ�.
};

#endif // STLVIEWER_H
