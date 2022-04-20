#ifndef _MODELINFO2_H
#define _MODELINFO2_H

#include "plugin.h" 
#include <QPainter>
class modelInfo2: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	
	 void postFrame();
	 
  private:
	// add private methods and attributes here
	void calcInfo();
	
	float nObjects = 0;
	float nPoligons = 0;
	float nTriangles = 0;
	float nVertex = 0;
	QPainter painter;
};

#endif
