#include "CustomvtkInteractorActor.h"
#include <QDebug>

CustomvtkInteractorActor::CustomvtkInteractorActor()
{

}

CustomvtkInteractorActor::~CustomvtkInteractorActor()
{

}

void CustomvtkInteractorActor::addObserver(Observer* observer)
{
	mObserver = observer;
}

void CustomvtkInteractorActor::GetActor(vtkSmartPointer<vtkActor> sphereSource)
{
	mActor = sphereSource;
}

void CustomvtkInteractorActor::GetPolyData(vtkSmartPointer<vtkPolyData>)
{

}

void CustomvtkInteractorActor::Rotate()
{
	__super::Rotate();
    double* center = mActor->GetCenter();
    double angle = 10.0; // degrees
    double axis[3] = { 0.0, 1.0, 0.0 };
    mActor->RotateY(angle);
    this->Interactor->Render();
}


void CustomvtkInteractorActor::Spin()
{

}

void CustomvtkInteractorActor::Pan()
{
}

void CustomvtkInteractorActor::OnLeftButtonDown()
{
	//this->FindPokedRenderer(this->Interactor->GetEventPosition()[0],
	//	this->Interactor->GetEventPosition()[1]);

 //   vtkAssemblyPath* path = this->GetPath();

 //   if (path)
 //   {
 //       vtkActor* actor = dynamic_cast<vtkActor*>(path->GetLastNode()->GetViewProp());
 //       if (actor)
 //       {
 //           this->RotateActor(actor);
 //       }
 //   }
 //   else
 //   {
 //       this->Superclass::OnLeftButtonDown();
 //   }
	__super::OnLeftButtonDown();
    this->StartRotate();
	qDebug() << "CustomvtkInteractorActor::OnLeftButtonDown";
	vtkSmartPointer<vtkInteractorStyleTrackballActor> style = vtkSmartPointer<vtkInteractorStyleTrackballActor>::New();
	style->Rotate();
	renderWindowInteractor->SetInteractorStyle(style);
}


void CustomvtkInteractorActor::OnLeftButtonUp()
{
	__super::OnLeftButtonUp();
    this->EndRotate();
}

