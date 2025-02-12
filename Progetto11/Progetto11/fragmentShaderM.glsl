#version 330 core

in vec4 ourColor ;
out vec4 FragColor;  

in vec2 frag_coord;

uniform int sceltaShader; 
uniform sampler2D id_tex1;

void main()
{
    if (sceltaShader == 0 || sceltaShader == 4){
        FragColor = ourColor;
    } else {
        FragColor = mix(ourColor, texture(id_tex1, frag_coord), 0.5);
    }
}