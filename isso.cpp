#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <allegro5/allegro_image.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#include "personagem.h";//Struct Personagem
#include "elementos.h";//Struct Elementos
/// <summary>
/// Usar este aqui
/// </summary>
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int POS_X_INICIAL = SCREEN_WIDTH / 2;
const int POS_Y_INICIAL = SCREEN_HEIGHT / 2;


#define SIZE_MAX_ELEMENTOS      11

ALLEGRO_FONT* font = NULL;

////////////////////////////////////////////
//INDICE
////////////////////////////////////////////
   
#define INDICE_ELEM_CLORO       0
#define INDICE_ELEM_SODIO       1
#define INDICE_ELEM_OXIGENIO    2
#define INDICE_ELEM_HIDROGENIO  3
#define INDICE_ELEM_NITROGENIO  4
#define INDICE_ELEM_COBRE       5
#define INDICE_ELEM_ENXOFRE     6 
#define INDICE_ELEM_SAL         7
#define INDICE_ELEM_BOMBA_HIDRO 8
#define INDICE_ELEM_AGUA        9
#define INDICE_ELEM_FOGO        10


////////////////////////////////////////////
//ID
////////////////////////////////////////////

#define ID_ELEM_CLORO       1
#define ID_ELEM_SODIO       2
#define ID_ELEM_OXIGENIO    3
#define ID_ELEM_HIDROGENIO  4
#define ID_ELEM_NITROGENIO  5
#define ID_ELEM_COBRE       6
#define ID_ELEM_ENXOFRE     7 
#define ID_ELEM_SAL         8
#define ID_ELEM_BOMBA_HIDRO 9
#define ID_ELEM_AGUA        10
#define ID_ELEM_FOGO        11

//**************************************
// Variaveis
//**************************************
struct personagem nerdola;//Struct personagem

elementos arrayElementos[SIZE_MAX_ELEMENTOS]; 


//Chama Função iniciar elemento

//Usado na camera
float camera_x = 0;//atualiza camera x
float camera_y = 0;//atualiza camera y
float zoom_map = 2;//Dá zoom

//X para função de capturar usar
float pos_character_x = 0;
float pos_character_x_mais_larg = 0;
float pos_character_y = 0;
float pos_character_y_mais_alt = 0;
//Y para função de capturar usar
float pos_element_x = 0;
float pos_element_x_mais_larg = 0;
float pos_element_y = 0;
float pos_element_y_mais_alt = 0;

//Usado para o personagem e os elementos
int tamanho_map_x = 1000;//Tamanho do mapa x
int tamanho_map_y = 600;//Tamanho do mapa y
int tamanho_nerd_x = 58;//Tamanho x do protagonista
int tamanho_nerd_y = 63;//Tamanho y do protagonista

int tam_map_max_x = 1920;//Tamanho maximo na horizontal
int tam_map_max_y = 1882;//Tamanho maximo na vertical
int num_rand_x = 0;//Numero aleatorio x
int num_rand_y = 0;//Numero aleatorio y

char infoAdicional[10];// Letras
char textoCompleto[20];// Letras finais




//**************************************
// Funções
//**************************************
void num_rand() {
    srand(time(NULL));
    for (int i = 0; i < 7; i++) {
        arrayElementos[i].ativo = true;
    }
    for (int indice = 0; indice < SIZE_MAX_ELEMENTOS; indice++) {
        if (arrayElementos[indice].ativo == true) {
            arrayElementos[indice].pos_x = rand() % (tam_map_max_x - arrayElementos[indice].largura);
            arrayElementos[indice].pos_y = rand() % (tam_map_max_y - arrayElementos[indice].altura);
        }
    }
}

void iniciar_personagem() {
    //Nerdola e seus tamanhos
    nerdola.frame = 0.f;
    nerdola.largura = tamanho_nerd_x;
    nerdola.altura = tamanho_nerd_y;
    nerdola.pos_x = tamanho_map_x - tamanho_nerd_x;
    nerdola.pos_y = tamanho_map_y - tamanho_nerd_y;
    nerdola.current_frame_y = 0;
    nerdola.time = 0;
}

void atualizar_camera() {
    //Atualiza a camera comforme o personagem anda pelo mapa
    camera_x = nerdola.pos_x - tamanho_map_x / 2;
    camera_y = nerdola.pos_y - tamanho_map_y / 2;
}

void iniciar_elementos() {

    srand(time(NULL));
    int ini = 0;
    if(ini == 1 || ini == 0){
    //Inicia Elemento cloro
    arrayElementos[INDICE_ELEM_CLORO].id = INDICE_ELEM_CLORO;
    memcpy((void*)arrayElementos[INDICE_ELEM_CLORO].nome, (void*)"Cloro", sizeof("Cloro"));
    arrayElementos[INDICE_ELEM_CLORO].bitmap = al_load_bitmap("./cloro.png");
    arrayElementos[INDICE_ELEM_CLORO].largura = 54;
    arrayElementos[INDICE_ELEM_CLORO].altura = 182;
    arrayElementos[INDICE_ELEM_CLORO].pos_x = 0;
    arrayElementos[INDICE_ELEM_CLORO].pos_y = 0;
    arrayElementos[INDICE_ELEM_CLORO].contador = 0;
    arrayElementos[INDICE_ELEM_CLORO].ativo = true;
    arrayElementos[INDICE_ELEM_CLORO].capturado = false;
    }
    //Cloro    
    
    if(ini == 2 || ini == 0){
    //Inicia Elemento Sodio
    arrayElementos[INDICE_ELEM_SODIO].id = INDICE_ELEM_SODIO;
    memcpy((void*)arrayElementos[INDICE_ELEM_SODIO].nome, (void*)"Sodio", sizeof("Sodio"));
    arrayElementos[INDICE_ELEM_SODIO].bitmap = al_load_bitmap("./sodio.png");
    arrayElementos[INDICE_ELEM_SODIO].largura = 58;
    arrayElementos[INDICE_ELEM_SODIO].altura = 78;
    arrayElementos[INDICE_ELEM_SODIO].pos_x = 0;
    arrayElementos[INDICE_ELEM_SODIO].pos_y = 0;
    arrayElementos[INDICE_ELEM_SODIO].contador = 0;
    arrayElementos[INDICE_ELEM_SODIO].ativo = true;
    arrayElementos[INDICE_ELEM_SODIO].capturado = false;
    }
    //sodio

    if (ini == 3 || ini == 0) {
        //Inicia Elemento Oxigênio
        arrayElementos[INDICE_ELEM_OXIGENIO].id = INDICE_ELEM_OXIGENIO;
        memcpy((void*)arrayElementos[INDICE_ELEM_OXIGENIO].nome, (void*)"OXIGENIO", sizeof("OXIGENIO"));
        arrayElementos[INDICE_ELEM_OXIGENIO].bitmap = al_load_bitmap("./cloro.png");
        arrayElementos[INDICE_ELEM_OXIGENIO].largura = 50;
        arrayElementos[INDICE_ELEM_OXIGENIO].altura = 50;
        arrayElementos[INDICE_ELEM_OXIGENIO].pos_x = 0;
        arrayElementos[INDICE_ELEM_OXIGENIO].pos_y = 0;
        arrayElementos[INDICE_ELEM_OXIGENIO].contador = 0;
        arrayElementos[INDICE_ELEM_OXIGENIO].ativo = true;
        arrayElementos[INDICE_ELEM_OXIGENIO].capturado = false;
    }
    //Oxigênio

    if (ini == 4 || ini == 0) {
        //Inicia Elemento HIDROGENIO
        arrayElementos[INDICE_ELEM_HIDROGENIO].id = INDICE_ELEM_HIDROGENIO;
        memcpy((void*)arrayElementos[INDICE_ELEM_HIDROGENIO].nome, (void*)"HIDROGENIO", sizeof("HIDROGENIO"));
        arrayElementos[INDICE_ELEM_HIDROGENIO].bitmap = al_load_bitmap("./cloro.png");
        arrayElementos[INDICE_ELEM_HIDROGENIO].largura = 50;
        arrayElementos[INDICE_ELEM_HIDROGENIO].altura = 50;
        arrayElementos[INDICE_ELEM_HIDROGENIO].pos_x = 0;
        arrayElementos[INDICE_ELEM_HIDROGENIO].pos_y = 0;
        arrayElementos[INDICE_ELEM_HIDROGENIO].contador = 0;
        arrayElementos[INDICE_ELEM_HIDROGENIO].ativo = true;
        arrayElementos[INDICE_ELEM_HIDROGENIO].capturado = false;
    }
    //HIDROGENIO

    if (ini == 5 || ini == 0) {
        //Inicia Elemento NITROGENIO
        arrayElementos[INDICE_ELEM_NITROGENIO].id = INDICE_ELEM_NITROGENIO;
        memcpy((void*)arrayElementos[INDICE_ELEM_NITROGENIO].nome, (void*)"NITROGENIO", sizeof("NITROGENIO"));
        arrayElementos[INDICE_ELEM_NITROGENIO].bitmap = al_load_bitmap("./cloro.png");
        arrayElementos[INDICE_ELEM_NITROGENIO].largura = 50;
        arrayElementos[INDICE_ELEM_NITROGENIO].altura = 50;
        arrayElementos[INDICE_ELEM_NITROGENIO].pos_x = 0;
        arrayElementos[INDICE_ELEM_NITROGENIO].pos_y = 0;
        arrayElementos[INDICE_ELEM_NITROGENIO].contador = 0;
        arrayElementos[INDICE_ELEM_NITROGENIO].ativo = true;
        arrayElementos[INDICE_ELEM_NITROGENIO].capturado = false;
    }
    //NITROGENIO

    if (ini == 6 || ini == 0) {
        //Inicia Elemento COBRE
        arrayElementos[INDICE_ELEM_COBRE].id = INDICE_ELEM_COBRE;
        memcpy((void*)arrayElementos[INDICE_ELEM_COBRE].nome, (void*)"COBRE", sizeof("COBRE"));
        arrayElementos[INDICE_ELEM_COBRE].bitmap = al_load_bitmap("./cloro.png");
        arrayElementos[INDICE_ELEM_COBRE].largura = 50;
        arrayElementos[INDICE_ELEM_COBRE].altura = 50;
        arrayElementos[INDICE_ELEM_COBRE].pos_x = 0;
        arrayElementos[INDICE_ELEM_COBRE].pos_y = 0;
        arrayElementos[INDICE_ELEM_COBRE].contador = 0;
        arrayElementos[INDICE_ELEM_COBRE].ativo = true;
        arrayElementos[INDICE_ELEM_COBRE].capturado = false;
    }
    //COBRE

    if (ini == 7 || ini == 0) {
        //Inicia Elemento ENXOFRE
        arrayElementos[INDICE_ELEM_ENXOFRE].id = INDICE_ELEM_ENXOFRE;
        memcpy((void*)arrayElementos[INDICE_ELEM_ENXOFRE].nome, (void*)"ENXOFRE", sizeof("ENXOFRE"));
        arrayElementos[INDICE_ELEM_ENXOFRE].bitmap = al_load_bitmap("./cloro.png");
        arrayElementos[INDICE_ELEM_ENXOFRE].largura = 50;
        arrayElementos[INDICE_ELEM_ENXOFRE].altura = 50;
        arrayElementos[INDICE_ELEM_ENXOFRE].pos_x = 0;
        arrayElementos[INDICE_ELEM_ENXOFRE].pos_y = 0;
        arrayElementos[INDICE_ELEM_ENXOFRE].contador = 0;
        arrayElementos[INDICE_ELEM_ENXOFRE].ativo = true;
        arrayElementos[INDICE_ELEM_ENXOFRE].capturado = false;
    }
    //ENXOFRE

    if (ini == 8 || ini == 0) {
        //Inicia Elemento SAL
        arrayElementos[INDICE_ELEM_SAL].id = INDICE_ELEM_SAL;
        memcpy((void*)arrayElementos[INDICE_ELEM_SAL].nome, (void*)"SAL", sizeof("SAL"));
        arrayElementos[INDICE_ELEM_SAL].bitmap = al_load_bitmap("./cloro.png");
        arrayElementos[INDICE_ELEM_SAL].largura = 0;
        arrayElementos[INDICE_ELEM_SAL].altura = 0;
        arrayElementos[INDICE_ELEM_SAL].pos_x = 0;
        arrayElementos[INDICE_ELEM_SAL].pos_y = 0;
        arrayElementos[INDICE_ELEM_SAL].contador = 0;
        arrayElementos[INDICE_ELEM_SAL].ativo = false;
        arrayElementos[INDICE_ELEM_SAL].capturado = false;
    }
    //SAL

    if (ini == 9 || ini == 0) {
        //Inicia Elemento BOMBA_HIDRO
        arrayElementos[INDICE_ELEM_BOMBA_HIDRO].id = INDICE_ELEM_BOMBA_HIDRO;
        memcpy((void*)arrayElementos[INDICE_ELEM_BOMBA_HIDRO].nome, (void*)"BOMBA_HIDRO", sizeof("BOMBA_HIDRO"));
        arrayElementos[INDICE_ELEM_BOMBA_HIDRO].bitmap = al_load_bitmap("./cloro.png");
        arrayElementos[INDICE_ELEM_BOMBA_HIDRO].largura = 0;
        arrayElementos[INDICE_ELEM_BOMBA_HIDRO].altura = 0;
        arrayElementos[INDICE_ELEM_BOMBA_HIDRO].pos_x = 0;
        arrayElementos[INDICE_ELEM_BOMBA_HIDRO].pos_y = 0;
        arrayElementos[INDICE_ELEM_BOMBA_HIDRO].contador = 0;
        arrayElementos[INDICE_ELEM_BOMBA_HIDRO].ativo = false;
        arrayElementos[INDICE_ELEM_BOMBA_HIDRO].capturado = false;
    }
    //BOMBA_HIDRO

    if (ini == 10 || ini == 0) {
        //Inicia Elemento AGUA
        arrayElementos[INDICE_ELEM_AGUA].id = INDICE_ELEM_AGUA;
        memcpy((void*)arrayElementos[INDICE_ELEM_AGUA].nome, (void*)"AGUA", sizeof("AGUA"));
        arrayElementos[INDICE_ELEM_AGUA].bitmap = al_load_bitmap("./cloro.png");
        arrayElementos[INDICE_ELEM_AGUA].largura = 0;
        arrayElementos[INDICE_ELEM_AGUA].altura = 0;
        arrayElementos[INDICE_ELEM_AGUA].pos_x = 0;
        arrayElementos[INDICE_ELEM_AGUA].pos_y = 0;
        arrayElementos[INDICE_ELEM_AGUA].contador = 0;
        arrayElementos[INDICE_ELEM_AGUA].ativo = false;
        arrayElementos[INDICE_ELEM_AGUA].capturado = false;
    }
    //AGUA

    if (ini == 11 || ini == 0) {
        //Inicia Elemento FOGO
        arrayElementos[INDICE_ELEM_FOGO].id = INDICE_ELEM_FOGO;
        memcpy((void*)arrayElementos[INDICE_ELEM_FOGO].nome, (void*)"FOGO", sizeof("FOGO"));
        arrayElementos[INDICE_ELEM_FOGO].bitmap = al_load_bitmap("./cloro.png");
        arrayElementos[INDICE_ELEM_FOGO].largura = 0;
        arrayElementos[INDICE_ELEM_FOGO].altura = 0;
        arrayElementos[INDICE_ELEM_FOGO].pos_x = 0;
        arrayElementos[INDICE_ELEM_FOGO].pos_y = 0;
        arrayElementos[INDICE_ELEM_FOGO].contador = 0;
        arrayElementos[INDICE_ELEM_FOGO].ativo = false;
        arrayElementos[INDICE_ELEM_FOGO].capturado = false;
    }
    //FOGO
}

void capturação() {
    pos_character_x = nerdola.pos_x;
    pos_character_x_mais_larg = nerdola.pos_x + tamanho_nerd_x;
    pos_character_y = nerdola.pos_y;
    pos_character_y_mais_alt = nerdola.pos_y + tamanho_nerd_y;




    //Varre o array para ver como está indo o bicho
    for (int indice = 0; indice < SIZE_MAX_ELEMENTOS; indice++) {
        // Ve o elemento esta ativo e ve o elemento NAO foi capturado
        if (arrayElementos[indice].ativo == true && arrayElementos[indice].capturado == false) {

            // Calcula Quadrado do Elemento
            pos_element_x = arrayElementos[indice].pos_x;
            pos_element_x_mais_larg = arrayElementos[indice].pos_x + arrayElementos[indice].largura;
            pos_element_y = arrayElementos[indice].pos_y;
            pos_element_y_mais_alt = arrayElementos[indice].pos_y + arrayElementos[indice].altura;

            // Se algum ponto do quadrado do personagem estiver dentro do quadrado do elemento  
            if (            
                (((pos_character_x >= pos_element_x) && (pos_character_x <= pos_element_x_mais_larg)) ||
                ((pos_character_x_mais_larg >= pos_element_x) && (pos_character_x_mais_larg <= pos_element_x_mais_larg))
                ) && (
                ((pos_character_y >= pos_element_y) && (pos_character_y <= pos_element_y_mais_alt)) ||
                ((pos_character_y_mais_alt >= pos_element_y) && (pos_character_y_mais_alt <= pos_element_y_mais_alt))
                )
                )
            {                
                arrayElementos[indice].pos_x = rand() % (tam_map_max_x - arrayElementos[indice].largura);
                arrayElementos[indice].pos_y = rand() % (tam_map_max_y - arrayElementos[indice].altura);
                arrayElementos[indice].contador += 1;
            }
        }
    }


}

void craft() {

    //Sal
    if ((arrayElementos[INDICE_ELEM_SODIO].contador >= 1) 
        && (arrayElementos[INDICE_ELEM_CLORO].contador >= 1)) {
        arrayElementos[INDICE_ELEM_SAL].contador += 1;
        arrayElementos[INDICE_ELEM_SODIO].contador -= 1;
        arrayElementos[INDICE_ELEM_CLORO].contador -= 1;
    }


    //Fogo
    if ((arrayElementos[INDICE_ELEM_SODIO].capturado == true)
        && (arrayElementos[INDICE_ELEM_CLORO].capturado == true)
        && (1 == 1)) {

    }


    //Bomba de Hidrogenio
    if ((arrayElementos[INDICE_ELEM_SODIO].capturado == true)
        && (arrayElementos[INDICE_ELEM_CLORO].capturado == true)
        && (1 == 1)) {

    }


    ///Agua
    if ((arrayElementos[INDICE_ELEM_OXIGENIO].contador >= 1) 
        && (arrayElementos[INDICE_ELEM_HIDROGENIO].contador >= 2)) {
        arrayElementos[INDICE_ELEM_AGUA].contador += 1;
        arrayElementos[INDICE_ELEM_OXIGENIO].contador -= 1;
        arrayElementos[INDICE_ELEM_HIDROGENIO].contador -= 2;
    }


}

void desenhar_cena(ALLEGRO_BITMAP* bg, ALLEGRO_BITMAP* sprite, personagem nerdola, elementos arrayElem[]) {
    //Desenha o fundo do jogo, o mapa e o nerdola 

    //Da um fundo preto ao jogo
    al_clear_to_color(al_map_rgb(0, 0, 0));


    //desenha a cena
    al_draw_scaled_bitmap(bg, 0, 0, tam_map_max_x, tam_map_max_y, -camera_x, -camera_y, tam_map_max_x * zoom_map, tam_map_max_y * zoom_map, 0);


    //desenha o personagem
    al_draw_bitmap_region(sprite, nerdola.largura * (int)nerdola.frame, nerdola.current_frame_y, nerdola.largura, nerdola.altura, (nerdola.pos_x - camera_x), (nerdola.pos_y - camera_y), 0);


   
    //desenha elementos
    for (int indice = 0; indice < SIZE_MAX_ELEMENTOS; indice++) {
        if (arrayElementos[indice].ativo == true) {
            al_draw_bitmap(arrayElementos[INDICE_ELEM_CLORO].bitmap, arrayElementos[indice].pos_x - camera_x, arrayElementos[indice].pos_y - camera_y, 0);
        }

        float pos_text_y = 20;
        for (int indice = 0; indice < SIZE_MAX_ELEMENTOS; indice++) {
            // Se o elemento esta capturado
                snprintf(infoAdicional, sizeof(infoAdicional), " %d", arrayElementos[indice].contador);
                snprintf(textoCompleto, sizeof(textoCompleto), "%s%s", arrayElementos[indice].nome, infoAdicional);
                al_draw_textf(font, al_map_rgb(255, 0, 0), 10, pos_text_y + 10, 0, textoCompleto);
                pos_text_y = pos_text_y + 10;            
        }
    }
}

void destruir_elementos() {
    for (int indice = 0; indice < SIZE_MAX_ELEMENTOS; indice++) {
        al_destroy_bitmap(arrayElementos[indice].bitmap);
    }
}



//**************************************
// Principal
//**************************************
int main() {

    al_init();
    al_init_font_addon();
    al_init_image_addon();
    al_install_keyboard();

    ALLEGRO_DISPLAY* display = al_create_display(tamanho_map_x, tamanho_map_y);
    al_set_window_position(display, 200, 200);
    al_set_window_title(display, "Reino da Alquimia");

    font = al_create_builtin_font();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 20.0);

    ALLEGRO_BITMAP* sprite = al_load_bitmap("./nerdola.png");
    ALLEGRO_BITMAP* bg = al_load_bitmap("./cena.png");


    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    
    //Inicia Personagem

    iniciar_personagem();

    //Inicia Elementos
   
    iniciar_elementos();


    //Numeros Aleatorios a todos
    num_rand();
    
    

    //Loop
    while (true) {
        //Atualiza camera
        atualizar_camera();

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);


        //Se clicar no C irá fazer a função craft
        if (event.keyboard.keycode == ALLEGRO_KEY_C) {
            craft();
        }


        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        else if ((event.keyboard.keycode == ALLEGRO_KEY_RIGHT || event.keyboard.keycode == ALLEGRO_KEY_D)  && (nerdola.pos_x + tamanho_nerd_x < tam_map_max_x)) {
            //Right
            nerdola.current_frame_y = nerdola.altura;
            nerdola.pos_x += 10;
            nerdola.frame += 0.3f;
            if (nerdola.frame > 3) {
                nerdola.frame -= 3;
            }
            nerdola.time = 0;
        }
        else if ((event.keyboard.keycode == ALLEGRO_KEY_LEFT || event.keyboard.keycode == ALLEGRO_KEY_A) && (nerdola.pos_x - 1 > 2)) {
            //Left
            nerdola.current_frame_y = nerdola.altura * 3;
            nerdola.pos_x -= 10;
            nerdola.frame += 0.3f;
            if (nerdola.frame > 3) {
                nerdola.frame -= 3;
            }
            nerdola.time = 0;
        }
        else if ((event.keyboard.keycode == ALLEGRO_KEY_DOWN || event.keyboard.keycode == ALLEGRO_KEY_S) && (nerdola.pos_y + tamanho_nerd_y < tam_map_max_y)) {
            //Down
            nerdola.current_frame_y = 0;
            nerdola.pos_y += 10;
            nerdola.frame += 0.3f;
            if (nerdola.frame > 3) {
                nerdola.frame -= 3;
            }
            nerdola.time = 0;
        }
        else if ((event.keyboard.keycode == ALLEGRO_KEY_UP || event.keyboard.keycode == ALLEGRO_KEY_W) && (nerdola.pos_y - 1 > 2)) {
            //Up
            nerdola.current_frame_y = nerdola.altura * 2;
            nerdola.pos_y -= 10;
            nerdola.frame += 0.3f;
            if (nerdola.frame > 3) {
                nerdola.frame -= 3;
            }
            nerdola.time = 0;
        }
        else {
            nerdola.time++;
        }
       

        if (nerdola.time > 12) {
            nerdola.current_frame_y = nerdola.altura * 4;
            nerdola.frame += 0.1f;
            if (nerdola.frame > 2) {
                nerdola.frame -= 2;
            }
        };
        

        //desenhar_cena(bg, sprite, nerdola);
        desenhar_cena(bg, sprite, nerdola, arrayElementos);

        //Verificar a captura
        capturação();

        al_draw_textf(font, al_map_rgb(0, 0,0 ), 10, 10, 0, "nerdola: (%d, %d)", nerdola.pos_x, nerdola.pos_y);

        al_flip_display();
    }

    // Destroi elementos
    destruir_elementos();

    al_destroy_bitmap(sprite);
    al_destroy_bitmap(bg);
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);

    return 0;
}

