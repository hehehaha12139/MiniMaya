#include "jointdisplay.h"

JointDisplay::JointDisplay(OpenGLContext* context):
    Drawable(context), representedJoint(nullptr),
    isSelected(false) {}

void JointDisplay::setJoint(Joint* _joint)
{
    representedJoint = _joint;
}

void JointDisplay::create()
{
    if(representedJoint == nullptr)
    {
        return;
    }

    // Get joint global position
    glm::mat4 globalTransform = representedJoint->getGlobalTransformationForDisplay();
    glm::vec3 jPos = glm::vec3(globalTransform[0][3],
                               globalTransform[1][3],
                               globalTransform[2][3]);

    glm::mat4 parentTransform = representedJoint->parent->getGlobalTransformationForDisplay();
    glm::vec3 pPos = glm::vec3(parentTransform[0][3],
                               parentTransform[1][3],
                               parentTransform[2][3]);

    //glm::vec3 jPos = representedJoint->position;
    std::vector<glm::vec4> pos;
    std::vector<glm::vec4> nor;
    std::vector<glm::vec4> col;
    std::vector<GLuint> idx;

    float radius = 0.5;

    // X-axis rotation
    for(int i = 0; i < 12; i++)
    {
        pos.push_back(glm::vec4(jPos.x, jPos.y + radius * sin(glm::radians(i * 30.0f)), jPos.z + radius * cos(glm::radians(i * 30.0f)), 1.0f));
        if(isSelected)
        {
            col.push_back(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
        }
        else
        {
            col.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        }
        nor.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        if(i == 11)
        {
            idx.push_back(i);
            idx.push_back(0);
        }
        else
        {
            idx.push_back(i);
            idx.push_back(i + 1);
        }
    }

    // Y-axis rotation
    for(int i = 0; i < 12; i++)
    {
        pos.push_back(glm::vec4(jPos.x + radius * cos(glm::radians(i * 30.0f)), jPos.y, jPos.z + radius * sin(glm::radians(i * 30.0f)), 1.0f));
        nor.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        if(isSelected)
        {
            col.push_back(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
        }
        else
        {
            col.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        }
        if(i == 11)
        {
            idx.push_back(12 + i);
            idx.push_back(12);
        }
        else
        {
            idx.push_back(12 + i);
            idx.push_back(12 + i + 1);
        }
    }

    // Z-axis rotation
    for(int i = 0; i < 12; i++)
    {
        pos.push_back(glm::vec4(jPos.x + radius * sin(glm::radians(i * 30.0f)), jPos.y + radius * cos(glm::radians(i * 30.0f)), jPos.z, 1.0f));
        nor.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        if(isSelected)
        {
            col.push_back(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
        }
        else
        {
            col.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        }
        if(i == 11)
        {
            idx.push_back(24 + i);
            idx.push_back(24);
        }
        else
        {
            idx.push_back(24 + i);
            idx.push_back(24 + i + 1);
        }
    }

    // Set parentConnection
    if(representedJoint->parent != nullptr)
    {
        pos.push_back(glm::vec4(jPos, 1.0f));
        nor.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        col.push_back(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
        idx.push_back(36);
        pos.push_back(glm::vec4(pPos, 1.0f));
        nor.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        col.push_back(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
        col.push_back(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
        idx.push_back(37);
    }

    count = idx.size();

    generatePos();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    mp_context->glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(glm::vec4), pos.data(), GL_STATIC_DRAW);

    generateNor();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufNor);
    mp_context->glBufferData(GL_ARRAY_BUFFER, nor.size() * sizeof(glm::vec4), nor.data(), GL_STATIC_DRAW);

    generateCol();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    mp_context->glBufferData(GL_ARRAY_BUFFER, col.size() * sizeof(glm::vec4), col.data(), GL_STATIC_DRAW);

    generateIdx();
    mp_context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    mp_context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx.size() * sizeof(GLuint), idx.data(), GL_STATIC_DRAW);
}

GLenum JointDisplay::drawMode()
{
    return GL_LINES;
}

JointDisplay::~JointDisplay() {}



