#pragma once

#include <QWidget> 
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <QVTKInteractor.h>
#include <vtkInteractorStyle.h> 
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkParallelCoordinatesInteractorStyle.h>
#include <vtkPolyData.h>
#include <vtkCellPicker.h>
#include <vtkIdTypeArray.h>
#include <vtkSelectionNode.h>
#include <vtkSelection.h>
#include <vtkExtractSelection.h>
#include <vtkNamedColors.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkTriangle.h>
#include "observer.h"
#include "TriMesh.h"
#include <vtkVector.h>
#include <vector>
#include <queue>
#include <QHash>
#include <vtkIdList.h>
#include <vtkLight.h>
#include <vtkCamera.h>
#include <vtkLight.h>
#include <vtkRenderWindow.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkMatrix4x4.h>

using namespace std;

class CustomInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
	CustomInteractorStyle();
	~CustomInteractorStyle();
	
	void GetPolyData(vtkSmartPointer<vtkPolyData>);
	void GetSphere(vtkSmartPointer<vtkSphereSource>);
	void GetActor(vtkSmartPointer<vtkActor>);
	void addObserver(Observer*);
	std::vector<int> dijkstra(int startIdx, int endIdx, const TriMesh& triMesh);

protected:
	virtual void OnRightButtonDown() override;
	virtual void OnRightButtonUp() override;
	virtual void OnLeftButtonDown() override;
	virtual void OnLeftButtonUp() override;

	virtual void OnMouseWheelForward() override;
	virtual void OnMouseWheelBackward() override;

	virtual void OnKeyPress() override;

	TriMesh convertToMesh(vtkSmartPointer<vtkPolyData>);
	vtkSmartPointer<vtkPolyData> convertToPolyData(TriMesh);
	vtkSmartPointer<vtkCellArray> mCellArray;
private:
	vtkSmartPointer<vtkCamera> m_Camera;
	vtkSmartPointer<vtkPolyData> mPolyData;
	vtkSmartPointer<vtkRenderWindowInteractor> minteractor;
	vtkSmartPointer<vtkSphereSource> mSphere;
	vtkSmartPointer<vtkActor> mActor;
	vtkIdType mIdType;
	Observer* mObserver;
	vtkSmartPointer<vtkRenderer>m_Renderer;
	vtkSmartPointer<vtkPoints> mVertex;
	QHash<int, OpenMesh::Vec3d> dvertexhash;
	QHash< int, OpenMesh::Vec3d> lvertexhash;
	OpenMesh::Vec3d mLvertex;
	OpenMesh::Vec3d mEvertex;
	vtkIdList* idList;
};
