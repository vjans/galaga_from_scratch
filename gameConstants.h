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
#define NO_ANIMATION -1

enum GameState{
    MAIN_MENU,
    PLAYING, // while inside of a level
    PLAYING_SHOP, // shopping interface between levels
    PAUSED,
    GAME_OVER
};

// Instance type for custom drawing and animations
enum DrawType {
	DEFAULT_PLAYER_DRAW,
	DEFAULT_ENEMY_DRAW,
	DEFAULT_BULLET_DRAW
};

enum BulletType{
	SINGLE_SHOT,
	DOUBLE_SHOT,
	SPREAD_SHOT,
	HEAT_SEEKING_SHOT
};

enum ModelType{
	ENEMY_DOUBLE_OCT,
	FLAT_OCTAHEDRON_STAR,
	ICOSAHEDRON,
	ITEM,
	OCTAHEDRON,
	PLAYER_MODEL1,
	TETRAHEDRON_MERGE,
	TETRAHEDRA_STACKED,
	TETRAHEDRON,
	TRIANGLE
};


enum AnimationType{
	NONE,
	WIGGLE,
	WIGGLE_FAST,
	ROTO_X,
	ROTO_Y,
	ROTO_Z,
	ROTO_X_FAST,
	ROTO_Y_FAST,
	ROTO_Z_FAST,
};

enum EnemyState{
	IDLE_ORIGIN,
	IDLE_SOMEWHERE,
	DEFAULT_SHOOTING,
	MOVE_ORIGIN,
	MOVE_PLAYER,
	WANDER,
	DODGE
};

enum EnemyAnimationState{
	IDLE,
	MOVING,
	ATTACKING
};

enum AIType{
	PASSIVE,
	WANDERING,
	HUNTER,
	PASSIVE_AGGRO
};

#endif
