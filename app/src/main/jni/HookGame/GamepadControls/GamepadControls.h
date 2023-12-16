//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_GAMEPADCONTROLS_H
#define PVZ_TV_1_1_5_GAMEPADCONTROLS_H

#include "../Board/Board.h"

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;

void GamepadControls_pickUpCobCannon(int gamePad, int cobCannon) {
    // 用于拿起指定的加农炮
    int v8; // r6
    int v9; // r1
    int *v10; // r0
    int v11; // r3
    int v12; // r3
    int v13; // r7
    int v14; // r6
    int v15; // r1
    int v16; // s14
    int v17; // s15
    _DWORD *v18; // r3
    int v19; // r3

    v8 = 0;
    v9 = *((_DWORD *) gamePad + 37);
    v10 = (int *) *((_DWORD *) gamePad + 14);
    if (v9)
        v11 = 140;
    else
        v11 = 141;
    v12 = *((_DWORD *) v10 + v11);
    if (*(_DWORD *) (v12 + 152) != -1) {
        if (*(_BYTE *) (v12 + 200)) {
            v19 = *(_DWORD *) (v12 + 196);
            if (v19) {
                if ((unsigned int) (unsigned int) v19 < *((_DWORD *) v10 + 79)) {
                    if (v19 ==
                        *(_DWORD *) (*((_DWORD *) v10 + 77) + 352 * (unsigned int) v19 + 348))
                        v8 = *((_DWORD *) v10 + 77) + 352 * (unsigned int) v19;
                    else
                        v8 = 0;
                }
            } else {
                v8 = 0;
            }
        } else {
            v8 = *(_BYTE *) (v12 + 200);
        }
    }
    v13 = cobCannon;
    if (cobCannon != v8 && *(_DWORD *) (cobCannon + 76) == 37 && *((_DWORD *) gamePad + 24) != 8) {
        v14 = *((_BYTE *) gamePad + 200);
        if (!*((_BYTE *) gamePad + 200)) {
            Board_ClearCursor(v10, v9);
            v15 = *(_DWORD *) (v13 + 348);
            v16 = (int) *((float *) gamePad + 27);
            v17 = (int) *((float *) gamePad + 28);
            v18 = (_DWORD *) (*((_DWORD *) gamePad + 14) + 22528);
            v18[29] = 30;
            v18[30] = v16;
            v18[31] = v17;
            *((_DWORD *) gamePad + 49) = v15;
            *((_DWORD *) gamePad + 55) = v14;
            *((_BYTE *) gamePad + 200) = 1;
        }
    }
}

void GamepadControls_InvalidatePreviewReanim(int *a) {}

int (*old_GamepadControls_Draw)(int *gamePad, int *graphics);

int GamepadControls_Draw(int *gamePad, int *graphics) {
    //实现在光标内绘制铲子和黄油手套(黄油手套其实就是花园的手套)
    if (requestDrawShovelInCursor) {
        int *board = (int *) *((int *) gamePad + 14);
        int cursorObject_1P = *((_DWORD *) board + 142);
        *(_DWORD *) (cursorObject_1P + 64) = 6;
        *(int *) (cursorObject_1P + 24) = *(float *) ((int) gamePad + 108) - 20;
        *(int *) (cursorObject_1P + 28) = *(float *) ((int) gamePad + 112) - 20;
    }
    if (requestDrawButterInCursor) {
        if (gameIndex < 79 || gameIndex > 89) requestDrawButterInCursor = false;
        int *board = (int *) *((int *) gamePad + 14);
        int cursorObject_2P = *((_DWORD *) board + 143);
        *(_DWORD *) (cursorObject_2P + 64) = 14;
        *(int *) (cursorObject_2P + 24) = *(float *) ((int) gamePad + 108);
        *(int *) (cursorObject_2P + 28) = *(float *) ((int) gamePad + 112);
    }
    return old_GamepadControls_Draw(gamePad, graphics);
}

void (*old_GamepadControls_DrawPreview)(int *gamePad, int *graphics);

void GamepadControls_DrawPreview(int *gamePad, int *graphics) {
    //试图修复排山倒海不显示植物预览的问题。效果极差。
    int *gamePadApp = (int *) *((_DWORD *) gamePad + 5);
    int gameState = *(int *) (gamePad + 0x60);
    if (gameState != 7) {
        return;
        return old_GamepadControls_DrawPreview(gamePad, graphics);
    }
    bool tmp1 = *((_BYTE *) gamePadApp + 2200);
    bool tmp2 = *((_BYTE *) gamePadApp + 2201);
    bool tmp3 = *((_BYTE *) gamePadApp + 2109);
    *((_BYTE *) gamePadApp + 2200) = true;
    *((_BYTE *) gamePadApp + 2201) = true;
    *((_BYTE *) gamePadApp + 2109) = true;
    old_GamepadControls_DrawPreview(gamePad, graphics);
    *((_BYTE *) gamePadApp + 2200) = false;
    *((_BYTE *) gamePadApp + 2201) = false;
    *((_BYTE *) gamePadApp + 2109) = false;
    *(int *) (gamePad + 0x60) = 7;
}

#endif //PVZ_TV_1_1_5_GAMEPADCONTROLS_H
