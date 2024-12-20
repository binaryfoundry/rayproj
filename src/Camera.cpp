#include "Camera.hpp"

Camera::Camera(const glm::vec3 position) :
    position(position)
{
    Validate();
}

void Camera::Strafe(const float value)
{
    glm::vec3 strafe_direction = glm::cross(
        up,
        direction);

    if (glm::length(strafe_direction) > 0.001f)
    {
        strafe_direction = glm::normalize(
            strafe_direction);
    }

    position += strafe_direction * value;

    validated = false;
}

void Camera::Forward(const float value)
{
    const glm::vec3 d = glm::vec3(
        direction.x,
        direction.y,
        direction.z);
    position += d * value;

    validated = false;
}

void Camera::Yaw(const float value)
{
    orientation.yaw += value;
}

void Camera::Pitch(const float value)
{
    orientation.pitch += value;
}

void Camera::Viewport(const glm::vec4 value)
{
    viewport = value;
}

float Camera::Aspect() const
{
    return viewport.w / viewport.z;
}

float Camera::Near() const
{
    return near_plane;
}

float Camera::Far() const
{
    return far_plane;
}

void Camera::Zoom(const float value)
{
    zoom = value;
}

float Camera::Zoom() const
{
    return zoom;
}

void Camera::Validate()
{
    if (validated)
        return;

    const glm::quat roll = quat_from_axis_angle(
        yaw_axis,
        orientation.roll);

    const glm::quat pitch = quat_from_axis_angle(
        pitch_axis,
        orientation.pitch);

    const glm::quat yaw = quat_from_axis_angle(
        yaw_axis,
        orientation.yaw);

    const glm::quat temp_1 = pitch * yaw;
    const glm::quat temp_2 = temp_1 * roll;

    const glm::mat4x4 pitch_matrix = mat4_cast(
        pitch);

    const glm::quat temp_3 = yaw * pitch;

    const glm::mat4x4 temp_matrix = mat4_cast(
        temp_3);

    direction = glm::vec3(
        temp_matrix[2][0],
        pitch_matrix[2][1],
        -temp_matrix[2][2]);

    view = mat4_cast(temp_2);

    validated = true;
}
