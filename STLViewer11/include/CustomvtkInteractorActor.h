#pragma once

#include <vtkInteractorStyleTrackballActor.h>
#include "observer.h"
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkObjectFactory.h>
#include <vtkMatrix4x4.h>

#include <vtkCallbackCommand.h>
#include <vtkCamera.h>
#include <vtkCellPicker.h>
#include <vtkMath.h>
#include <vtkObjectFactory.h>
#include <vtkProp3D.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTransform.h>

using namespace std;

class CustomvtkInteractorActor : public vtkInteractorStyleTrackballActor
{

public:
	CustomvtkInteractorActor();
	~CustomvtkInteractorActor();

	static vtkInteractorStyleTrackballActor* New();
	vtkTypeMacro(vtkInteractorStyleTrackballActor, vtkInteractorStyle);
	void PrintSelf(ostream& os, vtkIndent indent) override;

	void addObserver(Observer*);
	void GetActor(vtkSmartPointer<vtkActor>);
	void GetPolyData(vtkSmartPointer<vtkPolyData>);

	void OnMouseMove() override;
	void OnLeftButtonDown() override;
	void OnLeftButtonUp() override;
	void OnMiddleButtonDown() override;
	void OnMiddleButtonUp() override;
	void OnRightButtonDown() override;
	void OnRightButtonUp() override;

	void Rotate() override;
	void Spin() override;
	void Pan() override;
	void Dolly() override;
	void UniformScale() override;

protected:


	void FindPickedActor(int x, int y);

	void Prop3DTransform(
		vtkProp3D* prop3D, double* boxCenter, int NumRotation, double** rotate, double* scale);

	double MotionFactor;

	vtkProp3D* InteractionProp;
	vtkCellPicker* InteractionPicker;

private:
	Observer* mObserver;
	vtkSmartPointer<vtkPolyData> mPolyData;
	vtkSmartPointer<vtkActor> mActor;
	vtkSmartPointer<vtkRenderer>m_Renderer;
	vtkSmartPointer<vtkSphereSource> mSphere;
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;


};