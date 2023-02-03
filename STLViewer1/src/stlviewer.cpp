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

    m_Slider = new QSlider(Qt::Horizontal, this);
    m_Slider->setRange(0,100); 
    m_Slider->setMaximumSize(QSize(200, 50));
    m_Cutbutton = new QPushButton("Cut", this);
    m_Openbutton = new QPushButton("Open", this);
    m_Colorbutton = new QPushButton("Color", this);
    m_LightButton = new QPushButton("Light", this);

    m_AmbientPushButton = new QPushButton("AmbientButton", this);
    m_DiffusePushButton = new QPushButton("DiffuseButton", this);
    m_SpotPushButton = new QPushButton("SpotButton", this);
    m_SpecularPushButton = new QPushButton("SpecularButton", this);
    mColorDialog = new QColorDialog();

    //m_Colorbutton->setGeometry(0, 0, 100, 100);
    //m_Openbutton->setGeometry(0, 0, 100, 100);
    //m_Light->setGeometry(0, 0, 100, 100);
    //m_Cutbutton->setGeometry(0, 0, 100, 100);
    m_Renderer = vtkSmartPointer<vtkRenderer>::New();
    m_RenderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    m_Renderer = ui->openGLWidget->GetInteractor()->GetInteractorStyle()->GetCurrentRenderer();
    m_RenderWindow = ui->openGLWidget->GetRenderWindow();
    mcolors = vtkSmartPointer<vtkNamedColors>::New();
    m_InteractorStyle = vtkSmartPointer<QVTKInteractor>::New();

    m_Sliderbutton = new QPushButton("Opacity", this);
    connect(m_Sliderbutton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(m_Openbutton, SIGNAL(clicked()), this, SLOT(ClickedOpen()));
    connect(m_Colorbutton, &QPushButton::clicked, this, [this](bool) { mColorDialog->show(); });
    connect(mColorDialog, SIGNAL(currentColorChanged(QColor)), this, SLOT(SetColor(QColor)));
    connect(m_Slider, SIGNAL(valueChanged(int)), this, SLOT(SetOpacity(int)));

    connect(m_LightButton, SIGNAL(clicked()), this, SLOT(cliekedLightButton()));


    m_Hlayout = new QHBoxLayout();
    m_Vlayout = new QVBoxLayout();
    m_HlayoutLight = new QHBoxLayout();
    m_Slider->hide();
    //m_layout->addWidget(m_Slider);
    m_Hlayout->addWidget(m_Openbutton); 
    m_Hlayout->addWidget(m_Colorbutton); 
    m_Hlayout->addWidget(m_Cutbutton); 
    m_Hlayout->addWidget(m_LightButton);
    m_Hlayout->addWidget(m_Sliderbutton); 

    m_HlayoutLight->addWidget(m_AmbientPushButton);
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

    w->setLayout(m_Vlayout);
    w->setMinimumSize(500, 100);


    w->setStyleSheet("QWidget::horver{"
                     "background-color:#fff;"
                     "border: 10px;}");

    wLight->setLayout(m_HlayoutLight);

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
    
    //qDebug() << "1qqqqqqqqqqqqqqqq";
    //if (m_AmbientPushButton->isHidden())
    //    m_AmbientPushButton->show();
    //else
    //    m_AmbientPushButton->hide();


    switch (1)
    {
    case 0:
        m_AmbientPushButton->hide();
        m_DiffusePushButton->hide();
        m_SpecularPushButton->hide();
        m_SpotPushButton->hide();
        qDebug() << "2222222222222222222" <<  0;
    case 1:
        m_AmbientPushButton->show();
        m_DiffusePushButton->show();
        m_SpecularPushButton->show();
        m_SpotPushButton->show();
    default:

        break;
    }

    //QColor color = mColorDialog->getColor();
    //double r = color.toRgb().redF();
    //double g = color.toRgb().greenF();
    //double b = color.toRgb().blueF();

    ////mLight->SetLightTypeToSceneLight();
    //mLight->SetLightTypeToCameraLight();
    ////mLight->SetLightTypeToCameraLight();

    //mLight->SetAmbientColor(r, g, b);
    //qDebug() << "mLight" << mLight;
    //m_Renderer->AddLight(mLight);
  
}

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
}


void STLViewer::on_AmbientButton_clicked()
{
    qDebug() << "Ambient---------------";

    //mColorDialog->show();

    QColor color = mColorDialog->getColor();
    double r = color.toRgb().redF();
    double g = color.toRgb().greenF();
    double b = color.toRgb().blueF();

    //mLight->SetLightTypeToSceneLight();
    mLight->SetLightTypeToCameraLight();
    //mLight->SetLightTypeToCameraLight();

    mLight->SetAmbientColor(r, g, b);
    qDebug() << "mLight" << mLight;
    m_Renderer->AddLight(mLight);
    m_InteractorStyle->Start();

}

void STLViewer::on_DiffusetButton_clicked()
{
    QColor color = mColorDialog->getColor();
    double r = color.toRgb().redF();
    double g = color.toRgb().greenF();
    double b = color.toRgb().blueF();

    mLight->SetLightTypeToSceneLight();
    //mLight->SetLightTypeToCameraLight();

    mLight->SetDiffuseColor(r, g, b);
    m_Renderer->AddLight(mLight);
    m_InteractorStyle->Start();
}

void STLViewer::on_SpotPushButton_clicked()
{
    qDebug() << "SpotPushButton";
    QColor color = mColorDialog->getColor();
    double r = color.toRgb().redF();
    double g = color.toRgb().greenF();
    double b = color.toRgb().blueF();

    m_Renderer->ResetCamera();
    m_Renderer->GetActiveCamera()->Azimuth(40.0);
    m_Renderer->GetActiveCamera()->Elevation(30.0);

    m_SpotLight->PositionalOn();
    m_SpotLight->SetColor(r, g, b);
    m_SpotLight->SetPosition(-3.0, 10.0, -1.0);
    m_SpotLight->SetIntensity(0.5);

    m_Renderer->AddLight(m_SpotLight);

    m_Renderer->SetBackground(mcolors->GetColor3d("RoyalBlue").GetData());
    m_Renderer->GradientBackgroundOn();

    m_InteractorStyle->Initialize();
    m_RenderWindow->Render();
    m_InteractorStyle->Start();
}


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
