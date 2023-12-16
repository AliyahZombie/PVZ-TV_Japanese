//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_SEEDPACKET_H
#define PVZ_TV_1_1_5_SEEDPACKET_H

#include "../Graphics/GraphicsInGameFunction.h"
#include "../SpecialConstraints.h"

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;

void (*old_SeedPacket_Update)(int *seedPacket);

void SeedPacket_Update(int *seedPacket) {
    if (CoolDownSeedPacketButt) {
        *(_BYTE *) ((uintptr_t) seedPacket + 88) = 1;//mActive
        *(_BYTE *) ((uintptr_t) seedPacket + 89) = 0;
    }
    if (requestPause) {
        int v3 = *(_DWORD *) (*((_DWORD *) seedPacket + 4) + CUTSCENE_NOWGAMESTATE_OFFSET);
        if (v3 == 3 && *((_DWORD *) seedPacket + 17) != -1)
            *((_DWORD *) seedPacket + 13) = *((_DWORD *) seedPacket + 13) - 1;
    }
    return old_SeedPacket_Update(seedPacket);
}


bool SeedPacket_GetPlayerIndex(int *a) {
    return *((_DWORD *) a + 24) != *(_DWORD *) (*((_DWORD *) a + 5) + 524);
}

void (*old_SeedPacket_UpdateSelected)(int *seedPacket);

void SeedPacket_UpdateSelected(int *seedPacket) {
    int *lawnApp = (int *) *((_DWORD *) seedPacket + 4);
    int nowGameIndex = *(lawnApp + LAWNAPP_GAMEINDEX_OFFSET);
    if (nowGameIndex >= 76 && nowGameIndex <= 89) {
        //如果是双人模式关卡(对战或结盟)，则使用下面的逻辑来更新当前选中的卡片。用于修复1P和2P的卡片选择框同时出现在两个人各自的植物栏里(也就是植物栏一共出现四个选择框)的问题。
        int *v1 = (int *) *((_DWORD *) seedPacket + 5);
        int v2 = v1[140];
        int v3 = v1[141];
        int selection1P = *(_DWORD *) (v2 + 180);
        int selection2P = *(_DWORD *) (v3 + 180);
        int seedPacketIndex = *((_DWORD *) seedPacket + 15);
        bool playerIndex = SeedPacket_GetPlayerIndex(seedPacket);
        bool selectedBy1P = playerIndex == 0 && seedPacketIndex == selection1P;
        bool selectedBy2P = playerIndex == 1 && seedPacketIndex == selection2P;

        *((_BYTE *) seedPacket + 113) = selectedBy1P || selectedBy2P;
        *((_BYTE *) seedPacket + 112) = selectedBy2P;
        return;
    }
    return old_SeedPacket_UpdateSelected(seedPacket);
}

bool showCoolDown = false;

void (*old_SeedPacket_DrawOverlay)(int *seedPacket, int *graphics);

void SeedPacket_DrawOverlay(int *seedPacket, int *graphics) {
    //绘制卡片冷却进度倒计时
    old_SeedPacket_DrawOverlay(seedPacket, graphics);
    int *lawnApp = (int *) *((_DWORD *) seedPacket + 4);
    int nowGameIndex = *(lawnApp + LAWNAPP_GAMEINDEX_OFFSET);
    if (showCoolDown || nowGameIndex == 76) {//如果玩家开启了“显示冷却倒计时”，或者当前为对战关卡(代号76)，则绘制倒计时
        if (!*(_BYTE *) ((uintptr_t) seedPacket + 88)) {
            int holder[16];
            int coolDownRemaining = *((_DWORD *) seedPacket + 14) - *((_DWORD *) seedPacket + 13);
            Sexy_StrFormat((int *) holder, "%1.1f", coolDownRemaining / 100.0f);
            Sexy_Graphics_SetColor(graphics, SeedPacket_GetPlayerIndex(seedPacket) ? yellow : blue);
            Sexy_Graphics_SetFont((int) graphics, (int *) *Sexy_FONT_DWARVENTODCRAFT18_Addr);
            Sexy_Graphics_DrawString(graphics, (int) holder, coolDownRemaining < 1000 ? 10 : 0, 39);
            Sexy_Graphics_SetFont((int) graphics, NULL);
        }
    }
}

//void (*old_ShopSeedPacket_Update)(int *);
//
//void ShopSeedPacket_Update(int *a) {
//    if (elevenSeeds) { return; }
//    return old_ShopSeedPacket_Update(a);
//}

#endif //PVZ_TV_1_1_5_SEEDPACKET_H
