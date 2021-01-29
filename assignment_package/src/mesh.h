#ifndef MESH
#define MESH
#include <vector>
#include "meshdata.h"
#include "drawable.h"
#include "openglcontext.h"
#include "skeleton.h"
#include "jointdisplay.h"

class Mesh: public Drawable
{
    Q_OBJECT
public:
    std::vector<std::unique_ptr<Face>> faces;
    std::vector<std::unique_ptr<HalfEdge>> halfEdges;
    std::vector<std::unique_ptr<Vertex>> vertices;
    HalfEdge* heRoot;
    glm::mat4 curModel;
    bool isLoadObj;
    std::string fileNameStd;
    int faceVerticesCount;
    Skeleton meshSkeleton;
    std::vector<std::unique_ptr<JointDisplay>> jointdisplays; // Joint display components
    int selectedId;
    GLuint bufWeight; // Weight buffer
    GLuint bufJointIndex; // Weight Index

    bool weightBound;
    bool weightIdxBound;

public:
    // Constructor
    Mesh(OpenGLContext* context, QObject* parent = Q_NULLPTR);

    // Construct a cube mesh
    void constructCube();

    // Construct a mesh from file
    void constructFileMesh(std::string& fileName);

    // Destructor
    ~Mesh();
    // Create function
    void create();

    // Update data
    void update();

    // Add a midPoint
    void addMidPoint(HalfEdge* he);

    // Triangulate half-edge mesh data
    void triangulate(Face* f);

    // Find nearest mesh data structure
    Face* findNearestFace(glm::vec3 rayD, glm::vec3 eye);
    HalfEdge* findNearestHalfEdge(glm::vec3 ray, glm::vec3 eye);
    Vertex* findNearestVertex(glm::vec3 ray, glm::vec3 eye);

    // Planarity test
    void planarityTest(Face* face);
    void planar();

    // Subdivision
    void smooth();

    // Extrude
    void extrude(Face* face);

    // Heat-diffusion skinning
    void setJointWeights();

    // Load skeleton
    void loadSkeleton(QString& path);

    // Update jointDisplay
    void updateJoints();

    // Generare buffers
    void generateWeight();
    void generateWeightIdx();

    bool bindWeight();
    bool bindWeightIdx();

signals:
    // Send vertices to list widget
    void sendVertex(Vertex* v);

    // Send faces to list widget
    void sendFace(Face* f);

    // Send half-edges to list widget
    void sendHalfEdge(HalfEdge* he);

    // Send skeleton root
    void sendRoot(QTreeWidgetItem*);
};

#endif // MESH

