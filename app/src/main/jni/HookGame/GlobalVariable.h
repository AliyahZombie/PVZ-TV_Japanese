//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_GLOBALVARIABLE_H
#define PVZ_TV_1_1_5_GLOBALVARIABLE_H


int mBoardBackground = -1;  //当前的场景，白天、黑夜、泳池、雾夜、屋顶、月夜、花园、蘑菇园、水族馆、智慧树
int gameState = 1;  //当前是是否正在SeedBank中选择植物种子。其可能的值为：    1：手上没拿种子，也不在SeedBank里选种子     6：正在SeedBank里选种子(我是僵尸模式也会生效哦)     7：已经选择完毕，手上正拿着种子
int dialogCount = 0; //当前对话框数量。如果这个数字大于0，则说明有对话框。
int maxPlantsNumInSeedBank = 0;  //SeedBank中的植物卡片数量
int gameIndex = 0; //小游戏索引
int VSSetupState = 0;//对战状态
bool isMainMenu = true; //游戏是否在主界面

bool isSeedChooseHas7Rows = false;//玩家在选择种子界面是否拥有7行的植物
bool isSeedChoosingNow = false;//游戏是否在选择种子界面
bool isInVSSetupMenu = false;//游戏是否在对战开始前的选择种子界面
bool hasNewOptionsDialog = false;//是否存在暂停菜单
bool isAwardScreen = false; //游戏是否在关卡完成时的奖励界面
bool isImitaterEnabled = false;//玩家是否拥有模仿者植物
bool isStoreEnabled = false;//玩家是否拥有商店
bool isAlmanacEnabled = false;//玩家是否拥有图鉴
bool isImitaterChooser = false;//游戏是否在模仿者选择种子界面
bool isStartButtonEnabled = false;//选择种子界面的“开始按钮”是否可以点击（即种子是否选满了）
bool isCrazyDaveShowing = false;//是否存在疯狂戴夫正与你对话
bool isVaseBreakerMode = false;//当前游戏是否为砸罐子模式
bool isWhackAZombie = false;//游戏是否在砸僵尸模式
bool isShovelEnabled = false;//当前关卡是否拥有铲子
bool isAlmanacDialogExist = false;//游戏是否在图鉴界面
bool isDaveStore = false;//游戏是否在商店界面
bool isSurvivalRepick = false;//游戏是否为生存模式打完第一面旗帜之后的带有“查看草坪”按钮的选卡界面
bool isCreditScreen = false;//是否在制作人员界面
bool isChallengeScreen = false;//游戏是否在小游戏列表界面
bool isInShovelTutorial = false;//冒险模式1-5开头的铲子教学模式
int gridX = 0;//Board光标横坐标
int gridY = 0;//Board光标纵坐标
bool requestPause = false;
bool requestPlayPauseSound = false;
bool requestPlayResumeSound = false;

int gameState_2P = 1;
int gridX_2P = 0;//Board光标横坐标
int gridY_2P = 0;//Board光标纵坐标

//用于检查（row,col）处是否为一个充能完毕的加农炮
bool requestValidCobCannonCheckByGrid = false;
int row = 0;
int col = 0;
bool requestValidCobCannonCheckByXY = false;
bool isCobCannonSelected = false;
float cobToCheckX = 0;
float cobToCheckY = 0;
bool requestValidCobCannonCheckByXY_2P = false;
bool isCobCannonSelected_2P = false;
float cobToCheckX_2P = 0;
float cobToCheckY_2P = 0;


//用于拿起加农炮
bool requestCobCannonPickUp = false;
bool requestCobCannonPickUp_2P = false;

//用于设定SeedBank中的光标位置
int seekBankPositionOrigin = 0;
int seekBankPositionToSet = 0;
bool requestSetSeedBankPosition = false;
int seekBankPositionOrigin_2P = 0;
int seekBankPositionToSet_2P = 0;
bool requestSetSeedBankPosition_2P = false;

//用于设定Board中的光标位置
float boardPositionXToSet = 80;
float boardPositionYToSet = 130;
bool requestSetBoardPositionByXY = false;
float boardPositionXToSet_2P = 80;
float boardPositionYToSet_2P = 130;
bool requestSetBoardPositionByXY_2P = false;

//用于native层发送按键
bool requestButtonDown = false;
int buttonCode1 = 0;
bool requestButtonDown_2P = false;
int buttonCode1_2P = 0;
bool requestButtonUp_2P = false;
int buttonCode2_2P = 0;

//用于设定选卡状态
bool requestSetGameState = false;
int stateToSet = 0;
bool requestSetGameState_2P = false;
int stateToSet_2P = 0;


bool requestCheckAndSelectSeedPacket = false;
float checkSeedPacketX = 0;
bool requestCheckAndSelectSeedPacket_2P = false;
float checkSeedPacketX_2P = 0;

//用于小游戏界面滚动
bool requestSetScrollTarget = false;
int scrollTarget = 0;
int scrollOffset = 0;


//用于商店界面的触控
bool requestSetStoreSelectedSlot = false;
bool isDaveTalkingInStore = false;
int slotToSet = 0;
int selectedStoreItem = 0;




//铲子
bool requestShovelDown = false;
bool requestClearCursor = false;
bool requestPlayFoley = false;
bool requestDrawShovelInCursor = false;
int foleyToPlay = 0;

//2P黄油绘制
bool requestDrawButterInCursor = false;

//光标类型
int cursorType = 0;

bool requestCheckAndSelectUsefulSeedPacket = false;
bool requestPlantUsefulSeedPacket = false;

bool requestQuickDig = false;
bool hasConveyOrBelt = false;

bool keyboardMode = false;

int VSBackGround = 0;

bool CoolDownSeedPacketButt = false;//选卡冷却开关

bool projectilePierce = false;

bool seedChooseFinished1P = false, seedChooseFinished2P = false;
bool requestChooseSeed2P = false;
int chooseSeed2PX = 0;
int chooseSeed2PY = 0;

bool requestClickSeedInBank = false;
int seedToClick = 0;

//bool elevenSeeds = false;
bool normalLevel = false; //恢复一二周目正常出怪

int speedUpMode = 0;
int speedUpCounter = 0;

#endif //PVZ_TV_1_1_5_GLOBALVARIABLE_H
