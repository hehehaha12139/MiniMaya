/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include "mygl.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionCamera_Controls;
    QWidget *centralWidget;
    MyGL *mygl;
    QListWidget *vertsListWidget;
    QListWidget *halfEdgesListWidget;
    QListWidget *facesListWidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QDoubleSpinBox *vertPosXSpinBox;
    QDoubleSpinBox *vertPosYSpinBox;
    QDoubleSpinBox *vertPosZSpinBox;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QDoubleSpinBox *faceBlueSpinBox;
    QLabel *label_10;
    QDoubleSpinBox *faceGreenSpinBox;
    QDoubleSpinBox *faceRedSpinBox;
    QLabel *label_11;
    QPushButton *trangulateButton;
    QPushButton *midPointPushButton;
    QCheckBox *vertexSet;
    QCheckBox *halfEdgeSet;
    QCheckBox *faceSet;
    QLabel *label_12;
    QPushButton *extrudePushButton;
    QPushButton *smoothPushButton;
    QPushButton *loadObjPushButton;
    QPushButton *sharpPushButton;
    QDoubleSpinBox *faceSharpSpinBox;
    QLabel *label_13;
    QLabel *label_14;
    QDoubleSpinBox *vertexSharpSpinBox;
    QLabel *label_15;
    QDoubleSpinBox *halfEdgeSharpSpinBox;
    QLabel *label_16;
    QPushButton *skinningPushButton;
    QFrame *line;
    QTreeWidget *jointTreeWidget;
    QLabel *label_17;
    QPushButton *loadSkeletonPushButton;
    QLabel *label_18;
    QDoubleSpinBox *xJointPosSpinBox;
    QDoubleSpinBox *yJointPosSpinBox;
    QDoubleSpinBox *zJointPosSpinBox;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *rotXLabel;
    QLabel *label_23;
    QLabel *rotYLabel;
    QLabel *label_24;
    QLabel *rotZLabel;
    QLabel *labe_25;
    QPushButton *xPlusPushButton;
    QPushButton *xMinusPushButton;
    QPushButton *yPlusPushButton;
    QPushButton *yMinusPushButton;
    QPushButton *zPlusPushButton;
    QPushButton *zMinusPushButton;
    QLabel *globalXLabel;
    QLabel *globalYLabel;
    QLabel *globalZLabel;
    QLabel *label_26;
    QFrame *line_2;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_29;
    QLabel *rotYGlobalLabel;
    QLabel *rotZGlobalLabel;
    QLabel *rotXGlobalLabel;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1348, 669);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionCamera_Controls = new QAction(MainWindow);
        actionCamera_Controls->setObjectName(QStringLiteral("actionCamera_Controls"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        mygl = new MyGL(centralWidget);
        mygl->setObjectName(QStringLiteral("mygl"));
        mygl->setGeometry(QRect(10, 10, 681, 631));
        vertsListWidget = new QListWidget(centralWidget);
        vertsListWidget->setObjectName(QStringLiteral("vertsListWidget"));
        vertsListWidget->setGeometry(QRect(700, 10, 111, 261));
        halfEdgesListWidget = new QListWidget(centralWidget);
        halfEdgesListWidget->setObjectName(QStringLiteral("halfEdgesListWidget"));
        halfEdgesListWidget->setGeometry(QRect(830, 10, 111, 261));
        facesListWidget = new QListWidget(centralWidget);
        facesListWidget->setObjectName(QStringLiteral("facesListWidget"));
        facesListWidget->setGeometry(QRect(960, 10, 111, 261));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(700, 280, 111, 16));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(830, 280, 111, 16));
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(960, 280, 111, 16));
        label_3->setAlignment(Qt::AlignCenter);
        vertPosXSpinBox = new QDoubleSpinBox(centralWidget);
        vertPosXSpinBox->setObjectName(QStringLiteral("vertPosXSpinBox"));
        vertPosXSpinBox->setGeometry(QRect(780, 310, 62, 22));
        vertPosXSpinBox->setMinimum(-100);
        vertPosXSpinBox->setSingleStep(0.1);
        vertPosYSpinBox = new QDoubleSpinBox(centralWidget);
        vertPosYSpinBox->setObjectName(QStringLiteral("vertPosYSpinBox"));
        vertPosYSpinBox->setGeometry(QRect(860, 310, 62, 22));
        vertPosYSpinBox->setMinimum(-100);
        vertPosYSpinBox->setSingleStep(0.1);
        vertPosZSpinBox = new QDoubleSpinBox(centralWidget);
        vertPosZSpinBox->setObjectName(QStringLiteral("vertPosZSpinBox"));
        vertPosZSpinBox->setGeometry(QRect(940, 310, 62, 22));
        vertPosZSpinBox->setMinimum(-100);
        vertPosZSpinBox->setSingleStep(0.1);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(700, 310, 71, 21));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(780, 330, 61, 16));
        label_5->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(860, 330, 61, 16));
        label_6->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(940, 330, 61, 16));
        label_7->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(940, 380, 61, 16));
        label_8->setAlignment(Qt::AlignCenter);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(780, 380, 61, 16));
        label_9->setAlignment(Qt::AlignCenter);
        faceBlueSpinBox = new QDoubleSpinBox(centralWidget);
        faceBlueSpinBox->setObjectName(QStringLiteral("faceBlueSpinBox"));
        faceBlueSpinBox->setGeometry(QRect(940, 360, 62, 22));
        faceBlueSpinBox->setMaximum(1);
        faceBlueSpinBox->setSingleStep(0.05);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(700, 360, 71, 21));
        faceGreenSpinBox = new QDoubleSpinBox(centralWidget);
        faceGreenSpinBox->setObjectName(QStringLiteral("faceGreenSpinBox"));
        faceGreenSpinBox->setGeometry(QRect(860, 360, 62, 22));
        faceGreenSpinBox->setMaximum(1);
        faceGreenSpinBox->setSingleStep(0.05);
        faceRedSpinBox = new QDoubleSpinBox(centralWidget);
        faceRedSpinBox->setObjectName(QStringLiteral("faceRedSpinBox"));
        faceRedSpinBox->setGeometry(QRect(780, 360, 62, 22));
        faceRedSpinBox->setMaximum(1);
        faceRedSpinBox->setSingleStep(0.05);
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(860, 380, 61, 16));
        label_11->setAlignment(Qt::AlignCenter);
        trangulateButton = new QPushButton(centralWidget);
        trangulateButton->setObjectName(QStringLiteral("trangulateButton"));
        trangulateButton->setGeometry(QRect(710, 410, 80, 31));
        midPointPushButton = new QPushButton(centralWidget);
        midPointPushButton->setObjectName(QStringLiteral("midPointPushButton"));
        midPointPushButton->setGeometry(QRect(810, 410, 80, 31));
        vertexSet = new QCheckBox(centralWidget);
        vertexSet->setObjectName(QStringLiteral("vertexSet"));
        vertexSet->setGeometry(QRect(1030, 330, 70, 17));
        halfEdgeSet = new QCheckBox(centralWidget);
        halfEdgeSet->setObjectName(QStringLiteral("halfEdgeSet"));
        halfEdgeSet->setGeometry(QRect(1030, 350, 70, 17));
        faceSet = new QCheckBox(centralWidget);
        faceSet->setObjectName(QStringLiteral("faceSet"));
        faceSet->setGeometry(QRect(1030, 370, 70, 17));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(1030, 310, 71, 16));
        extrudePushButton = new QPushButton(centralWidget);
        extrudePushButton->setObjectName(QStringLiteral("extrudePushButton"));
        extrudePushButton->setGeometry(QRect(910, 410, 80, 31));
        smoothPushButton = new QPushButton(centralWidget);
        smoothPushButton->setObjectName(QStringLiteral("smoothPushButton"));
        smoothPushButton->setGeometry(QRect(1010, 410, 80, 31));
        loadObjPushButton = new QPushButton(centralWidget);
        loadObjPushButton->setObjectName(QStringLiteral("loadObjPushButton"));
        loadObjPushButton->setGeometry(QRect(1010, 520, 81, 31));
        sharpPushButton = new QPushButton(centralWidget);
        sharpPushButton->setObjectName(QStringLiteral("sharpPushButton"));
        sharpPushButton->setGeometry(QRect(1010, 470, 81, 31));
        faceSharpSpinBox = new QDoubleSpinBox(centralWidget);
        faceSharpSpinBox->setObjectName(QStringLiteral("faceSharpSpinBox"));
        faceSharpSpinBox->setGeometry(QRect(720, 470, 61, 21));
        faceSharpSpinBox->setMaximum(1);
        faceSharpSpinBox->setSingleStep(0.05);
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(700, 450, 54, 12));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(720, 490, 54, 12));
        vertexSharpSpinBox = new QDoubleSpinBox(centralWidget);
        vertexSharpSpinBox->setObjectName(QStringLiteral("vertexSharpSpinBox"));
        vertexSharpSpinBox->setGeometry(QRect(820, 470, 61, 21));
        vertexSharpSpinBox->setMaximum(1);
        vertexSharpSpinBox->setSingleStep(0.05);
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(820, 490, 54, 12));
        halfEdgeSharpSpinBox = new QDoubleSpinBox(centralWidget);
        halfEdgeSharpSpinBox->setObjectName(QStringLiteral("halfEdgeSharpSpinBox"));
        halfEdgeSharpSpinBox->setGeometry(QRect(920, 470, 61, 21));
        halfEdgeSharpSpinBox->setMaximum(1);
        halfEdgeSharpSpinBox->setSingleStep(0.05);
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(920, 490, 54, 12));
        skinningPushButton = new QPushButton(centralWidget);
        skinningPushButton->setObjectName(QStringLiteral("skinningPushButton"));
        skinningPushButton->setGeometry(QRect(910, 520, 81, 31));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(1090, 10, 20, 641));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        jointTreeWidget = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        jointTreeWidget->setHeaderItem(__qtreewidgetitem);
        jointTreeWidget->setObjectName(QStringLiteral("jointTreeWidget"));
        jointTreeWidget->setGeometry(QRect(1120, 10, 221, 301));
        jointTreeWidget->setColumnCount(1);
        label_17 = new QLabel(centralWidget);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(1170, 320, 111, 16));
        label_17->setAlignment(Qt::AlignCenter);
        loadSkeletonPushButton = new QPushButton(centralWidget);
        loadSkeletonPushButton->setObjectName(QStringLiteral("loadSkeletonPushButton"));
        loadSkeletonPushButton->setGeometry(QRect(810, 520, 81, 31));
        label_18 = new QLabel(centralWidget);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(1120, 330, 81, 16));
        xJointPosSpinBox = new QDoubleSpinBox(centralWidget);
        xJointPosSpinBox->setObjectName(QStringLiteral("xJointPosSpinBox"));
        xJointPosSpinBox->setGeometry(QRect(1120, 410, 62, 22));
        xJointPosSpinBox->setMinimum(-100);
        xJointPosSpinBox->setSingleStep(0.1);
        yJointPosSpinBox = new QDoubleSpinBox(centralWidget);
        yJointPosSpinBox->setObjectName(QStringLiteral("yJointPosSpinBox"));
        yJointPosSpinBox->setGeometry(QRect(1200, 410, 62, 22));
        yJointPosSpinBox->setMinimum(-100);
        yJointPosSpinBox->setSingleStep(0.1);
        zJointPosSpinBox = new QDoubleSpinBox(centralWidget);
        zJointPosSpinBox->setObjectName(QStringLiteral("zJointPosSpinBox"));
        zJointPosSpinBox->setGeometry(QRect(1280, 410, 62, 22));
        zJointPosSpinBox->setMinimum(-100);
        zJointPosSpinBox->setSingleStep(0.1);
        label_19 = new QLabel(centralWidget);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(1120, 430, 61, 16));
        label_19->setAlignment(Qt::AlignCenter);
        label_20 = new QLabel(centralWidget);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(1200, 430, 61, 16));
        label_20->setAlignment(Qt::AlignCenter);
        label_21 = new QLabel(centralWidget);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(1280, 430, 61, 16));
        label_21->setAlignment(Qt::AlignCenter);
        label_22 = new QLabel(centralWidget);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(1120, 450, 54, 12));
        rotXLabel = new QLabel(centralWidget);
        rotXLabel->setObjectName(QStringLiteral("rotXLabel"));
        rotXLabel->setGeometry(QRect(1120, 530, 54, 12));
        label_23 = new QLabel(centralWidget);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(1120, 550, 54, 12));
        rotYLabel = new QLabel(centralWidget);
        rotYLabel->setObjectName(QStringLiteral("rotYLabel"));
        rotYLabel->setGeometry(QRect(1200, 530, 54, 12));
        label_24 = new QLabel(centralWidget);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(1200, 550, 54, 12));
        rotZLabel = new QLabel(centralWidget);
        rotZLabel->setObjectName(QStringLiteral("rotZLabel"));
        rotZLabel->setGeometry(QRect(1280, 530, 54, 12));
        labe_25 = new QLabel(centralWidget);
        labe_25->setObjectName(QStringLiteral("labe_25"));
        labe_25->setGeometry(QRect(1280, 550, 54, 12));
        xPlusPushButton = new QPushButton(centralWidget);
        xPlusPushButton->setObjectName(QStringLiteral("xPlusPushButton"));
        xPlusPushButton->setGeometry(QRect(1120, 570, 51, 20));
        xMinusPushButton = new QPushButton(centralWidget);
        xMinusPushButton->setObjectName(QStringLiteral("xMinusPushButton"));
        xMinusPushButton->setGeometry(QRect(1120, 600, 51, 20));
        yPlusPushButton = new QPushButton(centralWidget);
        yPlusPushButton->setObjectName(QStringLiteral("yPlusPushButton"));
        yPlusPushButton->setGeometry(QRect(1200, 570, 51, 20));
        yMinusPushButton = new QPushButton(centralWidget);
        yMinusPushButton->setObjectName(QStringLiteral("yMinusPushButton"));
        yMinusPushButton->setGeometry(QRect(1200, 600, 51, 20));
        zPlusPushButton = new QPushButton(centralWidget);
        zPlusPushButton->setObjectName(QStringLiteral("zPlusPushButton"));
        zPlusPushButton->setGeometry(QRect(1280, 570, 51, 20));
        zMinusPushButton = new QPushButton(centralWidget);
        zMinusPushButton->setObjectName(QStringLiteral("zMinusPushButton"));
        zMinusPushButton->setGeometry(QRect(1280, 600, 51, 20));
        globalXLabel = new QLabel(centralWidget);
        globalXLabel->setObjectName(QStringLiteral("globalXLabel"));
        globalXLabel->setGeometry(QRect(1120, 370, 54, 12));
        globalYLabel = new QLabel(centralWidget);
        globalYLabel->setObjectName(QStringLiteral("globalYLabel"));
        globalYLabel->setGeometry(QRect(1200, 370, 54, 12));
        globalZLabel = new QLabel(centralWidget);
        globalZLabel->setObjectName(QStringLiteral("globalZLabel"));
        globalZLabel->setGeometry(QRect(1280, 370, 54, 12));
        label_26 = new QLabel(centralWidget);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(1120, 350, 81, 16));
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(1120, 340, 221, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label_27 = new QLabel(centralWidget);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(1120, 390, 81, 16));
        label_28 = new QLabel(centralWidget);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(1120, 470, 54, 12));
        label_29 = new QLabel(centralWidget);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(1120, 510, 54, 12));
        rotYGlobalLabel = new QLabel(centralWidget);
        rotYGlobalLabel->setObjectName(QStringLiteral("rotYGlobalLabel"));
        rotYGlobalLabel->setGeometry(QRect(1200, 490, 54, 12));
        rotZGlobalLabel = new QLabel(centralWidget);
        rotZGlobalLabel->setObjectName(QStringLiteral("rotZGlobalLabel"));
        rotZGlobalLabel->setGeometry(QRect(1280, 490, 54, 12));
        rotXGlobalLabel = new QLabel(centralWidget);
        rotXGlobalLabel->setObjectName(QStringLiteral("rotXGlobalLabel"));
        rotXGlobalLabel->setGeometry(QRect(1120, 490, 54, 12));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1348, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionQuit);
        menuHelp->addAction(actionCamera_Controls);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "OpenGLDemo", Q_NULLPTR));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionCamera_Controls->setText(QApplication::translate("MainWindow", "Camera Controls", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Vertices", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Half-Edges", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Faces", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Vertex Position", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "X", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "Y", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Z", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Blue", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "Red", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "Face Color", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "Green", Q_NULLPTR));
        trangulateButton->setText(QApplication::translate("MainWindow", "Trangulate", Q_NULLPTR));
        midPointPushButton->setText(QApplication::translate("MainWindow", "Midpoint", Q_NULLPTR));
        vertexSet->setText(QApplication::translate("MainWindow", "Vertex", Q_NULLPTR));
        halfEdgeSet->setText(QApplication::translate("MainWindow", "HalfEdge", Q_NULLPTR));
        faceSet->setText(QApplication::translate("MainWindow", "Face", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "Select mode", Q_NULLPTR));
        extrudePushButton->setText(QApplication::translate("MainWindow", "Extrude", Q_NULLPTR));
        smoothPushButton->setText(QApplication::translate("MainWindow", "Smooth", Q_NULLPTR));
        loadObjPushButton->setText(QApplication::translate("MainWindow", "LoadObj", Q_NULLPTR));
        sharpPushButton->setText(QApplication::translate("MainWindow", "Set Sharp", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "Sharpness", Q_NULLPTR));
        label_14->setText(QApplication::translate("MainWindow", "  Face", Q_NULLPTR));
        label_15->setText(QApplication::translate("MainWindow", " Vertex", Q_NULLPTR));
        label_16->setText(QApplication::translate("MainWindow", "Half-edge", Q_NULLPTR));
        skinningPushButton->setText(QApplication::translate("MainWindow", "Skinning", Q_NULLPTR));
        label_17->setText(QApplication::translate("MainWindow", "Joints", Q_NULLPTR));
        loadSkeletonPushButton->setText(QApplication::translate("MainWindow", "LoadSkeleton", Q_NULLPTR));
        label_18->setText(QApplication::translate("MainWindow", "Translation", Q_NULLPTR));
        label_19->setText(QApplication::translate("MainWindow", "X", Q_NULLPTR));
        label_20->setText(QApplication::translate("MainWindow", "Y", Q_NULLPTR));
        label_21->setText(QApplication::translate("MainWindow", "Z", Q_NULLPTR));
        label_22->setText(QApplication::translate("MainWindow", "Rotation", Q_NULLPTR));
        rotXLabel->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_23->setText(QApplication::translate("MainWindow", "  Rotx", Q_NULLPTR));
        rotYLabel->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_24->setText(QApplication::translate("MainWindow", "  RotY", Q_NULLPTR));
        rotZLabel->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        labe_25->setText(QApplication::translate("MainWindow", "  RotZ", Q_NULLPTR));
        xPlusPushButton->setText(QApplication::translate("MainWindow", "X plus", Q_NULLPTR));
        xMinusPushButton->setText(QApplication::translate("MainWindow", "X minus", Q_NULLPTR));
        yPlusPushButton->setText(QApplication::translate("MainWindow", "Y plus", Q_NULLPTR));
        yMinusPushButton->setText(QApplication::translate("MainWindow", "Y minus", Q_NULLPTR));
        zPlusPushButton->setText(QApplication::translate("MainWindow", "Z plus", Q_NULLPTR));
        zMinusPushButton->setText(QApplication::translate("MainWindow", "Z minus", Q_NULLPTR));
        globalXLabel->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        globalYLabel->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        globalZLabel->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_26->setText(QApplication::translate("MainWindow", "Global", Q_NULLPTR));
        label_27->setText(QApplication::translate("MainWindow", "Local", Q_NULLPTR));
        label_28->setText(QApplication::translate("MainWindow", "Global", Q_NULLPTR));
        label_29->setText(QApplication::translate("MainWindow", "Local", Q_NULLPTR));
        rotYGlobalLabel->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        rotZGlobalLabel->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        rotXGlobalLabel->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
