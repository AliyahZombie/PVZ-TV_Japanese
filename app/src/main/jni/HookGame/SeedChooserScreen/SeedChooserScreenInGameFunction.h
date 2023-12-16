//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_SEEDCHOOSERSCREENINGAMEFUNCTION_H
#define PVZ_TV_1_1_5_SEEDCHOOSERSCREENINGAMEFUNCTION_H

int (*SeedChooserScreen_ClickedSeedInBank)(int *a1, int *a2, unsigned int a3);

int (*SeedChooserScreen_GameButtonDown)(int *a1, int a2, unsigned int a3);

int (*SeedChooserScreen_CloseSeedChooser)(int *a);

int (*SeedChooserScreen_FindSeedInBank)(int *a1, int a2, int a3);

int (*SeedChooserScreen_HasPacket)(int *a, int a2, bool a3);

bool (*SeedChooserScreen_Has7Rows)(void *instance);

#endif //PVZ_TV_1_1_5_SEEDCHOOSERSCREENINGAMEFUNCTION_H
