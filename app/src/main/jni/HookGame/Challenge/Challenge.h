//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_CHALLENGE_H
#define PVZ_TV_1_1_5_CHALLENGE_H

#include "../Reanimation/ReanimationInGameFunction.h"
#include "../LawnApp/LawnAppInGameFunction.h"
#include "ChallengeInGameFunction.h"

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;

inline int Challenge_ScaryPotterCountSunInPot(int *a1, int *a2) {
    return *((_DWORD *) a2 + 24);
}

int targetWavesToJump = 1;
bool requestJumpSurvivalStage = false;

int *(*old_Challenge_Update)(int *a);

int *Challenge_Update(int *a) {
    if (requestJumpSurvivalStage) {
        //如果玩家按了无尽跳关
        int mSurvivalStage = *((_DWORD *) a + 33);
        if (mSurvivalStage > 0) {
            //需要玩家至少已完成一关，才能跳关。否则有BUG
            *((_DWORD *) a + 33) = targetWavesToJump;
        }
        requestJumpSurvivalStage = false;
    }
    if (requestPause) {
        return a;
    }
    return old_Challenge_Update(a);
}

void (*old_Challenge_Challenge)(int *a);

void Challenge_Challenge(int *a) {
    if (requestJumpSurvivalStage) {
        //如果玩家按了无尽跳关
        int mSurvivalStage = *((_DWORD *) a + 33);
        if (mSurvivalStage > 0) {
            //需要玩家至少已完成一关，才能跳关。否则有BUG
            *((_DWORD *) a + 33) = targetWavesToJump;
        }
        requestJumpSurvivalStage = false;
    }
    old_Challenge_Challenge(a);
}

//重型武器角度设定
float angle1 = 0;
float angle2 = 1;

int (*old_Challenge_HeavyWeaponFire)(int *challenge, float a2, float a3);

int Challenge_HeavyWeaponFire(int *challenge, float a2, float a3) {
    //设定重型武器的发射角度
    if (a2 == 0 && a3 == 1) {
        a2 = angle1;
        a3 = angle2;
//        float mHeavyWeaponPositionX = *((float *) challenge + 67);
//        float mHeavyWeaponPositionY = *((float *) challenge + 68);
//        LOGD("%f",*((float *) challenge + 69));
//        *((float *) challenge + 69) = acosf(a2) - 1.5708f;
    }
    return old_Challenge_HeavyWeaponFire(challenge, a2, a3);
}

void (*old_Challenge_HeavyWeaponUpdate)(int *challenge);

void Challenge_HeavyWeaponUpdate(int *challenge) {
    //设定重型武器的发射角度。未完成
//    LOGD("%f",*((float *) challenge + 69));
//    *((float *) challenge + 69) = acosf(angle1) - 1.5708f;
    old_Challenge_HeavyWeaponUpdate(challenge);
}

void (*old_Challenge_IZombieDrawPlant)(int *a, int *graphics, int *plant);

void Challenge_IZombieDrawPlant(int *a, int *graphics, int *plant) {
    //参照WP版源代码，在IZ模式绘制植物的函数开始前额外绘制纸板效果。其实就是向两个方向平移植物轮廓后画个灰色虚影
    Sexy_Graphics_SetDrawMode((int) graphics, 0);
    int reanimation = LawnApp_ReanimationTryToGet(*((_DWORD *) a + 4), *((_DWORD *) plant + 41));
    if (reanimation == NULL) {
        return;
    }
    float num = *((float *) graphics + 2);
    float num2 = *((float *) graphics + 3);
    Sexy_Graphics_SetColorizeImages((int) graphics, 1);
//    *((float *) graphics + 2) = (int) (num - 4);
//    *((float *) graphics + 3) = (int) (num2 - 4);
//    Sexy_Graphics_SetColor(graphics, black);
//    Reanimation_DrawRenderGroup(reanimation, graphics, 0);
    *((float *) graphics + 2) = (int) (num - 2);
    *((float *) graphics + 3) = (int) (num2 - 2);
    Sexy_Graphics_SetColor(graphics, black);
    Reanimation_DrawRenderGroup(reanimation, graphics, 0);
    *((float *) graphics + 2) = (int) (num + 2);
    *((float *) graphics + 3) = (int) (num2 + 2);
    Sexy_Graphics_SetColor(graphics, black);
    Reanimation_DrawRenderGroup(reanimation, graphics, 0);
    *((float *) graphics + 2) = (int) num;
    *((float *) graphics + 3) = (int) num2;
    old_Challenge_IZombieDrawPlant(a, graphics, plant);
}

bool Challenge_IZombieEatBrain(int *challenge, int *zombie) {
    //修复IZ脑子血量太高
    int *brain = (int *) Challenge_IZombieGetBrainTarget(challenge, zombie);
    if (brain == NULL)
        return false;
    Zombie_StartEating(zombie);
//    int mHealth = *((_DWORD *) brain + 10) - 1;
    int mHealth = *((_DWORD *) brain + 10) - 2;//一次吃掉脑子的两滴血
    *((_DWORD *) brain + 10) = mHealth;
    if (mHealth <= 0) {
        (*(void (__fastcall **)(_DWORD, int, int)) (**((_DWORD **) challenge + 4) + LAWNAPP_PLAYSOUND_OFFSET))(
                *((_DWORD *) challenge + 4),
                *Sexy_SOUND_GULP_Addr,
                1);
        GridItem_GridItemDie((unsigned int)brain);
        Challenge_IZombieScoreBrain(challenge, brain);
    }
    return true;
}

#endif //PVZ_TV_1_1_5_CHALLENGE_H
