#pragma once
#include "stlviewer.h"
#include "ui_stlviewer.h"
#include "CustomInteractorStyle.h"
#include <QDebug>
#include <QDebug>
#include <TriMesh.h>
#include <algorithm> 

const int PI = 3.141592;
const double thresholdA = 85.0;
const double thresholdB = 135.0;
const double alpha = 0.45;

STLViewer::STLViewer(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::STLViewer)
{

	ui->setupUi(this);
	mColorDialog = new QColorDialog();
	m_HoleFilling = new QPushButton;
	//QPushButton ColortoolButton = QPushButton("Color", this);
	mCutform = new CutForm(0);
	lightform = new LightWidgetForm(0);
	shadingform = new ShadingForm(0);
	occlusion = new Occlusion(0);

	mLight = vtkSmartPointer<vtkLight>::New();
	mLightActor = vtkSmartPointer<vtkLightActor>::New();
	mInteractor = vtkSmartPointer<QVTKInteractor>::New();
	mOutlineActor = vtkSmartPointer<vtkActor>::New();
	mcolors = vtkSmartPointer<vtkNamedColors>::New();
	mSTLReader = vtkSmartPointer<vtkSTLReader>::New();
	mMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mRenderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	mSsaoPass = vtkSmartPointer<vtkSSAOPass>::New();
	mProperty = vtkSmartPointer<vtkProperty>::New();

	connect(ui->ColortoolButton, &QPushButton::clicked, this, [this](bool) { if (mActor == nullptr) return; mColorDialog->show(); });
	connect(mColorDialog, SIGNAL(currentColorChanged(QColor)), this, SLOT(on_ColortoolButton_clicked(QColor)));
	connect(m_HoleFilling, SIGNAL(clicked()), this, SLOT(HoleFilling()));

	//light
	connect(lightform, SIGNAL(ambientValue(int)), this, SLOT(setLightAmbientChange(int)));
	connect(lightform, SIGNAL(diffuseValue(int)), this, SLOT(setLightDiffuseChange(int)));
	connect(lightform, SIGNAL(specularValue(int)), this, SLOT(setLightSpecularChange(int)));
	connect(lightform, SIGNAL(spotValue()), this, SLOT(setSpotChange()));
	connect(lightform, SIGNAL(lightX()), this, SLOT(setLightXMove()));
	connect(lightform, SIGNAL(lightY()), this, SLOT(setLightYMove()));
	connect(lightform, SIGNAL(lightZ()), this, SLOT(setLightZMove()));
	connect(lightform, SIGNAL(Intensity(int)), this, SLOT(setIntensityChange(int)));
	connect(lightform, SIGNAL(AmbientLightcolorChange()), this, SLOT(AmbientColorChange()));
	connect(lightform, SIGNAL(DiffuseLightcolorChange()), this, SLOT(DiffuseColorChange()));
	connect(lightform, SIGNAL(SpecularLightcolorChange()), this, SLOT(SpecularColorChange()));
	//texture
	connect(shadingform, SIGNAL(flatShading()), this, SLOT(SetFlatChange()));
	connect(shadingform, SIGNAL(gouraudShading()), this, SLOT(SetGouraudChange()));
	//connect(shadingform, SIGNAL(phongShading()), this, SLOT(SetPhongChange()));
	//connect(shadingform, SIGNAL(textureShading()), this, SLOT(SetTexture()));

	//occlusion
	connect(occlusion, SIGNAL(AmbientRadius(int)), this, SLOT(SetAmbientRadiusChange(int)));
	connect(occlusion, SIGNAL(AmbientBias(int)), this, SLOT(SetAmbientBiasChange(int)));
	connect(occlusion, SIGNAL(AmbientLerne(int)), this, SLOT(SetAmbientKernelSizeChange(int)));
	connect(occlusion, SIGNAL(AmbientBlur(int)), this, SLOT(SetAmbientBlurChange(int)));


	mRenderer = ui->openGLWidget->GetInteractor()->GetInteractorStyle()->GetCurrentRenderer();


}

STLViewer::~STLViewer()
{
	delete ui;
}

void STLViewer::resizeEvent(QResizeEvent* event)
{
	int height = event->size().height();
	int width = event->size().width();
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

void STLViewer::HoleFilling()
{
	if (mActor == nullptr) return;

	vtkSmartPointer<vtkPolyData> mPolyData = vtkPolyDataMapper::SafeDownCast(mActor->GetMapper())->GetInput();
	TriMesh triMesh = convertToMesh(mPolyData);

	std::vector<std::vector<TriMesh::VertexHandle> > holes;

	std::vector<int> boundaryVertex;
	std::set<TriMesh::VertexHandle> visited_vertices;
	// Iterate through all halfedges and find boundary halfedges
	for (TriMesh::HalfedgeIter he_it = triMesh.halfedges_begin(); he_it != triMesh.halfedges_end(); ++he_it)
	{

		std::vector<TriMesh::VertexHandle> hole;

		if (triMesh.is_boundary(*he_it))
		{
			// Start from the current boundary halfedge and follow the boundary
			TriMesh::VertexHandle start = triMesh.to_vertex_handle(*he_it);
			TriMesh::HalfedgeHandle current = *he_it;

			TriMesh::VertexHandle vh = triMesh.to_vertex_handle(*he_it);
			if (triMesh.is_boundary(vh))
			{
				boundaryVertex.push_back(vh.idx());
			}

			if (visited_vertices.count(start) == 0)
			{
				while (visited_vertices.count(start) == 0)
				{
					visited_vertices.insert(start);
					hole.push_back(start);
					current = triMesh.next_halfedge_handle(current);
					start = triMesh.to_vertex_handle(current);
				}
			}
			if (hole.size())
			{
				holes.push_back(hole);
			}
		}
	}

	//Print the vertex indices of the holes

	OpenMesh::Vec3d centerVertex;
	for (int i = 0; i < holes.size(); ++i)
	{
		OpenMesh::Vec3d points = { 0.0,0.0,0.0 };
		std::cout << "Hole " << i << ": ";
		for (int j = 0; j < holes[i].size(); ++j)
		{
			std::cout << holes[i][j].idx() << " ";
			cout << "points : " << triMesh.point(OpenMesh::VertexHandle(holes[i][j])) << endl;
			points += triMesh.point(OpenMesh::VertexHandle(holes[i][j]));

		}
		cout << "sum points : " << points << endl;
		cout << "holes[i].size() : " << holes[i].size() << endl;
		centerVertex = points / holes[i].size();
		cout << "centerVertex : " << centerVertex << endl << endl;

		MakeMesh(holes, centerVertex, triMesh);

		vtkNew<vtkNamedColors> colors;
		vtkNew<vtkSphereSource> sphereSource2;
		sphereSource2->SetCenter(centerVertex[0], centerVertex[1], centerVertex[2]);
		sphereSource2->SetRadius(0.1);
		// Make the surface smooth.
		sphereSource2->SetPhiResolution(100);
		sphereSource2->SetThetaResolution(100);                                                      // ���� ��ǥ���� �� ����

		vtkNew<vtkPolyDataMapper> mapper2;                                                           // ���ۿ� �� ����
		mapper2->SetInputConnection(sphereSource2->GetOutputPort());
		vtkNew<vtkActor> mActor2;                                                                    // ���Ϳ��� �� ����
		mActor2->SetMapper(mapper2);
		mActor2->GetProperty()->SetColor(colors->GetColor3d("Red").GetData());
		ui->openGLWidget->AddActor(mActor2);
	}

	// hole boundary vertex
	vtkNew<vtkNamedColors> colors;
	for (int vertexIdx : boundaryVertex)
	{
		vtkNew<vtkSphereSource> sphereSource2;
		sphereSource2->SetCenter(triMesh.point(OpenMesh::VertexHandle(vertexIdx)).data());
		sphereSource2->SetRadius(0.1);
		// Make the surface smooth.
		sphereSource2->SetPhiResolution(100);
		sphereSource2->SetThetaResolution(100);                                                      // ���� ��ǥ���� �� ����

		vtkNew<vtkPolyDataMapper> mapper2;                                                           // ���ۿ� �� ����
		mapper2->SetInputConnection(sphereSource2->GetOutputPort());
		vtkNew<vtkActor> mActor2;                                                                    // ���Ϳ��� �� ����
		mActor2->SetMapper(mapper2);
		mActor2->GetProperty()->SetColor(colors->GetColor3d("Yellow").GetData());
		ui->openGLWidget->AddActor(mActor2);
	}

}

void STLViewer::MakeMesh(std::vector<std::vector<TriMesh::VertexHandle> > holes, OpenMesh::Vec3d centerVertex, TriMesh& triMesh)
{
	OpenMesh::VertexHandle vertexHandle2 = triMesh.add_vertex(OpenMesh::Vec3d(centerVertex[0], centerVertex[1], centerVertex[2]));
	for (int i = 0; i < holes.size(); ++i)
	{
		for (int j = 0; j < holes[i].size(); ++j)
		{
			if (j == holes[i].size() - 1)
			{
				OpenMesh::VertexHandle vertexHandle0(holes[i][j]);
				OpenMesh::VertexHandle vertexHandle1(holes[i][0]);
				triMesh.add_face({ vertexHandle0, vertexHandle1, vertexHandle2 });
				vtkSmartPointer<vtkPolyData> meshToPoly = convertToPolyData(triMesh);
				vtkPolyDataMapper::SafeDownCast(mActor->GetMapper())->SetInputData(meshToPoly);
				break;
			}
			OpenMesh::VertexHandle vertexHandle0(holes[i][j]);
			OpenMesh::VertexHandle vertexHandle1(holes[i][j + 1]);

			triMesh.add_face({ vertexHandle0, vertexHandle1, vertexHandle2 });
		}
		vtkSmartPointer<vtkPolyData> meshToPoly = convertToPolyData(triMesh);
		vtkPolyDataMapper::SafeDownCast(mActor->GetMapper())->SetInputData(meshToPoly);
	}
}

TriMesh STLViewer::convertToMesh(vtkSmartPointer<vtkPolyData> polyData)
{
	int nPoints = polyData->GetNumberOfPoints();
	int nCells = polyData->GetNumberOfCells();

	TriMesh triMesh;

	for (int vertexId = 0; vertexId < nPoints; ++vertexId)
	{
		double* point = polyData->GetPoint(vertexId);
		triMesh.add_vertex(OpenMesh::Vec3d(point[0], point[1], point[2]));
	}

	for (int cellId = 0; cellId < nCells; ++cellId)
	{
		int vertexId0 = polyData->GetCell(cellId)->GetPointIds()->GetId(0);
		int vertexId1 = polyData->GetCell(cellId)->GetPointIds()->GetId(1);
		int vertexId2 = polyData->GetCell(cellId)->GetPointIds()->GetId(2);

		OpenMesh::VertexHandle vertexHandle0(vertexId0);
		OpenMesh::VertexHandle vertexHandle1(vertexId1);
		OpenMesh::VertexHandle vertexHandle2(vertexId2);
		triMesh.add_face({ vertexHandle0, vertexHandle1, vertexHandle2 });
	}
	qDebug("Completed Conver To Mesh");
	return triMesh;
}

vtkSmartPointer<vtkPolyData> STLViewer::convertToPolyData(TriMesh triMesh)
{
	vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();

	vtkSmartPointer<vtkPoints>   points = vtkSmartPointer<vtkPoints>::New();
	int vid = 0;
	for (TriMesh::VertexIter vertexItr = triMesh.vertices_begin(); vertexItr != triMesh.vertices_end(); ++vertexItr, ++vid)
	{
		OpenMesh::Vec3d from = triMesh.point(*vertexItr);
		double* coords = from.data();

		while (vid < vertexItr->idx())
		{
			vid++; points->InsertNextPoint(0, 0, 0);
		}
		points->InsertNextPoint(coords[0], coords[1], coords[2]);
	}
	polyData->SetPoints(points);

	vtkSmartPointer<vtkCellArray> cellArray = vtkSmartPointer<vtkCellArray>::New();
	for (TriMesh::FaceIter faceItr = triMesh.faces_begin(); faceItr != triMesh.faces_end(); ++faceItr)
	{
		TriMesh::FaceVertexIter   faceVertexItr;
		faceVertexItr = triMesh.cfv_iter(*faceItr);
		int   v0 = (faceVertexItr++).handle().idx();
		int   v1 = (faceVertexItr++).handle().idx();
		int   v2 = faceVertexItr.handle().idx();

		vtkSmartPointer<vtkTriangle> triangle = vtkSmartPointer<vtkTriangle>::New();
		triangle->GetPointIds()->SetId(0, v0);
		triangle->GetPointIds()->SetId(1, v1);
		triangle->GetPointIds()->SetId(2, v2);
		cellArray->InsertNextCell(triangle);
	}

	polyData->SetPolys(cellArray);
	polyData->Modified();

	return polyData;
}

void STLViewer::on_CuttoolButton_clicked()
{
	mCutform->show();
	mCutform->setWindowFlag(Qt::WindowStaysOnTopHint);
}


void STLViewer::on_FillingtoolButton_clicked()
{
	if (mActor == nullptr) return;
	vtkNew<vtkNamedColors> colors;

	vtkSmartPointer<vtkPolyData> mPolyData = vtkPolyDataMapper::SafeDownCast(mActor->GetMapper())->GetInput();
	TriMesh triMesh = convertToMesh(mPolyData);

	AdvancingFrontMethod(triMesh);
}


void STLViewer::on_OpacitytoolButton_clicked()
{

}


void STLViewer::on_LighttoolButton_clicked()
{
	int width = ui->openGLWidget->sizeHint().width();
	int height = ui->openGLWidget->sizeHint().height();

	lightform->setWindowFlag(Qt::WindowStaysOnTopHint);
	lightform->show();
	//    lightform->setGeometry(width,height,10,10);
	qDebug() << "light" << lightform->geometry();


}


void STLViewer::on_ShadingtoolButton_clicked()
{
	shadingform->setWindowFlag(Qt::WindowStaysOnTopHint);
	shadingform->show();
}


void STLViewer::on_ColortoolButton_clicked(QColor color)
{
	double r = color.toRgb().redF();
	double g = color.toRgb().greenF();
	double b = color.toRgb().blueF();
	mActor->GetProperty()->SetDiffuseColor(r, g, b);
	mActor->Modified();
	ui->openGLWidget->GetRenderWindow()->Render();
}

void STLViewer::on_BoxtoolButton_clicked()
{
	vtkSmartPointer<vtkOutlineFilter> outlineFilter =
		vtkSmartPointer<vtkOutlineFilter>::New();
	outlineFilter->SetInputConnection(mSTLReader->GetOutputPort());

	vtkSmartPointer<vtkPolyDataMapper> outLinemapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	outLinemapper->SetInputConnection(outlineFilter->GetOutputPort());

	mOutlineActor->SetMapper(outLinemapper);
	mOutlineActor->GetProperty()->SetColor(1, 1, 1);
	// --------------------- Drawing bounding box end------------------------ 
	ui->openGLWidget->AddActor(mOutlineActor);
}

void STLViewer::on_VertextoolButton_clicked()
{
	vtkNew<vtkNamedColors> colors;
	vtkNew<vtkSphereSource> sphereSource;
	sphereSource->SetRadius(0.1);
	sphereSource->SetPhiResolution(1);
	sphereSource->SetThetaResolution(1);
	vtkSmartPointer<vtkGlyph3D> glyph3D = vtkSmartPointer<vtkGlyph3D>::New();
	glyph3D->SetSourceConnection(sphereSource->GetOutputPort());
	glyph3D->SetInputData(mPolyData);
	glyph3D->SetScaleModeToScaleByScalar();
	vtkSmartPointer<vtkPolyDataMapper> glyphMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	glyphMapper->SetInputConnection(glyph3D->GetOutputPort());
	vtkSmartPointer<vtkActor> glyphActor = vtkSmartPointer<vtkActor>::New();
	glyphActor->SetMapper(glyphMapper);
	glyphActor->GetProperty()->SetPointSize(1);
	glyphActor->GetProperty()->SetColor(colors->GetColor3d("Yellow").GetData());
	ui->openGLWidget->AddActor(glyphActor);
	for (TriMesh::VertexIter v_it = mTriMesh.vertices_begin(); v_it != mTriMesh.vertices_end(); ++v_it)
	{
		glyph3D->SetScaleFactor(1);
		glyph3D->Update();
	}
}

void STLViewer::on_WiretoolButton_clicked()
{
}

void STLViewer::on_AxistoolButton_clicked()
{
}


void STLViewer::on_OpentoolButton_clicked()
{
	qDebug("Triggered Open Button");
	std::string fileName = QFileDialog::getOpenFileName(nullptr,
		"STL Files", "/home", "STL Files (*.stl)").toStdString().c_str();

	// STL Reader
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
	ui->openGLWidget->GetInteractor()->GetInteractorStyle()->GetCurrentRenderer()->ResetCamera();
	ui->openGLWidget->GetRenderWindow()->Render();

	//ui->openGLWidget->GetPolyData(polyData);
	qDebug() << "Actor" << mActor;
	qDebug() << "PolyData" << polyData;

	vtkSmartPointer<vtkPolyData> mPolyData = vtkPolyDataMapper::SafeDownCast(mActor->GetMapper())->GetInput();
	mTriMesh = convertToMesh(mPolyData);
}


void STLViewer::on_SavetoolButton_clicked()
{
	mTriMesh.request_vertex_normals();
	mTriMesh.request_face_normals();
	mTriMesh.update_normals();
	mTriMesh.release_vertex_normals();
	mTriMesh.release_face_normals();
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

		return;
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

	writer->SetInputData(mMeshToPoly);

	writer->SetFileTypeToBinary(); // 바이너리 파일로 저장
	writer->Write();

	QMessageBox::warning(this, "", "Success!.");

	//msgBox.setText("File save!!");
}

std::vector<std::vector<TriMesh::VertexHandle>> STLViewer::FindHoleVertex(TriMesh& triMesh)
{
	std::vector<std::vector<TriMesh::VertexHandle> > holes;
	std::vector<int> boundaryVertex;
	std::set<TriMesh::VertexHandle> visited_vertices;
	// Iterate through all halfedges and find boundary halfedges

	for (TriMesh::HalfedgeIter he_it = triMesh.halfedges_begin(); he_it != triMesh.halfedges_end(); ++he_it)
	{
		std::vector<TriMesh::VertexHandle> hole;

		if (triMesh.is_boundary(*he_it))
		{
			// Start from the current boundary halfedge and follow the boundary
			TriMesh::VertexHandle start = triMesh.to_vertex_handle(*he_it);
			TriMesh::HalfedgeHandle current = *he_it;

			TriMesh::VertexHandle vh = triMesh.to_vertex_handle(*he_it);
			if (triMesh.is_boundary(vh))
			{
				boundaryVertex.push_back(vh.idx());
			}

			if (visited_vertices.count(start) == 0)
			{
				while (visited_vertices.count(start) == 0)
				{
					visited_vertices.insert(start);
					hole.push_back(start);
					current = triMesh.next_halfedge_handle(current);
					start = triMesh.to_vertex_handle(current);
				}
			}
			if (hole.size())
			{
				holes.push_back(hole);
			}
		}
	}
	return holes;
}

void STLViewer::AdvancingFrontMethod(TriMesh& triMesh)
{
	//for (int i = 0 ; i < 100 ; i++)
	//{
	vtkNew<vtkNamedColors> colors;
	triMesh.request_vertex_normals();
	triMesh.request_face_normals();
	triMesh.update_normals();
	triMesh.release_vertex_normals();
	triMesh.release_face_normals();
	std::vector<std::vector<TriMesh::VertexHandle> > holes;
	holes = FindHoleVertex(triMesh);

	for (int i = 0; i < holes.size(); i++)
	{
		std::vector<std::pair<int, int>> linkedVertex(triMesh.n_vertices(), { -1, -1 });
		std::unordered_map<int, OpenMesh::Vec3d> vertexNormalMap;
		OpenMesh::Vec3d firstVertex = { 0.0,0.0,0.0, };
		OpenMesh::Vec3d secondVertex = { 0.0,0.0,0.0, };
		OpenMesh::Vec3d thirdVertex = { 0.0,0.0,0.0, };

		double min = 360.0;
		double minAngle = 360.0;
		TriMesh::VertexHandle minIdx;

		OpenMesh::Vec3d prevVertex = { 0,0,0 };
		OpenMesh::Vec3d currentVertex = { 0,0,0 };
		OpenMesh::Vec3d nextVertex = { 0,0,0 };
		int count = 0;

		for (int j = 0; j < holes[i].size(); j++)
		{
			if (j == 0)
			{
				prevVertex = triMesh.point(holes[i].back());
				currentVertex = triMesh.point(holes[i][j]);
				nextVertex = triMesh.point(holes[i][j + 1]);

				linkedVertex[holes[i][j].idx()].first = holes[i].back().idx();
				linkedVertex[holes[i][j].idx()].second = holes[i][j + 1].idx();
			}
			else if (j == holes[i].size() - 1)
			{
				prevVertex = triMesh.point(holes[i][j - 1]);
				currentVertex = triMesh.point(holes[i][j]);
				nextVertex = triMesh.point(holes[i].front());

				linkedVertex[holes[i][j].idx()].first = holes[i][j - 1].idx();
				linkedVertex[holes[i][j].idx()].second = holes[i].front().idx();
			}
			else
			{
				prevVertex = triMesh.point(holes[i][j - 1]);
				currentVertex = triMesh.point(holes[i][j]);
				nextVertex = triMesh.point(holes[i][j + 1]);

				linkedVertex[holes[i][j].idx()].first = holes[i][j - 1].idx();
				linkedVertex[holes[i][j].idx()].second = holes[i][j + 1].idx();
			}

			OpenMesh::Vec3d currentNextVertex;
			OpenMesh::Vec3d currentPrevVertex;
			currentNextVertex = nextVertex - currentVertex;
			currentPrevVertex = prevVertex - currentVertex;

			// dot product
			double dotProduct = 0.0;
			double currentNextMagnitude = 0.0;
			double currentPrevMagnitude = 0.0;
			double radian = 0.0;

			dotProduct = (currentNextVertex[0] * currentPrevVertex[0]) + (currentNextVertex[1] * currentPrevVertex[1]) + (currentNextVertex[2] * currentPrevVertex[2]);
			currentNextMagnitude = sqrt((currentNextVertex[0] * currentNextVertex[0]) + (currentNextVertex[1] * currentNextVertex[1]) + (currentNextVertex[2] * currentNextVertex[2]));
			currentPrevMagnitude = sqrt((currentPrevVertex[0] * currentPrevVertex[0]) + (currentPrevVertex[1] * currentPrevVertex[1]) + (currentPrevVertex[2] * currentPrevVertex[2]));

			//cout << "dotProduct : " << dotProduct << endl;
			//cout << "(currentNextMagnitude * currentNextMagnitude) : " << (currentNextMagnitude * currentNextMagnitude) << endl;

			radian = acos(dotProduct / (currentNextMagnitude * currentPrevMagnitude));
			double angle = (radian * 180) / PI;
			double frontAngle = 0.0;
			//cout << "frontAngle : " << frontAngle << endl;
			double vectorAngle = 0.0;

			for (TriMesh::VertexEdgeIter ve_it = triMesh.ve_iter(holes[i][j]); ve_it.is_valid(); ++ve_it, count++)
			{
				if (count > 0)
				{
					TriMesh::HalfedgeHandle heh = ve_it.current_halfedge_handle();
					firstVertex = triMesh.point(holes[i][j]);
					secondVertex = triMesh.point(triMesh.to_vertex_handle(heh));

					TriMesh::HalfedgeHandle nextHeh = triMesh.next_halfedge_handle(heh);
					thirdVertex = triMesh.point(triMesh.to_vertex_handle(nextHeh));

					OpenMesh::Vec3d firstVec;
					OpenMesh::Vec3d secondVec;
					firstVec = secondVertex - firstVertex;
					secondVec = thirdVertex - firstVertex;

					// dot product
					double dotProduct = 0.0;
					double firstVecMagnitude = 0.0;
					double secondVecMagnitude = 0.0;
					double theta = 0.0;

					dotProduct = (firstVec[0] * secondVec[0]) + (firstVec[1] * secondVec[1]) + (firstVec[2] * secondVec[2]);
					firstVecMagnitude = sqrt((firstVec[0] * firstVec[0]) + (firstVec[1] * firstVec[1]) + (firstVec[2] * firstVec[2]));
					secondVecMagnitude = sqrt((secondVec[0] * secondVec[0]) + (secondVec[1] * secondVec[1]) + (secondVec[2] * secondVec[2]));

					theta = acos(dotProduct / (firstVecMagnitude * secondVecMagnitude));
					double angle = (theta * 180) / PI;
					vectorAngle += angle;
				}
			}

			if (vectorAngle > 180)
			{
				frontAngle = angle;
			}
			else
			{
				continue;
			}

			min = (min > frontAngle) ? frontAngle : min;
			if (min == frontAngle)
			{
				minAngle = min;
				minIdx = holes[i][j];
			}
			vectorAngle = 0.0;
		}

		/*
		각도에 따른 메쉬 홀 필링
		*/
		if (minAngle <= thresholdA)  // 0 < angle <= 85
		{
			OpenMesh::VertexHandle vertexHandle0(linkedVertex[minIdx.idx()].first);
			OpenMesh::VertexHandle vertexHandle1(minIdx);
			OpenMesh::VertexHandle vertexHandle2(linkedVertex[minIdx.idx()].second);
			triMesh.add_face({ vertexHandle0, vertexHandle1, vertexHandle2 });
			vtkSmartPointer<vtkPolyData> meshToPoly = convertToPolyData(triMesh);
			vtkPolyDataMapper::SafeDownCast(mActor->GetMapper())->SetInputData(meshToPoly);
			linkedVertex.clear();
		}
		else if (minAngle > thresholdA && minAngle <= thresholdB) // 85 < angle < 135
		{
			OpenMesh::VertexHandle prevVertexHandle(linkedVertex[minIdx.idx()].first);
			OpenMesh::VertexHandle currentVertexHandle(minIdx);
			OpenMesh::VertexHandle nextVertexHandle(linkedVertex[minIdx.idx()].second);

			OpenMesh::Vec3d firstVector;
			OpenMesh::Vec3d secondVector;

			firstVector = triMesh.point(prevVertexHandle) - triMesh.point(currentVertexHandle);
			secondVector = triMesh.point(nextVertexHandle) - triMesh.point(currentVertexHandle);

			OpenMesh::Vec3d bisectorVector;
			bisectorVector = (firstVector.normalize() + secondVector.normalize()).normalize();

			TriMesh::Normal vNormal = { 0.0,0.0,0.0 };
			vNormal = triMesh.calc_vertex_normal(minIdx);


			OpenMesh::Vec3d ppVector;
			OpenMesh::Vec3d pVector;
			ppVector = bisectorVector - ((bisectorVector.dot(vNormal)) * vNormal);
			pVector = ppVector / ppVector.norm();

			OpenMesh::Vec3d pNormal;
			pNormal = vNormal + (alpha * abs(vNormal.dot(bisectorVector)) * bisectorVector);
			pNormal = pNormal / pNormal.norm();

			double nnTheta = 0.0;
			nnTheta = acos(vNormal.dot(pNormal));
			double k = (cos(nnTheta) - 1) / pNormal.dot(pVector);

			OpenMesh::Vec3d delta = { 0.0,0.0,0.0 };
			int weight = 0;
			for (OpenMesh::VertexHandle neighbor : triMesh.vv_range(minIdx))
			{
				weight += 1;
			}
			for (OpenMesh::VertexHandle neighbor : triMesh.vv_range(minIdx))
			{
				delta += ((1 / weight) * triMesh.point(neighbor)) - triMesh.point(minIdx);
			}
			OpenMesh::Vec3d BVector = { 0,0,0 };
			double checkCon = 0.0;

			//delta = delta / weight; 
			checkCon = vNormal.dot(delta);
			if (checkCon <= 0)          // convex (볼록)
			{
				BVector = (pVector + (k * pNormal)) / (pVector + (k * pNormal)).norm();
			}
			else                        // concave (오목)
			{
				BVector = (pVector - (k * pNormal)) / (pVector - (k * pNormal)).norm();
			}

			OpenMesh::Vec3d newVector = { 0.0,0.0,0.0 };
			firstVector; // v1
			secondVector; // v2  
			newVector = triMesh.point(currentVertexHandle) + ((firstVector + secondVector).norm() / 2) * BVector;
			OpenMesh::VertexHandle vertexHandle0(linkedVertex[minIdx.idx()].first);
			OpenMesh::VertexHandle vertexHandle1(minIdx);
			OpenMesh::VertexHandle vertexHandle2(linkedVertex[minIdx.idx()].second);
			OpenMesh::VertexHandle newVertexHandle = triMesh.add_vertex(newVector);
			triMesh.add_face({ newVertexHandle, vertexHandle1, vertexHandle2 });
			triMesh.add_face({ newVertexHandle, vertexHandle0, vertexHandle1 });
			vtkSmartPointer<vtkPolyData> meshToPoly = convertToPolyData(triMesh);
			vtkPolyDataMapper::SafeDownCast(mActor->GetMapper())->SetInputData(meshToPoly);

			linkedVertex.clear();

		}
		else if (minAngle > thresholdB && minAngle <= 180) // 135 < angle < 180
		{

		}
	}

}

void STLViewer::setLightAmbientChange(int ambient)
{
	qDebug() << "SetLightChange";
	if (mActor != NULL)
	{
		mActor->GetProperty()->SetAmbient(ambient / 100.0);
		mActor->Modified();
		ui->openGLWidget->GetRenderWindow()->Render();
	}
}

void STLViewer::setLightDiffuseChange(int diffuse)
{
	qDebug() << "SetLightDiffuseChange";
	if (mActor != NULL)
	{
		mActor->GetProperty()->SetDiffuse(diffuse / 100.0);
		mActor->Modified();
		ui->openGLWidget->GetRenderWindow()->Render();
	}
}

void STLViewer::setLightSpecularChange(int Specular)
{
	qDebug() << "SetLightSpeclarChange";
	if (mActor != NULL)
	{
		mActor->GetProperty()->SetSpecular(Specular / 100.0);
		mActor->Modified();
		ui->openGLWidget->GetRenderWindow()->Render();
	}
}
void STLViewer::setSpotChange()
{
	QColor color = mColorDialog->getColor(); // 색 설정을 위한 colorDialog
	double r = color.toRgb().redF();
	double g = color.toRgb().greenF();
	double b = color.toRgb().blueF();

	//mLight->SetConeAngle(0.3); // 콘의 각도
   // LightActor->GetConeProperty()->SetColor(r, g, b);

 //   mLight->SetLightTypeToCameraLight();
	mLight->SetPositional(true);
	mLight->SetLightTypeToCameraLight();
	//mLight->SetColor(mcolors->GetColor3d("Magenta").GetData());
	mLight->SetColor(r, g, b);
	mLight->PositionalOn();

	mLightActor->SetLight(mLight);

	//mActor->GetProperty()->SetAmbient(ambient);
	//mActor->GetProperty()->SetDiffuse(diffuse);
	//mActor->GetProperty()->SetSpecular(specular);
	//mActor->GetProperty()->SetSpecularPower(specularpower);
	//mActor->GetProperty()->SetSpecularColor(r, g, b);

	//mActor->AddPosition(position.data());

	qDebug() << "mLight" << mLight;
	mRenderer->AddLight(mLight);
	mRenderer->AddViewProp(mLightActor);

	ui->openGLWidget->GetRenderWindow()->Render();

}

void STLViewer::AmbientColorChange()
{
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
	mLight->SetLightTypeToSceneLight();

	mLight->SetAmbientColor(r, g, b);
	mActor->GetProperty()->SetAmbientColor(r, g, b);
	mActor->GetProperty()->SetAmbient(ambient);
	mActor->GetProperty()->SetDiffuse(diffuse);
	mActor->GetProperty()->SetSpecular(specular);
	mActor->GetProperty()->SetSpecularPower(specularpower);

	qDebug() << "mLight" << mLight;
	mRenderer->AddLight(mLight);
	mRenderer->AddActor(mActor);
	mRenderer->SetAmbient(0.5, 0.5, 0.5);

	mRenderer->Render();
	mInteractor->Start();
	ui->openGLWidget->GetRenderWindow()->Render();
}

void STLViewer::DiffuseColorChange()
{
	QColor color = mColorDialog->getColor(); // 색 설정을 위한 colorDialog
	double r = color.toRgb().redF();
	double g = color.toRgb().greenF();
	double b = color.toRgb().blueF();

	mLight->SetLightTypeToCameraLight(); // 카메라 시점에 따라 빛 이동

	//mLight->SetPosition(0, 0, 5);
	mLight->SetDiffuseColor(r, g, b); //색 정보를 받아 온다
	mRenderer->AddLight(mLight);
	mInteractor->Start();
	ui->openGLWidget->GetRenderWindow()->Render();
}

void STLViewer::SpecularColorChange()
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

	mLight->SetPositional(true);
	mLight->SetLightTypeToSceneLight();
	mLight->SetFocalPoint(0, 0, 0);

	mLightActor->SetLight(mLight);

	mActor->GetProperty()->SetAmbient(ambient);
	mActor->GetProperty()->SetDiffuse(diffuse);
	mActor->GetProperty()->SetSpecular(specular);
	mActor->GetProperty()->SetSpecularPower(specularpower);
	mActor->GetProperty()->SetSpecularColor(r, g, b);

	//mActor->AddPosition(position.data());

	qDebug() << "mLight" << mLight;
	mRenderer->AddLight(mLight);
	mRenderer->AddViewProp(mLightActor);
	ui->openGLWidget->GetInteractor()->GetInteractorStyle()->GetCurrentRenderer()->AddViewProp(mLightActor);
	ui->openGLWidget->GetRenderWindow()->Render();
	mInteractor->Start();
}

void STLViewer::setLightXMove()
{
	qDebug() << "LightMove";

	double max = 0;
	double bound = 0;
	for (int i = 0; i < 6; i++)
	{
		// cout << "i : " << abs(outlineActor->GetBounds()[i]) << endl;
		max = (max < abs(mOutlineActor->GetBounds()[i])) ? abs(mOutlineActor->GetBounds()[i]) : max;
		if (max == abs(mOutlineActor->GetBounds()[i]))
		{
			bound = abs(max);
		}
	}

	mOutlineActor->GetCenter();

	mLight->SetPosition(mOutlineActor->GetCenter()[0] + abs(mOutlineActor->GetBounds()[1] + 10.0), mOutlineActor->GetCenter()[1], mOutlineActor->GetCenter()[2]);

	mLight->SetFocalPoint(mActor->GetPosition());
	mLight->SetColor(mcolors->GetColor3d("Magenta").GetData());
	mLight->PositionalOn();
	mRenderer->AddLight(mLight);
	mLight->SwitchOn();

	mLight->SetConeAngle(10);
	mLightActor->SetLight(mLight);
	mRenderer->AddViewProp(mLightActor);
	ui->openGLWidget->GetRenderWindow()->Render();
}

void STLViewer::setLightYMove()
{
	qDebug() << "LightMove";

	double max = 0;
	double bound = 0;
	for (int i = 0; i < 6; i++)
	{
		// cout << "i : " << abs(outlineActor->GetBounds()[i]) << endl;
		max = (max < abs(mOutlineActor->GetBounds()[i])) ? abs(mOutlineActor->GetBounds()[i]) : max;
		if (max == abs(mOutlineActor->GetBounds()[i]))
		{
			bound = abs(max);
		}
	}
	//cout << "max :" << abs(max) << endl;

	mOutlineActor->GetCenter();

	mLight->SetPosition(mOutlineActor->GetCenter()[0], mOutlineActor->GetCenter()[1] + abs(mOutlineActor->GetBounds()[3] + 10.0),
		mOutlineActor->GetCenter()[2]);


	// mLight->SetPosition(0, 0, 1);
	mLight->SetFocalPoint(mActor->GetPosition());
	mLight->SetColor(mcolors->GetColor3d("Magenta").GetData());
	mLight->PositionalOn();
	mRenderer->AddLight(mLight);
	mLight->SwitchOn();

	mLight->SetConeAngle(10);
	mLightActor->SetLight(mLight);
	mRenderer->AddViewProp(mLightActor);
	ui->openGLWidget->GetRenderWindow()->Render();
}

void STLViewer::setLightZMove()
{
	qDebug() << "LightMove";
	double max = 0;
	double bound = 0;
	for (int i = 0; i < 6; i++)
	{

		max = (max < abs(mOutlineActor->GetBounds()[i])) ? abs(mOutlineActor->GetBounds()[i]) : max;
		if (max == abs(mOutlineActor->GetBounds()[i]))
		{
			bound = abs(max);
		}
	}


	mOutlineActor->GetCenter();
	mLight->SetPosition(mOutlineActor->GetCenter()[0], mOutlineActor->GetCenter()[1],
		mOutlineActor->GetCenter()[2] + abs(mOutlineActor->GetBounds()[5] + 10.0));

	mLight->SetFocalPoint(mActor->GetPosition());
	mLight->SetColor(mcolors->GetColor3d("Magenta").GetData());
	mLight->PositionalOn();

	mRenderer->AddLight(mLight);
	mLight->SwitchOn();
	mLight->SetConeAngle(10);
	mLightActor->SetLight(mLight);
	mRenderer->AddViewProp(mLightActor);
	ui->openGLWidget->GetRenderWindow()->Render();
}

void STLViewer::setIntensityChange(int intensity)
{
	qDebug() << "ConAngleChange";
	if (mActor != NULL)
	{
		//mActor->GetProperty()->SetAngle(intensity);
		mLight->SetConeAngle(intensity / 100.0);
		// mActor->Modified();
		ui->openGLWidget->GetRenderWindow()->Render();
	}

}

void STLViewer::SetFlatChange()
{
	qDebug() << "Flat";

	mMapper->SetInputConnection(mSTLReader->GetOutputPort());
	mMapper->SetScalarVisibility(0);

	mActor->SetMapper(mMapper);
	mActor->GetProperty()->SetInterpolationToFlat();

	//mRenderer->AddActor(mActor);
	//mRenderWindow->AddRenderer(mRenderer);
	//mInteractor->SetRenderWindow(mRenderWindow);

	ui->openGLWidget->GetRenderWindow()->Render();
}

void STLViewer::SetGouraudChange()
{
	qDebug() << "Gour";
	vtkSmartPointer<vtkPolyDataNormals> normalGenerator =
		vtkSmartPointer<vtkPolyDataNormals>::New();
	normalGenerator->SetInputConnection(mSTLReader->GetOutputPort());
	normalGenerator->ComputePointNormalsOn();
	normalGenerator->ComputeCellNormalsOff();
	normalGenerator->SetFeatureAngle(60.0);
	normalGenerator->Update();

	mMapper->SetInputConnection(normalGenerator->GetOutputPort());
	mActor->SetMapper(mMapper);
	mActor->GetProperty()->SetInterpolationToGouraud();

	// vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();
	/* mLight->SetPosition(1, 1, 1);
	 mLight->SetColor(1, 1, 1);
	 mRenderer->AddLight(mLight);*/

	vtkSmartPointer<vtkCamera> camera =
		vtkSmartPointer<vtkCamera>::New();
	camera->SetPosition(0, 0, 30);
	camera->SetFocalPoint(0, 0, 0);
	camera->SetViewUp(0, 1, 0);
	camera->Azimuth(30);
	camera->Elevation(30);

	mRenderer->AddActor(mActor);
	mRenderWindow->AddRenderer(mRenderer);
	mInteractor->SetRenderWindow(mRenderWindow);

	ui->openGLWidget->GetRenderWindow()->Render();
	mInteractor->Start();
}

//void STLViewer::SetPhongChange()
//{
//    qDebug() << "Phong";
//    /*mActor->GetProperty()->SetSpecularPower(0.3);*/
//
//    vtkSmartPointer<vtkPolyDataNormals> normalGenerator = // 다각형 메시에 대한 법선 계산을 위해서 사용
//        vtkSmartPointer<vtkPolyDataNormals>::New();
//    normalGenerator->SetInputConnection(mSTLReader->GetOutputPort());
//    normalGenerator->ComputePointNormalsOn(); //접 번선 계산을 킨다.
//    normalGenerator->ComputeCellNormalsOff(); //셀 법선 계산을 끈다
//    normalGenerator->SetFeatureAngle(60.0); // 각도를 지정한다.
//    normalGenerator->Update();
//
//    mMapper->SetInputConnection(normalGenerator->GetOutputPort());
//    mActor->SetMapper(mMapper);
//    mActor->GetProperty()->SetInterpolationToPhong();
//
//
//
//    mRenderer->AddActor(mActor);
//    mRenderWindow->AddRenderer(mRenderer);
//    mInteractor->SetRenderWindow(mRenderWindow);
//
//
//    ui->openGLWidget->GetRenderWindow()->Render();
//    mInteractor->Start();
//}

//void STLViewer::SetTexture()
//{
//    qDebug() << "SetTexture";
//
//    std::string fileName = QFileDialog::getOpenFileName(nullptr,
//        "PNG Files", "/home", "png Files (*.png)").toStdString().c_str();
//
//    vtkSmartPointer<vtkPNGReader> pngReader =
//        vtkSmartPointer<vtkPNGReader>::New();
//    pngReader->SetFileName(fileName.c_str());
//    pngReader->Update();
//    qDebug() << "pngRender" << pngReader->GetFileName();
//
//    mPolyData->DeepCopy(pngReader->GetOutput());
//    mMapper->SetInputData(mPolyData);
//    mMapper->SetInputConnection(pngReader->GetOutputPort()); //
//    qDebug() << "m_polyData" << mPolyData;
//
//    vtkSmartPointer<vtkTexture> mTexture =
//        vtkSmartPointer<vtkTexture>::New();
//
//    qDebug() << "m_Texture" << mTexture->GetTextureUnit();
//    mTexture->SetInputConnection(pngReader->GetOutputPort());
//
//    mTexture->InterpolateOn(); // 선형 보간을 킨다.
//
//    qDebug() << "MaxFiltering" << mTexture->GetMaximumAnisotropicFiltering();
//
//    vtkSmartPointer<vtkTextureMapToSphere> textureMapToSphere = // 한개의 png 파일을 입히기 
//        vtkSmartPointer<vtkTextureMapToSphere>::New();
//
//    textureMapToSphere->SetInputData(mPolyData);
//    textureMapToSphere->SetInputConnection(mSTLReader->GetOutputPort());
//    textureMapToSphere->Update();
//    textureMapToSphere->PreventSeamOn();
//    textureMapToSphere->SetAutomaticSphereGeneration(1);
//
//    mMapper->SetInputConnection(textureMapToSphere->GetOutputPort());
//    mActor->SetMapper(mMapper);
//    mActor->SetTexture(mTexture);
//
//    qDebug() << "texture" << mTexture;
//    mRenderer->AddActor(mActor);
//    mRenderer->UseDepthPeelingOn(); // texture 투명도 해결을 위한 방법
//    mRenderWindow->SetAlphaBitPlanes(1); //texture 투명도 해결을 위해 설정
//    mRenderWindow->SetMultiSamples(0);     //texture 투명도 해결을 위해 설정
//    mRenderWindow->AddRenderer(mRenderer);
//    mInteractor->SetRenderWindow(mRenderWindow);
//
//    ui->openGLWidget->GetRenderWindow()->Render();
//    /* m_Interactor->Start();*/
//    mPolyData = mActor->GetProperty();
//    qDebug() << "m_OrigninProp" << mPolyData;
//}

void STLViewer::SetAmbientRadiusChange(int radius)
{
	qDebug() << "Radius";
	if (mActor != NULL)
	{
		mSsaoPass->SetRadius(radius / 100.0);
		mRenderer->SetPass(mSsaoPass);
		// mActor->Modified();
		ui->openGLWidget->GetRenderWindow()->Render();
	}
}

void STLViewer::SetAmbientBiasChange(int bias)
{
	qDebug() << "Bias";
	if (mActor != NULL)
	{
		// mActor->GetProperty()->SetAngle(Angle);
		mSsaoPass->SetBias(bias / 100.0);
		mRenderer->SetPass(mSsaoPass); //
		//ssao->SetDelegatePass(basicPasses);
	  // mActor->Modified();
		ui->openGLWidget->GetRenderWindow()->Render();
	}
}

void STLViewer::SetAmbientKernelSizeChange(int kernelSize)
{
	qDebug() << "Kernel";
	if (mActor != NULL)
	{
		// mActor->GetProperty()->SetAngle(Angle);
		mSsaoPass->SetKernelSize(kernelSize);
		mRenderer->SetPass(mSsaoPass); //
		ui->openGLWidget->GetRenderWindow()->Render();
	}
}
void STLViewer::SetAmbientBlurChange(int Blur)
{
	qDebug() << "Blur";
	if (mActor != NULL)
	{
		// mActor->GetProperty()->SetAngle(Angle);
		mSsaoPass->SetBlur(true);
		mRenderer->SetPass(mSsaoPass); //
		// mActor->Modified();
		ui->openGLWidget->GetRenderWindow()->Render();
	}
}