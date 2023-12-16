//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_PROJECTILE_H
#define PVZ_TV_1_1_5_PROJECTILE_H


#include "ProjectileInGameFunction.h"
#include "../Zombie/ZombieInGameFunction.h"
#include "../LawnApp/LawnAppInGameFunction.h"

#define randomInt(a, b) (rand()%(b-a+1)+a)//指定范围随机数产生
//--------------------------------------------------------------------------------------------------
//子弹分析,随机子弹实现
bool RandomBulletBUTT;
int BulletSpinnerChosenNum = -1;
bool IsOnlyPeaUseableButt;
bool BanCobCannonBullet, BanStar;
bool OnlyTouchFireWoodButt;

int (*old_ProjectileInitialize)(void *instance, int theX, int theY, int theRenderOrder, int theRow,
                                int theProjectileType);

int Projectile_ProjectileInitialize(void *instance, int theX, int theY, int theRenderOrder, int theRow,
                                    int theProjectileType) {

    if (!OnlyTouchFireWoodButt) {
        //僵尸子弹与加农炮子弹NULL
        if (theProjectileType == 11 || theProjectileType == 13) {
            return old_ProjectileInitialize(instance, theX, theY, theRenderOrder, theRow,
                                            theProjectileType);
        }
        if (theProjectileType == 7 && BanStar) {
            return old_ProjectileInitialize(instance, theX, theY, theRenderOrder, theRow,
                                            theProjectileType);
        }
        if (IsOnlyPeaUseableButt && theProjectileType != 0) {
            return old_ProjectileInitialize(instance, theX, theY, theRenderOrder, theRow,
                                            theProjectileType);
        }
        if (BulletSpinnerChosenNum != -1) {
            theProjectileType = BulletSpinnerChosenNum;
        }
        if (RandomBulletBUTT) {
            theProjectileType = randomInt(1, 12);
        }
        if (theProjectileType == 11 && BanCobCannonBullet) {
            theProjectileType = randomInt(1, 10);//同时降低好友玉米黄油的概率!!
        }
    }
    return old_ProjectileInitialize(instance, theX, theY, theRenderOrder, theRow,
                                    theProjectileType);
}



void (*old_ConvertToFireball)(int _this, int aGridX);

void Projectile_ConvertToFireball(int _this, int aGridX) {

    if (OnlyTouchFireWoodButt) {
        if (BulletSpinnerChosenNum != -1) {
            *((_DWORD *) _this + 27) = BulletSpinnerChosenNum;
            return;
        }
        if (RandomBulletBUTT) {
            *((_DWORD *) _this + 27) = randomInt(1, 12);
            return;
        }
    }
    return old_ConvertToFireball(_this, aGridX);
}

//此函数将完全取代游戏原函数!!!!
bool ColdPeaCanPassFireWood;

int Projectile_ConvertToPea(int _this, int aGridX) {

    _DWORD *v2; // r4
    v2 = (_DWORD *) _this;
    if (*(_DWORD *) (_this + 136) != aGridX) {
        Attachment_AttachmentDie(_this + 140);
        v2[34] = aGridX;
        v2[27] = 0;
        //---****---
        if (ColdPeaCanPassFireWood) {
            v2[27] = 1;//冰豌豆
        }
        //---****---
        _this = LawnApp_PlayFoley(v2[4], 3);
    }
    return _this;
}

void (*old_Projectile_Update)(int *a);

void Projectile_Update(int *a) {
    if (requestPause) {
        //如果开了高级暂停
        return;
    }
    return old_Projectile_Update(a);
}


void (*old_Projectile_DoImpact)(int *a1, int *a2);

void Projectile_DoImpact(int *a1, int *a2) {
    //负责 直线子弹帧伤
    old_Projectile_DoImpact(a1, a2);
    if (projectilePierce) {//如果玩家开启了“直线子弹帧伤”
        int mMotionType = *(_DWORD *) ((int) a1 + 104);
        if (mMotionType == 1) {//如果是抛物线轨迹，则让子弹正常消失
            Projectile_Die(a1);
            return;
        }
        int mProjectileType = *((_DWORD *) a1 + 27);
        if (mProjectileType == 13) { //如果是僵尸子弹ZombiePea，也让子弹消失
            Projectile_Die(a1);
        }
    }
}

int *Projectile_FindCollisionMindControlledTarget(int *a) {
    //豌豆僵尸的子弹专用的寻敌函数，寻找被魅惑的僵尸。
    unsigned int zombie = NULL;
    unsigned int zombie2 = NULL;
    int num = 0;
    int zombieRect[4];
    int projectileRect[4];
    Projectile_GetProjectileRect(projectileRect, a);
    while (Board_IterateZombies(*((_DWORD *) a + 5), &zombie)) {

//        if (!zombie.mDead && zombie.mRow == mRow && zombie.mMindControlled)
//        {
//            TRect zombieRect = zombie.GetZombieRect();
//            int rectOverlap = GameConstants.GetRectOverlap(projectileRect, zombieRect);
//            if (rectOverlap >= 0 && (zombie2 != NULL || zombie.mX > num))
//            {
//                zombie2 = zombie;
//                num = zombie.mX;
//            }
//        }

        if (!*((_BYTE *) zombie + 252) && *((_DWORD *) zombie + 11) == *((_DWORD *) a + 11) &&
            *((_BYTE *) zombie + 200)) {
            Zombie_GetZombieRect(zombieRect, (int *) zombie);
            int rectOverlap = GetRectOverlap(projectileRect, zombieRect);
            if (rectOverlap >= 0 && (zombie2 != NULL || *((_DWORD *) zombie + 6) > num)) {
                zombie2 = zombie;
                num = *((_DWORD *) zombie + 6);
            }
        }
    }
    return (int *) zombie2;
}

void (*old_Projectile_CheckForCollision)(int a);

void Projectile_CheckForCollision(int a) {
    //修复豌豆僵尸的子弹无法击中魅惑僵尸。
    int mProjectileType = *((_DWORD *) a + 27);
    if (mProjectileType == 13) {
        float mPosX = *(float *) (a + 64);
        int mWidth = *(int *) (a + 32);
        if (mPosX > 800.0f || mPosX + mWidth < 0.0f)
            return old_Projectile_CheckForCollision(a);

        int *zombie2 = Projectile_FindCollisionMindControlledTarget((int *) a);
        if (zombie2 != NULL) {
//            if (zombie2.mOnHighGround && CantHitHighGround(a))
//            {
//                return;
//            }
            Projectile_DoImpact((int *) a, zombie2);
        }
    }
    old_Projectile_CheckForCollision(a);
}
#endif //PVZ_TV_1_1_5_PROJECTILE_H
