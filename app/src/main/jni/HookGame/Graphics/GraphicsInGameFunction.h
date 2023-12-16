//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_GRAPHICSINGAMEFUNCTION_H
#define PVZ_TV_1_1_5_GRAPHICSINGAMEFUNCTION_H
typedef unsigned int _DWORD;
typedef unsigned char _BYTE;

inline int Sexy_Graphics_SetDrawMode(int a, int a2) {
    *(_DWORD *) (a + 96) = a2;
    return a;
}

inline int Sexy_Graphics_SetColorizeImages(int a, bool a2) {
    *(_BYTE *) (a + 100) = a2;
    return a;
}

inline int Sexy_Graphics_SetFont(int a, int *a2) {
    *(_DWORD *) (a + 92) = (_DWORD) a2;
    return a;
}

void (*Sexy_Graphics_FillRect)(int *graphics, int *rect);

int (*Sexy_Graphics_DrawString)(int *a1, int a2, int a3, int a4);

void (*Sexy_Graphics_DrawImage)(int* a1, int *a2, int a3, int a4);

int (*Sexy_Graphics_DrawImageCel)(int *a1, int *a2, int a3, int a4, int a5, int a6);

int (*Sexy_Graphics_DrawImageCel2)(int *a1, int *a2, int a3, int a4, int a5);

int *(*Sexy_Graphics_Graphics)(int *a1, const int *a2);

void (*Sexy_Graphics_PrepareForReuse)(int *a);

int (*Sexy_Graphics_SetColor)(int *a, int *a2);

int black[4] = {80, 80, 80, 255};

int white[4] = {255, 255, 255, 255};

int blue[4] = {0, 255, 255, 255};

int yellow[4] = {255, 255, 0, 255};

#endif //PVZ_TV_1_1_5_GRAPHICSINGAMEFUNCTION_H
