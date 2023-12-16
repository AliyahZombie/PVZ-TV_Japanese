//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_LAWNAPPINGAMEFUNCTION_H
#define PVZ_TV_1_1_5_LAWNAPPINGAMEFUNCTION_H

int (*LawnApp_KillChallengeScreen)(int lawnApp);

int (*LawnApp_KillMainMenu)(int lawnApp);

int (*LawnApp_KillNewOptionsDialog)(int lawnApp);

int (*LawnApp_PreNewGame)(int lawnApp, int a2, int a3);

int (*LawnApp_CanShowStore)(int* lawnApp);

int (*LawnApp_CanShowAlmanac)(int* lawnApp);

int (*LawnApp_IsScaryPotterLevel)(int *lawnApp);

int (*LawnApp_IsWhackAZombieLevel)(int *lawnApp);

int (*LawnApp_PlayFoley)(int lawnApp, int theFoleyType);

int (*LawnApp_DoCheatDialog)(int* lawnApp);

int (*LawnApp_DoCheatCodeDialog)(int* lawnApp);

int (*LawnApp_DoUserDialog)(int *lawnApp);

int (*LawnApp_ReanimationTryToGet)(int lawnApp, int a2);

int (*LawnApp_ClearSecondPlayer)(int *lawnApp);

bool (*LawnApp_IsFirstTimeAdventureMode)(int *lawnApp);

bool (*LawnApp_IsAdventureMode)(int *lawnApp);

bool (*LawnApp_IsCoopMode)(int *lawnApp);

int (*LawnApp_ReanimationGet)(int *lawnApp, int theReanimationId);

//阻塞式函数，能创建并立即展示一个带按钮的对话框。按钮个数由最后一个参数决定。其返回值就是用户按下的按钮ID，一般情况下只可能为1000或1001。
int (*LawnApp_LawnMessageBox)(int *lawnApp,
                              int theDialogId,//用于标识本对话框的ID，以便于用KillDialog(theDialogId)关闭此对话框。一般用不到，所以随便填个数字就可以。
                              const char *theHeaderName,
                              const char *theLinesName,
                              const char *theButton1Name,
                              const char *theButton2Name,
                              int theButtonMode);//取值为0，1，2，3。其中0就是无按钮；1和2会展示两个按钮，其ID分别为1000和1001；3只会展示一个按钮，其ID为1000。

bool (*LawnApp_IsIZombieLevel)(int* lawnApp);
#endif //PVZ_TV_1_1_5_LAWNAPPINGAMEFUNCTION_H
