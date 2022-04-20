#include "MyEffect.h"
#include "glwidget.h"

void MyEffect::onPluginLoad()
{
	cout << "Load :^)" << endl;
}

//justo antes de pintar la escena
void MyEffect::preFrame()
{
	//glDisable(GL_DEPTH_TEST);
	//glDepthMask(GL_FALSE);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE); 
}

//justo despues de pintar la escena (por si queremos añadir mas cosas a la escena)
void MyEffect::postFrame()
{
	
}

void MyEffect::onObjectAdd()
{
	cout << "Object counter: " << scene()->objects().size() << endl;
}

bool MyEffect::drawScene()
{
	return false; // return true only if implemented
}

bool MyEffect::drawObject(int)
{
	return false; // return true only if implemented
}

bool MyEffect::paintGL() //cada vez que se repinta la escena (cada frame n  )
{
	return false; // return true only if implemented
}

void MyEffect::keyPressEvent(QKeyEvent *)
{
	
}

void MyEffect::mouseMoveEvent(QMouseEvent *)
{
	
}

