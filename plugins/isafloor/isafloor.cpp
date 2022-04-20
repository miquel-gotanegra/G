// GLarena, a plugin based platform to teach OpenGL programming
// © Copyright 2012-2018, ViRVIG Research Group, UPC, https://www.virvig.eu
// 
// This file is part of GLarena
//
// GLarena is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "isafloor.h"
#include <QCoreApplication>

const int IMAGE_WIDTH = 512;
const int IMAGE_HEIGHT = IMAGE_WIDTH;

void Isafloor::onPluginLoad()
{
    GLWidget & g = *glwidget();
    g.makeCurrent();
    // Carregar shader, compile & link 
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile(g.getPluginPath()+"/../isafloor/isafloor.vert");

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile(g.getPluginPath()+"/../isafloor/isafloor.frag");

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    
    Scene* scn=scene();
    
    const vector<Vertex> vert = scn->objects()[0].vertices();
    const vector<Face> f = scn->objects()[0].faces();
    
    float area_total = 0.0;
    float area_terra = 0.0;
    for(int i=0; i<f.size();++i){
    	//calculem l'area de la cara
    	Point x = vert[(f[i].vertexIndex(0))].coord();
    	Point y = vert[(f[i].vertexIndex(1))].coord();
    	Point z = vert[(f[i].vertexIndex(2))].coord();
    	
    	Vector cross = Vector::crossProduct(x-y,x-z);
    	
    	float a = cross.length()/2;
    	area_total += a;
    	
    	
    	//calculem si sera terra o no
    	Vector N = f[i].normal().normalized();
    	
    	float d = Vector::dotProduct(N,Vector(0,0,1));
    	if(d>0.7) area_terra += a;
    	
    	
    }
    cout << "proporico de terra = " << area_terra/area_total << endl;
    proporcio = area_terra/area_total;
    
}

void Isafloor::onObjectAdd(){
	Scene* scn=scene();
    
    const vector<Vertex> vert = scn->objects()[0].vertices();
    const vector<Face> f = scn->objects()[0].faces();
    
    float area_total = 0.0;
    float area_terra = 0.0;
    for(int i=0; i<f.size();++i){
    	//calculem l'area de la cara
    	Point x = vert[(f[i].vertexIndex(0))].coord();
    	Point y = vert[(f[i].vertexIndex(1))].coord();
    	Point z = vert[(f[i].vertexIndex(2))].coord();
    	
    	Vector cross = Vector::crossProduct(x-y,x-z);
    	
    	float a = cross.length()/2;
    	area_total += a;
    	
    	
    	//calculem si sera terra o no
    	Vector N = f[i].normal().normalized();
    	
    	float d = Vector::dotProduct(N,Vector(0,0,1));
    	if(d>0.7) area_terra += a;
    	
    	
    }
    cout << "proporico de terra = " << area_terra/area_total << endl;
    proporcio = area_terra/area_total;
}
void Isafloor::preFrame()
{
	program->bind();
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
	QMatrix3x3 NM = (camera()->viewMatrix()).normalMatrix();
	program->setUniformValue("normalMatrix", NM);
	program->setUniformValue("prop", proporcio);
}

void Isafloor::postFrame()
{
	program->release();
}






