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
#include "overlays/actors/player_actor/m_player.h"
#include "6E3240.h"
#include "m_player_lib.h"
#include "m_common_data.h"
#include "m_bgm.h"
#include "m_collision_bg.h"
#include "m_rcp.h"

#define THIS ((Shop*)thisx)

void aSHOP_actor_ct(Actor* thisx, Game_Play* game_play);
void aSHOP_actor_dt(Actor* thisx, Game_Play* game_play);

void aSHOP_set_bgOffset(Shop* this, s32 heightTableIndex);
void func_80A0DED4_jp(Shop* this, Game_Play* game_play);

s32 func_80A0DFD0_jp(Game_Play* game_play);
s32 func_80A0E02C_jp(Shop* this, Game_Play* game_play);
void func_80A0E0DC_jp(Shop* this);

void func_80A0E1F0_jp(Actor* thisx);

void func_80A0E2B4_jp(Shop* this, Game_Play* game_play);
void func_80A0E334_jp(Shop* this, Game_Play* game_play);
void func_80A0E440_jp(Shop* this, Game_Play* game_play);
void func_80A0E474_jp(Shop* this, Game_Play* game_play);

void aSHOP_setupAction(Shop* this, s32 processIndex);

void aSHOP_actor_move(Actor* thisx, Game_Play* game_play);
void aSHOP_actor_init(Actor* thisx, Game_Play* game_play);

s32 aSHOP_actor_draw_before(Game_Play* game_play, SkeletonInfoR* skeletonInfo, s32 jointIndex, Gfx** dlist,
                            u8* displayBufferFlag, void* thisx, s_xyz* rotation, xyz_t* translation);
s32 aSHOP_actor_draw_after(Game_Play* game_play, SkeletonInfoR* skeletonInfo, s32 jointIndex, Gfx** dlist,
                           u8* displayBufferFlag, void* thisx, s_xyz* rotation, xyz_t* translation);

void aSHOP_actor_draw(Actor* thisx, Game_Play* game_play);

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
static u8 D_80A0E9C4_jp[8] = { 1, 0, 1, 0, 1, 0, 0, 1 };
static ShadowData D_80A0E9CC_jp = { 8, D_80A0E9C4_jp, 60.0f, (Vtx *)0x06006578, (Gfx *)0x060065F8 };
static f32 D_FLT_80A0EA9C_jp[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
static f32 D_FLT_80A0EAAC_jp[4] = { 1.0f, 16.0f, 16.0f, 1.0f };
static f32 D_FLT_80A0EABC_jp[4] = { 1.0f, 16.0f, 1.0f, 16.0f };
static ShopActionFunc D_80A0EACC_jp[4] = { func_80A0E2B4_jp, func_80A0E334_jp, func_80A0E440_jp, func_80A0E474_jp };
#endif

extern BaseSkeletonR* D_80A0E9E0_jp[];
extern mCoBG_unkStruct2* D_80A0EA6C_jp[];
extern f32 D_FLT_80A0EA74_jp[4];
extern f32 D_80A0EA84_jp[4];
extern u8 D_80A0E9C4_jp[];
extern ShadowData D_80A0E9CC_jp;
extern BaseAnimationR* D_80A0EA94_jp[];
extern f32 D_FLT_80A0EA9C_jp[];
extern f32 D_FLT_80A0EAAC_jp[];
extern f32 D_FLT_80A0EABC_jp[];
extern ShopActionFunc D_80A0EACC_jp[];
extern s32 D_80A0EADC_jp[];

void aSHOP_actor_ct(Actor* thisx, Game_Play* game_play) {
    s32 var_v0;
    s32 var_v1;
    Player* player;
    s32 isWinter;
    s32 processIndex;
    UNUSED s32 pad;

    Shop* this = THIS;
    StructureActor* shop = &this->structureActor;
    player = get_player_actor_withoutCheck(game_play);
    isWinter = common_data.time.season == WINTER;
    processIndex = 1;

    SegmentBaseAddress[6] =
        (uintptr_t)OS_PHYSICAL_TO_K0(common_data.clip.structureClip->getObjectSegment(STRUCTURE_TYPE_SHOP));

    cKF_SkeletonInfo_R_ct(&shop->skeletonInfo, D_80A0E9E0_jp[isWinter], NULL, shop->jointTable, shop->morphTable);
    aSHOP_set_bgOffset(this, 1);

    thisx->world.pos.x += -20.0f;
    thisx->uncullZoneScale = 550.0f;
    thisx->unk_140 = 550.0f;
    thisx->world.pos.z += 20.0f;
    thisx->unk_144 = 80.0f;

    if (func_800C2578_jp() != 2) {
        processIndex = 0;
    }

    var_v0 = (s32)(thisx->world.pos.x - 68.29f);
    var_v1 = (s32)(thisx->world.pos.z + 68.29f);

    if ((var_v0 == (s32)player->actor.world.pos.x) && (var_v1 == (s32)player->actor.world.pos.z)) {
        processIndex = 1;
    }

    aSHOP_setupAction(this, processIndex);

    shop->unk_174 = cKF_SkeletonInfo_R_play(&shop->skeletonInfo);
    shop->unk_1E8 = 1;
}

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

void aSHOP_set_bgOffset(Shop* this, s32 heightTableIndex) {
    s32 i;
    s32 j;
    mCoBG_unkStruct2* offsetTable;
    xyz_t pos;

    offsetTable = D_80A0EA6C_jp[heightTableIndex];

    for (i = 0; i < ARRAY_COUNT(D_80A0EA84_jp); i++) {
        pos.z = D_80A0EA84_jp[i] + this->structureActor.actor.home.pos.z;

        for (j = 0; j < ARRAY_COUNT(D_FLT_80A0EA74_jp); j++) {
            if (i * 4 + j != 0 && i * 4 + j != 3 && i * 4 + j != 12 && i * 4 + j != 15) {
                pos.x = this->structureActor.actor.home.pos.x + D_FLT_80A0EA74_jp[j];
                mCoBG_SetPluss5PointOffset_file(pos, *offsetTable, "../ac_shop_move.c_inc", 162);
            }

            offsetTable++;
        }
    }
}

void func_80A0DED4_jp(Shop* this, Game_Play* game_play) {
    CommonData* data = &common_data;
    xyz_t pos;

    if (game_play->unk_1EE3 == 0) {
        data->structureExitDoorData.nextSceneId = data->save.sceneNo;
        data->structureExitDoorData.exitOrientation = 7;
        data->structureExitDoorData.exitType = 0;
        data->structureExitDoorData.params = 3;

        pos.x = this->structureActor.actor.world.pos.x - 68.29f;
        pos.z = this->structureActor.actor.world.pos.z + 68.29f;
        pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(pos, 0.0f);

        data->structureExitDoorData.exitPos.x = (s16)pos.x;
        data->structureExitDoorData.exitPos.y = (s16)pos.y;
        data->structureExitDoorData.exitPos.z = (s16)pos.z;
        data->structureExitDoorData.fgName = 0x5804;
        data->structureExitDoorData.wipeType = 1;

        mBGMPsComp_make_ps_wipe(0x28A);
    }
}

s32 func_80A0DFD0_jp(Game_Play* game_play) {
    Player* player = get_player_actor_withoutCheck(game_play);
    s32 var_v0 = 0;

    if ((u16)player->actor.world.rot.y >= 0x4001 && (u16)player->actor.world.rot.y < 0x8000 &&
        player->actor.speed > 0.0f) {
        var_v0 = 1;
    }

    return var_v0;
}

s32 func_80A0E02C_jp(Shop* this, Game_Play* game_play) {
    Player* player = get_player_actor_withoutCheck(game_play);
    s32 var_v0 = 0;
    f32 diffX;
    f32 diffZ;

    if (player == NULL) {
        return 0;
    }

    diffX = player->actor.world.pos.x - (this->structureActor.actor.world.pos.x - 38.0f);
    diffZ = player->actor.world.pos.z - (this->structureActor.actor.world.pos.z + 42.0f);

    if ((u16)player->actor.shape.rot.y >= 0x4001 && (u16)player->actor.shape.rot.y < 0x8000 &&
        (diffX * diffX + diffZ * diffZ) < 550.0f) {
        var_v0 = 1;
    }

    return var_v0;
}

void func_80A0E0DC_jp(Shop* this UNUSED) {
    s32 timeSec;
    Color_RGBA8 color;
    s32 msgNum;

    timeSec = common_data.time.nowSec;

    if (func_8007D318_jp(0) != 0) {
        if (func_800C2578_jp() == 0) {
            msgNum = 0x7D1;
        } else {
            msgNum = 0x7D9;
        }
    } else if ((common_data.time.rtcTime.day ==
                lbRTC_GetDaysByMonth(common_data.time.rtcTime.year, common_data.time.rtcTime.month)) &&
               timeSec >= 0x5460) {
        if (func_800C2578_jp() == 0) {
            msgNum = 0x7D6;
        } else {
            msgNum = 0x7D7;
        }
    } else if (func_800C2578_jp() == 3) {
        msgNum = 0x7D8;
    } else {
        msgNum = 0x7CD;
    }

    mDemo_Set_msg_num(msgNum);
    mDemo_Set_talk_display_name(0);
    mDemo_Set_camera(1);
    mPlib_Set_able_hand_all_item_in_demo(1);
    mDemo_Set_ListenAble();

    color.r = 0x91;
    color.g = 0x3C;
    color.b = 0x28;
    color.a = 0xFF;

    mDemo_Set_talk_window_color(&color);
}

void func_80A0E1F0_jp(Actor* thisx) {
    s32 timeSec = common_data.time.nowSec;
    Shop* this = THIS;

    if (func_8007D650_jp() == 1) {
        this->structureActor.unk_2B8 = 0;

        if (func_800C2578_jp() == 2 && ((timeSec >= mTM_TIME_TO_SEC(18, 0, 0) || timeSec < mTM_TIME_TO_SEC(5, 0, 0)))) {
            this->structureActor.unk_2B8 = 1;
        }
    } else if (timeSec < mTM_TIME_TO_SEC(18, 0, 0) || timeSec >= mTM_TIME_TO_SEC(22, 0, 0)) {
        this->structureActor.unk_2B8 = 0;
    } else if (func_800C2578_jp() == 2) {
        this->structureActor.unk_2B8 = 1;
    } else {
        this->structureActor.unk_2B8 = 0;
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E2B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E334_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E440_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E474_jp.s")

void aSHOP_setupAction(Shop* this, s32 processIndex) {
    f32 speed = D_FLT_80A0EA9C_jp[processIndex];
    s32 isWinter = common_data.time.season == WINTER;

    cKF_SkeletonInfo_R_init(&this->structureActor.skeletonInfo, this->structureActor.skeletonInfo.skeleton,
                            D_80A0EA94_jp[isWinter], 1.0f, D_FLT_80A0EABC_jp[processIndex],
                            D_FLT_80A0EAAC_jp[processIndex], speed, 0.0f, ANIMATION_STOP, NULL);

    this->structureActor.process = D_80A0EACC_jp[processIndex];
    this->structureActor.unk_2B4 = processIndex;
}

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

void aSHOP_actor_init(Actor* thisx, Game_Play* game_play) {
    Shop* this = THIS;
    StructureActor* shop = &this->structureActor;

    mFI_SetFG_common(0xF0E3, shop->actor.home.pos, 0);
    aSHOP_actor_move(&shop->actor, game_play);

    shop->actor.update = aSHOP_actor_move;
}

s32 aSHOP_actor_draw_before(Game_Play* game_play, SkeletonInfoR* skeletonInfo UNUSED, s32 jointIndex, Gfx** dlist,
                            u8* displayBufferFlag UNUSED, void* thisx, s_xyz* rotation UNUSED,
                            xyz_t* translation UNUSED) {
    Shop* this = THIS;
    GraphicsContext* gfxCtx = game_play->state.gfxCtx;

    if (jointIndex == 5) {
        OPEN_POLY_OPA_DISP(gfxCtx);
        gDPPipeSync(__polyOpa++);

        if (this->structureActor.unk_2B8 != 0) {
            gDPSetEnvColor(__polyOpa++, 0xFF, 0xFF, 0x96, 0x78);
        } else {
            gDPSetEnvColor(__polyOpa++, 0x00, 0x00, 0x00, 0x00);
        }

        CLOSE_POLY_OPA_DISP(gfxCtx);
    } else if (jointIndex == 6) {
        *dlist = NULL;
    }

    return 1;
}

s32 aSHOP_actor_draw_after(Game_Play* game_play, SkeletonInfoR* skeletonInfo UNUSED, s32 jointIndex, Gfx** dlist UNUSED,
                           u8* displayBufferFlag UNUSED, void* thisx, s_xyz* rotation UNUSED,
                           xyz_t* translation UNUSED) {
    GraphicsContext* gfxCtx;
    Shop* this = THIS;
    s32 object;
    u16* palette;
    s32 isWinter;
    Mtx* mtx;

    gfxCtx = game_play->state.gfxCtx;

    if (jointIndex == 6) {
        mtx = _Matrix_to_Mtx_new(gfxCtx);

        if (mtx != NULL) {
            object = common_data.clip.structureClip->getObjectSegment(STRUCTURE_TYPE_SHOP);
            palette = common_data.clip.structureClip->getPalSegment(STRUCTURE_PALETTE_SHOP);
            isWinter = common_data.time.season == WINTER;

            _texture_z_light_fog_prim_shadow(gfxCtx);

            OPEN_SHADOW_DISP(gfxCtx);
            gSPSegment(__shadow_gfx++, G_MWO_SEGMENT_8, palette);
            gSPSegment(__shadow_gfx++, G_MWO_SEGMENT_6, object);
            gDPPipeSync(__shadow_gfx++);

            if (this->structureActor.unk_2B8 != 0) {
                gDPSetPrimColor(__shadow_gfx++, 0, 0x78, 0xFF, 0xFF, 0x96, 0x00);
            } else {
                gDPSetPrimColor(__shadow_gfx++, 0, 0, 0x00, 0x00, 0x00, 0x00);
            }

            gSPMatrix(__shadow_gfx++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(__shadow_gfx++, D_80A0EADC_jp[isWinter]);
            CLOSE_SHADOW_DISP(gfxCtx);
        }
    }

    return 1;
}

void aSHOP_actor_draw(Actor* thisx, Game_Play* game_play) {
    GraphicsContext* gfxCtx = game_play->state.gfxCtx;
    Shop* this = THIS;
    SkeletonInfoR* skeletonInfo = &this->structureActor.skeletonInfo;
    Mtx* mtx;
    s32 object;
    u16* palette;
    u8 numberOfDisplayLists = skeletonInfo->skeleton->unk01;

    mtx = GRAPH_ALLOC_NO_ALIGN(gfxCtx, sizeof(Mtx) * numberOfDisplayLists);

    if (mtx != NULL) {
        object = common_data.clip.structureClip->getObjectSegment(STRUCTURE_TYPE_SHOP);
        palette = common_data.clip.structureClip->getPalSegment(STRUCTURE_PALETTE_SHOP);

        _texture_z_light_fog_prim_npc(gfxCtx);

        OPEN_POLY_OPA_DISP(gfxCtx);
        gSPSegment(__polyOpa++, G_MWO_SEGMENT_8, palette);
        SegmentBaseAddress[6] = (uintptr_t)OS_PHYSICAL_TO_K0(object);
        gSPSegment(__polyOpa++, G_MWO_SEGMENT_6, object);
        CLOSE_POLY_OPA_DISP(gfxCtx);

        cKF_Si3_draw_R_SV(game_play, skeletonInfo, mtx, aSHOP_actor_draw_before, aSHOP_actor_draw_after, this);

        common_data.clip.unk_074->unk_04(game_play, &D_80A0E9CC_jp, STRUCTURE_TYPE_SHOP);
    }
}
