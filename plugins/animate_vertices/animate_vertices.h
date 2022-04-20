#ifndef _ANIMATE_VERTICES_H
#define _ANIMATE_VERTICES_H

#include "plugin.h" 
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QElapsedTimer> 

class Animate_vertices: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();
	 
	private:
	QOpenGLShaderProgram* program;
    QOpenGLShader *fs, *vs; 
    QElapsedTimer elapsedTimer;
};

#endif
