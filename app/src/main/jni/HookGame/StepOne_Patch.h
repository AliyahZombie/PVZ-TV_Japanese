//
// Created by Homura on 2023/5/18.
//

#ifndef PVZ_TV_TOUCH_STEPONE_PATCH_H
#define PVZ_TV_TOUCH_STEPONE_PATCH_H

#include "../KittyMemory/MemoryPatch.h"
#include "../Includes/Utils.h"

#define targetLibName "libGameMain.so"

struct Game_Patches {
    MemoryPatch
//    RemoveSessionTaskFailedDialog,
//    RepairZombiesWon,
    RepairShopA,
    RepairShopB,
    ShowShovel,
    ShowNewOptions,
//    IZombieBrainFix,
    UsefulSeedPacketAutoPickupDisable,
    ProjectilePierce,
//    ZombiesWonDecay1_10,
//    ZombiesWonDecay2_10,
//    ZombiesWonDecay3_10,
//    ZombiesWonDecay4_10,
//    ZombiesWonDecay1_20,
//    ZombiesWonDecay2_20,
//    ZombiesWonDecay3_20,
//    ZombiesWonDecay4_20,
//    ZombiesWonDecay1_30,
//    ZombiesWonDecay2_30,
//    ZombiesWonDecay3_30,
//    ZombiesWonDecay4_30,
//    ZombiesWonDecay1_40,
//    ZombiesWonDecay2_40,
//    ZombiesWonDecay3_40,
//    ZombiesWonDecay4_40,
//        FogFix,

//    ImitaterChooseFix,
    ManualCollection;
//    ElevenSeedPacket;

} GamePatches;

bool IsPatched = false;
bool enableManualCollect = false;
bool enableNewOptionsDialog = false;

void StepOnePatchGame(){
    if (!IsPatched) {
//        GamePatches.RemoveSessionTaskFailedDialog = MemoryPatch::createWithHex(targetLibName,string2Offset("0x2B2B74"),"70 47");
//        GamePatches.RemoveSessionTaskFailedDialog.Modify();
//        GamePatches.RepairZombiesWon = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1B8E4C"),"04 E0");
//        GamePatches.RepairZombiesWon.Modify();
        GamePatches.RepairShopA = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1C3B06"),"05 E0");
        GamePatches.RepairShopA.Modify();
        GamePatches.RepairShopB = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1C3C6C"),"06 E0");
        GamePatches.RepairShopB.Modify();
        GamePatches.ShowShovel = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1C23D2"),"05 2A 00 F3 ED 81");
        GamePatches.ShowShovel.Modify();
        GamePatches.UsefulSeedPacketAutoPickupDisable = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1C6068"),"99");
        GamePatches.UsefulSeedPacketAutoPickupDisable.Modify();

//        GamePatches.ZombiesWonDecay1_10 = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1B8DCA"),"6D");
//        GamePatches.ZombiesWonDecay2_10 = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1B8E20"),"86");
//        GamePatches.ZombiesWonDecay3_10 = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1B8E12"),"59");
//        GamePatches.ZombiesWonDecay4_10 = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1B8E16"),"3B");
//
//        GamePatches.ZombiesWonDecay1_20 = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1B8DCA"),"77");
//        GamePatches.ZombiesWonDecay2_20 = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1B8E20"),"90");
//        GamePatches.ZombiesWonDecay3_20 = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1B8E12"),"63");
//        GamePatches.ZombiesWonDecay4_20 = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1B8E16"),"45");
//
//        GamePatches.ZombiesWonDecay1_30 = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1B8DCA"),"81");
//        GamePatches.ZombiesWonDecay2_30 = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1B8E20"),"9A");
//        GamePatches.ZombiesWonDecay3_30 = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1B8E12"),"6D");
//        GamePatches.ZombiesWonDecay4_30 = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1B8E16"),"4F");
//
//        GamePatches.ZombiesWonDecay1_40 = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1B8DCA"),"8B");
//        GamePatches.ZombiesWonDecay2_40 = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1B8E20"),"A4");
//        GamePatches.ZombiesWonDecay3_40 = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1B8E12"),"77");
//        GamePatches.ZombiesWonDecay4_40 = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1B8E16"),"59");

        GamePatches.ProjectilePierce = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1958DC"),"00 BF 70 47");
        GamePatches.ShowNewOptions = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1439CA"),"4F F0 01 00");
        GamePatches.ManualCollection = MemoryPatch::createWithHex(targetLibName,string2Offset("0x19B15A"),"00 BF 00 BF");
        if (enableNewOptionsDialog){
            GamePatches.ShowNewOptions.Modify();
        }
        if (enableManualCollect){
            GamePatches.ManualCollection.Modify();
        }
        IsPatched = true;
    }
}




#endif //PVZ_TV_TOUCH_STEPONE_PATCH_H
