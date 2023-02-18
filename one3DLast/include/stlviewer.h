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
#include <vtkTexture.h>
#include <vtkSTLWriter.h>
#include <QMessageBox>
#include <vtkWindowToImageFilter.h>
#include <vtkOutlineFilter.h>

#include <vtkPNGReader.h>
#include <vtkTextureMapToSphere.h>
#include <vtkPolyDataNormals.h>
#include <vtkSSAOPass.h>
#include <vtkRenderStepsPass.h>

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

    // 재질 버튼
    QPushButton* m_PhongButton;
    QPushButton* m_GouraudButton;
    QPushButton* m_FlatButton;
    // 상자 구역 설정 버튼
    QPushButton* m_BoundingBoxButton;

    // 빛의 방향 버튼
    QPushButton* m_LightXMoveButton;
    QPushButton* m_LightYMoveButton;
    QPushButton* m_LightZMoveButton;
    QPushButton* m_LightResetButton;

    QPushButton* m_TextButton;
    QPushButton* m_SaveButton;
    QPushButton* m_AmbientOcclusionButton;


    QHBoxLayout* m_Hlayout;
    QHBoxLayout* m_HlayoutLight;
    QHBoxLayout* m_HAmLightSliderLayout;
    QHBoxLayout* m_HDiLightSliderLayout;
    QHBoxLayout* m_HSpLightSliderLayout;
    QVBoxLayout* m_Vlayout;
    QVBoxLayout* m_VlayoutLightSlider;
    QVBoxLayout* m_VlayoutAmbientOcclusion;
    QHBoxLayout* m_HToolLayout;
    QHBoxLayout* m_HmaterialLayout;
    QHBoxLayout* m_ConeAngleLayout;

    QWidget* w;
    QWidget* wLight;
    QWidget* m_WLightSlider;
    QWidget* mWTool;
    QWidget* mWMaterial;
    QWidget* m_WAmbientSlider;

    CustomVTKWidget* m_customVTKWidget;
    QSlider* m_AmbientLightSlider; //AmbientLight
    QSlider* m_DiffuseLightSlider; // DiffuseLight
    QSlider* m_SpecularLightSlider; // SpecularLight
    QSlider* m_ConeAngle;  // ConeAngle;

    QSlider* m_AmbientRadiusSlider;
    QSlider* m_AmbientBiasSlider;
    QSlider* m_AmbientKernelSizeSlider;
    QSlider* m_AmbientBlurSlider;

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

    vtkSmartPointer<vtkSSAOPass> ssaoPass;

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
    int SaveFile();            // STL 파일을 저장한다.
    void BoundingBox();        // 엑터의 사각형을 테두리를 만든다.
    void SetPhongChange();     // 퐁 재질로 변경
    void SetGouraudChange();   // 고러드 재질로 변경
    void SetFlatChange();      // Flat 으로 재질 변경
    void SetConeAngleChange(int); // cone 의 각도를 설정 한다.
    void SetvtkAmbientOcclusion(); // 실제 모델과 비슷하게 만들기 위한 명암 함수
    void clieckedTextureButton();
    void SetAmbientRadiusChange(int);
    void SetAmbientBiasChange(int);
    void SetAmbientKernelSizeChange(int);
    void SetAmbientBlurChange(int);

  //  void MoveButton(); // 
};

#endif // STLVIEWER_H
