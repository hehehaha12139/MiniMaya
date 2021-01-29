#ifndef MYGL_H
#define MYGL_H

#include <openglcontext.h>
#include <utils.h>
#include <shaderprogram.h>
#include <scene/squareplane.h>
#include "camera.h"
#include "mesh.h"
#include "meshdisplay.h"
#include "mainwindow.h"
#include "jointdisplay.h"

#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>


class MyGL
    : public OpenGLContext
{
    Q_OBJECT
    friend class MainWindow;
private:
    SquarePlane m_geomSquare;// The instance of a unit cylinder we can use to render any cylinder
    Mesh m_geomCube; // The instance of unit cube
    ShaderProgram m_progLambert;// A shader program that uses lambertian reflection
    ShaderProgram m_progFlat;// A shader program that uses "flat" reflection (no shadowing at all)
    ShaderProgram m_progSkeleton; // A shader program that shade a mesh with skeleton

    GLuint vao; // A handle for our vertex array object. This will store the VBOs created in our geometry classes.
                // Don't worry too much about this. Just know it is necessary in order to render geometry.
    Camera m_glCamera;

    VertexDisplay m_vertDisplay;
    FaceDisplay m_faceDisplay;
    HalfEdgeDisplay m_halfEdgeDisplay;
    //std::vector<std::unique_ptr<JointDisplay>> jointdisplays; // Joint display components

    bool isVertex;
    bool isHalfEdge;
    bool isFace;

    QTreeWidgetItem* selectedJoint;

public:
    explicit MyGL(QWidget *parent = nullptr);
    ~MyGL();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

protected:
    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *e);
    glm::vec3 getWorldPosition(float x, float y);

signals:
    void nextHalfEdge();
    void symHalfEdge();
    void halfEdgeFace();
    void halfEdgeVertex();
    void vertexHalfEdge();
    void faceHalfEdge();
    void sendFace(Face*);
    void sendVertex(Vertex*);
    void sendHalfEdge(HalfEdge*);
};


#endif // MYGL_H
