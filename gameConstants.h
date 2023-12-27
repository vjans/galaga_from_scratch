#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#define FRIENDLY 1
#define HOSTILE 0
#define DRAW_MODE_LINE 1
#define DRAW_MODE_FILL 0
#define SCALE_MODE_FACTOR 0
#define SCALE_MODE_VECTOR 1
#define BULLET_BUFFER_MAX 10000
#define ENEMY_BUFFER_MAX 100
#define SCREEN_SIZE 768

enum GameState{
    MAIN_MENU,
    PLAYING, // while inside of a level
    PLAYING_SHOP, // shopping interface between levels
    PAUSED,
    GAME_OVER
};

// Instance type for custom drawing and animations
enum InstanceType {
	DEFAULT_PLAYER_INSTANCE,
	DEFAULT_ENEMY_INSTANCE,
	DEFAULT_BULLET_INSTANCE
};

enum BulletType{
	SINGLE_SHOT,
	DOUBLE_SHOT,
	SPREAD_SHOT,
	HEAT_SEEKING_SHOT
};

enum ModelType{
	ENEMY_DOUBLE_OCT,
	ICOSAHEDRON,
	OCTAHEDRON,
	ITEM,
	PLAYER_MODEL1,
	TRIANGLE
};

#endif
