//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_COIN_H
#define PVZ_TV_1_1_5_COIN_H


#include "../GlobalVariable.h"
#include "../StepOne_Patch.h"
#include "CoinInGameFunction.h"

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;

void (*old_Coin_GamepadCursorOver)(int *a, int a2);

void Coin_GamepadCursorOver(int *a, int a2) {

    //*((_DWORD *)a + 29) == 16 则意味着是砸罐子种子雨老虎机中的植物卡片

    if (!keyboardMode && *((_DWORD *) a + 29) == 16) return;
    old_Coin_GamepadCursorOver(a, a2);
}


bool BanDropCoin = false;

void (*old_Coin_Update)(int a1);

void Coin_Update(int a1) {
    int mCoinType = *((_DWORD *) a1 + 29);
    if (BanDropCoin && mCoinType <= 6) {
        //开启了"禁止掉落阳光金币"时
        Coin_Die(a1);
        return;
    }
    int *lawnApp = (int *) *((_DWORD *) a1 + 4);
    if (LawnApp_IsCoopMode(lawnApp)) {
        //固定地为结盟模式关闭自动拾取。
        *((int *) a1 + 25) = 0;
    }

    if (!enableManualCollect) {
        if (mCoinType == 30) {
            //如果没有关闭自动拾取，则为对战模式的僵尸方阳光也加入自动拾取。
            if (*((int *) a1 + 25) > 79 && !*((_BYTE *) a1 + 104)) {
                Coin_Collect(a1, 0);
            }
        }
    }
//    else {
//        //如果关闭了自动拾取，则重置Coin的存在时间计数器为0，从而不会触发自动拾取。
//        *((int *) a1 + 25) = 0;
//    }

    old_Coin_Update(a1);
    //解决种子雨老虎机砸罐子模式中，铲子经过植物卡片时植物卡片变灰的问题
    if (*((_BYTE *) a1 + 104)) {
        if (mCoinType == 16 && requestDrawShovelInCursor) {
            *((_BYTE *) a1 + 104) = false;
        }
    }
}

bool (*old_Coin_MouseHitTest)(int *coin, int a2, int a3, int **hitResult, int a5);

bool Coin_MouseHitTest(int *coin, int a2, int a3, int **hitResult, int a5) {
    //去除在玩家按A键时的阳光金币检测，以防止玩家种植、铲除、发射加农炮时的操作被阳光金币遮挡。
    int mCoinType = *((_DWORD *) coin + 29);
    if (mCoinType <= 6) return false;
    return old_Coin_MouseHitTest(coin, a2, a3, hitResult, a5);
}

#endif //PVZ_TV_1_1_5_COIN_H
