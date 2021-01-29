#ifndef MESHDISPLAY_H
#define MESHDISPLAY_H
#include "meshdata.h"
#include "drawable.h"
#include "mainwindow.h"

class VertexDisplay: public Drawable
{
    friend class MainWindow;
protected:
    Vertex* representedVertex;

public:
    // Creates VBO data for current vertex display
    void create();

    // Change draw mode
    GLenum drawMode();

    // Change displayed vertex
    void updateVertex(Vertex* v);

    // Change vertex position
    void changePosX(double x);
    void changePosY(double y);
    void changePosZ(double z);

    // Constructor
    VertexDisplay(OpenGLContext* context);

    bool isNull();

    // Destructor
    ~VertexDisplay();
};

class FaceDisplay: public Drawable
{
    friend class MainWindow;
protected:
    Face* representedFace;

public:
    // Creates VBO data for current vertex display
    void create() override;

    // Change draw mode
    GLenum drawMode();

    // Change color
    void changeColorR(double r);
    void changeColorG(double g);
    void changeColorB(double b);

    // Change displayed vertex
    void updateFace(Face* f);

    // Constructor
    FaceDisplay(OpenGLContext* context);

    bool isNull();

    // Destructor
    ~FaceDisplay();
};

class HalfEdgeDisplay: public Drawable
{
    friend class MainWindow;
protected:
    HalfEdge* representedHalfEdge;

public:
    // Creates VBO data for current vertex display
    void create() override;

    // Change displayed vertex
    void updateHalfEdge(HalfEdge* he);

    // Change draw mode
    GLenum drawMode();

    // Constructor
    HalfEdgeDisplay(OpenGLContext *context);

    bool isNull();

    // Destructor
    ~HalfEdgeDisplay();
};



#endif // MESHDISPLAY_H
