#pragma once
#include "lib.h"
#include "strutture.h"
#include "gestione_interazioni.h"
#include "gestione_telecamera.h"
#include "ImGui/imgui.h"
#include "enum.h"
#include "utilities.h"


extern GLFWwindow* window;
extern mat4 Projection;
extern int height, width;
extern PerspectiveSetup SetupProspettiva;
extern ViewSetup SetupTelecamera;
extern mat4 View;
extern float w_up, h_up;
extern bool flagAncora;
 
string stringa_asse = "---", Operazione = "---";

int last_mouse_pos_X, last_mouse_pos_Y;
float Theta=-89.0;
float Phi=0.0;
bool moving_trackball = false;
bool isNavigationMode = false;
 
extern int selected_obj;
extern int selected_obj_j;
extern vector<Mesh> Scena;
extern vector<vector<MeshObj>> ScenaObj;
float raggio_sfera = 5.0;
float amount = 0.2;

vec3 asse;

vec3 getTrackBallPoint(float x, float y) {
    float Delta, tmp;
    vec3 point;

    // Mappo nell'intervallo normalizzato [-1,1]
    point.x = (2.0f * x - width) / width;
    point.y = (height - 2.0f * y) / height;

    //Cooordinata z del punto di coordinate (x,y,z) che si muove sulla sfera virtuale con centro (0,0,0) e raggio r=1
    tmp = pow(point.x, 2.0) - pow(point.y, 2.0);
    Delta = 1.0f - tmp;

    if (Delta > 0.0f)
        point.z = sqrt(Delta);
    else
        point.z = 0;

    return normalize(point);
}

// Calcola il raggio che parte dalla posizione della telecamera e passa per le coordinate del mouse
vec3 get_ray_from_mouse(float mouse_x, float mouse_y) {

    mouse_y = height - mouse_y;

    // mappiamo le coordinate di viewport del mouse [0,width], [0,height] in coordinate normalizzate [-1,1]  
    float ndc_x = (2.0f * mouse_x) / width - 1.0;
    float ndc_y = (2.0f * mouse_y) / height - 1.0;
    float ndc_z = -1.0f;

    // Coordinate nel clip space 
    vec4 P_clip = vec4(ndc_x, ndc_y, ndc_z, 1.0);

    // Le coordinate nell' eye space si ottengono premoltiplicando per l'inversa della matrice Projection.
    vec4 ViewModelp = inverse(Projection) * P_clip;

    // le coordinate nel world space: si ottengono premoltiplicando per l'inversa della matrice di Vista 
    ViewModelp.w = 1;
    vec4 Pw = inverse(View) * ViewModelp;

    //Il vettore del raggio viene calcolato sottraendo la posizione della telecamera SetupTelecamera.position dal punto Pw nel world space.
    vec3 ray_wor = normalize(vec3(Pw) - vec3(SetupTelecamera.position));

    return ray_wor;
}


bool ray_sphere(vec3 O, vec3 d, vec3 sphere_centre_wor, float sphere_radius, float* intersection_distance) {

    vec3 dist_sfera = O - sphere_centre_wor;
    float b = dot(dist_sfera, d);
    float cc = dot(dist_sfera, dist_sfera) - sphere_radius * sphere_radius;

    float delta = b * b - cc;

    if (delta < 0.0f)  //Il raggio non interseca la sfera
        return false;

    //Calcolo i valori di t per cui il raggio interseca la sfera e restituisco il valore dell'intersezione 
    //più vicina all'osservatore (la t più piccola)
    if (delta > 0.0f) {
        //calcola le due intersezioni
        float t_a = -b + sqrt(delta);
        float t_b = -b - sqrt(delta);
        *intersection_distance = t_b;

        //Caso di intersezioni dietro l'osservatore
        if (t_a < 0.0) {
            if (t_b < 0)
                return false;
        }

        return true;
    }

    //Caso in cui il raggio è tangente alla sfera: un interesezione con molteplicità doppia.
    if (delta == 0) {
        float t = -b + sqrt(delta);
        
        if (t < 0)
            return false;
        
        *intersection_distance = t;
        return true;
    }

    return false;
}


void cursor_position_callback(GLFWwindow* window, double xposIn, double yposIn) {

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    float xoffset, yoffset;
    float alfaX = 0.10; // Ridimensionamento dell'offset fra due posizioni del mouse
    float alfaY = 0.05;
    ypos = height - ypos;

    float center_x = width / 2.0f;
    float center_y = height / 2.0f;


    xoffset = xpos - center_x;
    yoffset = ypos - center_y;

    // Navigazione ma non come trackball
    if (isNavigationMode && !moving_trackball) {

        xoffset *= alfaX;
        yoffset *= alfaY;
        //Aggiorna gli angoli di rotazione orizzontale(Theta) e verticale(Phi) in base agli offset calcolati.
        // L'angolo Theta controlla la rotazione attorno all'asse y, mentre Phi controlla la rotazione attorno all'asse x.
        Theta += xoffset;   //Aggiorno l'angolo Theta sommandogli l'offset della posizione x del mouse
        Phi += yoffset;  //Aggiorno l'angolo Phi sommandogli l'offset della posizione y del mouse 

        // Facciamo si' che l'angolo di Phi vari tra -90 e 90, evitando così di capovolgere la telecamera.
        if (Phi > 89.0f)
            Phi = 89.0f;

        if (Phi < -89.0f)
            Phi = -89.0f;

        //Calcola le coordinate x, y e z di un punto sulla sfera unitaria, 
        // utilizzando gli angoli Theta e Phi convertiti in radianti.Questo punto rappresenta la direzione in cui punta la telecamera.
        vec3 front;
        front.x = cos(radians(Theta)) * cos(radians(Phi));
        front.y = sin(radians(Phi));
        front.z = sin(radians(Theta)) * cos(radians(Phi));

        //Normalizza il vettore front per ottenere un vettore unitario che rappresenta la nuova direzione della telecamera.
        cout << SetupTelecamera.direction.x << endl;
        SetupTelecamera.direction = normalize(front); //Aggiorno la direzione della telecamera
        cout << SetupTelecamera.direction.x << endl;
        SetupTelecamera.target = SetupTelecamera.position + SetupTelecamera.direction; //aggiorno il punto in cui guarda la telecamera

        //Disabilita il cursore del mouse per evitare che si muova fuori dalla finestra durante la navigazione.
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // Imposta la nuova posizione del cursore
        //Riposiziona il cursore al centro della finestra per mantenere una navigazione fluida.
        glfwSetCursorPos(window, (int)center_x, (int)center_y);


    }

    // Trackball ma non navigazione
    if (moving_trackball == true && !isNavigationMode) {

        float velocity = 10.0;
        glm::vec3 destination = getTrackBallPoint(xpos, ypos);
        glm::vec3 origin = getTrackBallPoint(last_mouse_pos_X, last_mouse_pos_Y);
        float dx, dy, dz;
        dx = destination.x - origin.x;
        dy = destination.y - origin.y;
        dz = destination.z - origin.z;

        // Controllo se il mouse si è spostato, altrimenti non eseguo alcun calcolo
        if (dx || dy || dz) {

            // rotation angle = acos( (v dot w) / (len(v) * len(w)) ) o approssimato da ||dest-orig||;
            float pi = glm::pi<float>();
            float angle = sqrt(dx * dx + dy * dy + dz * dz) * velocity;

            // rotation axis = (dest vec orig) / (len(dest vec orig))
            glm::vec3 rotation_vec = glm::cross(origin, destination);

            // calcolo del vettore direzione w = C - A
            SetupTelecamera.direction = -SetupTelecamera.target + SetupTelecamera.position;

            // rotazione del vettore direzione w 
            // determinazione della nuova posizione della camera 
            SetupTelecamera.position = SetupTelecamera.target + vec3(rotate(mat4(1.0f), radians(-angle), rotation_vec) * vec4(SetupTelecamera.direction, 0.0));
        }

        last_mouse_pos_X = xpos;
        last_mouse_pos_Y = ypos;
    }
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    double xpos, ypos;
    
    switch (button) {

        // Pressione tasto sinistro del mouse  
        case GLFW_MOUSE_BUTTON_LEFT:
            
            // Verifica che il mouse non sia sopra all'interfaccia di menu di ImGui 
            if (!ImGui::IsAnyItemHovered()) {

                // Abilita il movimento della trackball
                if (action == GLFW_PRESS)
                    moving_trackball = true;
                // Disabilita il movimento della trackball
                else
                    moving_trackball = false;

                // Prende le posizioni del mouse
                glfwGetCursorPos(window, &xpos, &ypos);

                // Salva le posizioni del mouse
                last_mouse_pos_X = (int)xpos;
                last_mouse_pos_Y = (int)ypos;
            }
            break;

        // Pressione della rotella del mouse
        case GLFW_MOUSE_BUTTON_MIDDLE:
            if (action == GLFW_PRESS) {

                // Ottieni la posizione del mouse
                glfwGetCursorPos(window, &xpos, &ypos);
                float xmouse = xpos;
                float ymouse = ypos;

                // Generazione del raggio (ray tracing) a partire dalle coordinate del mouse
                vec3 ray_wor = get_ray_from_mouse(xmouse, ymouse);

                cout << "Coordinate mouse: " << xmouse << ", " << ymouse << endl;

                // Inizializzazione selezione oggetto (inizialmente nessuno selezionato)
                selected_obj = -1;
                selected_obj_j = -1;
                
                // Inizializzazione distanza intersezione più vicina
                float closest_intersection = 3000.0f;
                
                // Verifica intersezione con oggetti della scena (prende quello più vicino all'osservatore)
                for (int i = 0; i < Scena.size(); i++) {
                    float t_dist = 0.0f;

                    if (ray_sphere(SetupTelecamera.position, ray_wor, Scena[i].ancora_world, raggio_sfera, &t_dist)) {
                        if (selected_obj == -1 || t_dist < closest_intersection) {
                            // Imposta la selezione dell'oggetto all'indice del vettore Scena
                            selected_obj = i;
                            // Imposta la distanza dell'interesezione più vicina a quella dell'oggetto valutato
                            closest_intersection = t_dist;
                        }
                    }
                }

                for (int i = 0; i < ScenaObj.size(); i++) {
                    for (int j = 0; j < ScenaObj[i].size(); j++) {
                        float t_dist = 0.0f;

                        if (ray_sphere(SetupTelecamera.position, ray_wor, ScenaObj[i][j].ancora_world, raggio_sfera, &t_dist)) {
                            if (t_dist < closest_intersection) {
                                // Imposta la selezione dell'oggetto all'indice del vettore Scena
                                selected_obj = i;
                                selected_obj_j = j;
                                // Imposta la distanza dell'interesezione più vicina a quella dell'oggetto valutato
                                closest_intersection = t_dist;
                            }
                        }
                    }
                }
            }
            break;

        // Default
        default:
            break;
    }
    
}
 
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    switch (key) {

        // Se il tasto ESCAPE è premuto, chiude la finestra
        case GLFW_KEY_ESCAPE:
            if (action == GLFW_PRESS)
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;

        //Muove la telecamera in avanti o in alto (shift)
        case GLFW_KEY_W:
            if (mods & GLFW_MOD_SHIFT)
                moveCameraUp();
            else
                moveCameraForward();
            break;

        // Muove la telecamera indietro o in basso (shift)
        case GLFW_KEY_S:
            if (mods & GLFW_MOD_CONTROL) {
                OperationMode = SCALING;
                Operazione = "SCALATURA";
            }
            else if (mods & GLFW_MOD_SHIFT)
                moveCameraDown();
            else
                moveCameraBack();
            break;

        // Muove la telecamera a sinsitra
        case GLFW_KEY_A:
            moveCameraLeft();
            break;

        //Muove la telecamera a destra
        case GLFW_KEY_D:
            moveCameraRight();
            break;

        // Entra in modalità traslazione (come in Blender)
        case GLFW_KEY_G:
            OperationMode = TRASLATING;
            Operazione = "TRASLAZIONE";
            break;

        // Entra in modalità rotazione (come in Blender)
        case GLFW_KEY_R:
            OperationMode = ROTATING;
            Operazione = "ROTAZIONE";
            break;

        // Seleziona l'asse x come asse lungo cui effetturare l'operazione selezionata
        case GLFW_KEY_X:
            WorkingAxis = X;
            stringa_asse = " Asse X";
            break;

        // Seleziona l'asse y come asse lungo cui effetturare l'operazione selezionata
        case GLFW_KEY_Y:
            WorkingAxis = Y;
            stringa_asse = " Asse Y";
            break;

        // Seleziona l'asse z come asse lungo cui effettuare l'operazione selezionata
        case GLFW_KEY_Z:
            WorkingAxis = Z;
            stringa_asse = " Asse Z";
            break;
   
        // Default
        default:
            break;
    }

    // Selezione dell'asse per le trasformazioni
    switch (WorkingAxis) {
        
        // Asse x
        case X:	
            asse = glm::vec3(1.0, 0.0, 0.0);
            break;
        
        // Asse y
        case Y: 
            asse = glm::vec3(0.0, 1.0, 0.0);
            break;

        // Asse z
        case Z: 
            asse = glm::vec3(0.0, 0.0, 1.0);
            break;

        // Default
        default:
            break;

    }

 
    switch (OperationMode) {
    
        // Traslazione
        case TRASLATING:
            
            // Pressione freccia a destra (-> aggiorna la posizione dell'oggetto a destra)
            if (key==GLFW_KEY_RIGHT) {  
                amount = abs(amount);
                modifyModelMatrix(asse * amount, asse, 0.0f, 1.0f);
            }
            
            // Pressione freccia a sinistra (<- aggiorna la posizione dell'oggetto a sinistra)
            if (key == GLFW_KEY_LEFT ) {
                amount = -abs(amount);
                modifyModelMatrix(asse * amount, asse, 0.0f, 1.0f);
            }
            break;

        // Rotazione
        case ROTATING:
            
            // Pressione freccia a destra (-> aggiorna la rotazione in senso antiorario)
            if (key == GLFW_KEY_RIGHT) {
                amount = abs(amount);
                modifyModelMatrix(glm::vec3(0), asse, amount * 2.0f, 1.0f);
            }

            // Pressione freccia a sinistra (<- aggiorna la rotazione in senso orario)
            if (key == GLFW_KEY_LEFT) {
                amount = -abs(amount);
                modifyModelMatrix(glm::vec3(0), asse, amount * 2.0f, 1.0f);
            }
            break;

        // Scalatura
        case SCALING:
            
            // Pressione freccia a destra (-> aggiorna la scalatura come amplificazione delle dimensioni)
            if (key == GLFW_KEY_RIGHT) {
                amount = abs(amount);
                modifyModelMatrix(glm::vec3(0), asse, 0.0f, 1.0f + amount);
            }

            // Pressione freccia a sinistra (<- aggiorna la scalatura come diminuzione delle dimensioni)
            if (key == GLFW_KEY_LEFT) {
                amount = -abs(amount);
                modifyModelMatrix(glm::vec3(0), asse, 0.0f, 1.0f + amount);
            }
            break;

        // Default
        default:
            break;

    }
}
 

void framebuffer_size_callback(GLFWwindow* window, int w, int h) {
    
    //Rapporto larghezza altezza di tutto ciò che è nel mondo 
    float AspectRatio_mondo = (float)(width) / (float)(height);

    //Se l'aspect ratio del mondo è diversa da quella della finestra, mappa in modo diverso per evitare distorsioni
    if (AspectRatio_mondo > w / h) {
        w_up = (float)w;
        h_up = w / AspectRatio_mondo;
    }
    else {
        glViewport(0, 0, h * AspectRatio_mondo, h);
        w_up = h * AspectRatio_mondo;
        h_up = (float)h;
    }

    glViewport(0, 0, w_up, h_up);
}