#include "ModelInfo.h"
#include "glwidget.h"


void ModelInfo::onObjectAdd()
{
	showInfo();
}

void ModelInfo::showInfo(){
	Scene* scn = scene();
	
	float nObjects = 0;
	float nPoligons = 0;
	float nTriangles = 0;
	float nVertex = 0;
	
	nObjects = scn->objects().size();
	
	for(int i=0; i<nObjects; ++i) {
	const Object o = scn->objects()[i];
	
	nVertex += o.vertices().size();
	nPoligons += o.faces().size();
		for(int j=0; j<(int)o.faces().size();++j){
		const Face f = o.faces()[j];
		if(f.numVertices()==3) ++nTriangles;
		}
	}
	cout << "----- INFO -----" << endl;
	cout << "nObjects= " << nObjects << endl;
	cout << "nVertex= " << nVertex << endl;
	cout << "nPoligons= " << nPoligons << endl;
	cout << "nTriangles= " << nTriangles << endl;
	cout << "Percentatge de triangles " << (nTriangles/(float)nPoligons) * 100 << "%" << endl;
	cout << endl;
}

void ModelInfo::onPluginLoad(){
	showInfo();
}
