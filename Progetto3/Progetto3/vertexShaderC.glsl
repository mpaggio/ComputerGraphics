#version 330 core

//layout(location = 0) specifica che l'attributo aPos avrà l'indice 0 nel vertex shader. Questo è importante per associarlo correttamente all'attributo corrispondente nel VAO (Vertex Array Object).
//in vec3 aPos;: Dichiara una variabile di input di tipo vec3 (vettore a 3 componenti) chiamata aPos. Questa variabile rappresenta la posizione del vertice in coordinate 3D.

layout(location = 0) in vec3 aPos;

//layout(location = 1) specifica che l'attributo Color  avrà l'indice 1 nel vertex shader. 
//in vec4 Color;: Dichiara una variabile di input di tipo vec4 (vettore a 4 componenti) chiamata Color. Questa variabile rappresenta le componenti di colore del vertice

layout(location =1 ) in vec4 Color;


out vec4 colore_frag;
//Dichiara una variabile di output di tipo vec4 chiamata colore_frag.
// Questa variabile verrà interpolatora per determinare il colore dei pixel all'interno della primitiva (triangolo, linea, ecc.) e verrà passata al fragment shader.

void main(){	
	gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);  //Assegna alla variabile predefinita gl_Position  la posizione del vertice in coordinate omogenee(x, y, z, w)
	colore_frag= Color;
}

