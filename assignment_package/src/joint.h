#ifndef JOINT_H
#define JOINT_H
#include <QTreeWidgetItem>
#include <vector>
#include "la.h"
#include "drawable.h"

// Joint basic class
class Joint: public QTreeWidgetItem
{
public:
    std::string name; // Joint's name
    Joint* parent; // Joint's parent
    std::vector<Joint*> children; // Joint's children
    glm::vec3 position; // Local translation of joint
    glm::quat rotation; // Local orientation of joint
    glm::mat4 bindMatrix; // Inverse transform of given joint

public:
    // Constructor
    Joint();
    Joint(std::string _name, Joint* _parent,
          glm::vec3 _position, glm::quat _rotation);

    // Get local transformation
    glm::mat4 getLocalTransformation();

    // Set bind matrix
    void setBindMatrix();

    // Get global transformation
    glm::mat4 getGlobalTransformation();

    // Get global translation
    glm::vec3 getGlobalTranslation();

    // Get global rotation
    glm::mat3 getGlobalRotation();

    // Get rotation matrix from a quaternion
    glm::mat3 quatToRotation();

    // Get euler angle from a rotation matrix
    glm::vec3 toEulerAngle(glm::mat3 rotation);

    // Get double quat of joint
    glm::mat2x4 getLocalDoubleQuat();

    // Get global transformation for display
    glm::mat4 getGlobalTransformationForDisplay();
};


#endif // JOINT_H
