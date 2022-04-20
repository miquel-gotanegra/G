#include "showDegree.h"
#include "glwidget.h"


void showDegree::postFrame()
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
  	
  	painter.drawText(x, y, QString("mDegree: %1").arg(Mdegree));
  	//painter.drawText(x, y+30, QString("nPoligons: %1").arg(nPoligons));   
  	//painter.drawText(x, y+60, QString("nVertex: %1").arg(nVertex));   
  	//painter.drawText(x, y+90, QString("Percentatge de Triangles %1 %").arg( ((nTriangles/(float)nPoligons) * 100)));      
  	painter.end();
	
}


void showDegree::calcInfo(){
	
	

	Scene* scn = scene();
	
	nObjects = scn->objects().size();
	
	for(int i=0; i<nObjects && i==0; ++i) {
	const Object o = scn->objects()[i];
	
	contador= vector<int>(o.vertices().size());
		for(int j=0; j<(int)o.faces().size();++j){
			const Face f = o.faces()[j];
				for(int k=0; k<(int)f.numVertices();++k) ++contador[f.vertexIndex(k)];
		}
	
	
	}
	Mdegree=0;
	for(int i=0;i<(int)contador.size();++i) Mdegree += contador[i];
	
	Mdegree /= contador.size();
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

