#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H
#include "gameConstants.h"
#include "enemy.h"

void load_level(Enemy* enemies, BulletManager* bullet_manager, BGPlane* background,  int level_index);

#endif // LEVEL_LOADER_H
