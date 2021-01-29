#include "mygl.h"
#include <la.h>

#include <iostream>
#include <QApplication>
#include <QKeyEvent>
#include <cmath>


MyGL::MyGL(QWidget *parent)
    : OpenGLContext(parent),
      m_geomSquare(this),
      m_geomCube(this),
      m_progLambert(this), m_progFlat(this), m_progSkeleton(this),
      m_glCamera(),
      m_vertDisplay(this),
      m_faceDisplay(this),
      m_halfEdgeDisplay(this),
      isFace(false),
      isVertex(false),
      isHalfEdge(false)
{}

MyGL::~MyGL()
{
    makeCurrent();
    glDeleteVertexArrays(1, &vao);
    m_geomSquare.destroy();
    m_geomCube.destroy();
}

void MyGL::initializeGL()
{
    // Create an OpenGL context using Qt's QOpenGLFunctions_3_2_Core class
    // If you were programming in a non-Qt context you might use GLEW (GL Extension Wrangler)instead
    initializeOpenGLFunctions();
    // Print out some information about the current OpenGL context
    debugContextVersion();

    // Set a few settings/modes in OpenGL rendering
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    // Set the size with which points should be rendered
    glPointSize(5);
    // Set the color with which the screen is filled at the start of each render call.
    glClearColor(0.5, 0.5, 0.5, 1);

    printGLErrorLog();

    // Create a Vertex Attribute Object
    glGenVertexArrays(1, &vao);

    //Create the instances of Cylinder and Sphere.
    //m_geomSquare.create();
    m_geomCube.create();

    // Create and set up the diffuse shader
    m_progLambert.create(":/glsl/lambert.vert.glsl", ":/glsl/lambert.frag.glsl");
    // Create and set up the flat lighting shader
    m_progFlat.create(":/glsl/flat.vert.glsl", ":/glsl/flat.frag.glsl");
    m_progSkeleton.create(":/glsl/skeleton.vert.glsl", ":/glsl/skeleton.frag.glsl");
    // We have to have a VAO bound in OpenGL 3.2 Core. But if we're not
    // using multiple VAOs, we can just bind one once.
    glBindVertexArray(vao);
}

void MyGL::resizeGL(int w, int h)
{
    //This code sets the concatenated view and perspective projection matrices used for
    //our scene's camera view.
    m_glCamera = Camera(w, h);
    glm::mat4 viewproj = m_glCamera.getViewProj();

    // Upload the view-projection matrix to our shaders (i.e. onto the graphics card)

    m_progLambert.setViewProjMatrix(viewproj);
    m_progFlat.setViewProjMatrix(viewproj);
    m_progSkeleton.setViewProjMatrix(viewproj);
    printGLErrorLog();
}

//This function is called by Qt any time your GL window is supposed to update
//For example, when the function update() is called, paintGL is called implicitly.
void MyGL::paintGL()
{
    // Clear the screen so that we only see newly drawn images
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_progFlat.setViewProjMatrix(m_glCamera.getViewProj());
    m_progLambert.setViewProjMatrix(m_glCamera.getViewProj());
    m_progLambert.setCamPos(m_glCamera.eye);

    m_progSkeleton.setViewProjMatrix(m_glCamera.getViewProj());
    m_progSkeleton.setCamPos(m_glCamera.eye);

    if(!m_geomCube.meshSkeleton.isEmpty)
    {
        std::vector<glm::mat2x4> bindMatrices;
        std::vector<glm::mat2x4> dualQ;
        std::vector<glm::mat4> bindMat4;
        for(int i = 0; i < m_geomCube.meshSkeleton.joints.size(); i++)
        {
            glm::mat4 bindTransform = m_geomCube.meshSkeleton.joints[i]->bindMatrix;
            glm::mat4 overallTransform = m_geomCube.meshSkeleton.joints[i]->getGlobalTransformation();
            glm::mat4 jointTrans = glm::transpose(overallTransform) * glm::transpose(bindTransform);
            glm::dualquat bindQuat = glm::dualquat_cast(glm::mat3x4(
                                    glm::vec4(jointTrans[0][0], jointTrans[0][1], jointTrans[0][2], jointTrans[0][3]),
                                    glm::vec4(jointTrans[1][0], jointTrans[1][1], jointTrans[1][2], jointTrans[1][3]),
                                    glm::vec4(jointTrans[2][0], jointTrans[2][1], jointTrans[2][2], jointTrans[2][3])));
            bindMatrices.push_back(glm::mat2x4_cast(bindQuat));
            dualQ.push_back(m_geomCube.meshSkeleton.joints[i]->getLocalDoubleQuat());
            bindMat4.push_back(jointTrans);
        }
        m_progSkeleton.setBindMatrices(bindMatrices);
        m_progSkeleton.setBindMatricesMat(bindMat4);
        m_progSkeleton.setJointTrans(dualQ);
    }

//#define NOPE
#ifndef NOPE
    //Create a model matrix. This one scales the sphere uniformly by 3, then translates it by <-2,0,0>.
    //Note that we have to transpose the model matrix before passing it to the shader
    //This is because OpenGL expects column-major matrices, but you've
    //implemented row-major matrices.
    //glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-2,0,0)) * glm::rotate(glm::mat4(), 0.25f * 3.14159f, glm::vec3(0,1,0));
    glm::mat4 model = glm::mat4(1.0);
    //m_geomCube.curModel = model;
    //Send the geometry's transformation matrix to the shader
    if(m_geomCube.meshSkeleton.isEmpty)
    {
        m_progLambert.setModelMatrix(model);
        //Draw the example sphere using our lambert shader
        //m_progLambert.draw(m_geomSquare);
        m_progLambert.draw(m_geomCube);
    }
    else
    {
        m_progSkeleton.setModelMatrix(model);
        //Draw the example sphere using our lambert shader
        //m_progLambert.draw(m_geomSquare);
        m_progSkeleton.draw(m_geomCube);
    }
//    m_progLambert.setModelMatrix(model);
//    //Draw the example sphere using our lambert shader
//    //m_progLambert.draw(m_geomSquare);
//    m_progLambert.draw(m_geomCube);


    //Now do the same to render the cylinder
    //We've rotated it -45 degrees on the Z axis, then translated it to the point <2,2,0>
    //model = glm::translate(glm::mat4(1.0f), glm::vec3(2,2,0)) * glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(0,0,1));
    //m_progLambert.setModelMatrix(model);
    //m_progLambert.draw(m_geomSquare);
    //m_progLambert.draw(m_geomCube);

    glDisable(GL_DEPTH_TEST);
    // Draw selected vertex
    if(!m_vertDisplay.isNull())
    {
        m_progFlat.setModelMatrix(model);
        m_progFlat.draw(m_vertDisplay);
    }

    // Draw selected face
    if(!m_faceDisplay.isNull())
    {
        m_progFlat.setModelMatrix(model);
        m_progFlat.draw(m_faceDisplay);
    }

    // Draw selected half-edge
    if(!m_halfEdgeDisplay.isNull())
    {
        m_progFlat.setModelMatrix(model);
        m_progFlat.draw(m_halfEdgeDisplay);
    }

    // Draw joints
    for(int i = 0; i < m_geomCube.jointdisplays.size(); i++)
    {
        m_progFlat.setModelMatrix(model);
        m_progFlat.draw(*(m_geomCube.jointdisplays[i]));
    }

    glEnable(GL_DEPTH_TEST);
#endif
}


void MyGL::keyPressEvent(QKeyEvent *e)
{
    float amount = 2.0f;
    if(e->modifiers() & Qt::ShiftModifier){
        amount = 10.0f;
    }
    // http://doc.qt.io/qt-5/qt.html#Key-enum
    // This could all be much more efficient if a switch
    // statement were used
    if (e->key() == Qt::Key_Escape)
    {
        QApplication::quit();
    }
    else if (e->key() == Qt::Key_Right)
    {
        m_glCamera.TranslateAlongRight(amount);
    }
    else if (e->key() == Qt::Key_Left)
    {
        m_glCamera.TranslateAlongRight(-amount);
    }
    else if (e->key() == Qt::Key_Up)
    {
        m_glCamera.TranslateAlongUp(amount);
    }
    else if (e->key() == Qt::Key_Down)
    {
        m_glCamera.TranslateAlongUp(-amount);
    }
    else if (e->key() == Qt::Key_1)
    {
        m_glCamera.fovy += amount;
    }
    else if (e->key() == Qt::Key_2)
    {
        m_glCamera.fovy -= amount;
    }
    else if (e->key() == Qt::Key_W)
    {
        //m_glCamera.TranslateAlongLook(amount);
        m_glCamera.translateZAxisZoom(amount);
    }
    else if (e->key() == Qt::Key_S)
    {
        //m_glCamera.TranslateAlongLook(-amount);
        m_glCamera.translateZAxisZoom(-amount);
    }
    else if (e->key() == Qt::Key_D)
    {
        m_glCamera.rotateXAxisAngle(-2.0f);
    }
    else if (e->key() == Qt::Key_A)
    {
        m_glCamera.rotateXAxisAngle(2.0f);
    }
    else if (e->key() == Qt::Key_Q)
    {
        m_glCamera.rotateYAxisAngle(-2.0f);
    }
    else if (e->key() == Qt::Key_E)
    {
        m_glCamera.rotateYAxisAngle(2.0f);
    }
    else if (e->key() == Qt::Key_Z)
    {
        m_glCamera.TranslateAlongLook(amount);
    }
    else if (e->key() == Qt::Key_C)
    {
        m_glCamera.TranslateAlongLook(-amount);
    }
    else if (e->key() == Qt::Key_R)
    {
        m_glCamera = Camera(this->width(), this->height());
    }
    else if (e->key() == Qt::Key_N)
    {
        emit nextHalfEdge();
    }
    else if (e->key() == Qt::Key_M)
    {
        emit symHalfEdge();
    }
    else if (e->key() == Qt::Key_F)
    {
        emit halfEdgeFace();
    }
    else if (e->key() == Qt::Key_V)
    {
        emit halfEdgeVertex();
    }
    else if (e->key() == Qt::Key_H)
    {
        if(e->modifiers() & Qt::ShiftModifier)
        {
            emit faceHalfEdge();
        }
        else
        {
            emit vertexHalfEdge();
        }
    }
    //m_glCamera.RecomputeAttributes();
    //m_glCamera.reComputeSphericalVectors();
    update();  // Calls paintGL, among other things
}

// Get mouse input to select a mesh data
void MyGL::mousePressEvent(QMouseEvent *e)
{
    glm::vec3 worldCoord = getWorldPosition(e->x(), e->y());
    glm::vec3 rayDirection = glm::normalize(worldCoord - m_glCamera.eye);

    // Select vertex
    if(isVertex)
    {
         Vertex* v = this->m_geomCube.findNearestVertex(rayDirection, m_glCamera.eye);
         if(v != nullptr)
         {
             this->m_vertDisplay.updateVertex(v);
             this->m_vertDisplay.create();
             emit sendVertex(v);
         }
    }

    // Select face
    if(isFace)
    {
        Face* f = this->m_geomCube.findNearestFace(rayDirection, m_glCamera.eye);
        if(f != nullptr)
        {
            this->m_faceDisplay.updateFace(f);
            this->m_faceDisplay.create();
            emit sendFace(f);
        }
    }

    // Select half-edge
    if(isHalfEdge)
    {
        HalfEdge* he = this->m_geomCube.findNearestHalfEdge(rayDirection, m_glCamera.eye);
        if(he != nullptr)
        {
            this->m_halfEdgeDisplay.updateHalfEdge(he);
            this->m_halfEdgeDisplay.create();
            emit sendHalfEdge(he);
        }
    }

    update();
    this->setFocus();
}

// Given screen space coord, output a view space coord
glm::vec3 MyGL::getWorldPosition(float x, float y)
{
    // Pixel space -> NDC
    float Sx = (x / m_glCamera.width) * 2.0 - 1.0;
    float Sy = 1 - (y / m_glCamera.height) * 2.0;

    // Compute ref point
    glm::vec3 ref = m_glCamera.ref;
    float len = glm::length(ref - m_glCamera.eye);

    // Vertical vector
    glm::vec3 v = len * tanf(glm::radians(m_glCamera.fovy / 2.0)) * m_glCamera.up;

    float aspect = float(this->width()) / float(this->height());

    // Horizonal vector
    glm::vec3 h = len * aspect * tanf(glm::radians(m_glCamera.fovy / 2.0)) * m_glCamera.right;

    return ref + Sx * h + Sy * v;
}
