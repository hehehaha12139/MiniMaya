#include "meshdata.h"

int Vertex::lastId = 0;

Vertex::Vertex():
    isSharped(false),
    sharpCount(0),
    sharpness(1.0f)
{
    id = lastId;
    lastId++;
    QString name = QString::number(this->id);
    QListWidgetItem::setText(name);
}

Vertex::Vertex(int _id):
    id(_id) {}

Vertex::Vertex(glm::vec4& _pos, std::unique_ptr<HalfEdge> _edge, int _id):
    pos(_pos), edge(_edge.get()), id(_id) {}


int HalfEdge::lastId = 0;

HalfEdge::HalfEdge():
    isSharped(false),
    sharpness(1.0f)
{
    id = lastId;
    lastId++;
    QString name = QString::number(this->id);
    QListWidgetItem::setText(name);
}

HalfEdge::HalfEdge(int _id):
    id(_id) {}

HalfEdge::HalfEdge(std::unique_ptr<HalfEdge> _nextEdge,
                   std::unique_ptr<HalfEdge> _symEdge,
                   std::unique_ptr<Face> _face,
                   std::unique_ptr<Vertex> _nextVertex, int _id):
    nextEdge(_nextEdge.get()), symEdge(_symEdge.get()),
    face(_face.get()), nextVertex(_nextVertex.get()), id(_id) {}

int Face::lastId = 0;

Face::Face():
    isMid(false),
    isSharped(false),
    sharpness(1.0f)
{
    id = lastId;
    lastId++;
    QString name = QString::number(this->id);
    QListWidgetItem::setText(name);
}

Face::Face(int _id):
    id(_id) {}

Face::Face(glm::vec4& _color, std::unique_ptr<HalfEdge> _edge, int _id):
    color(_color), edge(_edge.get()), id(_id) {}

