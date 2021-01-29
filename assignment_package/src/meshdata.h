#ifndef MESHDATA
#define MESHDATA

#include <memory>
#include <iostream>
#include <QListWidgetItem>
#include <unordered_map>

#include "la.h"
#include "openglcontext.h"

class HalfEdge;
class Face;

class Vertex: public QListWidgetItem
{
public:
    glm::vec4 pos; // Position of a vertex
    HalfEdge* edge; // Half edge pointed
    int id; // Vertex's id
    int idx; // Vertex's idx in vector
    static int lastId; // Last id
    bool isSharped; // Sharp
    int sharpCount; // Sharp edge connection count
    std::vector<Vertex*> endPoints; // Sharp end points
    std::vector<float> heSharpness; // Half-edge's sharpness
    float sharpness; // Sharpness of vertex
    std::unordered_map<int, float> weightMap; // Joints' weights

public:
    // Constructor
    Vertex();
    Vertex(int _id);
    Vertex(glm::vec4& _pos, std::unique_ptr<HalfEdge> _edge, int _id);
};

class HalfEdge: public QListWidgetItem
{
public:
    HalfEdge* nextEdge; // Next half edge
    HalfEdge* symEdge; // Symmetrical edge
    Face* face; // Face pointed
    Vertex* nextVertex; // Next vertex
    int id; // Half edge's id
    static int lastId; // Last id
    bool isSharped; // Sharp
    float sharpness; // Sharpness of halfedge

public:
    // Constructor
    HalfEdge();
    HalfEdge(int _id);
    HalfEdge(std::unique_ptr<HalfEdge> _nextEdge,
             std::unique_ptr<HalfEdge> _symEdge,
             std::unique_ptr<Face> _face,
             std::unique_ptr<Vertex> _nextVertex, int _id);
};

class Face: public QListWidgetItem
{
public:
    HalfEdge* edge; // Half edge pointed
    glm::vec4 color; // Face's color
    glm::vec4 normal; // Face's normal
    int id; // Face's id;
    static int lastId; // Last id
    bool isMid; // Midpoint set flag
    bool isSharped; // Sharp
    float sharpness; // Sharpness of face

public:
    // Constructor
    Face();
    Face(int _id);
    Face(glm::vec4& _color, std::unique_ptr<HalfEdge> _edge, int _id);
};

#endif // MESHDATA




