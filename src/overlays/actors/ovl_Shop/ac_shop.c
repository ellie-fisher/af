/*
 * File: ac_shop.c
 * Overlay: ovl_Shop
 * Description: Nook's Cranny
 */

#include "ac_shop.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "macros.h"
#include "m_time.h"
#include "m_event.h"
#include "code_variables.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "6E3240.h"
#include "overlays/actors/player_actor/m_player.h"
#include "m_player_lib.h"

#define THIS ((Shop*)thisx)

void aSHOP_actor_ct(Actor* thisx, Game_Play* game_play);
void aSHOP_actor_dt(Actor* thisx, Game_Play* game_play);
void aSHOP_actor_init(Actor* thisx, Game_Play* game_play);
void aSHOP_actor_draw(Actor* thisx, Game_Play* game_play);
void aSHOP_actor_move(Actor* thisx, Game_Play* game_play);

void func_80A0DD54_jp(Actor* thisx, s32 arg0);
void func_80A0E1F0_jp(Actor* thisx);
void func_80A0E4A8_jp(Actor* thisx, s32 arg0);

#if 0
ActorProfile Shop_Profile = {
    /* */ ACTOR_SHOP,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5804,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Shop),
    /* */ aSHOP_actor_ct,
    /* */ aSHOP_actor_dt,
    /* */ aSHOP_actor_init,
    /* */ aSHOP_actor_draw,
    /* */ NULL,
};

static BaseSkeletonR* D_80A0E9E0_jp[2] = { (BaseSkeletonR*)0x0605A3AC, (BaseSkeletonR*)0x0605C3EC };
#endif

extern BaseSkeletonR* D_80A0E9E0_jp[];

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/aSHOP_actor_ct.s")
void aSHOP_actor_ct(Actor* thisx, Game_Play* game_play) {
    s32 var_v0;
    s32 var_v1;
    Player* player;
    s32 var_v2;
    s32 var_v3;
    s32 var_v4;
    Shop* this = THIS;
    StructureActor* shop = &this->structureActor;

    player = get_player_actor_withoutCheck(game_play);
    var_v2 = common_data.time.season == 3;
    var_v3 = 1;

    SegmentBaseAddress[6] =
        (uintptr_t)OS_PHYSICAL_TO_K0(common_data.clip.structureClip->getObjectSegment(STRUCTURE_TYPE_SHOP));

    cKF_SkeletonInfo_R_ct(&shop->skeletonInfo, D_80A0E9E0_jp[var_v2], NULL, shop->jointTable, shop->morphTable);
    func_80A0DD54_jp(thisx, 1);

    thisx->world.pos.x += -20.0f;
    thisx->uncullZoneScale = 550.0f;
    thisx->unk_140 = 550.0f;
    thisx->world.pos.z += 20.0f;
    thisx->unk_144 = 80.0f;

    if (func_800C2578_jp() != 2) {
        var_v3 = 0;
    }

    var_v0 = (s32)(thisx->world.pos.x - 68.29f);
    var_v1 = (s32)(thisx->world.pos.z + 68.29f);
    var_v4 = var_v3;

    if ((var_v0 == (s32)player->actor.world.pos.x) && (var_v1 == (s32)player->actor.world.pos.z)) {
        var_v4 = 1;
    }

    func_80A0E4A8_jp(thisx, var_v4);

    shop->unk_174 = cKF_SkeletonInfo_R_play(&shop->skeletonInfo);
    shop->unk_1E8 = 1;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/aSHOP_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0DD54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0DED4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0DFD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E02C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E0DC_jp.s")

//#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E1F0_jp.s")
void func_80A0E1F0_jp(Actor* thisx) {
    s32 timeSec;
    Shop* this = THIS;

    timeSec = common_data.time.nowSec;

    if (func_8007D650_jp() == 1) {
        this->structureActor.unk_2B8 = 0;

        if ((func_800C2578_jp() == 2) &&
            ((timeSec >= mTM_TIME_TO_SEC(18, 0, 0) || timeSec < mTM_TIME_TO_SEC(5, 0, 0)))) {
            this->structureActor.unk_2B8 = 1;
        }
    } else {
        if (timeSec < mTM_TIME_TO_SEC(18, 0, 0) || timeSec >= mTM_TIME_TO_SEC(22, 0, 0)) {
            this->structureActor.unk_2B8 = 0;
            return;
        } else if (func_800C2578_jp() == 2) {
            this->structureActor.unk_2B8 = 1;
            return;
        }

        this->structureActor.unk_2B8 = 0;
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E2B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E334_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E440_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E474_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E4A8_jp.s")

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/aSHOP_actor_move.s")
void aSHOP_actor_move(Actor* thisx, Game_Play* game_play) {
    Shop* this = THIS;
    StructureActor* shop = &this->structureActor;

    SegmentBaseAddress[6] =
        (uintptr_t)OS_PHYSICAL_TO_K0(common_data.clip.structureClip->getObjectSegment(STRUCTURE_TYPE_SHOP));

    shop->unk_174 = cKF_SkeletonInfo_R_play(&shop->skeletonInfo);
    shop->unk_1E8 = shop->skeletonInfo.frameControl.currentFrame;

    ((ShopActionFunc)shop->process)(this, game_play);
    func_80A0E1F0_jp(thisx);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/aSHOP_actor_init.s")
void aSHOP_actor_init(Actor* thisx, Game_Play* game_play) {
    Shop* this = THIS;
    StructureActor* shop = &this->structureActor;

    mFI_SetFG_common(0xF0E3, shop->actor.home.pos, 0);
    aSHOP_actor_move(&shop->actor, game_play);

    shop->actor.update = aSHOP_actor_move;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E654_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E6E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/aSHOP_actor_draw.s")
