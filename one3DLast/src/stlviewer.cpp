#include "stlviewer.h"
#include "ui_stlviewer.h"
#include "CustomInteractorStyle.h"
#include <QDebug>
#include <QDebug>
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
    m_WLightSlider = new QWidget(this);
    mWTool = new QWidget(this);
    mWMaterial = new QWidget(this);
    m_WAmbientSlider = new QWidget(this);

    m_Slider = new QSlider(Qt::Horizontal, this);
    m_Slider->setRange(0,100); 
    m_Slider->setMaximumSize(QSize(200, 50));

    m_Cutbutton = new QPushButton("Cut", this);
    m_Openbutton = new QPushButton("Open", this);
    m_Colorbutton = new QPushButton("Color", this);
    m_LightButton = new QPushButton("Light", this);

    m_LightXMoveButton = new QPushButton("XLight", this);
    m_LightYMoveButton = new QPushButton("YLight", this);
    m_LightZMoveButton = new QPushButton("ZLight", this);

    m_LightResetButton = new QPushButton("ResetLight", this);

    m_AmbientPushButton = new QPushButton("AmbientButton", this);
    m_DiffusePushButton = new QPushButton("DiffuseButton", this);
    m_SpotPushButton = new QPushButton("SpotButton", this);
    m_SpecularPushButton = new QPushButton("SpecularButton", this);
  
    m_FlatButton = new QPushButton("FlatButton", this);
    m_PhongButton = new QPushButton("PhongButton", this);
    m_GouraudButton = new QPushButton("GouraudButton", this);

    m_TextButton = new QPushButton("Texture", this);
    m_SaveButton = new QPushButton("Save", this);
    m_AmbientOcclusionButton = new QPushButton("Occlusion", this);
    m_BoundingBoxButton = new QPushButton("Box", this);


    mColorDialog = new QColorDialog();

    QLabel* AmbientLabel = new QLabel("AmbientLight");
    AmbientLabel->setStyleSheet("QLabel {color : #fff;}");
    QLabel* DiffuseLabel = new QLabel("DiffuseLight");
    DiffuseLabel->setStyleSheet("QLabel {color : #fff;}");
    QLabel* SpecularLabel = new QLabel("SpecualLight");
    SpecularLabel->setStyleSheet("QLabel {color : #fff;}");

    QLabel* ConeLabel = new QLabel("ConeLabel");
    ConeLabel->setStyleSheet("QLabel {color : #fff}");

    QLabel* AmbientRadiusLabel = new QLabel("AmbientRadiusLabel");
    AmbientRadiusLabel->setStyleSheet("QLabel {color : #fff}");

    QLabel* AmbientBiasLabel = new QLabel("AmbientBiasLabel");
    AmbientBiasLabel->setStyleSheet("QLabel {color : #fff}");

    QLabel* AmbientKernelLabel = new QLabel("AmbientKernelLabel");
    AmbientKernelLabel->setStyleSheet("QLabel {color : #fff}");

    QLabel* AmbientBlurLabel = new QLabel("AmbientBlurLabel");
    AmbientBlurLabel->setStyleSheet("QLabel {color : #fff}");

    m_HAmLightSliderLayout = new QHBoxLayout();
    m_HDiLightSliderLayout = new QHBoxLayout();
    m_HSpLightSliderLayout = new QHBoxLayout();

    m_HToolLayout = new QHBoxLayout();
    m_HmaterialLayout = new QHBoxLayout();
    m_ConeAngleLayout = new QHBoxLayout();
   // m_SettingButtonLayout = new QHBoxLayout();
    m_VlayoutAmbientOcclusion = new QVBoxLayout();

    m_AmbientLightSlider = new QSlider(Qt::Horizontal, this);
    m_AmbientLightSlider->setRange(0, 100);
    m_AmbientLightSlider->setMaximumSize(QSize(200, 50));

    m_DiffuseLightSlider = new QSlider(Qt::Horizontal, this);
    m_DiffuseLightSlider->setRange(0, 100);
    m_DiffuseLightSlider->setMaximumSize(QSize(200, 50));

    m_SpecularLightSlider = new QSlider(Qt::Horizontal, this);
    m_SpecularLightSlider->setRange(0, 100);
    m_SpecularLightSlider->setMaximumSize(QSize(200, 50));

    m_ConeAngle = new QSlider(Qt::Horizontal, this);
    m_ConeAngle->setRange(0, 100);
    m_ConeAngle->setMaximumSize(QSize(200, 50));

    m_AmbientRadiusSlider = new QSlider(Qt::Horizontal, this);
    m_AmbientRadiusSlider->setRange(0, 100);
    m_AmbientRadiusSlider->setMaximumSize(QSize(200, 50));

    m_AmbientBiasSlider = new QSlider(Qt::Horizontal, this);
    m_AmbientBiasSlider->setRange(0, 100);
    m_AmbientBiasSlider->setMaximumSize(QSize(200, 50));

    m_AmbientKernelSizeSlider = new QSlider(Qt::Horizontal, this);
    m_AmbientKernelSizeSlider->setRange(0, 100);
    m_AmbientKernelSizeSlider->setMaximumSize(QSize(200, 50));

    m_AmbientBlurSlider = new QSlider(Qt::Horizontal, this);
    m_AmbientBlurSlider->setRange(0, 100);
    m_AmbientBlurSlider->setMaximumSize(QSize(200, 50));

    m_VlayoutAmbientOcclusion->addWidget(AmbientRadiusLabel);
    m_VlayoutAmbientOcclusion->addWidget(m_AmbientRadiusSlider);

    m_VlayoutAmbientOcclusion->addWidget(AmbientBiasLabel);
    m_VlayoutAmbientOcclusion->addWidget(m_AmbientBiasSlider);

    m_VlayoutAmbientOcclusion->addWidget(AmbientKernelLabel);
    m_VlayoutAmbientOcclusion->addWidget(m_AmbientKernelSizeSlider);

    m_VlayoutAmbientOcclusion->addWidget(AmbientBlurLabel);
    m_VlayoutAmbientOcclusion->addWidget(m_AmbientBlurSlider);

    m_HAmLightSliderLayout->addWidget(AmbientLabel);
    m_HAmLightSliderLayout->addWidget(m_AmbientLightSlider);

    m_HDiLightSliderLayout->addWidget(DiffuseLabel);
    m_HDiLightSliderLayout->addWidget(m_DiffuseLightSlider);

    m_HSpLightSliderLayout->addWidget(SpecularLabel);
    m_HSpLightSliderLayout->addWidget(m_SpecularLightSlider);

    m_ConeAngleLayout->addWidget(ConeLabel);
    m_ConeAngleLayout->addWidget(m_ConeAngle);

    m_HToolLayout->addWidget(m_TextButton);
    m_HToolLayout->addWidget(m_SaveButton);
    m_HToolLayout->addWidget(m_AmbientOcclusionButton);
    m_HToolLayout->addWidget(m_BoundingBoxButton);

    m_HmaterialLayout->addWidget(m_PhongButton);
    m_HmaterialLayout->addWidget(m_GouraudButton);
    m_HmaterialLayout->addWidget(m_FlatButton);

    m_Renderer = vtkSmartPointer<vtkRenderer>::New();
    m_RenderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    mcolors = vtkSmartPointer<vtkNamedColors>::New();
    m_SpotLight = vtkSmartPointer<vtkLight>::New();
    m_Interactor = vtkSmartPointer<QVTKInteractor>::New();
    m_InteractorStyle = vtkSmartPointer<QVTKInteractor>::New();
    m_LightActor = vtkSmartPointer<vtkLightActor>::New();
    m_STLReader = vtkSmartPointer< vtkSTLReader>::New();
    m_PolyData = vtkSmartPointer<vtkPolyData>::New();
    m_OutlineActor = vtkSmartPointer<vtkActor>::New();
    ssaoPass = vtkSmartPointer<vtkSSAOPass>::New();

    m_Renderer = ui->openGLWidget->GetInteractor()->GetInteractorStyle()->GetCurrentRenderer();
    m_RenderWindow = ui->openGLWidget->GetRenderWindow();
    m_Interactor = ui->openGLWidget->GetInteractor();


    m_Sliderbutton = new QPushButton("Opacity", this);
    connect(m_Sliderbutton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(m_Openbutton, SIGNAL(clicked()), this, SLOT(ClickedOpen()));
    connect(m_Colorbutton, &QPushButton::clicked, this, [this](bool) { mColorDialog->show(); });
    connect(mColorDialog, SIGNAL(currentColorChanged(QColor)), this, SLOT(SetColor(QColor)));
    connect(m_Slider, SIGNAL(valueChanged(int)), this, SLOT(SetOpacity(int)));

    connect(m_LightButton, SIGNAL(clicked()), this, SLOT(cliekedLightButton()));
    connect(m_AmbientPushButton, SIGNAL(clicked()), this, SLOT(on_AmbientButton_clicked())); //Ambient
    connect(m_DiffusePushButton, SIGNAL(clicked()), this, SLOT(on_DiffusetButton_clicked())); //Diffuse
    connect(m_SpecularPushButton, SIGNAL(clicked()), this, SLOT(on_SpecularPushButton_clicked()));
    connect(m_SpotPushButton, SIGNAL(clicked()), this, SLOT(on_SpotPushButton_clicked()));// Spot

    connect(m_AmbientLightSlider, SIGNAL(valueChanged(int)), this, SLOT(SetLightAmbientChange(int)));
    connect(m_DiffuseLightSlider, SIGNAL(valueChanged(int)), this, SLOT(SetLightDiffuseChange(int)));
    connect(m_SpecularLightSlider, SIGNAL(valueChanged(int)), this, SLOT(SetLightSpecularChange(int)));
    connect(m_ConeAngle, SIGNAL(valueChanged(int)), this, SLOT(SetConeAngleChange(int)));
   
    connect(m_AmbientRadiusSlider, SIGNAL(valueChanged(int)), this, SLOT(SetAmbientRadiusChange(int)));
    connect(m_AmbientBiasSlider, SIGNAL(valueChanged(int)), this, SLOT(SetAmbientBiasChange(int)));
    connect(m_AmbientKernelSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(SetAmbientKernelSizeChange(int)));
    connect(m_AmbientBlurSlider, SIGNAL(valueChanged(int)), this, SLOT(SetAmbientBlurChange(int)));

    connect(m_LightXMoveButton, SIGNAL(clicked()), this, SLOT(SetLigntXMove()));
    connect(m_LightYMoveButton, SIGNAL(clicked()), this, SLOT(SetLightYMove()));
    connect(m_LightZMoveButton, SIGNAL(clicked()), this, SLOT(SetLightZMove()));
    connect(m_LightResetButton, SIGNAL(clicked()), this, SLOT(SetResetLight()));

    connect(m_TextButton, SIGNAL(clicked()), this, SLOT(SetTexture()));
    connect(m_SaveButton, SIGNAL(clicked()), this, SLOT(SaveFile()));
    connect(m_BoundingBoxButton, SIGNAL(clicked()), this, SLOT(BoundingBox()));

    connect(m_AmbientOcclusionButton, SIGNAL(clicked()), this, SLOT(SetvtkAmbientOcclusion()));
    
    connect(m_AmbientOcclusionButton, SIGNAL(clicked()), this, SLOT(clieckedTextureButton()));
    connect(m_AmbientRadiusSlider, SIGNAL(valueChanged(int)), this, SLOT(SetLightAmbientChange(int)));
    connect(m_AmbientBiasSlider, SIGNAL(valueChanged(int)), this, SLOT(SetLightAmbientChange(int)));
    connect(m_AmbientKernelSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(SetLightAmbientChange(int)));
    connect(m_AmbientBlurSlider, SIGNAL(valueChanged(int)), this, SLOT(SetLightAmbientChange(int)));

    connect(m_PhongButton, SIGNAL(clicked()), this, SLOT(SetPhongChange()));
    connect(m_GouraudButton, SIGNAL(clicked()), this, SLOT(SetGouraudChange()));
    connect(m_FlatButton, SIGNAL(clicked()), this, SLOT(SetFlatChange()));

    m_Hlayout = new QHBoxLayout();
    m_Vlayout = new QVBoxLayout();
    m_HlayoutLight = new QHBoxLayout();
    m_VlayoutLightSlider = new QVBoxLayout();

    m_Slider->hide();

    m_VlayoutLightSlider->addLayout(m_HAmLightSliderLayout);
    m_VlayoutLightSlider->addLayout(m_HDiLightSliderLayout);
    m_VlayoutLightSlider->addLayout(m_HSpLightSliderLayout);
    m_VlayoutLightSlider->addLayout(m_ConeAngleLayout);
    m_VlayoutLightSlider->addWidget(m_LightXMoveButton);
    m_VlayoutLightSlider->addWidget(m_LightYMoveButton);
    m_VlayoutLightSlider->addWidget(m_LightZMoveButton);

    m_VlayoutLightSlider->addWidget(m_LightResetButton);

    m_Hlayout->addWidget(m_Openbutton); 
    m_Hlayout->addWidget(m_Colorbutton); 
    m_Hlayout->addWidget(m_Cutbutton); 
    m_Hlayout->addWidget(m_LightButton);
    m_Hlayout->addWidget(m_Sliderbutton); 

    m_HlayoutLight->addWidget(m_AmbientPushButton);
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
    w->setStyleSheet("QWidget::horver{"
                     "background-color:#fff;"
                     "border: 10px;}");

    wLight->setLayout(m_HlayoutLight);
    wLight->setMinimumSize(500, 100);
    wLight->hide();

    mWTool->setLayout(m_HToolLayout);
    mWTool->setMinimumSize(500, 100);

    mWMaterial->setLayout(m_HmaterialLayout);
    mWMaterial->setMinimumSize(500, 100);
    mWMaterial->hide();

    m_WAmbientSlider->setLayout(m_VlayoutAmbientOcclusion);
    m_WAmbientSlider->setMinimumSize(500, 500);
    m_WAmbientSlider->hide();
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
    m_WLightSlider->move(0, 100);

    mWTool->move(width/ 2 - 200, height/3 + 500);
    mWMaterial->move(width / 3 + 300, height / 3 + 200);

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

void STLViewer::SetConeAngleChange(int Angle)
{
    qDebug() << "ConAngleChange";
    if (mActor != NULL)
    {
       // mActor->GetProperty()->SetAngle(Angle);
        mLight->SetConeAngle(Angle / 100.0);
       // mActor->Modified();
        ui->openGLWidget->GetRenderWindow()->Render();
    }
}

void STLViewer::SetAmbientRadiusChange(int Radius)
{
    qDebug() << "Radius";
    if (mActor != NULL)
    {
        ssaoPass->SetRadius(Radius / 100.0);
        m_Renderer->SetPass(ssaoPass);
        // mActor->Modified();
        ui->openGLWidget->GetRenderWindow()->Render();
    }
}

void STLViewer::SetAmbientBiasChange(int Bias)
{
    qDebug() << "Bias";
    if (mActor != NULL)
    {
        // mActor->GetProperty()->SetAngle(Angle);
        ssaoPass->SetBias(Bias/ 100.0);
          //ssao->SetDelegatePass(basicPasses);
        // mActor->Modified();
        ui->openGLWidget->GetRenderWindow()->Render();
    }
}

void STLViewer::SetAmbientKernelSizeChange(int KernelSize)
{
    qDebug() << "Kernel";
    if (mActor != NULL)
    {
        // mActor->GetProperty()->SetAngle(Angle);
        ssaoPass->SetKernelSize(KernelSize);
        // mActor->Modified();
        ui->openGLWidget->GetRenderWindow()->Render();
    }
}

void STLViewer::SetAmbientBlurChange(int Blur)
{
    qDebug() << "Blur";
    if (mActor != NULL)
    {
        // mActor->GetProperty()->SetAngle(Angle);
        ssaoPass->SetBlur(true);
        // mActor->Modified();
        ui->openGLWidget->GetRenderWindow()->Render();
    }
}


void STLViewer::cliekedLightButton()
{
        static int count = 0;

        switch (++count)
        {
        case 1:
            wLight->show();
            m_WLightSlider->show();
            mWMaterial->show();
            break;
        default:
            count = 0;
            wLight->hide();
            m_WLightSlider->hide();
            mWMaterial->hide();
            break;
        }

    }

void STLViewer::clieckedTextureButton()
{
    static int count = 0;
    qDebug() << "clieckedTextureButton";
    switch (++count)
    {
    case 1:
        m_WAmbientSlider->show();
        break;
    default:
        count = 0;
        m_WAmbientSlider->hide();
        break;
    }

}


//void STLViewer::MoveButton()
//{
//    int* pos = m_Interactor->GetEventPosition();
//    double worldPos[3];
//    m_Renderer->SetDisplayPoint(pos[0], pos[1], 0.0);
//    m_Renderer->DisplayToWorld();
//    m_Renderer->GetWorldPoint(worldPos);
//    vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
//    transform->Translate(worldPos);
//    mActor->SetUserTransform(transform);
//
//    m_Renderer->Render();
//    m_RenderWindow->AddRenderer(m_Renderer);
//    m_Interactor->SetRenderWindow(m_RenderWindow);
//
//    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
//    m_Interactor->SetInteractorStyle(style);
//    m_Interactor->AddObserver(vtkCommand::LeftButtonPressEvent, );
//
//    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
//    // set up actor here ...
//
//    m_Renderer->AddActor(actor);
//    m_Renderer->ResetCamera();
//    m_RenderWindow->Render();
//}
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
    m_STLReader = vtkSmartPointer<vtkSTLReader>::New();
    m_STLReader->SetFileName(fileName.c_str());
    qDebug() << " Open STL File" << m_STLReader->GetFileName();
    m_STLReader->Update();

    // Mapper
    m_PolyData->DeepCopy(m_STLReader->GetOutput());
    mMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mMapper->SetInputData(m_PolyData);
    mMapper->SetInputConnection(m_STLReader->GetOutputPort()); //

    // Actor
    mActor = vtkSmartPointer<vtkActor>::New();
    mActor->SetMapper(mMapper);
    //1mActor->GetProperty()->SetColor(mcolors->GetColor3d("Magenta").GetData());
    //mActor->GetProperty()->LightingOff();

    ui->openGLWidget->AddActor(mActor);
    //m_customVTKWidget->AddActor(mActor);
    //ui->openGLWidget->GetPolyData(polyData);
    qDebug() << "Actor" << mActor;
    qDebug() << "PolyData" << m_PolyData;
    ui->openGLWidget->GetInteractor()->GetInteractorStyle()->GetCurrentRenderer()->ResetCamera();
    ui->openGLWidget->GetRenderWindow()->Render();
    m_OriginProp = vtkSmartPointer<vtkProperty>::New();
    m_OriginProp = mActor->GetProperty();
    qDebug() << "m_OriginProp" << m_OriginProp<< endl;
    
}

void STLViewer::SetLightAmbientChange(int Ambient) // 주변광 slider 설정
{
    qDebug() << "SetLightChange";
    if (mActor != NULL)
    {
        mActor->GetProperty()->SetAmbient(Ambient / 100.0);
        mActor->Modified();
        ui->openGLWidget->GetRenderWindow()->Render();
    }
}

void STLViewer::SetLightDiffuseChange(int Diffuse) // 산란광 slider 설정
{
    qDebug() << "SetLightDiffuseChange";
    if (mActor != NULL)
    {
        mActor->GetProperty()->SetDiffuse(Diffuse / 100.0);
        mActor->Modified();
        ui->openGLWidget->GetRenderWindow()->Render();
    }
}

void STLViewer::SetLightSpecularChange(int Specular) //정반사광 slider 설정
{
    qDebug() << "SetLightSpeclarChange";
    if (mActor != NULL)
    {
        mActor->GetProperty()->SetSpecular(Specular / 100.0);
        mActor->Modified();
        ui->openGLWidget->GetRenderWindow()->Render();
    }
}

void STLViewer::SetLigntXMove() // X 축 방향으로 빛 설정
{
    qDebug() << "LightMove";

    double max = 0;
    double bound = 0;
    for (int i = 0; i < 6; i++)
    {
        // cout << "i : " << abs(outlineActor->GetBounds()[i]) << endl;
        max = (max < abs(m_OutlineActor->GetBounds()[i])) ? abs(m_OutlineActor->GetBounds()[i]) : max;
        if (max == abs(m_OutlineActor->GetBounds()[i]))
        {
            bound = abs(max);
        }
    }
    //cout << "max :" << abs(max) << endl;

    m_OutlineActor->GetCenter();

    mLight->SetPosition(m_OutlineActor->GetCenter()[0] + abs(m_OutlineActor->GetBounds()[1] + 10.0), m_OutlineActor->GetCenter()[1] , m_OutlineActor->GetCenter()[2]);

   // mLight->SetPosition(1, 0, 0);
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

void STLViewer::SetLightYMove() //Y축 방향으로 빛 설정
{
    qDebug() << "LightMove";

    double max = 0;
    double bound = 0;
    for (int i = 0; i < 6; i++)
    {
       // cout << "i : " << abs(outlineActor->GetBounds()[i]) << endl;
        max = (max < abs(m_OutlineActor->GetBounds()[i])) ? abs(m_OutlineActor->GetBounds()[i]) : max;
        if (max == abs(m_OutlineActor->GetBounds()[i]))
        {
            bound = abs(max);
        }
    }
    //cout << "max :" << abs(max) << endl;

    m_OutlineActor->GetCenter();
    
    mLight->SetPosition(m_OutlineActor->GetCenter()[0], m_OutlineActor->GetCenter()[1] + abs(m_OutlineActor->GetBounds()[3]+10.0), 
                        m_OutlineActor->GetCenter()[2]);


   // mLight->SetPosition(0, 0, 1);
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

void STLViewer::SetLightZMove() // z축 방향으로 빛 설정
{
    qDebug() << "LightMove";
    //m_transform->RotateWXYZ(-90, 1, 0, 0);
    //m_Camera->ApplyTransform(m_transform);
    double max = 0;
    double bound = 0;
    for (int i = 0; i < 6; i++)
    {
        // cout << "i : " << abs(outlineActor->GetBounds()[i]) << endl;
        max = (max < abs(m_OutlineActor->GetBounds()[i])) ? abs(m_OutlineActor->GetBounds()[i]) : max;
        if (max == abs(m_OutlineActor->GetBounds()[i]))
        {
            bound = abs(max);
        }
    }
    //cout << "max :" << abs(max) << endl;

    m_OutlineActor->GetCenter();
    mLight->SetPosition(m_OutlineActor->GetCenter()[0], m_OutlineActor->GetCenter()[1], 
        m_OutlineActor->GetCenter()[2] + abs(m_OutlineActor->GetBounds()[5] + 10.0));

   // mLight->SetPosition(0, 0, 1);
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

void STLViewer::SetTexture()
{
    qDebug() << "SetTexture";

    std::string fileName = QFileDialog::getOpenFileName(nullptr,
        "PNG Files", "/home", "png Files (*.png)").toStdString().c_str();

    vtkSmartPointer<vtkPNGReader> pngReader =
        vtkSmartPointer<vtkPNGReader>::New();
    pngReader->SetFileName(fileName.c_str());
    pngReader->Update();
    qDebug() << "pngRender" << pngReader->GetFileName();

    m_PolyData->DeepCopy(pngReader->GetOutput());
    mMapper->SetInputData(m_PolyData);
    mMapper->SetInputConnection(pngReader->GetOutputPort()); //
    qDebug() << "m_polyData" << m_PolyData;

    vtkSmartPointer<vtkTexture> m_Texture =
        vtkSmartPointer<vtkTexture>::New();

    qDebug() << "m_Texture" << m_Texture->GetTextureUnit();
    m_Texture->SetInputConnection(pngReader->GetOutputPort());

    m_Texture->InterpolateOn(); // 선형 보간을 킨다.

    qDebug() << "MaxFiltering" << m_Texture->GetMaximumAnisotropicFiltering();

    vtkSmartPointer<vtkTextureMapToSphere> textureMapToSphere = // 한개의 png 파일을 입히기 
        vtkSmartPointer<vtkTextureMapToSphere>::New();

    textureMapToSphere->SetInputData(m_PolyData);
    textureMapToSphere->SetInputConnection(m_STLReader->GetOutputPort());
    textureMapToSphere->Update(); 
    textureMapToSphere->PreventSeamOn();
    textureMapToSphere->SetAutomaticSphereGeneration(1);
     
    mMapper->SetInputConnection(textureMapToSphere->GetOutputPort());
    mActor->SetMapper(mMapper);
    mActor->SetTexture(m_Texture);

    qDebug() << "texture" << m_Texture;
    m_Renderer->AddActor(mActor);
    m_Renderer->UseDepthPeelingOn(); // texture 투명도 해결을 위한 방법
    m_RenderWindow->SetAlphaBitPlanes(1); //texture 투명도 해결을 위해 설정
    m_RenderWindow->SetMultiSamples(0);     //texture 투명도 해결을 위해 설정
    m_RenderWindow->AddRenderer(m_Renderer);
    m_Interactor->SetRenderWindow(m_RenderWindow);

    ui->openGLWidget->GetRenderWindow()->Render();
   /* m_Interactor->Start();*/
    m_OriginProp = mActor->GetProperty();
    qDebug() << "m_OrigninProp" << m_OriginProp;
}

void STLViewer::SetvtkAmbientOcclusion()
{
    //vtkSmartPointer<vtkSSAOPass> ssaoPass = vtkSmartPointer<vtkSSAOPass>::New();
    //ssaoPass->SetRadius(0.9);
    //ssaoPass->SetBias(0.16);
    //ssaoPass->SetKernelSize(500);

    //vtkNew<vtkRenderStepsPass> basicPasses;
    //double sceneSize =0; // e.g. the diagonal of the bounding box

    //vtkNew<vtkSSAOPass> ssao;
    //ssao->SetRadius(0.1 * sceneSize); // comparison radius
    //ssao->SetBias(0.001 * sceneSize); // comparison bias
    //ssao->SetKernelSize(128); // number of samples used
    //ssao->BlurOff(); // do not blur occlusion
    //ssao->SetDelegatePass(basicPasses);

    vtkNew<vtkRenderStepsPass> basicPasses;

    ssaoPass->SetRadius(0.1);
    ssaoPass->SetBias(0.001 );
    ssaoPass->SetKernelSize(128);
    ssaoPass->BlurOn();
    ssaoPass->SetDelegatePass(basicPasses);
    m_Renderer->SetPass(ssaoPass);


    //mActor->GetProperty()->SetOcclusionStrength(1.0);

    //m_Renderer->SetPass(ssaoPass);
    //m_Renderer->AddActor(mActor);
    ////m_RenderWindow->Render();

    ////m_Interactor->SetRenderWindow(m_RenderWindow);

    ui->openGLWidget->GetRenderWindow()->Render();
}

void STLViewer::on_AmbientButton_clicked() //주변광 
{
    qDebug() << "Ambient---------------";

    double ambient = 0.4;
    double diffuse = 0.4;
    double specular = 0.4;
    double spbase = 0.5;
    double spscale = 0.1;

    double specularpower = spbase * spscale; 

    QColor color = mColorDialog->getColor();
    double r = color.toRgb().redF();
    double g = color.toRgb().greenF();
    double b = color.toRgb().blueF();

    mLight->SetLightTypeToSceneLight(); //세계 좌표 공간에 위치한 조명
   // mLight->SetLightTypeToCameraLight();

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
    ui->openGLWidget->GetRenderWindow()->Render();
}

void STLViewer::on_DiffusetButton_clicked()// 분산광 / 산란광
{
    QColor color = mColorDialog->getColor(); // 색 설정을 위한 colorDialog
    double r = color.toRgb().redF();
    double g = color.toRgb().greenF();
    double b = color.toRgb().blueF();

    //mLight->SetLightTypeToSceneLight();
    mLight->SetLightTypeToCameraLight(); // 카메라 시점에 따라 빛 이동

    //mLight->SetPosition(0, 0, 5);
    mLight->SetDiffuseColor(r, g, b); //색 정보를 받아 온다
    m_Renderer->AddLight(mLight);
    m_InteractorStyle->Start();
    ui->openGLWidget->GetRenderWindow()->Render();
}

void STLViewer::on_SpotPushButton_clicked()
{
    QColor color = mColorDialog->getColor(); // 색 설정을 위한 colorDialog
    double r = color.toRgb().redF();
    double g = color.toRgb().greenF();
    double b = color.toRgb().blueF();

    mLight->SetConeAngle(0.3); // 콘의 각도
   // LightActor->GetConeProperty()->SetColor(r, g, b);

 //   mLight->SetLightTypeToCameraLight();
    mLight->SetPositional(true);
    mLight->SetLightTypeToCameraLight();
    //mLight->SetColor(mcolors->GetColor3d("Magenta").GetData());
    mLight->SetColor(r, g, b);
    mLight->PositionalOn();

    m_LightActor->SetLight(mLight);

    //mActor->GetProperty()->SetAmbient(ambient);
    //mActor->GetProperty()->SetDiffuse(diffuse);
    //mActor->GetProperty()->SetSpecular(specular);
    //mActor->GetProperty()->SetSpecularPower(specularpower);
    //mActor->GetProperty()->SetSpecularColor(r, g, b);

    //mActor->AddPosition(position.data());

    qDebug() << "mLight" << mLight;
    m_Renderer->AddLight(mLight);
    m_Renderer->AddViewProp(m_LightActor);

    ui->openGLWidget->GetRenderWindow()->Render();
}

void STLViewer::on_SpecularPushButton_clicked() // Specular(정반사광) light 버튼이 눌렸을 때 실행
{
    double ambient = 0.4; // 초기 설정값
    double diffuse = 0.4;
    double specular = 0.4;
    double spbase = 0.5;
    double spscale = 1.0;

    double specularpower = spbase * spscale; // 반사력 설정

    QColor color = mColorDialog->getColor();
    double r = color.toRgb().redF();
    double g = color.toRgb().greenF();
    double b = color.toRgb().blueF();

    mLight->SetPosition(-1.0, 0.0, 1.0); // 빛의 위치
    mLight->SetConeAngle(0.3); // 콘의 각도
   // LightActor->GetConeProperty()->SetColor(r, g, b);

 //   mLight->SetLightTypeToCameraLight();
    mLight->SetPositional(true);
    mLight->SetLightTypeToSceneLight();
    mLight->SetFocalPoint(0, 0, 0);

    m_LightActor->SetLight(mLight);

    mActor->GetProperty()->SetAmbient(ambient);
    mActor->GetProperty()->SetDiffuse(diffuse);
    mActor->GetProperty()->SetSpecular(specular);
    mActor->GetProperty()->SetSpecularPower(specularpower);
    mActor->GetProperty()->SetSpecularColor(r, g, b);
    
    //mActor->AddPosition(position.data());

    qDebug() << "mLight" << mLight;
    m_Renderer->AddLight(mLight);
    m_Renderer->AddViewProp(m_LightActor); 
   ui->openGLWidget->GetInteractor()->GetInteractorStyle()->GetCurrentRenderer()->AddViewProp(m_LightActor);
    ui->openGLWidget->GetRenderWindow()->Render();
    m_Interactor->Start();
}

void STLViewer::SetFlatChange()
{
    qDebug() << "Flat";
    
    mMapper->SetInputConnection(m_STLReader->GetOutputPort());
    mMapper->SetScalarVisibility(0);

    mActor->SetMapper(mMapper);
    mActor->GetProperty()->SetInterpolationToFlat();

    m_Renderer->AddActor(mActor);
    m_RenderWindow->AddRenderer(m_Renderer);
    m_Interactor->SetRenderWindow(m_RenderWindow);

    ui->openGLWidget->GetRenderWindow()->Render();

}

void STLViewer::SetPhongChange() // 셀 전체에 색상을 보간하기 위해 사용한다.
{                               // 고러드 쉐이딩에서 하이라이트나 반사광을 표현할 수 없는것을
                                // 가능하게 해주는 쉐이딩
    qDebug() << "Phong";
    /*mActor->GetProperty()->SetSpecularPower(0.3);*/

    vtkSmartPointer<vtkPolyDataNormals> normalGenerator = // 다각형 메시에 대한 법선 계산을 위해서 사용
        vtkSmartPointer<vtkPolyDataNormals>::New();
    normalGenerator->SetInputConnection(m_STLReader->GetOutputPort());
    normalGenerator->ComputePointNormalsOn(); //접 번선 계산을 킨다.
    normalGenerator->ComputeCellNormalsOff(); //셀 법선 계산을 끈다
    normalGenerator->SetFeatureAngle(60.0); // 각도를 지정한다.
    normalGenerator->Update();

    mMapper->SetInputConnection(normalGenerator->GetOutputPort());
    mActor->SetMapper(mMapper);
    mActor->GetProperty()->SetInterpolationToPhong();

    //vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();
    //light->SetPosition(1, 1, 1);
    ///*light->SetColor(1, 1, 1);*/
    //m_Renderer->AddLight(light);

    //vtkSmartPointer<vtkCamera> camera =
    //    vtkSmartPointer<vtkCamera>::New();
    //camera->SetPosition(0, 0, 3);
    //camera->SetFocalPoint(0, 0, 0);
    //camera->SetViewUp(0, 1, 0);
    //camera->Azimuth(30);
    //camera->Elevation(30);

    m_Renderer->AddActor(mActor);
    m_RenderWindow->AddRenderer(m_Renderer);
    m_Interactor->SetRenderWindow(m_RenderWindow);


    ui->openGLWidget->GetRenderWindow()->Render();
    m_Interactor->Start();
}

void STLViewer::SetGouraudChange() // falt 쉐이딩의 단점을 보완한 쉐이딩
{
    //mActor->GetProperty()->SetSpecularPower(0.3);    
    qDebug() << "gour";
    vtkSmartPointer<vtkPolyDataNormals> normalGenerator =
        vtkSmartPointer<vtkPolyDataNormals>::New();
    normalGenerator->SetInputConnection(m_STLReader->GetOutputPort());
    normalGenerator->ComputePointNormalsOn();
    normalGenerator->ComputeCellNormalsOff();
    normalGenerator->SetFeatureAngle(60.0);
    normalGenerator->Update();

    mMapper->SetInputConnection(normalGenerator->GetOutputPort());
    mActor->SetMapper(mMapper);
    mActor->GetProperty()->SetInterpolationToGouraud();

    //vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();
    //light->SetPosition(1, 1, 1);
    //light->SetColor(1, 1, 1);
    //m_Renderer->AddLight(light);

    vtkSmartPointer<vtkCamera> camera =
        vtkSmartPointer<vtkCamera>::New();
    camera->SetPosition(0, 0, 30);
    camera->SetFocalPoint(0, 0, 0);
    camera->SetViewUp(0, 1, 0);
    camera->Azimuth(30);
    camera->Elevation(30);

    m_Renderer->AddActor(mActor);
    m_RenderWindow->AddRenderer(m_Renderer);
    m_Interactor->SetRenderWindow(m_RenderWindow);

    ui->openGLWidget->GetRenderWindow()->Render();
    m_Interactor->Start();
}

void STLViewer::SetResetLight() //리셋 버튼이 눌렀을 때 빛 설정을 초기화 한다.
{
    qDebug() << "SetResetLight";

  //  mActor->GetProperty()->SetColor(1.0, 1.0, 1.0);
    //mActor->GetProperty()->SetAmbientColor(1.0, 1.0, 1.0);
    //mActor->GetProperty()->SetDiffuseColor(1.0, 1.0, 1.0);
    //mActor->GetProperty()->SetSpecularColor(1.0, 1.0, 1.0);
   // m_Renderer->SetBackground(mcolors->GetColor3d("white").GetData());
    mActor->SetProperty(m_OriginProp);
    ui->openGLWidget->GetRenderWindow()->Render();
    qDebug() << "m_OriginProp" << m_OriginProp << endl;
}

int STLViewer::SaveFile()
{
    qDebug() << "SaveFile";

    //std::string fileName = QFileDialog::getOpenFileName(nullptr,
    //    "STL Files", "/home", "STL Files (*.stl)").toStdString().c_str();

    //vtkSmartPointer<vtkSTLWriter> writer =
    //    vtkSmartPointer<vtkSTLWriter>::New();
    //writer->SetFileName("*.stl");
    //writer->SetInputConnection(m_STLReader->GetOutputPort());
    //writer->Write();
    QMessageBox msgBox;
    std::string fileName = QFileDialog::getSaveFileName(nullptr,
        "STL Files", "/home", "STL Files (*.stl)").toStdString().c_str();

    if (fileName.empty())
    {
        QMessageBox::warning(this, "", "File name is empty.");
      
        return -1;
    }

    vtkSmartPointer<vtkSTLWriter> writer =
        vtkSmartPointer<vtkSTLWriter>::New();
    vtkSmartPointer<vtkWindowToImageFilter> winToImg = 
        vtkSmartPointer< vtkWindowToImageFilter>::New();

    winToImg->SetInputBufferTypeToRGBA();
    winToImg->ReadFrontBufferOff();

    writer->SetInputConnection(winToImg->GetOutputPort());
    qDebug() << "writer11111111111111" << writer;
    writer->SetFileName(fileName.c_str());
  
    writer->SetInputData(m_PolyData);
   
    writer->SetFileTypeToBinary(); // 바이너리 파일로 저장
    writer->Write();

    QMessageBox::warning(this, "", "Success!.");

    //msgBox.setText("File save!!");
}

void STLViewer::BoundingBox()
{
    vtkSmartPointer<vtkOutlineFilter> outlineFilter =
        vtkSmartPointer<vtkOutlineFilter>::New();
    outlineFilter->SetInputConnection(m_STLReader->GetOutputPort());

    vtkSmartPointer<vtkPolyDataMapper> outLinemapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    outLinemapper->SetInputConnection(outlineFilter->GetOutputPort());
  
    m_OutlineActor->SetMapper(outLinemapper);
    m_OutlineActor->GetProperty()->SetColor(1, 1, 1);
    // --------------------- Drawing bounding box end------------------------ 
    ui->openGLWidget->AddActor(m_OutlineActor);
}