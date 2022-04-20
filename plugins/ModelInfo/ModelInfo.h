#ifndef _MODELINFO_H
#define _MODELINFO_H

#include "plugin.h" 

class ModelInfo: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	
	 void onObjectAdd();
	 void showInfo();
	 void onPluginLoad();
  private:
	// add private methods and attributes here
};

#endif
