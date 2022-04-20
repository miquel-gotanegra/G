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

#include "shadowmap.h"
#include <QCoreApplication>

const int SHADOW_MAP_WIDTH = 512;
const int SHADOW_MAP_HEIGHT = 512;

void ShadowMap::onPluginLoad()
{
    cout << "[Shadowmap plugin] C - Copy camera position to light position" << endl;

    GLWidget &g = *glwidget();
    g.makeCurrent();
    // Resize to power-of-two viewport

    // Carregar shader, compile & link 
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile(glwidget()->getPluginPath()+"/../shadowmap/shadowmap.vert");
    //cout << "vs" << endl;

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile(glwidget()->getPluginPath()+"/../shadowmap/shadowmap.frag");
    //cout << "fs" << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    if (!program->isLinked()) cout << "Shader link error" << endl; 

    // Setup texture
    g.glActiveTexture(GL_TEXTURE0);
    g.glGenTextures( 1, &textureId);
    g.glBindTexture(GL_TEXTURE_2D, textureId);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    g.glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, SHADOW_MAP_WIDTH,
		   SHADOW_MAP_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    // Camera
    lightCamera = *camera();
    g.resize(SHADOW_MAP_WIDTH,SHADOW_MAP_HEIGHT);

}

void ShadowMap::keyPressEvent(QKeyEvent*e)
{
    if (e->key() == Qt::Key_C) lightCamera = *camera();

    glwidget()->update();
}

// TODO: update VBO coords after creation...
void ShadowMap::drawQuad(const Point& p0, const Point& p1, const Point& p2, const Point& p3)
{
    static bool created = false;
    static GLuint VAO_rect;
    GLWidget &g = *glwidget();
    g.makeCurrent();

    // 1. Create VBO Buffers
    if (!created)
    {
        created = true;        

        // Create & bind empty VAO
        g.glGenVertexArrays(1, &VAO_rect); //Creamos 1 VAO VAO_rect
        g.glBindVertexArray(VAO_rect); //decimos que los cambios siguientes son sobre este VAO

        // Create VBO with (x,y,z) coordinates
        float coords[] = { p0.x(), p0.y(), p0.z(), p1.x(), p1.y(), p1.z(), p3.x(), p3.y(), p3.z(), p2.x(), p2.y(), p2.z() }; //cada 3 valores es un vertice, esta en este orden porque es un triangle strip

        GLuint VBO_coords;
        g.glGenBuffers(1, &VBO_coords);
        g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords); //bindeamos el VBO que queremos modificar
        g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
        g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        g.glEnableVertexAttribArray(0); // corresponde al layout 0 del vs
        //glBindVertexArray(0);


		// Create VBO with (x,y,z) normals
        float normals[] = { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0}; //cada tres valors es un vector normal

        GLuint VBO_normals;
        g.glGenBuffers(1, &VBO_normals);
        g.glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
        g.glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
        g.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        g.glEnableVertexAttribArray(1); // corresponde al layout 1 del vs
        
        
        // Create VBO with (indices)
        GLuint indices[] = {0,1,2,3}; //cada tres valors consecutius construeixen un triangle

        GLuint VBO_indices;
        g.glGenBuffers(1, &VBO_indices);
        g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_indices);
        g.glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        g.glBindVertexArray(0); //unbind
    }
	/*
		CON INDICES NECESITAMOS 8 VERTICES PARA PINTAR UN CUBO --> mejor si representa una superficie suave (porque las noramles seran muy parecidas entre caras)
		
		SIN INDICES NECESITAMOS 3*(6*2)= 36 VERTICES PARA PINTAR UN CUBO -> mejor en objetos con aristas bien definidas, ya que las normales entre las caras seran muy dispares
	*/
    // 2. Draw
    g.glBindVertexArray(VAO_rect);
    //g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //sin indices
    g.glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT,0); //los indices son 4 enteros sin signos
    
    //g.glDrawElementsInstanced(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT,0,numInstances);
    //VS : int gl_InstanceID -> numero de la instancia (0...numInstances-1)
    g.glBindVertexArray(0);
}



bool ShadowMap::paintGL()
{
    // Pass 1. Build depth map
    GLWidget &g = *glwidget();
    g.makeCurrent();
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    QMatrix4x4 CMVP = lightCamera.projectionMatrix() * lightCamera.viewMatrix();
    g.defaultProgram()->setUniformValue("modelViewProjectionMatrix", CMVP); 
    

    // Draw scene (with z offset)
    g.glPolygonOffset(1,1);
    g.glEnable(GL_POLYGON_OFFSET_FILL);
    if (drawPlugin()) drawPlugin()->drawScene();
    g.glDisable(GL_POLYGON_OFFSET_FILL);
    
    //return true; // show shadow map

    // Get texture
    glBindTexture(GL_TEXTURE_2D, textureId);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, SHADOW_MAP_WIDTH,
			SHADOW_MAP_HEIGHT);

    // Pass 2. Draw scene using shadowmap
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    program->bind();
    program->setUniformValue("lightViewMatrix", lightCamera.viewMatrix());
    program->setUniformValue("lightProjectionMatrix",
			     lightCamera.projectionMatrix());
    QMatrix4x4 biasMatrix;
    biasMatrix.translate(0.5, 0.5, 0.5);
    biasMatrix.scale(0.5, 0.5, 0.5);
    program->setUniformValue("biasMatrix", biasMatrix);
    program->setUniformValue("shadowMap", 0); 
    program->setUniformValue("lightPos", lightCamera.getObs());
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP); 
    program->setUniformValue("modelViewMatrix", camera()->viewMatrix());
    program->setUniformValue("normalMatrix",
			     camera()->viewMatrix().normalMatrix());

    // draw scene + floor 
    if (drawPlugin())
		drawPlugin()->drawScene();

    Point min = scene()->boundingBox().min();
    float r = scene()->boundingBox().radius();
    drawQuad(Point(-r,min.y(), r), Point( r,min.y(), r),
	     Point( r,min.y(),  -r), Point(-r,min.y(), -r));

    g.defaultProgram()->bind();
    glBindTexture(GL_TEXTURE_2D, 0);

    
    return true;
}

