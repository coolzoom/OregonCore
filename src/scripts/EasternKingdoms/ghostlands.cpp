/*
 * This file is part of the OregonCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* ScriptData
SDName: Ghostlands
SD%Complete: 100
SDComment: Quest support: 9692, 9212. Obtain Budd's Guise of Zul'aman. Vendor Rathis Tomber
SDCategory: Ghostlands
EndScriptData */

/* ContentData
npc_blood_knight_dawnstar
npc_budd_nedreck
npc_rathis_tomber
npc_ranger_lilatha
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptedGossip.h"

/*######
## npc_blood_knight_dawnstar
######*/

#define GOSSIP_H_BKD "Take Blood Knight Insignia"





/*######
## npc_budd_nedreck
######*/

#define GOSSIP_HBN "You gave the crew disguises?"





/*######
## npc_rathis_tomber
######*/





/*#####
## go_gilded_brazier (Paladin First Trail quest (9678))
#####*/

;

/*######
## npc_ranger_lilatha
######*/

enum eEnums
{
    SAY_START           = -1000140,
    SAY_PROGRESS1       = -1000141,
    SAY_PROGRESS2       = -1000142,
    SAY_PROGRESS3       = -1000143,
    SAY_END1            = -1000144,
    SAY_END2            = -1000145,
    SAY_CAPTAIN_ANSWER  = -1000146,

    QUEST_ESCAPE_FROM_THE_CATACOMBS     = 9212,
    GO_CAGE             = 181152,
    NPC_CAPTAIN_HELIOS  = 16220,
    FACTION_SMOON_E     = 1603,
};







class npc_blood_knight_dawnstar : public CreatureScript
{
public: 
    npc_blood_knight_dawnstar() : CreatureScript("npc_blood_knight_dawnstar") { }
    
    bool OnGossipHello(Player* pPlayer, Creature* pCreature) override
    {
        if (pPlayer->GetQuestStatus(9692) == QUEST_STATUS_INCOMPLETE && !pPlayer->HasItemCount(24226, 1, true))
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_H_BKD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    
        return true;
    }
    
    bool GossipHello_npc_blood_knight_dawnstar(Player* pPlayer, Creature* pCreature)
    {
        if (pPlayer->GetQuestStatus(9692) == QUEST_STATUS_INCOMPLETE && !pPlayer->HasItemCount(24226, 1, true))
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_H_BKD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    
        return true;
    }
    
    bool GossipSelect_npc_blood_knight_dawnstar(Player* pPlayer, Creature* /*pCreature*/, uint32 /*uiSender*/, uint32 uiAction)
    {
        if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
        {
            ItemPosCountVec dest;
            uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 24226, 1, NULL);
            if (msg == EQUIP_ERR_OK)
            {
                pPlayer->StoreNewItem(dest, 24226, 1, true);
                pPlayer->PlayerTalkClass->ClearMenus();
            }
        }
        return true;
    }
    
    bool OnGossipSelect(Player* pPlayer, Creature* /*pCreature*/, uint32 /*uiSender*/, uint32 uiAction) override
    {
        if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
        {
            ItemPosCountVec dest;
            uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 24226, 1, NULL);
            if (msg == EQUIP_ERR_OK)
            {
                pPlayer->StoreNewItem(dest, 24226, 1, true);
                pPlayer->PlayerTalkClass->ClearMenus();
            }
        }
        return true;
    }
    
    
    
};

class npc_budd_nedreck : public CreatureScript
{
public: 
    npc_budd_nedreck() : CreatureScript("npc_budd_nedreck") { }
    
    
    bool OnGossipHello(Player* pPlayer, Creature* pCreature) override
    {
        if (pCreature->IsQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());
    
        if (pPlayer->GetQuestStatus(11166) == QUEST_STATUS_INCOMPLETE)
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HBN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
    
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
        return true;
    }
    
    bool GossipHello_npc_budd_nedreck(Player* pPlayer, Creature* pCreature)
    {
        if (pCreature->IsQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());
    
        if (pPlayer->GetQuestStatus(11166) == QUEST_STATUS_INCOMPLETE)
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HBN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
    
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
        return true;
    }
    
    bool GossipSelect_npc_budd_nedreck(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        if (uiAction == GOSSIP_ACTION_INFO_DEF)
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer, 42540, false);
        }
        return true;
    }
    
    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction) override
    {
        if (uiAction == GOSSIP_ACTION_INFO_DEF)
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer, 42540, false);
        }
        return true;
    }
    
    
    
};

class npc_rathis_tomber : public CreatureScript
{
public: 
    npc_rathis_tomber() : CreatureScript("npc_rathis_tomber") { }
    
    
    bool OnGossipHello(Player* pPlayer, Creature* pCreature) override
    {
        if (pCreature->IsQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());
    
        if (pCreature->IsVendor() && pPlayer->GetQuestRewardStatus(9152))
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
            pPlayer->SEND_GOSSIP_MENU(8432, pCreature->GetGUID());
        }
        else
            pPlayer->SEND_GOSSIP_MENU(8431, pCreature->GetGUID());
    
        return true;
    }

   
    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction) override
    {
        if (uiAction == GOSSIP_ACTION_TRADE)
            pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
        return true;
    }
    
    
    
};

class go_gilded_brazier : public GameObjectScript
{
public: 
    go_gilded_brazier() : GameObjectScript("go_gilded_brazier") { }
    
    
    bool OnGossipHello(Player* player, GameObject* /*_GO*/) override
    {
        if (player->GetQuestStatus(9678) == QUEST_STATUS_INCOMPLETE)
        {
            Creature* Stillblade = player->SummonCreature(17716, 8106.11f, -7542.06f, 151.775f, 3.02598f, TEMPSUMMON_DEAD_DESPAWN, 60000);
            if (Stillblade)
                ((CreatureAI*)Stillblade->AI())->AttackStart(player);
        }
        return true;
    }
    
    
    
};

class npc_ranger_lilatha : public CreatureScript
{
public: 
    npc_ranger_lilatha() : CreatureScript("npc_ranger_lilatha") { }
    struct npc_ranger_lilathaAI : public npc_escortAI
    {
        npc_ranger_lilathaAI(Creature* c) : npc_escortAI(c) {}
    
        void WaypointReached(uint32 i)
        {
            Player* pPlayer = GetPlayerForEscort();
    
            if (!pPlayer)
                return;
    
            switch (i)
            {
            case 0:
                {
                    me->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
                    if (GameObject* Cage = me->FindNearestGameObject(GO_CAGE, 20))
                        Cage->SetGoState(GO_STATE_ACTIVE);
                    DoScriptText(SAY_START, me, pPlayer);
                    break;
                }
            case 5:
                DoScriptText(SAY_PROGRESS1, me, pPlayer);
            case 11:
                DoScriptText(SAY_PROGRESS2, me, pPlayer);
                me->SetOrientation(4.762841f);
                break;
            case 18:
                {
                    DoScriptText(SAY_PROGRESS3, me, pPlayer);
                    Creature* Summ1 = me->SummonCreature(16342, 7627.083984f, -7532.538086f, 152.128616f, 1.082733f, TEMPSUMMON_DEAD_DESPAWN, 0);
                    Creature* Summ2 = me->SummonCreature(16343, 7620.432129f, -7532.550293f, 152.454865f, 0.827478f, TEMPSUMMON_DEAD_DESPAWN, 0);
                    if (Summ1 && Summ2)
                    {
                        Summ1->Attack(me, true);
                        Summ2->Attack(pPlayer, true);
                    }
                    me->AI()->AttackStart(Summ1);
                    break;
                }
            case 19:
                me->RemoveUnitMovementFlag(false);
                break;
            case 25:
                me->SetWalk(true);
                break;
            case 30:
                if (pPlayer && pPlayer->GetTypeId() == TYPEID_PLAYER)
                    CAST_PLR(pPlayer)->GroupEventHappens(QUEST_ESCAPE_FROM_THE_CATACOMBS, me);
                break;
            case 32:
                me->SetOrientation(2.978281f);
                DoScriptText(SAY_END1, me, pPlayer);
                break;
            case 33:
                me->SetOrientation(5.858011f);
                DoScriptText(SAY_END2, me, pPlayer);
                Unit* CaptainHelios = me->FindNearestCreature(NPC_CAPTAIN_HELIOS, 50);
                if (CaptainHelios)
                    DoScriptText(SAY_CAPTAIN_ANSWER, CaptainHelios, pPlayer);
                break;
            }
        }
    
        void Reset()
        {
            if (GameObject* Cage = me->FindNearestGameObject(GO_CAGE, 20))
                Cage->SetGoState(GO_STATE_READY);
        }
    };

    CreatureAI* GetAI_npc_ranger_lilathaAI(Creature* pCreature)
    {
        return  new npc_ranger_lilathaAI(pCreature);
    }

    bool OnQuestAccept(Player* pPlayer, Creature* pCreature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_ESCAPE_FROM_THE_CATACOMBS)
        {
            pCreature->SetFaction(113);
    
            if (npc_escortAI* pEscortAI = CAST_AI(npc_ranger_lilathaAI, pCreature->AI()))
                pEscortAI->Start(true, false, pPlayer->GetGUID());
        }
        return true;
    }
    
    
    
};


void AddSC_ghostlands()
{
    new npc_blood_knight_dawnstar();
    new npc_budd_nedreck();
    new npc_rathis_tomber();
    new go_gilded_brazier();
    new npc_ranger_lilatha();

}

