#include <iostream>
#include <stdio.h>
#include <string.h>

#include <allegro5/allegro_image.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#include "personagem.h";//Struct Personagem
#include "elementos.h";//Struct Elementos

#define SIZE_MAX_ELEMENTOS      10


////////////////////////////////////////////
//INDICE
////////////////////////////////////////////

#define INDICE_ELEM_PERSO      0
#define INDICE_ELEM_CLORO      1
#define INDICE_ELEM_SODIO      2


////////////////////////////////////////////
//ID
////////////////////////////////////////////
#define ID_ELEM_CLORO      1
#define ID_ELEM_SODIO      2



//**************************************
// Variaveis
//**************************************
struct personagem nerdola;//Struct personagem


elementos arrayElementos[SIZE_MAX_ELEMENTOS];


int indice_elem_coletados = 0;



float camera_x = 0;//atualiza camera x
float camera_y = 0;//atualiza camera y
float zoom_map = 1;//Dá zoom
int tamanho_map_x = 1000;//Tamanho do mapa x
int tamanho_map_y = 600;//Tamanho do mapa y
int tamanho_nerd_x = 65;//Tamanho x do protagonista
int tamanho_nerd_y = 85;//Tamanho y do protagonista



//**************************************
// Funções
//**************************************

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

void iniciar_elementos() {

    //Inicia Elemento Oxigênio
    arrayElementos[INDICE_ELEM_CLORO].id = INDICE_ELEM_CLORO;
    memcpy((void*)arrayElementos[INDICE_ELEM_CLORO].nome, (void*)"Cloro", sizeof("Cloro"));
    arrayElementos[INDICE_ELEM_CLORO].bitmap = al_load_bitmap("./cloro.png");
    arrayElementos[INDICE_ELEM_CLORO].frame = 0.f;
    arrayElementos[INDICE_ELEM_CLORO].largura = 58;
    arrayElementos[INDICE_ELEM_CLORO].altura = 78;
    arrayElementos[INDICE_ELEM_CLORO].pos_x = -100;
    arrayElementos[INDICE_ELEM_CLORO].pos_y = -178;
    arrayElementos[INDICE_ELEM_CLORO].current_frame_y = 0;
    arrayElementos[INDICE_ELEM_CLORO].time = 0;
    arrayElementos[INDICE_ELEM_CLORO].ativo = true;

    //Inicia Elemento Sodio
    arrayElementos[INDICE_ELEM_SODIO].id = INDICE_ELEM_SODIO;
    memcpy((void*)arrayElementos[INDICE_ELEM_SODIO].nome, (void*)"Sodio", sizeof("Sodio"));
    arrayElementos[INDICE_ELEM_SODIO].bitmap = al_load_bitmap("./sodio.png");
    arrayElementos[INDICE_ELEM_SODIO].frame = 0.f;
    arrayElementos[INDICE_ELEM_SODIO].largura = 58;
    arrayElementos[INDICE_ELEM_SODIO].altura = 78;
    arrayElementos[INDICE_ELEM_SODIO].pos_x = -500;
    arrayElementos[INDICE_ELEM_SODIO].pos_y = -178;
    arrayElementos[INDICE_ELEM_SODIO].current_frame_y = 0;
    arrayElementos[INDICE_ELEM_SODIO].time = 0;
    arrayElementos[INDICE_ELEM_SODIO].ativo = false;
}

void destruir_elementos() {
    for (int indice = 0; indice < SIZE_MAX_ELEMENTOS; indice++) {
        al_destroy_bitmap(arrayElementos[indice].bitmap);
    }
}

//Desenha o fundo de tudo, o mapa e o nerdola 
void desenhar_cena(ALLEGRO_BITMAP* bg, ALLEGRO_BITMAP* sprite, personagem nerdola, elementos arrayElem[]) {

    al_clear_to_color(al_map_rgb(0, 0, 0));

    //desenha a cena
    al_draw_scaled_bitmap(bg, 0, 0, 1920, 1882, -camera_x, -camera_y, 1920 * zoom_map, 1882 * zoom_map, 0);
    
    //desenha o personagem
    al_draw_bitmap_region(sprite, nerdola.largura * (int)nerdola.frame, nerdola.current_frame_y, nerdola.largura, nerdola.altura, (nerdola.pos_x - camera_x), (nerdola.pos_y - camera_y), 0);
    
    // Varre o array de Elementos a serem mostrados na tela
    for (int indice = 0; indice < SIZE_MAX_ELEMENTOS; indice++) {
        // Se o elemento esta ativo?
        if (arrayElementos[indice].ativo == true) {
            // Se a camera esta na região que o elemento deve aparecer ?
            // 01 - Montar uma verificacao consistencia de camera como um quadrado
            if ((camera_x == arrayElementos[indice].pos_x) &&
                (camera_y == arrayElementos[indice].pos_y)) {
                // Desenha o elemento
                al_draw_bitmap_region(arrayElementos[indice].bitmap,
                    arrayElementos[indice].largura * (int)arrayElementos[indice].frame,
                    arrayElementos[indice].current_frame_y,
                    arrayElementos[indice].largura,
                    arrayElementos[indice].altura,
                    (arrayElementos[indice].pos_x - camera_x), 
                    (arrayElementos[indice].pos_y - camera_y),
                    0);
            }
        }
    }
}

//Atualiza a camera comforme o personagem anda pelo mapa
void atualizar_camera() {
    camera_x = nerdola.pos_x - tamanho_map_x / 2;
    camera_y = nerdola.pos_y - tamanho_map_y / 2;
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

    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 20.0);

    ALLEGRO_BITMAP* sprite = al_load_bitmap("./nerdola.png");
    ALLEGRO_BITMAP* bg = al_load_bitmap("./S.png");


    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    iniciar_personagem();

    iniciar_elementos();

    //Loop
    while (true) {

        atualizar_camera();

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        else if ((event.keyboard.keycode == ALLEGRO_KEY_RIGHT || event.keyboard.keycode == ALLEGRO_KEY_D) /* && (nerdola.pos_x < 1920)*/) {
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
        else if ((event.keyboard.keycode == ALLEGRO_KEY_DOWN || event.keyboard.keycode == ALLEGRO_KEY_S) /* && (nerdola.pos_y < 1882)*/) {
            //Down
            nerdola.current_frame_y = 0;
            nerdola.pos_y += 10;
            nerdola.frame += 0.3f;
            if (nerdola.frame > 3) {
                nerdola.frame -= 3;
            }
            nerdola.time = 0;
        }
        else if ((event.keyboard.keycode == ALLEGRO_KEY_UP || event.keyboard.keycode == ALLEGRO_KEY_W ) && (nerdola.pos_y - 1 > 2)) {
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

        al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 10, 0, "nerdola: (%d, %d)", nerdola.pos_x, nerdola.pos_y);

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
