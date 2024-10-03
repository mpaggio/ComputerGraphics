#version 330 core
 
/* L'input del vertex shader divent l'input del fragment shader */
in vec4 fragment_color;

out vec4 FragColor;

void main()
{
    FragColor = fragment_color;
}