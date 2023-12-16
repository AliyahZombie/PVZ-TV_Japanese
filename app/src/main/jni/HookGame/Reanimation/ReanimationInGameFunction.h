//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_REANIMATIONINGAMEFUNCTION_H
#define PVZ_TV_1_1_5_REANIMATIONINGAMEFUNCTION_H

int (*Reanimation_DrawRenderGroup)(int a, int *graphics, int a3);

void (*Reanimation_Reanimation)(int *a);

int (*Reanimation_ReanimationInitializeType)(int *a1, float a2, float a3, int a4);

bool *(*Reanimation_Draw)(int *a, int *a2);

void (*Reanimation_PrepareForReuse)(int *a);

int (*Reanimation_FindTrackIndexById)(int *a, char *a2);

void (*Reanimation_GetCurrentTransform)(int*, int, float *);

void (*ReanimatorTransform_ReanimatorTransform)(float *a);

void (*Reanimation_PlayReanim)(int *a1, char *a2, int a3, int a4, float a5);

#endif //PVZ_TV_1_1_5_REANIMATIONINGAMEFUNCTION_H
