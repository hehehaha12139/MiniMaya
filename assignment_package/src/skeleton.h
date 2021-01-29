#ifndef SKELETON_H
#define SKELETON_H
#include <memory>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include "joint.h"

class Skeleton
{
public:
    Joint* rootJoint; // Skeleton's root
    std::vector<std::unique_ptr<Joint>> joints; // All joints of skeleton
    std::string fileNameStd; // Skeleton file name
    bool isEmpty;

public:
    // Constructor
    Skeleton();

    // Read joint data from json file
    void constructSkeleton();

private:
    void setJoint(QJsonObject& jointObject, Joint* parent);
};

#endif // SKELETON_H
