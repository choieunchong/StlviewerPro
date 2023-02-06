<<<<<<< HEAD
=======
#pragma once
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
#include "stlviewer.h"
#include "ui_stlviewer.h"
#include "CustomInteractorStyle.h"
#include <QDebug>
<<<<<<< HEAD
#include <QDebug>
=======
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
#include <TriMesh.h>
#include <algorithm> 


STLViewer::STLViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::STLViewer)
{ 
    ui->setupUi(this);

    //m_customVTKWidget = new CustomVTKWidget(this);
    mLight = vtkSmartPointer<vtkLight>::New();
    w = new QWidget(this);
    wLight = new QWidget(this);
<<<<<<< HEAD
    m_WLightSlider = new QWidget(this);
=======
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088

    m_Slider = new QSlider(Qt::Horizontal, this);
    m_Slider->setRange(0,100); 
    m_Slider->setMaximumSize(QSize(200, 50));
    m_Cutbutton = new QPushButton("Cut", this);
    m_Openbutton = new QPushButton("Open", this);
    m_Colorbutton = new QPushButton("Color", this);
    m_LightButton = new QPushButton("Light", this);

<<<<<<< HEAD
    m_LightXMoveButton = new QPushButton("XLight", this);
    m_LightYMoveButton = new QPushButton("YLight", this);
    m_LightZMoveButton = new QPushButton("ZLight", this);

    m_LightResetButton = new QPushButton("ResetLight", this);

=======
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
    m_AmbientPushButton = new QPushButton("AmbientButton", this);
    m_DiffusePushButton = new QPushButton("DiffuseButton", this);
    m_SpotPushButton = new QPushButton("SpotButton", this);
    m_SpecularPushButton = new QPushButton("SpecularButton", this);
    mColorDialog = new QColorDialog();
<<<<<<< HEAD

    QLabel* AmbientLabel = new QLabel("AmbientLight");
    AmbientLabel->setStyleSheet("QLabel {color : #fff;}");
    QLabel* DiffuseLabel = new QLabel("DiffuseLight");
    DiffuseLabel->setStyleSheet("QLabel {color : #fff;}");
    QLabel* SpecularLabel = new QLabel("SpecualLight");
    SpecularLabel->setStyleSheet("QLabel {color : #fff;}");

    m_HAmLightSliderLayout = new QHBoxLayout();
    m_HDiLightSliderLayout = new QHBoxLayout();
    m_HSpLightSliderLayout = new QHBoxLayout();
   // m_SettingButtonLayout = new QHBoxLayout();

    m_AmbientLightSlider = new QSlider(Qt::Horizontal, this);
    m_AmbientLightSlider->setRange(0, 100);
    m_AmbientLightSlider->setMaximumSize(QSize(200, 50));

    m_DiffuseLightSlider = new QSlider(Qt::Horizontal, this);
    m_DiffuseLightSlider->setRange(0, 100);
    m_DiffuseLightSlider->setMaximumSize(QSize(200, 50));

    m_SpecularLightSlider = new QSlider(Qt::Horizontal, this);
    m_SpecularLightSlider->setRange(0, 100);
    m_SpecularLightSlider->setMaximumSize(QSize(200, 50));

    m_HAmLightSliderLayout->addWidget(AmbientLabel);
    m_HAmLightSliderLayout->addWidget(m_AmbientLightSlider);

    m_HDiLightSliderLayout->addWidget(DiffuseLabel);
    m_HDiLightSliderLayout->addWidget(m_DiffuseLightSlider);

    m_HSpLightSliderLayout->addWidget(SpecularLabel);
    m_HSpLightSliderLayout->addWidget(m_SpecularLightSlider);
=======
    m_LightSlider = new QSlider(Qt::Horizontal, this);
    m_LightSlider->setRange(0, 100);
    m_LightSlider->setMaximumSize(QSize(200, 50));
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088

    //m_Colorbutton->setGeometry(0, 0, 100, 100);
    //m_Openbutton->setGeometry(0, 0, 100, 100);
    //m_Light->setGeometry(0, 0, 100, 100);
    //m_Cutbutton->setGeometry(0, 0, 100, 100);
<<<<<<< HEAD

    m_Renderer = vtkSmartPointer<vtkRenderer>::New();
    m_RenderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    mcolors = vtkSmartPointer<vtkNamedColors>::New();
    m_SpotLight = vtkSmartPointer<vtkLight>::New();
    m_Interactor = vtkSmartPointer<QVTKInteractor>::New();
    m_InteractorStyle = vtkSmartPointer<QVTKInteractor>::New();
    m_LightActor = vtkSmartPointer<vtkLightActor>::New();
    m_Renderer = ui->openGLWidget->GetInteractor()->GetInteractorStyle()->GetCurrentRenderer();
    m_RenderWindow = ui->openGLWidget->GetRenderWindow();
    m_Interactor = ui->openGLWidget->GetInteractor();


=======
    m_Renderer = vtkSmartPointer<vtkRenderer>::New();
    m_RenderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    m_Renderer = ui->openGLWidget->GetInteractor()->GetInteractorStyle()->GetCurrentRenderer();
    m_RenderWindow = ui->openGLWidget->GetRenderWindow();
    mcolors = vtkSmartPointer<vtkNamedColors>::New();
    m_SpotLight = vtkSmartPointer<vtkLight>::New();
    m_Interactor = vtkSmartPointer<QVTKInteractor>::New();
    m_Interactor = ui->openGLWidget->GetInteractor();

>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
    m_Sliderbutton = new QPushButton("Opacity", this);
    connect(m_Sliderbutton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(m_Openbutton, SIGNAL(clicked()), this, SLOT(ClickedOpen()));
    connect(m_Colorbutton, &QPushButton::clicked, this, [this](bool) { mColorDialog->show(); });
    connect(mColorDialog, SIGNAL(currentColorChanged(QColor)), this, SLOT(SetColor(QColor)));
    connect(m_Slider, SIGNAL(valueChanged(int)), this, SLOT(SetOpacity(int)));
<<<<<<< HEAD

    connect(m_LightButton, SIGNAL(clicked()), this, SLOT(cliekedLightButton()));
    connect(m_AmbientPushButton, SIGNAL(clicked()), this, SLOT(on_AmbientButton_clicked())); //Ambient
    connect(m_DiffusePushButton, SIGNAL(clicked()), this, SLOT(on_DiffusetButton_clicked())); //Diffuse
    connect(m_SpecularPushButton, SIGNAL(clicked()), this, SLOT(on_SpecularPushButton_clicked()));
    connect(m_SpotPushButton, SIGNAL(clicked()), this, SLOT(on_SpotPushButton_clicked()));// Spot

    connect(m_AmbientLightSlider, SIGNAL(valueChanged(int)), this, SLOT(SetLightAmbientChange(int)));
    connect(m_DiffuseLightSlider, SIGNAL(valueChanged(int)), this, SLOT(SetLightDiffuseChange(int)));
    connect(m_SpecularLightSlider, SIGNAL(valueChanged(int)), this, SLOT(SetLightSpecularChange(int)));

    connect(m_LightXMoveButton, SIGNAL(clicked()), this, SLOT(SetLigntXMove()));
    connect(m_LightYMoveButton, SIGNAL(clicked()), this, SLOT(SetLightYMove()));
    connect(m_LightZMoveButton, SIGNAL(clicked()), this, SLOT(SetLightZMove()));
    connect(m_LightResetButton, SIGNAL(clicked()), this, SLOT(SetResetLight()));
=======
    connect(m_LightButton, SIGNAL(clicked()), this, SLOT(cliekedLightButton())); //라이트 버튼 이 눌렀을때 그에 해당하는 버튼을 보여준다.
    connect(m_AmbientPushButton, SIGNAL(clicked()), this, SLOT(on_AmbientButton_clicked())); //Ambient 버튼 
    connect(m_DiffusePushButton, SIGNAL(clicked()), this, SLOT(on_DiffusetButton_clicked())); //Diffuse 버튼
    connect(m_SpecularPushButton, SIGNAL(clicked()), this, SLOT(on_SpecularPushButton_clicked()));
    connect(m_SpotPushButton, SIGNAL(clicked()), this, SLOT(on_SpotPushButton_clicked()));// Spot 버튼
  
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088

    m_Hlayout = new QHBoxLayout();
    m_Vlayout = new QVBoxLayout();
    m_HlayoutLight = new QHBoxLayout();
<<<<<<< HEAD
    m_VlayoutLightSlider = new QVBoxLayout();

    m_Slider->hide();

    m_VlayoutLightSlider->addLayout(m_HAmLightSliderLayout);
    m_VlayoutLightSlider->addLayout(m_HDiLightSliderLayout);
    m_VlayoutLightSlider->addLayout(m_HSpLightSliderLayout);
    m_VlayoutLightSlider->addWidget(m_LightXMoveButton);
    m_VlayoutLightSlider->addWidget(m_LightYMoveButton);
    m_VlayoutLightSlider->addWidget(m_LightZMoveButton);

    m_VlayoutLightSlider->addWidget(m_LightResetButton);

=======
    m_Slider->hide();
    m_LightSlider->hide();
    //m_layout->addWidget(m_Slider);
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
    m_Hlayout->addWidget(m_Openbutton); 
    m_Hlayout->addWidget(m_Colorbutton); 
    m_Hlayout->addWidget(m_Cutbutton); 
    m_Hlayout->addWidget(m_LightButton);
    m_Hlayout->addWidget(m_Sliderbutton); 

    m_HlayoutLight->addWidget(m_AmbientPushButton);
<<<<<<< HEAD
    m_HlayoutLight->addWidget(m_DiffusePushButton);
    m_HlayoutLight->addWidget(m_SpecularPushButton);
    m_HlayoutLight->addWidget(m_SpotPushButton);
    wLight->setLayout(m_HlayoutLight);
    
    m_WLightSlider->setLayout(m_VlayoutLightSlider);
    m_WLightSlider->hide();
    m_WLightSlider->setMinimumSize(500, 350);

    m_Vlayout->addLayout(m_Hlayout);
    m_Vlayout->addWidget(m_Slider);
    m_Vlayout->addLayout(m_HlayoutLight);
    w->setLayout(m_Vlayout);
    w->setMinimumSize(500, 100);
=======
    m_AmbientPushButton->hide();
    m_HlayoutLight->addWidget(m_DiffusePushButton);
    m_DiffusePushButton->hide();
    m_HlayoutLight->addWidget(m_SpecularPushButton);
    m_SpecularPushButton->hide();
    m_HlayoutLight->addWidget(m_SpotPushButton);
    m_SpotPushButton->hide();
   // wLight->setLayout(m_HlayoutLight);
    
    m_Vlayout->addLayout(m_Hlayout);
    m_Vlayout->addWidget(m_Slider);
    m_Vlayout->addLayout(m_HlayoutLight);
    m_Vlayout->addWidget(m_LightSlider);

    w->setLayout(m_Vlayout);
    w->setMinimumSize(500, 100);

>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
    w->setStyleSheet("QWidget::horver{"
                     "background-color:#fff;"
                     "border: 10px;}");

    wLight->setLayout(m_HlayoutLight);
<<<<<<< HEAD
    wLight->setMinimumSize(500, 100);
    wLight->hide();
=======
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
}

STLViewer::~STLViewer()
{
    delete ui;
}

void STLViewer::resizeEvent(QResizeEvent *event)
{
    int height = event->size().height();
    int width = event->size().width(); 
    w->move(width/2 - 200, 50);  
    wLight->move(width / 2 - 200, 100);
<<<<<<< HEAD
    m_WLightSlider->move(0, 100);

=======
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
}

void STLViewer::SetColor(QColor color)
{
    double r = color.toRgb().redF();
    double g = color.toRgb().greenF();
    double b = color.toRgb().blueF();
    mActor->GetProperty()->SetDiffuseColor(r, g, b);
    mActor->Modified();
    ui->openGLWidget->GetRenderWindow()->Render();
}

void STLViewer::SetOpacity(int opacity)
{
    if (mActor != NULL)
    {
        mActor->GetProperty()->SetOpacity(opacity / 100.0);
        mActor->Modified();
        ui->openGLWidget->GetRenderWindow()->Render();
    }
}

void STLViewer::cliekedLightButton()
{
<<<<<<< HEAD
        static int count = 0;

        switch (++count)
        {
        case 1:
            wLight->show();
            m_WLightSlider->show();
            break;
        default:
            count = 0;
            wLight->hide();
            m_WLightSlider->hide();
            break;
        }
    }
=======
    static int count = 0;

    switch (++count)
    {
    case 1:
        m_AmbientPushButton->show();
        m_DiffusePushButton->show();
        m_SpecularPushButton->show();
        m_SpotPushButton->show();
        m_LightSlider->show();
        break;
    default:
        count = 0;
        m_AmbientPushButton->hide();
        m_DiffusePushButton->hide();
        m_SpecularPushButton->hide();
        m_SpotPushButton->hide();
        m_LightSlider->hide();
        break;
    }
}
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088

void STLViewer:: on_pushButton_clicked()
{
    qDebug() << "11111";
    if (m_Slider->isHidden())
            m_Slider->show();
        else
            m_Slider->hide();
}

void STLViewer::ClickedOpen()
{
    qDebug("Triggered Open Button");
    std::string fileName = QFileDialog::getOpenFileName(nullptr,
        "STL Files", "/home", "STL Files (*.stl)").toStdString().c_str();

    // STL Reader
    vtkSmartPointer<vtkSTLReader> mSTLReader = vtkSmartPointer<vtkSTLReader>::New();
    mSTLReader->SetFileName(fileName.c_str());
    mSTLReader->Update();

    // Mapper
    vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
    polyData->DeepCopy(mSTLReader->GetOutput());
    vtkSmartPointer<vtkPolyDataMapper> mMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mMapper->SetInputData(polyData);

    // Actor
    mActor = vtkSmartPointer<vtkActor>::New();
    mActor->SetMapper(mMapper);

    ui->openGLWidget->AddActor(mActor);
    //m_customVTKWidget->AddActor(mActor);
    //ui->openGLWidget->GetPolyData(polyData);
    qDebug() << "Actor" << mActor;
    qDebug() << "PolyData" << polyData;
<<<<<<< HEAD
    ui->openGLWidget->GetInteractor()->GetInteractorStyle()->GetCurrentRenderer()->ResetCamera();
    ui->openGLWidget->GetRenderWindow()->Render();
}

void STLViewer::SetLightAmbientChange(int Ambient)
{
    qDebug() << "SetLightChange";
    if (mActor != NULL)
    {
        mActor->GetProperty()->SetAmbient(Ambient / 100.0);
        mActor->Modified();
        ui->openGLWidget->GetRenderWindow()->Render();
    }
}

void STLViewer::SetLightDiffuseChange(int Diffuse)
{
    qDebug() << "SetLightDiffuseChange";
    if (mActor != NULL)
    {
        mActor->GetProperty()->SetDiffuse(Diffuse / 100.0);
        mActor->Modified();
        ui->openGLWidget->GetRenderWindow()->Render();
    }
}

void STLViewer::SetLightSpecularChange(int Specular)
{
    qDebug() << "SetLightSpeclarChange";
    if (mActor != NULL)
    {
        mActor->GetProperty()->SetSpecular(Specular / 100.0);
        mActor->Modified();
        ui->openGLWidget->GetRenderWindow()->Render();
    }
}

void STLViewer::SetLigntXMove()
{
    qDebug() << "LightMove";

    mLight->SetPosition(1, 0, 0);
    mLight->SetFocalPoint(mActor->GetPosition());
    mLight->SetColor(mcolors->GetColor3d("Magenta").GetData());
    mLight->PositionalOn();
    m_Renderer->AddLight(mLight);
    mLight->SwitchOn();

    mLight->SetConeAngle(10);
    m_LightActor->SetLight(mLight);
    m_Renderer->AddViewProp(m_LightActor);
    ui->openGLWidget->GetRenderWindow()->Render();
}

void STLViewer::SetLightYMove()
{
    qDebug() << "LightMove";

    mLight->SetPosition(0, 1, 0);
    mLight->SetFocalPoint(mActor->GetPosition());
    mLight->SetColor(mcolors->GetColor3d("Magenta").GetData());
    mLight->PositionalOn();
    m_Renderer->AddLight(mLight);
    mLight->SwitchOn();

    mLight->SetConeAngle(10);
    m_LightActor->SetLight(mLight);
    m_Renderer->AddViewProp(m_LightActor);
    ui->openGLWidget->GetRenderWindow()->Render();
}

void STLViewer::SetLightZMove()
{
    qDebug() << "LightMove";

    mLight->SetPosition(0, 0, 1);
    mLight->SetFocalPoint(mActor->GetPosition());
    mLight->SetColor(mcolors->GetColor3d("Magenta").GetData());
    mLight->PositionalOn();
    m_Renderer->AddLight(mLight);
    mLight->SwitchOn();

    mLight->SetConeAngle(10);
    m_LightActor->SetLight(mLight);
    m_Renderer->AddViewProp(m_LightActor);
    ui->openGLWidget->GetRenderWindow()->Render();
=======
}
void STLViewer::SetLightChange()
{

>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
}


void STLViewer::on_AmbientButton_clicked()
{
    qDebug() << "Ambient---------------";
<<<<<<< HEAD

=======
  
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
    double ambient = 0.4;
    double diffuse = 0.4;
    double specular = 0.4;
    double spbase = 0.5;
    double spscale = 0.1;

<<<<<<< HEAD
=======

>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
    double specularpower = spbase * spscale;

    QColor color = mColorDialog->getColor();
    double r = color.toRgb().redF();
    double g = color.toRgb().greenF();
    double b = color.toRgb().blueF();

    mLight->SetLightTypeToSceneLight();
    //mLight->SetLightTypeToCameraLight();
<<<<<<< HEAD

=======
    
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
    mLight->SetAmbientColor(r, g, b);
    mActor->GetProperty()->SetAmbientColor(r, g, b);
    mActor->GetProperty()->SetAmbient(ambient);
    mActor->GetProperty()->SetDiffuse(diffuse);
    mActor->GetProperty()->SetSpecular(specular);
    mActor->GetProperty()->SetSpecularPower(specularpower);

    qDebug() << "mLight" << mLight;
    m_Renderer->AddLight(mLight);
    m_Renderer->SetAmbient(0.5, 0.5, 0.5);

    m_Renderer->Render();
    m_Interactor->Start();
<<<<<<< HEAD
    ui->openGLWidget->GetRenderWindow()->Render();
=======

>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
}

void STLViewer::on_DiffusetButton_clicked()
{
<<<<<<< HEAD
=======
    qDebug() << "Diffuse";
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
    QColor color = mColorDialog->getColor();
    double r = color.toRgb().redF();
    double g = color.toRgb().greenF();
    double b = color.toRgb().blueF();

<<<<<<< HEAD
    //mLight->SetLightTypeToSceneLight();
    mLight->SetLightTypeToCameraLight();

    //mLight->SetPosition(0, 0, 5);
    mLight->SetDiffuseColor(r, g, b);
    m_Renderer->AddLight(mLight);
    m_InteractorStyle->Start();
    ui->openGLWidget->GetRenderWindow()->Render();
=======
    mLight->SetLightTypeToSceneLight();
    mLight->SetLightTypeToCameraLight();

    mLight->SetDiffuseColor(r, g, b);
    m_Renderer->AddLight(mLight);
    m_Interactor->Start();

>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
}

void STLViewer::on_SpotPushButton_clicked()
{
    qDebug() << "SpotPushButton";
    QColor color = mColorDialog->getColor();
    double r = color.toRgb().redF();
    double g = color.toRgb().greenF();
    double b = color.toRgb().blueF();

    m_Renderer->ResetCamera();
<<<<<<< HEAD
=======

>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
    m_Renderer->GetActiveCamera()->Azimuth(40.0);
    m_Renderer->GetActiveCamera()->Elevation(30.0);

    m_SpotLight->PositionalOn();
    m_SpotLight->SetColor(r, g, b);
    m_SpotLight->SetPosition(-3.0, 10.0, -1.0);
<<<<<<< HEAD
    m_SpotLight->SetIntensity(0.5);
=======
    m_SpotLight->SetIntensity(0.7);
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088

    m_Renderer->AddLight(m_SpotLight);

    m_SpotLight->SetLightTypeToCameraLight();
<<<<<<< HEAD
    m_SpotLight->SetPosition(m_Renderer->GetActiveCamera()->GetPosition()); 
    m_SpotLight->SetFocalPoint(m_Renderer->GetActiveCamera()->GetFocalPoint()); 
=======
    m_SpotLight->SetPosition(m_Renderer->GetActiveCamera()->GetPosition()); // 조명 위치 설정
    m_SpotLight->SetFocalPoint(m_Renderer->GetActiveCamera()->GetFocalPoint()); // 비추는 지점
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088

    m_Renderer->SetBackground(mcolors->GetColor3d("RoyalBlue").GetData());
    m_Renderer->GradientBackgroundOn();

<<<<<<< HEAD
    m_InteractorStyle->Initialize();
    m_RenderWindow->Render();
    m_InteractorStyle->Start();
    ui->openGLWidget->GetRenderWindow()->Render();
=======
    m_Interactor->Initialize();
    m_RenderWindow->Render();
    m_Interactor->Start();
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
}

void STLViewer::on_SpecularPushButton_clicked()
{
    double ambient = 0.4;
    double diffuse = 0.4;
    double specular = 0.4;
    double spbase = 0.5;
<<<<<<< HEAD
    double spscale = 1.0;
=======
    double spscale = 0.1;
    
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088

    double specularpower = spbase * spscale;

    QColor color = mColorDialog->getColor();
    double r = color.toRgb().redF();
    double g = color.toRgb().greenF();
    double b = color.toRgb().blueF();

<<<<<<< HEAD
    mLight->SetPosition(0, 1.0, 1.0);
    mLight->SetConeAngle(0.3);
   // LightActor->GetConeProperty()->SetColor(r, g, b);

 //   mLight->SetLightTypeToCameraLight();
    mLight->SetPositional(true);
    mLight->SetLightTypeToSceneLight();
    mLight->SetFocalPoint(0, 0, 0);

    m_LightActor->SetLight(mLight);

=======
    mLight->SetLightTypeToSceneLight();
    //mLight->SetLightTypeToCameraLight();

    mLight->SetAmbientColor(r, g, b);
    mActor->GetProperty()->SetSpecularColor(r, g, b);
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
    mActor->GetProperty()->SetAmbient(ambient);
    mActor->GetProperty()->SetDiffuse(diffuse);
    mActor->GetProperty()->SetSpecular(specular);
    mActor->GetProperty()->SetSpecularPower(specularpower);
<<<<<<< HEAD
    mActor->GetProperty()->SetSpecularColor(r, g, b);
    
    //mActor->AddPosition(position.data());

    qDebug() << "mLight" << mLight;
    m_Renderer->AddLight(mLight);
    m_Renderer->AddViewProp(m_LightActor); 
  // ui->openGLWidget->GetInteractor()->GetInteractorStyle()->GetCurrentRenderer()->AddViewProp(LightActor);
    ui->openGLWidget->GetRenderWindow()->Render();
    m_Interactor->Start();
}

void STLViewer::SetResetLight()
{
    qDebug() << "SetResetLight";

    m_Renderer->SetBackground(mcolors->GetColor3d("white").GetData());
    ui->openGLWidget->GetRenderWindow()->Render();

}


=======

    qDebug() << "mLight" << mLight;
    m_Renderer->AddLight(mLight);
    m_Renderer->SetAmbient(0.5, 0.5, 0.5);

    m_Renderer->Render();
    m_Interactor->Start();
}

>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
//void STLViewer::sendLightButton(QPushButton* button)
//{
//    m_Light = button;
//    emit sendButtonEmit();
//}

//void STLViewer::sendButton(QPushButton *button)
//{
//    m_Light = button;
//    emit sendLightButton(m_Light);
//}
