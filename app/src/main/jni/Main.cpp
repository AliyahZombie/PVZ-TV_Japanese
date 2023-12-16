#include <list>
#include <vector>
#include <cstring>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include "Includes/Utils.h"
#include "KittyMemory/MemoryPatch.h"

//Target lib here
#define targetLibName "libGameMain.so"

#include "HookGame/HookGame.h"
#include "HookGame/StepOne_Patch.h"


void *hack_thread(void *) {

    while (!isLibraryLoaded(targetLibName));
    StepOnePatchGame();
    GetFunctionAddr();
    CallHook();

    return NULL;
}


__attribute__((constructor))
void lib_main() {
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeIsSeedChoosing(JNIEnv *env, jclass clazz) {
    return isSeedChoosingNow;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeNowScene(JNIEnv *env, jclass clazz) {
    return mBoardBackground;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeGameState(JNIEnv *env, jclass clazz) {
    return gameState;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeIsMainMenu(JNIEnv *env, jclass clazz) {
    return isMainMenu;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeIsDaveTalking(JNIEnv *env, jclass clazz) {
    return !isCreditScreen && isCrazyDaveShowing;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeIsStartButtonEnabled(JNIEnv *env, jclass clazz) {
    return isStartButtonEnabled;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeIsDialogExist(JNIEnv *env, jclass clazz) {
    if ((gameIndex == 44 || gameIndex == 51) && isDaveStore && hasNewOptionsDialog &&
        dialogCount == 1) {
        return false;
    }
    return dialogCount > 0 || isAlmanacDialogExist;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeIsImitaterChooser(JNIEnv *env, jclass clazz) {
    return isImitaterChooser;
}


extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeIsVaseBreakerMode(JNIEnv *env, jclass clazz) {
    return isVaseBreakerMode;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeIsCobCannonSelected(JNIEnv *env,
                                                                       jclass clazz) {
    return isCobCannonSelected;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeCheckAndPickUpCobCannon(JNIEnv *env,
                                                                           jclass clazz, jint x,
                                                                           jint y) {

    col = x;
    row = y;
    requestValidCobCannonCheckByGrid = true;

}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeSetSeedBankPosition(JNIEnv *env,
                                                                       jclass clazz, jint x) {

    seekBankPositionToSet = x;
    requestSetSeedBankPosition = true;
    requestDrawShovelInCursor = false;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeGetSeekBankPosition(JNIEnv *env, jclass clazz) {
    return seekBankPositionOrigin;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeIsAwardScreen(JNIEnv *env, jclass clazz) {
    return isAwardScreen;
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeMaxPlants(JNIEnv *env, jclass clazz) {
    return maxPlantsNumInSeedBank;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeIsSeedChooserHas7Rows(JNIEnv *env,
                                                                         jclass clazz) {
    return isSeedChooseHas7Rows;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeIsShovelEnabled(JNIEnv *env,
                                                                   jclass clazz) {
    return isShovelEnabled;
}


extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeIsSurvivalRepick(JNIEnv *env, jclass clazz) {
    return isSurvivalRepick;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeSetGameState(JNIEnv *env, jclass clazz,
                                                                jint state) {
    stateToSet = state;
    requestSetGameState = true;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeIsChallengeScreen(JNIEnv *env, jclass clazz) {
    return isChallengeScreen;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeSetChallengeScreenScrollTarget(JNIEnv *env,
                                                                                  jclass clazz,
                                                                                  jint target,
                                                                                  jint offset) {
    scrollTarget = target;
    scrollOffset = offset;
    requestSetScrollTarget = true;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeIsStoreEnabled(JNIEnv *env, jclass clazz) {
    return isStoreEnabled;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeIsAlmanacEnabled(JNIEnv *env, jclass clazz) {
    return isAlmanacEnabled;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeIsImitaterEnabled(JNIEnv *env, jclass clazz) {
    return isImitaterEnabled;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeIsWhackAZombieLevel(JNIEnv *env, jclass clazz) {
    return isWhackAZombie;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeGetCursorPositionX(JNIEnv *env, jclass clazz) {
    return gridX;
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeGetCursorPositionY(JNIEnv *env, jclass clazz) {
    return gridY;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeDisableShop(JNIEnv *env, jclass clazz) {
    disableShop = true;

}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeEnableManualCollect(JNIEnv *env, jclass clazz) {
    enableManualCollect = true;
    if (IsPatched) {
        GamePatches.ManualCollection.Modify();
        return;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeSetStoreSelectedSlot(JNIEnv *env, jclass clazz,
                                                                        jint slot) {
    requestSetStoreSelectedSlot = true;
    slotToSet = slot;
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeIsStoreScreen(JNIEnv *env, jclass clazz) {
    return isDaveStore;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeGetSelectedStoreItem(JNIEnv *env, jclass clazz) {
    return selectedStoreItem;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeSetHeavyWeaponAngle(JNIEnv *env, jclass clazz,
                                                                       jint i) {

    float radian = i * M_PI / 180.0f;
    angle1 = -cos(radian);
    angle2 = sin(radian);
}



extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeSetZenGardenTool(JNIEnv *env, jclass clazz,
                                                                    jint position) {
    requestSetZenGardenTool = true;
    zenGardenToolPosition = position;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeCursorType(JNIEnv *env,
                                                              jclass clazz) {
    return requestDrawShovelInCursor ? 6 : cursorType;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeHasGoldenWaterCan(JNIEnv *env, jclass clazz) {
    return isGoldWateringCan;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeGameIndex(JNIEnv *env, jclass clazz) {
    return gameIndex;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeSetBoardPositionByXY(JNIEnv *env, jclass clazz,
                                                                        jfloat x, jfloat y) {
    requestSetBoardPositionByXY = true;
    boardPositionXToSet = x;
    boardPositionYToSet = y;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_isDaveTalkingInStore(JNIEnv *env,
                                                                  jclass clazz) {
    return isDaveTalkingInStore;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativePickUpShovel(JNIEnv *env, jclass clazz,
                                                                jboolean pickUp) {
    requestClearCursor = true;
    requestDrawShovelInCursor = pickUp;
    requestSetGameState = pickUp;
//    requestPlayFoley = true;
//    foleyToPlay = 75;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeShovelDown(JNIEnv *env, jclass clazz) {
    requestShovelDown = true;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeSetSeedBankPosition2P(JNIEnv *env, jclass clazz,
                                                                         jint x) {
    seekBankPositionToSet_2P = x;
    requestSetSeedBankPosition_2P = true;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeGetSeekBankPosition2P(JNIEnv *env,
                                                                         jclass clazz) {
    return seekBankPositionOrigin_2P;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeSetBoardPositionByXY2P(JNIEnv *env, jclass clazz,
                                                                          jfloat x, jfloat y) {
    requestSetBoardPositionByXY_2P = true;
    boardPositionXToSet_2P = x;
    boardPositionYToSet_2P = y;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeSetGameState2P(JNIEnv *env, jclass clazz,
                                                                  jint state) {
    stateToSet_2P = state;
    requestSetGameState_2P = true;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeGameState2P(JNIEnv *env, jclass clazz) {
    return gameState_2P;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_native1PButtonDown(JNIEnv *env, jclass clazz,
                                                                jint code) {
    requestButtonDown = true;
    buttonCode1 = code;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_native2PButtonDown(JNIEnv *env, jclass clazz,
                                                                jint code) {
    requestButtonDown_2P = true;
    buttonCode1_2P = code;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_native1PSelectPlantSeed(JNIEnv *env, jclass clazz,
                                                                     jint x, jint y) {
    requestVSPlantSelectSeed = true;
    plantX = x < 0 ? 0 : x;
    plantY = y < 0 ? 0 : y;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_native2PSelectZombieSeed(JNIEnv *env, jclass clazz,
                                                                      jint x, jint y) {
    requestVSZombieSelectSeed = true;
    zombieX = x < 0 ? 0 : x;
    zombieY = y < 0 ? 0 : y;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeVSSetupState(JNIEnv *env, jclass clazz) {
    return isInVSSetupMenu ? VSSetupState : -1;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeIsInVSResultMenu(JNIEnv *env, jclass clazz) {
    return isInVSResultsMenu;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativePlayFoley(JNIEnv *env, jclass clazz,
                                                             jint foley_type) {
    requestPlayFoley = true;
    foleyToPlay = foley_type;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeCheckAndPickUpCobCannonByXY(JNIEnv *env,
                                                                               jclass clazz,
                                                                               jfloat x,
                                                                               jfloat y) {
    cobToCheckX = x;
    cobToCheckY = y;
    requestValidCobCannonCheckByXY = true;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeIs2PChoosingSeed(JNIEnv *env, jclass clazz) {
    return gameIndex >= 79 && gameIndex <= 89 && seedChooseFinished1P;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_native2PChooseSeed(JNIEnv *env, jclass clazz, jint x,
                                                                jint y) {
    chooseSeed2PX = x < 0 ? 0 : x;
    chooseSeed2PY = y < 0 ? 0 : y;
    requestChooseSeed2P = true;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeEnableNewOptionsDialog(JNIEnv *env,
                                                                          jclass clazz) {
    enableNewOptionsDialog = true;
    if (IsPatched) {
        GamePatches.ShowNewOptions.Modify();
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativePickUpButter(JNIEnv *env, jclass clazz,
                                                                jboolean pick_up) {
    requestDrawButterInCursor = pick_up;
    if (pick_up) {
        requestSetGameState_2P = true;
        stateToSet_2P = 1;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeCheckAndPickUpCobCannonByXY2P(JNIEnv *env,
                                                                                 jclass clazz,
                                                                                 jfloat x,
                                                                                 jfloat y) {
    cobToCheckX_2P = x;
    cobToCheckY_2P = y;
    requestValidCobCannonCheckByXY_2P = true;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeIsCobCannonSelected2P(JNIEnv *env,
                                                                         jclass clazz) {
    return isCobCannonSelected_2P;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeButterPicked(JNIEnv *env, jclass clazz) {
    return requestDrawButterInCursor;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeGaoJiPause(JNIEnv *env, jclass clazz,
                                                              jboolean enable) {
    if (isMainMenu || isDaveStore || isInVSResultsMenu || isChallengeScreen) {
        return;
    }
    requestPause = enable;
    if (enable) {
        requestPlayPauseSound = true;
    } else {
        requestPlayResumeSound = true;
//        requestPlayFoley = true;
//        foleyToPlay = 31;
    }
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeIsGaoJiPaused(JNIEnv *env, jclass clazz) {
    return requestPause;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_checkAndSelectSeedPacket1P(JNIEnv *env, jclass clazz,
                                                                        jfloat x, jfloat y) {
    requestCheckAndSelectSeedPacket = true;
    checkSeedPacketX = x;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_checkAndSelectSeedPacket2P(JNIEnv *env, jclass clazz,
                                                                        jfloat x, jfloat y) {
    requestCheckAndSelectSeedPacket_2P = true;
    checkSeedPacketX_2P = x;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeHasConveyOrBelt(JNIEnv *env, jclass clazz) {
    return hasConveyOrBelt;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeClickSeedInBank(JNIEnv *env, jclass clazz,
                                                                   jint x) {
    requestClickSeedInBank = true;
    seedToClick = x;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeHideCoverLayer(JNIEnv *env, jclass clazz) {
    hideCoverLayer = true;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeShowCoolDown(JNIEnv *env, jclass clazz) {
    showCoolDown = true;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeCheckAndPickupUsefulSeedPacket(JNIEnv *env,
                                                                                  jclass clazz) {
    if (keyboardMode) {
        GamePatches.UsefulSeedPacketAutoPickupDisable.Modify();
    }
    keyboardMode = false;
    requestCheckAndSelectUsefulSeedPacket = true;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativePlantUsefulSeedPacket(JNIEnv *env,
                                                                         jclass clazz) {
    if (keyboardMode) {
        GamePatches.UsefulSeedPacketAutoPickupDisable.Modify();
    }
    keyboardMode = false;
    requestPlantUsefulSeedPacket = true;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_transmension_mobile_EnhanceActivity_nativeEnableNormalLevelMode(JNIEnv *env,
                                                                         jclass clazz) {
    normalLevel = true;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_android_support_Preferences_Changes(JNIEnv *env, jclass clazz, jobject con, jint featNum,
                                             jstring featName, jint value, jboolean boolean,
                                             jstring str) {

    switch (featNum) {
        case 1:
            infiniteSun = boolean;
            break;

        case 2:
            CoolDownSeedPacketButt = boolean;
            break;

        case 23:
            PassNowLevel = boolean;
            break;//过了这关

        case 50:
            RandomBulletBUTT = boolean;
            break;//随机子弹
        case 51:
            BulletSpinnerChosenNum = value - 1;
            break;

        case 52:
            ClearAllPlant = boolean;
            break;
        case 53:
            GetedChangeFormationID(value - 1);
            break;
        case 54:
            FormationDecideButt = boolean;
            break;
        case 55:
            IsOnlyPeaUseableButt = boolean;
            break;

        case 61:
            PumpkinWithLadder = boolean;
            break;

        case 62:
            LadderX = value;
            break;
        case 63:
            LadderY = value;
            break;

        case 64:
            DoneLadderBuild = boolean;
            break;
        case 65:
            ThePlantID = value >= 50 ? value : value - 1;
            break;
        case 66:
            ThePlantID = value;
            break;
        case 67:
            DonePlantBuild = boolean;
            break;
        case 68:
            BuildPlantX = value;
            break;
        case 69:
            BuildPlantY = value;
            break;
        case 70:
            BuildZombieCount = value;
            break;
        case 71:
            TheZombieBuildRow = value;
            break;
        case 72:
            DoneZombieBuild = boolean;
            Buildi = 0;
            break;
        case 73:
            TheZombieID = value - 1;
            break;
        case 74:
            UniformPlace = boolean;
            break;
        case 75:
            TheZombieID = value;
            break;
        case 81:
            drawDebugText = boolean;
            break;
        case 83:
            FreePlantAt = boolean;
            break;

        case 84:
            BanCobCannonBullet = boolean;
            break;
        case 85:
            BanStar = boolean;
            break;
        case 86:
            OnlyTouchFireWoodButt = boolean;
            break;
        case 87:
            ColdPeaCanPassFireWood = boolean;
            break;
        case 110:
            ZombieCanNotWon = boolean;
            break;
        case 111:
            BanDropCoin = boolean;
            break;
        case 112:
            DoCheatDialogButt = boolean;
            break;
        case 113:
            DoCheatCodeDialogButt = boolean;
            break;
        case 114:
            speedUpMode = value;
            break;
        case 115:
            mushroomsNoSleep = boolean;
            break;
        case 116:
            requestPause = boolean;
            break;
        case 117:
            zombieBloated = boolean;
            break;
        case 118:
            VSBackGround = value;
            break;
        case 119:
            transparentVase = boolean;
            break;
        case 120:
            projectilePierce = boolean;
            if (boolean) {
                GamePatches.ProjectilePierce.Modify();
            } else {
                GamePatches.ProjectilePierce.Restore();
            }
            break;
        case 121:
            showZombieHealth = boolean;
            break;
        case 122:
            showPlantHealth = boolean;
            break;
        case 123:
            boardEdgeAdjust = value * 10;
            break;
        case 124:
            drawDebugRects = boolean;
            break;
        case 125:
            targetWavesToJump = value;
            break;
        case 126:
            requestJumpSurvivalStage = boolean;
            break;
        default:
            break;

    }
}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_android_support_CkHomuraMenu_GetFeatureList(JNIEnv *env, jobject thiz) {
    jobjectArray ret;
    const char *features[] = {

            "Category_By-波奇酱",
            "Collapse_チート",//** 

            "1_CollapseAdd_Toggle_太陽は無限",
            "2_CollapseAdd_Toggle_ジャージなし",
            "83_CollapseAdd_Toggle_自由なプラント",
            "110_CollapseAdd_Toggle_失敗なし",
            "115_CollapseAdd_Toggle_シュルームが眠らない",
            "23_CollapseAdd_OnceCheckBox_レベルをクリア",

            "Collapse_アドバンスド",//**
            "81_CollapseAdd_Toggle_ゾンビDEBUG",
            "119_CollapseAdd_Toggle_ツボ透視",
            "121_CollapseAdd_Toggle_ゾンビのHPを表示",
            "122_CollapseAdd_Toggle_プラントのHPを表示",
            "116_CollapseAdd_Toggle_時間停止",
            "117_CollapseAdd_Toggle_普通のゾンビが必ずむせる",
            "124_CollapseAdd_Toggle_バリアを描画するには",
            "111_CollapseAdd_Toggle_太陽とコインの落下禁止",
            "112_CollapseAdd_OnceCheckBox_レベルスキッパー",
            "113_CollapseAdd_OnceCheckBox_チートコード",
            "114_CollapseAdd_Spinner_<font color='green'>スピードを上げる：_キャンセル,1.2倍,1.5倍,2倍,2.5倍,3倍,5倍,10倍",
            "118_CollapseAdd_Spinner_<font color='green'>バックグラウンドを変更：_キャンセル,昼,夜,プール,キリ,屋根 昼,屋根 夜",
            "123_CollapseAdd_Spinner_<font color='green'>失敗ラインの後退：_キャンセル,10,20,30,40,50,60,70,80",

            "Collapse_弾丸機能",
            "120_CollapseAdd_Toggle_直線弾丸フレーム損傷",
            "50_CollapseAdd_Toggle_ランダム弾丸",
            "51_CollapseAdd_Spinner_<font color='green'>ある弾丸を決定する：_キャンセル,マメ,凍ったマメ,キャベツ,メロン,胞子,凍ったメロン,火の玉,星,トゲ,バスケットボール,コーンの粒,トウモロコシ,バター,じこざんりゅう弾",
            "86_CollapseAdd_Toggle_トーチウッドモード(マメを通る)",
            "87_CollapseAdd_Toggle_凍った火の玉",
            "55_CollapseAdd_CheckBox_マメのみ",
            "84_CollapseAdd_CheckBox_トウモロコシ禁止",
            "85_CollapseAdd_CheckBox_星禁止",

            "Collapse_サバイバルエンドレス",
            "52_CollapseAdd_OnceCheckBox_クリアランス",
            "53_CollapseAdd_Spinner_<font color='green'>プールエンドレス：_キャンセル,[0]电波钟无炮,[1]最简无炮,[2]伪无伤无炮,[3]自然控丑无炮,[4]火焰无炮,[5]分裂火焰无炮,[6]后退无炮,[7]超前置无炮,[8]王子无炮,[9]机械钟无炮,[10]神之无炮,[11]石英钟无炮,[12]靠天无炮,[13]方块无神无炮,[14]56加速无神无炮,[15]压制一炮,[16]小二炮,[17]火焰二炮,[18]核武二炮,[19]分裂二炮,[20]方正二炮,[21]经典二炮,[22]冲关三炮,[23]太极四炮,[24]全金属四炮,[25]方块四炮,[26]青四炮,[27]水路无植物四炮,[28]方四炮,[29]神之四炮,[30]双核底线四炮,[31]经典四炮,[32]火焰四炮,[33]底线四炮,[34]传统四炮,[35]半场无植物五炮,[36]散炸五炮,[37]心五炮,[38]陆路无植物六炮,[39]水路无植物六炮,[40]青苔六炮,[41]禅房花木深,[42]神之六炮,[43]玉米六炮,[44]空炸六炮,[45]超后置六炮,[46]方六炮,[47]蝶韵,[48]一勺汤圆,[49]间隔无植物七炮,[50]玉兔茕茕,[51]无保护八炮,[52]树八炮,[53]全对称树八炮,[54]矩形八炮,[55]神之八炮,[56]阴阳八炮,[57]浮萍八炮,[58]后置八炮,[59]饲养海豚,[60]玉米八炮,[61]经典八炮,[62]花海八炮,[63]C2八炮,[64]分离八炮,[65]全对称八炮,[66]3C八炮,[67]灯台八炮,[68]⑨炮,[69]方块九炮,[70]C6i九炮,[71]心九炮,[72]轮炸九炮,[73]②炮,[74]六芒星十炮,[75]六边形十炮,[76]方块十炮,[77]斜方十炮,[78]简化十炮,[79]后置十炮,[80]经典十炮,[81]六线囚尸,[82]斜十炮,[83]魔方十炮,[84]戴夫的小汉堡,[85]鸡尾酒,[86]一勺汤圆十二炮,[87]玉壶春十二炮,[88]半场十二炮,[89]简化十二炮,[90]经典十二炮,[91]火焰十二炮,[92]冰雨十二炮·改,[93]冰雨十二炮•改改,[94]单紫卡十二炮,[95]神柱十二炮,[96神之十二炮],[97]水路无植物十二炮,[98]纯白悬空十二炮,[99]后花园十二炮,[100]玉米十二炮,[101]两路暴狂,[102]九列十二炮,[103]梯曾十二炮,[104]君海十二炮,[105]箜篌引,[106]梅花十三,[107]最后之作,[108]冰心灯,[109]太极十四炮,[110]真·四炮,[111]神棍十四炮,[112]神之十四炮,[113]穿越十四炮,[114]钻石十五炮,[115]神之十五炮,[116]真·二炮,[117]冰箱灯,[118]炮环十二花,[119]单冰十六炮,[120]对称十六炮,[121]神之十六炮,[122]裸奔十六炮,[123]双冰十六炮,[124]超前置十六炮,[125]火焰十六炮,[126]经典十六炮,[127]折线十六炮,[128]肺十八炮(极限),[129]纯十八炮,[130]真·十八炮,[131]冰魄十八炮,[132]尾炸十八炮,[133]经典十八炮,[134]纯二十炮,[135]空炸二十炮,[136]钉耙二十炮,[137]新二十炮,[138]无冰瓜二十炮,[139]绝望之路,[140]二十一炮,[141]新二十二炮,[142]二十二炮,[143]无冰瓜二十二炮,[144]九列二十二炮,[145]二十四炮,[146]垫材二十四炮,[147]胆守(极限)",
            "54_CollapseAdd_OnceCheckBox_ビルド",
            "CollapseAdd_RichTextView_<font color='yellow'>ハシゴ:",
            "61_CollapseAdd_Toggle_パンプキンハシゴ",
            "62_CollapseAdd_InputValue_X",
            "63_CollapseAdd_InputValue_Y",
            "64_CollapseAdd_OnceCheckBox_ハシゴを掛ける",
            "CollapseAdd_RichTextView_<font color='yellow'>エンドレススキップ:",
            "125_CollapseAdd_InputValue_目指しフラグ",
            "126_CollapseAdd_OnceCheckBox_スキップ",
            "CollapseAdd_RichTextView_<font color='yellow'>#少なくとも1つのフラグをクリアからスキップすることができます",

            "Collapse_カスタム",
            "CollapseAdd_RichTextView_<font color='yellow'>プラント:--->",
            "65_CollapseAdd_Spinner_<font color='green'>プラントを選択：_キャンセル,ピーシューター,サンフラワー,チェリーボム,ウォールナッツ,ポテトマイン,スノーピー,チャンパー,リピーター,パフシュルーム,サンシュルーム,フュームシュルーム,グレイブバスター,ヒプノシュルーム,スケアディシュルーム,アイスシュルーム,ドゥームシュルーム,リリーパッド,スクワッシュ,スリーピーター,タングルケルブ,ハラペーニョ,スパイクウィード,トーチウッド,トールナッツ,シーシュルーム,プランタン,サボテン,ブローバー,スプリットピー,スターフルーツ,パンプキン,マグネットシュルーム,キャベツパルト,フラワーポット,カーネルパルト,コーヒービーン,ガーリック,アンブレラリーフ,マリーゴールド,メロンパルト,ガトリングピー,ツインサンフラワー,グルームシュルーム,キャットテール,ウィンターメロン,ゴールドマグネット,スパイクロック,コップキャノン,イミテーター,バクハツ！ナッツ,ジャイアントウォールナッツ,シード,逆方向のリピーター",
            "66_CollapseAdd_InputValue_カスタムプラントID",
            "68_CollapseAdd_InputValue_X",
            "69_CollapseAdd_InputValue_Y",
            "67_CollapseAdd_OnceCheckBox_プラント",
            "CollapseAdd_RichTextView_<font color='yellow'>ゾンビ:--->",
            "73_CollapseAdd_Spinner_<font color='green'>ゾンビを選択：_キャンセル,ゾンビ,フラグゾンビ,コーンヘッドゾンビ,棒高跳びゾンビ,バケツヘッドゾンビ,ニューズペーパーゾンビ,スクリーンドアゾンビ,フットボールゾンビ,ダンシングゾンビ,バックダンサーゾンビ,浮き輪ゾンビ,シュノーケルゾンビ,ゾンボーニ,ボブスレーチームゾンビ,イルカに乗ったゾンビ,びっくり箱ゾンビ,バルーンゾンビ,ディガーゾンビ,ポーゴーゾンビ,イエティゾンビ,バンジーゾンビ,ハシゴゾンビ,カタパルトゾンビ,ガルガンチュア,インプ,ゾンボス博士,ゴミ箱ゾンビ,ピーシューターヘッドゾンビ,ウォールナッツヘッドゾンビ,ハラペーニョヘッドゾンビ,ガトリングピーヘッドゾンビ,スクワッシュヘッドゾンビ,トールナッツヘッドゾンビ,赤目ガルガンチュア",
            "75_CollapseAdd_InputValue_カスタムゾンビID",
            "70_CollapseAdd_InputValue_数量",
            "71_CollapseAdd_InputValue_行の数",
            "74_CollapseAdd_CheckBox_平均セット",
            "72_CollapseAdd_OnceCheckBox_セット",
            "CollapseAdd_RichTextView_<font color='yellow'>#ゲームをポーズしても続行できます",
    };

    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass("java/lang/String"),
                                env->NewStringUTF(""));

    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    return (ret);

}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_android_support_CkHomuraMenu_SettingsList(JNIEnv *env, jobject thiz) {
    jobjectArray ret;
    const char *features[] = {

            "Category_设置",
            "-1_Toggle_保存功能首选项", //-1 is checked on Preferences.java
            "Category_选择",
            "-6_Button_<font color='red'>退出设置</font>",
    };

    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass("java/lang/String"),
                                env->NewStringUTF(""));
    int i;
    for (i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    return (ret);

}
