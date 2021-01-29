#include "skeleton.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <fStream>
#include <cmath>

Skeleton::Skeleton():
    isEmpty(true) {}

// Read skeleton data from json filess
void Skeleton::constructSkeleton()
{
    isEmpty = false;

    std::ifstream fileIn;
    fileIn.open(fileNameStd);

    // Convert string to json data
    std::string content((std::istreambuf_iterator<char>(fileIn)),
                        std::istreambuf_iterator<char>());
    QByteArray qContent = QString::fromStdString(content).toUtf8();
    int size = content.size();
    const char* data = content.c_str();
    QJsonDocument jsonContent = QJsonDocument();
    jsonContent = jsonContent.fromJson(qContent);

    // Read json content
    if(!jsonContent.isNull())
    {
        // Get root of skeleton
        QJsonObject rootObject = (jsonContent.object())["root"].toObject();
        setJoint(rootObject, nullptr);
    }
}

void Skeleton::setJoint(QJsonObject &jointObject, Joint *parent)
{
    std::unique_ptr<Joint> jsonJoint = std::make_unique<Joint>();
    if(parent == nullptr)
    {
        rootJoint = jsonJoint.get();
        jsonJoint->parent = nullptr;
    }
    else
    {
        jsonJoint->parent = parent;
        parent->children.push_back(jsonJoint.get());
        parent->addChild(jsonJoint.get());
    }
    // Set joint name
    jsonJoint->name = jointObject[QString("name")].toString().toStdString();
    jsonJoint->setText(0, jointObject[QString("name")].toString());

    // Set joint position
    QJsonArray jsonPosition = jointObject[QString("pos")].toArray();
    jsonJoint->position = glm::vec3(jsonPosition[0].toDouble(), jsonPosition[1].toDouble(), jsonPosition[2].toDouble());

    // Set joint rotation
    QJsonArray jsonRotation = jointObject[QString("rot")].toArray();
    double angle = jsonRotation[0].toDouble();
    glm::vec3 axis = glm::normalize(glm::vec3(jsonRotation[1].toDouble(),
                                              jsonRotation[2].toDouble(),
                                              jsonRotation[3].toDouble()));
    jsonJoint->rotation = glm::angleAxis(float(angle), axis);

    // Set joint children
    QJsonArray jsonChildren = jointObject[QString("children")].toArray();
    for(int i = 0; i < jsonChildren.size(); i++)
    {
        QJsonObject jsonChild = jsonChildren[i].toObject();
        setJoint(jsonChild, jsonJoint.get());
    }
    joints.push_back(std::move(jsonJoint));
}
