//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_VSSETUPMENU_H
#define PVZ_TV_1_1_5_VSSETUPMENU_H

#include "../GlobalVariable.h"
#include "VSSetupMenuInGameFunction.h"
#include "../LawnApp/LawnApp.h"

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;

bool requestVSPlantSelectSeed = false;
bool requestVSZombieSelectSeed = false;
int plantX = 0;
int plantY = 0;
int zombieX = 0;
int zombieY = 0;



int VSSetupMenu_Update(int *a) {
    if (a) {
        //记录当前游戏状态
        isInVSSetupMenu = true;
        VSSetupState = *((_DWORD *) a + 74);
        if (VSSetupState == 1) {
            //自动分配阵营
            VSSetupMenu_GameButtonDown(a, 18, 0, 0);
            VSSetupMenu_GameButtonDown(a, 19, 1, 0);
            VSSetupMenu_GameButtonDown(a, 6, 0, 0);
            VSSetupMenu_GameButtonDown(a, 6, 1, 0);
        }
        if (requestVSPlantSelectSeed) {
            for (int i = 0; i < 7; ++i) {
                VSSetupMenu_GameButtonDown(a, 18, 0, 0);
            }
            for (int i = 0; i < 4; ++i) {
                VSSetupMenu_GameButtonDown(a, 16, 0, 0);
            }
            for (int i = 0; i < plantX; ++i) {
                VSSetupMenu_GameButtonDown(a, 19, 0, 0);
            }
            for (int i = 0; i < plantY; ++i) {
                VSSetupMenu_GameButtonDown(a, 17, 0, 0);
            }
            VSSetupMenu_GameButtonDown(a, 6, 0, 0);
            requestVSPlantSelectSeed = false;
        }
        if (requestVSZombieSelectSeed) {
            for (int i = 0; i < 4; ++i) {
                VSSetupMenu_GameButtonDown(a, 18, 1, 0);
            }
            for (int i = 0; i < 3; ++i) {
                VSSetupMenu_GameButtonDown(a, 16, 1, 0);
            }
            for (int i = 0; i < zombieX; ++i) {
                VSSetupMenu_GameButtonDown(a, 19, 1, 0);
            }
            for (int i = 0; i < zombieY; ++i) {
                VSSetupMenu_GameButtonDown(a, 17, 1, 0);
            }
            VSSetupMenu_GameButtonDown(a, 6, 1, 0);
            requestVSZombieSelectSeed = false;
        }
    }
    return old_VSSetupMenu_Update(a);
}


void (*old_VSSetupMenu_KeyDown)(int *a, int a2);

void VSSetupMenu_KeyDown(int *a, int a2) {
    //修复在对战的阵营选取界面无法按返回键退出的BUG。
    if (a2 == 27) {
        switch (VSSetupState) {
            case 1:
            case 2:
                LawnApp_DoBackToMain(*((int **) a + 73));
                return;
            case 3:
                LawnApp_DoNewOptions(*((int **) a + 73), 0, 0);
                return;
        }
    }
    return old_VSSetupMenu_KeyDown(a, a2);
}

#endif //PVZ_TV_1_1_5_VSSETUPMENU_H
