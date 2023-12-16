//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_BOARDINGAMEFUNCTION_H
#define PVZ_TV_1_1_5_BOARDINGAMEFUNCTION_H


//检查加农炮用
int (*Board_GetPlantsOnLawn)(int board, unsigned int a2, unsigned int a3, int *a4);

int (*Board_GridToPixelX)(void *board, unsigned int a2, unsigned int a3);

int (*Board_GridToPixelY)(void *board, unsigned int a2, unsigned int a3);

int (*Board_PixelToGridX)(void *board, unsigned int a2, unsigned int a3);

int (*Board_PixelToGridY)(void *board, unsigned int a2, unsigned int a3);

int (*Board_LoadBackgroundImages)(int *board);

unsigned int (*Board_AddALadder)(void *board, int x, int y);

int (*Board_MouseHitTest)(void *board, int x, int y, int *hitResult, bool posScaled);

int (*Board_ToolHitTest)(int *board, int a2, int a3);

int (*Board_RefreshSeedPacketFromCursor)(void *board, int a2);

int (*Board_CanUseGameObject)(int *board, int a2);

int (*Board_NewPlant)(int *board, int a2, int a3, int a4, int a5, int a6);

int (*Board_GetTopPlantAt)(int *board, unsigned int a2, unsigned int a3, int a4);

int (*Board_ClearCursor)(int *board, int a2);

int (*Board_UpdateGridItems)(int *board);

int (*Board_MouseDownWithTool)(int *board, int a2, int a3, int a4, int a5, int a6);

int (*Board_CountPlantByType)(int *board, int a2);

int (*Board_SetTutorialState)(int *board, int a2);

int *(*Board_ZombieHitTest)(int *board, int a2, int a3, int a4);

int (*Board_HasConveyorBeltSeedBank)(int *board, int a2);

int (*Board_InitCoverLayer)(int *board);

int (*Board_GameAxisMove)(int *board, int a2, int a3, int a4);

int (*Board_AddProjectile)(int, int, int, int, int, int);

bool (*Board_IterateZombies)(int board, unsigned int *zombie);

bool (*Board_IterateGridItems)(int board, unsigned int *gridItem);

bool (*Board_IteratePlants)(int board, unsigned int *plant);

bool (*Board_IterateProjectiles)(int board, unsigned int *projectile);

bool (*Board_IsSurvivalStageWithRepick)(int *board);

void (*Board_PickUpTool)(int *board, int a2, int a3);

bool (*Board_ProgressMeterHasFlags)(int *board);

//整体移动整个草坪，包括种子栏和铲子按钮等等。
void (*Board_Move)(int *board, int newX, int newY);

void (*Board_DoFwoosh)(int board, int mRow);

void (*Board_ShakeBoard)(int baord, int, int);

void (*Board_GetButterButtonRect)(int*,int*);

void (*Board_GetShovelButtonRect)(int*,int*);

//void (*Board_DrawZenButtons)(int*,int*);

void Board_ZombiesWon(int _this, int Zombie_this);

int Board_AddZombieInRow(void *board, int theZombieType, int theRow, int theFromWave,bool playAnim);

#endif //PVZ_TV_1_1_5_BOARDINGAMEFUNCTION_H
