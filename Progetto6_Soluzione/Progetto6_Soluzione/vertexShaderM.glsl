#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec4 aColor; // the color variable has attribute position 1
layout(location = 2) in vec3 aPos_CP;   // the position variable has attribute position 0
layout(location = 3) in vec4 aColor_CP; // the color variable has attribute position 1
layout(location = 4) in vec3 tg_CP;   // the position variable has attribute position 0
layout(location = 5) in vec4 col_tg_CP; // the color variable has attribute position 1

out vec4 ourColor; // output a color to the fragment shader
uniform mat4 Projection;  //vARIABILE DI TIPO uniform, rimane la stessa per ogni vertice della primitiva e viene passata dall'esterno
uniform mat4 Model;
uniform int flagP;
void main()
{
//Trasformazione dei vertici dalle coordinate nel sistema di riferimento dell'oggetto (apos), al sistema di riferimento del mondo (premoltiplicazione 
// per Model) e successivamente proiettate nel cubo di centro l'origine e lato lungo 2, con x,y,z che variano tra -1 ed 1- (premoltiplicazione 
//per la matrice Projection)
    if (flagP==1){
        gl_Position = Projection*Model*vec4(aPos_CP, 1.0);
        ourColor = aColor; // set ourColor to the input color we got from the vertex data
    }
    if (flagP == 0) {
        gl_Position = Projection * Model * vec4(aPos, 1.0);
        ourColor = aColor_CP; // set ourColor to the input color we got from the vertex data
    }
    if (flagP == 2) {
        gl_Position = Projection * Model * vec4(tg_CP, 1.0);
        ourColor = col_tg_CP; // set ourColor to the input color we got from the vertex data
    }
   
    
    }  

