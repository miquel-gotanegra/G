#include "animate_vertices.h"
#include "glwidget.h"

void Animate_vertices::onPluginLoad()
{	

	QString vs_src =
    "#version 330 core\nlayout (location=0) in vec3 vertex; layout (location=1) in vec3 normal; layout (location=2) in vec3 color; layout (location=3) in vec2 texCoord; out vec4 frontColor; out vec2 vtexCoord; uniform mat4 modelViewProjectionMatrix; uniform mat3 normalMatrix; uniform float time; uniform float amplitude=0.1; uniform float freq=1; const float PI=acos(-1.0); void main() { vec3 V=vertex+normal*abs(amplitude*sin(PI*2*freq*time)); vec3 N=normalize(normalMatrix*normal); frontColor=vec4(vec3(N.z),1); gl_Position=modelViewProjectionMatrix*vec4(V, 1); }";
  
      
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceCode(vs_src);
    cout << "VS log:" << vs->log().toStdString() << endl;

    QString fs_src =
      "#version 330 core\nin vec4 frontColor; out vec4 fragColor; void main() { fragColor=frontColor; }";
  
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceCode(fs_src);
    cout << "FS log:" << fs->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;
    
    elapsedTimer.start();
     QTimer *timer = new QTimer(this);
  	connect(timer, SIGNAL(timeout()), glwidget(), SLOT(updateGL()));
  	timer->start();
}

void Animate_vertices::preFrame() 
{
    // bind shader and define uniforms
    program->bind();
    program->setUniformValue("time", float(elapsedTimer.elapsed()/1000.0f));
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP); 
    QMatrix3x3 N = (camera()->viewMatrix()).normalMatrix();
    program->setUniformValue("normalMatrix", N); 
}

void Animate_vertices::postFrame() 
{
    // unbind shader
    program->release();
}

