#include "joint.h"
#include <cmath>
#include "utils.h"

// Constructor
Joint::Joint() {}

Joint::Joint(std::string _name, Joint* _parent,
             glm::vec3 _position, glm::quat _rotation):
    name(_name), parent(_parent),
    position(_position), rotation(_rotation) {}

// Get local transformation
glm::mat4 Joint::getLocalTransformation()
{
    glm::mat4 localRotation = glm::mat4_cast(rotation);
    return glm::transpose(glm::translate(glm::mat4(1.0f), position) * localRotation);
}

// Get global transform
glm::mat4 Joint::getGlobalTransformation()
{
    glm::mat4 result = glm::mat4();
    Joint* curJoint = this;
    while(curJoint != nullptr)
    {
        glm::mat4 local = curJoint->getLocalTransformation();
        result = local * result;
        curJoint = curJoint->parent;
    }
    return result;
}

// Set bind matrix
void Joint::setBindMatrix()
{
    glm::mat4 globalMatrix = getGlobalTransformation();

    glm::mat3 globalRotation = glm::mat3(
                glm::vec3(globalMatrix[0][0], globalMatrix[0][1], globalMatrix[0][2]),
                glm::vec3(globalMatrix[1][0], globalMatrix[1][1], globalMatrix[1][2]),
                glm::vec3(globalMatrix[2][0], globalMatrix[2][1], globalMatrix[2][2])
                );

    glm::vec3 globalTranslation = glm::vec3(globalMatrix[0][3],
                                            globalMatrix[1][3],
                                            globalMatrix[2][3]);

    glm::mat3 inverseRotation = glm::transpose(globalRotation);
    glm::vec3 inverseTranslation = -inverseRotation * globalTranslation;

    bindMatrix =  glm::mat4(
                    glm::vec4(inverseRotation[0][0], inverseRotation[0][1], inverseRotation[0][2], inverseTranslation[0]),
                    glm::vec4(inverseRotation[1][0], inverseRotation[1][1], inverseRotation[1][2], inverseTranslation[1]),
                    glm::vec4(inverseRotation[2][0], inverseRotation[2][1], inverseRotation[2][2], inverseTranslation[2]),
                    glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
                 );
}

// Get rotation matrix from a quaternion
glm::mat3 Joint::quatToRotation()
{
    return glm::mat3_cast(rotation);
}

// Get global translation
glm::vec3 Joint::getGlobalTranslation()
{
    glm::mat4 globalTransform = getGlobalTransformation();
    return glm::vec3(globalTransform[0][3],
                     globalTransform[1][3],
                     globalTransform[2][3]);
}

// Get global rotation
glm::mat3 Joint::getGlobalRotation()
{
    glm::mat4 globalTransform = getGlobalTransformation();
    return glm::transpose(glm::mat3(globalTransform));
}

// Get euler angle
glm::vec3 Joint::toEulerAngle(glm::mat3 rot)
{
    glm::vec3 angleRad = glm::vec3(0.0f);
    angleRad[2] = asin(rot[0][2]);

    if (!fequal(angleRad[2], float(-M_PI_2))
            && (angleRad[2] > float(-M_PI_2)))
    {
        if (!fequal(angleRad[2], float(M_PI_2)) && angleRad[1] < float(M_PI_2))
        {
            angleRad[0] = atan2(-rot[1][2], rot[2][2]);
            angleRad[2] = atan2(-rot[0][1], rot[0][0]);
        }
        else
        {
            angleRad[2] = 0.0f;
            angleRad[0] = atan2(rot[1][0], rot[1][1]);
        }
    }
    else
    {
        angleRad[2] = 0.0f;  // any angle works
        angleRad[0] = -atan2(rot[1][0], rot[1][1]);
    }
    return angleRad;
}


glm::mat2x4 Joint::getLocalDoubleQuat()
{
    glm::mat4 transMat = getGlobalTransformation();
    glm::mat3x4 transform = glm::mat3x4(
                                glm::vec4(transMat[0][0], transMat[0][1], transMat[0][2], transMat[0][3]),
                                glm::vec4(transMat[1][0], transMat[1][1], transMat[1][2], transMat[1][3]),
                                glm::vec4(transMat[2][0], transMat[2][1], transMat[2][2], transMat[2][3]));

    glm::dualquat localDualQuat = glm::dualquat_cast(transform);
    glm::mat2x4 localDualQuatMat = glm::mat2x4_cast(localDualQuat);
    return localDualQuatMat;
}

glm::mat4 Joint::getGlobalTransformationForDisplay()
{
    glm::mat4 result = glm::mat4();
    Joint* curJoint = this;
    while(curJoint != nullptr)
    {
        glm::mat4 local = curJoint->getLocalTransformation();
        local = glm::transpose(local);
        result = glm::transpose(result);
        result = glm::transpose(local * result);
        curJoint = curJoint->parent;
    }
    return result;
}
