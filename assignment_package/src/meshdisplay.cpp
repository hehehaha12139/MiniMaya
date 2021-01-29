#include "meshdisplay.h"

// Vertex display
void VertexDisplay::create()
{
    if(representedVertex == nullptr)
    {
        return;
    }

    std::vector<glm::vec4> pos;
    pos.push_back(representedVertex->pos);

    std::vector<glm::vec4> nor;
    nor.push_back(glm::vec4(0.0, 0.0, 1.0, 1.0));

    std::vector<glm::vec4> col;
    col.push_back(glm::vec4(1.0, 1.0, 0.0, 1.0));

    std::vector<GLuint> idx{0};

    count = 1;

    generatePos();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    mp_context->glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4), pos.data(), GL_STATIC_DRAW);

    generateNor();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufNor);
    mp_context->glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4), nor.data(), GL_STATIC_DRAW);

    generateCol();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    mp_context->glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4), col.data(), GL_STATIC_DRAW);

    generateIdx();
    mp_context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    mp_context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint), idx.data(), GL_STATIC_DRAW);
}

GLenum VertexDisplay::drawMode()
{
    return GL_POINTS;
}

void VertexDisplay::updateVertex(Vertex* v)
{
    representedVertex = v;
}

void VertexDisplay::changePosX(double x)
{
    representedVertex->pos.x = x;
}

void VertexDisplay::changePosY(double y)
{

}

void VertexDisplay::changePosZ(double z)
{
    representedVertex->pos.z = z;
}

VertexDisplay::VertexDisplay(OpenGLContext* context):
    Drawable(context)
{
    representedVertex = nullptr;
}

bool VertexDisplay::isNull()
{
    if(representedVertex == nullptr)
    {
        return true;
    }
    return false;
}


VertexDisplay::~VertexDisplay() {}

// Half-edge display
HalfEdgeDisplay::HalfEdgeDisplay(OpenGLContext *context):
    Drawable(context)
{
    representedHalfEdge = nullptr;
}

void HalfEdgeDisplay::create()
{
    if(representedHalfEdge == nullptr)
    {
        return;
    }

    std::vector<glm::vec4> pos;
    std::vector<glm::vec4> nor;
    std::vector<glm::vec4> col;
    std::vector<GLuint> idx;

    pos.push_back(representedHalfEdge->symEdge->nextVertex->pos);
    pos.push_back(representedHalfEdge->nextVertex->pos);

    col.push_back(glm::vec4(1.0, 0.0, 0.0, 1.0));
    col.push_back(glm::vec4(1.0, 1.0, 0.0, 1.0));

    nor.push_back(glm::vec4(0.0, 0.0, 1.0, 1.0));
    nor.push_back(glm::vec4(0.0, 0.0, 1.0, 1.0));

    idx.push_back(0);
    idx.push_back(1);

    count = 2;

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

GLenum HalfEdgeDisplay::drawMode()
{
    return GL_LINES;
}

void HalfEdgeDisplay::updateHalfEdge(HalfEdge* he)
{
    representedHalfEdge = he;
}

bool HalfEdgeDisplay::isNull()
{
    if(representedHalfEdge == nullptr)
    {
        return true;
    }
    return false;
}

HalfEdgeDisplay::~HalfEdgeDisplay() {}

// Face display
FaceDisplay::FaceDisplay(OpenGLContext *context):
    Drawable(context)
{
    representedFace = nullptr;
}

void FaceDisplay::create()
{
    if(representedFace == nullptr)
    {
        return;
    }

    std::vector<glm::vec4> pos;
    std::vector<glm::vec4> nor;
    std::vector<glm::vec4> col;
    std::vector<GLuint> idx;

    HalfEdge* first = representedFace->edge;
    int i = 0;
    do
    {
        // Push half-edge's vertices
        pos.push_back(first->nextVertex->pos);
        pos.push_back(first->nextEdge->nextVertex->pos);

        // Push vertices' color
        col.push_back(glm::vec4(1.0) - representedFace->color);
        col.push_back(glm::vec4(1.0) - representedFace->color);

        // Push vertices' normal
        nor.push_back(glm::vec4(0.0, 0.0, 1.0, 1.0));
        nor.push_back(glm::vec4(0.0, 0.0, 1.0, 1.0));

        // Push indices
        idx.push_back(i);
        idx.push_back(i + 1);
        i += 2;

        // Next edge
        first = first->nextEdge;
    }while(first != representedFace->edge);

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

// Change color
void FaceDisplay::changeColorR(double r)
{
    representedFace->color.x = r;
}

void FaceDisplay::changeColorG(double g)
{
    representedFace->color.y = g;
}

void FaceDisplay::changeColorB(double b)
{
    representedFace->color.z = b;
}

GLenum FaceDisplay::drawMode()
{
    return GL_LINES;
}

void FaceDisplay::updateFace(Face *f)
{
    representedFace = f;
}

bool FaceDisplay::isNull()
{
    if(representedFace == nullptr)
    {
        return true;
    }
    return false;
}

FaceDisplay::~FaceDisplay() {}
