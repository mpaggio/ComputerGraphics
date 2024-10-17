#version 330 core

// questo fragment shader prende il colore interpolato da un vertex shader e lo assegna direttamente al pixel corrente.
// Viene eseguito una volta per ogni pixel che deve essere colorato sullo schermo
in vec4 colore_frag; 

//La variabile di input colore_frag  contiene il valore del colore interpolato da un vertex shader per il frammento corrente.
// In altre parole, il colore di ciascun vertice viene calcolato nel vertex shader e poi interpolato per ottenere il colore di ogni pixel all'interno della primitiva

out vec4 color;
//la variabile di output color di tipo vec4 contiene il colore finale che verrà assegnato al pixel corrente.

void main(){
	color = colore_frag;
}