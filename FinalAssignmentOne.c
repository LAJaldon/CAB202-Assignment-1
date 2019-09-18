#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>

//Configuration

#define PLAYER_HEIGHT 4
#define PLAYER_WIDTH 3
#define STARTING_BLOCK_HEIGHT 2
#define STARTING_BLOCK_WIDTH 7
#define SAFE_BLOCK_HEIGHT 2
#define SAFE_BLOCK_WIDTH 7
#define FORBIDDEN_BLOCK_HEIGHT 2
#define FORBIDDEN_BLOCK_WIDTH 7
#define TREASURE_HEIGHT 2
#define TREASURE_WIDTH 2
#define FOOD_HEIGHT 2
#define FOOD_WIDTH 2
#define ZOMBIE_HEIGHT 4
#define ZOMBIE_WIDTH 3
#define DELAY (10)

///// sprite id ///////////
#define MAX_PLATFORMS (100000)
sprite_id platform_safe[MAX_PLATFORMS];
sprite_id platform_forbidden[MAX_PLATFORMS];
sprite_id platform_safe_offscreen[MAX_PLATFORMS];
sprite_id platform_forbidden_offscreen[MAX_PLATFORMS];
sprite_id platform_safe_right[MAX_PLATFORMS];
sprite_id platform_forbidden_right[MAX_PLATFORMS];
sprite_id platform_safe_offscreen_right[MAX_PLATFORMS];
sprite_id platform_forbidden_offscreen_right[MAX_PLATFORMS];
//////zombie id///////


//global variables
int lives = 10;

bool game_over = false;
bool gravity_toggle = true;
bool pause = false;
bool pause_treasure = false;
bool restart_game = false;
bool food_created = false;
bool food_gravity = true;
bool zombie_gravity = true;



char * _Time = 
/**/ "Time:";

char * _Score =
/**/ "Score";

char *_Student_Number = 
/**/ "Student Number:"; 

char * game_over_message = 
/**/ "       GAME OVER! ALL LIVES LOST!  "
     "             Playing Time:         "
	 "             Total Score:          ";

char * player_image =
/**/  " o "
      "x|x"
	  " | "
	  "e e"; 
	  
 
char * safe_block_image = 
	 "======="
	 "=======";

char * forbidden_block_image =
	 "xxxxxxx"
	 "xxxxxxx";
	 
char * treasure_image =
	 "$^"
	 "v$";
	 
char * food_image =
	"~~"
	"~~";
	
char * zombie_image = 
	" z "
	"zzz"
	" z "
	"z z";

// declaring sprited_id called player_start
sprite_id player_start; 
sprite_id safe_block;
sprite_id forbidden_block;
sprite_id treasure;
sprite_id starting_block;
sprite_id respawn_block;
sprite_id second_respawn_block;
sprite_id added_food;
sprite_id zombie1;
sprite_id zombie2;
sprite_id zombie3;
sprite_id zombie4;
sprite_id zombie5;

int _student_number = 10000381; 
int score = 0;
int food = 5;
int zombies = 1;

// declaring time parameters
int milliseconds = 0; 
int seconds = 0;
int minutes = 0;

void dashboard (void) {
	

	draw_formatted( 2, 1, "Student Number: %d", _student_number);
	draw_formatted( 2, 3, "Lives: %d", lives); 
	draw_formatted ( 30, 3, "Time: %.2d:%.2d", minutes, seconds);
	draw_formatted( 70, 3, "Score: %d", score);
	draw_formatted( 90, 3, "Food: %d", food);
	draw_formatted( 110, 3, "Zombies: %d", zombies);
	
}



void draw_border (void) {
	
int w = screen_width(); 

int left = -1;

int top = 0;

int right = w;

int bottom = 5;
	
	// // DASHBOARD BORDER // 
    // (e) Draw a line from (left, top) to (right, top), using the '~' symbol
	
    draw_line(left, top, right, top, '~');
    draw_line(right, top, right, bottom, ' ');
    draw_line(left, bottom, right, bottom, '~');
    draw_line(left, top, left, bottom, ' ');

}

void game_timer(void) {
	milliseconds++;
	if (milliseconds == 100) {
		milliseconds = 0;
		seconds++;
	}
	if (seconds == 60) {
		seconds = 0;
		minutes++;
	}
}



///////////////////////////////////////making blocks on all screen//////////////////////////////////////
void first_block(void)
{
    starting_block = sprite_create(179, 11, SAFE_BLOCK_WIDTH, SAFE_BLOCK_HEIGHT, safe_block_image);
    sprite_draw(starting_block);
}

void second_block(void)
{
    respawn_block = sprite_create(94, 11, SAFE_BLOCK_WIDTH, SAFE_BLOCK_HEIGHT, safe_block_image);
    sprite_draw(respawn_block);
}

void third_block(void)
{
    second_respawn_block = sprite_create(5, 11, SAFE_BLOCK_WIDTH, SAFE_BLOCK_HEIGHT, safe_block_image);
    sprite_draw(second_respawn_block);
}



sprite_id draw_platform_safe(){
    //int h = screen_height();
    int random_x_coordinate_placement = rand() % 34;
    int random_y_coordinate_placement = rand() % 3;
    
    int crx[] = {0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120, 128, 134, 142, 150, 158, 166, 174, 182, 190, 198, 206, 214, 222, 230, 238, 246, 254, 262};
    int cry[]={16, 30, 44};
    
    int columns = crx[random_x_coordinate_placement];
    int rows = cry[random_y_coordinate_placement];
    
    sprite_id platform_safe = sprite_create(columns, rows, SAFE_BLOCK_WIDTH, SAFE_BLOCK_HEIGHT, safe_block_image);
    sprite_draw(platform_safe);
    
    return platform_safe;
}

sprite_id draw_forbidden_block(){
    //int h = screen_height();
    int random_x_coordinate_placement = rand() % 34;
    int random_y_coordinate_placement = rand() % 3;

    int crx[] = {0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120, 128, 134, 142, 150, 158, 166, 174, 182, 190, 198, 206, 214, 222, 230, 238, 246, 254, 262};
     int cry[]={16, 30, 44};
    
    int columns = crx[random_x_coordinate_placement];
    int rows = cry[random_y_coordinate_placement];
    
    sprite_id platform_forbidden = sprite_create(columns, rows, FORBIDDEN_BLOCK_WIDTH, FORBIDDEN_BLOCK_HEIGHT, forbidden_block_image);
    sprite_draw(platform_forbidden);
    
    return platform_forbidden;
}

sprite_id draw_platform_safe_offscreen(){
    //int h = screen_height();
    int random_x_coordinate_placement = rand() % 34;
    int random_y_coordinate_placement = rand() % 3;
    
    int crx[] = {-270, -262, -254, -246, -238, -230, -222, -214, -206, -198, -190, -182, -174, -166, -158, -150, -142, -134, -128, -120, -112, -104, -96, -88, -80, -72, -64, -56, -48, -40, -32, -24, -16, -8};
	int cry[]={16, 30, 44};

    int columns = crx[random_x_coordinate_placement];
    int rows = cry[random_y_coordinate_placement];
    
    sprite_id platform_safe_offscreen = sprite_create(columns, rows, SAFE_BLOCK_WIDTH, SAFE_BLOCK_HEIGHT, safe_block_image);
    sprite_draw(platform_safe_offscreen);
    
    return platform_safe_offscreen;
}

sprite_id draw_forbidden_block_offscreen(){
    //int h = screen_height();
    int random_x_coordinate_placement = rand() % 34;
    int random_y_coordinate_placement = rand() % 3;
    
    int crx[] = {-270, -262, -254, -246, -238, -230, -222, -214, -206, -198, -190, -182, -174, -166, -158, -150, -142, -134, -128, -120, -112, -104, -96, -88, -80, -72, -64, -56, -48, -40, -32, -24, -16, -8};
    int cry[]={16, 30, 44};

    int columns = crx[random_x_coordinate_placement];
    int rows = cry[random_y_coordinate_placement];
    
    sprite_id platform_forbidden_offscreen = sprite_create(columns, rows, FORBIDDEN_BLOCK_WIDTH, FORBIDDEN_BLOCK_HEIGHT, forbidden_block_image);
    sprite_draw(platform_forbidden_offscreen);
    
    return platform_forbidden_offscreen;
}

sprite_id setup_zombies() {
	
	int random_x_coordinate_placement = rand() % 10;
	int y_coordinate_placement = rand() % 1;
	
	int crx[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	int cry[] = {13}; 
	
	int x_coordinate = crx[random_x_coordinate_placement];
	int y_coordinate = cry[y_coordinate_placement];
	
	sprite_id zombies_spawn = sprite_create(x_coordinate, y_coordinate, ZOMBIE_WIDTH, ZOMBIE_HEIGHT, zombie_image);
    sprite_draw(zombies_spawn);
    
    return zombies_spawn;
	
}

sprite_id draw_platform_safe_right(){
    //int h = screen_height();
    int random_x_coordinate_placement = rand() % 34;
    int random_y_coordinate_placement = rand() % 3;
    
    int crx[] = {0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120, 128, 134, 142, 150, 158, 166, 174, 182, 190, 198, 206, 214, 222, 230, 238, 246, 254, 262};
    int cry[]={23, 37, 51};
    
    int columns = crx[random_x_coordinate_placement];
    int rows = cry[random_y_coordinate_placement];
    
    sprite_id platform_safe = sprite_create(columns, rows, SAFE_BLOCK_WIDTH, SAFE_BLOCK_HEIGHT, safe_block_image);
    sprite_draw(platform_safe);
    
    return platform_safe;
}

sprite_id draw_forbidden_block_right(){
    //int h = screen_height();
    int random_x_coordinate_placement = rand() % 34;
    int random_y_coordinate_placement = rand() % 3;

    int crx[] = {0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120, 128, 134, 142, 150, 158, 166, 174, 182, 190, 198, 206, 214, 222, 230, 238, 246, 254, 262};
    int cry[]={23, 37, 51};
    
    int columns = crx[random_x_coordinate_placement];
    int rows = cry[random_y_coordinate_placement];
    
    sprite_id platform_forbidden = sprite_create(columns, rows, FORBIDDEN_BLOCK_WIDTH, FORBIDDEN_BLOCK_HEIGHT, forbidden_block_image);
    sprite_draw(platform_forbidden);
    
    return platform_forbidden;
}

sprite_id draw_platform_safe_offscreen_right(){
    //int h = screen_height();
    int random_x_coordinate_placement = rand() % 34;
    int random_y_coordinate_placement = rand() % 3;
    
    int crx[] = {270, 278, 286, 294, 302, 310, 318, 326, 334, 342, 350, 358, 366, 374, 382, 390, 398, 406, 414, 422, 430, 438, 446, 454, 462, 470, 478, 486, 494, 502, 510, 518, 526, 534};
	int cry[]={23, 37, 51};

    int columns = crx[random_x_coordinate_placement];
    int rows = cry[random_y_coordinate_placement];
    
    sprite_id platform_safe_offscreen = sprite_create(columns, rows, SAFE_BLOCK_WIDTH, SAFE_BLOCK_HEIGHT, safe_block_image);
    sprite_draw(platform_safe_offscreen);
    
    return platform_safe_offscreen;
}

sprite_id draw_forbidden_block_offscreen_right(){
    //int h = screen_height();
    int random_x_coordinate_placement = rand() % 34;
    int random_y_coordinate_placement = rand() % 3;
    
int crx[] = {270, 278, 286, 294, 302, 310, 318, 326, 334, 342, 350, 358, 366, 374, 382, 390, 398, 406, 414, 422, 430, 438, 446, 454, 462, 470, 478, 486, 494, 502, 510, 518, 526, 534};
    int cry[]={23, 37, 51};

    int columns = crx[random_x_coordinate_placement];
    int rows = cry[random_y_coordinate_placement];
    
    sprite_id platform_forbidden_offscreen = sprite_create(columns, rows, FORBIDDEN_BLOCK_WIDTH, FORBIDDEN_BLOCK_HEIGHT, forbidden_block_image);
    sprite_draw(platform_forbidden_offscreen);
    
    return platform_forbidden_offscreen;
}

//////////////////////////////////////////////////////////////


////////////////////////////
void draw_all()
{
    clear_screen();
	first_block();
	second_block();
	third_block();
    sprite_draw(player_start);
	if (food_created == true) 
	{
		sprite_draw(added_food);
	}
    dashboard();
	draw_border();
    sprite_draw(treasure);
}
//////////////////////////

//////////////////////moving the blocks//////////////////////////////

void right_setup(void) {
	
	for (int i=0; i<80; i++) {
		platform_safe_right[i] = draw_platform_safe_right();
	}

    for (int i=0; i<80; i++) {
		platform_safe_offscreen_right[i] = draw_platform_safe_offscreen_right();
	}

	for(int i=0; i<10; i++) {
	 	platform_forbidden_right[i] = draw_forbidden_block_right();
 	}

    for(int i=0; i<10; i++) {
	 	platform_forbidden_offscreen_right[i] = draw_forbidden_block_offscreen_right();
 	}
	
	
}

void setup_zombie1 (void) {
	
	int dice_roll = rand() % 90;
		
		
		if (dice_roll <= 10 )  {
			zombie1 = sprite_create(14, 9, ZOMBIE_WIDTH, ZOMBIE_HEIGHT, zombie_image);     
		}
		else if (dice_roll <= 20) {
			zombie1 = sprite_create(30, 9, ZOMBIE_WIDTH, ZOMBIE_HEIGHT, zombie_image);     
		}	
		else if (dice_roll <= 30){
			zombie1 = sprite_create(50, 9, ZOMBIE_WIDTH, ZOMBIE_HEIGHT, zombie_image);     
		}
		else if (dice_roll <= 40){
			zombie1 = sprite_create(70, 9, ZOMBIE_WIDTH, ZOMBIE_HEIGHT, zombie_image);     
		}
		else if (dice_roll <= 50){
			zombie1 = sprite_create(90, 9, ZOMBIE_WIDTH, ZOMBIE_HEIGHT, zombie_image);     
		}
		else if (dice_roll <= 60){
			zombie1 = sprite_create(110, 9, ZOMBIE_WIDTH, ZOMBIE_HEIGHT, zombie_image);     
		}
		else if (dice_roll <= 70){
			zombie1 = sprite_create(130, 9, ZOMBIE_WIDTH, ZOMBIE_HEIGHT, zombie_image);     
		}
		else {
			zombie1 = sprite_create(150, 9, ZOMBIE_WIDTH, ZOMBIE_HEIGHT, zombie_image);     
		}
 
	sprite_draw(zombie1);
	zombie_gravity = true;
}


void setup(void)
{
   

    treasure = sprite_create(1, 55, TREASURE_WIDTH, TREASURE_HEIGHT, treasure_image);
    sprite_turn_to(treasure, 0.3, 0);

    player_start = sprite_create(180, 7, PLAYER_WIDTH, PLAYER_HEIGHT, player_image);
	
	setup_zombie1();

	

    //srand(time(0));

    for (int i=0; i<80; i++) {
		platform_safe[i] = draw_platform_safe();
	}

    for (int i=0; i<80; i++) {
		platform_safe_offscreen[i] = draw_platform_safe_offscreen();
	}

	for(int i=0; i<10; i++) {
	 	platform_forbidden[i] = draw_forbidden_block();
 	}

    for(int i=0; i<10; i++) {
	 	platform_forbidden_offscreen[i] = draw_forbidden_block_offscreen();
 	}
     
	right_setup();
	
    draw_all();
}

int key_reader()
{
    int key_code = pause ? wait_char() : get_char();

    if ('p' == key_code)
    {
        pause = !pause;
    }

    if ('t' == key_code)
    {
        pause_treasure = !pause_treasure;
    } 
    return key_code;
}


///////////////////////////////////////////////////////////////////////////

void draw_platforms1()
{
    for (int i = 0; i<80; i++)
    {
        sprite_turn_to(platform_safe[i], 0.05, 0);
        sprite_step(platform_safe[i]);
		sprite_draw(platform_safe[i]);
		

        int check_platform = round(sprite_x(platform_safe_offscreen[i]));
        int w = screen_width();
        //int h = screen_height();
        int random_x_coordinate_placement = rand() % 34;
        int random_y_coordinate_placement = rand() % 3;
        
        int crx[] = {-270, -262, -254, -246, -238, -230, -222, -214, -206, -198, -190, -182, -174, -166, -158, -150, -142, -134, -128, -120, -112, -104, -96, -88, -80, -72, -64, -56, -48, -40, -32, -24, -16, -8};
        int cry[]={16, 30, 44};

        int columns = crx[random_x_coordinate_placement];
        int rows = cry[random_y_coordinate_placement];

        sprite_turn_to(platform_safe_offscreen[i], 0.05, 0);
        sprite_step(platform_safe_offscreen[i]);
		sprite_draw(platform_safe_offscreen[i]);
        
        if(check_platform == w)
        {
            sprite_destroy(platform_safe_offscreen[i]);

            platform_safe_offscreen[i] = sprite_create(columns, rows, SAFE_BLOCK_WIDTH, SAFE_BLOCK_HEIGHT, safe_block_image);
            sprite_draw(platform_safe_offscreen[i]);
        }
    }
}

void draw_platforms2()
{
    for (int i = 0; i<10; i++)
    {
        sprite_turn_to(platform_forbidden[i], 0.05, 0);
        sprite_step(platform_forbidden[i]);
		sprite_draw(platform_forbidden[i]);

        int check_platform2 = round(sprite_x(platform_forbidden_offscreen[i]));
        int w = screen_width();
       // int h = screen_height();
        int random_x_coordinate_placement = rand() % 34;
        int random_y_coordinate_placement = rand() % 3;
        
        int crx[] = {-270, -262, -254, -246, -238, -230, -222, -214, -206, -198, -190, -182, -174, -166, -158, -150, -142, -134, -128, -120, -112, -104, -96, -88, -80, -72, -64, -56, -48, -40, -32, -24, -16, -8};
        int cry[]={16, 30, 44};

        int columns = crx[random_x_coordinate_placement];
        int rows = cry[random_y_coordinate_placement];

        sprite_turn_to(platform_forbidden_offscreen[i], 0.05, 0);
        sprite_step(platform_forbidden_offscreen[i]);
		sprite_draw(platform_forbidden_offscreen[i]);
        
        if(check_platform2 == w)
        {
            sprite_destroy(platform_forbidden_offscreen[i]);

            platform_forbidden_offscreen[i] = sprite_create(columns, rows, FORBIDDEN_BLOCK_WIDTH, FORBIDDEN_BLOCK_HEIGHT, forbidden_block_image);
            sprite_draw(platform_forbidden_offscreen[i]);
        }
    }
}


void draw_platforms3()
{
    for (int i = 0; i<80; i++)
    {
        sprite_turn_to(platform_safe_right[i], -0.05, 0);
        sprite_step(platform_safe_right[i]);
		sprite_draw(platform_safe_right[i]);

        int check_platform = round(sprite_x(platform_safe_offscreen_right[i]));
        //int w = screen_width();
        //int h = screen_height();
        int random_x_coordinate_placement = rand() % 34;
        int random_y_coordinate_placement = rand() % 3;
        
       int crx[] = {270, 278, 286, 294, 302, 310, 318, 326, 334, 342, 350, 358, 366, 374, 382, 390, 398, 406, 414, 422, 430, 438, 446, 454, 462, 470, 478, 486, 494, 502, 510, 518, 526, 534};
        int cry[]={23, 37, 51};

        int columns = crx[random_x_coordinate_placement];
        int rows = cry[random_y_coordinate_placement];

        sprite_turn_to(platform_safe_offscreen_right[i], -0.05, 0);
        sprite_step(platform_safe_offscreen_right[i]);
		sprite_draw(platform_safe_offscreen_right[i]);
        
        if(check_platform == -8)
        {
            sprite_destroy(platform_safe_offscreen_right[i]);

            platform_safe_offscreen_right[i] = sprite_create(columns, rows, SAFE_BLOCK_WIDTH, SAFE_BLOCK_HEIGHT, safe_block_image);
            sprite_draw(platform_safe_offscreen_right[i]);
        }
    }
}

void draw_platforms4()
{
    for (int i = 0; i<10; i++)
    {
        sprite_turn_to(platform_forbidden_right[i], -0.05, 0);
        sprite_step(platform_forbidden_right[i]);
		sprite_draw(platform_forbidden_right[i]);

        int check_platform2 = round(sprite_x(platform_forbidden_offscreen_right[i]));
        //int w = screen_width();
       // int h = screen_height();
        int random_x_coordinate_placement = rand() % 34;
        int random_y_coordinate_placement = rand() % 3;
        
        int crx[] = {270, 278, 286, 294, 302, 310, 318, 326, 334, 342, 350, 358, 366, 374, 382, 390, 398, 406, 414, 422, 430, 438, 446, 454, 462, 470, 478, 486, 494, 502, 510, 518, 526, 534};
        int cry[]={23, 37, 51};

        int columns = crx[random_x_coordinate_placement];
        int rows = cry[random_y_coordinate_placement];

        sprite_turn_to(platform_forbidden_offscreen_right[i], -0.05, 0);
        sprite_step(platform_forbidden_offscreen_right[i]);
		sprite_draw(platform_forbidden_offscreen_right[i]);
        
        if(check_platform2 == -8)
        {
            sprite_destroy(platform_forbidden_offscreen_right[i]);

            platform_forbidden_offscreen_right[i] = sprite_create(columns, rows, FORBIDDEN_BLOCK_WIDTH, FORBIDDEN_BLOCK_HEIGHT, forbidden_block_image);
            sprite_draw(platform_forbidden_offscreen_right[i]);
        }
    }
}

void draw_zombies(){
	
	sprite_draw(zombie1);
	
	
}

bool sprites_collide(sprite_id s1, sprite_id s2)
{
    if ((!s1->is_visible) || (!s2->is_visible))
    {
        return false;
    }

    int l1 = round(sprite_x(s1));
    int l2 = round(sprite_x(s2));
    int t1 = round(sprite_y(s1));
    int t2 = round(sprite_y(s2));
    int r1 = l1 + sprite_width(s1) - 1;
    int r2 = l2 + sprite_width(s2) - 1;
    int b1 = t1 + sprite_height(s1);
    int b2 = t2 + sprite_height(s2);

    if (l1 > r2)
        return false;
    if (l2 > r1)
        return false;
    if (t1 > b2)
        return false;
    if (t2 > b1)
        return false;

    return true;
}


void move_treasure(void) 
{
	if (pause_treasure == false) 
	{
		int w = screen_width();
		int trx = round(sprite_x(treasure));

		if (trx >= 0 && trx <= w - 1)
		{
			if (trx == w - 5)
			{
				sprite_turn_to(treasure, -0.5, 0);
			} 
			else if (trx == 1)
			{
				sprite_turn_to(treasure, +0.5, 0);
			}
		}
		sprite_step(treasure);
		sprite_draw(treasure);  
	}
}

void player_gravity(void)
{
    if (gravity_toggle == true) 
    {
        int plx = round(sprite_x(player_start));

        
        double pdx = sprite_dx(player_start);
        double pdy = sprite_dy(player_start);


        if ( plx >= 0 )
        {
            pdx = 0;
            pdy += 0.01;
        }
       
        sprite_turn_to(player_start, pdx, pdy);
        sprite_step(player_start);
		
    }
    
}

void gravity_for_food(void) 
{
	
	if (food_gravity == true) 
		{
		if (food_created == true) 
		{
		int food_x = round(sprite_x(added_food));

        
		double fdx = sprite_dx(added_food);
		double fdy = sprite_dy(added_food);


		if ( food_x >= 0 )
		{
			fdx = 0;
			fdy += 0.01;
		}
       
		sprite_turn_to(added_food, fdx, fdy);
		sprite_step(added_food);
		
		}
	}
}


void gravity_for_zombie(void) {
	
	if (zombie_gravity == true)
	{
		int zombie1_x = round(sprite_x(zombie1));
		double adx = sprite_dx(zombie1);
		double ady = sprite_dy(zombie1);

		if ( zombie1_x >= 0 )
		{
			adx = 0;
			ady += 0.01;
		}
		sprite_turn_to(zombie1, adx, ady);
		sprite_step(zombie1);
		
	}

	
}

void end_game()
{
	int msg_height = 3;
	int msg_width = strlen(game_over_message) / msg_height;
    game_over = true;
	clear_screen();
	
	// Display game over message
	sprite_id message_box = sprite_create(
    (screen_width() - msg_width) / 2,
    (screen_height() - msg_height) / 2, msg_width, msg_height, game_over_message );
    sprite_draw(message_box);
	draw_formatted( 105, 28, "%.2d:%.2d", minutes, seconds);
    draw_formatted( 104, 29, "%.2d", score);
    show_screen();
	
	
    int key = get_char();
    while(key != 'q' && key != 'r')
    {
        int key = get_char();
        if (key == 'q')
        {
            restart_game = false;
            return;
        }

        else if (key == 'r')
        {
            restart_game = true;
            return;
        }
    }
    
    timer_pause(1000);
}


void creating_food (void) {
	
	int player_x = round(sprite_x(player_start));
	int player_y = round(sprite_y(player_start));
	
	food_created = true;
	if (food > 0)
	{
		added_food = sprite_create(player_x, player_y, FOOD_WIDTH, FOOD_HEIGHT, food_image);
		food -= 1;
		sprite_draw(added_food);
	}
}

void move_player (int key) {
	
	//	(d) Get a character code from standard input without waiting.
		


	// moving the player
	int player_x = round(sprite_x(player_start));
	//int player_y = round(sprite_y(player_start));
	
	int w = screen_width(); 
	//Moving the player_image left, ensuring that it always remains within the screen.	
		
		if ( key == 'a' && player_x > 1) 
		{
		sprite_move(player_start, -1, 0);
		sprite_draw(player_start);
		}
	//(g) Moving the player_image right, ensuring that it always remains within the screen.
		if ( key == 'd' && player_x < w - PLAYER_WIDTH - 1)
		{ 
			sprite_move(player_start, +1, 0);
			sprite_draw(player_start);
		}		
		
		if (gravity_toggle == false)
		{
			//// creating food////////////////////
			if (key == 's')
			{
				creating_food();
			}
		}
}

void collision_with_respawn_block (void) {
	if (sprites_collide(player_start, respawn_block))
    {
        gravity_toggle = false;
    }
	if (sprites_collide(player_start, second_respawn_block))
    {
        gravity_toggle = false;
    }
	
}

void process_collision (void) {
	
	
	// process_collision
    //if (sprites_collide_any(player, ))
    player_gravity();
	gravity_for_food();
	gravity_for_zombie();
	
    // Collision check initial_block
    if (sprites_collide(player_start, starting_block))
    {
        gravity_toggle = false;
    }
	collision_with_respawn_block();

    // Collision 
    if (!sprites_collide(player_start, starting_block))
        {
            gravity_toggle = true;
        }
		
	
	if (food_created == true)
	{
		if (sprites_collide(added_food, starting_block))
		{
			food_gravity = false;
		}

		// Collision 
		if (!sprites_collide(added_food, starting_block))
        {
            food_gravity = true;
        }

	}
	
	 if (sprites_collide(zombie1, starting_block))
    {
        zombie_gravity = false;
    }

    // Collision 
    if (!sprites_collide(zombie1, starting_block))
        {
            zombie_gravity = true;
        }
	
}




void collision_with_platforms_for_zombie1(void) {
	
		for (int i = 0; i < 80; i++) {
		if (sprites_collide(zombie1, platform_safe[i]) || sprites_collide(zombie1, platform_safe_offscreen[i]))
			{
				zombie_gravity = false;
				sprite_turn_to(zombie1, -0.05, 0);
				sprite_step(zombie1);
				sprite_draw(zombie1);
			}
		if (sprites_collide(zombie1, platform_safe_right[i]) || sprites_collide(zombie1, platform_safe_offscreen_right[i]))
        {
            zombie_gravity = false;
            sprite_turn_to(zombie1, 0.05, 0);
            sprite_step(zombie1);
            sprite_draw(zombie1);
        }
		}
		
		for (int i = 0; i < 10; i++) {
		
		if (sprites_collide(zombie1, platform_forbidden[i]) || sprites_collide(zombie1, platform_forbidden_offscreen[i]))
        {
            zombie_gravity = false;
            sprite_turn_to(zombie1, -0.05, 0);
			sprite_step(zombie1);
			sprite_draw(zombie1);
          
        }
		
		if (sprites_collide(zombie1, platform_forbidden_right[i]) || sprites_collide(zombie1, platform_forbidden_offscreen_right[i]))
			{
				zombie_gravity = false;
				sprite_turn_to(zombie1, 0.05, 0);
				sprite_step(zombie1);
				sprite_draw(zombie1);
			}
			
		}


}	


void collision_with_safe_platform(void)
{
    int buttonPress = key_reader();
    for (int i = 0; i < 80; i++)
    {
        if (sprites_collide(player_start, platform_safe[i]) || sprites_collide(player_start, platform_safe_offscreen[i]))
        {
            gravity_toggle = false;
            score += 1;
            // sprite_set_image(player, player_image);
            sprite_turn_to(player_start, 0.05, 0);
            move_player(buttonPress);
            sprite_step(player_start);
            sprite_draw(player_start);
        }
		
		if (food_created == true)
		{
			if (sprites_collide(added_food, platform_safe[i]) || sprites_collide(added_food, platform_safe_offscreen[i]))
			{
				food_gravity = false;
				// sprite_set_image(player, player_image);
				sprite_turn_to(added_food, 0.05, 0);
				sprite_step(added_food);
				sprite_draw(added_food);
			}
		}

		
	}
}

void collision_with_safe_platform_right(void)
{
    int buttonPress = key_reader();
    for (int i = 0; i < 80; i++)
    {
        if (sprites_collide(player_start, platform_safe_right[i]) || sprites_collide(player_start, platform_safe_offscreen_right[i]))
        {
            gravity_toggle = false;
            score += 1;
            // sprite_set_image(player, player_image);
            sprite_turn_to(player_start, -0.05, 0);
            move_player(buttonPress);
            sprite_step(player_start);
            sprite_draw(player_start);
        }

        if (food_created == true)
		{
			if (sprites_collide(added_food, platform_safe_right[i]) || sprites_collide(added_food, platform_safe_offscreen_right[i]))
			{
				food_gravity = false;
				// sprite_set_image(player, player_image);
				sprite_turn_to(added_food, -0.05, 0);
				sprite_step(added_food);
				sprite_draw(added_food);
			}
		}	
    }
}

void random_respawn (void) {
	
	int dice_roll = rand() % 40;
		
		
		if (dice_roll <= 20 )  {
			player_start = sprite_create(179, 7, PLAYER_WIDTH, PLAYER_HEIGHT, player_image);     
		}
		else if (dice_roll <=30) {
			player_start = sprite_create(94, 7, PLAYER_WIDTH, PLAYER_HEIGHT, player_image);     
		}	
		else {
		player_start = sprite_create(5, 7, PLAYER_WIDTH, PLAYER_HEIGHT, player_image);     
		}
         
}

void collision_with_forbidden_platform()
{
    for (int i = 0; i < 10; i++)
    {
        if (sprites_collide(player_start, platform_forbidden[i]) || sprites_collide(player_start, platform_forbidden_offscreen[i]))
        {
            gravity_toggle = false;
            lives -= 1;
            sprite_destroy(player_start);
            random_respawn();
        }
    
	
	if (food_created == true)
	{
        if (sprites_collide(added_food, platform_forbidden[i]) || sprites_collide(added_food, platform_forbidden_offscreen[i]))
        {
            food_gravity = false;
            sprite_turn_to(added_food, -0.05, 0);
			sprite_step(added_food);
			sprite_draw(added_food);
          
        }
	}
    }
	
	 if (lives == 0)
    {
        end_game();
    }
}

void collision_with_forbidden_platform_right()
{
    for (int i = 0; i < 10; i++)
    {
        if (sprites_collide(player_start, platform_forbidden_right[i]) || sprites_collide(player_start, platform_forbidden_offscreen_right[i]))
        {
            gravity_toggle = false;
            lives -= 1;
            sprite_destroy(player_start);
            random_respawn();
        }
    
		if (food_created == true)
		{
			if (sprites_collide(added_food, platform_forbidden_right[i]) || sprites_collide(added_food, platform_forbidden_offscreen_right[i]))
			{
				food_gravity = false;
				sprite_turn_to(added_food, -0.05, 0);
				sprite_step(added_food);
				sprite_draw(added_food);
			}
		}
    }
	
	 if (lives == 0)
    {
        end_game();
    }
}

void collision_treasure (void) {
    // Collision treasure
    if (sprites_collide(player_start, treasure))
    {
        lives += 2;
        sprite_destroy(treasure);
        treasure = sprite_create(1, 55, TREASURE_WIDTH, TREASURE_HEIGHT, treasure_image);
        sprite_turn_to(treasure, 0.5, 0);
        sprite_destroy(player_start);
        player_start = sprite_create(5, 7, PLAYER_WIDTH, PLAYER_HEIGHT, player_image);
    }
}


void check_zombie_num (void) {
	
	if (zombies == 0)
		{
		setup_zombie1();
		zombies = 1;
		}
}

void zombie_interaction (void) {
	
	if (sprites_collide(player_start, zombie1))
	{
		lives -= 1;
		sprite_destroy(player_start);
		random_respawn();
	}
	
	if (food_created == true)
	{
		
		if (sprites_collide(zombie1, added_food))
		{
		sprite_destroy(added_food);
		food += 1;
		sprite_destroy(zombie1);
		zombies -= 1;
		food_created = false;
		check_zombie_num();
		
		}
	}
	
}

void zombie_death (void) {
	
	int h = screen_height();
	int w = screen_width();
	int zombie_x = round(sprite_x(zombie1));
    int zombie_y = round(sprite_y(zombie1));
// Death from fall
    if (zombie_x == w || zombie_y == h - 1 || zombie_x == -4)
    {
        zombies = zombies - 1;
        sprite_destroy(zombie1);
		
		check_zombie_num();
    }
	
	
}

void death_collision (void) {
	
	int h = screen_height();
	int w = screen_width();
	int player_start_x = round(sprite_x(player_start));
    int player_start_y = round(sprite_y(player_start));
// Death from fall
    if (player_start_x == w || player_start_y == h - 1 || player_start_x == -4)
    {
        lives = lives - 1;
        sprite_destroy(player_start);
		
		random_respawn();
    }
	
	if (food_created == true)
	{
		int added_food_x = round(sprite_x(added_food));
		int added_food_y = round(sprite_y(added_food));
		
		if (added_food_x == w || added_food_y == h - 1 || added_food_x == -4)
		{
			
			sprite_destroy(added_food);
			food = food + 1;
			food_created = false;
		
		}
		
	}

	
 // End game when out of lives
    if (lives == 0)
    {
        end_game();
    }

}

void restarting_game()
{
    clear_screen();
    game_over = false;
    lives = 10;
    minutes = 0;
    seconds = 0;
    milliseconds = 0;
    score = 0;
	food = 5;
    setup();
}


void process (void) {
	
	int buttonPress = key_reader();
	
	if (buttonPress == 'q')
    {
        end_game();
    } else if (buttonPress == 'r') {
        restarting_game();
    }
	
	draw_platforms1();
	draw_platforms2();
	draw_platforms3();
	draw_platforms4();
	draw_zombies();
	draw_all();
	move_treasure();
	move_player(buttonPress);
	
	
	process_collision();
	collision_with_safe_platform();
	collision_with_platforms_for_zombie1();
	collision_with_forbidden_platform();
	collision_with_forbidden_platform_right();
	collision_with_safe_platform_right();
	collision_treasure();
	death_collision();
	zombie_death();
	zombie_interaction();
}
	
	


int main( void ) {
	
	setup_screen();
	setup();
    show_screen();
	
	 while (!game_over)
    {
        game_timer();
        process();
        draw_platforms1();
        draw_platforms2();
		draw_platforms3();
		draw_platforms4();
		draw_zombies();
		
		if (game_over)
			
			{
				clear_screen();
				end_game();
				
				if (restart_game)
				{
					game_over = false;
					lives = 10;
					minutes = 0;
					seconds = 0;
					milliseconds = 0;
					score = 0;
					food = 5;
					setup();
					
				}
				
				
			}
        
        

        show_screen();
        timer_pause(DELAY);
    }

	
	return 0;
}