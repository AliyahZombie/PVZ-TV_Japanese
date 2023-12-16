//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_GRIDITEM_H
#define PVZ_TV_1_1_5_GRIDITEM_H

#include "../GlobalVariable.h"
#include "../SpecialConstraints.h"
#include "../Graphics/GraphicsInGameFunction.h"
#include "../Challenge/Challenge.h"
#include "../Board/BoardInGameFunction.h"
#include "../Reanimation/Reanimation.h"
#include "../MiscInGameFunction.h"

int GridItem_DrawScaryPot(int *a, int *graphics) {
    //前半段是从IDA Pro直接复制过来的一些TV1.0.1的代码，后半段是参照WP版源代码自己写的

    int mSeedType;
    int mZombieType;
    int num6;
    float v12; // s15
    float v13; // s14
    float tmpTransX;
    float tmpTransY;
    char newReanim[264]; // [sp+30h] [bp-108h] BYREF
    char newGraphics[16]; // [sp+F4h] [bp-B4h] BYREF

    int num = *((_DWORD *) a + 7) - 3;
    int num2 = Board_GridToPixelX(*((int **) a + 5), *((_DWORD *) a + 8), *((_DWORD *) a + 9)) - 5;
    int num3 = Board_GridToPixelY(*((int **) a + 5), *((_DWORD *) a + 8), *((_DWORD *) a + 9)) - 15;
    TodDrawImageCelCenterScaledF(graphics, (int *) *Sexy_IMAGE_PLANTSHADOW2_Addr,
                                 (float) num2 - 5.0, (float) num3 + 72.0, 0, 1.3, 1.3);


    if (Challenge_ScaryPotterCountSunInPot(*(int **) (*((_DWORD *) a + 5) + 596),
                                           a) > 0) {
        //照透阳光罐子不知为什么会闪退，所以这里判断下是不是阳光罐子
        *((_BYTE *) a + 88) = *((int *) a + 23) > 0;//如果罐子要被照透(透明度不为0)，则将罐子高亮
        *((int *) a + 23) = 0;//并取消罐子的照透(透明度赋为0)
    }


    if (*((int *) a + 23) > 0) {//如果罐子要被照透(透明度不为0)
        Sexy_Graphics_DrawImageCel(graphics, (int *) *Sexy_IMAGE_SCARY_POT_Addr, num2, num3, num,
                                   0);
        Sexy_Graphics_Graphics((int *) newGraphics, graphics);
        int mScaryPotType = *((_DWORD *) a + 21);
        switch (mScaryPotType) {
            case 1://罐子内装着植物
                mSeedType = *((_DWORD *) a + 20);
                *((float *) newGraphics + 4) = 0.7f;
                *((float *) newGraphics + 5) = 0.7f;
                tmpTransX = *((float *) newGraphics + 2);
                tmpTransY = *((float *) newGraphics + 3);
                *((float *) newGraphics + 2) += (float) num2 + 23;
                *((float *) newGraphics + 3) += (float) num3 + 33;
                DrawSeedPacket((float *) newGraphics, num2 + 23, num3 + 33, mSeedType, -1, 0.0, 255,
                               0, 0, 0, 1);
                *((float *) newGraphics + 2) = tmpTransX;
                *((float *) newGraphics + 3) = tmpTransY;
                break;
            case 2://罐子内装着僵尸
                mZombieType = *((_DWORD *) a + 19);
                *((float *) newGraphics + 4) = 0.4f;
                *((float *) newGraphics + 5) = 0.4f;
                if (mZombieType == 7) {
                    v12 = 16.0;
                    v13 = 1.0;
                } else if (mZombieType == 23) {
                    v12 = 26.0;
                    v13 = 15.0;
                    *((float *) newGraphics + 4) = 0.3f;
                    *((float *) newGraphics + 5) = 0.3f;
                } else {
                    v12 = 19.0;
                    v13 = 6.0;
                }
                ReanimatorCache_DrawCachedZombie(
                        *(_DWORD *) (*((_DWORD *) a + 4) + LAWNAPP_REANIMATORCACHE_OFFSET),
                        (int *) newGraphics,
                        v13 + num2, v12 + num3, mZombieType);
                break;
            case 3://罐子内装着阳光
                num6 = Challenge_ScaryPotterCountSunInPot(*(int **) (*((_DWORD *) a + 5) + 596),
                                                          a);
                Reanimation_Reanimation((int *) newReanim);
                Reanimation_ReanimationInitializeType((int *) newReanim, 0, 0, 22);
                Reanimation_OverrideScale((int) newReanim, 0.5f, 0.5f);


                for (int i = 0; i < num6; i++) {
                    float num7 = 42.0f;
                    float num8 = 62.0f;
                    switch (i) {
                        case 1:
                            num7 += 3.0f;
                            num8 += -20.0f;
                            break;
                        case 2:
                            num7 += -6.0f;
                            num8 += -10.0f;
                            break;
                        case 3:
                            num7 += 6.0f;
                            num8 += -5.0f;
                            break;
                        case 4:
                            num7 += 5.0f;
                            num8 += -15.0f;
                            break;
                    }
                    Reanimation_SetPosition((int) newReanim, num2 + num7, num3 + num8);
                    Reanimation_Draw((int *) newReanim, graphics);
                }
                Reanimation_PrepareForReuse((int *) newReanim);
                break;
        }
        int theAlpha = TodAnimateCurve(0, 50, *((_DWORD *) a + 23), 255, 58, 1);
        Sexy_Graphics_SetColorizeImages((int) graphics, 1);
        int theColor[4] = {255, 255, 255, theAlpha};
        Sexy_Graphics_SetColor(graphics, theColor);
        Sexy_Graphics_PrepareForReuse((int *) newGraphics);
    }
//    int *tmpImage = FilterEffectCreateImage((int *) Get_Sexy_IMAGE_SCARY_POT(), 1);
//    Sexy_Graphics_DrawImageCel(graphics, tmpImage, num2, num3, num, 1);
    Sexy_Graphics_DrawImageCel(graphics, (int *) *Sexy_IMAGE_SCARY_POT_Addr, num2, num3, num, 1);
    if (*((_BYTE *) a + 88)) {
        Sexy_Graphics_SetDrawMode((int) graphics, 1);
        Sexy_Graphics_SetColorizeImages((int) graphics, 1);
        if (!*((_DWORD *) a + 23)) {
            int theColor[4] = {255, 255, 255, 196};
            Sexy_Graphics_SetColor(graphics, theColor);
        }
        Sexy_Graphics_DrawImageCel(graphics, (int *) *Sexy_IMAGE_SCARY_POT_Addr, num2, num3, num,
                                   1);
        Sexy_Graphics_SetDrawMode((int) graphics, 0);
    }
    return Sexy_Graphics_SetColorizeImages((int) graphics, 0);
}

void (*old_GridItem_Update)(int *a1);

void GridItem_Update(int *a1) {
    if (requestPause) {
        //如果开了高级暂停
        return;
    }
    old_GridItem_Update(a1);
}

void (*old_GridItem_UpdateScaryPot)(int *a);

bool transparentVase = false;

void GridItem_UpdateScaryPot(int *a) {
    old_GridItem_UpdateScaryPot(a);
    if (transparentVase) {//如果玩家开启“罐子透视”
        int mTransparentCounter = *((int *) a + 23);
        if (mTransparentCounter < 50) {
            //透明度如果小于50，则为透明度加2
            *((int *) a + 23) = mTransparentCounter + 2;
        }
    }
}

void (*old_GridItem_DrawStinky)(int *a, int *graphics);

void GridItem_DrawStinky(int *mStinky, int *graphics) {
    // 在玩家选取巧克力时，高亮显示光标下方且没喂巧克力的Stinky。
    // 从而修复Stinky无法在醒着时喂巧克力、修复Stinky在喂过巧克力后还能继续喂巧克力。
    // 因为游戏通过Stinky是否高亮来判断是否能喂Stinky。这个机制是为鼠标操作而生，但渡维不加改动地将其用于按键操作，导致无法在Stinky醒着时喂它。
    int *board = *((int **) mStinky + 5);
    int gamePad = *((_DWORD *) board + 140);
    int mCursorX = *(float *) (gamePad + 108);
    int mCursorY = *(float *) (gamePad + 112);
    int mCursorGridX = Board_PixelToGridX(board, mCursorX, mCursorY);
    int mCursorGridY = Board_PixelToGridY(board, mCursorX, mCursorY);
    float mStinkyX = *((float *) mStinky + 13);
    float mStinkyY = *((float *) mStinky + 14);
    int mStinkyGridX = Board_PixelToGridX(board, (int) mStinkyX, (int) mStinkyY);
    int mStinkyGridY = Board_PixelToGridY(board, (int) mStinkyX, (int) mStinkyY);
    if (mStinkyGridX != mCursorGridX || mStinkyGridY != mCursorGridY) {
        //如果Stinky不在光标位置处，则取消高亮。
        *((_BYTE *) mStinky + 88) = false;
        return old_GridItem_DrawStinky(mStinky, graphics);
    }
    //如果Stinky在光标位置处
    int cursorObject = *((_DWORD *) board + 142);
    int mCursorType = *(_DWORD *) (cursorObject + 64);
    if (mCursorType == 13) {
        //如果光标类型为巧克力
        int *mZenGarden = *(int **) (board[69] + LAWNAPP_ZENGARDEN_OFFSET);
        bool isStinkyHighOnChocolate = ZenGarden_IsStinkyHighOnChocolate(mZenGarden);
        *((_BYTE *) mStinky + 88) = !isStinkyHighOnChocolate; //为没喂巧克力的Stinky加入高亮效果
    }
    return old_GridItem_DrawStinky(mStinky, graphics);
}

#endif //PVZ_TV_1_1_5_GRIDITEM_H
