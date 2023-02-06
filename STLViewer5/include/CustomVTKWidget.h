#pragma once
#include <QVTKOpenGLNativeWidget.h>
#include <QVTKInteractorAdapter.h>
#include <vtkSTLReader.h>
#include <vtkActor.h>
#include "CustomInteractorStyle.h"
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include "observer.h"
#include <vtkOrientationMarkerWidget.h>
#include <vtkAxesActor.h>
#include <QDebug>
<<<<<<< HEAD
=======
//#include <vtkLight.h>
//#include <QPushButton>
//#include <QWidget>
//#include <QHBoxLayout>
//#include <QColorDialog>
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088


class CustomVTKWidget : public QVTKOpenGLNativeWidget , public Observer
{ 
    Q_OBJECT
        

public:
    CustomVTKWidget();
	CustomVTKWidget(QWidget* parent);
	~CustomVTKWidget();

    // Renderer Add Actor
    void AddActor(vtkSmartPointer<vtkActor>);
    void GetPolyData(vtkSmartPointer<vtkPolyData>);
    void GetSphere(vtkSmartPointer<vtkSphereSource>);
    void AddSphere(vtkSmartPointer<vtkActor>);


protected:
    // VTK Renderer
    vtkSmartPointer<vtkRenderer> mRenderer; 
    // VTK Render Window
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> mRenderWindow; 
    vtkSmartPointer<QVTKInteractor> mInteractor;
    QVTKInteractorAdapter* mvtkInteractorAdapter; 
<<<<<<< HEAD
    virtual void func(vtkSmartPointer<vtkActor>);

private: 
=======
    
    virtual void func(vtkSmartPointer<vtkActor>);

//private slots:
//    void on_AmbientButton_clicked();
//    void on_DiffusetButton_clicked();
//    void on_SpotPushButton_clicked();
//    void ShowLightButton();
   
private: 
    //vtkSmartPointer<vtkLight> greenLight;//
    //vtkSmartPointer<vtkNamedColors> colors; //

    //vtkSmartPointer<vtkLight> mLight;
    //QPushButton* mAmbient;
    //QPushButton* mDiffuseButton;
    //QPushButton* mSpotPushButton;
    //QWidget* mWViewer;
    //QHBoxLayout* mlayout;
    //QColorDialog* mColorDialog;
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
    CustomInteractorStyle* customInteractorStyle;
};