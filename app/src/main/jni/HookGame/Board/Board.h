//
// Created by Administrator on 2023/10/22.
//

#ifndef PVZ_TV_1_1_5_BOARD_H
#define PVZ_TV_1_1_5_BOARD_H

#include "../GlobalVariable.h"
#include "BoardInGameFunction.h"
#include "../Plant/PlantInGameFunction.h"
#include "../Graphics/GraphicsInGameFunction.h"
#include "../Plant/Plant.h"
#include "../Zombie/Zombie.h"
#include "../Coin/Coin.h"
#include "../Challenge/Challenge.h"
#include "../Projectile/Projectile.h"
#include "../StepOne_Patch.h"
#include "../LawnApp/LawnApp.h"
#include "../GamepadControls/GamepadControlsInGameFunction.h"
#include "../GamepadControls/GamepadControls.h"

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;

void Board_SetGrids(int *board) {
    //从IDA Pro直接复制的代码，更换场地时需要。猜测是用于初始化每一个格子的类型。
    unsigned int v7; // lr
    int i; // r1
    int *v9; // r3
    int v10; // r4
    int v11; // r2

    v7 = -4;
    for (i = 0; i != 216; i += 24) {
        v9 = board;
        v10 = 0;
        do {
            while (1) {
                v11 = *((_DWORD *) v9 + 443);
                if (v11)
                    break;
                *(_DWORD *) ((char *) v9 + i + 604) = 2;
                LABEL_17:
                ++v10;
                v9 = (int *) ((char *) v9 + 4);
                if (v10 == 6)
                    goto LABEL_27;
            }
            if (v11 == 2) {
                *(_DWORD *) ((char *) v9 + i + 604) = 3;
                goto LABEL_17;
            }
            if (v11 != 3)
                goto LABEL_17;
            ++v10;
            v9 = (int *) ((char *) v9 + 4);
            if (v7 <= 4)
                *(_DWORD *) ((char *) v9 + i + 604) = 4;
        } while (v10 != 6);
        LABEL_27:
        ++v7;
    }
}

void Board_ShovelDown(int *board) {
    // 用于铲掉光标正下方的植物。
    if (isInShovelTutorial) {
        //如果正在铲子教学中(即冒险1-5的保龄球的开场前，戴夫要求你铲掉三个豌豆的这段时间),则发送铲除键来铲除。
        GamepadControls_OnKeyDown(*((_DWORD *) board + 140), 49, 1112);
        Board_ClearCursor(board, 0);
        Board_RefreshSeedPacketFromCursor(board, 0);
        requestDrawShovelInCursor = false;
        return;
    }
    // 下方就是自己写的铲除逻辑喽。
    int plantUnderShovel = Board_ToolHitTest(board, boardPositionXToSet, boardPositionYToSet);
    if (plantUnderShovel != NULL) {
        LawnApp_PlayFoley((int) *((int **) board + 69), 8); // 播放铲除音效
        Plant_Die((int *) plantUnderShovel);// 让被铲的植物趋势

        int plantType = *((_DWORD *) plantUnderShovel + 13);
        int plantGridX = *((_DWORD *) plantUnderShovel + 14);
        int plantGridY = *((_DWORD *) plantUnderShovel + 11);
        if (plantType == 43 && Board_GetTopPlantAt(board, plantGridX, plantGridY, 8)) {
            // 如果铲的是南瓜套内的猫尾草,则再在原地种植一个荷叶
            Board_NewPlant(board, plantGridX, plantGridY, 16, -1, -1);
        }
    }
    Board_ClearCursor(board, 0);
    Board_RefreshSeedPacketFromCursor(board, 0);
    requestDrawShovelInCursor = false;
}

void (*old_Board_UpdateGame)(int *a);

void Board_UpdateGame(int *a) {
    if (requestPause) {
        --*((_DWORD *) a + 5537);
        int mIceTrapCounter = *((_DWORD *) a + 5582);
        if (mIceTrapCounter > 0) {
            ++*((_DWORD *) a + 5582);
        }
        int mFogBlownCountDown = *((_DWORD *) a + 442);
        if (mFogBlownCountDown > 0) {
            ++*((_DWORD *) a + 442);
        }
    }
    return old_Board_UpdateGame(a);
}


void (*old_Board_UpdateGameObjects)(int board);

void Board_UpdateGameObjects(int board) {
    //修复过关后游戏卡住不动
    int levelCompleted = *(_DWORD *) (board + 22304);
    if (levelCompleted > 0) {
        //如果已经过关，则手动刷新植物，僵尸，子弹
        unsigned int tmp = NULL;
        while (Board_IteratePlants(board, &tmp)) {
            Plant_Update((void *) tmp);
        }
        tmp = NULL;
        while (Board_IterateZombies(board, &tmp)) {
            Zombie_Update(tmp);
        }
        tmp = NULL;
        while (Board_IterateProjectiles(board, &tmp)) {
            Projectile_Update((int *) tmp);
        }
    }
    old_Board_UpdateGameObjects(board);
}

bool drawDebugText = false;

//int *theImage;
//bool created = false;

void (*old_Board_DrawDebugText)(int *board, int *graphics);

void Board_DrawDebugText(int *board, int *graphics) {
    //出僵DEBUG功能
    if (drawDebugText) {
        _DWORD tmp = *((_DWORD *) board + 5574);
        *((_DWORD *) board + 5574) = 1;
        old_Board_DrawDebugText(board, graphics);
        *((_DWORD *) board + 5574) = tmp;
        return;
    }
    old_Board_DrawDebugText(board, graphics);
//    if (!created) {
//        created = true;
//        theImage = Plant_GetImage(0);
//    }
//    Sexy_Graphics_DrawImage(graphics, Plant_GetImage(0), 130, 80);

}

bool drawDebugRects = false;

void (*old_Board_DrawDebugObjectRects)(int *board, int *graphics);

void Board_DrawDebugObjectRects(int *board, int *graphics) {
    //碰撞体积绘制
    if (drawDebugRects) {
        _DWORD tmp = *((_DWORD *) board + 5574);
        *((_DWORD *) board + 5574) = 4;
        old_Board_DrawDebugObjectRects(board, graphics);
        *((_DWORD *) board + 5574) = tmp;
        return;
    }
    old_Board_DrawDebugObjectRects(board, graphics);
}


void Board_DrawFadeOut(int *board, int *graphics) {
    //修复关卡完成后的白色遮罩无法遮住整个屏幕
    int mBoardFadeOutCounter = board[5576];
    if (mBoardFadeOutCounter < 0) {
        return;
    }
    if (Board_IsSurvivalStageWithRepick(board)) {
        return;
    }
    int theAlpha = TodAnimateCurve(200, 0, mBoardFadeOutCounter, 0, 255, 1);
    int mLevel = board[5529];
    if (mLevel == 9 || mLevel == 19 || mLevel == 29 || mLevel == 39 || mLevel == 49) {
        int theColor[4] = {0, 0, 0, theAlpha};
        Sexy_Graphics_SetColor(graphics, theColor);
    } else {
        int theColor[4] = {255, 255, 255, theAlpha};
        Sexy_Graphics_SetColor(graphics, theColor);
    }
    Sexy_Graphics_SetColorizeImages((int) graphics, 1);
    int fullScreenRect[4] = {-240, -60, 1280, 720};
    //修复BUG的核心原理，就是不要在此处PushState和PopState，而是直接FillRect。
    Sexy_Graphics_FillRect(graphics, fullScreenRect);
}

bool infiniteSun;//无限阳光

int (*old_Board_GetCurrentPlantCost)(int a1, int a2, int a3);

int Board_GetCurrentPlantCost(int a1, int a2, int a3) {
    if (infiniteSun) return 0;
    else return old_Board_GetCurrentPlantCost(a1, a2, a3);
}

int Board_AddSunMoney(int _this, int theAmount, int a3) {
    //无限阳光
    int v3; // r2
    int v4; // r1
    v3 = _this + 4 * a3 + 22016;
    v4 = theAmount + *(_DWORD *) (v3 + 116);
    if (infiniteSun) {
        *(_DWORD *) (v3 + 116) = 9990;
    } else {
        *(_DWORD *) (v3 + 116) = v4 > 9990 ? 9990 : v4;
    }
    return _this;
}

char *Board_AddDeathMoney(int _this, int theAmount) {
    //无限阳光
    char *result; // r0
    int v3; // r1
    result = (char *) _this + 22016;
    v3 = theAmount + *((_DWORD *) result + 31);
    if (infiniteSun) {
        *((_DWORD *) result + 31) = 9990;
    } else {
        *((_DWORD *) result + 31) = v3 > 9990 ? 9990 : v3;
    }
    return result;
}

bool FreePlantAt = false;

int (*old_CanPlantAt)(int _this, int a2, int a3, int a4);

int Board_CanPlantAt(int _this, int a2, int a3, int a4) {
    if (FreePlantAt) {
        return 0; // 0<==>PLANTING_OK
    }
    return old_CanPlantAt(_this, a2, a3, a4);
}

bool (*old_Board_PlantingRequirementsMet)(int *a, int a2);

bool Board_PlantingRequirementsMet(int *a, int a2) {
    if (FreePlantAt) {
        return 1;
    }
    return old_Board_PlantingRequirementsMet(a, a2);
}

bool ZombieCanNotWon = false;

void (*old_BoardZombiesWon)(int _this, int Zombie_this);

void Board_ZombiesWon(int _this, int Zombie_this) {
    if (ZombieCanNotWon) {
        Zombie_ApplyBurn(Zombie_this);
        Zombie_DieNoLoot(Zombie_this);
        return;
    }
    return old_BoardZombiesWon(_this, Zombie_this);
}

//Board_AddPlant
bool PumpkinWithLadder = false;

int (*old_Board_AddPlant)(void *instance, int x, int y, int SeedType, int theImitaterType);

int Board_AddPlant(void *instance, int x, int y, int SeedType, int theImitaterType) {
    if (PumpkinWithLadder && SeedType == 30) {
        Board_AddALadder(instance, x, y);
    }
    return old_Board_AddPlant(instance, x, y, SeedType, theImitaterType);
}

//布阵建造普通植物韩束
void FormationBuildPlant(void *FormationBtn, int PlantArr[30][9]) {

    if (PlantArr[FormationBuild_y + 12][FormationBuild_x] != -1) {
        old_Board_AddPlant(FormationBtn, FormationBuild_x, FormationBuild_y,
                           PlantArr[FormationBuild_y + 12][FormationBuild_x], 0);//荷叶建造
    }//建荷叶
    if (IsRoofButt && FormationBuild_y != 5) {
        old_Board_AddPlant(FormationBtn, FormationBuild_x, FormationBuild_y, 33, 0);//花盆建造
    }//建造花盆
    if (PlantArr[FormationBuild_y][FormationBuild_x] != -1) {
        old_Board_AddPlant(FormationBtn, FormationBuild_x, FormationBuild_y,
                           PlantArr[FormationBuild_y][FormationBuild_x], 0);//植物建造
    }//建普通植物
    if (PlantArr[FormationBuild_y + 6][FormationBuild_x] != -1) {
        old_Board_AddPlant(FormationBtn, FormationBuild_x, FormationBuild_y,
                           PlantArr[FormationBuild_y + 6][FormationBuild_x], 0);//南瓜建造
    }//建南瓜

    if (PlantArr[FormationBuild_y + 18][FormationBuild_x] != -1) {
        old_Board_AddPlant(FormationBtn, FormationBuild_x, FormationBuild_y, 35, 0);//咖啡豆建造
    }//建咖啡豆
    if (PlantArr[FormationBuild_y + 24][FormationBuild_x] != -1) {
        Board_AddALadder(FormationBtn, FormationBuild_x, FormationBuild_y);//咖啡豆建造
    }//建梯子




    FormationBuild_x++;
    if (FormationBuild_x >= 9) {
        FormationBuild_y++;
        FormationBuild_x = 0;
    }
    if (FormationBuild_y > 5) {
        FormationButt = 0;
        IsRoofButt = 0;
        FormationDecideButt = 0;
        ChangeFormationArr[0][0] = 1314;
        FormationBuild_x = 0;
        FormationBuild_y = 0;

    }


}//

//Board
int LadderX = 0;
int BuildPlantX = 0;
int BuildZombieX = 0;
int LadderY = 0;
int BuildPlantY = 0;
int BuildZombieY = 0;
bool DoneLadderBuild;
bool DonePlantBuild;
bool DoneZombieBuild;
int ThePlantID = 0;
int TheZombieID = 0;
int BuildZombieCount = 1;
int TheZombieBuildRow = 0;
int Buildi = 0;
bool UniformPlace;
int UniformRow = 0;
int NowPlantCount = 0;//Board植物数
bool PassNowLevel;


bool Board_ZenGardenItemNumIsZero(int *board, int itemId) {
    //消耗性工具的数量是否为0个
    switch (itemId) {
        case 7:
            return *(_DWORD *) (
                    *(_DWORD *) (*((_DWORD *) board + 69) + LAWNAPP_PLAYER_PURCHASEINFO_OFFSET) +
                    500) == 1000;
        case 8:
            return *(_DWORD *) (
                    *(_DWORD *) (*((_DWORD *) board + 69) + LAWNAPP_PLAYER_PURCHASEINFO_OFFSET) +
                    504) == 1000;
        case 10:
            return *(_DWORD *) (
                    *(_DWORD *) (*((_DWORD *) board + 69) + LAWNAPP_PLAYER_PURCHASEINFO_OFFSET) +
                    548) == 1000;
        case 14:
            return *(_DWORD *) (
                    *(_DWORD *) (*((_DWORD *) board + 69) + LAWNAPP_PLAYER_PURCHASEINFO_OFFSET) +
                    556) == 1000;
    }
    return false;
}

//花园触控
bool requestSetZenGardenTool = false;
int zenGardenToolPosition = 0;
int zenGardenObjects[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int zenGardenObjectsCount = 0;
bool isGoldWateringCan = false;

int (*old_Board_DrawZenButtons)(int *board, int *a2);

int Board_DrawZenButtons(int *board, int *a2) {
    //记录当前花园工具栏的工具们
    zenGardenObjectsCount = 0;
    isGoldWateringCan = *(_DWORD *) (
            *(_DWORD *) (*((_DWORD *) board + 69) + LAWNAPP_PLAYER_PURCHASEINFO_OFFSET) + 496);
    for (int i = 6; i != 19; ++i) {
        if (Board_CanUseGameObject(board, i)) {
            zenGardenObjects[zenGardenObjectsCount] = Board_ZenGardenItemNumIsZero(board, i) ? 0 : (
                    i +
                    3);
            zenGardenObjectsCount++;
        }
    }
    return old_Board_DrawZenButtons(board, a2);
}

int *(*old_Board_KeyDown)(int *board, int a2);

int *Board_KeyDown(int *board, int keyCode) {
    //用于打开新版暂停菜单
    if (keyCode == 27) {
        if (enableNewOptionsDialog && gameState == 1 && !isCobCannonSelected &&
            !isCrazyDaveShowing) {
            LawnApp_DoNewOptions(*((int **) board + 69), 0, 0);  //植物方发起投降
            //LawnApp_DoNewOptions(*((int **) board + 69), 0, 1);  //僵尸方发起投降
            return board;
        } else {
            int *lawnApp = *((int **) board + 69);
            int nowGameIndex = *(lawnApp + LAWNAPP_GAMEINDEX_OFFSET);
            if (nowGameIndex == 76 && gameState == 1) {
                LawnApp_DoNewOptions(*((int **) board + 69), 0, 0);  //植物方发起投降
                //LawnApp_DoNewOptions(*((int **) board + 69), 0, 1);  //僵尸方发起投降
                return board;
            }
        }
    }
    //用于切换键盘模式，自动开关砸罐子老虎机种子雨关卡内的"自动拾取植物卡片"功能
    if (keyCode >= 37 && keyCode <= 40) {
        if (!keyboardMode) {
            GamePatches.UsefulSeedPacketAutoPickupDisable.Restore();
        }
        keyboardMode = true;
    }
    return old_Board_KeyDown(board, keyCode);
}

void (*old_Board_UpdateSunSpawning)(int *board);

void Board_UpdateSunSpawning(int *board) {
    if (requestPause) {
        //如果开了高级暂停
        return;
    }
    return old_Board_UpdateSunSpawning(board);
}

void (*old_Board_UpdateZombieSpawning)(int *board);

void Board_UpdateZombieSpawning(int *board) {
    if (requestPause) {
        //如果开了高级暂停
        return;
    }
    return old_Board_UpdateZombieSpawning(board);
}

void (*old_Board_UpdateIce)(int *board);

void Board_UpdateIce(int *board) {
    if (requestPause) {
        //如果开了高级暂停
        return;
    }
    return old_Board_UpdateIce(board);
}

bool hideCoverLayer = false;

void (*old_Board_DrawCoverLayer)(int *board, int *a2, int a3);

void Board_DrawCoverLayer(int *board, int *a2, int a3) {
    if (hideCoverLayer) {
        //如果玩家“隐藏草丛和电线杆”，则终止绘制函数
        return;
    }
    return old_Board_DrawCoverLayer(board, a2, a3);
}

void (*old_Board_PickBackground)(int *board);

void Board_PickBackground(int *board) {
    //用于控制关卡的场地选取。可选择以下场地：前院白天/夜晚，泳池白天/夜晚，屋顶白天/夜晚
    int *v2 = (int *) *((_DWORD *) board + 69);
    char *v3 = (char *) board + 22016;
    switch (VSBackGround) {
        case 1:
            *((_DWORD *) v3 + 24) = 0;
            Board_LoadBackgroundImages(board);
            *((_DWORD *) board + 443) = 1;
            *((_DWORD *) board + 444) = 1;
            *((_DWORD *) board + 445) = 1;
            *((_DWORD *) board + 446) = 1;
            *((_DWORD *) board + 447) = 1;
            *((_DWORD *) board + 448) = 0;
            Board_InitCoverLayer(board);
            Board_SetGrids(board);
            return;
        case 2:
            *((_DWORD *) v3 + 24) = 1;
            Board_LoadBackgroundImages(board);
            *((_DWORD *) board + 443) = 1;
            *((_DWORD *) board + 444) = 1;
            *((_DWORD *) board + 445) = 1;
            *((_DWORD *) board + 446) = 1;
            *((_DWORD *) board + 447) = 1;
            *((_DWORD *) board + 448) = 0;
            Board_InitCoverLayer(board);
            Board_SetGrids(board);
            return;
        case 3:
            *((_DWORD *) v3 + 24) = 2;
            Board_LoadBackgroundImages(board);
            *((_DWORD *) board + 443) = 1;
            *((_DWORD *) board + 444) = 1;
            *((_DWORD *) board + 445) = 2;
            *((_DWORD *) board + 446) = 2;
            *((_DWORD *) board + 447) = 1;
            *((_DWORD *) board + 448) = 1;
            Board_InitCoverLayer(board);
            Board_SetGrids(board);
            return;
        case 4:
            *((_DWORD *) v3 + 24) = 3;
            Board_LoadBackgroundImages(board);
            *((_DWORD *) board + 443) = 1;
            *((_DWORD *) board + 444) = 1;
            *((_DWORD *) board + 445) = 2;
            *((_DWORD *) board + 446) = 2;
            *((_DWORD *) board + 447) = 1;
            *((_DWORD *) board + 448) = 1;
            Board_InitCoverLayer(board);
            Board_SetGrids(board);
            return;
        case 5:
            *((_DWORD *) v3 + 24) = 4;
            Board_LoadBackgroundImages(board);
            *((_DWORD *) board + 443) = 1;
            *((_DWORD *) board + 444) = 1;
            *((_DWORD *) board + 445) = 1;
            *((_DWORD *) board + 446) = 1;
            *((_DWORD *) board + 447) = 1;
            *((_DWORD *) board + 448) = 0;
            Board_InitCoverLayer(board);
            Board_SetGrids(board);
            if (*((_DWORD *) v2 + LAWNAPP_GAMEINDEX_OFFSET) == 76) {
                Board_AddPlant(board, 0, 1, 33, 0);
                Board_AddPlant(board, 0, 3, 33, 0);
                for (int i = 3; i < 5; ++i) {
                    for (int j = 0; j < 5; ++j) {
                        Board_AddPlant(board, i, j, 33, 0);
                    }
                }
            }
            return;
        case 6:
            *((_DWORD *) v3 + 24) = 5;
            Board_LoadBackgroundImages(board);
            *((_DWORD *) board + 443) = 1;
            *((_DWORD *) board + 444) = 1;
            *((_DWORD *) board + 445) = 1;
            *((_DWORD *) board + 446) = 1;
            *((_DWORD *) board + 447) = 1;
            *((_DWORD *) board + 448) = 0;
            Board_InitCoverLayer(board);
            Board_SetGrids(board);
            if (*((_DWORD *) v2 + LAWNAPP_GAMEINDEX_OFFSET) == 76) {
                Board_AddPlant(board, 0, 1, 33, 0);
                Board_AddPlant(board, 0, 3, 33, 0);
                for (int i = 3; i < 4; ++i) {
                    for (int j = 0; j < 5; ++j) {
                        Board_AddPlant(board, i, j, 33, 0);
                    }
                }
            }
            return;
    }
    old_Board_PickBackground(board);
}

void (*old_Board_UpdateFwoosh)(int *board);

void Board_UpdateFwoosh(int *board) {
    if (requestPause) {
        return;
    }
    old_Board_UpdateFwoosh(board);
}

void (*old_Board_UpdateFog)(int *board);

void Board_UpdateFog(int *board) {
    if (requestPause) {
        return;
    }
    old_Board_UpdateFog(board);
}

int (*old_Board_AddZombieInRow)(void *board, int theZombieType, int theRow, int theFromWave,
                                bool playAnim);

int
Board_AddZombieInRow(void *board, int theZombieType, int theRow, int theFromWave, bool playAnim) {
    //修复蹦极僵尸出现时草丛也会摇晃
    if (theZombieType == 20) playAnim = false;
    return old_Board_AddZombieInRow(board, theZombieType, theRow, theFromWave, playAnim);
}

//void (*old_Board_UpdateCoverLayer)(int *board);
//
//void Board_UpdateCoverLayer(int *board) {
//    if (requestPause) {
//        return;
//    }
//    old_Board_UpdateCoverLayer(board);
//}

void Board_SpeedUpUpdate(int *board) {
    Board_UpdateGridItems(board);
    Board_UpdateFwoosh(board);
    Board_UpdateGame(board);
    Board_UpdateFog(board);
//    Board_UpdateCoverLayer(board);
    Challenge_Update(*((int **) board + 149));
}

int (*old_Board_Update)(int *board);

int Board_Update(int *board) {
    // 触控的90%代码都在此函数中处理。
    isMainMenu = false;
    isInVSSetupMenu = false;
    mBoardBackground = *((_DWORD *) board + 5528);
    int cursorObject_1P = *((_DWORD *) board + 142);
    if (requestSetZenGardenTool) {
        //requestSetZenGardenTool = false;
        if (zenGardenToolPosition < zenGardenObjectsCount) {
            Board_PickUpTool(board, zenGardenObjects[zenGardenToolPosition] - 3, 0);
            //*(_DWORD *) (cursorObject_1P + 64) = zenGardenObjects[zenGardenToolPosition];
        }
    }
    cursorType = *(_DWORD *) (cursorObject_1P + 64);
    hasConveyOrBelt = Board_HasConveyorBeltSeedBank(board, 0);

    if (requestShovelDown) {
        Board_ShovelDown(board);
        requestShovelDown = false;
    }
    if (requestClearCursor) {
        Board_ClearCursor(board, 0);
        Board_RefreshSeedPacketFromCursor(board, 0);
        requestClearCursor = false;
    }
    if (requestDrawShovelInCursor) {
        int plantUnderShovel = Board_ToolHitTest(board, boardPositionXToSet, boardPositionYToSet);
        if (plantUnderShovel != NULL) {
            // 让这个植物高亮
            *(_DWORD *) ((int) plantUnderShovel + 200) = 1000;//1000是为了不和其他闪光效果冲突
        }
    }
    int cobCannonPlant = 0;
    int cobCannonPlant_2P = 0;
    if (requestValidCobCannonCheckByXY) {
        int plants[4] = {0};
        Board_GetPlantsOnLawn((uintptr_t) board,
                              Board_PixelToGridX(board, cobToCheckX, cobToCheckY),
                              Board_PixelToGridY(board, cobToCheckX, cobToCheckY), plants);
        bool isCurrentPlantValidCobCannon = plants[3] != 0 && *((int *) plants[3] + 13) == 47 &&
                                            *((int *) plants[3] + 19) == 37;
        requestValidCobCannonCheckByXY = false;
        if (isCurrentPlantValidCobCannon) {
            requestSetGameState = true;
            stateToSet = 1;
            requestCobCannonPickUp = true;
            cobCannonPlant = plants[3];
        }
    }
    if (requestValidCobCannonCheckByXY_2P) {
        int plants[4] = {0};
        Board_GetPlantsOnLawn((uintptr_t) board,
                              Board_PixelToGridX(board, cobToCheckX_2P, cobToCheckY_2P),
                              Board_PixelToGridY(board, cobToCheckX_2P, cobToCheckY_2P),
                              plants);
        bool isCurrentPlantValidCobCannon = plants[3] != 0 && *((int *) plants[3] + 13) == 47 &&
                                            *((int *) plants[3] + 19) == 37;
        requestValidCobCannonCheckByXY_2P = false;
        if (isCurrentPlantValidCobCannon) {
            requestSetGameState_2P = true;
            stateToSet_2P = 1;
            requestCobCannonPickUp_2P = true;
            cobCannonPlant_2P = plants[3];
        }
    }
    if (requestValidCobCannonCheckByGrid) {
        int plants[4] = {0};
        Board_GetPlantsOnLawn((uintptr_t) board, col, row, plants);
        bool isCurrentPlantValidCobCannon = plants[3] != 0 && *((int *) plants[3] + 13) == 47 &&
                                            *((int *) plants[3] + 19) == 37;
        requestValidCobCannonCheckByGrid = false;
        if (isCurrentPlantValidCobCannon) {
            requestSetGameState = true;
            stateToSet = 1;
            requestCobCannonPickUp = true;
            cobCannonPlant = plants[3];
        }
    }

    int gamePad = *((_DWORD *) board + 140);
    int gamePad_2P = *((_DWORD *) board + 141);
    int *lawnApp = *((int **) board + 69);
    if (gamePad != 0) {
        *(_DWORD *) (gamePad + 152) = 0;
        isCobCannonSelected = *((_BYTE *) gamePad + 200);

        if (requestCheckAndSelectSeedPacket) {
            if (isCobCannonSelected) {
                GamepadControls_OnKeyDown(gamePad, 27, 1096);
            }
            int hitResult[2] = {0};
            int v7 = GamepadControls_GetSeedBank(gamePad);
            SeedBank_MouseHitTest((int *) v7, checkSeedPacketX, 50, hitResult);
            if (hitResult[1] == 4) {
                requestSetSeedBankPosition = true;
                seekBankPositionToSet = *((_DWORD *) (int *) hitResult[0] + 15);
                if (seekBankPositionToSet == seekBankPositionOrigin) {
                    requestSetGameState = true;
                    stateToSet = gameState == 7 ? 1 : 7;
                }
            }
            requestCheckAndSelectSeedPacket = false;
        }
        bool needPlaySelectSeedSound_1P = false;
        if (requestSetSeedBankPosition) {
            *(int *) (gamePad + 0x60) = requestDrawShovelInCursor ? 1 : 7;
            if (*((int *) gamePad + 45) != seekBankPositionToSet) {
                needPlaySelectSeedSound_1P = true;
            }
            *((int *) gamePad + 45) = seekBankPositionToSet;
            int v7 = GamepadControls_GetSeedBank(gamePad);
            int result = v7 + 116 * seekBankPositionToSet;
            *(_DWORD *) (result + 172) = 0;
            requestSetSeedBankPosition = false;
        }
        if (requestSetGameState) {
            if (*(int *) (gamePad + 0x60) != 7 && stateToSet == 7) {
                needPlaySelectSeedSound_1P = true;
            }
            *(int *) (gamePad + 0x60) = requestDrawShovelInCursor ? 1 : stateToSet;

            requestSetGameState = false;
        }
        if (needPlaySelectSeedSound_1P) {
            (*(void (__fastcall **)(_DWORD, int, int)) (*lawnApp + LAWNAPP_PLAYSOUND_OFFSET))(
                    (int) lawnApp,
                    *Sexy_SOUND_SEEDLIFT_Addr,
                    1);
        }
        gameState = *(int *) (gamePad + 0x60);

        seekBankPositionOrigin = *((int *) gamePad + 45);
        if (requestSetBoardPositionByXY) {
            *(float *) (gamePad + 108) = boardPositionXToSet;
            *(float *) (gamePad + 112) = boardPositionYToSet;
            requestSetBoardPositionByXY = false;
        }
        gridX = Board_PixelToGridX(board, *(float *) (gamePad + 108),
                                   *(float *) (gamePad + 112));
        gridY = Board_PixelToGridY(board, *(float *) (gamePad + 108),
                                   *(float *) (gamePad + 112));
        if (requestCheckAndSelectUsefulSeedPacket) {
            int hitResult[2] = {0};
            Board_MouseHitTest(board, boardPositionXToSet, boardPositionYToSet, hitResult,
                               false);
            if (hitResult[1] == 3) {
                if (*((_DWORD *) hitResult[0] + 29) == 16) {
                    Board_RefreshSeedPacketFromCursor(board, 0);
                    old_Coin_GamepadCursorOver((int *) hitResult[0], 0);
                }
            }
            requestCheckAndSelectUsefulSeedPacket = false;
        }
        if (requestPlantUsefulSeedPacket) {
            int hitResult[2] = {0};
            Board_MouseHitTest(board, boardPositionXToSet, boardPositionYToSet, hitResult,
                               false);
            if (hitResult[1] == 3) {
                if (*((_DWORD *) hitResult[0] + 29) == 16) {
                    Board_RefreshSeedPacketFromCursor(board, 0);
                    old_Coin_GamepadCursorOver((int *) hitResult[0], 0);
                }
            } else {
                GamepadControls_OnKeyDown(gamePad, 13, 1112);
            }
            requestPlantUsefulSeedPacket = false;
        }
        if (requestQuickDig) {
            GamepadControls_OnKeyDown(gamePad, 49, 1112);
            requestQuickDig = false;
        }
        if (requestButtonDown) {
            GamepadControls_OnButtonDown(gamePad, buttonCode1, 0, 0);
            requestButtonDown = false;
        }
        if (requestCobCannonPickUp) {
            GamepadControls_pickUpCobCannon(gamePad, cobCannonPlant);
            requestCobCannonPickUp = false;
        }
    }
    int nowGameIndex = *(lawnApp + LAWNAPP_GAMEINDEX_OFFSET);
    if (gamePad_2P != 0 && nowGameIndex >= 76 && nowGameIndex <= 89) {
        *(_DWORD *) (gamePad_2P + 152) = 1;
        isCobCannonSelected_2P = *((_BYTE *) gamePad_2P + 200);

        if (requestCheckAndSelectSeedPacket_2P) {
            if (isCobCannonSelected_2P) {
                GamepadControls_OnKeyDown(gamePad_2P, 27, 1096);
            }
            int hitResult_2P[2] = {0};
            int v7_2P = GamepadControls_GetSeedBank(gamePad_2P);
            SeedBank_MouseHitTest((int *) v7_2P, checkSeedPacketX_2P, 50, hitResult_2P);
            if (hitResult_2P[1] == 4) {
                requestSetSeedBankPosition_2P = true;
                seekBankPositionToSet_2P = *((_DWORD *) (int *) hitResult_2P[0] + 15);
                if (seekBankPositionToSet_2P == seekBankPositionOrigin_2P) {
                    requestSetGameState_2P = true;
                    stateToSet_2P = gameState_2P == 7 ? 1 : 7;
                }
            }
            requestCheckAndSelectSeedPacket_2P = false;
        }
        bool needPlaySelectSeedSound_2P = false;
        if (requestSetSeedBankPosition_2P) {
            *(int *) (gamePad_2P + 0x60) = requestDrawButterInCursor ? 1 : 7;
            if (*((int *) gamePad_2P + 45) != seekBankPositionToSet_2P) {
                needPlaySelectSeedSound_2P = true;
            }
            *((int *) gamePad_2P + 45) = seekBankPositionToSet_2P;
            int v7 = GamepadControls_GetSeedBank(gamePad_2P);
            int result = v7 + 116 * seekBankPositionToSet_2P;
            *(_DWORD *) (result + 172) = 0;
            requestSetSeedBankPosition_2P = false;
        }
        if (requestSetGameState_2P) {
            if (*(int *) (gamePad_2P + 0x60) != 7 && stateToSet_2P == 7) {
                needPlaySelectSeedSound_2P = true;
            }
            *(int *) (gamePad_2P + 0x60) = requestDrawButterInCursor ? 1 : stateToSet_2P;
            requestSetGameState_2P = false;
        }
        if (needPlaySelectSeedSound_2P) {
            (*(void (__fastcall **)(_DWORD, int, int)) (*lawnApp + LAWNAPP_PLAYSOUND_OFFSET))(
                    (int) lawnApp,
                    *Sexy_SOUND_SEEDLIFT_Addr,
                    1);
        }
        gameState_2P = *(int *) (gamePad_2P + 0x60);
        seekBankPositionOrigin_2P = *((int *) gamePad_2P + 45);
        if (requestSetBoardPositionByXY_2P) {
            *(float *) (gamePad_2P + 108) = boardPositionXToSet_2P;
            *(float *) (gamePad_2P + 112) = boardPositionYToSet_2P;
            requestSetBoardPositionByXY_2P = false;
        }
        gridX_2P = Board_PixelToGridX(board, *(float *) (gamePad_2P + 108),
                                      *(float *) (gamePad_2P + 112));
        gridY_2P = Board_PixelToGridY(board, *(float *) (gamePad_2P + 108),
                                      *(float *) (gamePad_2P + 112));
        if (requestButtonDown_2P) {
            //GamepadControls_OnKeyDown(gamePad_2P, buttonCode1_2P, buttonCode2_2P);
            GamepadControls_OnButtonDown(gamePad_2P, buttonCode1_2P, 1, 0);
            if (buttonCode1_2P == 6 && nowGameIndex == 76) *(int *) (gamePad_2P + 0x60) = 1;
            requestButtonDown_2P = false;
        }
        if (requestDrawButterInCursor) {
            int *zombieUnderButter = Board_ZombieHitTest(board, boardPositionXToSet_2P,
                                                         boardPositionYToSet_2P, 1);
            if (zombieUnderButter != 0) {
                int mButterCounter = *((_DWORD *) zombieUnderButter + 48);
                if (mButterCounter <= 100) {
                    if (mButterCounter == 0) {
                        LawnApp_PlayFoley((int) lawnApp, 43);
                    }
                    Zombie_ApplyButter(zombieUnderButter);
                }
            }
        }
//            if (requestButtonUp_2P) {
//                GamepadControls_OnButtonUp(gamePad_2P, buttonCode2_2P, 1, 0);
//                requestButtonUp_2P = false;
//            }
        if (requestCobCannonPickUp_2P) {
            GamepadControls_pickUpCobCannon(gamePad_2P, cobCannonPlant_2P);
            requestCobCannonPickUp_2P = false;
        }
    }

    if (!*((_BYTE *) board + 601) && *((int *) board + 5658) <= 0) {
        switch (speedUpMode) {
            case 1:
                if (speedUpCounter++ % 5 == 0) {
                    Board_SpeedUpUpdate(board);
                }
                break;
            case 2:
                if (speedUpCounter++ % 2 == 0) {
                    Board_SpeedUpUpdate(board);
                }
                break;
            case 3:
                Board_SpeedUpUpdate(board);
                break;
            case 4:
                Board_SpeedUpUpdate(board);
                if (speedUpCounter++ % 2 == 0) {
                    Board_SpeedUpUpdate(board);
                }
                break;
            case 5:
                for (int i = 0; i < 2; ++i) {
                    Board_SpeedUpUpdate(board);
                }
                break;
            case 6:
                for (int i = 0; i < 4; ++i) {
                    Board_SpeedUpUpdate(board);
                }
                break;
            case 7:
                for (int i = 0; i < 9; ++i) {
                    Board_SpeedUpUpdate(board);
                }
                break;
            default:
                break;
        }
    }

    //----------*************------------
    NowPlantCount = *(int *) ((uintptr_t) board + 0x144);
    if (ClearAllPlant && NowPlantCount == 0) {
        ClearAllPlant = false;
    }

    if (PassNowLevel) {
        *(int *) ((uintptr_t) board + 0x571C) = 1;
        PassNowLevel = false;
    }

//    __android_log_print(ANDROID_LOG_DEBUG, "TAG", "%d %d", Board_GetNumWavesPerFlag(board),
//                        Board_ProgressMeterHasFlags(board));


    //植物建造----------------
    if (FormationButt && FormationDecideButt) {
        if (ChangeFormationArr[0][0] != 1314) {
            FormationBuildPlant(board, ChangeFormationArr);
        }
    }
    //-------------------------
    if (DoneLadderBuild) {
        Board_AddALadder(board, LadderX, LadderY);
        DoneLadderBuild = 0;
    }
    if (DonePlantBuild && ThePlantID != -1) {
        Board_AddPlant(board, BuildPlantX, BuildPlantY, ThePlantID, 0);
        DonePlantBuild = 0;
    }
    if (DoneZombieBuild && TheZombieID != -1) {
        if (Buildi >= BuildZombieCount) {
            DoneZombieBuild = 0;
            return old_Board_Update(board);
        }
        if (UniformPlace) {
            Board_AddZombieInRow(board, TheZombieID, UniformRow, 0,1);
            UniformRow++;
            Buildi++;
            if (UniformRow > ((mBoardBackground == 2 || mBoardBackground == 3) ? 5 : 4)) {
                UniformRow = 0;
            }
        } else {
            Board_AddZombieInRow(board, TheZombieID, TheZombieBuildRow, 0,1);
            Buildi++;
        }
    }
    return old_Board_Update(board);
}

//int (*old_Board_GetNumSeedsInBank)(int *board, bool a2);
//
//int Board_GetNumSeedsInBank(int *board, bool a2) {
//    if (gameIndex == 76) {
//        return 7;
//    }
//    return old_Board_GetNumSeedsInBank(board, a2);
//}

int Board_GetNumWavesPerFlag(int *board) {
    //修改此函数，以做到在进度条上正常绘制旗帜波的旗帜。
    int *lawnApp = *((int **) board + 69);
    int mNumWaves = *((_DWORD *) board + 5536);
    if (LawnApp_IsFirstTimeAdventureMode(lawnApp) && mNumWaves < 10) {
        return mNumWaves;
    }
    //额外添加一段判断逻辑，判断关卡代码20且波数少于10的情况
    int nowGameIndex = *(lawnApp + LAWNAPP_GAMEINDEX_OFFSET);
    if (nowGameIndex == 20 && mNumWaves < 10) {
        return mNumWaves;
    }
    return 10;
}

bool (*old_Board_IsFlagWave)(int *board, int a2);

bool Board_IsFlagWave(int *board, int currentWave) {
    //修改此函数，以做到正常出旗帜波僵尸。
    if (!normalLevel) {
        return old_Board_IsFlagWave(board, currentWave);
    }
    int *lawnApp = *((int **) board + 69);
    int nowGameIndex = *(lawnApp + LAWNAPP_GAMEINDEX_OFFSET);
    if (nowGameIndex == 76)
        return true;
    if (LawnApp_IsFirstTimeAdventureMode(lawnApp) && *((int *) board + 5529) == 1)
        return false;
    int mNumWavesPerFlag = Board_GetNumWavesPerFlag(board);
    return currentWave % mNumWavesPerFlag == mNumWavesPerFlag - 1;

}

void (*old_Board_DrawProgressMeter)(int *board, int *graphics, int a3, int a4);

void Board_DrawProgressMeter(int *board, int *graphics, int a3, int a4) {
    //修改此函数，以做到在进度条上正常绘制旗帜波的旗帜。
    if (normalLevel) {
        int *lawnApp = *((int **) board + 69);
        if (LawnApp_IsAdventureMode(lawnApp) && Board_ProgressMeterHasFlags(board)) {
            *(lawnApp + LAWNAPP_GAMEINDEX_OFFSET) = 20;//修改关卡信息为非冒险模式
            old_Board_DrawProgressMeter(board, graphics, a3, a4);
            *(lawnApp + LAWNAPP_GAMEINDEX_OFFSET) = 0;//再把关卡信息改回冒险模式
            return;
        }
        old_Board_DrawProgressMeter(board, graphics, a3, a4);
    } else {
        old_Board_DrawProgressMeter(board, graphics, a3, a4);
    }
}

bool (*old_Board_IsLevelDataLoaded)(int *board);

bool Board_IsLevelDataLoaded(int *board) {
    //确保在开启原版难度时，所有用到levels.xml的地方都不生效
    if (normalLevel) return false;
    return old_Board_IsLevelDataLoaded(board);
}

bool (*old_Board_NeedSaveGame)(int *board);

bool Board_NeedSaveGame(int *board) {
    //可以让结盟关卡存档，但是好多BUG啊
//    if (LawnApp_IsCoopMode(*((int **) board + 69))) {
//        return true;
//    }
    return old_Board_NeedSaveGame(board);
}

void (*old_Board_DrawBackdrop)(int *board, int *graphics);

void Board_DrawBackdrop(int *board, int *graphics) {
//    int background = *((_DWORD *)board + 5528);
//    *((_DWORD *)board + 5528) = 2;
    old_Board_DrawBackdrop(board, graphics);
//    *((_DWORD *)board + 5528) = background;

}
//int *(*old_Board_SpawnZombiesFromPool)(int *zombie);
//
//int *Board_SpawnZombiesFromPool(int *zombie) {
//    int mZombieType = *((_DWORD *) zombie + 13);
//    if(mZombieType)
//}


//int (*old_Board_GetSurvivalFlagsCompleted)(int *board);
//
//int Board_GetSurvivalFlagsCompleted(int *board) {
//
//    return old_Board_GetSurvivalFlagsCompleted(board);
//}

bool Sexy_GamepadApp_HasGamepad(int *lawnApp) {
    return false;
}

void Board_DrawShovel(int *board, int *graphics) {
    //实现拿着铲子、黄油的时候不在栏内绘制铲子、黄油
    int *lawnApp = (int *) board[69];
    int nowGameIndex = *((_DWORD *) lawnApp + LAWNAPP_GAMEINDEX_OFFSET);
    if (nowGameIndex == 20)
        return;
    if (*((_BYTE *) board + 22291)) {
        float tmp = *((float *) graphics + 3);
        int rect[4];
        Board_GetButterButtonRect(rect, board);
        Sexy_Graphics_DrawImage(graphics, (int *) *Sexy_IMAGE_SHOVELBANK_Addr, rect[0], rect[1]);
        Sexy_Graphics_DrawImage(graphics, (int *) *Sexy_IMAGE_HAMMER_ICON_Addr, rect[0] - 7,
                                rect[1] - 3);
        if (Sexy_GamepadApp_HasGamepad(lawnApp) ||
            (*((_BYTE *) lawnApp + LAWNAPP_GAMEPAD1_OFFSET) &&
             *((_BYTE *) lawnApp + LAWNAPP_GAMEPAD2_OFFSET))) {
            Sexy_Graphics_DrawImageCel2(graphics, (int *) *Sexy_IMAGE_HELP_BUTTONS_Addr,
                                        rect[0] + 36, rect[1] + 40, 2);
        } else {
            Sexy_Graphics_DrawImageCel2(graphics, (int *) *Sexy_IMAGE_HELP_BUTTONS2_Addr,
                                        rect[0] + 36, rect[1] + 40, 2);
        }
        Sexy_Graphics_SetColorizeImages((int) graphics, 0);
        *((float *) graphics + 3) = tmp;
    }
    if (*((_BYTE *) board + 22290)) {
        if (!LawnApp_IsCoopMode(lawnApp)) {
            if (!LawnApp_IsAdventureMode(lawnApp))
                goto LABEL_4;
            if (*((_DWORD *) lawnApp + LAWNAPP_TWOPLAYER_OFFSET) == -1)
                goto LABEL_4;
        }
        float tmp = *((float *) graphics + 3);
        int rect[4];
        Board_GetButterButtonRect(rect, board);
        Sexy_Graphics_DrawImage(graphics, (int *) *Sexy_IMAGE_SHOVELBANK_Addr, rect[0], rect[1]);
        if (*(_DWORD *) (board[149] + 104) == 15) {
            int color[4];
            GetFlashingColor(color, board[5537], 75);
            Sexy_Graphics_SetColorizeImages((int) graphics, 1);
            Sexy_Graphics_SetColor(graphics, color);
        }
        //实现拿着黄油的时候不在栏内绘制黄油
        if (!requestDrawButterInCursor) {
            Sexy_Graphics_DrawImage(graphics, (int *) *Sexy_IMAGE_BUTTER_ICON_Addr, rect[0] - 7,
                                    rect[1] - 3);
        }
        Sexy_Graphics_DrawImageCel2(graphics, (int *) *Sexy_IMAGE_HELP_BUTTONS_Addr, rect[0] + 36,
                                    rect[1] + 40, 2);
        Sexy_Graphics_SetColorizeImages((int) graphics, 0);
        *((float *) graphics + 3) = tmp;
    }
    LABEL_4:

    if (nowGameIndex != 51 && nowGameIndex != 44) {
        if (nowGameIndex == 76)
            return;
        if (*((_BYTE *) board + 22289)) {
            float tmp = *((float *) graphics + 3);
            int rect[4];
            Board_GetShovelButtonRect(rect, board);
            Sexy_Graphics_DrawImage(graphics, (int *) *Sexy_IMAGE_SHOVELBANK_Addr, rect[0],
                                    rect[1]);
            if (*(_DWORD *) (board[149] + 104) == 15) {
                int color[4];
                GetFlashingColor(color, board[5537], 75);
                Sexy_Graphics_SetColorizeImages((int) graphics, 1);
                Sexy_Graphics_SetColor(graphics, color);
            }
            //实现拿着铲子的时候不在栏内绘制铲子
            if (!requestDrawShovelInCursor) {
                Sexy_Graphics_DrawImage(graphics, (int *) *Sexy_IMAGE_SHOVEL_Addr, rect[0] - 7,
                                        rect[1] - 3);
            }
            if (LawnApp_IsCoopMode(lawnApp)) {
                Sexy_Graphics_DrawImageCel2(graphics, (int *) *Sexy_IMAGE_HELP_BUTTONS_Addr,
                                            rect[0] + 40, rect[1] + 40, 1);
            } else {
                if (Sexy_GamepadApp_HasGamepad(lawnApp) ||
                    (*((_BYTE *) lawnApp + LAWNAPP_GAMEPAD1_OFFSET) &&
                     *((_BYTE *) lawnApp + LAWNAPP_GAMEPAD2_OFFSET))) {
                    Sexy_Graphics_DrawImageCel2(graphics, (int *) *Sexy_IMAGE_HELP_BUTTONS_Addr,
                                                rect[0] + 50, rect[1] + 40, 1);
                } else {
                    Sexy_Graphics_DrawImageCel2(graphics, (int *) *Sexy_IMAGE_HELP_BUTTONS2_Addr,
                                                rect[0] + 50, rect[1] + 40, 1);
                }
            }
            Sexy_Graphics_SetColorizeImages((int) graphics, 0);
            *((float *) graphics + 3) = tmp;
        }
    }

    if (nowGameIndex == 51 || nowGameIndex == 44) {
        Board_DrawZenButtons(board, graphics);
    }
}

#endif //PVZ_TV_1_1_5_BOARD_H