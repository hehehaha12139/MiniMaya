#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include "meshdata.h"


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();

    void on_actionCamera_Controls_triggered();

    //  Add mesh data
    void addVertex(Vertex* v);
    void addFace(Face* f);
    void addHalfEdge(HalfEdge* he);

    // Add draw mesh data
    void drawCurrentVertex(QListWidgetItem* v);
    void drawCurrentFace(QListWidgetItem* f);
    void drawCurrentHalfEdge(QListWidgetItem* he);

    // Vertex position change
    void changeVertexXValue(double x);
    void changeVertexYValue(double y);
    void changeVertexZValue(double z);

    // Face color change
    void changeFaceRedValue(double r);
    void changeFaceGreenValue(double g);
    void changeFaceBlueValue(double b);

    // Debug tools
    void nextHalfEdge();
    void symHalfEdge();
    void halfEdgeFace();
    void halfEdgeVertex();
    void vertexHalfEdge();
    void faceHalfEdge();

    // Topology
    void triangulateFace();
    void midPoint();

    // Planarity
    void planarity();

    // Select mode
    void selectVertex(int state);
    void selectFace(int state);
    void selectHalfEdge(int state);

    // Set listview item
    void setFace(Face* f);
    void setHalfEdge(HalfEdge* he);
    void setVertex(Vertex* v);

    // Extrude face
    void extrudeFace();

    // Smooth mesh
    void smoothMesh();

    // Load object
    void loadObj();

    // Set sharp
    void setSharp();

    // Skinning
    void skinning();

    // Add joint data
    void addJoint(QTreeWidgetItem* root);

    // Select joint
    void selectJoint(QTreeWidgetItem* selected);

    // Load skeleton
    void loadSkeleton();

    // Set joint
    void setJointXpos(double x);
    void setJointYpos(double y);
    void setJointZpos(double z);

    // Rotation
    void rotXPlus();
    void rotYPlus();
    void rotZPlus();
    void rotXMinus();
    void rotYMinus();
    void rotZMinus();
private:
    Ui::MainWindow *ui;

};


#endif // MAINWINDOW_H
