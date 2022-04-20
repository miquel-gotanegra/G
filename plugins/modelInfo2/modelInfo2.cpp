#include "modelInfo2.h"
#include "glwidget.h"


void modelInfo2::postFrame()
{
	calcInfo();
	
	QFont font;
  	font.setPixelSize(24);
  	painter.begin(glwidget());
  	painter.setFont(font);
  	int x = 15;
  	int y = 40;
  	//painter.drawText(x, y, QString("nObjects: %1").arg(nObjects));
  	//painter.drawText(x, y, QString("nObjects: %1 nPoligons: %2 nVertex %3 Percentatge de Triangles %4 %").arg(nObjects).arg(nPoligons).arg(nVertex).arg( ((nTriangles/(float)nPoligons) * 100))   ) ; 
  	
  	painter.drawText(x, y, QString("nObjects: %1").arg(nObjects));
  	painter.drawText(x, y+30, QString("nPoligons: %1").arg(nPoligons));   
  	painter.drawText(x, y+60, QString("nVertex: %1").arg(nVertex));   
  	painter.drawText(x, y+90, QString("Percentatge de Triangles %1 %").arg( ((nTriangles/(float)nPoligons) * 100)));      
  	painter.end();
	
}


void modelInfo2::calcInfo(){
	Scene* scn = scene();
	//cojemos la escena
	//
	 nObjects = 0;
	 nPoligons = 0;
	 nTriangles = 0;
	 nVertex = 0;
	
	nObjects = scn->objects().size();
	//conjunto de objetos de la escena
	
	for(int i=0; i<nObjects; ++i) {
	const Object o = scn->objects()[i];
	
	nVertex += o.vertices().size();
	nPoligons += o.faces().size();
		for(int j=0; j<(int)o.faces().size();++j){
		const Face f = o.faces()[j];
		if(f.numVertices()==3) ++nTriangles;
		}
	}
	
	
}
/*
cout << "----- INFO -----" << endl;
	cout << "nObjects= " << nObjects << endl;
	cout << "nVertex= " << nVertex << endl;
	cout << "nPoligons= " << nPoligons << endl;
	cout << "nTriangles= " << nTriangles << endl;
	cout << "Percentatge de triangles " << (nTriangles/(float)nPoligons) * 100 << "%" << endl;
	cout << endl;
	*/

