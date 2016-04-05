#include<iostream>
#include<allegro5/allegro.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_primitives.h>
using namespace std;
int main(){
	ALLEGRO_DISPLAY *display;
	if (!al_init())
	{
		al_show_native_message_box(NULL, NULL, NULL, "Couldn't initialise allegro", NULL, NULL);
	}
	display = al_create_display(800, 800);
	al_set_window_position(display, 200, 200);
	al_init_image_addon();
	al_install_keyboard();
	ALLEGRO_BITMAP *background = al_load_bitmap("WHu9Z.png");
	ALLEGRO_BITMAP *player = al_load_bitmap("image1.png");
	al_draw_bitmap(background, 0, 0, NULL);
	al_draw_bitmap(player, 50, 50, ALLEGRO_FLIP_HORIZONTAL);
	if (!display)
	{
		al_show_native_message_box(NULL, NULL, NULL, "Couldn't initialise allegro", NULL, NULL);
	}
	al_rest(15.0);
	al_destroy_bitmap(background);
	al_destroy_bitmap(player);
	al_destroy_display(display);
	return 0;
}