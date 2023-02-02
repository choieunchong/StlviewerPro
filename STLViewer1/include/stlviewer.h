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
#include <vtkSmartPointer.h>
#include <QSlider>
#include <vtkLight.h>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class STLViewer; }
QT_END_NAMESPACE

class STLViewer : public QMainWindow
{
    Q_OBJECT

public:
    STLViewer(QWidget *parent = nullptr);
    ~STLViewer();

private:
    Ui::STLViewer *ui;
    CustomVTKWidget* customVTKWidget;

    //vtkSmartPointer<vtkLight> mLight;
    vtkSmartPointer<vtkActor> mActor;
    QColorDialog* mColorDialog;  
    QSlider* mSlider;
    vtkSmartPointer<vtkPolyData> mPolyData;
    //QPushButton* mAmbient;
    //QWidget* mWViewer;
    //QVBoxLayout* m_layout;

protected:
    virtual void resizeEvent(QResizeEvent* event) override;

private slots:
    void ClickedOpen(bool);                         // Menu -> Open 
    void SetColor(QColor);                          // Actor Color Change
    void SetOpacity(int);                           // Acotr Opacity Change
    //void on_AmbientButton_clicked();

};
#endif // STLVIEWER_H
