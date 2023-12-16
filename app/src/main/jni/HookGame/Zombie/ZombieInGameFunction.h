//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_ZOMBIEINGAMEFUNCTION_H
#define PVZ_TV_1_1_5_ZOMBIEINGAMEFUNCTION_H

int (*Zombie_DieNoLoot)(int Zombie_this);

int (*Zombie_ApplyBurn)(int Zombie_this);

int *(*Zombie_ApplyButter)(int *zombie);

void (*Zombie_GetZombieRect)(int *a1, int *a2);

bool (*Zombie_IsImmobilizied)(int *zombie);

bool (*Zombie_EffectedByDamage)(unsigned int zombie, int flag);

void (*Zombie_RemoveColdEffects)(unsigned int zombie);

void (*Zombie_StartEating)(int *);

void (*Zombie_TakeDamage)(int *, int, unsigned int);

bool (*Zombie_IsWalkingBackwards)(int *);

#endif //PVZ_TV_1_1_5_ZOMBIEINGAMEFUNCTION_H
