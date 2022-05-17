/*
 * screen_main.c
 *
 *  Created on: 16 de mai. de 2022
 *      Author: rinaldo
 */


#include "lvgl/lvgl.h"
#include <stdio.h>
#include <string.h>


void print_header(void);
void print_clock(void);
void print_freq(long int freq);
void print_rds(void);

LV_IMG_DECLARE(Tela_xt);

static lv_obj_t * Tela_Principal;
static lv_obj_t * img_fundo;
static lv_obj_t * txt_header;
static lv_obj_t * txt_clock;
static lv_obj_t * txt_freq;
static lv_obj_t * txt_rds;
static lv_obj_t * frame6;

char buffer[32] = {0};

void screen_main(void)
{
	Tela_Principal = lv_obj_create(NULL);
	lv_obj_clear_flag(Tela_Principal, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_style_bg_color(Tela_Principal, lv_color_hex(0x0000FF), 0);
	lv_obj_set_style_bg_grad_color(Tela_Principal, lv_color_hex(0x0000FF), 0);

	// Imagem de Fundo
	img_fundo = lv_img_create(Tela_Principal);
	lv_img_cache_invalidate_src(NULL);
	lv_img_set_src(img_fundo, &Tela_xt);
	lv_obj_set_width(img_fundo, LV_HOR_RES);

	print_header();
	print_clock();
	print_freq(9810);
	print_rds();

	lv_scr_load(Tela_Principal);
}


void print_header(void)
{
    // Create a new label
    txt_header = lv_label_create(Tela_Principal);

    lv_obj_set_style_text_font(txt_header, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(txt_header, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(txt_header, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(txt_header, 1, 0);
    lv_obj_set_style_text_line_space(txt_header, 1, 0);

    lv_label_set_long_mode(txt_header, LV_LABEL_LONG_WRAP);     		// Break the long lines
    lv_label_set_recolor(txt_header, true);                      		// Enable re-coloring by commands in the text
    lv_label_set_text_fmt(txt_header, "%s [RDS ON]", "Sinteck Next  DDS\0");
    lv_obj_set_width(txt_header, 500);                           		// Set a width
    lv_obj_set_pos(txt_header, 191, 8);
}


void print_clock(void)
{
	// Clock
	txt_clock = lv_label_create(Tela_Principal);

    lv_obj_set_style_text_font(txt_clock, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(txt_clock, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(txt_clock, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(txt_clock, 1, 0);
    lv_obj_set_style_text_line_space(txt_clock, 1, 0);

	lv_label_set_long_mode(txt_clock, LV_LABEL_LONG_WRAP);		// Break the long lines
	lv_label_set_recolor(txt_clock, true);						// Enable re-coloring by commands in the text

	lv_label_set_text_fmt(txt_clock, "%02d:%02d", 0, 0);
	lv_obj_set_width(txt_clock, 300);							// Set a width
	lv_obj_set_pos(txt_clock, 440, 8);
}

void print_freq(long int freq)
{
	uint16_t q0, q1, q2, q3, q4;

	sprintf(buffer, "%ld", freq);
	if(strlen(buffer) > 4) {
		q0 = buffer[0] - '0';
		q1 = buffer[1] - '0';
		q2 = buffer[2] - '0';
		q3 = buffer[3] - '0';
		q4 = buffer[4] - '0';
		sprintf(buffer, "%d%d%d.%d%d%d MHz", q0, q1, q2, q3, q4, 0);
	}
	else {
		q0 = buffer[0] - '0';
		q1 = buffer[1] - '0';
		q2 = buffer[2] - '0';
		q3 = buffer[3] - '0';
		sprintf(buffer, "%d%d.%d%d%d MHz", q0, q1, q2, q3, 0);
	}

	// teste Desenha Frame
	frame6 = lv_obj_create(Tela_Principal);
    lv_obj_set_size(frame6, 182, 60);
    lv_obj_set_style_radius(frame6, 4, 0);
    lv_obj_set_style_bg_color(frame6, lv_color_hex(0x000000), 0);
    lv_obj_set_style_bg_grad_color(frame6, lv_color_hex(0x000000), 0);
    lv_obj_set_style_border_color(frame6, lv_color_hex(0xAAA9AD), 0);
    lv_obj_set_style_bg_opa(frame6, LV_OPA_50, 0);
    lv_obj_clear_flag(frame6, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_pos(frame6, 5, 4);

	// Cria um novo rotulo
	txt_freq = lv_label_create(frame6);
    lv_obj_set_style_text_font(txt_freq, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(txt_freq, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(txt_freq, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(txt_freq, 1, 0);
    lv_obj_set_style_text_line_space(txt_freq, 1, 0);

	lv_label_set_long_mode(txt_freq, LV_LABEL_LONG_WRAP); 	// Quebra as linhas longas
	lv_label_set_recolor(txt_freq, true); 					// Ativa recolorizar por comandos no texto

	lv_label_set_text(txt_freq, buffer);
	lv_obj_align_to(txt_freq, frame6, LV_ALIGN_CENTER, 0, -14);		// Align to center
}

void print_rds(void)
{
	// Cria um novo rotulo
	txt_rds = lv_label_create(frame6);
    lv_obj_set_style_text_font(txt_rds, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(txt_rds, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(txt_rds, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(txt_rds, 1, 0);
    lv_obj_set_style_text_line_space(txt_rds, 1, 0);

	lv_label_set_long_mode(txt_rds, LV_LABEL_LONG_SCROLL_CIRCULAR);	// Quebra as linhas longas
	lv_label_set_recolor(txt_rds, true); 						// Ativa recolorizar por comandos no texto
	//memset(rds_scrool, ' ', 72);
	//strncpy(rds_scrool, rds2.rt1, strlen(rds2.rt1));
	lv_label_set_text_fmt(txt_rds, "%s", "1234567890");

	lv_obj_set_width(txt_rds, 150); 							// Configuura o comprimento
	lv_obj_align_to(txt_rds, frame6, LV_ALIGN_TOP_LEFT, 0, 14);		// Align to center
}
