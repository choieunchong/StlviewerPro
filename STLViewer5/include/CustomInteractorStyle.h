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
#include <vtkDijkstraGraphGeodesicPath.h> //Dijkstra
#include <vtkMutableDirectedGraph.h>
#include <vtkVector.h>
#include <vtkGraphToPolyData.h>
#include <vector>
#include <queue>
#include <QHash>
#include <vtkIdList.h>
<<<<<<< HEAD
#include <vtkLight.h>
=======
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
#include <vtkCamera.h>
#include <vtkLight.h>
#include <vtkRenderWindow.h>

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
<<<<<<< HEAD

=======
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
	virtual void OnMouseWheelForward() override;
	virtual void OnMouseWheelBackward() override;

	virtual void OnKeyPress() override;

<<<<<<< HEAD
=======


>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
	TriMesh convertToMesh(vtkSmartPointer<vtkPolyData>);
	vtkSmartPointer<vtkPolyData> convertToPolyData(TriMesh);
	vtkSmartPointer<vtkCellArray> mCellArray;
private:
<<<<<<< HEAD
	vtkSmartPointer<vtkLight> m_Light;
	vtkSmartPointer<vtkCamera> m_Camera;
	vtkSmartPointer<vtkPolyData> mPolyData;
	vtkSmartPointer<vtkSphereSource> mSphere;
	vtkSmartPointer<vtkActor> mActor;
	vtkIdType mIdType;
	Observer* mObserver;
	vtkSmartPointer<vtkRenderer>m_Renderer;
	vtkSmartPointer<vtkPoints> mVertex;
=======
	vtkSmartPointer<vtkPolyData> mPolyData;
	vtkSmartPointer<vtkSphereSource> mSphere;
	vtkSmartPointer<vtkActor> mActor;
	vtkSmartPointer<vtkCamera> m_Camera;
	vtkSmartPointer<vtkLight> m_Light;
	//vtkSmartPointer<vtkRenderWindow> m_RendererWindow;

	vtkIdType mIdType;
	Observer* mObserver;
	vtkSmartPointer<vtkPoints> mVertex;
	vtkSmartPointer<vtkRenderer>m_Renderer;
>>>>>>> 5d342e87858d7bbe42f81d7e8a0016ccc961c088
	QHash<int, OpenMesh::Vec3d> dvertexhash;
	QHash< int, OpenMesh::Vec3d> lvertexhash;
	OpenMesh::Vec3d mLvertex;
	OpenMesh::Vec3d mEvertex;
	vtkIdList* idList;
};
