//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_MAINMENUINGAMEFUNCTION_H
#define PVZ_TV_1_1_5_MAINMENUINGAMEFUNCTION_H

bool (*MainMenu_InTransition)(int *instance);

int (*MainMenu_SetScene)(int *instance, int scene);

void (*MainMenu_StartAdventureMode)(int *);


#endif //PVZ_TV_1_1_5_MAINMENUINGAMEFUNCTION_H
