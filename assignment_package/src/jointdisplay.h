#ifndef JOINTDISPLAY_H
#define JOINTDISPLAY_H
#include "drawable.h"
#include "joint.h"

class JointDisplay: public Drawable
{
    friend class MainWindow;
    friend class MyGL;
public:
    Joint* representedJoint;

public:
    void create();
    GLenum drawMode();
    void setJoint(Joint* _joint);

    // Constructor
    JointDisplay(OpenGLContext* context);

    // Destructor
    ~JointDisplay();

    // Selected flag
    bool isSelected;
};

#endif // JOINTDISPLAY_H
