//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_PLANTINGAMEFUNCTION_H
#define PVZ_TV_1_1_5_PLANTINGAMEFUNCTION_H


int (*Plant_Die)(void *instance);

int *(*Plant_GetImage)(int seedType);

void (*Plant_GetPlantRect)(char* rect,unsigned int plant);

bool(*Plant_NotOnGround)(unsigned int plant);

#endif //PVZ_TV_1_1_5_PLANTINGAMEFUNCTION_H
