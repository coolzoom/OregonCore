/* ScriptData
SDName: NPC ITEM EXCHANGER
SD%Complete: 100
SDComment: By Evrial
SDCategory: NPC
EndScriptData */

#include "ScriptPCH.h"
#include <cstring>

bool GossipHello_npc_item_exchanger(Player* pPlayer, Creature* pCreature)
{
	for (uint32 i = 1; i <= 12; i++)
	{
		QueryResult_AutoPtr type = WorldDatabase.PQuery("SELECT `text1`, `action` FROM `npc_item_exchanger` WHERE `type` = %u AND `active` = 1", i);
		if (type)
		{
			Field *fields = type->Fetch();
			pPlayer->ADD_GOSSIP_ITEM( 9, fields[0].GetString(), GOSSIP_SENDER_MAIN, fields[1].GetInt32());
		}
	}

	pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
	return true;
}

void SendDefaultMenu_npc_item_exchanger(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    // Not allowed if in combat.
    if (pPlayer->isInCombat())
    {
      pPlayer->CLOSE_GOSSIP_MENU();
      pCreature->MonsterSay("You are in combat!", LANG_UNIVERSAL, NULL);
      return;
    }

	switch(uiAction)
    {
	case 1001:
		{
		QueryResult_AutoPtr type1 = WorldDatabase.PQuery("SELECT `item1id`, `item1count`, `item2id`, `item2count`, `text2` FROM `npc_item_exchanger` WHERE `type` = 1");
		Field *fields1 = type1->Fetch();
		if (pPlayer->HasItemCount(fields1[0].GetUInt32(), fields1[1].GetUInt32()))
		{
			pPlayer->DestroyItemCount(fields1[0].GetUInt32(), fields1[1].GetUInt32(), true);
			pPlayer->StoreNewItemInBestSlots(fields1[2].GetUInt32(), fields1[3].GetUInt32());
			pCreature->MonsterWhisper(fields1[4].GetString(), pPlayer->GetGUID());
		}
		else
			pCreature->MonsterWhisper("You have not enough Items", pPlayer->GetGUID());
		}
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case 1002:
		{
		QueryResult_AutoPtr type1 = WorldDatabase.PQuery("SELECT `item1id`, `item1count`, `item2id`, `item2count`, `text2` FROM `npc_item_exchanger` WHERE `type` = 2");
		Field *fields1 = type1->Fetch();
		if (pPlayer->HasItemCount(fields1[0].GetUInt32(), fields1[1].GetUInt32()))
		{
			pPlayer->DestroyItemCount(fields1[0].GetUInt32(), fields1[1].GetUInt32(), true);
			pPlayer->StoreNewItemInBestSlots(fields1[2].GetUInt32(), fields1[3].GetUInt32());
			pCreature->MonsterWhisper(fields1[4].GetString(), pPlayer->GetGUID());
		}
		else
			pCreature->MonsterWhisper("You have not enough Items", pPlayer->GetGUID());
		}
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case 1003:
		{
		QueryResult_AutoPtr type1 = WorldDatabase.PQuery("SELECT `item1id`, `item1count`, `item2id`, `item2count`, `text2` FROM `npc_item_exchanger` WHERE `type` = 3");
		Field *fields1 = type1->Fetch();
		if (pPlayer->HasItemCount(fields1[0].GetUInt32(), fields1[1].GetUInt32()))
		{
			pPlayer->DestroyItemCount(fields1[0].GetUInt32(), fields1[1].GetUInt32(), true);
			pPlayer->StoreNewItemInBestSlots(fields1[2].GetUInt32(), fields1[3].GetUInt32());
			pCreature->MonsterWhisper(fields1[4].GetString(), pPlayer->GetGUID());
		}
		else
			pCreature->MonsterWhisper("You have not enough Items", pPlayer->GetGUID());
		}
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case 1004:
		{
		QueryResult_AutoPtr type1 = WorldDatabase.PQuery("SELECT `item1id`, `item1count`, `item2id`, `item2count`, `text2` FROM `npc_item_exchanger` WHERE `type` = 4");
		Field *fields1 = type1->Fetch();
		if (pPlayer->HasItemCount(fields1[0].GetUInt32(), fields1[1].GetUInt32()))
		{
			pPlayer->DestroyItemCount(fields1[0].GetUInt32(), fields1[1].GetUInt32(), true);
			pPlayer->StoreNewItemInBestSlots(fields1[2].GetUInt32(), fields1[3].GetUInt32());
			pCreature->MonsterWhisper(fields1[4].GetString(), pPlayer->GetGUID());
		}
		else
			pCreature->MonsterWhisper("You have not enough Items", pPlayer->GetGUID());
		}
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case 1005:
		{
		QueryResult_AutoPtr type1 = WorldDatabase.PQuery("SELECT `item1id`, `item1count`, `item2id`, `item2count`, `text2` FROM `npc_item_exchanger` WHERE `type` = 5");
		Field *fields1 = type1->Fetch();
		if (pPlayer->HasItemCount(fields1[0].GetUInt32(), fields1[1].GetUInt32()))
		{
			pPlayer->DestroyItemCount(fields1[0].GetUInt32(), fields1[1].GetUInt32(), true);
			pPlayer->StoreNewItemInBestSlots(fields1[2].GetUInt32(), fields1[3].GetUInt32());
			pCreature->MonsterWhisper(fields1[4].GetString(), pPlayer->GetGUID());
		}
		else
			pCreature->MonsterWhisper("You have not enough Items", pPlayer->GetGUID());
		}
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case 1006:
		{
		QueryResult_AutoPtr type1 = WorldDatabase.PQuery("SELECT `item1id`, `item1count`, `item2id`, `item2count`, `text2` FROM `npc_item_exchanger` WHERE `type` = 6");
		Field *fields1 = type1->Fetch();
		if (pPlayer->HasItemCount(fields1[0].GetUInt32(), fields1[1].GetUInt32()))
		{
			pPlayer->DestroyItemCount(fields1[0].GetUInt32(), fields1[1].GetUInt32(), true);
			pPlayer->StoreNewItemInBestSlots(fields1[2].GetUInt32(), fields1[3].GetUInt32());
			pCreature->MonsterWhisper(fields1[4].GetString(), pPlayer->GetGUID());
		}
		else
			pCreature->MonsterWhisper("You have not enough Items", pPlayer->GetGUID());
		}
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case 1007:
		{
		QueryResult_AutoPtr type1 = WorldDatabase.PQuery("SELECT `item1id`, `item1count`, `item2id`, `item2count`, `text2` FROM `npc_item_exchanger` WHERE `type` = 7");
		Field *fields1 = type1->Fetch();
		if (pPlayer->HasItemCount(fields1[0].GetUInt32(), fields1[1].GetUInt32()))
		{
			pPlayer->DestroyItemCount(fields1[0].GetUInt32(), fields1[1].GetUInt32(), true);
			pPlayer->StoreNewItemInBestSlots(fields1[2].GetUInt32(), fields1[3].GetUInt32());
			pCreature->MonsterWhisper(fields1[4].GetString(), pPlayer->GetGUID());
		}
		else
			pCreature->MonsterWhisper("You have not enough Items", pPlayer->GetGUID());
		}
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case 1008:
		{
		QueryResult_AutoPtr type1 = WorldDatabase.PQuery("SELECT `item1id`, `item1count`, `item2id`, `item2count`, `text2` FROM `npc_item_exchanger` WHERE `type` = 8");
		Field *fields1 = type1->Fetch();
		if (pPlayer->HasItemCount(fields1[0].GetUInt32(), fields1[1].GetUInt32()))
		{
			pPlayer->DestroyItemCount(fields1[0].GetUInt32(), fields1[1].GetUInt32(), true);
			pPlayer->StoreNewItemInBestSlots(fields1[2].GetUInt32(), fields1[3].GetUInt32());
			pCreature->MonsterWhisper(fields1[4].GetString(), pPlayer->GetGUID());
		}
		else
			pCreature->MonsterWhisper("You have not enough Items", pPlayer->GetGUID());
		}
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case 1009:
		{
		QueryResult_AutoPtr type1 = WorldDatabase.PQuery("SELECT `item1id`, `item1count`, `item2id`, `item2count`, `text2` FROM `npc_item_exchanger` WHERE `type` = 9");
		Field *fields1 = type1->Fetch();
		if (pPlayer->HasItemCount(fields1[0].GetUInt32(), fields1[1].GetUInt32()))
		{
			pPlayer->DestroyItemCount(fields1[0].GetUInt32(), fields1[1].GetUInt32(), true);
			pPlayer->StoreNewItemInBestSlots(fields1[2].GetUInt32(), fields1[3].GetUInt32());
			pCreature->MonsterWhisper(fields1[4].GetString(), pPlayer->GetGUID());
		}
		else
			pCreature->MonsterWhisper("You have not enough Items", pPlayer->GetGUID());
		}
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case 1010:
		{
		QueryResult_AutoPtr type1 = WorldDatabase.PQuery("SELECT `item1id`, `item1count`, `item2id`, `item2count`, `text2` FROM `npc_item_exchanger` WHERE `type` = 10");
		Field *fields1 = type1->Fetch();
		if (pPlayer->HasItemCount(fields1[0].GetUInt32(), fields1[1].GetUInt32()))
		{
			pPlayer->DestroyItemCount(fields1[0].GetUInt32(), fields1[1].GetUInt32(), true);
			pPlayer->StoreNewItemInBestSlots(fields1[2].GetUInt32(), fields1[3].GetUInt32());
			pCreature->MonsterWhisper(fields1[4].GetString(), pPlayer->GetGUID());
		}
		else
			pCreature->MonsterWhisper("You have not enough Items", pPlayer->GetGUID());
		}
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	default:
		break;
	}
}

bool GossipSelect_npc_item_exchanger(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    // Show menu
    if (uiSender == GOSSIP_SENDER_MAIN)
        SendDefaultMenu_npc_item_exchanger(pPlayer, pCreature, uiAction);
    return true;
}

void AddSC_npc_item_exchanger()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "npc_item_exchanger";
    newscript->pGossipHello = &GossipHello_npc_item_exchanger;
    newscript->pGossipSelect = &GossipSelect_npc_item_exchanger;
    newscript->RegisterSelf();
}
