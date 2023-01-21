#include "io/Camera.hpp"

Camera::Camera(glm::vec3 position):
cameraPos(position),
worldUp(glm::vec3(0.0f,1.0f,0.0f)),
yaw(-90.0f),
pitch(0.0f),
speed(5.0f),
zoom(45.0f),
cameraFront(glm::vec3(0.0f,0.0f,-1.0f))
{
    updateCameraVectors();
}

Camera::~Camera()
{
}

void Camera::updateDirection(double dx, double dy)
{
    yaw += dx;
    pitch += dy;

    if(pitch > 89.0f){
        pitch = 89.0f;
    }
    else if (pitch < -89.0f){
        pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::updatePosition(CameraDirection dir, double dt)
{
    float velocity = (float)dt * speed;

    switch(dir){
        case CameraDirection::FOWARD:
            cameraPos += cameraFront * velocity;
            break;
        case CameraDirection::BACKWARD:
            cameraPos -= cameraFront * velocity;
            break;     
        case CameraDirection::RIGHT:
            cameraPos += cameraRight * velocity;
            break;
        case CameraDirection::LEFT:
            cameraPos -= cameraRight * velocity;
            break;
        case CameraDirection::UP:
            cameraPos += cameraUp * velocity;
            break;
        case CameraDirection::DOWN:
            cameraPos -= cameraUp * velocity;
            break;                    
    }
}

void Camera::updateZoom(double dy)
{
    if(zoom < 1.0f){
        zoom = 1.0f;
    }
    else if(zoom > 45.0f){
        zoom = 45.0f;
    }
    if(zoom >= 1.0f && zoom <= 45.0f){
        zoom -= dy;
    }
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(cameraPos,cameraPos + cameraFront,cameraUp);
}

void Camera::updateCameraVectors()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);

    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight,cameraFront));

}
