#include "camera.h"

#include <la.h>
#include <iostream>
#include <cmath>


Camera::Camera():
    Camera(400, 400)
{
    look = glm::vec3(0,0,-1);
    up = glm::vec3(0,1,0);
    right = glm::vec3(1,0,0);
}

Camera::Camera(unsigned int w, unsigned int h):
    Camera(w, h, glm::vec3(0,0,10), glm::vec3(0,0,0), glm::vec3(0,1,0))
{}

Camera::Camera(unsigned int w, unsigned int h, const glm::vec3 &e, const glm::vec3 &r, const glm::vec3 &worldUp):
    fovy(45),
    width(w),
    height(h),
    near_clip(0.1f),
    far_clip(1000),
    eye(e),
    ref(r),
    world_up(worldUp)
{
    RecomputeAttributes();
}

Camera::Camera(const Camera &c):
    fovy(c.fovy),
    width(c.width),
    height(c.height),
    near_clip(c.near_clip),
    far_clip(c.far_clip),
    aspect(c.aspect),
    eye(c.eye),
    ref(c.ref),
    look(c.look),
    up(c.up),
    right(c.right),
    world_up(c.world_up),
    V(c.V),
    H(c.H)
{}


void Camera::RecomputeAttributes()
{
    look = glm::normalize(ref - eye);
    right = glm::normalize(glm::cross(look, world_up));
    up = glm::cross(right, look);

    float tan_fovy = tan(glm::radians(fovy/2));
    float len = glm::length(ref - eye);
    aspect = (float)width / (float)height;
    V = up * len * tan_fovy;
    H = right * len * aspect * tan_fovy;

    // Compute spherical angle
    xAxisAngle = acos(glm::dot(glm::normalize(glm::vec3(0.0f, look.y, look.z)),
                               glm::vec3(0.0, 0.0, 1.0)));
    yAxisAngle = acos(glm::dot(glm::normalize(glm::vec3(look.x, 0.0f, look.z)),
                               glm::vec3(0.0, 0.0, 1.0)));
    zAxisZoom = glm::length(ref - eye);
}

glm::mat4 Camera::getViewProj()
{
    return glm::perspective(glm::radians(fovy), width / (float)height, near_clip, far_clip) * glm::lookAt(eye, ref, up);
}

void Camera::RotateAboutUp(float deg)
{
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(deg), up);
    ref = ref - eye;
    ref = glm::vec3(rotation * glm::vec4(ref, 1));
    ref = ref + eye;
    RecomputeAttributes();
}
void Camera::RotateAboutRight(float deg)
{
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(deg), right);
    ref = ref - eye;
    ref = glm::vec3(rotation * glm::vec4(ref, 1));
    ref = ref + eye;
    RecomputeAttributes();
}

void Camera::TranslateAlongLook(float amt)
{
    glm::vec3 translation = look * amt;
    eye += translation;
    ref += translation;
}

void Camera::TranslateAlongRight(float amt)
{
    glm::vec3 translation = right * amt;
    eye += translation;
    ref += translation;
}
void Camera::TranslateAlongUp(float amt)
{
    glm::vec3 translation = up * amt;
    eye += translation;
    ref += translation;
}

// Spherical transformation
void Camera::rotateXAxisAngle(float deg)
{
    xAxisAngle += glm::radians(deg);
    reComputeSphericalVectors();
}

void Camera::rotateYAxisAngle(float deg)
{
    yAxisAngle += glm::radians(deg);
    reComputeSphericalVectors();
}

void Camera::translateZAxisZoom(float amt)
{
    zAxisZoom += amt;
    reComputeSphericalVectors();
}

void Camera::reComputeSphericalVectors()
{
    // Get rotation matrix
    glm::mat4 xRotMat = glm::rotate(glm::mat4(1.0f), xAxisAngle, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 yRotMat = glm::rotate(glm::mat4(1.0f), yAxisAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 zTransMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, zAxisZoom));

    // Calculate update value
    eye = glm::vec3(yRotMat * xRotMat * zTransMat * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    look = glm::vec3(yRotMat * xRotMat * zTransMat * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
    up = glm::vec3(yRotMat * xRotMat * zTransMat * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
    right = glm::vec3(yRotMat * xRotMat * zTransMat * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
}


