//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_MISCINGAMEFUNCTION_H
#define PVZ_TV_1_1_5_MISCINGAMEFUNCTION_H

bool (*CutScene_IsSurvivalRepick)(void *instance);

int (*ChallengeScreen_SetScrollTarget)(int *instance, int a);

int (*CursorObject_Draw)(int a, int *a2);

int (*StoreScreen_SetSelectedSlot)(int a1, int a2);

int (*Attachment_AttachmentDie)(int result);

int (*SeedBank_MouseHitTest)(int *a1, int a2, int a3, int *a4);

void (*old_ZenGardenControls_Update)(float *a1, float a2);

int (*WaitForSecondPlayerDialog_GameButtonDown)(int *a1, int a2, int a3);

int (*TodDrawImageCelCenterScaledF)(int *a1,
                                    int *a2, float a3, float a4, int a5, float a6, float a7);

void (*DrawSeedPacket)(float *a1, int a2, int a3, int seedType, int imitaterType,
                       float coolDownPercent, int grayness, char shouldDrawCostText, char a9,
                       char backgroundType, char a11);

int (*ReanimatorCache_DrawCachedZombie)(int a1, int *a2, float a3, float a4, int a5);

int *(*Sexy_StrFormat)(int *a, const char *a2, ...);

int (*TodAnimateCurve)(int a1, int a2, int a3, int a4, int a5, int a6);

int *(*FilterEffectCreateImage)(int *a1, int a2);

int (*GetRectOverlap)(int *a1, int *a2);

int (*LawnPlayerInfo_GetFlag)(int *, int);

void (*GetFlashingColor)(int *, int, int);

#endif //PVZ_TV_1_1_5_MISCINGAMEFUNCTION_H
