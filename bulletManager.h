#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#include "instance.h"  // Assuming Instance struct is defined in this header
#include "gameConstants.h"


struct Bullet {
    Instance instance;
    v2 speed;
    bool alignment;  // 1 for player, 0 for enemy
    bool exists;
};

class BulletManager {
public:
    BulletManager();
    void spawn_bullet(v2 pos, v2 dir, bool alignment, BulletType bullet_type);
    // Other methods, such as for updating and rendering bullets
	void draw_bullets();
	void animate_bullets(float time);
	void move_bullets();
    Bullet bullets[BULLET_BUFFER_MAX];
};

#endif // BULLET_MANAGER_H
