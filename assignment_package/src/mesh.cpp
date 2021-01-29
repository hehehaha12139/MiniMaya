#include "mesh.h"
#include "utils.h"
#include <cmath>
#include <fStream>
#include <map>
#include <unordered_map>
#include <sstream>
#include <QFileDialog>
#include <QDir>
#include <random>
#include <ctime>
#include <array>

Mesh::Mesh(OpenGLContext* context, QObject* parent):
    Drawable(context, parent), isLoadObj(false), selectedId(-1) {}

void Mesh::create()
{
    // Construct half-edge data structure
    if(!isLoadObj)
    {
        Vertex::lastId = 0;
        HalfEdge::lastId = 0;
        Face::lastId = 0;
        constructCube();
    }
    else
    {
        Vertex::lastId = 0;
        HalfEdge::lastId = 0;
        Face::lastId = 0;
        constructFileMesh(fileNameStd);
    }




    // Set data vector
    std::vector<glm::vec4> pos;
    std::vector<glm::vec4> col;
    std::vector<glm::vec4> nor;
    std::vector<GLuint> idx;

    count = 0;

    for(int i = 0; i <  faces.size(); i++)
    {
        HalfEdge* first = faces[i]->edge;
        GLuint prePosCount = pos.size();
        do {
            Vertex* curVertex = first->nextVertex;

            Vertex* lastVert = first->symEdge->nextVertex;
            Vertex* nextVert = first->nextEdge->nextVertex;
            glm::vec3 edge1 = glm::vec3(curVertex->pos - lastVert->pos);
            glm::vec3 edge2 = glm::vec3(nextVert->pos - curVertex->pos);

            glm::vec4 normal = glm::vec4(glm::normalize(glm::cross(edge1, edge2)), 0.0f);

            if(fequal(glm::length(normal), 0.0f))
            {
                normal = faces[i]->normal;
                continue;
            }

            nor.push_back(normal);
            pos.push_back(curVertex->pos);
            //int n = 0;
            //col.push_back(glm::vec4(curVertex->weightMap[n], curVertex->weightMap[n], curVertex->weightMap[n], 1.0f));
            col.push_back(faces[i]->color);
            first = first->nextEdge;
        }while(first != faces[i] -> edge);
        GLuint postPosCount = pos.size();
        for(int j = 0; j < postPosCount - prePosCount - 2; j++)
        {
            idx.push_back(prePosCount);
            idx.push_back(prePosCount + j + 1);
            idx.push_back(prePosCount + j + 2);
            count += 3;
        }
    }

    // Configure position vbo
    generatePos();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    mp_context->glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(glm::vec4), pos.data(), GL_STATIC_DRAW);

    // Configure color vbos
    generateCol();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    mp_context->glBufferData(GL_ARRAY_BUFFER, col.size() * sizeof(glm::vec4), col.data(), GL_STATIC_DRAW);

    // Configure normal vbo
    generateNor();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufNor);
    mp_context->glBufferData(GL_ARRAY_BUFFER, nor.size() * sizeof(glm::vec4), nor.data(), GL_STATIC_DRAW);

    // Configure index buffer
    generateIdx();
    mp_context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    mp_context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx.size() * sizeof(GLuint), idx.data(), GL_STATIC_DRAW);
}

void Mesh::constructCube()
{

    // Face indices
    int index[] = {1, 0, 3, 2,
                   0, 1, 5, 4,
                   1, 2, 6, 5,
                   3, 0, 4, 7,
                   4, 5, 6, 7,
                   2, 3, 7, 6
                  };

    // Add vertices
    for(int i = 0; i < 8; i++)
    {
        std::unique_ptr<Vertex> currentVertex = std::make_unique<Vertex>();
        currentVertex->idx = i;
        emit sendVertex(currentVertex.get());
        vertices.push_back(move(currentVertex));
    }

    // Set positions
    vertices[0]->pos = glm::vec4(-0.5, -0.5, 0.5, 1.0);
    vertices[1]->pos = glm::vec4(0.5, -0.5, 0.5, 1.0);
    vertices[2]->pos = glm::vec4(0.5, -0.5, -0.5, 1.0);
    vertices[3]->pos = glm::vec4(-0.5, -0.5, -0.5, 1.0);
    vertices[4]->pos = glm::vec4(-0.5, 0.5, 0.5, 1.0);
    vertices[5]->pos = glm::vec4(0.5, 0.5, 0.5, 1.0);
    vertices[6]->pos = glm::vec4(0.5, 0.5, -0.5, 1.0);
    vertices[7]->pos = glm::vec4(-0.5, 0.5, -0.5, 1.0);

    // Set faces and half-edges
    for(int i = 0; i < 6; i++)
    {
        // Create face
        std::unique_ptr<Face> currentFace = std::make_unique<Face>();

        for(int j = 0; j < 4; j++)
        {
            // Create half edge
            std::unique_ptr<HalfEdge> currentEdge = std::make_unique<HalfEdge>();
            currentEdge->face = currentFace.get();

            // Store face
            currentFace->edge = currentEdge.get();

            // Store vertex
            int in = index[4 * i + j];
            currentEdge->nextVertex = vertices[in].get();
            currentEdge->nextVertex->edge = currentEdge.get();

            // Store next half edge
            if(j != 0)
            {
                halfEdges[4 * i + j - 1]->nextEdge = currentEdge.get();

                // Set sym pointer
                for(int k = 0; k < faces.size(); k++)
                {
                    HalfEdge* comEdge = faces[k]->edge;
                    do
                    {
                        if(comEdge->nextVertex == currentEdge->nextVertex
                           && comEdge->nextEdge->nextVertex
                              == halfEdges[4 * i + j -1]->nextVertex)
                        {
                            comEdge->nextEdge->symEdge = currentEdge.get();
                            currentEdge->symEdge = comEdge -> nextEdge;
                        }
                        comEdge = comEdge->nextEdge;
                    }while(comEdge != faces[k]->edge);
                }
            }

            if(j == 3)
            {
                currentEdge->nextEdge = halfEdges[4 * i + j - 3].get();

                // Set first edge's sym pointer
                for(int k = 0; k < faces.size(); k++)
                {
                    HalfEdge* comEdge = faces[k]->edge;
                    do
                    {
                        if(comEdge->nextVertex == halfEdges[4 * i + j - 3]->nextVertex
                           && comEdge->nextEdge->nextVertex
                              == currentEdge->nextVertex)
                        {
                            comEdge->nextEdge->symEdge = halfEdges[4 * i + j - 3].get();
                            halfEdges[4 * i + j - 3]->symEdge = comEdge->nextEdge;
                        }
                        comEdge = comEdge->nextEdge;
                    }while(comEdge != faces[k]->edge);
                }

            }

            // Add half edge to vector
            emit sendHalfEdge(currentEdge.get());
            halfEdges.push_back(std::move(currentEdge));
        }


        // Add face to vector
        emit sendFace(currentFace.get());
        faces.push_back(std::move(currentFace));
    }

    // Configure faces normal
    faces[0]->normal = glm::vec4(0.0, -1.0, 0.0, 1.0);
    faces[1]->normal = glm::vec4(0.0, 0.0, 1.0, 1.0);
    faces[2]->normal = glm::vec4(1.0, 0.0, 0.0, 1.0);
    faces[3]->normal = glm::vec4(-1.0, 0.0, 0.0, 1.0);
    faces[4]->normal = glm::vec4(0.0, 1.0, 0.0, 1.0);
    faces[5]->normal = glm::vec4(0.0, 0.0, -1.0, 1.0);

    // Configure faces color
    faces[0]->color = glm::vec4(0.0, 0.0, 1.0, 1.0);
    faces[1]->color = glm::vec4(0.0, 0.0, 1.0, 1.0);
    faces[2]->color = glm::vec4(0.0, 0.0, 1.0, 1.0);
    faces[3]->color = glm::vec4(0.0, 0.0, 1.0, 1.0);
    faces[4]->color = glm::vec4(0.0, 0.0, 1.0, 1.0);
    faces[5]->color = glm::vec4(0.0, 0.0, 1.0, 1.0);
}

void Mesh::triangulate(Face* f)
{
    HalfEdge* he0 = f->edge;
    HalfEdge* first = f->edge;
    int count = 0;
    do
    {
        count += 1;
        first = first->nextEdge;
    }while(first->nextEdge != he0);

    if(count == 2)
    {
        return;
    }

    do
    {
        // Create two central half-edge
        std::unique_ptr<HalfEdge> newHeA = std::make_unique<HalfEdge>();
        std::unique_ptr<HalfEdge> newHeB = std::make_unique<HalfEdge>();

        // Set vertex pointer of central half-edge
        newHeA->nextVertex = first->nextVertex;
        newHeB->nextVertex = he0->nextEdge->nextVertex;

        // Set symmetric pointer
        newHeA->symEdge = newHeB.get();
        newHeB->symEdge = newHeA.get();

        // Create second face
        std::unique_ptr<Face> newFace = std::make_unique<Face>();
        newFace->normal = f->normal;

        // Set face pointers
        newHeA->face = f;
        he0->face = f;
        he0->nextEdge->nextEdge->face = newFace.get();
        f->edge = newHeA.get();
        newFace->edge = newHeB.get();
        newFace->color = f->color;

        // Set nextEdge pointers
        newHeB->nextEdge = he0->nextEdge->nextEdge;
        he0->nextEdge->nextEdge = newHeA.get();
        newHeA->nextEdge = he0;

        // Add new face
        f = newFace.get();
        emit sendFace(newFace.get());
        faces.push_back(std::move(newFace));

        // Add two central half-edge
        emit sendHalfEdge(newHeA.get());
        emit sendHalfEdge(newHeB.get());
        halfEdges.push_back(std::move(newHeA));
        halfEdges.push_back(std::move(newHeB));

        // Next edge
        he0 = he0->nextEdge->nextEdge->symEdge;
    }while(he0->nextEdge->nextEdge != first);

    // Set last edge's face
    first->face = f;
    first->nextEdge = he0;
}

void Mesh::update()
{
    // Set data vector
    std::vector<glm::vec4> pos;
    std::vector<glm::vec4> col;
    std::vector<glm::vec4> nor;
    std::vector<GLuint> idx;
    std::vector<glm::ivec4> jointIndex; // Joint indices
    std::vector<glm::vec4> jointMaxWeight; // Joint weights

    count = 0;

    for(int i = 0; i <  faces.size(); i++)
    {
        HalfEdge* first = faces[i]->edge;
        GLuint prePosCount = pos.size();
        do {
            Vertex* curVertex = first->nextVertex;

            std::vector<float> jointWeight;
            std::vector<float> jointSumWeight;
            std::vector<int> jointWeightIndices;
            std::unordered_map<int, bool> maxMap;

            if(curVertex->id == 2181)
            {
                std::cout<<std::endl;
            }

            if(!meshSkeleton.isEmpty)
            {
                // Normalize all joint weight and transfer it into buffer
                float totalWeight = 0.0f;
                for(int j = 0; j < meshSkeleton.joints.size(); j++)
                {
                    jointWeight.push_back(curVertex->weightMap[j]);
                    //maxMap[curVertex->weightMap[j]] = j;
                }

                for(int j = 0; j < 4; j++)
                {
                    if(jointWeight.empty())
                    {
                        jointWeightIndices.push_back(-1);
                        jointSumWeight.push_back(0.0f);
                    }


                    float maxWeight = 0.0;
                    float maxIndex = -1;
                    for(int k = 0; k < jointWeight.size(); k++)
                    {
                        if(fequal(std::fmax(jointWeight[k], maxWeight), jointWeight[k]))
                        {
                            if(!maxMap[k])
                            {
                                maxWeight = jointWeight[k];
                                maxMap[maxIndex] = false;
                                maxIndex = k;
                                maxMap[k] = true;
                            }
                        }
                    }
                    jointSumWeight.push_back(jointWeight[maxIndex]);
                    jointWeightIndices.push_back(maxIndex);
                    totalWeight += jointWeight[maxIndex];
                }

//                if(!fequal(jointSumWeight[0], 0.05f), jointSumWeight[0] < 0.05f)
//                {
//                    jointSumWeight[0] = 0.0f;
//                    jointSumWeight[1] = 0.0f;
//                    jointSumWeight[2] = 0.0f;
//                    jointSumWeight[3] = 0.0f;
//                }

                for(int j = 0; j < 4; j++)
                {
                    jointSumWeight[j] = jointSumWeight[j] / totalWeight;
                }

                glm::vec4 jointWeightVec = glm::vec4(jointSumWeight[0],
                                                     jointSumWeight[1],
                                                     jointSumWeight[2],
                                                     jointSumWeight[3]);

                jointMaxWeight.push_back(jointWeightVec);

                jointIndex.push_back(glm::ivec4(jointWeightIndices[0],
                                               jointWeightIndices[1],
                                               jointWeightIndices[2],
                                               jointWeightIndices[3]));
            }

            Vertex* lastVert = first->symEdge->nextVertex;
            Vertex* nextVert = first->nextEdge->nextVertex;
            glm::vec3 edge1 = glm::vec3(curVertex->pos - lastVert->pos);
            glm::vec3 edge2 = glm::vec3(nextVert->pos - curVertex->pos);

            glm::vec4 normal = glm::vec4(glm::normalize(glm::cross(edge1, edge2)), 0.0f);

            if(std::isnan(normal.x))
            {
                normal = faces[i]->normal;
            }

            nor.push_back(normal);
            pos.push_back(curVertex->pos);
            //int n = 1;
            //float color = curVertex->weightMap[n];
            //col.push_back(glm::vec4(curVertex->weightMap[0], curVertex->weightMap[1], curVertex->weightMap[13], 1.0f));
            col.push_back(faces[i]->color);

            first = first->nextEdge;
        }while(first != faces[i] -> edge);
        GLuint postPosCount = pos.size();
        for(int j = 0; j < postPosCount - prePosCount - 2; j++)
        {
            idx.push_back(prePosCount);
            idx.push_back(prePosCount + j + 1);
            idx.push_back(prePosCount + j + 2);
            count += 3;
        }
    }

    // Configure position vbo
    generatePos();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    mp_context->glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(glm::vec4), pos.data(), GL_STATIC_DRAW);

    // Configure color vbo
    generateCol();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    mp_context->glBufferData(GL_ARRAY_BUFFER, col.size() * sizeof(glm::vec4), col.data(), GL_STATIC_DRAW);

    // Configure normal vbo
    generateNor();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufNor);
    mp_context->glBufferData(GL_ARRAY_BUFFER, nor.size() * sizeof(glm::vec4), nor.data(), GL_STATIC_DRAW);

    // Configure index buffer
    generateIdx();
    mp_context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    mp_context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx.size() * sizeof(GLuint), idx.data(), GL_STATIC_DRAW);

    // Configure weight buffer
    generateWeight();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufWeight);
    mp_context->glBufferData(GL_ARRAY_BUFFER, jointMaxWeight.size() * sizeof(glm::vec4), jointMaxWeight.data(), GL_STATIC_DRAW);

    // Configure weight index buffer
    generateWeightIdx();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufJointIndex);
    mp_context->glBufferData(GL_ARRAY_BUFFER, jointIndex.size() * sizeof(glm::ivec4), jointIndex.data(), GL_STATIC_DRAW);
}

void Mesh::addMidPoint(HalfEdge* he)
{
    // Create a new vertex as midpoint
    std::unique_ptr<Vertex> v3 = std::make_unique<Vertex>();

    // Get original edge's two vertices
    HalfEdge* symHe = he->symEdge;
    Vertex* v1 = he->nextVertex;
    Vertex* v2 = symHe->nextVertex;

    // Set position of midpoint
    v3->pos = 0.5f * (v1->pos + v2->pos);

    // Create two new half-edges
    std::unique_ptr<HalfEdge> heB = std::make_unique<HalfEdge>();
    std::unique_ptr<HalfEdge> symHeB = std::make_unique<HalfEdge>();

    // Set new half-edges' vertex pointer
    heB->nextVertex = v1;
    symHeB->nextVertex = v2;

    // Set new half-edge's face pointer
    heB->face = he->face;
    symHeB->face = symHe->face;

    // Set symmetric edges
    he->symEdge = symHeB.get();
    symHeB->symEdge = he;
    symHe->symEdge = heB.get();
    heB->symEdge = symHe;

    // Set next edges
    heB->nextEdge = he->nextEdge;
    he->nextEdge = heB.get();
    symHeB->nextEdge = symHe->nextEdge;
    symHe->nextEdge = symHeB.get();

    // Set vertices
    he->nextVertex = v3.get();
    symHe->nextVertex = v3.get();

    // Add vertex
    emit sendVertex(v3.get());
    vertices.push_back(std::move(v3));

    // Add halfEdges
    emit sendHalfEdge(heB.get());
    emit sendHalfEdge(symHeB.get());
    halfEdges.push_back(std::move(heB));
    halfEdges.push_back(std::move(symHeB));
}

// Find nearest mesh data structure
Face* Mesh::findNearestFace(glm::vec3 rayD, glm::vec3 eye)
{
    Face* nearest = nullptr;
    float nearestZ = -1000.0f;

    // Traverse face for seleting nearest face
    for(int i = 0; i < faces.size(); i++)
    {
        // Get face normal
        HalfEdge* first = faces[i]->edge;
        Vertex* firstV = first->nextVertex;
        Vertex* lastVert = first->symEdge->nextVertex;
        Vertex* nextVert = first->nextEdge->nextVertex;
        glm::vec3 edge1 = glm::vec3(first->nextVertex->pos - lastVert->pos);
        glm::vec3 edge2 = glm::vec3(nextVert->pos - first->nextVertex->pos);
        glm::vec4 normal = glm::vec4(glm::normalize(glm::cross(edge1, edge2)), 0.0f);

        // Calculate intersect point
        float t = glm::dot(glm::vec3(normal), (glm::vec3(firstV->pos) - eye))
                / glm::dot(glm::vec3(normal), rayD);
        glm::vec3 inter = eye + t * rayD;

        bool onPlane = false;

        // Judge the point whether on the plane
        HalfEdge* fixed = first;
        do
        {
            // Split face into triangles
            glm::vec3 v1 = glm::vec3(fixed->nextVertex->pos);
            glm::vec3 v2 = glm::vec3(first->nextEdge->nextVertex->pos);
            glm::vec3 v3 = glm::vec3(first->nextEdge->nextEdge->nextVertex->pos);

            float s = glm::length(glm::cross(v3 - v1, v2 - v1));
            float s1 = glm::length(glm::cross(v2 - inter, v3 - inter)) / s;
            float s2 = glm::length(glm::cross(v1 - inter, v3 - inter)) / s;
            float s3 =glm::length(glm::cross(v1 - inter, v2 - inter)) / s;

            // Barycentric interpolation
            float sum = s1 + s2 + s3;
            if(fequal(glm::clamp(s1, 0.0f, 1.0f), s1) &&
               fequal(glm::clamp(s2, 0.0f, 1.0f), s2) &&
               fequal(glm::clamp(s3, 0.0f, 1.0f), s3) &&
               fequal(sum, 1.0f))
            {
                onPlane = true;
            }

            first = first->nextEdge;
        } while(first->nextEdge->nextEdge != faces[i]->edge);

        // Judge the nearest point by z value
        if(onPlane)
        {
            if(nearest != nullptr)
            {
                if(!fequal(nearestZ, inter.z) && inter.z > nearestZ)
                {
                    nearest = faces[i].get();
                    nearestZ = inter.z;
                }
            }
            else
            {
                nearest = faces[i].get();
                nearestZ = inter.z;
            }
        }
    }
    return nearest;
}

Vertex* Mesh::findNearestVertex(glm::vec3 ray, glm::vec3 eye)
{
    Vertex* nearest = nullptr;
    float nearestZ = -1000.0f;

    // Traverse vertices to find nearest one
    for(int i = 0; i < vertices.size(); i++)
    {
        // Calculate formulas a, b, c to get intersect point
        float a = pow(ray.x, 2) + pow(ray.y, 2) + pow(ray.z, 2);
        float b = 2 * (ray.x * (eye.x - vertices[i]->pos.x)
                       + ray.y * (eye.y - vertices[i]->pos.y)
                       + ray.z * (eye.z - vertices[i]->pos.z));
        float c = pow((eye.x - vertices[i]->pos.x), 2) +
                  pow((eye.y - vertices[i]->pos.y), 2) +
                  pow((eye.z - vertices[i]->pos.z), 2) -
                  pow(0.05, 2);
        float delta = pow(b, 2) - 4 * a * c;

        // Judge the nearest point
        if(!fequal(delta, 0.0f) && delta < 0.0f)
        {
            continue;
        }
        else
        {
            float t0 = (-b - delta) / (2 * a);
            if(!fequal(t0, 0.0f) && t0 > 0.0f)
            {
                glm::vec3 inter = eye + t0 * ray;
                if(!fequal(nearestZ, inter.z) && inter.z > nearestZ)
                {
                    nearestZ = inter.z;
                    nearest = vertices[i].get();
                }
                else
                {
                    float t1 = (-b + delta) / (2 * a);
                    if(!fequal(t1, 0.0f) && t1 > 0.0f)
                    {
                        glm::vec3 inter = eye + t1 * ray;
                        if(!fequal(nearestZ, inter.z) && inter.z > nearestZ)
                        {
                            nearestZ = inter.z;
                            nearest = vertices[i].get();
                        }
                    }
                }
            }
            else
            {
                float t1 = (-b + delta) / (2 * a);
                if(!fequal(t1, 0.0f) && t1 > 0.0f)
                {
                    glm::vec3 inter = eye + t1 * ray;
                    if(!fequal(nearestZ, inter.z) && inter.z > nearestZ)
                    {
                        nearestZ = inter.z;
                        nearest = vertices[i].get();
                    }
                }
            }
        }
    }
    return nearest;
}

HalfEdge* Mesh::findNearestHalfEdge(glm::vec3 ray, glm::vec3 eye)
{
    HalfEdge* nearest = nullptr;
    float nearestZ = -1000.0f;

    // Traverse halfEdges to find nearest halfEdges
    for(int i = 0; i < halfEdges.size(); i++)
    {
        // Calculate formula's a, b, c to get nearest halfEdges
        glm::vec3 endPoint = glm::vec3(halfEdges[i]->nextVertex->pos);
        glm::vec3 startPoint = glm::vec3(halfEdges[i]->symEdge->nextVertex->pos);
        glm::vec3 cylinderDir = glm::normalize(endPoint - startPoint);
        glm::vec3 distance = eye - startPoint;
        float a = glm::dot(ray - glm::dot(ray, cylinderDir) * cylinderDir, ray - glm::dot(ray, cylinderDir) * cylinderDir);
        float b = 2 * glm::dot(ray - glm::dot(ray, cylinderDir) * cylinderDir,
                               distance - glm::dot(distance, cylinderDir) * cylinderDir);
        float c = glm::dot(distance - glm::dot(distance, cylinderDir) * cylinderDir,
                           distance - glm::dot(distance, cylinderDir) * cylinderDir) - pow(0.05, 2);

        float delta = pow(b, 2) - 4 * a * c;

        // Judge nearest halfEdge
        if(!fequal(delta, 0.0f) && delta < 0.0f)
        {
            continue;
        }
        else
        {
            float t0 = (-b - delta) / (2 * a);
            if(!fequal(t0, 0.0f) && t0 > 0.0f)
            {
                glm::vec3 inter = eye + t0 * ray;
                if(!fequal(nearestZ, inter.z) && inter.z > nearestZ)
                {
                    nearestZ = inter.z;
                    nearest = halfEdges[i].get();
                }
                else
                {
                    float t1 = (-b + delta) / (2 * a);
                    if(!fequal(t1, 0.0f) && t1 > 0.0f)
                    {
                        glm::vec3 inter = eye + t1 * ray;
                        if(!fequal(nearestZ, inter.z) && inter.z > nearestZ)
                        {
                            nearestZ = inter.z;
                            nearest = halfEdges[i].get();
                        }
                    }
                }
            }
            else
            {
                float t1 = (-b + delta) / (2 * a);
                if(!fequal(t1, 0.0f) && t1 > 0.0f)
                {
                    glm::vec3 inter = eye + t1 * ray;
                    if(!fequal(nearestZ, inter.z) && inter.z > nearestZ)
                    {
                        nearestZ = inter.z;
                        nearest = halfEdges[i].get();
                    }
                }
            }
        }
    }
    return nearest;
}

// Get a face to make it planar
void Mesh::planarityTest(Face* face)
{
    // Calculate first face's normal
    HalfEdge* first = face->edge;
    Vertex* lastVert = first->symEdge->nextVertex;
    Vertex* nextVert = first->nextEdge->nextVertex;
    glm::vec3 edge1 = glm::vec3(first->nextVertex->pos - lastVert->pos);
    glm::vec3 edge2 = glm::vec3(nextVert->pos - first->nextVertex->pos);
    glm::vec4 lastNormal = glm::vec4(glm::normalize(glm::cross(edge1, edge2)), 0.0f);
    do
    {
        // Calculate each normal and compare it with last normal
        Vertex* curVertex = first->nextVertex;
        lastVert = first->symEdge->nextVertex;
        nextVert = first->nextEdge->nextVertex;
        glm::vec3 edge1 = glm::vec3(curVertex->pos - lastVert->pos);
        glm::vec3 edge2 = glm::vec3(nextVert->pos - curVertex->pos);

        glm::vec4 normal = glm::vec4(glm::normalize(glm::cross(edge1, edge2)), 0.0f);

        if(!(fequal(lastNormal.x, normal.x) &&
           fequal(lastNormal.y, normal.y) &&
           fequal(lastNormal.z, normal.z)))
        {
            // Colinear situation
            if(std::isnan(normal.x) || std::isnan(lastNormal.x))
            {
                first = first->nextEdge;
                continue;
            }

            // If normals are different, triangulate it
            std::unique_ptr<HalfEdge> he1 = std::make_unique<HalfEdge>();
            std::unique_ptr<HalfEdge> he2 = std::make_unique<HalfEdge>();

            // Set symmetric edge
            he1->symEdge = he2.get();
            he2->symEdge = he1.get();

            // Set face
            std::unique_ptr<Face> newF = std::make_unique<Face>();
            newF->color = first->face->color;
            he1->face = newF.get();
            he2->face = first->face;
            first->face->edge = he2.get();
            newF->edge = he1.get();
            first->face->edge = he2.get();
            first->nextEdge->face = newF.get();

            // Set Vertex
            he1->nextVertex = lastVert;
            he2->nextVertex = nextVert;

            // Set HalfEdges
            first->nextEdge->nextEdge->nextEdge->nextEdge = he2.get();
            he2->nextEdge = first->nextEdge->nextEdge;
            he1->nextEdge = first;
            first->nextEdge->nextEdge = he1.get();

            // Add halfEdges
            halfEdges.push_back(std::move(he1));
            halfEdges.push_back(std::move(he2));

            faces.push_back(std::move(newF));
            break;
        }
        first = first->nextEdge;
    } while(first != face->edge);
}

// Traverse each face to make all faces planar
void Mesh::planar()
{
    for(int i = 0; i < faces.size(); i++)
    {
        planarityTest(faces[i].get());
    }
}

// Smooth given mesh
void Mesh::smooth()
{
    // Get random value
    srand(time(NULL));
    std::vector<Vertex*> centroids;
    std::vector<HalfEdge*> midEdges;
    int originalCount = vertices.size();

    // Traverse each face to calculate centroid
    for(int i = 0; i < faces.size(); i++)
    {
        // Calculate centroid
        HalfEdge* first = faces[i]->edge;
        std::unique_ptr<Vertex> centroid = std::make_unique<Vertex>();
        int vertCount = 0;
        do
        {
            centroid->pos += first->nextVertex->pos;
            first = first->nextEdge;
            vertCount++;
        } while(first != faces[i]->edge);
        centroid->pos = glm::vec4(centroid->pos[0] / float(vertCount),
                                  centroid->pos[1] / float(vertCount),
                                  centroid->pos[2] / float(vertCount),
                                  centroid->pos[3] / float(vertCount));
        emit sendVertex(centroid.get());
        centroids.push_back(centroid.get());
        vertices.push_back(std::move(centroid));
    }

    // Calculate midpoints
    for(int i = 0; i < faces.size(); i++)
    {
        HalfEdge* first = faces[i]->edge;
        do
        {
            // Get midpoint components
            HalfEdge* nextEdge = first->nextEdge;
            HalfEdge* symHe = first->symEdge;
            Vertex* v1 = first->nextVertex;
            Vertex* v2 = symHe->nextVertex;
            Vertex* f1 = centroids[i];
            Vertex* f2 = centroids[symHe->face->id];

            // Create two new half-edges
            std::unique_ptr<HalfEdge> heB = std::make_unique<HalfEdge>();
            std::unique_ptr<HalfEdge> symHeB = std::make_unique<HalfEdge>();

            // Set new midpoint
            std::unique_ptr<Vertex>  midPoint = std::make_unique<Vertex>();

            // Sharp edge detection
            if(faces[i]->isSharped)
            {
                // Set sharped and sharpness
                first->isSharped = true;
                symHe->isSharped = true;
                heB->isSharped = true;
                symHeB->isSharped = true;
                v1->isSharped = true;
                v2->isSharped = true;
                midPoint->isSharped = true;

                first->sharpness = faces[i]->sharpness;
                symHe->sharpness = faces[i]->sharpness;
                heB->sharpness = faces[i]->sharpness;
                symHeB->sharpness = faces[i]->sharpness;
                v1->sharpness = faces[i]->sharpness;
                v2->sharpness = faces[i]->sharpness;
                midPoint->sharpness = faces[i]->sharpness;
            }

            if(symHe->face->isSharped)
            {
                first->isSharped = true;
                symHe->isSharped = true;
                heB->isSharped = true;
                symHeB->isSharped = true;
                v1->isSharped = true;
                v2->isSharped = true;
                midPoint->isSharped = true;

                first->sharpness = symHe->face->sharpness;
                symHe->sharpness = symHe->face->sharpness;
                heB->sharpness = symHe->face->sharpness;
                symHeB->sharpness = symHe->face->sharpness;
                v1->sharpness = symHe->face->sharpness;
                v2->sharpness = symHe->face->sharpness;
                midPoint->sharpness = symHe->face->sharpness;
            }

            if(symHe->face->isSharped && faces[i]->isSharped)
            {
                first->isSharped = true;
                symHe->isSharped = true;
                heB->isSharped = true;
                symHeB->isSharped = true;
                v1->isSharped = true;
                v2->isSharped = true;
                midPoint->isSharped = true;

                float exSharpness = (symHe->face->sharpness + faces[i]->sharpness) / 2.0;
                first->sharpness = exSharpness;
                symHe->sharpness = exSharpness;
                heB->sharpness = exSharpness;
                symHeB->sharpness = exSharpness;
                v1->sharpness = exSharpness;
                v2->sharpness = exSharpness;
                midPoint->sharpness = exSharpness;
            }

            // Judge whether this edge has been split
            if(symHe->face->isMid)
            {
                // Add midEdges
                midEdges.push_back(first->nextEdge);
                first = first->nextEdge->nextEdge;
                continue;
            }


            if(first->isSharped)
            {
                v1->sharpCount++;
                v1->endPoints.push_back(v2);
                v1->heSharpness.push_back(first->sharpness);

                v2->sharpCount++;
                v2->endPoints.push_back(v1);
                v2->heSharpness.push_back(first->sharpness);

                midPoint->pos = first->sharpness * (v1->pos + v2->pos) / 2.0f
                                + (1.0f - first->sharpness) * (v1->pos + v2->pos + f1->pos + f2->pos) / 4.0f;
            }
            else
            {
                midPoint->pos = (v1->pos + v2->pos + f1->pos + f2->pos) / 4.0f;
            }

            // Set new half-edges' vertex pointer
            heB->nextVertex = v1;
            symHeB->nextVertex = v2;

            // Set new half-edge's face pointer
            heB->face = first->face;
            symHeB->face = symHe->face;

            // Set symmetric edges
            first->symEdge = symHeB.get();
            symHeB->symEdge = first;
            symHe->symEdge = heB.get();
            heB->symEdge = symHe;

            // Set next edges
            heB->nextEdge = first->nextEdge;
            first->nextEdge = heB.get();
            symHeB->nextEdge = symHe->nextEdge;
            symHe->nextEdge = symHeB.get();

            // Set vertices
            first->nextVertex = midPoint.get();
            symHe->nextVertex = midPoint.get();
            midPoint->edge = first;

            // Add midEdges
            midEdges.push_back(heB.get());

            // Add vertex
            emit sendVertex(midPoint.get());
            vertices.push_back(std::move(midPoint));

            // Add halfEdges
            emit sendHalfEdge(heB.get());
            emit sendHalfEdge(symHeB.get());
            halfEdges.push_back(std::move(heB));
            halfEdges.push_back(std::move(symHeB));

            first = nextEdge;
        } while(first != faces[i]->edge);
        faces[i]->isMid = true;
    }

    // Calculate vertices new position
    for(int i = 0; i < originalCount; i++)
    {
        Vertex* vPrime = vertices[i].get();
        glm::vec4 sumE = glm::vec4(0.0f);
        glm::vec4 sumF = glm::vec4(0.0f);
        int count = 0;
        for(int j = 0; j < midEdges.size(); j++)
        {
            if(midEdges[j]->nextVertex == vPrime)
            {
                sumE += midEdges[j]->symEdge->nextVertex->pos;
                sumF += centroids[midEdges[j]->face->id]->pos;
                count++;
            }
        }
        float n = (float)count;
        glm::vec4 smoothPos = (n - 2.0f) * vPrime->pos / n + sumE / powf(n, 2.0f) + sumF / powf(n, 2.0f);
        if(vPrime->isSharped)
        {
            vPrime->pos = vPrime->sharpness * vPrime->pos + (1 - vPrime->sharpness) * smoothPos;
        }
        else if(vPrime->sharpCount == 3)
        {
            float sharpness = 0.0f;
            for(int j = 0; j < vPrime->heSharpness.size(); j++)
            {
                sharpness += vPrime->heSharpness[j];
            }
            sharpness /= vPrime->heSharpness.size();
            vPrime->pos = sharpness * vPrime->pos + (1 - sharpness) * smoothPos;
        }
        else if(vPrime->sharpCount == 2)
        {
            Vertex* v1 = vPrime->endPoints[0];
            Vertex* v2 = vPrime->endPoints[1];
            float sharpness = (vPrime->heSharpness[0] + vPrime->heSharpness[1]) / 2.0;
            vPrime->pos = sharpness * (0.75f * vPrime->pos + 0.125f * v1->pos + 0.125f * v2->pos)
                          + (1 - sharpness) * smoothPos;
        }
        else
        {
            vPrime->pos = smoothPos;
        }
    }

    // Quadrangulate
    HalfEdge* midToCentroidPointer = nullptr;
    HalfEdge* firstCentroidToMid = nullptr;
    for(int i = 0; i < midEdges.size(); i++)
    {
        // Deal with first face's sym edge pointer
        if(midToCentroidPointer != nullptr && midEdges[i]->face->isMid)
        {
            firstCentroidToMid->symEdge = midToCentroidPointer;
            midToCentroidPointer->symEdge = firstCentroidToMid;
        }

        // Set a new face
        std::unique_ptr<HalfEdge> midToCentroid = std::make_unique<HalfEdge>();
        std::unique_ptr<HalfEdge> centroidToMid = std::make_unique<HalfEdge>();

        // Set vertices
        midToCentroid->nextVertex = centroids[midEdges[i]->face->id];
        centroidToMid->nextVertex = midEdges[i]->symEdge->nextVertex;
        centroids[midEdges[i]->face->id]->edge = midToCentroid.get();


        // Set halfEdges
        midToCentroid->nextEdge = centroidToMid.get();
        centroidToMid->nextEdge = midEdges[i];
        midEdges[i]->nextEdge->nextEdge = midToCentroid.get();


        // Set symEdges and faces
        if(midEdges[i]->face->isMid)
        {
            // First subface
            midEdges[i]->face->edge = midEdges[i];
            midToCentroid->face = midEdges[i]->face;
            centroidToMid->face = midEdges[i]->face;
            firstCentroidToMid = centroidToMid.get();
            midEdges[i]->face->isMid = false;
        }
        else
        {
            // Set new face
            std::unique_ptr<Face> newF = std::make_unique<Face>();

            if(midEdges[i]->face->isSharped)
            {
                newF->isSharped = true;
                newF->sharpness = midEdges[i]->face->sharpness;
            }
            newF->edge = midEdges[i];
            float r = rand() / float(RAND_MAX);
            float g = rand() / float(RAND_MAX);
            float b = rand() / float(RAND_MAX);

            newF->color = glm::vec4(r, g, b, 1.0f);

            midEdges[i]->face = newF.get();
            midEdges[i]->nextEdge->face = newF.get();
            midToCentroid->face = newF.get();
            centroidToMid->face = newF.get();

            // Set sym pointer
            centroidToMid->symEdge = midToCentroidPointer;
            midToCentroidPointer->symEdge = centroidToMid.get();

            // Add face
            emit sendFace(newF.get());
            faces.push_back(std::move(newF));
        }

        midToCentroidPointer = midToCentroid.get();

        // Add half edge
        emit sendHalfEdge(midToCentroid.get());
        emit sendHalfEdge(centroidToMid.get());
        halfEdges.push_back(std::move(midToCentroid));
        halfEdges.push_back(std::move(centroidToMid));
    }

    // Deal with first face's sym pointer
    if(midToCentroidPointer != nullptr)
    {
        firstCentroidToMid->symEdge = midToCentroidPointer;
        midToCentroidPointer->symEdge = firstCentroidToMid;
    }

}

void Mesh::extrude(Face *face)
{
    HalfEdge* first = face->edge;
    HalfEdge* parent = first;
    Vertex* lastVertex = nullptr;
    Vertex* thisVertex = nullptr;
    Vertex* firstVertex = nullptr;
    Vertex* firstNextVertex = nullptr;
    Vertex* v2 = first->symEdge->nextVertex;

    // Calculate given face normal
    Vertex* lastVert = first->symEdge->nextVertex;
    Vertex* nextVert = first->nextEdge->nextVertex;
    glm::vec3 edge1 = glm::vec3(first->nextVertex->pos - lastVert->pos);
    glm::vec3 edge2 = glm::vec3(nextVert->pos - first->nextVertex->pos);

    glm::vec4 normal = glm::vec4(glm::normalize(glm::cross(edge1, edge2)), 0.0f);

    do
    {
        parent = parent->nextEdge;
    } while(parent->nextEdge != first);

    do
    {
        // Setup original pointer
        HalfEdge* he1 = first;
        HalfEdge* he2 = first->symEdge;
        Vertex* v1 = first->nextVertex;

        // First iteration
        if(first == face->edge)
        {
            std::unique_ptr<Vertex> v3 = std::make_unique<Vertex>();
            std::unique_ptr<Vertex> v4 = std::make_unique<Vertex>();
            lastVertex = v4.get();
            thisVertex = v3.get();
            firstVertex = v4.get();
            firstNextVertex = v2;

            // Set position
            v3->pos = v1->pos + 0.5f * normal;
            v4->pos = v2->pos + 0.5f * normal;

            // Add vertices
            emit sendVertex(v3.get());
            emit sendVertex(v4.get());
            vertices.push_back(std::move(v3));
            vertices.push_back(std::move(v4));
        }
        else if(first->nextEdge == face->edge)
        {
            thisVertex = firstVertex;
            v1 = firstNextVertex;
        }
        else
        {
            std::unique_ptr<Vertex> v3 = std::make_unique<Vertex>();
            thisVertex = v3.get();

            v3->pos = v1->pos + 0.5f * normal;

            emit sendVertex(v3.get());
            vertices.push_back(std::move(v3));
        }

        // Adjust vertex' pointer
        parent->nextVertex = lastVertex;
        lastVertex->edge = parent;
        he1->nextVertex = thisVertex;
        thisVertex->edge = he1;

        // Add new half-edges
        std::unique_ptr<HalfEdge> he1B = std::make_unique<HalfEdge>();
        std::unique_ptr<HalfEdge> he2B = std::make_unique<HalfEdge>();
        he1->symEdge = he1B.get();
        he2->symEdge = he2B.get();
        he1B->symEdge = he1;
        he2B->symEdge = he2;
        he1B->nextVertex = lastVertex;
        lastVertex->edge = he1B.get();
        he2B->nextVertex = v1;
        v1->edge = he2B.get();

        // Add new face
        std::unique_ptr<Face> newF = std::make_unique<Face>();
        std::unique_ptr<HalfEdge> he3 = std::make_unique<HalfEdge>();
        std::unique_ptr<HalfEdge> he4 = std::make_unique<HalfEdge>();
        he3->nextVertex = thisVertex;
        he4->nextVertex = v2;
        he1B->nextEdge = he4.get();
        he4->nextEdge = he2B.get();
        he2B->nextEdge = he3.get();
        he3->nextEdge = he1B.get();
        newF->edge = he1B.get();
        newF->color = face->color;
        he3->face = newF.get();
        he4->face = newF.get();
        he1B->face = newF.get();
        he2B->face = newF.get();

        // Add components
        emit sendFace(newF.get());
        faces.push_back(std::move(newF));

        emit sendHalfEdge(he1B.get());
        emit sendHalfEdge(he2B.get());
        emit sendHalfEdge(he3.get());
        emit sendHalfEdge(he4.get());
        halfEdges.push_back(std::move(he1B));
        halfEdges.push_back(std::move(he2B));
        halfEdges.push_back(std::move(he3));
        halfEdges.push_back(std::move(he4));

        // Next half-edge
        first = first->nextEdge;
        parent = parent->nextEdge;
        lastVertex = thisVertex;
        v2 = v1;
    } while(first != face->edge);

    // Set symmetric edges
    do
    {
        HalfEdge* he4 = first->symEdge->nextEdge;
        HalfEdge* he3 = parent->symEdge;
        do
        {
            he3 = he3->nextEdge;
        } while(he3->nextEdge != parent->symEdge);

        he4->symEdge = he3;
        he3->symEdge = he4;

        // Next half-edge
        first = first->nextEdge;
        parent = parent->nextEdge;
    } while(first != face->edge);
}

// Construct a mesh from file
void Mesh::constructFileMesh(std::string& fileName)
{
    srand(time(NULL));
    // Clear all mesh components
    vertices.clear();
    halfEdges.clear();
    faces.clear();

    faceVerticesCount = 0;

    // Index vector
    std::vector<int> indices;
    std::unordered_map<std::string, HalfEdge*> symMap;

    // Open obj file
    const char* cFileName = (char*)fileName.c_str();
    std::ifstream fileIn;
    fileIn.open(cFileName);

    // Read file
    std::string lineBuffer = "";
    while(std::getline(fileIn, lineBuffer))
    {
        std::istringstream iss(lineBuffer);
        std::string split;

        std::vector<std::string> lineSegment;

        bool first = true;

        if(lineBuffer == "")
        {
            continue;
        }

        // Split line segment
        while(std::getline(iss, split, ' '))
        {
           lineSegment.push_back(split);
           if(first)
           {
               first = false;
               if(split != "v" && split != "f")
               {
                   break;
               }
           }
        }

        if(lineSegment[0] == "v")
        {
            // Read vertex info
            float x = float(atof((char*)lineSegment[1].c_str()));
            float y = float(atof((char*)lineSegment[2].c_str()));
            float z = float(atof((char*)lineSegment[3].c_str()));

            std::unique_ptr<Vertex> curVertex = std::make_unique<Vertex>();
            glm::vec4 pos(x, y, z, 1.0f);
            curVertex->pos = pos;

            emit sendVertex(curVertex.get());
            vertices.push_back(std::move(curVertex));
        }
        else if(lineSegment[0] == "f")
        {
            faceVerticesCount = lineSegment.size() - 1;
            // Read vertex index
            for(int i = 1; i < lineSegment.size(); i++)
            {
                std::string indexString;
                std::istringstream indexReader(lineSegment[i]);
                if(std::getline(indexReader, indexString, '/'))
                {
                    indices.push_back(atoi(indexString.c_str()));
                }

            }
        }
    }

    // Close file
    fileIn.close();

    // Set mesh data structure
    for(int i = 0; i < indices.size(); i = i + faceVerticesCount)
    {
        // Set a new face
        std::unique_ptr<Face> f = std::make_unique<Face>();

        // Get vertices
        std::vector<Vertex*> faceVertices;
        for(int j = 0; j < faceVerticesCount; j++)
        {
            faceVertices.push_back(vertices[indices[i + j] - 1].get());
        }

        // Create halfEdges
        std::vector<HalfEdge*> faceHalfEdges;
        for(int k = 0; k < faceVerticesCount; k++)
        {
            std::unique_ptr<HalfEdge> he = std::make_unique<HalfEdge>();
            he->nextVertex = faceVertices[k];
            faceVertices[k]->edge = he.get();
            he->face = f.get();
            f->edge = he.get();
            faceHalfEdges.push_back(he.get());

            // Add halfEdges
            emit sendHalfEdge(he.get());
            halfEdges.push_back(std::move(he));
        }

        std::string middle = "t";
        // Setup halfEdge pointers
        for(int w = 0; w < faceVerticesCount; w++)
        {
            // Set nextEdge
            if(w == faceVerticesCount - 1)
            {
                faceHalfEdges[w]->nextEdge = faceHalfEdges[0];
            }
            else
            {
                faceHalfEdges[w]->nextEdge = faceHalfEdges[w + 1];
            }
            // Set symEdge
            std::string heSymString = "";
            if(w == 0)
            {
                heSymString = std::to_string(indices[i]) + middle + std::to_string(indices[i + faceVerticesCount - 1]);
            }
            else
            {
                heSymString = std::to_string(indices[i + w]) + middle + std::to_string(indices[i + w - 1]);
            }
            // Get sym edge
            HalfEdge* heSym = symMap[heSymString];

            // Set sym edge
            if(heSym == NULL)
            {
                std::string name = "";
                if(w == 0)
                {
                    name = std::to_string(indices[i + faceVerticesCount - 1]) + middle + std::to_string(indices[i]);
                }
                else
                {
                    name = std::to_string(indices[i + w - 1]) + middle + std::to_string(indices[i + w]);
                }
                symMap[name] = faceHalfEdges[w];
            }
            else
            {
                faceHalfEdges[w]->symEdge = heSym;
                heSym->symEdge = faceHalfEdges[w];
                symMap.erase(heSymString);
            }
        }

        // Set face color

        float r = rand() / float(RAND_MAX);
        float g = rand() / float(RAND_MAX);
        float b = rand() / float(RAND_MAX);

        f->color = glm::vec4(r, g, b, 1.0f);

        emit sendFace(f.get());
        faces.push_back(std::move(f));
    }
}

void Mesh::setJointWeights()
{
    float minThreshold = 0.5;
    for(int i = 0; i < meshSkeleton.joints.size(); i++)
    {
        std::vector<Vertex*> diffuseVertex;
        std::unordered_map<int, bool> isDiffused;
        Joint* curJoint = meshSkeleton.joints[i].get();
        glm::mat4 globalTransform = curJoint->getGlobalTransformation();
        glm::vec3 jPos = glm::vec3(globalTransform[0][3],
                                   globalTransform[1][3],
                                   globalTransform[2][3]);
        for(int j = 0; j < vertices.size(); j++)
        {
            vertices[j]->weightMap[i] = 0.0;
            float distance = glm::length(vertices[j]->pos - glm::vec4(jPos, 1.0f));
            if((!fequal(distance, minThreshold) && distance < minThreshold))
            {
                vertices[j]->weightMap[i] = 1.0f;
                isDiffused[vertices[j]->id] = true;
                diffuseVertex.push_back(vertices[j].get());
            }
        }
        while(!diffuseVertex.empty())
        {
            int diffusedSize = diffuseVertex.size();
            for(int k = 0; k < diffusedSize; k++)
            {
                // fall function -(x - 1)^3
                // Get all neighborhood vertices
                for(int z = 0; z < halfEdges.size(); z++)
                {
                    if(halfEdges[z]->nextVertex == diffuseVertex[k]
                            && (!isDiffused[halfEdges[z]->symEdge->nextVertex->id]))
                    {
                        Vertex* neighborVert = halfEdges[z]->symEdge->nextVertex;
                        float distance = glm::length(neighborVert->pos - glm::vec4(jPos, 1.0f));
                        float ratio = distance / (10 * minThreshold);
                        if(!fequal(ratio, 1.0f) && ratio >= 1.0f)
                        {
                            neighborVert->weightMap[i] = 0.0f;
                        }
                        else
                        {
                            neighborVert->weightMap[i] = -pow(ratio - 1.0, 9.0);
                            diffuseVertex.push_back(halfEdges[z]->symEdge->nextVertex);
                        }
                        isDiffused[halfEdges[z]->symEdge->nextVertex->id] = true;
                    }
                }
            }

            for(int w = 0; w < diffusedSize; w++)
            {
                diffuseVertex.erase(diffuseVertex.begin());
            }
        }
    }
}

void Mesh::loadSkeleton(QString& path)
{
    // Load skeleton
    meshSkeleton = Skeleton();
    meshSkeleton.fileNameStd = path.toStdString();
    meshSkeleton.constructSkeleton();

    // Set joint display
    jointdisplays.clear();
    for(int i = 0; i < meshSkeleton.joints.size(); i++)
    {
        std::unique_ptr<JointDisplay> jd = std::make_unique<JointDisplay>(this->mp_context);
        jd->setJoint(meshSkeleton.joints[i].get());
        jd->create();
        meshSkeleton.joints[i]->setBindMatrix();
        jointdisplays.push_back(std::move(jd));
    }

    emit sendRoot(meshSkeleton.rootJoint);

}

void Mesh::updateJoints()
{
    for(int i = 0; i < jointdisplays.size(); i++)
    {
        jointdisplays[i]->create();
    }
}

void Mesh::generateWeight()
{
    weightBound = true;
    mp_context->glGenBuffers(1, &bufWeight);
}

void Mesh::generateWeightIdx()
{
    weightIdxBound = true;
    mp_context->glGenBuffers(1, &bufJointIndex);
}

bool Mesh::bindWeight()
{
    if(weightBound)
    {
        mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufWeight);
    }

    return weightBound;
}

bool Mesh::bindWeightIdx()
{
    if(weightIdxBound)
    {
        mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufJointIndex);
    }
    return weightIdxBound;
}

Mesh::~Mesh() {}


