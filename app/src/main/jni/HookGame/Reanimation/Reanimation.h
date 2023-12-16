//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_REANIMATION_H
#define PVZ_TV_1_1_5_REANIMATION_H

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;

void Reanimation_OverrideScale(int ream, float a2, float a3) {
    int v3; // r3
    v3 = *(_DWORD *) (ream + 188);
    *(_BYTE *) (ream + 208) = 0;
    *(float *) (ream + 52) = a2;
    *(float *) (ream + 68) = a3;
    *(_DWORD *) (ream + 188) = v3 | 2;
}

int Reanimation_SetPosition(int a, float a2, float a3) {
    int v3; // r3

    v3 = *(_DWORD *) (a + 188);
    *(_BYTE *) (a + 208) = 0;
    *(float *) (a + 60) = a2;
    *(float *) (a + 72) = a3;
    *(_DWORD *) (a + 188) = v3 | 2;
    return a;
}
#endif //PVZ_TV_1_1_5_REANIMATION_H
