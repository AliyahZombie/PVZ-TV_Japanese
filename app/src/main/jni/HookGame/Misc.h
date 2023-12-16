//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_MISC_H
#define PVZ_TV_1_1_5_MISC_H

#include "GlobalVariable.h"
#include "LawnApp/LawnAppInGameFunction.h"
#include "MiscInGameFunction.h"

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;

bool isInVSResultsMenu = false;

int (*old_VSResultsMenu_Update)(int *a);

int VSResultsMenu_Update(int *a) {
    //记录当前游戏状态
    isInVSResultsMenu = true;
    return old_VSResultsMenu_Update(a);
}

int (*old_VSResultsMenu_OnExit)(int *a);

int VSResultsMenu_OnExit(int *a) {
    isInVSResultsMenu = false;
    return old_VSResultsMenu_OnExit(a);
}

void (*old_HelpOptionsDialog_ButtonDepress)(int *a, int a2);

void HelpOptionsDialog_ButtonDepress(int *a, int a2) {
    //修复在游戏战斗中打开新版暂停菜单时可以切换用户
    if (a2 == 1) {
        if (isMainMenu) LawnApp_DoUserDialog(*((int **) a + HELPOPTIONS_LAWNAPP_OFFSET));
        return;
    }
    return old_HelpOptionsDialog_ButtonDepress(a, a2);
}


int (*old_WaitForSecondPlayerDialog_WaitForSecondPlayerDialog)(int *a, int *a2);

int WaitForSecondPlayerDialog_WaitForSecondPlayerDialog(int *a, int *a2) {
    //自动跳过等待2P对话框
    int returnValue = old_WaitForSecondPlayerDialog_WaitForSecondPlayerDialog(a, a2);
    WaitForSecondPlayerDialog_GameButtonDown(a, 6, 1);
    WaitForSecondPlayerDialog_GameButtonDown(a, 6, 1);
    return returnValue;
}


void (*old_AlmanacDialog_SetPage)(int *a1, int targetPage);

void AlmanacDialog_SetPage(int *a1, int targetPage) {
    //修复点击气球僵尸进植物图鉴、点击介绍文字进植物图鉴
    if (targetPage != 0) {
        //前往非Index Page
        int mOpenPage = *((_DWORD *) a1 + ALMANAC_OPENPAGE_OFFSET);
        if (mOpenPage != 0) {
            //如果当前的Page不是Index Page，则不切换Page
            return;
        }
    }
    old_AlmanacDialog_SetPage(a1, targetPage);
}

void AlmanacDialog_MouseUp(int *a, int a2, int a3, int a4) {
    //空函数替换，修复点击图鉴Index界面中任何位置都会跳转植物图鉴的问题
}

void Sexy_ScrollbarWidget_MouseDown(int a, int a1, int a2, int a3, int a4) {
    //空函数替换，修复点击图鉴介绍文本滚动条时闪退的问题
}

void ZenGardenControls_Update(float *a1, float a2) {
    //用于触控拿起花园工具
    if (requestSetZenGardenTool) {
        requestSetZenGardenTool = false;
        if (zenGardenToolPosition < zenGardenObjectsCount) {
            *((_DWORD *) a1 + 66) = zenGardenObjects[zenGardenToolPosition] - 3;
        }
    }
    old_ZenGardenControls_Update(a1, a2);
}

int (*old_CutScene_Update)(void *instance);

int CutScene_Update(void *instance) {
    //记录当前游戏状态
    isSeedChoosingNow = *(bool *) ((uintptr_t) instance + 44);
    if (!isSeedChoosingNow) {
        isStartButtonEnabled = false;
        //isSurvivalRepick = false;
    }
    int v2 = *((int *) instance + 8);
    isCrazyDaveShowing =
            *(int *) (*(int *) instance + CUTSCENE_NOWGAMESTATE_OFFSET) == 2 && (v2 > 0) &&
            *((int *) instance + 2) < v2 + 3500;
    isShovelEnabled = *(_BYTE *) (*((_DWORD *) instance + 1) + 22289);
    isInShovelTutorial =
            (unsigned int) (*(_DWORD *) (*((_DWORD *) instance + 1) + 22176) - 15) <= 2;
    return old_CutScene_Update(instance);
}

int (*old_SexyDialog_AddedToManager)(void *instance, void *instance1);

int SexyDialog_AddedToManager(void *instance, void *instance1) {
    //记录当前游戏状态
    dialogCount++;
    return old_SexyDialog_AddedToManager(instance, instance1);
}

int (*old_SexyDialog_RemovedFromManager)(void *instance, void *instance1);

int SexyDialog_RemovedFromManager(void *instance, void *instance1) {
    //记录当前游戏状态
    dialogCount--;
    isImitaterChooser = false;
    if (dialogCount <= 0) hasNewOptionsDialog = false;
    return old_SexyDialog_RemovedFromManager(instance, instance1);
}

int (*old_ImitaterDialog_ImitaterDialog)(void *instance, int a2);

int ImitaterDialog_ImitaterDialog(void *instance, int a2) {
    //记录当前游戏状态
    isImitaterChooser = true;
    return old_ImitaterDialog_ImitaterDialog(instance, a2);
}

int (*old_AlmanacDialog_AddedToManager)(void *instance, int a2);

int AlmanacDialog_AddedToManager(int *a, int a2) {
    //记录当前游戏状态
    isAlmanacDialogExist = true;
    return old_AlmanacDialog_AddedToManager(a, a2);
}

int (*old_AlmanacDialog_RemovedFromManager)(void *instance, int a2);

int AlmanacDialog_RemovedFromManager(int *a, int a2) {
    //记录当前游戏状态
    isAlmanacDialogExist = false;
    dialogCount++;
    return old_AlmanacDialog_RemovedFromManager(a, a2);

}

int (*old_StoreScreen_AddedToManager)(int *a, int a2);

int StoreScreen_AddedToManager(int *a, int a2) {
    //记录当前游戏状态
    isDaveStore = true;
    isMainMenu = false;
    isChallengeScreen = false;
    return old_StoreScreen_AddedToManager(a, a2);
}

int (*old_StoreScreen_RemovedFromManager)(int *a, int a2);

int StoreScreen_RemovedFromManager(int *a, int a2) {
    //记录当前游戏状态
    isDaveStore = false;
    return old_StoreScreen_RemovedFromManager(a, a2);
}

int (*old_GamepadControls_ButtonDownFireCobcannonTest)(int *instance);

int GamepadControls_ButtonDownFireCobcannonTest(int *instance) {
    //解除加农炮选取半秒后才能发射的限制
    int *v5 = (int *) *((int *) instance + 14);
    *((int *) v5 + 5661) = 0;
    return old_GamepadControls_ButtonDownFireCobcannonTest(instance);
}

void (*old_SeedBank_Draw)(int *instance, float a2);

void SeedBank_Draw(int *instance, float a2) {
    //记录当前游戏状态
    maxPlantsNumInSeedBank = *((_DWORD *) instance + 13);
    return old_SeedBank_Draw(instance, a2);
}

int totalGamesInThisPage = 0;
int gamesMin = 0;
int gamesMax = 0;

int (*old_ChallengeScreen_AddedToManager)(int *a, int a2);

int ChallengeScreen_AddedToManager(int *a, int a2) {
    //记录当前游戏状态
    isChallengeScreen = true;
    isMainMenu = false;
    isAwardScreen = false;
    isSeedChoosingNow = false;
    isDaveStore = false;
    totalGamesInThisPage = a[376];
    gamesMin = a[378];
    gamesMax = gamesMin + totalGamesInThisPage;
    return old_ChallengeScreen_AddedToManager(a, a2);
}

int (*old_ChallengeScreen_Update)(int *a);

int ChallengeScreen_Update(int *a) {
    //记录当前游戏状态
    isChallengeScreen = true;
    requestDrawShovelInCursor = false;
    if (requestSetScrollTarget) {
        //设置当前已选关卡的位置。效果挺烂的，但是暂时没好办法。
        if (totalGamesInThisPage > 0) {
            char *v7 = (char *) a + 748 + 4 * (a[186] + scrollTarget);
            int v8 = *((_DWORD *) v7 + 1);
            v8 = v8 >= gamesMax ? gamesMax : v8 <= gamesMin ? gamesMin : v8;
            a[378] = (v8 + scrollOffset) <= gamesMax ? v8 + scrollOffset : 88;
        }
        ChallengeScreen_SetScrollTarget(a, a[186] + scrollTarget);
        requestSetScrollTarget = false;
    }
    return old_ChallengeScreen_Update(a);
}

int (*old_ChallengeScreen_RemovedFromManager)(int *a, int a2);

int ChallengeScreen_RemovedFromManager(int *a, int a2) {
    //记录当前游戏状态
    isChallengeScreen = false;
    return old_ChallengeScreen_RemovedFromManager(a, a2);
}

int (*old_CreditScreen_RemovedFromManager)(int *a, int a2);

int CreditScreen_RemovedFromManager(int *a, int a2) {
    //记录当前游戏状态
    isCreditScreen = false;
    return old_CreditScreen_RemovedFromManager(a, a2);
}

int (*old_StoreScreen_Update)(int a);

int StoreScreen_Update(int a) {
    //记录当前游戏状态
    isDaveStore = true;
    isMainMenu = false;
    isChallengeScreen = false;
    selectedStoreItem = *((_DWORD *) a + 194);
    isDaveTalkingInStore = *(_BYTE *) (a + 756);
    if (requestSetStoreSelectedSlot) {
        //选取某个商品
        requestSetStoreSelectedSlot = false;
        StoreScreen_SetSelectedSlot(a, slotToSet);
    }
    return old_StoreScreen_Update(a);
}

int *(*ZenGarden_GetStinky)(int **zenGarden);

bool (*ZenGarden_IsStinkyHighOnChocolate)(int *zenGarden);

//void (*old_ZenGarden_MouseDownWithFeedingTool)(int **a1, int a2, int a3, int toolType, int a5);

//void ZenGarden_MouseDownWithFeedingTool(int **a1, int a2, int a3, int toolType, int a5) {
//    //修复Stinky在喂巧克力后还可以继续喂巧克力
//    if (toolType == 13 && *(int *) (*((_DWORD *) *a1 + LAWNAPP_PLAYERINFO_OFFSET) + 548) > 1000) {
//        int *mStinky = ZenGarden_GetStinky(a1);
//        if (mStinky != NULL) {
//            float mStinkyX = *((float *) mStinky + 13);
//            float mStinkyY = *((float *) mStinky + 14);
//            int mStinkyGridX = Board_PixelToGridX(a1[1], (int) mStinkyX, (int) mStinkyY);
//            int mStinkyGridY = Board_PixelToGridY(a1[1], (int) mStinkyX, (int) mStinkyY);
//            int mCursorX = Board_PixelToGridX(a1[1], a2, a3);
//            int mCursorY = Board_PixelToGridY(a1[1], a2, a3);
//            bool isStinkyHighOnChocolate = ZenGarden_IsStinkyHighOnChocolate((int *) a1);
//            if (isStinkyHighOnChocolate && mStinkyGridX == mCursorX && mStinkyGridY == mCursorY) {
//                return;
//            }
//        }
//    }
//    old_ZenGarden_MouseDownWithFeedingTool(a1, a2, a3, toolType, a5);
//}

#endif //PVZ_TV_1_1_5_MISC_H
