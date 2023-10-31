#pragma once
typedef struct{
	int id;
	unsigned char nome[100];
	ALLEGRO_BITMAP* bitmap;
	float frame;
	int largura;
	int altura;
	int pos_x;
	int pos_y;
	int current_frame_y;
	int time;
	bool ativo;
	bool capturado;
}elementos;