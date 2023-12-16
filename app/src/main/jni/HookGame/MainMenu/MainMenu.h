//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_MAINMENU_H
#define PVZ_TV_1_1_5_MAINMENU_H


#include "../GlobalVariable.h"
#include "MainMenuInGameFunction.h"

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;

void (*old_MainMenu_ButtonDepress)(int *mainMenu, int a2);

void MainMenu_ButtonDepress(int *instance, int mSelectedButton) {
    //解锁触控或确认键进入对战和结盟
    if (MainMenu_InTransition(instance))
        return old_MainMenu_ButtonDepress(instance, mSelectedButton);
    if (*((_BYTE *) instance + 260))
        return old_MainMenu_ButtonDepress(instance, mSelectedButton);
    if (instance[89] > 0)
        return old_MainMenu_ButtonDepress(instance, mSelectedButton);
    int lawnApp = instance[73];
    switch (mSelectedButton) {
        case 0:
        case 1:
            MainMenu_StartAdventureMode(instance);
            if (LawnPlayerInfo_GetFlag(
                    *(int **) (instance[73] + LAWNAPP_PLAYER_PURCHASEINFO_OFFSET), 4096) &&
                *(_DWORD *) (*(_DWORD *) (lawnApp + LAWNAPP_PLAYER_PURCHASEINFO_OFFSET) + 36) ==
                35) {
                instance[87] = 16;
                *((_BYTE *) instance + 371) = 1;
                (*(void (__fastcall **)(int *)) (*instance + 496))(instance);
            } else {
                instance[87] = 1;
                *(_DWORD *) (lawnApp + 4 * LAWNAPP_GAMEINDEX_OFFSET) = 0;
                (*(void (__fastcall **)(int *)) (*instance + 496))(instance);
            }
            return;
        case 10://如果按下了对战按钮
            if (*((_BYTE *) instance + 370)) {
                //如果没解锁结盟（冒险2-1解锁）
                LawnApp_LawnMessageBox(
                        (int *) lawnApp,
                        51,
                        "[MODE_LOCKED]",
                        "[VS_LOCKED_MESSAGE]",
                        "[DIALOG_BUTTON_OK]",
                        "",
                        3);
                return;
            }
            instance[87] = mSelectedButton;
            (*(int (__fastcall **)(int *)) (*instance + 496))(instance);
            return;
        case 11://如果按下了结盟按钮
            if (*((_BYTE *) instance + 367)) {
                //如果没解锁结盟（冒险2-1解锁）
                LawnApp_LawnMessageBox(
                        (int *) lawnApp,
                        51,
                        "[MODE_LOCKED]",
                        "[COOP_LOCKED_MESSAGE]",
                        "[DIALOG_BUTTON_OK]",
                        "",
                        3);
                return;
            }
            instance[87] = mSelectedButton;
            (*(int (__fastcall **)(int *)) (*instance + 496))(instance);
            return;
    }
    return old_MainMenu_ButtonDepress(instance, mSelectedButton);
}

void (*old_MainMenu_KeyDown)(int *mainMenu, int keyCode);

void MainMenu_KeyDown(int *mainMenu, int keyCode) {
    old_MainMenu_KeyDown(mainMenu, keyCode);
}

int (*old_MainMenu_Update)(void *instance);

int MainMenu_Update(void *instance) {
    //记录当前游戏状态
    isMainMenu = true;
    isDaveStore = false;
    //isSurvivalRepick = false;
    isCrazyDaveShowing = false;
    isSeedChoosingNow = false;
    isInVSSetupMenu = false;
    requestDrawShovelInCursor = false;
    requestDrawButterInCursor = false;
    return old_MainMenu_Update(instance);
}

#endif //PVZ_TV_1_1_5_MAINMENU_H
