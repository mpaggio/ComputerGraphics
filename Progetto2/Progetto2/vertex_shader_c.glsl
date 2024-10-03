#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 Color;
 
out vec4 fragment_color;  

void main()
{
     
    gl_Position = vec4(aPos, 1.0);
    fragment_color = Color;
}