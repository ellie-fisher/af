#include "ac_shop.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "macros.h"
#include "code_variables.h"
#include "overlays/gamestates/ovl_play/m_play.h"

#define THIS ((Shop*)thisx)

void aSHOP_actor_ct(Actor* thisx, Game_Play* game_play);
void aSHOP_actor_dt(Actor* thisx, Game_Play* game_play);
void aSHOP_actor_init(Actor* thisx, Game_Play* game_play);
void aSHOP_actor_draw(Actor* thisx, Game_Play* game_play);
void aSHOP_actor_move(Actor* thisx, Game_Play* game_play);
void func_80A0E1F0_jp(Actor* thisx);

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
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/aSHOP_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/aSHOP_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0DD54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0DED4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0DFD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E02C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E0DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Shop/ac_shop/func_80A0E1F0_jp.s")

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
