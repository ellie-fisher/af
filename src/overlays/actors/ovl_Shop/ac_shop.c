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

void func_80A0E2B4_jp(Shop* this, Game_Play* game_play);
void func_80A0E334_jp(Shop* this, Game_Play* game_play);
void func_80A0E440_jp(Shop* this, Game_Play* game_play);
void func_80A0E474_jp(Shop* this, Game_Play* game_play);

void func_80A0DD54_jp(Actor* thisx, s32 arg0);
void func_80A0E1F0_jp(Actor* thisx);
void aSHOP_setupAction(Shop* this, s32 processIndex);

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
static mCoBG_unkStruct2* D_80A0EA6C_jp[];
static f32 D_FLT_80A0EA74_jp[4] = { -80.0f, -40.0f, 0.0f, 40.0f };
static f32 D_80A0EA84_jp[4] = { 80.0f, 40.0f, 0.0f, -40.0f };
static BaseAnimationR* D_80A0EA94_jp[2] = { (BaseAnimationR*)0x0605A410, (BaseAnimationR*)0x0605C450 };
static f32 D_FLT_80A0EA9C_jp[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
static f32 D_FLT_80A0EAAC_jp[4] = { 1.0f, 16.0f, 16.0f, 1.0f };
static f32 D_FLT_80A0EABC_jp[4] = { 1.0f, 16.0f, 1.0f, 16.0f };
static ShopActionFunc D_80A0EACC_jp[];
#endif

extern BaseSkeletonR* D_80A0E9E0_jp[];
extern mCoBG_unkStruct2* D_80A0EA6C_jp[];
extern f32 D_FLT_80A0EA74_jp[4];
extern f32 D_80A0EA84_jp[4];
extern BaseAnimationR* D_80A0EA94_jp[];
extern f32 D_FLT_80A0EA9C_jp[];
extern f32 D_FLT_80A0EAAC_jp[];
extern f32 D_FLT_80A0EABC_jp[];
extern ShopActionFunc D_80A0EACC_jp[];

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

    aSHOP_setupAction(this, var_v4);

    shop->unk_174 = cKF_SkeletonInfo_R_play(&shop->skeletonInfo);
    shop->unk_1E8 = 1;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/aSHOP_actor_dt.s")
void aSHOP_actor_dt(Actor* thisx, Game_Play* game_play UNUSED) {
    Shop* this = THIS;

    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->objectSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->objectSegmentTable),
                                                       STRUCTURE_TYPE_SHOP, thisx);
    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->paletteSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->paletteSegmentTable),
                                                       STRUCTURE_PALETTE_SHOP, thisx);
    common_data.clip.structureClip->removeInstanceProc(common_data.clip.structureClip->shadowSegmentTable,
                                                       ARRAY_COUNT(common_data.clip.structureClip->shadowSegmentTable),
                                                       STRUCTURE_TYPE_SHOP, thisx);

    cKF_SkeletonInfo_R_dt(&this->structureActor.skeletonInfo);

    thisx->world.pos.x -= -20.0f;
    thisx->world.pos.z -= 20.0f;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0DD54_jp.s")
void func_80A0DD54_jp(Actor* thisx, s32 arg0) {
    s32 i;
    s32 j;
    mCoBG_unkStruct2* offsetTable;
    xyz_t pos;

    offsetTable = D_80A0EA6C_jp[arg0];

    for (j = 0; j < 4; j++) {
        pos.z = D_80A0EA84_jp[j] + thisx->home.pos.z;

        for (i = 0; i < 4; i++) {
            if (j * 4 + i != 0 && j * 4 + i != 3 && j * 4 + i != 12 && j * 4 + i != 15) {
                pos.x = thisx->home.pos.x + D_FLT_80A0EA74_jp[i];
                mCoBG_SetPluss5PointOffset_file(pos, *offsetTable, "../ac_shop_move.c_inc", 162);
            }

            offsetTable++;
        }
    }
}

// void func_80A0DD54_jp(void *arg0, s32 arg1) {
//     f32 sp68;
//     f32 sp60;
//     s32 sp5C;
//     f32 *sp58;
//     ? *var_s2;
//     f32 *temp_t0;
//     s32 var_s0;
//     s32 var_s1;

//     var_s2 = D_80A0EA6C_jp[arg1];
//     sp58 = D_80A0EA84_jp;
//     sp5C = 0;
//     do {
//         var_s1 = 0;
//         var_s0 = sp5C;
//         sp68 = *sp58 + arg0->unk14;
// loop_2:
//         if ((var_s0 != 0) && (var_s0 != 3) && (var_s0 != 0xC) && (var_s0 != 0xF)) {
//             sp60 = D_FLT_80A0EA74_jp[var_s1] + arg0->unkC;
//             mCoBG_SetPluss5PointOffset_file(/* xyz_t+0x0 */ subroutine_arg0, /* xyz_t+0x4 */ sp60.unk4, /* xyz_t+0x8
//             */ sp60.unk8, /* mCoBG_unkStruct2+0x0 */ subroutine_arg3, /* mCoBG_unkStruct2+0x4 */ var_s2->unk4,
//             "../ac_shop_move.c_inc", 0xA2, /* extra? */ var_s2->unk5, /* extra? */ var_s2->unk6);
//         }
//         var_s1 += 1;
//         var_s0 += 1;
//         var_s2 += 7;
//         if (var_s1 != 4) {
//             goto loop_2;
//         }
//         temp_t0 = &sp58[1];
//         sp58 = temp_t0;
//         sp5C += 4;
//     } while (temp_t0 != &D_80A0EA94_jp);
// }

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0DED4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0DFD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E02C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E0DC_jp.s")

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E1F0_jp.s")
void func_80A0E1F0_jp(Actor* thisx) {
    s32 timeSec = common_data.time.nowSec;
    Shop* this = THIS;

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

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/aSHOP_setupAction.s")
void aSHOP_setupAction(Shop* this, s32 processIndex) {
    f32 var_v0 = D_FLT_80A0EA9C_jp[processIndex];
    s32 var_v1 = common_data.time.season == 3;

    cKF_SkeletonInfo_R_init(&this->structureActor.skeletonInfo, this->structureActor.skeletonInfo.skeleton,
                            D_80A0EA94_jp[var_v1], 1.0f, D_FLT_80A0EABC_jp[processIndex],
                            D_FLT_80A0EAAC_jp[processIndex], var_v0, 0.0f, ANIMATION_STOP, NULL);

    this->structureActor.process = D_80A0EACC_jp[processIndex];
    this->structureActor.unk_2B4 = processIndex;
}

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
