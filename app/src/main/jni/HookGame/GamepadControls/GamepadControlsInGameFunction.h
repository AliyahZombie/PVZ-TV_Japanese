//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_GAMEPADCONTROLSINGAMEFUNCTION_H
#define PVZ_TV_1_1_5_GAMEPADCONTROLSINGAMEFUNCTION_H

int (*GamepadControls_GetSeedBank)(int a);

int (*GamepadControls_OnButtonDown)(int a1, int a2, int a3, unsigned int a4);

// a3 根据手柄决定是0还是1
// a4 恒定为0
// a2 是按键键值，对应关系如下：

// 左摇杆上 0
// 左摇杆下 1
// 左摇杆左 2
// 左摇杆右 3

// 未知键 4
// 暂停键 5

// A 6
// B 7
// X 8
// Y 9

// L1 10
// R1 11
// L2 12
// R2 13

// TL 14
// TR 15

// 上 16
// 下 17
// 左 18
// 右 19

int (*GamepadControls_OnButtonUp)(int a1, int a2, int a3, unsigned int a4);

int (*GamepadControls_OnKeyDown)(int a1, int a2, unsigned int a3);

// 确定 13 1096
// 返回 27 1096

// 左 37 1096
// 上 38 1096
// 右 39 1096
// 下 40 1096

// 铲子 49 1112
// 铲子 50 1112

#endif //PVZ_TV_1_1_5_GAMEPADCONTROLSINGAMEFUNCTION_H
