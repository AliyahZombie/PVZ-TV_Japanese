//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_PLANT_H
#define PVZ_TV_1_1_5_PLANT_H

#include "../Graphics/GraphicsInGameFunction.h"
#include "../ChangeFormation.h"
#include "PlantInGameFunction.h"
#include "../Board/BoardInGameFunction.h"
#include "../SpecialConstraints.h"
#include "../MiscInGameFunction.h"

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;

bool showPlantHealth = false;

void (*old_Plant_Draw)(int *a1, int *graphics);

void Plant_Draw(int *a1, int *graphics) {
    //根据玩家的“植物显血”功能是否开启，决定是否在游戏的原始old_Plant_Draw函数执行完后额外绘制血量文本。
    old_Plant_Draw(a1, graphics);
    if (showPlantHealth) {//如果玩家开了 植物显血
        int holder[16];
        int mPlantHealth = *((_DWORD *) a1 + 20);
        int mPlantMaxHealth = *((_DWORD *) a1 + 21);
        Sexy_StrFormat((int *) holder, "%d/%d", mPlantHealth, mPlantMaxHealth);
        Sexy_Graphics_SetColor(graphics, white);
        Sexy_Graphics_SetFont((int) graphics, (int *) *Sexy_FONT_DWARVENTODCRAFT18_Addr);
        Sexy_Graphics_DrawString(graphics, (int) holder, 0, 0);
        Sexy_Graphics_SetFont((int) graphics, NULL);
    }
}


int (*old_Plant_GetRefreshTimeSeed)(int theSeedType, int theImitaterType);

int Plant_GetRefreshTimeSeed(int theSeedType, int theImitaterType) {
    if (CoolDownSeedPacketButt) {
        return 0;
    }
    return old_Plant_GetRefreshTimeSeed(theSeedType, theImitaterType);
}

void (*old_Plant_Update)(void *plant);

void Plant_Update(void *plant) {
    //用于修复植物受击闪光、生产发光、铲子下方植物发光
    int mHighLightCounter = *(_DWORD *) ((int) plant + 200);
    //铲子的发光计数是1000。这段代码用于在铲子移走之后的1ms内取消植物发光
    int cancelHighLightLimit = 999 - (speedUpMode > 0 ? 10 : 0);
    if (mHighLightCounter >= 900 && mHighLightCounter <= cancelHighLightLimit) {
        *(_DWORD *) ((int) plant + 204) = 0;
        *(_DWORD *) ((int) plant + 200) = 0;
    } else {
        *(_DWORD *) ((int) plant + 204) = mHighLightCounter > 30 ? 30 : mHighLightCounter;
    }

    if (ClearAllPlant) {
        //如果点击了“清空植物”
        Plant_Die(plant);
    }
    if (requestPause) {
        //如果开了高级暂停
        return;
    }
    return old_Plant_Update(plant);
}

bool mushroomsNoSleep = false;

int (*old_Plant_SetSleeping)(int *a, int a2);

int Plant_SetSleeping(int *a, int a2) {
    if (mushroomsNoSleep) {
        //如果开启"蘑菇免唤醒"
        a2 = false;
    }
    return old_Plant_SetSleeping(a, a2);
}

void (*old_Plant_UpdateReanimColor)(int *a);

void Plant_UpdateReanimColor(int *a) {
    //修复玩家选中但不拿起(gameState为1就是选中但不拿起，为7就是选中且拿起)某个紫卡植物时，相应的可升级绿卡植物也会闪烁的BUG。
    if (gameState != 7) {
        int seedType = *((_DWORD *) a + 13);
        if (seedType == 50) {
            return old_Plant_UpdateReanimColor(a);
        }
        *((_DWORD *) a + 13) = 0;
        old_Plant_UpdateReanimColor(a);
        *((_DWORD *) a + 13) = seedType;
        return;
    }
    old_Plant_UpdateReanimColor(a);
}

unsigned int Plant_FindTargetGridItem(int a1, int a2) {
    // 对战模式专用，植物索敌僵尸墓碑和靶子僵尸。
    // 原版函数BUG：植物还会索敌梯子和毁灭菇弹坑，故重写以修复BUG。
    unsigned int gridItem = NULL;
    unsigned int gridItem2 = NULL;
    int lastGridX = 0;
    if (*(_DWORD *) (*(_DWORD *) (a1 + 16) + 4 * LAWNAPP_GAMEINDEX_OFFSET) ==
        76) { //如果是对战模式(关卡ID为76)
        int mRow = *((_DWORD *) a1 + 11);
        int mPlantCol = *((_DWORD *) a1 + 14);
        int mSeedType = *(_DWORD *) (a1 + 52);
        while (Board_IterateGridItems(*(int *) (a1 + 20), &gridItem)) {//遍历场上的所有GridItem

            int mGridItemType = *((_DWORD *) gridItem + 6);
            if (mGridItemType != 1 && mGridItemType != 14) {
                //1是僵尸墓碑，14是靶子僵尸。这样就可以修复植物们攻击毁灭菇弹坑和梯子
                continue;
            }

            int mGridY = *((_DWORD *) gridItem + 9);
            if (mSeedType == 18 ? abs(mGridY - mRow) > 1 : mGridY != mRow) {
                //如果是三线射手，则索敌三行; 反之，索敌一行
                //注释掉此行，就会发现投手能够命中三格内的靶子僵尸了，但会导致很多其他BUG。尚不清楚原因。
                continue;
            }

            int mGridX = *((_DWORD *) gridItem + 8);
            if (gridItem2 == NULL || mGridX < lastGridX) {
                if ((mSeedType == 8 || mSeedType == 10) && mGridX - mPlantCol > 3) {
                    //如果是小/大喷菇，则索敌三格以内
                    continue;
                }
                gridItem2 = gridItem;
                lastGridX = mGridX;
            }
        }
    }
    return gridItem2;
}

#endif //PVZ_TV_1_1_5_PLANT_H
