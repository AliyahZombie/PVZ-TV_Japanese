#ifndef PVZ_TV_1_1_5_HOOKADDR_H
#define PVZ_TV_1_1_5_HOOKADDR_H

#include <sstream>

#define targetLibName "libGameMain.so"


void *Board_UpdateAddr;
void *Board_GetPlantsOnLawnAddr;
void *Board_GridToPixelXAddr;
void *Board_GridToPixelYAddr;
void *Board_PixelToGridXAddr;
void *Board_PixelToGridYAddr;
void *Board_MouseHitTestAddr;
void *Board_ToolHitTestAddr;
void *Board_RefreshSeedPacketFromCursorAddr;
void *Board_CanUseGameObjectAddr;
void *Board_DrawZenButtonsAddr;
void *Board_DrawShovelAddr;
void *Board_ClearCursorAddr;
void *Board_UpdateGameAddr;
void *Board_UpdateGameObjectsAddr;
void *Board_MouseDownWithToolAddr;
void *Board_CountPlantByTypeAddr;
void *Board_SetTutorialStateAddr;
void *Board_NewPlantAddr;
void *Board_PickUpToolAddr;
void *Board_DrawDebugTextAddr;
void *Board_DrawDebugObjectRectsAddr;
void *Board_DrawFadeOutAddr;
void *Board_GetTopPlantAtAddr;
void *Board_ZombieHitTestAddr;
void *Board_UpdateSunSpawningAddr;
void *Board_UpdateProgressMeterAddr;
void *Board_UpdateZombieSpawningAddr;
void *Board_TakeDeathMoneyAddr;
void *Board_CanTakeDeathMoneyAddr;
void *Board_CanTakeSunMoneyAddr;
void *Board_KeyDownAddr;
void *Board_HasConveyorBeltSeedBankAddr;
void *Board_TakeSunMoneyAddr;
void *Board_AddALadderAddr;
void *Board_AddPlantAddr;
void *Board_AddZombieInRowAddr;
void *Board_AddSunMoneyAddr;
void *Board_AddProjectileAddr;
void *Board_MouseDownWithPlantAddr;
void *Board_CanPlantAtAddr;
void *Board_ZombiesWonAddr;
void *Board_AddDeathMoneyAddr;
void *Board_PickBackgroundAddr;
void *Board_LoadBackgroundImagesAddr;
void *Board_InitCoverLayerAddr;
void *Board_DrawCoverLayerAddr;
void *Board_GameAxisMoveAddr;
void *Board_GetCurrentPlantCostAddr;
void *Board_UpdateGridItemsAddr;
void *Board_PlantingRequirementsMetAddr;
void *Board_IterateZombiesAddr;
void *Board_IterateGridItemsAddr;
void *Board_IteratePlantsAddr;
void *Board_IterateProjectilesAddr;
void *Board_IsSurvivalStageWithRepickAddr;
void *Board_GetNumSeedsInBankAddr;
void *Board_GetNumWavesPerFlagAddr;
void *Board_ProgressMeterHasFlagsAddr;
void *Board_DrawProgressMeterAddr;
void *Board_IsFlagWaveAddr;
void *Board_NeedSaveGameAddr;
void *Board_MoveAddr;
void *Board_IsLevelDataLoadedAddr;
void *Board_UpdateFwooshAddr;
void *Board_UpdateFogAddr;
void *Board_UpdateCoverLayerAddr;
void *Board_UpdateIceAddr;
void *Board_DrawBackdropAddr;
void *Board_DoFwooshAddr;
void *Board_ShakeBoardAddr;
void *Board_GetButterButtonRectAddr;
void *Board_GetShovelButtonRectAddr;


void *CutScene_UpdateAddr;
void *CutScene_IsSurvivalRepickAddr;


void *MainMenu_UpdateAddr;
void *MainMenu_ButtonDepressAddr;
void *MainMenu_InTransitionAddr;
void *MainMenu_SetSceneAddr;
void *MainMenu_KeyDownAddr;
void *MainMenu_StartAdventureModeAddr;


void *LawnApp_UpdateAppAddr;
void *LawnApp_ShowAwardScreenAddr;
void *LawnApp_KillAwardScreenAddr;
void *LawnApp_KillChallengeScreenAddr;
void *LawnApp_PreNewGameAddr;
void *LawnApp_ShowCreditScreenAddr;
void *LawnApp_KillMainMenuAddr;
void *LawnApp_KillNewOptionsDialogAddr;
void *LawnApp_CanShowStoreAddr;
void *LawnApp_CanShowAlmanacAddr;
void *LawnApp_IsScaryPotterLevelAddr;
void *LawnApp_IsWhackAZombieLevelAddr;
void *LawnApp_CanShopLevelAddr;
void *LawnApp_ReanimationTryToGetAddr;
void *LawnApp_IsTwoPlayerGameAddr;
void *LawnApp_GamepadToPlayerIndexAddr;
void *LawnApp_DoBackToMainAddr;
void *LawnApp_DoNewOptionsAddr;
void *LawnApp_DoConfirmBackToMainAddr;
void *LawnApp_PlayFoleyAddr;
void *LawnApp_DoCheatDialogAddr;
void *LawnApp_DoCheatCodeDialogAddr;
void *LawnApp_DoUserDialogAddr;
void *LawnApp_OnSessionTaskFailedAddr;
void *LawnApp_ClearSecondPlayerAddr;
void *LawnApp_LoadLevelConfigurationAddr;
void *LawnApp_IsFirstTimeAdventureModeAddr;
void *LawnApp_IsAdventureModeAddr;
void *LawnApp_IsCoopModeAddr;
void *LawnApp_LawnMessageBoxAddr;
void *LawnApp_ReanimationGetAddr;
void *LawnApp_TryHelpTextScreenAddr;
void *LawnApp_IsIZombieLevelAddr;


void *ChallengeScreen_UpdateAddr;
void *ChallengeScreen_AddedToManagerAddr;
void *ChallengeScreen_RemovedFromManagerAddr;
void *ChallengeScreen_SetScrollTargetAddr;


void *GamepadControls_ButtonDownFireCobcannonTestAddr;
void *GamepadControls_OnButtonDownAddr;
void *GamepadControls_OnButtonUpAddr;
void *GamepadControls_OnKeyDownAddr;
void *GamepadControls_GetSeedBankAddr;
void *GamepadControls_DrawAddr;
void *GamepadControls_InvalidatePreviewReanimAddr;
void *GamepadControls_DrawPreviewAddr;


void *Zombie_UpdateAddr;
void *Zombie_ApplyButterAddr;
void *Zombie_DieNoLootAddr;
void *Zombie_ApplyBurnAddr;
void *Zombie_DrawAddr;
void *Zombie_UpdateZombiePeaHeadAddr;
void *Zombie_GetZombieRectAddr;
void *Zombie_UpdateZombieGatlingHeadAddr;
void *Zombie_UpdateZombieJalapenoHeadAddr;
void *Zombie_DrawBossPartAddr;
void *Zombie_IsImmobiliziedAddr;
void *Zombie_GetDancerFrameAddr;
void *Zombie_RiseFromGraveAddr;
void *Zombie_EffectedByDamageAddr;
void *Zombie_RemoveColdEffectsAddr;
void *Zombie_StartEatingAddr;
void *Zombie_TakeDamageAddr;
void *Zombie_IsWalkingBackwardsAddr;
void *Zombie_CheckForBoardEdgeAddr;


void *SeedChooserScreen_UpdateAddr;
void *SeedChooserScreen_EnableStartButtonAddr;
void *SeedChooserScreen_HasPacketAddr;
void *SeedChooserScreen_Has7RowsAddr;
void *SeedChooserScreen_RebuildHelpbarAddr;
void *SeedChooserScreen_SeedChooserScreenAddr;
void *SeedChooserScreen_OnStartButtonAddr;
void *SeedChooserScreen_CloseSeedChooserAddr;
void *SeedChooserScreen_GameButtonDownAddr;
void *SeedChooserScreen_ClickedSeedInBankAddr;
void *SeedChooserScreen_SeedNotAllowedToPickAddr;

void *Coin_UpadteAddr;
void *Coin_DieAddr;
void *Coin_CollectAddr;
void *Coin_UpdateFallAddr;
void *Coin_GamepadCursorOverAddr;
void *Coin_MouseHitTestAddr;


void *StoreScreen_UpdateAddr;
void *StoreScreen_SetSelectedSlotAddr;
void *StoreScreen_AddedToManagerAddr;
void *StoreScreen_RemovedFromManagerAddr;


void *SeedBank_DrawAddr;
void *SeedBank_MouseHitTestAddr;


void *Challenge_UpdateAddr;
void *Challenge_HeavyWeaponFireAddr;
void *Challenge_IZombieDrawPlantAddr;
void *Challenge_CanPlantAtAddr;
void *Challenge_HeavyWeaponUpdateAddr;
void *Challenge_ChallengeAddr;
void *Challenge_IZombieGetBrainTargetAddr;
void *Challenge_IZombieScoreBrainAddr;
void *Challenge_IZombieEatBrainAddr;


void *Plant_UpdateAddr;
void *Plant_DieAddr;
void *Plant_SetSleepingAddr;
void *Plant_UpdateReanimAddr;
void *Plant_GetRefreshTimeSeedAddr;
//void * Plant_PlantInitializeAddr;
void *Plant_UpdateReanimColorAddr;
void *Plant_DrawAddr;
void *Plant_FindTargetGridItemAddr;
void *Plant_GetImageAddr;
void *Plant_GetPlantRectAddr;
void *Plant_NotOnGroundAddr;


void *Projectile_UpdateAddr;
void *Projectile_ProjectileInitializeAddr;
void *Projectile_ConvertToFireballAddr;
void *Projectile_ConvertToPeaAddr;
void *Projectile_DoImpactAddr;
void *Projectile_DieAddr;
void *Projectile_CheckForCollisionAddr;
void *Projectile_GetProjectileRectAddr;


void *SeedPacket_UpdateAddr;
void *SeedPacket_UpdateSelectedAddr;
void *SeedPacket_DrawOverlayAddr;
void *SeedPacket_CanPickUpAddr;
void *ShopSeedPacket_UpdateAddr;


void *VSSetupMenu_UpdateAddr;
void *VSSetupMenu_KeyDownAddr;
void *VSSetupMenu_GameButtonDownAddr;


void *VSResultsMenu_UpdateAddr;
void *VSResultsMenu_OnExitAddr;


void *WaitForSecondPlayerDialog_WaitForSecondPlayerDialogAddr;
void *WaitForSecondPlayerDialog_GameButtonDownAddr;
void *WaitForSecondPlayerDialog_KeyDownAddr;


void *Sexy_Dialog_AddedToManagerWidgetManagerAddr;
void *Sexy_Dialog_RemovedFromManagerAddr;


void *AlmanacDialog_AddedToManagerAddr;
void *AlmanacDialog_RemovedFromManagerAddr;
void *AlmanacDialog_SetPageAddr;
void *AlmanacDialog_MouseUpAddr;


void *Sexy_Graphics_GraphicsAddr;
void *Sexy_Graphics_ClipRectAddr;
void *Sexy_Graphics_DrawImageCelAddr;
void *Sexy_Graphics_DrawImageCel2Addr;
void *Sexy_Graphics_PrepareForReuseAddr;
void *Sexy_Graphics_SetColorAddr;
void *Sexy_Graphics_DrawStringAddr;
void *Sexy_Graphics_FillRectAddr;
void *Sexy_Graphics_DrawImageAddr;


void *Reanimation_ReanimationAddr;
void *Reanimation_ReanimationInitializeTypeAddr;
void *Reanimation_DrawAddr;
void *Reanimation_PrepareForReuseAddr;
void *Reanimation_DrawRenderGroupAddr;
void *Reanimation_GetCurrentTransformAddr;
void *Reanimation_FindTrackIndexByIdAddr;
void *Reanimation_PlayReanimAddr;


void *Sexy_GamepadApp_CheckGamepadAddr;
void *Sexy_GamepadApp_HasGamepadAddr;
void *Sexy_Level_isCardNotAllowedToPickAddr;
void *Sexy_ScrollbarWidget_MouseDownAddr;


void *ImitaterDialog_ImitaterDialogAddr;
void *ZenGarden_RebuildHelpbarAddr;
void *CreditScreen_RemovedFromManagerAddr;
void *CursorObject_DrawAddr;
void *HelpOptionsDialog_ButtonDepressAddr;
void *AttachmentDieAddr;
void *ReanimatorTransform_ReanimatorTransformAddr;

void *ZombieTypeCanGoInPoolAddr;
void *TodDrawStringAddr;


void *GridItem_UpdateAddr;
void *GridItem_UpdateBrainAddr;
void* GridItem_UpdateScaryPotAddr;
void *GridItem_DrawScaryPotAddr;
void *GridItem_DrawStinkyAddr;
void *GridItem_GridItemDieAddr;


void *TodDrawImageCelCenterScaledFAddr;
void *DrawSeedPacketAddr;
void *ReanimatorCache_DrawCachedZombieAddr;
void *TodAnimateCurveAddr;
void *Sexy_StrFormatAddr;
void *GetRectOverlapAddr;
void *FilterEffectCreateImageAddr;
void *ZenGardenControls_UpdateAddr;
void *ZenGarden_MouseDownWithFeedingToolAddr;
void *ZenGarden_GetStinkyAddr;
void *ZenGarden_IsStinkyHighOnChocolateAddr;
void *AwardScreen_GameButtonDownAddr;
void *LawnPlayerInfo_GetFlagAddr;
void *GetFlashingColorAddr;

int *Sexy_FONT_HOUSEOFTERROR28_Addr;
int *Sexy_FONT_DWARVENTODCRAFT18_Addr;
int *Sexy_IMAGE_PLANTSHADOW2_Addr;
int *Sexy_IMAGE_SCARY_POT_Addr;
int *Sexy_IMAGE_SHOVELBANK_Addr;
int *Sexy_IMAGE_HAMMER_ICON_Addr;
int *Sexy_IMAGE_HELP_BUTTONS_Addr;
int *Sexy_IMAGE_HELP_BUTTONS2_Addr;
int *Sexy_IMAGE_BUTTER_ICON_Addr;
int *Sexy_IMAGE_SHOVEL_Addr;
int *ReanimTrackId_anim_head1_Addr;
int *Sexy_SOUND_PAUSE_Addr;
int *Sexy_SOUND_BOING_Addr;
int *Sexy_SOUND_GRAVEBUTTON_Addr;
int *Sexy_SOUND_GULP_Addr;
int *Sexy_SOUND_SEEDLIFT_Addr;


//unsigned int gLibBaseOffset = 0;
//
//void GetBssAddress() {
//    if (gLibBaseOffset == 0) {
//        std::string filename = "/proc/self/maps";
//        std::ifstream file(filename);
//        if (!file.is_open()) {
//            return;
//        }
//
//        std::string line;
//        while (std::getline(file, line)) {
//            if (line.find(targetLibName) != std::string::npos) {
//                std::stringstream ss(line);
//                ss >> std::hex >> gLibBaseOffset;
//                break;
//            }
//        }
//        file.close();
//    }
//}
//
//inline void *GetConst(unsigned int offset) {
//    return (void *) (gLibBaseOffset + offset);
//}


void GetFunctionAddr() {

//    GetBssAddress();

    void *handle = dlopen(targetLibName, 4);

    Board_UpdateAddr = dlsym(handle, "_ZN5Board6UpdateEv");
    Board_MouseHitTestAddr = dlsym(handle, "_ZN5Board12MouseHitTestEiiP9HitResulti");
    Board_CanUseGameObjectAddr = dlsym(handle, "_ZN5Board16CanUseGameObjectE14GameObjectType");
    Board_DrawZenButtonsAddr = dlsym(handle, "_ZN5Board14DrawZenButtonsEPN4Sexy8GraphicsE");
    Board_DrawShovelAddr = dlsym(handle, "_ZN5Board10DrawShovelEPN4Sexy8GraphicsE");
    Board_ClearCursorAddr = dlsym(handle, "_ZN5Board11ClearCursorEi");
    Board_UpdateGameAddr = dlsym(handle, "_ZN5Board10UpdateGameEv");
    Board_UpdateGameObjectsAddr = dlsym(handle, "_ZN5Board17UpdateGameObjectsEv");
    Board_MouseDownWithToolAddr = dlsym(handle, "_ZN5Board17MouseDownWithToolEiii10CursorTypei");
    Board_ToolHitTestAddr = dlsym(handle, "_ZN5Board11ToolHitTestEii");
    Board_RefreshSeedPacketFromCursorAddr = dlsym(handle, "_ZN5Board27RefreshSeedPacketFromCursorEi");
    Board_CountPlantByTypeAddr = dlsym(handle, "_ZN5Board16CountPlantByTypeE8SeedType");
    Board_SetTutorialStateAddr = dlsym(handle, "_ZN5Board16SetTutorialStateE13TutorialState");
    Board_NewPlantAddr = dlsym(handle, "_ZN5Board8NewPlantEii8SeedTypeS0_i");
    Board_GetTopPlantAtAddr = dlsym(handle, "_ZN5Board13GetTopPlantAtEii13PlantPriority");
    Board_KeyDownAddr = dlsym(handle, "_ZN5Board7KeyDownEN4Sexy7KeyCodeE");
    Board_TakeDeathMoneyAddr = dlsym(handle, "_ZN5Board14TakeDeathMoneyEi");
    Board_CanTakeDeathMoneyAddr = dlsym(handle, "_ZN5Board17CanTakeDeathMoneyEi");
    Board_CanTakeSunMoneyAddr = dlsym(handle, "_ZN5Board15CanTakeSunMoneyEii");
    Board_HasConveyorBeltSeedBankAddr = dlsym(handle, "_ZN5Board23HasConveyorBeltSeedBankEb");
    Board_AddDeathMoneyAddr = dlsym(handle, "_ZN5Board13AddDeathMoneyEi");
    Board_UpdateSunSpawningAddr = dlsym(handle, "_ZN5Board17UpdateSunSpawningEv");
    Board_UpdateProgressMeterAddr = dlsym(handle, "_ZN5Board19UpdateProgressMeterEv");
    Board_UpdateZombieSpawningAddr = dlsym(handle, "_ZN5Board20UpdateZombieSpawningEv");
    Board_ZombieHitTestAddr = dlsym(handle, "_ZN5Board13ZombieHitTestEiib");
    Board_GetPlantsOnLawnAddr = dlsym(handle, "_ZN5Board15GetPlantsOnLawnEiiP12PlantsOnLawn");
    Board_GridToPixelXAddr = dlsym(handle, "_ZN5Board12GridToPixelXEii");
    Board_GridToPixelYAddr = dlsym(handle, "_ZN5Board12GridToPixelYEii");
    Board_TakeSunMoneyAddr = dlsym(handle, "_ZN5Board12TakeSunMoneyEii");
    Board_AddALadderAddr = dlsym(handle, "_ZN5Board10AddALadderEii");
    Board_AddPlantAddr = dlsym(handle, "_ZN5Board8AddPlantEii8SeedTypeS0_ib");
    Board_AddZombieInRowAddr = dlsym(handle, "_ZN5Board14AddZombieInRowE10ZombieTypeiib");
    Board_PixelToGridXAddr = dlsym(handle, "_ZN5Board12PixelToGridXEii");
    Board_PixelToGridYAddr = dlsym(handle, "_ZN5Board12PixelToGridYEii");
    Board_AddSunMoneyAddr = dlsym(handle, "_ZN5Board11AddSunMoneyEii");
    Board_MouseDownWithPlantAddr = dlsym(handle, "_ZN5Board18MouseDownWithPlantEiiii");
    Board_CanPlantAtAddr = dlsym(handle, "_ZN5Board10CanPlantAtEii8SeedType");
    Board_ZombiesWonAddr = dlsym(handle, "_ZN5Board10ZombiesWonEP6Zombie");
    Board_PickBackgroundAddr = dlsym(handle, "_ZN5Board14PickBackgroundEv");
    Board_LoadBackgroundImagesAddr = dlsym(handle, "_ZN5Board20LoadBackgroundImagesEv");
    Board_InitCoverLayerAddr = dlsym(handle, "_ZN5Board14InitCoverLayerEv");
    Board_DrawCoverLayerAddr = dlsym(handle, "_ZN5Board14DrawCoverLayerEPN4Sexy8GraphicsEi");
    Board_GameAxisMoveAddr = dlsym(handle, "_ZN5Board12GameAxisMoveEN4Sexy11GamepadAxisEii");
    Board_GetCurrentPlantCostAddr = dlsym(handle, "_ZN5Board19GetCurrentPlantCostE8SeedTypeS0_");
    Board_UpdateGridItemsAddr = dlsym(handle, "_ZN5Board15UpdateGridItemsEv");
    Board_PlantingRequirementsMetAddr = dlsym(handle, "_ZN5Board23PlantingRequirementsMetE8SeedType");
    Board_AddProjectileAddr = dlsym(handle, "_ZN5Board13AddProjectileEiiii14ProjectileType");
    Board_IterateZombiesAddr = dlsym(handle, "_ZN5Board14IterateZombiesERP6Zombie");
    Board_IterateGridItemsAddr = dlsym(handle, "_ZN5Board16IterateGridItemsERP8GridItem");
    Board_IteratePlantsAddr = dlsym(handle, "_ZN5Board13IteratePlantsERP5Plant");
    Board_IterateProjectilesAddr = dlsym(handle, "_ZN5Board18IterateProjectilesERP10Projectile");
    Board_PickUpToolAddr = dlsym(handle, "_ZN5Board10PickUpToolE14GameObjectTypei");
    Board_DrawDebugTextAddr = dlsym(handle, "_ZN5Board13DrawDebugTextEPN4Sexy8GraphicsE");
    Board_DrawDebugObjectRectsAddr = dlsym(handle, "_ZN5Board20DrawDebugObjectRectsEPN4Sexy8GraphicsE");
    Board_DrawFadeOutAddr = dlsym(handle, "_ZN5Board11DrawFadeOutEPN4Sexy8GraphicsE");
    Board_IsSurvivalStageWithRepickAddr = dlsym(handle, "_ZN5Board25IsSurvivalStageWithRepickEv");
    Board_GetNumSeedsInBankAddr = dlsym(handle, "_ZN5Board17GetNumSeedsInBankEb");
    Board_GetNumWavesPerFlagAddr = dlsym(handle, "_ZN5Board18GetNumWavesPerFlagEv");
    Board_ProgressMeterHasFlagsAddr = dlsym(handle, "_ZN5Board21ProgressMeterHasFlagsEv");
    Board_DrawProgressMeterAddr = dlsym(handle, "_ZN5Board17DrawProgressMeterEPN4Sexy8GraphicsEii");
    Board_IsFlagWaveAddr = dlsym(handle, "_ZN5Board10IsFlagWaveEi");
    Board_NeedSaveGameAddr = dlsym(handle, "_ZN5Board12NeedSaveGameEv");
    Board_MoveAddr = dlsym(handle, "_ZN5Board4MoveEii");
    Board_IsLevelDataLoadedAddr = dlsym(handle, "_ZN5Board17IsLevelDataLoadedEv");
    Board_UpdateFwooshAddr = dlsym(handle, "_ZN5Board12UpdateFwooshEv");
    Board_UpdateFogAddr = dlsym(handle, "_ZN5Board9UpdateFogEv");
    Board_UpdateCoverLayerAddr = dlsym(handle, "_ZN5Board16UpdateCoverLayerEv");
    Board_UpdateIceAddr = dlsym(handle, "_ZN5Board9UpdateIceEv");
    Board_DrawBackdropAddr = dlsym(handle, "_ZN5Board12DrawBackdropEPN4Sexy8GraphicsE");
    Board_DoFwooshAddr = dlsym(handle, "_ZN5Board8DoFwooshEi");
    Board_ShakeBoardAddr = dlsym(handle, "_ZN5Board10ShakeBoardEii");
    Board_GetButterButtonRectAddr = dlsym(handle, "_ZN5Board19GetButterButtonRectEv");
    Board_GetShovelButtonRectAddr = dlsym(handle, "_ZN5Board19GetShovelButtonRectEv");


    CutScene_UpdateAddr = dlsym(handle, "_ZN8CutScene6UpdateEv");
    CutScene_IsSurvivalRepickAddr = dlsym(handle, "_ZN8CutScene16IsSurvivalRepickEv");


    MainMenu_UpdateAddr = dlsym(handle, "_ZN8MainMenu6UpdateEv");
    MainMenu_ButtonDepressAddr = dlsym(handle, "_ZN8MainMenu13ButtonDepressEi");
    MainMenu_InTransitionAddr = dlsym(handle, "_ZN8MainMenu12InTransitionEv");
    MainMenu_SetSceneAddr = dlsym(handle, "_ZN8MainMenu8SetSceneENS_9MenuSceneE");
    MainMenu_KeyDownAddr = dlsym(handle, "_ZN8MainMenu7KeyDownEN4Sexy7KeyCodeE");
    MainMenu_StartAdventureModeAddr = dlsym(handle, "_ZN8MainMenu18StartAdventureModeEv");


    LawnApp_UpdateAppAddr = dlsym(handle, "_ZN7LawnApp9UpdateAppEv");
    LawnApp_PlayFoleyAddr = dlsym(handle, "_ZN7LawnApp9PlayFoleyE9FoleyType");
    LawnApp_PreNewGameAddr = dlsym(handle, "_ZN7LawnApp10PreNewGameE8GameModeb");
    LawnApp_ShowCreditScreenAddr = dlsym(handle, "_ZN7LawnApp16ShowCreditScreenEb");
    LawnApp_KillMainMenuAddr = dlsym(handle, "_ZN7LawnApp12KillMainMenuEv");
    LawnApp_KillNewOptionsDialogAddr = dlsym(handle, "_ZN7LawnApp20KillNewOptionsDialogEv");
    LawnApp_CanShowStoreAddr = dlsym(handle, "_ZN7LawnApp12CanShowStoreEv");
    LawnApp_CanShowAlmanacAddr = dlsym(handle, "_ZN7LawnApp14CanShowAlmanacEv");
    LawnApp_IsTwoPlayerGameAddr = dlsym(handle, "_ZN7LawnApp15IsTwoPlayerGameEv");
    LawnApp_DoBackToMainAddr = dlsym(handle, "_ZN7LawnApp12DoBackToMainEv");
    LawnApp_IsScaryPotterLevelAddr = dlsym(handle, "_ZN7LawnApp18IsScaryPotterLevelEv");
    LawnApp_IsWhackAZombieLevelAddr = dlsym(handle, "_ZN7LawnApp19IsWhackAZombieLevelEv");
    LawnApp_DoUserDialogAddr = dlsym(handle, "_ZN7LawnApp12DoUserDialogEv");
    LawnApp_GamepadToPlayerIndexAddr = dlsym(handle, "_ZN7LawnApp20GamepadToPlayerIndexEj");
    LawnApp_DoNewOptionsAddr = dlsym(handle, "_ZN7LawnApp12DoNewOptionsEbj");
    LawnApp_DoConfirmBackToMainAddr = dlsym(handle, "_ZN7LawnApp19DoConfirmBackToMainEb");
    LawnApp_CanShopLevelAddr = dlsym(handle, "_ZN7LawnApp12CanShopLevelEv");
    LawnApp_KillChallengeScreenAddr = dlsym(handle, "_ZN7LawnApp19KillChallengeScreenEv");
    LawnApp_DoCheatDialogAddr = dlsym(handle, "_ZN7LawnApp13DoCheatDialogEv");
    LawnApp_DoCheatCodeDialogAddr = dlsym(handle, "_ZN7LawnApp17DoCheatCodeDialogEv");
    LawnApp_ShowAwardScreenAddr = dlsym(handle, "_ZN7LawnApp15ShowAwardScreenE9AwardType");
    LawnApp_KillAwardScreenAddr = dlsym(handle, "_ZN7LawnApp15KillAwardScreenEv");
    LawnApp_ReanimationTryToGetAddr = dlsym(handle,
                                            "_ZN7LawnApp19ReanimationTryToGetE13ReanimationID");
    LawnApp_OnSessionTaskFailedAddr = dlsym(handle, "_ZN7LawnApp19OnSessionTaskFailedEiSs");
    LawnApp_ClearSecondPlayerAddr = dlsym(handle, "_ZN7LawnApp17ClearSecondPlayerEv");
    LawnApp_LoadLevelConfigurationAddr = dlsym(handle, "_ZN7LawnApp22LoadLevelConfigurationEii");
    LawnApp_IsFirstTimeAdventureModeAddr = dlsym(handle, "_ZN7LawnApp24IsFirstTimeAdventureModeEv");
    LawnApp_IsAdventureModeAddr = dlsym(handle, "_ZN7LawnApp15IsAdventureModeEv");
    LawnApp_IsCoopModeAddr = dlsym(handle, "_ZN7LawnApp10IsCoopModeEv");
    LawnApp_LawnMessageBoxAddr = dlsym(handle, "_ZN7LawnApp14LawnMessageBoxEiPKcS1_S1_S1_i");
    LawnApp_ReanimationGetAddr = dlsym(handle, "_ZN7LawnApp14ReanimationGetE13ReanimationID");
    LawnApp_TryHelpTextScreenAddr = dlsym(handle, "_ZN7LawnApp17TryHelpTextScreenEi");
    LawnApp_IsIZombieLevelAddr = dlsym(handle, "_ZN7LawnApp14IsIZombieLevelEv");


    ChallengeScreen_UpdateAddr = dlsym(handle, "_ZN15ChallengeScreen6UpdateEv");
    ChallengeScreen_AddedToManagerAddr = dlsym(handle,
                                               "_ZN15ChallengeScreen14AddedToManagerEPN4Sexy13WidgetManagerE");
    ChallengeScreen_RemovedFromManagerAddr = dlsym(handle,
                                                   "_ZN15ChallengeScreen18RemovedFromManagerEPN4Sexy13WidgetManagerE");
    ChallengeScreen_SetScrollTargetAddr = dlsym(handle, "_ZN15ChallengeScreen15SetScrollTargetEi");
    Challenge_CanPlantAtAddr = dlsym(handle, "_ZN15ChallengeScreen15SetScrollTargetEi");


    GamepadControls_ButtonDownFireCobcannonTestAddr = dlsym(handle,
                                                            "_ZN15GamepadControls27ButtonDownFireCobcannonTestEv");
    GamepadControls_OnKeyDownAddr = dlsym(handle,
                                          "_ZN15GamepadControls9OnKeyDownEN4Sexy7KeyCodeEj");
    GamepadControls_GetSeedBankAddr = dlsym(handle, "_ZN15GamepadControls11GetSeedBankEv");
    GamepadControls_DrawAddr = dlsym(handle, "_ZN15GamepadControls4DrawEPN4Sexy8GraphicsE");
    GamepadControls_OnButtonDownAddr = dlsym(handle, "_ZN15GamepadControls12OnButtonDownEiij");
    GamepadControls_OnButtonUpAddr = dlsym(handle, "_ZN15GamepadControls10OnButtonUpEiij");
    GamepadControls_InvalidatePreviewReanimAddr = dlsym(handle, "_ZN15GamepadControls23InvalidatePreviewReanimEv");
    GamepadControls_DrawPreviewAddr = dlsym(handle, "_ZN15GamepadControls11DrawPreviewEPN4Sexy8GraphicsE");

    Zombie_UpdateAddr = dlsym(handle, "_ZN6Zombie6UpdateEv");
    Zombie_ApplyButterAddr = dlsym(handle, "_ZN6Zombie11ApplyButterEv");
    Zombie_DieNoLootAddr = dlsym(handle, "_ZN6Zombie9DieNoLootEv");
    Zombie_ApplyBurnAddr = dlsym(handle, "_ZN6Zombie9ApplyBurnEv");
    Zombie_DrawAddr = dlsym(handle, "_ZN6Zombie4DrawEPN4Sexy8GraphicsE");
    Zombie_UpdateZombiePeaHeadAddr = dlsym(handle, "_ZN6Zombie19UpdateZombiePeaHeadEv");
    Zombie_UpdateZombieGatlingHeadAddr = dlsym(handle, "_ZN6Zombie23UpdateZombieGatlingHeadEv");
    Zombie_UpdateZombieJalapenoHeadAddr = dlsym(handle, "_ZN6Zombie24UpdateZombieJalapenoHeadEv");
    Zombie_GetZombieRectAddr = dlsym(handle, "_ZN6Zombie13GetZombieRectEv");
    Zombie_DrawBossPartAddr = dlsym(handle, "_ZN6Zombie12DrawBossPartEPN4Sexy8GraphicsE8BossPart");
    Zombie_IsImmobiliziedAddr = dlsym(handle, "_ZN6Zombie14IsImmobiliziedEv");
    Zombie_GetDancerFrameAddr = dlsym(handle, "_ZN6Zombie14GetDancerFrameEv");
    Zombie_RiseFromGraveAddr = dlsym(handle, "_ZN6Zombie13RiseFromGraveEii");
    Zombie_EffectedByDamageAddr = dlsym(handle, "_ZN6Zombie16EffectedByDamageEj");
    Zombie_RemoveColdEffectsAddr = dlsym(handle, "_ZN6Zombie17RemoveColdEffectsEv");
    Zombie_StartEatingAddr = dlsym(handle, "_ZN6Zombie11StartEatingEv");
    Zombie_TakeDamageAddr = dlsym(handle, "_ZN6Zombie10TakeDamageEij");
    Zombie_IsWalkingBackwardsAddr = dlsym(handle, "_ZN6Zombie18IsWalkingBackwardsEv");
    Zombie_CheckForBoardEdgeAddr = dlsym(handle, "_ZN6Zombie17CheckForBoardEdgeEv");


    SeedChooserScreen_UpdateAddr = dlsym(handle, "_ZN17SeedChooserScreen6UpdateEv");
    SeedChooserScreen_GameButtonDownAddr = dlsym(handle,
                                                 "_ZN17SeedChooserScreen14GameButtonDownEN4Sexy13GamepadButtonEij");
    SeedChooserScreen_OnStartButtonAddr = dlsym(handle, "_ZN17SeedChooserScreen13OnStartButtonEv");
    SeedChooserScreen_CloseSeedChooserAddr = dlsym(handle,
                                                   "_ZN17SeedChooserScreen16CloseSeedChooserEv");
    SeedChooserScreen_ClickedSeedInBankAddr = dlsym(handle,
                                                    "_ZN17SeedChooserScreen17ClickedSeedInBankER10ChosenSeedi");
    SeedChooserScreen_SeedChooserScreenAddr = dlsym(handle, "_ZN17SeedChooserScreenC2Eb");
    SeedChooserScreen_HasPacketAddr = dlsym(handle, "_ZN17SeedChooserScreen9HasPacketEib");
    SeedChooserScreen_EnableStartButtonAddr = dlsym(handle,
                                                    "_ZN17SeedChooserScreen17EnableStartButtonEb");
    SeedChooserScreen_RebuildHelpbarAddr = dlsym(handle,
                                                 "_ZN17SeedChooserScreen14RebuildHelpbarEv");
    SeedChooserScreen_Has7RowsAddr = dlsym(handle, "_ZN17SeedChooserScreen8Has7RowsEv");
    SeedChooserScreen_SeedNotAllowedToPickAddr = dlsym(handle,
                                                       "_ZN17SeedChooserScreen20SeedNotAllowedToPickE8SeedType");


    Coin_UpadteAddr = dlsym(handle, "_ZN4Coin6UpdateEv");
    Coin_DieAddr = dlsym(handle, "_ZN4Coin3DieEv");
    Coin_CollectAddr = dlsym(handle, "_ZN4Coin7CollectEi");
    Coin_UpdateFallAddr = dlsym(handle, "_ZN4Coin10UpdateFallEv");
    Coin_GamepadCursorOverAddr = dlsym(handle, "_ZN4Coin17GamepadCursorOverEi");
    Coin_MouseHitTestAddr = dlsym(handle, "_ZN4Coin12MouseHitTestEiiP9HitResulti");


    StoreScreen_UpdateAddr = dlsym(handle, "_ZN11StoreScreen6UpdateEv");
    StoreScreen_SetSelectedSlotAddr = dlsym(handle, "_ZN11StoreScreen15SetSelectedSlotEi");
    StoreScreen_AddedToManagerAddr = dlsym(handle,
                                           "_ZN11StoreScreen14AddedToManagerEPN4Sexy13WidgetManagerE");
    StoreScreen_RemovedFromManagerAddr = dlsym(handle,
                                               "_ZN11StoreScreen18RemovedFromManagerEPN4Sexy13WidgetManagerE");


    SeedBank_DrawAddr = dlsym(handle, "_ZN8SeedBank4DrawEPN4Sexy8GraphicsE");
    SeedBank_MouseHitTestAddr = dlsym(handle, "_ZN8SeedBank12MouseHitTestEiiP9HitResult");


    Challenge_UpdateAddr = dlsym(handle, "_ZN9Challenge6UpdateEv");
    Challenge_HeavyWeaponFireAddr = dlsym(handle, "_ZN9Challenge15HeavyWeaponFireEff");
    Challenge_IZombieDrawPlantAddr = dlsym(handle, "_ZN9Challenge16IZombieDrawPlantEPN4Sexy8GraphicsEP5Plant");
    Challenge_HeavyWeaponUpdateAddr = dlsym(handle, "_ZN9Challenge17HeavyWeaponUpdateEv");
    Challenge_ChallengeAddr = dlsym(handle, "_ZN9ChallengeC2Ev");
    Challenge_IZombieScoreBrainAddr = dlsym(handle, "_ZN9Challenge17IZombieScoreBrainEP8GridItem");
    Challenge_IZombieGetBrainTargetAddr = dlsym(handle, "_ZN9Challenge21IZombieGetBrainTargetEP6Zombie");
    Challenge_IZombieEatBrainAddr = dlsym(handle, "_ZN9Challenge15IZombieEatBrainEP6Zombie");

    Plant_UpdateAddr = dlsym(handle, "_ZN5Plant6UpdateEv");
    Plant_GetRefreshTimeSeedAddr = dlsym(handle, "_ZN5Plant14GetRefreshTimeE8SeedTypeS0_");
    Plant_DieAddr = dlsym(handle, "_ZN5Plant3DieEv");
    Plant_SetSleepingAddr = dlsym(handle, "_ZN5Plant11SetSleepingEb");
    Plant_UpdateReanimAddr = dlsym(handle, "_ZN5Plant12UpdateReanimEv");
    Plant_UpdateReanimColorAddr = dlsym(handle, "_ZN5Plant17UpdateReanimColorEv");
    Plant_DrawAddr = dlsym(handle, "_ZN5Plant4DrawEPN4Sexy8GraphicsE");
    Plant_FindTargetGridItemAddr = dlsym(handle, "_ZN5Plant18FindTargetGridItemEi11PlantWeapon");
    Plant_GetImageAddr = dlsym(handle, "_ZN5Plant8GetImageE8SeedType");
    Plant_GetPlantRectAddr = dlsym(handle, "_ZN5Plant12GetPlantRectEv");
    Plant_NotOnGroundAddr = dlsym(handle, "_ZN5Plant11NotOnGroundEv");


    Projectile_UpdateAddr = dlsym(handle, "_ZN10Projectile6UpdateEv");
    Projectile_ProjectileInitializeAddr = dlsym(handle,
                                                "_ZN10Projectile20ProjectileInitializeEiiii14ProjectileType");
    Projectile_ConvertToFireballAddr = dlsym(handle, "_ZN10Projectile17ConvertToFireballEi");
    Projectile_ConvertToPeaAddr = dlsym(handle, "_ZN10Projectile12ConvertToPeaEi");
    Projectile_DoImpactAddr = dlsym(handle, "_ZN10Projectile8DoImpactEP6Zombie");
    Projectile_DieAddr = dlsym(handle, "_ZN10Projectile3DieEv");
    Projectile_CheckForCollisionAddr = dlsym(handle, "_ZN10Projectile17CheckForCollisionEv");
    Projectile_GetProjectileRectAddr = dlsym(handle, "_ZN10Projectile17GetProjectileRectEv");


    SeedPacket_UpdateAddr = dlsym(handle, "_ZN10SeedPacket6UpdateEv");
    SeedPacket_UpdateSelectedAddr = dlsym(handle, "_ZN10SeedPacket14UpdateSelectedEv");
    SeedPacket_DrawOverlayAddr = dlsym(handle, "_ZN10SeedPacket11DrawOverlayEPN4Sexy8GraphicsE");
    SeedPacket_CanPickUpAddr = dlsym(handle, "_ZN10SeedPacket9CanPickUpEv");
    ShopSeedPacket_UpdateAddr = dlsym(handle, "_ZN14ShopSeedPacket6UpdateEv");


    VSSetupMenu_UpdateAddr = dlsym(handle, "_ZN11VSSetupMenu6UpdateEv");
    VSSetupMenu_GameButtonDownAddr = dlsym(handle,
                                           "_ZN11VSSetupMenu14GameButtonDownEN4Sexy13GamepadButtonEij");
    VSSetupMenu_KeyDownAddr = dlsym(handle, "_ZN11VSSetupMenu7KeyDownEN4Sexy7KeyCodeE");


    VSResultsMenu_UpdateAddr = dlsym(handle, "_ZN13VSResultsMenu6UpdateEv");
    VSResultsMenu_OnExitAddr = dlsym(handle, "_ZN13VSResultsMenu6OnExitEv");


    WaitForSecondPlayerDialog_WaitForSecondPlayerDialogAddr = dlsym(handle,
                                                                    "_ZN25WaitForSecondPlayerDialogC2EP7LawnApp");
    WaitForSecondPlayerDialog_GameButtonDownAddr = dlsym(handle,
                                                         "_ZN25WaitForSecondPlayerDialog14GameButtonDownEN4Sexy13GamepadButtonEij");
    WaitForSecondPlayerDialog_KeyDownAddr = dlsym(handle,
                                                  "_ZN25WaitForSecondPlayerDialog7KeyDownEN4Sexy7KeyCodeE");


    Sexy_Dialog_AddedToManagerWidgetManagerAddr = dlsym(handle,
                                                        "_ZN4Sexy6Dialog14AddedToManagerEPNS_13WidgetManagerE");
    Sexy_Dialog_RemovedFromManagerAddr = dlsym(handle,
                                               "_ZN4Sexy6Dialog18RemovedFromManagerEPNS_13WidgetManagerE");


    AlmanacDialog_AddedToManagerAddr = dlsym(handle,
                                             "_ZN13AlmanacDialog14AddedToManagerEPN4Sexy13WidgetManagerE");
    AlmanacDialog_RemovedFromManagerAddr = dlsym(handle,
                                                 "_ZN13AlmanacDialog18RemovedFromManagerEPN4Sexy13WidgetManagerE");
    AlmanacDialog_SetPageAddr = dlsym(handle, "_ZN13AlmanacDialog7SetPageE11AlmanacPage");
    AlmanacDialog_MouseUpAddr = dlsym(handle, "_ZN13AlmanacDialog7MouseUpEiii");


    Sexy_Graphics_GraphicsAddr = dlsym(handle, "_ZN4Sexy8GraphicsC2ERKS0_");
    Sexy_Graphics_DrawImageCelAddr = dlsym(handle, "_ZN4Sexy8Graphics12DrawImageCelEPNS_5ImageEiiii");
    Sexy_Graphics_DrawImageCel2Addr = dlsym(handle, "_ZN4Sexy8Graphics12DrawImageCelEPNS_5ImageEiii");
    Sexy_Graphics_PrepareForReuseAddr = dlsym(handle, "_ZN4Sexy8GraphicsD2Ev");
    Sexy_Graphics_SetColorAddr = dlsym(handle, "_ZN4Sexy8Graphics8SetColorERKNS_5ColorE");
    Sexy_Graphics_ClipRectAddr = dlsym(handle, "_ZN4Sexy8Graphics8ClipRectEiiii");
    Sexy_Graphics_DrawStringAddr = dlsym(handle, "_ZN4Sexy8Graphics10DrawStringERKSsii");
    Sexy_Graphics_FillRectAddr = dlsym(handle, "_ZN4Sexy8Graphics8FillRectERKNS_5TRectIiEE");
    Sexy_Graphics_DrawImageAddr = dlsym(handle, "_ZN4Sexy8Graphics9DrawImageEPNS_5ImageEii");


    Reanimation_ReanimationAddr = dlsym(handle, "_ZN11ReanimationC2Ev");
    Reanimation_ReanimationInitializeTypeAddr = dlsym(handle, "_ZN11Reanimation25ReanimationInitializeTypeEff15ReanimationType");
    Reanimation_DrawAddr = dlsym(handle, "_ZN11Reanimation4DrawEPN4Sexy8GraphicsE");
    Reanimation_PrepareForReuseAddr = dlsym(handle, "_ZN11ReanimationD2Ev");
    Reanimation_DrawRenderGroupAddr = dlsym(handle, "_ZN11Reanimation15DrawRenderGroupEPN4Sexy8GraphicsEi");
    Reanimation_GetCurrentTransformAddr = dlsym(handle, "_ZN11Reanimation19GetCurrentTransformEiP19ReanimatorTransform");
    Reanimation_FindTrackIndexByIdAddr = dlsym(handle, "_ZN11Reanimation18FindTrackIndexByIdEPc");
    Reanimation_PlayReanimAddr = dlsym(handle, "_ZN11Reanimation10PlayReanimEPKc14ReanimLoopTypeif");


    Sexy_GamepadApp_CheckGamepadAddr = dlsym(handle, "_ZN4Sexy10GamepadApp12CheckGamepadEv");
    Sexy_GamepadApp_HasGamepadAddr = dlsym(handle, "_ZN4Sexy10GamepadApp10HasGamepadEv");
    Sexy_Level_isCardNotAllowedToPickAddr = dlsym(handle,
                                                  "_ZN4Sexy5Level22isCardNotAllowedToPickEi");
    Sexy_ScrollbarWidget_MouseDownAddr = dlsym(handle, "_ZN4Sexy15ScrollbarWidget9MouseDownEiiii");
    ImitaterDialog_ImitaterDialogAddr = dlsym(handle, "_ZN14ImitaterDialogC2Ei");
    AttachmentDieAddr = dlsym(handle, "_Z13AttachmentDieR12AttachmentID");
    ReanimatorTransform_ReanimatorTransformAddr = dlsym(handle, "_ZN19ReanimatorTransformC2Ev");
    ZenGarden_RebuildHelpbarAddr = dlsym(handle, "_ZN9ZenGarden14RebuildHelpbarEb");
    CreditScreen_RemovedFromManagerAddr = dlsym(handle,
                                                "_ZN12CreditScreen18RemovedFromManagerEPN4Sexy13WidgetManagerE");
    CursorObject_DrawAddr = dlsym(handle, "_ZN12CursorObject4DrawEPN4Sexy8GraphicsE");
    HelpOptionsDialog_ButtonDepressAddr = dlsym(handle, "_ZN17HelpOptionsDialog13ButtonDepressEi");
    GridItem_DrawScaryPotAddr = dlsym(handle, "_ZN8GridItem12DrawScaryPotEPN4Sexy8GraphicsE");
    GridItem_DrawStinkyAddr = dlsym(handle, "_ZN8GridItem10DrawStinkyEPN4Sexy8GraphicsE");
    GridItem_GridItemDieAddr = dlsym(handle, "_ZN8GridItem11GridItemDieEv");

    ZombieTypeCanGoInPoolAddr = dlsym(handle, "_Z21ZombieTypeCanGoInPool10ZombieType");
    DrawSeedPacketAddr = dlsym(handle, "_Z14DrawSeedPacketPN4Sexy8GraphicsEff8SeedTypeS2_fibbbbb");
    TodDrawStringAddr = dlsym(handle, "_Z13TodDrawStringPN4Sexy8GraphicsERKSsiiPNS_4FontENS_5ColorE23DrawStringJustification");
    GridItem_UpdateAddr = dlsym(handle, "_ZN8GridItem6UpdateEv");
    GridItem_UpdateBrainAddr = dlsym(handle, "_ZN8GridItem11UpdateBrainEv");
    GridItem_UpdateScaryPotAddr = dlsym(handle, "_ZN8GridItem14UpdateScaryPotEv");
    TodDrawImageCelCenterScaledFAddr = dlsym(handle, "_Z28TodDrawImageCelCenterScaledFPN4Sexy8GraphicsEPNS_5ImageEffiff");
    ReanimatorCache_DrawCachedZombieAddr = dlsym(handle, "_ZN15ReanimatorCache16DrawCachedZombieEPN4Sexy8GraphicsEff10ZombieType");
    TodAnimateCurveAddr = dlsym(handle, "_Z15TodAnimateCurveiiiii9TodCurves");
    Sexy_StrFormatAddr = dlsym(handle, "_ZN4Sexy9StrFormatEPKcz");
    GetRectOverlapAddr = dlsym(handle, "_Z14GetRectOverlapRKN4Sexy5TRectIiEES3_");
    FilterEffectCreateImageAddr = dlsym(handle, "_Z23FilterEffectCreateImagePN4Sexy5ImageE12FilterEffect");
    ZenGardenControls_UpdateAddr = dlsym(handle, "_ZN17ZenGardenControls6UpdateEf");
    ZenGarden_GetStinkyAddr = dlsym(handle, "_ZN9ZenGarden9GetStinkyEv");
    ZenGarden_IsStinkyHighOnChocolateAddr = dlsym(handle, "_ZN9ZenGarden23IsStinkyHighOnChocolateEv");
    ZenGarden_MouseDownWithFeedingToolAddr = dlsym(handle, "_ZN9ZenGarden24MouseDownWithFeedingToolEii10CursorTypei");
    AwardScreen_GameButtonDownAddr = dlsym(handle, "_ZN17ZenGardenControls6UpdateEf");
    LawnPlayerInfo_GetFlagAddr = dlsym(handle, "_ZN14LawnPlayerInfo7GetFlagE11PlayerFlags");
    GetFlashingColorAddr = dlsym(handle, "_Z16GetFlashingColorii");


    Sexy_FONT_HOUSEOFTERROR28_Addr = (int *) dlsym(handle, "_ZN4Sexy20FONT_HOUSEOFTERROR28E");
    Sexy_FONT_DWARVENTODCRAFT18_Addr = (int *) dlsym(handle, "_ZN4Sexy22FONT_DWARVENTODCRAFT18E");
    Sexy_IMAGE_PLANTSHADOW2_Addr = (int *) dlsym(handle, "_ZN4Sexy18IMAGE_PLANTSHADOW2E");
    Sexy_IMAGE_SCARY_POT_Addr = (int *) dlsym(handle, "_ZN4Sexy15IMAGE_SCARY_POTE");
    Sexy_IMAGE_SHOVELBANK_Addr = (int *) dlsym(handle, "_ZN4Sexy16IMAGE_SHOVELBANKE");
    Sexy_IMAGE_HAMMER_ICON_Addr = (int *) dlsym(handle, "_ZN4Sexy17IMAGE_HAMMER_ICONE");
    Sexy_IMAGE_HELP_BUTTONS_Addr = (int *) dlsym(handle, "_ZN4Sexy18IMAGE_HELP_BUTTONSE");
    Sexy_IMAGE_HELP_BUTTONS2_Addr = (int *) dlsym(handle, "_ZN4Sexy19IMAGE_HELP_BUTTONS2E");
    Sexy_IMAGE_BUTTER_ICON_Addr = (int *) dlsym(handle, "_ZN4Sexy17IMAGE_BUTTER_ICONE");
    Sexy_IMAGE_SHOVEL_Addr = (int *) dlsym(handle, "_ZN4Sexy12IMAGE_SHOVELE");
    ReanimTrackId_anim_head1_Addr = (int *) dlsym(handle, "ReanimTrackId_anim_head1");
    Sexy_SOUND_PAUSE_Addr = (int *) dlsym(handle, "_ZN4Sexy11SOUND_PAUSEE");
    Sexy_SOUND_BOING_Addr = (int *) dlsym(handle, "_ZN4Sexy11SOUND_BOINGE");
    Sexy_SOUND_GRAVEBUTTON_Addr = (int *) dlsym(handle, "_ZN4Sexy17SOUND_GRAVEBUTTONE");
    Sexy_SOUND_GULP_Addr = (int *) dlsym(handle, "_ZN4Sexy10SOUND_GULPE");
    Sexy_SOUND_SEEDLIFT_Addr = (int *) dlsym(handle, "_ZN4Sexy14SOUND_SEEDLIFTE");
}


#endif //PVZ_TV_1_1_5_HOOKADDR_H
