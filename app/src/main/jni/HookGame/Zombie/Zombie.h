//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_ZOMBIE_H
#define PVZ_TV_1_1_5_ZOMBIE_H

#include "../Board/BoardInGameFunction.h"
#include "ZombieInGameFunction.h"
#include "HookGame/LawnApp/LawnAppInGameFunction.h"
#include "HookGame/Reanimation/ReanimationInGameFunction.h"
#include "HookGame/GridItem/GridItemInGameFunction.h"

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;

bool zombieBloated = false;

void (*old_Zombie_Update)(int a1);

void Zombie_Update(int a1) {
    if (zombieBloated) {
        //如果开启了“普僵必噎死”
        if (*(_DWORD *) (a1 + 52) == 0)
            //如果是普僵，将噎死属性设置为true
            *(_BYTE *) (a1 + 360) = 1;
    }
    if (requestPause) {
        //如果开了高级暂停
        return;
    }
    return old_Zombie_Update(a1);
}

void (*old_Zombie_UpdateZombiePeaHead)(float *zombie);

void Zombie_UpdateZombiePeaHead(float *zombie) {
    //用于修复豌豆僵尸被魅惑后依然向左发射会伤害植物的子弹的BUG
    if (*((_BYTE *) zombie + 202) && !*((_BYTE *) zombie + 97)) {//判断是否hasHead，如果僵尸没头就不进if里面了
        int mPhaseCounter = *((_DWORD *) zombie + 30);
        int *lawnApp = *((int **) zombie + 4);
        if (mPhaseCounter == 35) {
            int *reanimation = (int *) LawnApp_ReanimationGet(lawnApp, *((_DWORD *) zombie + 85));
            Reanimation_PlayReanim(reanimation, "anim_shooting", 3, 20, 35.0f);
        } else if (mPhaseCounter <= 0) {
            int *reanimation = (int *) LawnApp_ReanimationGet(lawnApp, *((_DWORD *) zombie + 85));
            Reanimation_PlayReanim(reanimation, "anim_head_idle", 3, 20, 15.0f);
            LawnApp_PlayFoley((int) lawnApp, 3);
            int *reanimation1 = (int *) LawnApp_ReanimationGet(lawnApp, *((_DWORD *) zombie + 74));
            int index = Reanimation_FindTrackIndexById(reanimation1,
                                                       (char *) *ReanimTrackId_anim_head1_Addr);
            float aTransForm[18];
            ReanimatorTransform_ReanimatorTransform(aTransForm);
            Reanimation_GetCurrentTransform(reanimation1, index, aTransForm);
            float mPosX = zombie[15];
            float mPosY = zombie[16];
            float mAltitude = zombie[37];

            float aOriginX = mPosX + aTransForm[0] - 9.0f;
            float aOriginY = mPosY + aTransForm[1] + 6.0f - mAltitude;

            if (*((_BYTE *) zombie + 200)) {//如果是mMindControlled
                float mScaleZombie = *((float *) zombie + 75);
                aOriginX += 90.0f * mScaleZombie;
                int projectile = Board_AddProjectile(*((_DWORD *) zombie + 5),
                                                     (int) aOriginX,
                                                     (int) aOriginY,
                                                     *((_DWORD *) zombie + 12),
                                                     *((_DWORD *) zombie + 11), 0);
                *(_DWORD *) (projectile + 132) = 1; // mDamageFlags = 1;
            } else {
                float *projectile = (float *) Board_AddProjectile(*((_DWORD *) zombie + 5),
                                                                  (int) aOriginX,
                                                                  (int) aOriginY,
                                                                  *((_DWORD *) zombie + 12),
                                                                  *((_DWORD *) zombie + 11), 13);
                *((_DWORD *) projectile + 26) = 6;//ProjectileMotion = BackWards
            }
            *((_DWORD *) zombie + 30) = 150;
        }
    }
}

void (*old_Zombie_UpdateZombieGatlingHead)(float *zombie);

void Zombie_UpdateZombieGatlingHead(float *zombie) {
    //用于修复加特林僵尸被魅惑后依然向左发射会伤害植物的子弹的BUG
    if (*((_BYTE *) zombie + 202) && !*((_BYTE *) zombie + 97)) {//判断是否hasHead，如果僵尸没头就不进if里面了
        int mPhaseCounter = *((_DWORD *) zombie + 30);
        int *lawnApp = *((int **) zombie + 4);
        if (mPhaseCounter == 100) {
            int *reanimation = (int *) LawnApp_ReanimationGet(lawnApp, *((_DWORD *) zombie + 85));
            Reanimation_PlayReanim(reanimation, "anim_shooting", 3, 20, 38.0f);
        } else if (mPhaseCounter == 18 || mPhaseCounter == 36 || mPhaseCounter == 51 ||
                   mPhaseCounter == 69) {
            LawnApp_PlayFoley((int) lawnApp, 3);
            int *reanimation = (int *) LawnApp_ReanimationGet(lawnApp, *((_DWORD *) zombie + 74));
            int index = Reanimation_FindTrackIndexById(reanimation,
                                                       (char *) *ReanimTrackId_anim_head1_Addr);
            float aTransForm[18];
            ReanimatorTransform_ReanimatorTransform(aTransForm);
            Reanimation_GetCurrentTransform(reanimation, index, aTransForm);

            float mPosX = zombie[15];
            float mPosY = zombie[16];
            float mAltitude = zombie[37];
            float mScaleZombie = *((float *) zombie + 75);
            float aOriginX = mPosX - 9.0f;
            float aOriginY = mPosY + 13.0f - mAltitude;

            if (*((_BYTE *) zombie + 200)) {//如果是mMindControlled
                aOriginX += 90.0f * mScaleZombie;
                int projectile = Board_AddProjectile(*((_DWORD *) zombie + 5),
                                                     (int) aOriginX,
                                                     (int) aOriginY,
                                                     *((_DWORD *) zombie + 12),
                                                     *((_DWORD *) zombie + 11), 0);
                *(_DWORD *) (projectile + 132) = 1; // mDamageFlags = 1;
            } else {
                float *projectile = (float *) Board_AddProjectile(*((_DWORD *) zombie + 5),
                                                                  (int) aOriginX,
                                                                  (int) aOriginY,
                                                                  *((_DWORD *) zombie + 12),
                                                                  *((_DWORD *) zombie + 11), 13);
                *((_DWORD *) projectile + 26) = 6;//ProjectileMotion = BackWards
            }
        } else if (mPhaseCounter <= 0) {
            int *reanimation = (int *) LawnApp_ReanimationGet(lawnApp, *((_DWORD *) zombie + 85));
            Reanimation_PlayReanim(reanimation, "anim_head_idle", 3, 20, 15.0f);
            *((_DWORD *) zombie + 30) = 150;
        }
    }
}

void Zombie_BurnRow(unsigned int zombie, int theRow) {
    //辣椒僵尸被魅惑后的爆炸函数
    int theDamageRangeFlags = 127;
    int board = *(_DWORD *) (zombie + 20);
    unsigned int tmpZombie = NULL;
    while (Board_IterateZombies(board, &tmpZombie)) {
        if (tmpZombie != zombie && !*(_BYTE *) (tmpZombie + 252)) {
            int tmpZombieRow = *(_DWORD *) (tmpZombie + 44);
            int num = tmpZombieRow - theRow;
            int tmpZombieType = *(_DWORD *) (tmpZombieRow + 52);
            if (tmpZombieType == 25) {
                num = 0;
            }
            if (num == 0 && Zombie_EffectedByDamage(tmpZombie, theDamageRangeFlags)) {
                Zombie_RemoveColdEffects(tmpZombie);
                Zombie_ApplyBurn(tmpZombie);
            }
        }
    }

    unsigned int tmpGridItem = NULL;
    while (Board_IterateGridItems(board, &tmpGridItem)) {
        int tmpGridItemType = *(_DWORD *) (tmpGridItem + 24);
        int tmpGridItemGridY = *(_DWORD *) (tmpGridItem + 36);
        if (tmpGridItemGridY == theRow && tmpGridItemType == 3) {
            GridItem_GridItemDie(tmpGridItem);
        }
    }
}

void (*old_Zombie_UpdateZombieJalapenoHead)(float *zombie);

void Zombie_UpdateZombieJalapenoHead(float *zombie) {
    //修复辣椒僵尸被魅惑后爆炸依然伤害植物的BUG
    if (*((_BYTE *) zombie + 202) && !*((_DWORD *) zombie + 30)) {
        int lawnApp = *((_DWORD *) zombie + 4);
        int board = *((_DWORD *) zombie + 5);
        int mRow = *((_DWORD *) zombie + 11);
        LawnApp_PlayFoley(lawnApp, 56);
        LawnApp_PlayFoley(lawnApp, 65);
        Board_DoFwoosh(board, mRow);
        Board_ShakeBoard(board, 3, -4);
        if (*((_BYTE *) zombie + 200)) {
            Zombie_BurnRow((unsigned int) zombie, mRow);
            Zombie_DieNoLoot((int) zombie);
            return;
        }
        unsigned int plant = 0;
        while (Board_IteratePlants(board, &plant)) {
            if (mRow == *((_DWORD *) plant + 11) && !Plant_NotOnGround(plant)) {
                Plant_Die((void *) plant);
            }
        }
        Zombie_DieNoLoot((int) zombie);
    }
}

bool showZombieHealth = false;

void (*old_Zombie_Draw)(int *zombie, int *graphics);

void Zombie_Draw(int *zombie, int *graphics) {
    //根据玩家的“僵尸显血”功能是否开启，决定是否在游戏的原始old_Zombie_Draw函数执行完后额外绘制血量文本。
    old_Zombie_Draw(zombie, graphics);
    if (showZombieHealth) {//如果玩家开了"僵尸显血"
        int drawHeightOffset = 0;
        int holder[16];
        int mZombieType = *((_DWORD *) zombie + 13);
        int mBodyHealth = *((_DWORD *) zombie + 54);
        int mBodyMaxHealth = *((_DWORD *) zombie + 55);
        Sexy_StrFormat((int *) holder, "%d/%d", mBodyHealth, mBodyMaxHealth);
        Sexy_Graphics_SetColor(graphics, white);
        Sexy_Graphics_SetFont((int) graphics, (int *) *Sexy_FONT_DWARVENTODCRAFT18_Addr);
        if (mZombieType == 25) {
            // 如果是僵王,将血量绘制到僵王头顶。从而修复图鉴中僵王血量绘制位置不正确。
            // 此处仅在图鉴中生效,实战中僵王绘制不走Zombie_Draw()，走Zombie_DrawBossPart()
            *((float *) graphics + 2) = 780.0f;
            *((float *) graphics + 3) = 240.0f;
        }
        Sexy_Graphics_DrawString(graphics, (int) holder, 0, drawHeightOffset);
        drawHeightOffset += 20;
        int mHelmHealth = *((_DWORD *) zombie + 56);
        int mHelmMaxHealth = *((_DWORD *) zombie + 57);
        if (mHelmHealth > 0) {//如果有头盔，绘制头盔血量
            Sexy_StrFormat((int *) holder, "%d/%d", mHelmHealth, mHelmMaxHealth);
            Sexy_Graphics_SetColor(graphics, yellow);
            Sexy_Graphics_DrawString(graphics, (int) holder, 0, drawHeightOffset);
            drawHeightOffset += 20;
        }
        int mShieldHealth = *((_DWORD *) zombie + 59);
        int mShieldMaxHealth = *((_DWORD *) zombie + 60);
        if (mShieldHealth) {//如果有盾牌，绘制盾牌血量
            Sexy_StrFormat((int *) holder, "%d/%d", mShieldHealth, mShieldMaxHealth);
            Sexy_Graphics_SetColor(graphics, blue);
            Sexy_Graphics_DrawString(graphics, (int) holder, 0, drawHeightOffset);
        }
        Sexy_Graphics_SetFont((int) graphics, NULL);
    }
}

void (*old_Zombie_DrawBossPart)(int *a1, int *graphics, int theBossPart);

void Zombie_DrawBossPart(int *zombie, int *graphics, int theBossPart) {
    //根据玩家的“僵尸显血”功能是否开启，决定是否在游戏的原始old_Zombie_DrawBossPart函数执行完后额外绘制血量文本。
    old_Zombie_DrawBossPart(zombie, graphics, theBossPart);
    if (theBossPart == 3) {
        // 每次绘制Boss都会调用四次本函数，且theBossPart从0到3依次增加，代表绘制Boss的不同Part。
        // 我们只在theBossPart==3时(绘制最后一个部分时)绘制一次血量，免去每次都绘制。
        if (showZombieHealth) {//如果玩家开了"僵尸显血"
            int holder[16];
            int mBodyHealth = *((_DWORD *) zombie + 54);
            int mBodyMaxHealth = *((_DWORD *) zombie + 55);
            Sexy_StrFormat((int *) holder, "%d/%d", mBodyHealth, mBodyMaxHealth);
            Sexy_Graphics_SetColor(graphics, white);
            Sexy_Graphics_SetFont((int) graphics, (int *) *Sexy_FONT_DWARVENTODCRAFT18_Addr);
            int tmpTransX = *((float *) graphics + 2);
            int tmpTransY = *((float *) graphics + 3);
            *((float *) graphics + 2) = 800.0f;
            *((float *) graphics + 3) = 200.0f;
            Sexy_Graphics_DrawString(graphics, (int) holder, 0, 0);
            *((float *) graphics + 2) = tmpTransX;
            *((float *) graphics + 3) = tmpTransY;
            Sexy_Graphics_SetFont((int) graphics, NULL);
        }
    }
}

int Zombie_GetDancerFrame(int *zombie) {
    //修复女仆秘籍问题、修复舞王和舞者的跳舞时间不吃高级暂停也不吃倍速
    if (*((_DWORD *) zombie + 31) == -3 || Zombie_IsImmobilizied(zombie))
        return 0;
    int mZombiePhase = *((_DWORD *) zombie + 14);
    int num1 = mZombiePhase == 40 ? 10 : 20;
    int num2 = mZombiePhase == 40 ? 110 : 460;
//    return *(_DWORD *) (lawnApp + 2368) % num2 / num1;
    return *(_DWORD *) (*(_DWORD *) ((int) zombie + 20) + 22148) % num2 / num1;  // 修复女仆秘籍问题
    // 关键就是用mBoard.mMainCounter代替mApp.mAppCounter做计时
}

bool (*old_ZombieTypeCanGoInPool)(int zombieType);

bool ZombieTypeCanGoInPool(int zombieType) {
    //修复泳池对战的僵尸们走水路时不攻击植物
    if (gameIndex == 76 && (VSBackGround == 3 || VSBackGround == 4)) {
        return true;
    }
    return old_ZombieTypeCanGoInPool(zombieType);
}

void (*old_Zombie_RiseFromGrave)(int *zombie, int gridX, int gridY);

void Zombie_RiseFromGrave(int *zombie, int gridX, int gridY) {
    //修复对战切换场地为泳池后的闪退BUG。但是仅仅是修复闪退，泳池对战还谈不上能玩的程度
    if (gameIndex == 76) {
        if (VSBackGround == 3 || VSBackGround == 4) {
            if (gridY == 2 || gridY == 3) {
                int mZombieType = *((_DWORD *) zombie + 13);
//                if (old_ZombieTypeCanGoInPool(mZombieType)) {
                Zombie_DieNoLoot((int) zombie);
                Board_AddZombieInRow(*((int **) zombie + 5), mZombieType, gridY, 0,1);
                return;
//                }
            }
            int *board = *((int **) zombie + 5);
            int mBackgroundType = *((_DWORD *) board + 5528);
            *((_DWORD *) board + 5528) = 0;
            old_Zombie_RiseFromGrave(zombie, gridX, gridY);
            *((_DWORD *) board + 5528) = mBackgroundType;
            return;
        }
    }
    old_Zombie_RiseFromGrave(zombie, gridX, gridY);
}

int boardEdgeAdjust = 0;

void Zombie_CheckForBoardEdge(int *zombie) {
    //修复僵尸正常进家、支持调整僵尸进家线
    if (Zombie_IsWalkingBackwards(zombie) && *((float *) zombie + 15) > 850.0f) {
        Zombie_DieNoLoot((int) zombie);
        return;
    }
    int boardEdge;
    int mZombieType = zombie[13];
    if (mZombieType == 3 || mZombieType == 23 || mZombieType == 33) {
        //如果是撑杆、巨人、红眼巨人
        boardEdge = -100;
    } else if (mZombieType == 7 || mZombieType == 12 || mZombieType == 22) {
        //如果是橄榄球、冰车、篮球
        boardEdge = -125;
    } else if (mZombieType == 8 || mZombieType == 9 || mZombieType == 11) {
        //如果是舞王、伴舞、潜水
        boardEdge = -80;
    } else {
        //如果是除上述僵尸外的僵尸
        boardEdge = -50;
    }
    boardEdge -= boardEdgeAdjust;//支持任意调整进家线
    int mX = zombie[6];
    bool mHasHead = *((_BYTE *) zombie + 202);
    if (mX <= boardEdge && mHasHead) {
        if (LawnApp_IsIZombieLevel((int *) zombie[4])) {
            Zombie_DieNoLoot((int) zombie);
        } else {
            Board_ZombiesWon((int)*((int **) zombie + 5), (int) zombie);
        }
    }
    if (mX <= boardEdge + 70 && !mHasHead) {
        Zombie_TakeDamage(zombie, 1800, 9u);
    }
}

#endif //PVZ_TV_1_1_5_ZOMBIE_H
