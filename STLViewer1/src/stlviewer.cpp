#include "stlviewer.h"
#include "./ui_stlviewer.h"
#include <QDebug>
#include <QFileDialog>
#include <QColorDialog>
#include <vtkPointData.h>



STLViewer::STLViewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::STLViewer)
{
    ui->setupUi(this);

    mColorDialog = new QColorDialog(this);

  /*  mLight = vtkSmartPointer<vtkLight>::New();*/
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(ClickedOpen(bool)));  
    connect(ui->actionColor,&QAction::triggered, this, [this](bool) { mColorDialog->show(); });
    connect(mColorDialog, SIGNAL(currentColorChanged(QColor)), this, SLOT(SetColor(QColor)));  
    connect(ui->opacitySlider, SIGNAL(valueChanged(int)), this, SLOT(SetOpacity(int)));
    //connect(mAmbient, SIGNAL(clicked()), this, SLOT(on_AmbientButton_clicked()));
}

STLViewer::~STLViewer()
{
    delete ui;
}

void STLViewer::ClickedOpen(bool)
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
   // mActor->GetProperty()->SetInterpolationToPhong(); //  Æþ ½¦ÀÌµù

    //double ambient[3] = { 0.2, 0.2, 0.2 };
    //mActor->GetProperty()->SetAmbientColor(ambient); //ambient ÁÖ±â
    //double ambientColor[3];
    //mActor->GetProperty()->GetAmbientColor(ambientColor);

    ui->openGLWidget->AddActor(mActor);
    ui->openGLWidget->GetPolyData(polyData);
    qDebug() << "Actor" << mActor;
    qDebug() << "PolyData" << polyData;
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
        mActor->GetProperty()->SetOpacity(opacity/100.0);
        mActor->Modified();
        ui->openGLWidget->GetRenderWindow()->Render();
    }
} 

//void STLViewer::on_AmbientButton_clicked()
//{
//    qDebug() << "11111111111111";
//    mLight->SetLightTypeToSceneLight();
//    mLight->SetAmbientColor(1, 1, 1);
//
//   // mRenderer->AddLight(mLight);
//
//}

void STLViewer::resizeEvent(QResizeEvent* event)
{
    //event->size().height();
   /* mWViewer->setGeometry(11, 500, 300, 200);*/
    //glClearColor(255, 255, 255, 0);

}
