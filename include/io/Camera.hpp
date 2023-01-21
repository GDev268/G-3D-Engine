#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraDirection{
    NONE = 0,
    FOWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera{
public:
    Camera(glm::vec3 position);
    ~Camera();

    void updateDirection(double dx,double dy);
    void updatePosition(CameraDirection dir,double dt);
    void updateZoom(double dy);

    glm::mat4 getViewMatrix();


    glm::vec3 cameraPos;

    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 cameraRight;

    glm::vec3 worldUp;

    float yaw;
    float pitch;
    float speed;
    float zoom;
private:
    void updateCameraVectors();

};

#endif