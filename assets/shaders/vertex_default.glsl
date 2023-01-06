#version 330
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform mat4 matrix; //hardcoded

void main(){
    gl_Position = matrix * vec4(aPos,1.0);
    
    ourColor = aColor;
}