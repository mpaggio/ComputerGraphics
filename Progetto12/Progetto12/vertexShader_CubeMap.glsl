#version 330 core
layout (location = 0) in vec3 aPos;   // Attributo Posizione


 uniform mat4 Projection;
 uniform mat4 View;
 out vec3 TexCoords;

void main(){	

  TexCoords = aPos;
  //La matrice di vista utilizzata per trasformare i vertici 
  // non include la traslazione.
  // Questo significa che l'oggetto non si muover� nello spazio 
  // della camera, ma la camera si muover� attorno all'oggetto.
  mat4 Static_View=mat4(mat3(View));  //Matrice di vista a cui si toglie il contributo della traslazione
  gl_Position = Projection * Static_View * vec4(aPos, 1.0);
	
    

}


