#include "mainwindow.h"
#include <ui_mainwindow.h>
#include <QFileDialog>
#include <QDir>
#include "cameracontrolshelp.h"
#include "mesh.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mygl->setFocus();

    ui->faceRedSpinBox->setMaximum(1.0);
    ui->faceGreenSpinBox->setMaximum(1.0);
    ui->faceBlueSpinBox->setMaximum(1.0);

    ui->faceRedSpinBox->setSingleStep(0.05);
    ui->faceGreenSpinBox->setSingleStep(0.05);
    ui->faceBlueSpinBox->setSingleStep(0.05);

    // Connect signal and slot
    connect(&(ui->mygl->m_geomCube), SIGNAL(sendVertex(Vertex*)), this, SLOT(addVertex(Vertex*)));
    connect(&(ui->mygl->m_geomCube), SIGNAL(sendFace(Face*)), this, SLOT(addFace(Face*)));
    connect(&(ui->mygl->m_geomCube), SIGNAL(sendHalfEdge(HalfEdge*)), this, SLOT(addHalfEdge(HalfEdge*)));
    connect(ui->vertsListWidget, SIGNAL(itemClicked(QListWidgetItem*)),
                                        this, SLOT(drawCurrentVertex(QListWidgetItem*)));
    connect(ui->facesListWidget, SIGNAL(itemClicked(QListWidgetItem*)),
                                        this, SLOT(drawCurrentFace(QListWidgetItem*)));
    connect(ui->halfEdgesListWidget, SIGNAL(itemClicked(QListWidgetItem*)),
                                        this, SLOT(drawCurrentHalfEdge(QListWidgetItem*)));
    // Vertex position spinbox slot set
    connect(ui->vertPosXSpinBox, SIGNAL(valueChanged(double)),
                                        this, SLOT(changeVertexXValue(double)));
    connect(ui->vertPosYSpinBox, SIGNAL(valueChanged(double)),
                                        this, SLOT(changeVertexYValue(double)));
    connect(ui->vertPosZSpinBox, SIGNAL(valueChanged(double)),
                                        this, SLOT(changeVertexZValue(double)));
    // Face color spinbox slot set
    connect(ui->faceRedSpinBox, SIGNAL(valueChanged(double)),
                                        this, SLOT(changeFaceRedValue(double)));
    connect(ui->faceGreenSpinBox, SIGNAL(valueChanged(double)),
                                        this, SLOT(changeFaceGreenValue(double)));
    connect(ui->faceBlueSpinBox, SIGNAL(valueChanged(double)),
                                        this, SLOT(changeFaceBlueValue(double)));

    // Mesh data structure debug tool
    connect(ui->mygl, SIGNAL(nextHalfEdge()), this, SLOT(nextHalfEdge()));
    connect(ui->mygl, SIGNAL(symHalfEdge()), this, SLOT(symHalfEdge()));
    connect(ui->mygl, SIGNAL(halfEdgeFace()), this, SLOT(halfEdgeFace()));
    connect(ui->mygl, SIGNAL(halfEdgeVertex()), this, SLOT(halfEdgeVertex()));
    connect(ui->mygl, SIGNAL(vertexHalfEdge()), this, SLOT(vertexHalfEdge()));
    connect(ui->mygl, SIGNAL(faceHalfEdge()), this, SLOT(faceHalfEdge()));

    // Topology
    connect(ui->trangulateButton, SIGNAL(clicked(bool)), this, SLOT(triangulateFace()));
    connect(ui->midPointPushButton, SIGNAL(clicked(bool)), this, SLOT(midPoint()));

    // Select mode
    connect(ui->vertexSet, SIGNAL(stateChanged(int)), this, SLOT(selectVertex(int)));
    connect(ui->faceSet, SIGNAL(stateChanged(int)), this, SLOT(selectFace(int)));
    connect(ui->halfEdgeSet, SIGNAL(stateChanged(int)), this, SLOT(selectHalfEdge(int)));

    // Set listview item
    connect(ui->mygl, SIGNAL(sendFace(Face*)), this, SLOT(setFace(Face*)));
    connect(ui->mygl, SIGNAL(sendVertex(Vertex*)), this, SLOT(setVertex(Vertex*)));
    connect(ui->mygl, SIGNAL(sendHalfEdge(HalfEdge*)), this, SLOT(setHalfEdge(HalfEdge*)));

    // Extrude face
    connect(ui->extrudePushButton, SIGNAL(clicked(bool)), this, SLOT(extrudeFace()));

    // Smooth cube
    connect(ui->smoothPushButton, SIGNAL(clicked(bool)), this, SLOT(smoothMesh()));

    // Load obj
    connect(ui->loadObjPushButton, SIGNAL(clicked(bool)), this, SLOT(loadObj()));

    // Set sharp
    connect(ui->sharpPushButton, SIGNAL(clicked(bool)), this, SLOT(setSharp()));

    // Skinning
    connect(ui->skinningPushButton, SIGNAL(clicked(bool)), this, SLOT(skinning()));

    // Get joint data
    connect(&(ui->mygl->m_geomCube), SIGNAL(sendRoot(QTreeWidgetItem*)), this, SLOT(addJoint(QTreeWidgetItem*)));

    // Select joint
    connect(ui->jointTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(selectJoint(QTreeWidgetItem*)));

    // Load skeleton
    connect(ui->loadSkeletonPushButton, SIGNAL(clicked(bool)), this, SLOT(loadSkeleton()));

    // Set joint
    connect(ui->xJointPosSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setJointXpos(double)));
    connect(ui->yJointPosSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setJointYpos(double)));
    connect(ui->zJointPosSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setJointZpos(double)));

    // Rotate joint
    connect(ui->xPlusPushButton, SIGNAL(clicked(bool)), this, SLOT(rotXPlus()));
    connect(ui->yPlusPushButton, SIGNAL(clicked(bool)), this, SLOT(rotYPlus()));
    connect(ui->zPlusPushButton, SIGNAL(clicked(bool)), this, SLOT(rotZPlus()));
    connect(ui->xMinusPushButton, SIGNAL(clicked(bool)), this, SLOT(rotXMinus()));
    connect(ui->yMinusPushButton, SIGNAL(clicked(bool)), this, SLOT(rotYMinus()));
    connect(ui->zMinusPushButton, SIGNAL(clicked(bool)), this, SLOT(rotZMinus()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_actionCamera_Controls_triggered()
{
    CameraControlsHelp* c = new CameraControlsHelp();
    c->show();
}

//  Add mesh data
void MainWindow::addVertex(Vertex *v)
{
    ui->vertsListWidget->addItem(v);
}

void MainWindow::addFace(Face *f)
{
    ui->facesListWidget->addItem(f);
}

void MainWindow::addHalfEdge(HalfEdge *he)
{
    ui->halfEdgesListWidget->addItem(he);
}

// Add draw mesh data
void MainWindow::drawCurrentVertex(QListWidgetItem *v)
{
    Vertex *vert = dynamic_cast<Vertex*>(v);
    ui->mygl->m_vertDisplay.updateVertex(vert);

    float x = vert->pos.x;
    float y = vert->pos.y;
    float z = vert->pos.z;

    ui->vertPosXSpinBox->blockSignals(true);
    ui->vertPosYSpinBox->blockSignals(true);
    ui->vertPosZSpinBox->blockSignals(true);

    ui->vertPosXSpinBox->setValue(x);
    ui->vertPosYSpinBox->setValue(y);
    ui->vertPosZSpinBox->setValue(z);

    ui->vertPosXSpinBox->blockSignals(false);
    ui->vertPosYSpinBox->blockSignals(false);
    ui->vertPosZSpinBox->blockSignals(false);

    ui->mygl->m_vertDisplay.create();

    ui->mygl->update();
    ui->mygl->setFocus();
}

void MainWindow::drawCurrentFace(QListWidgetItem *f)
{
    Face *face = dynamic_cast<Face*>(f);
    ui->mygl->m_faceDisplay.updateFace(face);
    ui->faceRedSpinBox->setValue(face->color.x);
    ui->faceGreenSpinBox->setValue(face->color.y);
    ui->faceBlueSpinBox->setValue(face->color.z);

    ui->mygl->m_faceDisplay.updateFace(face);
    ui->mygl->m_faceDisplay.create();
    ui->mygl->update();
    ui->mygl->setFocus();
}

void MainWindow::drawCurrentHalfEdge(QListWidgetItem* he)
{
    HalfEdge *halfEdge = dynamic_cast<HalfEdge*>(he);
    ui->mygl->m_halfEdgeDisplay.updateHalfEdge(halfEdge);
    ui->mygl->m_halfEdgeDisplay.create();
    ui->mygl->update();
    ui->mygl->setFocus();
}

// Vertex position change
void MainWindow::changeVertexXValue(double x)
{
    ui->mygl->m_vertDisplay.changePosX(x);
    ui->mygl->m_geomCube.planar();
    ui->mygl->m_geomCube.update();
    ui->mygl->m_vertDisplay.create();
    ui->mygl->m_halfEdgeDisplay.create();
    ui->mygl->m_faceDisplay.create();
    ui->mygl->update();
    ui->mygl->setFocus();
}

void MainWindow::changeVertexYValue(double y)
{
    ui->mygl->m_vertDisplay.changePosY(y);
    ui->mygl->m_geomCube.planar();
    ui->mygl->m_geomCube.update();
    ui->mygl->m_vertDisplay.create();
    ui->mygl->m_halfEdgeDisplay.create();
    ui->mygl->m_faceDisplay.create();
    ui->mygl->update();
    ui->mygl->setFocus();
}

void MainWindow::changeVertexZValue(double z)
{
    ui->mygl->m_vertDisplay.changePosZ(z);
    ui->mygl->m_geomCube.planar();
    ui->mygl->m_geomCube.update();
    ui->mygl->m_vertDisplay.create();
    ui->mygl->m_halfEdgeDisplay.create();
    ui->mygl->m_faceDisplay.create();
    ui->mygl->update();
    ui->mygl->setFocus();
}

// Face color change
void MainWindow::changeFaceRedValue(double r)
{
    ui->mygl->m_faceDisplay.changeColorR(r);
    ui->mygl->m_geomCube.update();
    ui->mygl->m_faceDisplay.create();
    ui->mygl->update();
    ui->mygl->setFocus();
}

void MainWindow::changeFaceGreenValue(double g)
{
    ui->mygl->m_faceDisplay.changeColorG(g);
    ui->mygl->m_geomCube.update();
    ui->mygl->m_faceDisplay.create();
    ui->mygl->update();
    ui->mygl->setFocus();
}

void MainWindow::changeFaceBlueValue(double b)
{
    ui->mygl->m_faceDisplay.changeColorB(b);
    ui->mygl->m_geomCube.update();
    ui->mygl->m_faceDisplay.create();
    ui->mygl->update();
    ui->mygl->setFocus();
}

// Debug tools
void MainWindow::nextHalfEdge()
{
    if(ui->mygl->m_halfEdgeDisplay.representedHalfEdge == nullptr)
    {
        return;
    }
    HalfEdge* nextHe = ui->mygl->m_halfEdgeDisplay.representedHalfEdge->nextEdge;
    ui->mygl->m_halfEdgeDisplay.representedHalfEdge = nextHe;
    ui->halfEdgesListWidget->setCurrentItem(nextHe);
    ui->mygl->m_halfEdgeDisplay.create();
    ui->mygl->update();
    ui->mygl->setFocus();
}

void MainWindow::symHalfEdge()
{
    if(ui->mygl->m_halfEdgeDisplay.representedHalfEdge == nullptr)
    {
        return;
    }
    HalfEdge* symHe = ui->mygl->m_halfEdgeDisplay.representedHalfEdge->symEdge;
    ui->mygl->m_halfEdgeDisplay.representedHalfEdge = symHe;
    ui->halfEdgesListWidget->setCurrentItem(symHe);
    ui->mygl->m_halfEdgeDisplay.create();
    ui->mygl->update();
    ui->mygl->setFocus();
}

void MainWindow::halfEdgeFace()
{
    if(ui->mygl->m_halfEdgeDisplay.representedHalfEdge == nullptr)
    {
        return;
    }
    Face* face = ui->mygl->m_halfEdgeDisplay.representedHalfEdge->face;
    ui->mygl->m_faceDisplay.representedFace = face;
    ui->facesListWidget->setCurrentItem(face);
    ui->mygl->m_faceDisplay.create();
    ui->mygl->update();
    ui->mygl->setFocus();
}

void MainWindow::halfEdgeVertex()
{
    if(ui->mygl->m_halfEdgeDisplay.representedHalfEdge == nullptr)
    {
        return;
    }
    Vertex* vert = ui->mygl->m_halfEdgeDisplay.representedHalfEdge->nextVertex;
    ui->mygl->m_vertDisplay.representedVertex = vert;
    ui->vertsListWidget->setCurrentItem(vert);
    ui->mygl->m_vertDisplay.create();
    ui->mygl->update();
    ui->mygl->setFocus();
}

void MainWindow::vertexHalfEdge()
{
    if(ui->mygl->m_vertDisplay.representedVertex == nullptr)
    {
        return;
    }
    HalfEdge* he = ui->mygl->m_vertDisplay.representedVertex->edge;
    ui->mygl->m_halfEdgeDisplay.representedHalfEdge = he;
    ui->halfEdgesListWidget->setCurrentItem(he);
    ui->mygl->m_halfEdgeDisplay.create();
    ui->mygl->update();
    ui->mygl->setFocus();
}

void MainWindow::faceHalfEdge()
{
    if(ui->mygl->m_faceDisplay.representedFace == nullptr)
    {
        return;
    }
    HalfEdge* he = ui->mygl->m_faceDisplay.representedFace->edge;
    ui->mygl->m_halfEdgeDisplay.representedHalfEdge = he;
    ui->halfEdgesListWidget->setCurrentItem(he);
    ui->mygl->m_halfEdgeDisplay.create();
    ui->mygl->update();
    ui->mygl->setFocus();
}

// Topology
void MainWindow::triangulateFace()
{
    if(ui->mygl->m_faceDisplay.representedFace == nullptr)
    {
        return;
    }
    ui->mygl->m_geomCube.triangulate(ui->mygl->m_faceDisplay.representedFace);
    ui->mygl->m_geomCube.update();
    ui->mygl->m_faceDisplay.create();
    ui->mygl->update();
    ui->mygl->setFocus();
}

void MainWindow::midPoint()
{
    if(ui->mygl->m_halfEdgeDisplay.representedHalfEdge == nullptr)
    {
        return;
    }
    ui->mygl->m_geomCube.addMidPoint(ui->mygl->m_halfEdgeDisplay.representedHalfEdge);
    ui->mygl->m_geomCube.update();
    ui->mygl->m_halfEdgeDisplay.create();
    ui->mygl->update();
    ui->mygl->setFocus();
}

// Select mode
void MainWindow::selectVertex(int state)
{
    switch(state)
    {
        case 0:
            ui->mygl->isVertex = false;
            break;
        case 2:
            ui->mygl->isVertex = true;
            break;
    }
}

void MainWindow::selectFace(int state)
{
    switch(state)
    {
        case 0:
            ui->mygl->isFace = false;
            break;
        case 2:
            ui->mygl->isFace = true;
            break;
    }
}

void MainWindow::selectHalfEdge(int state)
{
    switch(state)
    {
        case 0:
            ui->mygl->isHalfEdge = false;
            break;
        case 2:
            ui->mygl->isHalfEdge = true;
            break;
    }
}

// Planarity
void MainWindow::planarity()
{
    Face* f = ui->mygl->m_faceDisplay.representedFace;
    if(f == nullptr)
    {
        return;
    }
    ui->mygl->m_geomCube.planar();
    ui->mygl->m_faceDisplay.create();
    ui->mygl->update();
    ui->mygl->setFocus();
}

// Set listview item
void MainWindow::setFace(Face* f)
{
    if(f == nullptr)
    {
        return;
    }
    ui->facesListWidget->setCurrentItem(f);
    ui->faceRedSpinBox->setValue(f->color.x);
    ui->faceGreenSpinBox->setValue(f->color.y);
    ui->faceBlueSpinBox->setValue(f->color.z);
    ui->faceSharpSpinBox->setValue(f->sharpness);
}

void MainWindow::setVertex(Vertex *v)
{
    if(v == nullptr)
    {
        return;
    }
    ui->vertsListWidget->setCurrentItem(v);
    ui->vertPosXSpinBox->setValue(v->pos.x);
    ui->vertPosYSpinBox->setValue(v->pos.y);
    ui->vertPosZSpinBox->setValue(v->pos.z);
    ui->vertexSharpSpinBox->setValue(v->sharpness);
}

void MainWindow::setHalfEdge(HalfEdge *he)
{
    if(he == nullptr)
    {
        return;
    }
    ui->halfEdgesListWidget->setCurrentItem(he);
    ui->halfEdgeSharpSpinBox->setValue(he->sharpness);
}

// Extrude given face
void MainWindow::extrudeFace()
{
    Face* face = ui->mygl->m_faceDisplay.representedFace;
    if(face == nullptr)
    {
        return;
    }
    ui->mygl->m_geomCube.extrude(face);
    ui->mygl->m_geomCube.update();
    ui->mygl->m_faceDisplay.create();
    ui->mygl->m_vertDisplay.create();
    ui->mygl->m_halfEdgeDisplay.create();
    ui->mygl->update();
    ui->mygl->setFocus();
}

// Smooth given face
void MainWindow::smoothMesh()
{
    ui->mygl->m_geomCube.smooth();
    ui->mygl->m_geomCube.update();
    ui->mygl->m_halfEdgeDisplay.create();
    ui->mygl->m_faceDisplay.create();
    ui->mygl->m_vertDisplay.create();
    ui->mygl->update();
    ui->mygl->setFocus();
}

// Load obj file
void MainWindow::loadObj()
{
    QString fileName = QFileDialog::getOpenFileName(0, QString("Load OBJ File"),
                                                    QDir::currentPath().append(QString("../..")),
                                                    QString("*.obj"));
    std::string fileNameStd = fileName.toStdString();
    ui->mygl->m_geomCube.fileNameStd = fileNameStd;
    ui->mygl->m_geomCube.isLoadObj = true;
    ui->mygl->m_geomCube.create();
    ui->mygl->m_faceDisplay.representedFace = nullptr;
    ui->mygl->m_vertDisplay.representedVertex = nullptr;
    ui->mygl->m_halfEdgeDisplay.representedHalfEdge = nullptr;
    ui->mygl->m_halfEdgeDisplay.create();
    ui->mygl->m_faceDisplay.create();
    ui->mygl->m_vertDisplay.create();
    ui->mygl->update();
    ui->mygl->setFocus();
}

// Set given component to sharp
void MainWindow::setSharp()
{
    Vertex* curVertex = ui->mygl->m_vertDisplay.representedVertex;
    Face* curFace = ui->mygl->m_faceDisplay.representedFace;
    HalfEdge* curHe = ui->mygl->m_halfEdgeDisplay.representedHalfEdge;

    if(curVertex != nullptr)
    {
        curVertex->isSharped = true;
        curVertex->sharpness = float(ui->vertexSharpSpinBox->value());
    }

    if(curFace != nullptr)
    {
        curFace->isSharped = true;
        curFace->sharpness = float(ui->faceSharpSpinBox->value());
    }

    if(curHe != nullptr)
    {
        curHe->isSharped = true;
        curHe->symEdge->isSharped = true;
        curHe->sharpness = float(ui->halfEdgeSharpSpinBox->value());
        curHe->symEdge->sharpness = float(ui->halfEdgeSharpSpinBox->value());
    }
}

// Skinning given mesh
void MainWindow::skinning()
{
    ui->mygl->m_geomCube.setJointWeights();
    ui->mygl->m_geomCube.update();
    ui->mygl->update();
}

// Add joint data
void MainWindow::addJoint(QTreeWidgetItem *root)
{
    ui->jointTreeWidget->addTopLevelItem(root);
}

// Selected joint
void MainWindow::selectJoint(QTreeWidgetItem *selected)
{
    Joint* curJoint = dynamic_cast<Joint*>(selected);
    for(int i = 0; i < ui->mygl->m_geomCube.jointdisplays.size(); i++)
    {
        if(ui->mygl->m_geomCube.jointdisplays[i]->representedJoint == curJoint)
        {
            ui->mygl->m_geomCube.selectedId = i;
            ui->mygl->m_geomCube.jointdisplays[i]->isSelected = true;
            glm::vec3 globalTranslation = curJoint->getGlobalTranslation();
            glm::mat3 globalRotation = curJoint->getGlobalRotation();
            glm::mat3 localRotation = glm::mat3_cast(curJoint->rotation);
            glm::vec3 angleRad = glm::vec3(0.0f);
            glm::vec3 localAngleRad = glm::vec3(0.0f);

            angleRad = curJoint->toEulerAngle(globalRotation);
            localAngleRad = curJoint->toEulerAngle(localRotation);

            blockSignals(true);
            ui->xJointPosSpinBox->setValue(curJoint->position[0]);
            ui->yJointPosSpinBox->setValue(curJoint->position[1]);
            ui->zJointPosSpinBox->setValue(curJoint->position[2]);

            ui->globalXLabel->setText(QString::number(globalTranslation[0]));
            ui->globalYLabel->setText(QString::number(globalTranslation[1]));
            ui->globalZLabel->setText(QString::number(globalTranslation[2]));

            ui->rotXGlobalLabel->setText(QString::number(angleRad[0]));
            ui->rotYGlobalLabel->setText(QString::number(angleRad[1]));
            ui->rotZGlobalLabel->setText(QString::number(angleRad[2]));

            ui->rotXLabel->setText(QString::number(localAngleRad[0]));
            ui->rotYLabel->setText(QString::number(localAngleRad[1]));
            ui->rotZLabel->setText(QString::number(localAngleRad[2]));

            blockSignals(false);
        }
        else
        {
            ui->mygl->m_geomCube.jointdisplays[i]->isSelected = false;
        }
        ui->mygl->m_geomCube.jointdisplays[i]->create();
    }
    ui->mygl->update();
}

// load skeleton
void MainWindow::loadSkeleton()
{
    QString skeletonName = QFileDialog::getOpenFileName(0, QString("Load Skeleton File"),
                                                        QDir::currentPath().append(QString("../..")),
                                                        QString("*.json"));
    ui->mygl->m_geomCube.loadSkeleton(skeletonName);
    ui->mygl->update();
}

// Set joint
void MainWindow::setJointXpos(double x)
{
    Joint* curJoint = ui->mygl->m_geomCube.jointdisplays[ui->mygl->m_geomCube.selectedId]->representedJoint;
    curJoint->position.x = x;
    ui->mygl->m_geomCube.updateJoints();
    glm::vec3 globalTranslation = curJoint->getGlobalTranslation();
    ui->globalXLabel->setText(QString::number(globalTranslation[0]));
    ui->globalYLabel->setText(QString::number(globalTranslation[1]));
    ui->globalZLabel->setText(QString::number(globalTranslation[2]));
    ui->mygl->update();
    ui->mygl->setFocus();
}

void MainWindow::setJointYpos(double y)
{
    Joint* curJoint = ui->mygl->m_geomCube.jointdisplays[ui->mygl->m_geomCube.selectedId]->representedJoint;
    curJoint->position.y = y;
    ui->mygl->m_geomCube.updateJoints();
    glm::vec3 globalTranslation = curJoint->getGlobalTranslation();
    ui->globalXLabel->setText(QString::number(globalTranslation[0]));
    ui->globalYLabel->setText(QString::number(globalTranslation[1]));
    ui->globalZLabel->setText(QString::number(globalTranslation[2]));
    ui->mygl->update();
    ui->mygl->setFocus();
}

void MainWindow::setJointZpos(double z)
{
    Joint* curJoint = ui->mygl->m_geomCube.jointdisplays[ui->mygl->m_geomCube.selectedId]->representedJoint;
    curJoint->position.z = z;
    ui->mygl->m_geomCube.updateJoints();
    glm::vec3 globalTranslation = curJoint->getGlobalTranslation();
    ui->globalXLabel->setText(QString::number(globalTranslation[0]));
    ui->globalYLabel->setText(QString::number(globalTranslation[1]));
    ui->globalZLabel->setText(QString::number(globalTranslation[2]));
    ui->mygl->update();
    ui->mygl->setFocus();
}

void MainWindow::rotXPlus()
{
    Joint* curJoint = ui->mygl->m_geomCube.jointdisplays[ui->mygl->m_geomCube.selectedId]->representedJoint;
    glm::quat rotOrigin = curJoint->rotation;
    glm::quat newRot = glm::rotate(rotOrigin, glm::radians(5.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    curJoint->rotation = newRot;
    ui->mygl->m_geomCube.updateJoints();
    glm::mat3 globalRotation = curJoint->getGlobalRotation();
    glm::vec3 angleRad = glm::eulerAngles(glm::quat_cast(glm::transpose(globalRotation)));
    glm::vec3 localAngleRad = glm::eulerAngles(curJoint->rotation);


    ui->rotXGlobalLabel->setText(QString::number(angleRad[0]));
    ui->rotYGlobalLabel->setText(QString::number(angleRad[1]));
    ui->rotZGlobalLabel->setText(QString::number(angleRad[2]));

    ui->rotXLabel->setText(QString::number(localAngleRad[0]));
    ui->rotYLabel->setText(QString::number(localAngleRad[1]));
    ui->rotZLabel->setText(QString::number(localAngleRad[2]));

    glm::vec3 globalTranslation = curJoint->getGlobalTranslation();
    ui->globalXLabel->setText(QString::number(globalTranslation[0]));
    ui->globalYLabel->setText(QString::number(globalTranslation[1]));
    ui->globalZLabel->setText(QString::number(globalTranslation[2]));

    ui->mygl->m_geomCube.update();
    ui->mygl->update();
    ui->mygl->setFocus();
}

void MainWindow::rotYPlus()
{
    Joint* curJoint = ui->mygl->m_geomCube.jointdisplays[ui->mygl->m_geomCube.selectedId]->representedJoint;
    glm::quat rotOrigin = curJoint->rotation;
    glm::quat newRot = glm::rotate(rotOrigin, glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    curJoint->rotation = newRot;
    ui->mygl->m_geomCube.updateJoints();
    glm::mat3 globalRotation = curJoint->getGlobalRotation();
    glm::vec3 angleRad = glm::eulerAngles(glm::quat_cast(glm::transpose(globalRotation)));
    glm::vec3 localAngleRad = glm::eulerAngles(curJoint->rotation);

    ui->rotXGlobalLabel->setText(QString::number(angleRad[0]));
    ui->rotYGlobalLabel->setText(QString::number(angleRad[1]));
    ui->rotZGlobalLabel->setText(QString::number(angleRad[2]));

    ui->rotXLabel->setText(QString::number(localAngleRad[0]));
    ui->rotYLabel->setText(QString::number(localAngleRad[1]));
    ui->rotZLabel->setText(QString::number(localAngleRad[2]));

    glm::vec3 globalTranslation = curJoint->getGlobalTranslation();
    ui->globalXLabel->setText(QString::number(globalTranslation[0]));
    ui->globalYLabel->setText(QString::number(globalTranslation[1]));
    ui->globalZLabel->setText(QString::number(globalTranslation[2]));

    ui->mygl->m_geomCube.update();
    ui->mygl->update();
    ui->mygl->setFocus();
}

void MainWindow::rotZPlus()
{
    Joint* curJoint = ui->mygl->m_geomCube.jointdisplays[ui->mygl->m_geomCube.selectedId]->representedJoint;
    glm::quat rotOrigin = curJoint->rotation;
    glm::quat newRot = glm::rotate(rotOrigin, glm::radians(5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    curJoint->rotation = newRot;
    ui->mygl->m_geomCube.updateJoints();
    glm::mat3 globalRotation = curJoint->getGlobalRotation();
    glm::vec3 angleRad = glm::eulerAngles(glm::quat_cast(glm::transpose(globalRotation)));
    glm::vec3 localAngleRad = glm::eulerAngles(curJoint->rotation);


    ui->rotXGlobalLabel->setText(QString::number(angleRad[0]));
    ui->rotYGlobalLabel->setText(QString::number(angleRad[1]));
    ui->rotZGlobalLabel->setText(QString::number(angleRad[2]));

    ui->rotXLabel->setText(QString::number(localAngleRad[0]));
    ui->rotYLabel->setText(QString::number(localAngleRad[1]));
    ui->rotZLabel->setText(QString::number(localAngleRad[2]));

    glm::vec3 globalTranslation = curJoint->getGlobalTranslation();
    ui->globalXLabel->setText(QString::number(globalTranslation[0]));
    ui->globalYLabel->setText(QString::number(globalTranslation[1]));
    ui->globalZLabel->setText(QString::number(globalTranslation[2]));

    ui->mygl->m_geomCube.update();
    ui->mygl->update();
    ui->mygl->setFocus();
}

void MainWindow::rotXMinus()
{
    Joint* curJoint = ui->mygl->m_geomCube.jointdisplays[ui->mygl->m_geomCube.selectedId]->representedJoint;
    glm::quat rotOrigin = curJoint->rotation;
    glm::quat newRot = glm::rotate(rotOrigin, glm::radians(-5.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    curJoint->rotation = newRot;
    ui->mygl->m_geomCube.updateJoints();
    glm::mat3 globalRotation = curJoint->getGlobalRotation();
    glm::vec3 angleRad = glm::eulerAngles(glm::quat_cast(glm::transpose(globalRotation)));
    glm::vec3 localAngleRad = glm::eulerAngles(curJoint->rotation);


    ui->rotXGlobalLabel->setText(QString::number(angleRad[0]));
    ui->rotYGlobalLabel->setText(QString::number(angleRad[1]));
    ui->rotZGlobalLabel->setText(QString::number(angleRad[2]));

    ui->rotXLabel->setText(QString::number(localAngleRad[0]));
    ui->rotYLabel->setText(QString::number(localAngleRad[1]));
    ui->rotZLabel->setText(QString::number(localAngleRad[2]));

    glm::vec3 globalTranslation = curJoint->getGlobalTranslation();
    ui->globalXLabel->setText(QString::number(globalTranslation[0]));
    ui->globalYLabel->setText(QString::number(globalTranslation[1]));
    ui->globalZLabel->setText(QString::number(globalTranslation[2]));

    ui->mygl->m_geomCube.update();
    ui->mygl->update();
    ui->mygl->setFocus();
}

void MainWindow::rotYMinus()
{
    Joint* curJoint = ui->mygl->m_geomCube.jointdisplays[ui->mygl->m_geomCube.selectedId]->representedJoint;
    glm::quat rotOrigin = curJoint->rotation;
    glm::quat newRot = glm::rotate(rotOrigin, glm::radians(-5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    curJoint->rotation = newRot;
    ui->mygl->m_geomCube.updateJoints();
    glm::mat3 globalRotation = curJoint->getGlobalRotation();
    glm::vec3 angleRad = glm::eulerAngles(glm::quat_cast(glm::transpose(globalRotation)));
    glm::vec3 localAngleRad = glm::eulerAngles(curJoint->rotation);


    ui->rotXGlobalLabel->setText(QString::number(angleRad[0]));
    ui->rotYGlobalLabel->setText(QString::number(angleRad[1]));
    ui->rotZGlobalLabel->setText(QString::number(angleRad[2]));

    ui->rotXLabel->setText(QString::number(localAngleRad[0]));
    ui->rotYLabel->setText(QString::number(localAngleRad[1]));
    ui->rotZLabel->setText(QString::number(localAngleRad[2]));

    glm::vec3 globalTranslation = curJoint->getGlobalTranslation();
    ui->globalXLabel->setText(QString::number(globalTranslation[0]));
    ui->globalYLabel->setText(QString::number(globalTranslation[1]));
    ui->globalZLabel->setText(QString::number(globalTranslation[2]));

    ui->mygl->m_geomCube.update();
    ui->mygl->update();
    ui->mygl->setFocus();
}

void MainWindow::rotZMinus()
{
    Joint* curJoint = ui->mygl->m_geomCube.jointdisplays[ui->mygl->m_geomCube.selectedId]->representedJoint;
    glm::quat rotOrigin = curJoint->rotation;
    glm::quat newRot = glm::rotate(rotOrigin, glm::radians(-5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    curJoint->rotation = newRot;
    ui->mygl->m_geomCube.updateJoints();
    glm::mat3 globalRotation = curJoint->getGlobalRotation();
    glm::vec3 angleRad = glm::eulerAngles(glm::quat_cast(glm::transpose(globalRotation)));
    glm::vec3 localAngleRad = glm::eulerAngles(curJoint->rotation);


    ui->rotXGlobalLabel->setText(QString::number(angleRad[0]));
    ui->rotYGlobalLabel->setText(QString::number(angleRad[1]));
    ui->rotZGlobalLabel->setText(QString::number(angleRad[2]));

    ui->rotXLabel->setText(QString::number(localAngleRad[0]));
    ui->rotYLabel->setText(QString::number(localAngleRad[1]));
    ui->rotZLabel->setText(QString::number(localAngleRad[2]));

    glm::vec3 globalTranslation = curJoint->getGlobalTranslation();
    ui->globalXLabel->setText(QString::number(globalTranslation[0]));
    ui->globalYLabel->setText(QString::number(globalTranslation[1]));
    ui->globalZLabel->setText(QString::number(globalTranslation[2]));

    ui->mygl->m_geomCube.update();
    ui->mygl->update();
    ui->mygl->setFocus();
}
