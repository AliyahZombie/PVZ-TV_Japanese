#ifndef PVZ_TV_1_1_5_HOOKGAME_H
#define PVZ_TV_1_1_5_HOOKGAME_H

#include "HookAddr.h"
#include "Board/Board.h"
#include "Graphics/GraphicsInGameFunction.h"
#include "LawnApp/LawnApp.h"
#include "Challenge/Challenge.h"
#include "Plant/Plant.h"
#include "SeedPacket/SeedPacket.h"
#include "SeedChooserScreen/SeedChooserScreen.h"
#include "Reanimation/Reanimation.h"
#include "Zombie/Zombie.h"
#include "VSSetupMenu/VSSetupMenu.h"
#include "MainMenu/MainMenu.h"
#include "Projectile/Projectile.h"
#include "Coin/Coin.h"
#include "GamepadControls/GamepadControls.h"
#include "Misc.h"
#include "GridItem/GridItem.h"
#include "ChangeFormation.h"
#include "StepOne_Patch.h"
#include <Substrate/SubstrateHook.h>
#include <Substrate/CydiaSubstrate.h>

#define targetLibName "libGameMain.so"

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;



//int (*old_Plant_UpdateReanim)(int *a1);
//
//int Plant_UpdateReanim(int *a1) {
//    if (requestDrawShovelInCursor && a1 == (int *) plantUnderShovel && a1) {
//        int newReam = LawnApp_ReanimationTryToGet(*((_DWORD *) plantUnderShovel + 4),
//                                                  *((_DWORD *) plantUnderShovel + 41));
//        if (newReam) {
//            Reanimation_OverrideScale(newReam, 1.1f, 1.1f);
//        }
//        return newReam;
//    }
//    return old_Plant_UpdateReanim(a1);
//}

//int Sexy_GamepadApp_CheckGamepad(int *a1) {
//    return true;
//}
//
//int Sexy_GamepadApp_HasGamepad(int *a1) {
//    if (gameIndex == 44 || gameIndex == 51) {
//        return false;
//    }
//    return true;
//}



void InitInGameFunction() {
    Board_Move = (void (*)(int *, int, int)) Board_MoveAddr;
    Board_ProgressMeterHasFlags = (bool (*)(int *)) Board_ProgressMeterHasFlagsAddr;
    Board_IsSurvivalStageWithRepick = (bool (*)(int *)) Board_IsSurvivalStageWithRepickAddr;
    Board_PickUpTool = (void (*)(int *, int, int)) Board_PickUpToolAddr;
    Board_IteratePlants = (bool (*)(int, unsigned int *)) Board_IteratePlantsAddr;
    Board_IterateProjectiles = (bool (*)(int, unsigned int *)) Board_IterateProjectilesAddr;
    Board_IterateGridItems = (bool (*)(int, unsigned int *)) Board_IterateGridItemsAddr;
    Board_IterateZombies = (bool (*)(int, unsigned int *)) Board_IterateZombiesAddr;
    Board_AddProjectile = (int (*)(int, int, int, int, int, int)) Board_AddProjectileAddr;
    Board_GameAxisMove = (int (*)(int *, int, int, int)) Board_GameAxisMoveAddr;
    Board_InitCoverLayer = (int (*)(int *)) Board_InitCoverLayerAddr;
    Board_LoadBackgroundImages = (int (*)(int *)) Board_LoadBackgroundImagesAddr;
    Board_HasConveyorBeltSeedBank = (int (*)(int *, int)) Board_HasConveyorBeltSeedBankAddr;
    Board_UpdateGridItems = (int (*)(int *)) Board_UpdateGridItemsAddr;
    Board_ZombieHitTest = (int *(*)(int *, int, int, int)) Board_ZombieHitTestAddr;
    Board_GetTopPlantAt = (int (*)(int *, unsigned int, unsigned int, int)) Board_GetTopPlantAtAddr;
    Board_NewPlant = (int (*)(int *, int, int, int, int, int)) Board_NewPlantAddr;
    Board_CanUseGameObject = (int (*)(int *, int)) Board_CanUseGameObjectAddr;
    Board_MouseHitTest = (int (*)(void *, int, int, int *, bool)) Board_MouseHitTestAddr;
    Board_ToolHitTest = (int (*)(int *, int, int)) Board_ToolHitTestAddr;
    Board_RefreshSeedPacketFromCursor = (int (*)(void *,
                                                 int)) Board_RefreshSeedPacketFromCursorAddr;
    Board_GetPlantsOnLawn = (int (*)(int, unsigned int, unsigned int,
                                     int *)) Board_GetPlantsOnLawnAddr;
    Board_GridToPixelX = (int (*)(void *, unsigned int, unsigned int)) Board_GridToPixelXAddr;
    Board_GridToPixelY = (int (*)(void *, unsigned int, unsigned int)) Board_GridToPixelYAddr;
    Board_PixelToGridY = (int (*)(void *, unsigned int, unsigned int)) Board_PixelToGridYAddr;
    Board_PixelToGridX = (int (*)(void *, unsigned int, unsigned int)) Board_PixelToGridXAddr;
    Board_AddALadder = (unsigned int (*)(void *, int, int)) Board_AddALadderAddr;
    Board_ClearCursor = (int (*)(int *, int)) Board_ClearCursorAddr;
    Board_MouseDownWithTool = (int (*)(int *, int, int, int, int, int)) Board_MouseDownWithToolAddr;
    Board_CountPlantByType = (int (*)(int *, int)) Board_CountPlantByTypeAddr;
    Board_SetTutorialState = (int (*)(int *, int)) Board_SetTutorialStateAddr;
    Board_DoFwoosh = (void (*)(int, int)) Board_DoFwooshAddr;
    Board_ShakeBoard = (void (*)(int, int, int)) Board_ShakeBoardAddr;

    LawnApp_ClearSecondPlayer = (int (*)(int *)) LawnApp_ClearSecondPlayerAddr;
    LawnApp_IsWhackAZombieLevel = (int (*)(int *)) LawnApp_IsWhackAZombieLevelAddr;
    LawnApp_IsScaryPotterLevel = (int (*)(int *)) LawnApp_IsScaryPotterLevelAddr;
    LawnApp_CanShowStore = (int (*)(int *)) LawnApp_CanShowStoreAddr;
    LawnApp_CanShowAlmanac = (int (*)(int *)) LawnApp_CanShowAlmanacAddr;
    LawnApp_KillNewOptionsDialog = (int (*)(int)) LawnApp_KillNewOptionsDialogAddr;
    LawnApp_KillMainMenu = (int (*)(int)) LawnApp_KillMainMenuAddr;
    LawnApp_KillChallengeScreen = (int (*)(int)) LawnApp_KillChallengeScreenAddr;
    LawnApp_PreNewGame = (int (*)(int, int, int)) LawnApp_PreNewGameAddr;
    LawnApp_PlayFoley = (int (*)(int, int)) LawnApp_PlayFoleyAddr;
    LawnApp_DoCheatDialog = (int (*)(int *)) LawnApp_DoCheatDialogAddr;
    LawnApp_DoCheatCodeDialog = (int (*)(int *)) LawnApp_DoCheatCodeDialogAddr;
    LawnApp_DoUserDialog = (int (*)(int *)) LawnApp_DoUserDialogAddr;
    LawnApp_ReanimationTryToGet = (int (*)(int, int)) LawnApp_ReanimationTryToGetAddr;
    LawnApp_IsFirstTimeAdventureMode = (bool (*)(int *)) LawnApp_IsFirstTimeAdventureModeAddr;
    LawnApp_IsAdventureMode = (bool (*)(int *)) LawnApp_IsAdventureModeAddr;
    LawnApp_IsCoopMode = (bool (*)(int *)) LawnApp_IsCoopModeAddr;
    LawnApp_LawnMessageBox = (int (*)(int *, int, const char *, const char *, const char *,
                                      const char *, int)) LawnApp_LawnMessageBoxAddr;
    LawnApp_ReanimationGet = (int (*)(int *, int)) LawnApp_ReanimationGetAddr;


    Sexy_Graphics_FillRect = (void (*)(int *, int *)) Sexy_Graphics_FillRectAddr;
    Sexy_Graphics_DrawString = (int (*)(int *, int, int, int)) Sexy_Graphics_DrawStringAddr;
    Sexy_Graphics_DrawImageCel = (int (*)(int *, int *, int, int, int,
                                          int)) Sexy_Graphics_DrawImageCelAddr;
    Sexy_Graphics_Graphics = (int *(*)(int *, const int *)) Sexy_Graphics_GraphicsAddr;
    Sexy_Graphics_PrepareForReuse = (void (*)(int *)) Sexy_Graphics_PrepareForReuseAddr;
    Sexy_Graphics_SetColor = (int (*)(int *, int *)) Sexy_Graphics_SetColorAddr;
    Sexy_Graphics_DrawImage = (void (*)(int *, int *, int, int)) Sexy_Graphics_DrawImageAddr;


    Plant_GetImage = (int *(*)(int)) Plant_GetImageAddr;
    Plant_GetPlantRect = (void (*)(char *, unsigned int)) Plant_GetPlantRectAddr;
    Plant_NotOnGround = (bool (*)(unsigned int)) Plant_NotOnGroundAddr;
    FilterEffectCreateImage = (int *(*)(int *, int)) FilterEffectCreateImageAddr;
    GetRectOverlap = (int (*)(int *, int *)) GetRectOverlapAddr;

    Zombie_GetZombieRect = (void (*)(int *, int *)) Zombie_GetZombieRectAddr;
    Zombie_IsImmobilizied = (bool (*)(int *)) Zombie_IsImmobiliziedAddr;
    Zombie_EffectedByDamage = (bool (*)(unsigned int, int)) Zombie_EffectedByDamageAddr;
    Zombie_RemoveColdEffects = (void (*)(unsigned int)) Zombie_RemoveColdEffectsAddr;

    Projectile_GetProjectileRect = (void (*)(int *, int *)) Projectile_GetProjectileRectAddr;
    Sexy_StrFormat = (int *(*)(int *, const char *, ...)) Sexy_StrFormatAddr;
    TodDrawImageCelCenterScaledF = (int (*)(int *, int *, float, float, int, float,
                                            float)) TodDrawImageCelCenterScaledFAddr;
    DrawSeedPacket = (void (*)(float *, int, int, int, int, float, int, char, char, char,
                               char)) DrawSeedPacketAddr;
    ReanimatorCache_DrawCachedZombie = (int (*)(int, int *, float, float,
                                                int)) ReanimatorCache_DrawCachedZombieAddr;
    Reanimation_Reanimation = (void (*)(int *)) Reanimation_ReanimationAddr;
    Reanimation_ReanimationInitializeType = (int (*)(int *, float, float,
                                                     int)) Reanimation_ReanimationInitializeTypeAddr;
    Reanimation_Draw = (bool *(*)(int *, int *)) Reanimation_DrawAddr;
    Reanimation_PrepareForReuse = (void (*)(int *)) Reanimation_PrepareForReuseAddr;
    Reanimation_PlayReanim = (void (*)(int *, char *, int, int, float)) Reanimation_PlayReanimAddr;
    TodAnimateCurve = (int (*)(int, int, int, int, int, int)) TodAnimateCurveAddr;
    //    TodDrawString = (void (*)(int a1, std::string const &a2, int a3, int a4, int a5, char a6,
    //                             int a7, int a8, int a9, int a10)) TodDrawStringAddr;
    Reanimation_DrawRenderGroup = (int (*)(int, int *, int)) Reanimation_DrawRenderGroupAddr;
    SeedChooserScreen_ClickedSeedInBank = (int (*)(int *, int *,
                                                   unsigned int)) SeedChooserScreen_ClickedSeedInBankAddr;
    SeedBank_MouseHitTest = (int (*)(int *, int, int, int *)) SeedBank_MouseHitTestAddr;
    Zombie_ApplyButter = (int *(*)(int *)) Zombie_ApplyButterAddr;
    SeedChooserScreen_GameButtonDown = (int (*)(int *, int,
                                                unsigned int)) SeedChooserScreen_GameButtonDownAddr;
    SeedChooserScreen_CloseSeedChooser = (int (*)(int *a)) SeedChooserScreen_CloseSeedChooserAddr;
    Coin_Collect = (int (*)(int, int)) Coin_CollectAddr;
    GamepadControls_OnButtonUp = (int (*)(int, int, int,
                                          unsigned int)) GamepadControls_OnButtonUpAddr;
    GamepadControls_OnButtonDown = (int (*)(int, int, int,
                                            unsigned int)) GamepadControls_OnButtonDownAddr;
    VSSetupMenu_GameButtonDown = (void (*)(int *, int, unsigned int,
                                           int)) VSSetupMenu_GameButtonDownAddr;
    WaitForSecondPlayerDialog_GameButtonDown = (int (*)(int *, int,
                                                        int)) WaitForSecondPlayerDialog_GameButtonDownAddr;
    StoreScreen_SetSelectedSlot = (int (*)(int, int)) StoreScreen_SetSelectedSlotAddr;
    SeedChooserScreen_HasPacket = (int (*)(int *, int, bool)) SeedChooserScreen_HasPacketAddr;
    ChallengeScreen_SetScrollTarget = (int (*)(int *, int)) ChallengeScreen_SetScrollTargetAddr;
    CutScene_IsSurvivalRepick = (bool (*)(void *)) CutScene_IsSurvivalRepickAddr;
    SeedChooserScreen_Has7Rows = (bool (*)(void *instance)) SeedChooserScreen_Has7RowsAddr;
    Plant_Die = (int (*)(void *)) Plant_DieAddr;
    Attachment_AttachmentDie = (int (*)(int)) AttachmentDieAddr;
    Zombie_DieNoLoot = (int (*)(int)) Zombie_DieNoLootAddr;
    Zombie_ApplyBurn = (int (*)(int)) Zombie_ApplyBurnAddr;
    Zombie_StartEating = (void (*)(int *)) Zombie_StartEatingAddr;
    MainMenu_InTransition = (bool (*)(int *)) MainMenu_InTransitionAddr;
    MainMenu_SetScene = (int (*)(int *, int)) MainMenu_SetSceneAddr;
    Coin_Die = (int (*)(int)) Coin_DieAddr;
    GamepadControls_OnKeyDown = (int (*)(int, int, unsigned int)) GamepadControls_OnKeyDownAddr;
    CursorObject_Draw = (int (*)(int, int *)) CursorObject_DrawAddr;
    GamepadControls_GetSeedBank = (int (*)(int)) GamepadControls_GetSeedBankAddr;
    Projectile_Die = (void (*)(int *)) Projectile_DieAddr;
    ZenGarden_GetStinky = (int *(*)(int **)) ZenGarden_GetStinkyAddr;
    ZenGarden_IsStinkyHighOnChocolate = (bool (*)(int *)) ZenGarden_IsStinkyHighOnChocolateAddr;
    ReanimatorTransform_ReanimatorTransform = (void (*)(
            float *)) ReanimatorTransform_ReanimatorTransformAddr;
    Reanimation_FindTrackIndexById = (int (*)(int *, char *)) Reanimation_FindTrackIndexByIdAddr;
    Reanimation_GetCurrentTransform = (void (*)(int *, int,
                                                float *)) Reanimation_GetCurrentTransformAddr;
    GridItem_GridItemDie = (void (*)(unsigned int)) GridItem_GridItemDieAddr;
    LawnPlayerInfo_GetFlag = (int (*)(int *, int)) LawnPlayerInfo_GetFlagAddr;
    MainMenu_StartAdventureMode = (void (*)(int *)) MainMenu_StartAdventureModeAddr;
    Challenge_IZombieGetBrainTarget = (int *(*)(int *, int *)) Challenge_IZombieGetBrainTargetAddr;
    Challenge_IZombieScoreBrain = (void (*)(int *, int *)) Challenge_IZombieScoreBrainAddr;
    Zombie_TakeDamage = (void (*)(int *, int, unsigned int)) Zombie_TakeDamageAddr;
    LawnApp_IsIZombieLevel = (bool (*)(int *)) LawnApp_IsIZombieLevelAddr;
    Zombie_IsWalkingBackwards = (bool (*)(int *)) Zombie_IsWalkingBackwardsAddr;
    Board_GetButterButtonRect = (void (*)(int *, int *)) Board_GetButterButtonRectAddr;
    Board_GetShovelButtonRect = (void (*)(int *, int *)) Board_GetShovelButtonRectAddr;
    GetFlashingColor = (void (*)(int *, int, int)) GetFlashingColorAddr;
    Sexy_Graphics_DrawImageCel2 = (int (*)(int *, int *, int, int,
                                           int)) Sexy_Graphics_DrawImageCel2Addr;
}


void InitHookFunction() {
    MSHookFunction(LawnApp_OnSessionTaskFailedAddr, (void *) LawnApp_OnSessionTaskFailed, NULL);
    MSHookFunction(Board_UpdateAddr, (void *) Board_Update, (void **) &old_Board_Update);
    MSHookFunction(CutScene_UpdateAddr, (void *) CutScene_Update, (void **) &old_CutScene_Update);
    MSHookFunction(MainMenu_UpdateAddr, (void *) MainMenu_Update, (void **) &old_MainMenu_Update);
    MSHookFunction(SeedChooserScreen_EnableStartButtonAddr,
                   (void *) SeedChooserScreen_EnableStartButton,
                   (void **) &old_SeedChooserScreen_EnableStartButton);
    MSHookFunction(LawnApp_ShowAwardScreenAddr, (void *) LawnApp_ShowAwardScreen,
                   (void **) &old_LawnApp_ShowAwardScreen);
    MSHookFunction(LawnApp_KillAwardScreenAddr, (void *) LawnApp_KillAwardScreen,
                   (void **) &old_LawnApp_KillAwardScreen);
    MSHookFunction(Sexy_Dialog_AddedToManagerWidgetManagerAddr, (void *) SexyDialog_AddedToManager,
                   (void **) &old_SexyDialog_AddedToManager);
    MSHookFunction(Sexy_Dialog_RemovedFromManagerAddr, (void *) SexyDialog_RemovedFromManager,
                   (void **) &old_SexyDialog_RemovedFromManager);
    MSHookFunction(ImitaterDialog_ImitaterDialogAddr, (void *) ImitaterDialog_ImitaterDialog,
                   (void **) &old_ImitaterDialog_ImitaterDialog);
    MSHookFunction(AlmanacDialog_AddedToManagerAddr, (void *) AlmanacDialog_AddedToManager,
                   (void **) &old_AlmanacDialog_AddedToManager);
    MSHookFunction(AlmanacDialog_RemovedFromManagerAddr, (void *) AlmanacDialog_RemovedFromManager,
                   (void **) &old_AlmanacDialog_RemovedFromManager);
    MSHookFunction(StoreScreen_AddedToManagerAddr, (void *) StoreScreen_AddedToManager,
                   (void **) &old_StoreScreen_AddedToManager);
    MSHookFunction(StoreScreen_RemovedFromManagerAddr, (void *) StoreScreen_RemovedFromManager,
                   (void **) &old_StoreScreen_RemovedFromManager);
    MSHookFunction(LawnApp_UpdateAppAddr, (void *) LawnApp_UpDateApp,
                   (void **) &old_LawnApp_UpDateApp);
    MSHookFunction(GamepadControls_ButtonDownFireCobcannonTestAddr,
                   (void *) GamepadControls_ButtonDownFireCobcannonTest,
                   (void **) &old_GamepadControls_ButtonDownFireCobcannonTest);
    MSHookFunction(SeedBank_DrawAddr, (void *) SeedBank_Draw, (void **) &old_SeedBank_Draw);
    MSHookFunction(SeedChooserScreen_RebuildHelpbarAddr, (void *) SeedChooserScreen_RebuildHelpbar,
                   (void **) &old_SeedChooserScreen_RebuildHelpbar);
    MSHookFunction(MainMenu_ButtonDepressAddr, (void *) MainMenu_ButtonDepress,
                   (void **) &old_MainMenu_ButtonDepress);
    MSHookFunction(SeedPacket_UpdateAddr, (void *) SeedPacket_Update,
                   (void **) &old_SeedPacket_Update);
    MSHookFunction(GridItem_UpdateAddr, (void *) GridItem_Update,
                   (void **) &old_GridItem_Update);
    MSHookFunction(Plant_GetRefreshTimeSeedAddr, (void *) Plant_GetRefreshTimeSeed,
                   (void **) &old_Plant_GetRefreshTimeSeed);
    MSHookFunction(Board_AddPlantAddr, (void *) Board_AddPlant, (void **) &old_Board_AddPlant);
    MSHookFunction(Projectile_ProjectileInitializeAddr, (void *) Projectile_ProjectileInitialize,
                   (void **) &old_ProjectileInitialize);
    MSHookFunction(Plant_UpdateAddr, (void *) Plant_Update, (void **) &old_Plant_Update);
    MSHookFunction(Board_AddSunMoneyAddr, (void *) Board_AddSunMoney, NULL);
    MSHookFunction(Board_AddDeathMoneyAddr, (void *) Board_AddDeathMoney, NULL);
    MSHookFunction(Board_CanPlantAtAddr, (void *) Board_CanPlantAt, (void **) &old_CanPlantAt);
    MSHookFunction(Board_PlantingRequirementsMetAddr, (void *) Board_PlantingRequirementsMet,
                   (void **) &old_Board_PlantingRequirementsMet);
    MSHookFunction(Projectile_ConvertToFireballAddr, (void *) Projectile_ConvertToFireball,
                   (void **) &old_ConvertToFireball);
    MSHookFunction(Projectile_ConvertToPeaAddr, (void *) Projectile_ConvertToPea, NULL);
    MSHookFunction(Board_ZombiesWonAddr, (void *) Board_ZombiesWon, (void **) &old_BoardZombiesWon);
    MSHookFunction(Sexy_ScrollbarWidget_MouseDownAddr, (void *) Sexy_ScrollbarWidget_MouseDown,
                   NULL);
    MSHookFunction(ChallengeScreen_AddedToManagerAddr, (void *) ChallengeScreen_AddedToManager,
                   (void **) &old_ChallengeScreen_AddedToManager);
    MSHookFunction(ChallengeScreen_RemovedFromManagerAddr,
                   (void *) ChallengeScreen_RemovedFromManager,
                   (void **) &old_ChallengeScreen_RemovedFromManager);
    MSHookFunction(ChallengeScreen_UpdateAddr, (void *) ChallengeScreen_Update,
                   (void **) &old_ChallengeScreen_Update);
    MSHookFunction(LawnApp_ShowCreditScreenAddr, (void *) LawnApp_ShowCreditScreen,
                   (void **) &old_LawnApp_ShowCreditScreen);
    MSHookFunction(CreditScreen_RemovedFromManagerAddr, (void *) CreditScreen_RemovedFromManager,
                   (void **) &old_CreditScreen_RemovedFromManager);
    MSHookFunction(Coin_UpadteAddr, (void *) Coin_Update, (void **) &old_Coin_Update);
    MSHookFunction(StoreScreen_UpdateAddr, (void *) StoreScreen_Update,
                   (void **) &old_StoreScreen_Update);
    MSHookFunction(Challenge_HeavyWeaponFireAddr, (void *) Challenge_HeavyWeaponFire,
                   (void **) &old_Challenge_HeavyWeaponFire);
    MSHookFunction(Board_DrawZenButtonsAddr, (void *) Board_DrawZenButtons,
                   (void **) &old_Board_DrawZenButtons);
    MSHookFunction(GamepadControls_DrawAddr, (void *) GamepadControls_Draw,
                   (void **) &old_GamepadControls_Draw);
//    MSHookFunction( Plant_UpdateReanimAddr, (void *) Plant_UpdateReanim,
//                   (void **) &old_Plant_UpdateReanim);
//    MSHookFunction( Sexy_GamepadApp_CheckGamepadAddr,(void *) Sexy_GamepadApp_CheckGamepad,NULL);
//    MSHookFunction( Sexy_GamepadApp_HasGamepadAddr,(void *) Sexy_GamepadApp_HasGamepad,NULL);

    MSHookFunction(VSSetupMenu_UpdateAddr, (void *) VSSetupMenu_Update,
                   (void **) &old_VSSetupMenu_Update);
    MSHookFunction(VSResultsMenu_UpdateAddr, (void *) VSResultsMenu_Update,
                   (void **) &old_VSResultsMenu_Update);
    MSHookFunction(VSResultsMenu_OnExitAddr, (void *) VSResultsMenu_OnExit,
                   (void **) &old_VSResultsMenu_OnExit);
    MSHookFunction(SeedChooserScreen_OnStartButtonAddr, (void *) SeedChooserScreen_OnStartButton,
                   (void **) &old_SeedChooserScreen_OnStartButton);
    MSHookFunction(Plant_SetSleepingAddr, (void *) Plant_SetSleeping,
                   (void **) &old_Plant_SetSleeping);
    MSHookFunction(HelpOptionsDialog_ButtonDepressAddr, (void *) HelpOptionsDialog_ButtonDepress,
                   (void **) &old_HelpOptionsDialog_ButtonDepress);
    MSHookFunction(VSSetupMenu_KeyDownAddr, (void *) VSSetupMenu_KeyDown,
                   (void **) &old_VSSetupMenu_KeyDown);
    MSHookFunction(WaitForSecondPlayerDialog_WaitForSecondPlayerDialogAddr,
                   (void *) WaitForSecondPlayerDialog_WaitForSecondPlayerDialog,
                   (void **) &old_WaitForSecondPlayerDialog_WaitForSecondPlayerDialog);
    MSHookFunction(SeedChooserScreen_UpdateAddr, (void *) SeedChooserScreen_Update,
                   (void **) &old_SeedChooserScreen_Update);
    MSHookFunction(LawnApp_GamepadToPlayerIndexAddr, (void *) LawnApp_GamepadToPlayerIndex,
                   (void **) &old_LawnApp_GamepadToPlayerIndex);
    MSHookFunction(Zombie_UpdateAddr, (void *) Zombie_Update, (void **) &old_Zombie_Update);
    MSHookFunction(Projectile_UpdateAddr, (void *) Projectile_Update,
                   (void **) &old_Projectile_Update);
    MSHookFunction(Board_UpdateSunSpawningAddr, (void *) Board_UpdateSunSpawning,
                   (void **) &old_Board_UpdateSunSpawning);
    MSHookFunction(Board_UpdateZombieSpawningAddr, (void *) Board_UpdateZombieSpawning,
                   (void **) &old_Board_UpdateZombieSpawning);
    MSHookFunction(Challenge_UpdateAddr, (void *) Challenge_Update,
                   (void **) &old_Challenge_Update);
    MSHookFunction(Challenge_ChallengeAddr, (void *) Challenge_Challenge,
                   (void **) &old_Challenge_Challenge);

    MSHookFunction(SeedPacket_UpdateSelectedAddr, (void *) SeedPacket_UpdateSelected,
                   (void **) &old_SeedPacket_UpdateSelected);
    MSHookFunction(LawnApp_CanShopLevelAddr, (void *) LawnApp_CanShopLevel,
                   (void **) &old_LawnApp_CanShopLevel);
    MSHookFunction(Board_KeyDownAddr, (void *) Board_KeyDown, (void **) &old_Board_KeyDown);
    MSHookFunction(Board_PickBackgroundAddr, (void *) Board_PickBackground,
                   (void **) &old_Board_PickBackground);
    MSHookFunction(SeedChooserScreen_SeedNotAllowedToPickAddr,
                   (void *) SeedChooserScreen_SeedNotAllowedToPick,
                   (void **) &old_SeedChooserScreen_SeedNotAllowedToPick);
    MSHookFunction(Board_DrawCoverLayerAddr,
                   (void *) Board_DrawCoverLayer,
                   (void **) &old_Board_DrawCoverLayer);
    MSHookFunction(Board_UpdateGameAddr, (void *) Board_UpdateGame,
                   (void **) &old_Board_UpdateGame);
    MSHookFunction(LawnApp_DoNewOptionsAddr, (void *) LawnApp_DoNewOptions,
                   (void **) &old_LawnApp_DoNewOptions);
    MSHookFunction(Board_GetCurrentPlantCostAddr, (void *) Board_GetCurrentPlantCost,
                   (void **) &old_Board_GetCurrentPlantCost);
//    MSHookFunction(GamepadControls_InvalidatePreviewReanimAddr,(void *) GamepadControls_InvalidatePreviewReanim,NULL);
    MSHookFunction(Plant_UpdateReanimColorAddr, (void *) Plant_UpdateReanimColor,
                   (void **) &old_Plant_UpdateReanimColor);
    MSHookFunction(Challenge_IZombieDrawPlantAddr, (void *) Challenge_IZombieDrawPlant,
                   (void **) &old_Challenge_IZombieDrawPlant);
    MSHookFunction(GridItem_UpdateScaryPotAddr, (void *) GridItem_UpdateScaryPot,
                   (void **) &old_GridItem_UpdateScaryPot);
    MSHookFunction(Coin_GamepadCursorOverAddr, (void *) Coin_GamepadCursorOver,
                   (void **) &old_Coin_GamepadCursorOver);
    MSHookFunction(Projectile_DoImpactAddr, (void *) Projectile_DoImpact,
                   (void **) &old_Projectile_DoImpact);
    MSHookFunction(Zombie_UpdateZombiePeaHeadAddr, (void *) Zombie_UpdateZombiePeaHead,
                   (void **) &old_Zombie_UpdateZombiePeaHead);
    MSHookFunction(Zombie_UpdateZombieGatlingHeadAddr, (void *) Zombie_UpdateZombieGatlingHead,
                   (void **) &old_Zombie_UpdateZombieGatlingHead);
    MSHookFunction(Zombie_UpdateZombieJalapenoHeadAddr, (void *) Zombie_UpdateZombieJalapenoHead,
                   (void **) &old_Zombie_UpdateZombieJalapenoHead);

    MSHookFunction(Projectile_CheckForCollisionAddr, (void *) Projectile_CheckForCollision,
                   (void **) &old_Projectile_CheckForCollision);
    MSHookFunction(Plant_FindTargetGridItemAddr, (void *) Plant_FindTargetGridItem, NULL);
    MSHookFunction(LawnApp_DoBackToMainAddr, (void *) LawnApp_DoBackToMain,
                   (void **) &old_LawnApp_DoBackToMain);
    MSHookFunction(Board_UpdateGameObjectsAddr, (void *) Board_UpdateGameObjects,
                   (void **) &old_Board_UpdateGameObjects);
    MSHookFunction(ZenGardenControls_UpdateAddr, (void *) ZenGardenControls_Update,
                   (void **) &old_ZenGardenControls_Update);
    MSHookFunction(Board_DrawDebugTextAddr, (void *) Board_DrawDebugText,
                   (void **) &old_Board_DrawDebugText);
    MSHookFunction(Board_DrawDebugObjectRectsAddr, (void *) Board_DrawDebugObjectRects,
                   (void **) &old_Board_DrawDebugObjectRects);
    MSHookFunction(Board_DrawFadeOutAddr, (void *) Board_DrawFadeOut, NULL);
    MSHookFunction(AlmanacDialog_SetPageAddr, (void *) AlmanacDialog_SetPage,
                   (void **) &old_AlmanacDialog_SetPage);
    MSHookFunction(MainMenu_KeyDownAddr, (void *) MainMenu_KeyDown,
                   (void **) &old_MainMenu_KeyDown);
    MSHookFunction(AlmanacDialog_MouseUpAddr, (void *) AlmanacDialog_MouseUp, NULL);
    MSHookFunction(LawnApp_LoadLevelConfigurationAddr, (void *) LawnApp_LoadLevelConfiguration,
                   (void **) &old_LawnApp_LoadLevelConfiguration);
    MSHookFunction(Board_IsFlagWaveAddr, (void *) Board_IsFlagWave,
                   (void **) &old_Board_IsFlagWave);
    MSHookFunction(Board_DrawProgressMeterAddr, (void *) Board_DrawProgressMeter,
                   (void **) &old_Board_DrawProgressMeter);
    MSHookFunction(Board_GetNumWavesPerFlagAddr, (void *) Board_GetNumWavesPerFlag, NULL);
    MSHookFunction(Board_IsLevelDataLoadedAddr, (void *) Board_IsLevelDataLoaded,
                   (void **) &old_Board_IsLevelDataLoaded);
    MSHookFunction(Challenge_HeavyWeaponUpdateAddr, (void *) Challenge_HeavyWeaponUpdate,
                   (void **) &old_Challenge_HeavyWeaponUpdate);
    MSHookFunction(Board_NeedSaveGameAddr, (void *) Board_NeedSaveGame,
                   (void **) &old_Board_NeedSaveGame);
    MSHookFunction(Zombie_GetDancerFrameAddr, (void *) Zombie_GetDancerFrame, NULL);
    MSHookFunction(Board_UpdateFwooshAddr, (void *) Board_UpdateFwoosh,
                   (void **) &old_Board_UpdateFwoosh);
    MSHookFunction(Board_UpdateFogAddr, (void *) Board_UpdateFog,
                   (void **) &old_Board_UpdateFog);
//    MSHookFunction(Board_UpdateCoverLayerAddr, (void *) Board_UpdateCoverLayer,
//                   (void **) &old_Board_UpdateCoverLayer);
    MSHookFunction(Board_UpdateIceAddr, (void *) Board_UpdateIce,
                   (void **) &old_Board_UpdateIce);
    MSHookFunction(ZombieTypeCanGoInPoolAddr, (void *) ZombieTypeCanGoInPool,
                   (void **) &old_ZombieTypeCanGoInPool);
    MSHookFunction(Zombie_RiseFromGraveAddr, (void *) Zombie_RiseFromGrave,
                   (void **) &old_Zombie_RiseFromGrave);
    MSHookFunction(Board_DrawBackdropAddr, (void *) Board_DrawBackdrop,
                   (void **) &old_Board_DrawBackdrop);
//    MSHookFunction(Board_GetNumSeedsInBankAddr, (void *) Board_GetNumSeedsInBank,
//                   (void **) &old_Board_GetNumSeedsInBank);
//    MSHookFunction(ZenGarden_MouseDownWithFeedingToolAddr, (void *) ZenGarden_MouseDownWithFeedingTool, (void **) &old_ZenGarden_MouseDownWithFeedingTool);
    MSHookFunction(GridItem_DrawStinkyAddr, (void *) GridItem_DrawStinky,
                   (void **) &old_GridItem_DrawStinky);
//    MSHookFunction(GamepadControls_DrawPreviewAddr, (void *) GamepadControls_DrawPreview,
//                   (void **) &old_GamepadControls_DrawPreview);
    MSHookFunction(Coin_MouseHitTestAddr, (void *) Coin_MouseHitTest,
                   (void **) &old_Coin_MouseHitTest);
    MSHookFunction(SeedChooserScreen_SeedChooserScreenAddr,
                   (void *) SeedChooserScreen_SeedChooserScreen,
                   (void **) &old_SeedChooserScreen_SeedChooserScreen);
    MSHookFunction(LawnApp_TryHelpTextScreenAddr, (void *) LawnApp_TryHelpTextScreen, NULL);
    MSHookFunction(Challenge_IZombieEatBrainAddr, (void *) Challenge_IZombieEatBrain, NULL);
    MSHookFunction(Zombie_CheckForBoardEdgeAddr, (void *) Zombie_CheckForBoardEdge, NULL);
    MSHookFunction(Board_DrawShovelAddr, (void *) Board_DrawShovel, NULL);
    MSHookFunction(Board_AddZombieInRowAddr, (void *) Board_AddZombieInRow,
                   (void **) &old_Board_AddZombieInRow);
    MSHookFunction(SeedPacket_DrawOverlayAddr, (void *) SeedPacket_DrawOverlay,
                   (void **) &old_SeedPacket_DrawOverlay);
    MSHookFunction(GridItem_DrawScaryPotAddr, (void *) GridItem_DrawScaryPot, NULL);
    MSHookFunction(Zombie_DrawAddr, (void *) Zombie_Draw, (void **) &old_Zombie_Draw);
    MSHookFunction(Plant_DrawAddr, (void *) Plant_Draw, (void **) &old_Plant_Draw);
    MSHookFunction(Zombie_DrawBossPartAddr, (void *) Zombie_DrawBossPart,
                   (void **) &old_Zombie_DrawBossPart);

}

void CallHook() {
    InitInGameFunction();
    InitHookFunction();
}


#endif //PVZ_TV_1_1_5_HOOKGAME_H
