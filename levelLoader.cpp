#inlcude "levelLoader.h"



void load_level(Enemy enemies[ENEMY_BUFFER_MAX], BulletManager* bullet_manager, BGPlane* background,  int level_index){
	
	
	   int encount = 10;
    for(int i = 0; i < ENEMY_BUFFER_MAX; i++) {
        if(!enemies[i]->exists) {
			
			
            enemies[i] = Enemy(&bullet_manager,&background, {((float)i / 5.0f) - 0.9f, 0.7f}, BIG_GUY);
            encount--;
        }
        if(encount == 0) break;
    }
    
}
