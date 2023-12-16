//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_SEEDCHOOSERSCREEN_H
#define PVZ_TV_1_1_5_SEEDCHOOSERSCREEN_H


#include "../GlobalVariable.h"
#include "SeedChooserScreenInGameFunction.h"

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;

int (*old_SeedChooserScreen_RebuildHelpbar)(int *instance);

int SeedChooserScreen_RebuildHelpbar(int *seedChooserScreen) {
    //记录当前游戏状态
    isImitaterEnabled = SeedChooserScreen_HasPacket(seedChooserScreen, 48,
                                                    *((_BYTE *) seedChooserScreen + 3812)) != 0;
    int *lawnApp = (int *) *((_DWORD *) seedChooserScreen + 931);

    isStoreEnabled = LawnApp_CanShowStore(lawnApp);
    isAlmanacEnabled = LawnApp_CanShowAlmanac(lawnApp);
    isSurvivalRepick = CutScene_IsSurvivalRepick(
            (void *) (*(_DWORD *) (*((_DWORD *) seedChooserScreen + 932) + 592)));

    return old_SeedChooserScreen_RebuildHelpbar(seedChooserScreen);
}

int (*old_SeedChooserScreen_SeedChooserScreen)(int *instance, bool a2);

int SeedChooserScreen_SeedChooserScreen(int *seedChooserScreen, bool isZombieChooser) {
    //记录当前游戏状态，同时修复在没解锁商店图鉴时依然显示相应按钮的问题、对战选种子界面的按钮问题
    int returnValue = old_SeedChooserScreen_SeedChooserScreen(seedChooserScreen, isZombieChooser);
    int *lawnApp = (int *) *((_DWORD *) seedChooserScreen + 931);
    int nowGameIndex = *(lawnApp + LAWNAPP_GAMEINDEX_OFFSET);
    isStoreEnabled = LawnApp_CanShowStore(lawnApp);
    isAlmanacEnabled = LawnApp_CanShowAlmanac(lawnApp);
    //int mViewLawnButton = *((_DWORD *) seedChooserScreen + 958);
    int mStoreButton = *((_DWORD *) seedChooserScreen + 959);
    int mStartButton = *((_DWORD *) seedChooserScreen + 960);
    int mAlmanacButton = *((_DWORD *) seedChooserScreen + 961);

    if (nowGameIndex == 76) {//去除对战中的冗余按钮
        if (mStoreButton != NULL) {
            //mStoreButton.mDisabled = true;
            *(_BYTE *) (mStoreButton + 118) = true;
            //mStoreButton.mBtnNoDraw = true;
            *(_BYTE *) (mStoreButton + 773) = true;
        }
        if (mAlmanacButton != NULL) {
            //mAlmanacButton.mDisabled = true;
            *(_BYTE *) (mAlmanacButton + 118) = true;
            //mAlmanacButton.mBtnNoDraw = true;
            *(_BYTE *) (mAlmanacButton + 773) = true;
        }
        if (isZombieChooser && mStartButton != NULL) {
            //mStartButton.mDisabled = true;
            *(_BYTE *) (mStartButton + 118) = true;
            //mStartButton.mBtnNoDraw = true;
            *(_BYTE *) (mStartButton + 773) = true;
        }
    } else {
        if (mStoreButton != NULL) {
            if (!isStoreEnabled) {//去除在未解锁商店时商店按钮
                //mStoreButton.mDisabled = true;
                *(_BYTE *) (mStoreButton + 118) = true;
                //mStoreButton.mBtnNoDraw = true;
                *(_BYTE *) (mStoreButton + 773) = true;
            }
        }
        if (mAlmanacButton != NULL) {
            if (!isAlmanacEnabled) {//去除在未解锁图鉴时的图鉴按钮
                //mAlmanacButton.mDisabled = true;
                *(_BYTE *) (mAlmanacButton + 118) = true;
                //mAlmanacButton.mBtnNoDraw = true;
                *(_BYTE *) (mAlmanacButton + 773) = true;
            }
        }
    }

    return returnValue;
}

void SeedChooserScreen_ClickedSeedInBankCustom(int *a, int seedPosition, int playerIndex) {
    // 用于在选卡界面点击SeedBank中的已选卡片来退选该卡。
    // BUG：快速点击退选会导致SeedBank出现空位，所以我应该在这段代码里加入判断Flying状态的代码，以避免重复退选同一张卡片。
    char *v42 = (char *) a + 268;
    int v43 = 49;
    while (*((_DWORD *) v42 + 10) != 1 || *((_DWORD *) v42 + 11) != seedPosition || v42[60] ||
           *((_DWORD *) v42 + 8)) {
        --v43;
        v42 += 64;
        if (!v43)
            return;
    }
    SeedChooserScreen_ClickedSeedInBank(a, (int *) v42, playerIndex);
}

int (*old_SeedChooserScreen_Update)(int *a);

int SeedChooserScreen_Update(int *a) {
    //结盟中模仿者的选择BUG：在SeedChooserScreen::GameButtonDown()函数中，当总选取植物数大于等于最大可选植物数时就无法打开模仿者界面了。结盟模式中最大植物数为4单实际上应该判断8才对。
    //但暂时没办法修复此问题
    if (requestClickSeedInBank) {
        SeedChooserScreen_ClickedSeedInBankCustom(a, seedToClick, 0);
        requestClickSeedInBank = false;
    }
    int *lawnApp = *((int **) a + 931);
    int nowGameIndex = *(lawnApp + LAWNAPP_GAMEINDEX_OFFSET);
    if (nowGameIndex >= 79 && nowGameIndex <= 89) {
        seedChooseFinished1P = *(_DWORD *) ((int) a + 3744) == 4;
        seedChooseFinished2P = *(_DWORD *) ((int) a + 3748) == 4;
        if (requestChooseSeed2P) {
            for (int i = 0; i < 8; ++i) {
                SeedChooserScreen_GameButtonDown(a, 18, 1);
            }
            for (int i = 0; i < 6; ++i) {
                SeedChooserScreen_GameButtonDown(a, 16, 1);
            }
            for (int i = 0; i < chooseSeed2PY; ++i) {
                SeedChooserScreen_GameButtonDown(a, 17, 1);
            }
            for (int i = 0; i < chooseSeed2PX; ++i) {
                SeedChooserScreen_GameButtonDown(a, 19, 1);
            }
            SeedChooserScreen_GameButtonDown(a, 6, 1);
            requestChooseSeed2P = false;
        }
    }
//    __android_log_print(ANDROID_LOG_DEBUG, "TAG", "%d %d %d", *(_DWORD *) ((int) a + 3740), *(_DWORD *) ((int) a + 3744),
//                        *(_DWORD *) ((int) a + 3748));
    return old_SeedChooserScreen_Update(a);
}


int (*old_SeedChooserScreen_EnableStartButton)(void *instance, int isEnabled);

int SeedChooserScreen_EnableStartButton(void *instance, int isEnabled) {
    //记录当前游戏状态
    isStartButtonEnabled = isEnabled;
    isSeedChooseHas7Rows = SeedChooserScreen_Has7Rows(instance);
    return old_SeedChooserScreen_EnableStartButton(instance, isEnabled);
}

int (*old_SeedChooserScreen_OnStartButton)(int *a);

int SeedChooserScreen_OnStartButton(int *a) {
    int *lawnApp = (int *) *((_DWORD *) a + 931);
    int nowGameIndex = *(lawnApp + LAWNAPP_GAMEINDEX_OFFSET);
    if (nowGameIndex == 76) {
        //如果是对战模式，则直接关闭种子选择界面。用于修复对战模式选卡完毕后点击开始按钮导致的闪退
        return SeedChooserScreen_CloseSeedChooser(a);
    }
    return old_SeedChooserScreen_OnStartButton(a);
}

bool (*old_SeedChooserScreen_SeedNotAllowedToPick)(int *a, int theSeedType);

bool SeedChooserScreen_SeedNotAllowedToPick(int *a, int theSeedType) {
    //解除更多对战场地中的某些植物不能选取的问题，如泳池对战不能选荷叶，屋顶对战不能选花盆
    int *lawnApp = *((int **) a + 931);
    int nowGameIndex = *(lawnApp + LAWNAPP_GAMEINDEX_OFFSET);
    if (nowGameIndex == 76 && VSBackGround > 1) {
        //直接在其他对战场景解锁全部植物即可
        return false;
    }
    // 此处添加一些逻辑，就可以自定义Ban卡
    // 此处Ban卡仅对植物方生效，theSeedType取值范围是0~39。
    return old_SeedChooserScreen_SeedNotAllowedToPick(a, theSeedType);
}


#endif //PVZ_TV_1_1_5_SEEDCHOOSERSCREEN_H
