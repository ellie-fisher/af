#ifndef AC_SHOP_H
#define AC_SHOP_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"
#include "overlays/actors/ovl_Structure/ac_structure.h"

struct Game_Play;
struct Shop;

typedef void (*ShopActionFunc)(struct Shop*, struct Game_Play*);

typedef struct Shop {
    /* 0x000 */ StructureActor structureActor;
} Shop; // size = 0x2D8

#endif
