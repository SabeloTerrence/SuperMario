#include<iostream>
#include<allegro5/allegro.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<sstream>
using namespace std;
void update(float *pos,float screenheight,float screenwidth,float xpos,float ypos,float height,float width){
	pos[0] = -(screenheight / 2) + (xpos + height / 2);
	pos[1] = -(screenwidth / 2) + (ypos + width / 2);

	if (pos[0] < 0)
		pos[0] = 0;
	if (pos[1] < 0)
		pos[1] = 0;
}
int main(){
	ALLEGRO_DISPLAY *display;
	enum direction { UP, LEFT, RIGHT, DUMMY };
	int dir = DUMMY, index = 0;
	if (!al_init())
	{
		al_show_native_message_box(NULL, NULL, NULL, "Couldn't initialise allegro", NULL, NULL);
	}
	display = al_create_display(800, 800);
	if (!display)
	{
		al_show_native_message_box(NULL, NULL, NULL, "Couldn't initialise allegro", NULL, NULL);
	}
	bool done = false, draw = true, active = false;
	float x = 10, y = 300, speed = 5;
	float position[2] = { 0, 0 };
	ALLEGRO_BITMAP *player[11];
	al_install_keyboard();
	al_init_image_addon();
	for (int i = 0; i<11; i++){
		stringstream str;
		str << i + 1 << ".png";
		player[i] = al_load_bitmap(str.str().c_str());
	}
	ALLEGRO_KEYBOARD_STATE state;
	ALLEGRO_TIMER *timer = al_create_timer(2.0 / 60.0);
	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_draw_rectangle(200, 50, 250, 100, al_map_rgb(255, 255, 255), 1.0);
	al_draw_line(0, y + 100, 1000, y + 100, al_map_rgb(255, 255, 255), 2.0);
	al_start_timer(timer);
	while (!done){
		ALLEGRO_EVENT events;
		al_wait_for_event(queue, &events);
		al_get_keyboard_state(&state);
		if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			done = true;
		}
		else if (events.type == ALLEGRO_EVENT_TIMER){
			if (al_key_down(&state, ALLEGRO_KEY_RIGHT)){
				x += speed;
				index++;
				dir = RIGHT;
			}
			if (al_key_down(&state, ALLEGRO_KEY_LEFT)){
				x -= speed;
				index--;
				dir = LEFT;
			}
			update(position, 800, 800, x, y, 35, 35);
			draw = true;
			if (draw){
				if (index > 10){
					index = 0;
				}
				al_draw_bitmap(player[index], x, y, NULL);
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
		}
	}
	al_destroy_display(display);
	for (int k = 0; k<11; k++){
		al_destroy_bitmap(player[k]);
	}
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	return 0;
}