//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_LAWNAPP_H
#define PVZ_TV_1_1_5_LAWNAPP_H

#include "../GlobalVariable.h"
#include "LawnAppInGameFunction.h"

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;

int (*old_LawnApp_DoBackToMain)(int *lawnApp);

int LawnApp_DoBackToMain(int *lawnApp) {
    LawnApp_ClearSecondPlayer(lawnApp);
    return old_LawnApp_DoBackToMain(lawnApp);
}

int (*old_LawnApp_DoNewOptions)(int *lawnApp, bool a2, unsigned int a3);

int LawnApp_DoNewOptions(int *lawnApp, bool a2, unsigned int a3) {
    hasNewOptionsDialog = true;
    return old_LawnApp_DoNewOptions(lawnApp, a2, a3);
}

int (*old_LawnApp_ShowAwardScreen)(int lawnApp, int a2);

int LawnApp_ShowAwardScreen(int lawnApp, int a2) {
    //记录当前游戏状态
    isAwardScreen = true;
    return old_LawnApp_ShowAwardScreen(lawnApp, a2);
}

int (*old_LawnApp_KillAwardScreen)(int lawnApp);

int LawnApp_KillAwardScreen(int lawnApp) {
    //记录当前游戏状态
    isAwardScreen = false;
    return old_LawnApp_KillAwardScreen(lawnApp);
}

void LawnApp_OnSessionTaskFailed(int *lawnApp) {
    //用此空函数替换游戏原有的LawnApp_OnSessionTaskFailed()函数，从而去除启动游戏时的“网络错误：255”弹窗
}

int (*old_LawnApp_GamepadToPlayerIndex)(int *lawnApp, unsigned int a2);

int LawnApp_GamepadToPlayerIndex(int *lawnApp, unsigned int a2) {
    int nowGameIndex = *(lawnApp + LAWNAPP_GAMEINDEX_OFFSET);
    //实现双人结盟中1P选卡选满后自动切换为2P选卡
    if (nowGameIndex >= 79 && nowGameIndex <= 89) {
        return seedChooseFinished1P;
    }
    return old_LawnApp_GamepadToPlayerIndex(lawnApp, a2);
}

//菜单DoCheatDialog
bool DoCheatDialogButt = false;
//菜单DoCheatCodeDialog
bool DoCheatCodeDialogButt = false;


//int LawnApp_IsTwoPlayerGame(int *a) {
//    int result; // r0
//
//    result = *((_DWORD *) a + 552);
//    if (result)
//        return *(_DWORD *) (*(_DWORD *) (result + 560) + 152) != -1 &&
//               *(_DWORD *) (*(_DWORD *) (result + 564) + 152) != -1;
//    return result;
//}

int (*old_LawnApp_UpDateApp)(int *lawnApp);

int LawnApp_UpDateApp(int *lawnApp) {
    gameIndex = *((int *) lawnApp + LAWNAPP_GAMEINDEX_OFFSET);
    //__android_log_print(ANDROID_LOG_DEBUG, "TAG", "%d", gameIndex);
    int mPlayerInfo = *((_DWORD *) lawnApp + LAWNAPP_PLAYERINFO_OFFSET);
    if (mPlayerInfo == 0) {
        isVaseBreakerMode = false;
        isWhackAZombie = false;
    } else {
        isVaseBreakerMode = LawnApp_IsScaryPotterLevel(lawnApp);
        isWhackAZombie = LawnApp_IsWhackAZombieLevel(lawnApp);
        *(_BYTE *) (mPlayerInfo + 1842) = true;//标记玩家已经通过道具教学
    }
    if (DoCheatDialogButt) {
        if (!isMainMenu && !isChallengeScreen) LawnApp_DoCheatDialog(lawnApp);
        DoCheatDialogButt = false;
    }
    if (DoCheatCodeDialogButt) {
        if (!isMainMenu && !isChallengeScreen) LawnApp_DoCheatCodeDialog(lawnApp);
        DoCheatCodeDialogButt = false;
    }
    if (requestPlayFoley) {
        LawnApp_PlayFoley((int) lawnApp, foleyToPlay);
        requestPlayFoley = false;
    }
    if (requestPlayPauseSound) {
        (*(void (__fastcall **)(_DWORD, int, int)) (*lawnApp + LAWNAPP_PLAYSOUND_OFFSET))(
                (int) lawnApp,
                *Sexy_SOUND_PAUSE_Addr,
                1);
        requestPlayPauseSound = false;
    }
    if (requestPlayResumeSound) {
        (*(void (__fastcall **)(_DWORD, int, int)) (*lawnApp + LAWNAPP_PLAYSOUND_OFFSET))(
                (int) lawnApp,
                *Sexy_SOUND_GRAVEBUTTON_Addr,
                1);
        requestPlayResumeSound = false;
    }

    return old_LawnApp_UpDateApp(lawnApp);
}

bool disableShop = false;

bool (*old_LawnApp_CanShopLevel)(int *lawnApp);

bool LawnApp_CanShopLevel(int *lawnApp) {
    //决定是否在当前关卡显示道具栏
    if (disableShop) return false;
    int nowGameIndex = *(lawnApp + LAWNAPP_GAMEINDEX_OFFSET);
    if (nowGameIndex >= 76 && nowGameIndex <= 89) return false;
    return old_LawnApp_CanShopLevel(lawnApp);
}

int (*old_LawnApp_ShowCreditScreen)(int lawnApp, bool isFromMainMenu);

int LawnApp_ShowCreditScreen(int lawnApp, bool isFromMainMenu) {
    //记录当前游戏状态
    isCreditScreen = true;
    if (isFromMainMenu) {
        //用于点击"制作人员"按钮播放MV
        LawnApp_KillMainMenu(lawnApp);
        LawnApp_KillNewOptionsDialog(lawnApp);
        (*(void (__fastcall **)(int, int)) (*(_DWORD *) lawnApp + 428))(lawnApp, 3);
    }
    return old_LawnApp_ShowCreditScreen(lawnApp, false);
}

void (*old_LawnApp_LoadLevelConfiguration)(int *lawnApp, int a2, int a3);

void LawnApp_LoadLevelConfiguration(int *lawnApp, int a2, int a3) {
    //如果开启了恢复出怪，则什么都不做，以做到禁止从levels.xml加载出怪。
    if (normalLevel) return;
    old_LawnApp_LoadLevelConfiguration(lawnApp, a2, a3);
}

void LawnApp_TryHelpTextScreen(int *lawnApp, int a2) {
    //空函数替换，去除初次进入对战结盟模式时的操作提示。
}

#endif //PVZ_TV_1_1_5_LAWNAPP_H
