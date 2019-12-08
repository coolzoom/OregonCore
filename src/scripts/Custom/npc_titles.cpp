/* ScriptData
+SDName: Titles Giver NPC
+SD%Complete: 100
+SDComment: By Evrial
+SDCategory: NPC
+EndScriptData */

#include "ScriptPCH.h"
#include <cstring>
#include "World.h"

bool GossipHello_npc_titles(Player* pPlayer, Creature* pCreature)
{
	pPlayer->ADD_GOSSIP_ITEM( 0, "Gladiator's Title", GOSSIP_SENDER_MAIN, 1000);
	pPlayer->ADD_GOSSIP_ITEM( 0, "Merciless Gladiator's Title", GOSSIP_SENDER_MAIN, 2000);
	pPlayer->ADD_GOSSIP_ITEM( 0, "Vengeful Gladiator's Title", GOSSIP_SENDER_MAIN, 3000);

	pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
	return true;
}

void SendDefaultMenu_npc_titles(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    // Not allowed if in combat.
    if (pPlayer->isInCombat())
    {
      pPlayer->CLOSE_GOSSIP_MENU();
      pCreature->MonsterSay("You are in combat!", LANG_UNIVERSAL, NULL);
      return;
    }

    // Process menu selection
    switch(uiAction)
    { 
        case 1000:
            // Gladiator's Title
			if(pPlayer->GetMoney() >= (sWorld.getConfig(CONFIG_TITLER_G_GOLD) * 10000) && (pPlayer->GetMaxPersonalArenaRatingRequirement() >= sWorld.getConfig(CONFIG_TITLER_G_RATING) 
				&& pPlayer->HasItemCount(sWorld.getConfig(CONFIG_TITLER_G_ITEMID), sWorld.getConfig(CONFIG_TITLER_G_ITEMCOUNT), true) 
				&& pPlayer->GetHonorPoints() >= sWorld.getConfig(CONFIG_TITLER_G_HONOR) 
				&& pPlayer->GetArenaPoints() >= sWorld.getConfig(CONFIG_TITLER_G_AP)))
            {
				uint32 idg;
				idg = 42;
				CharTitlesEntry const* title = sCharTitlesStore.LookupEntry(idg);
                pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TITLER_G_GOLD) * 10000);
				pPlayer->DestroyItemCount(sWorld.getConfig(CONFIG_TITLER_G_ITEMID),sWorld.getConfig(CONFIG_TITLER_G_ITEMCOUNT), true);
				pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TITLER_G_HONOR));
				pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TITLER_G_AP));
				pPlayer->SetTitle(title);
                pCreature->MonsterWhisper("Here are your Gladuator's Title. Relogin please.", pPlayer->GetGUID());
            }
            else
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterWhisper("You can not do it!", pPlayer->GetGUID());
            }
            break;
        case 2000:
            // Merciless Gladiator's Title
            if(pPlayer->GetMoney() >= (sWorld.getConfig(CONFIG_TITLER_MG_GOLD) * 10000) && (pPlayer->GetMaxPersonalArenaRatingRequirement() >= sWorld.getConfig(CONFIG_TITLER_MG_RATING) 
				&& pPlayer->GetItemCount(sWorld.getConfig(CONFIG_TITLER_MG_ITEMID)) >= sWorld.getConfig(CONFIG_TITLER_MG_ITEMCOUNT) 
				&& pPlayer->GetHonorPoints() >= sWorld.getConfig(CONFIG_TITLER_MG_HONOR) 
				&& pPlayer->GetArenaPoints() >= sWorld.getConfig(CONFIG_TITLER_MG_AP)))
            {
				uint32 idmg;
				idmg = 62;
				CharTitlesEntry const* title = sCharTitlesStore.LookupEntry(idmg);
                pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TITLER_MG_GOLD) * 10000);
				pPlayer->DestroyItemCount(sWorld.getConfig(CONFIG_TITLER_MG_ITEMID),sWorld.getConfig(CONFIG_TITLER_G_ITEMCOUNT), true);
				pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TITLER_MG_HONOR));
				pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TITLER_MG_AP));
				pPlayer->SetTitle(title);
                pCreature->MonsterWhisper("Here are your Merciless Gladuator's Title. Relogin please.", pPlayer->GetGUID());
            }
            else
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterWhisper("You can not do it!", pPlayer->GetGUID());
            }
            break;
        case 3000:
            // Vengeful Gladiator's Title
            if(pPlayer->GetMoney() >= (sWorld.getConfig(CONFIG_TITLER_VG_GOLD) * 10000) && (pPlayer->GetMaxPersonalArenaRatingRequirement() >= sWorld.getConfig(CONFIG_TITLER_VG_RATING) 
				&& pPlayer->GetItemCount(sWorld.getConfig(CONFIG_TITLER_VG_ITEMID)) >= sWorld.getConfig(CONFIG_TITLER_VG_ITEMCOUNT) 
				&& pPlayer->GetHonorPoints() >= sWorld.getConfig(CONFIG_TITLER_VG_HONOR) 
				&& pPlayer->GetArenaPoints() >= sWorld.getConfig(CONFIG_TITLER_VG_AP)))
            {
				uint32 idvg;
				idvg = 71;
				CharTitlesEntry const* title = sCharTitlesStore.LookupEntry(idvg);
                pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TITLER_VG_GOLD) * 10000);
				pPlayer->DestroyItemCount(sWorld.getConfig(CONFIG_TITLER_VG_ITEMID),sWorld.getConfig(CONFIG_TITLER_G_ITEMCOUNT), true);
				pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TITLER_VG_HONOR));
				pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TITLER_VG_AP));
				pPlayer->SetTitle(title);
                pCreature->MonsterWhisper("Here are your Vengeful Gladuator's Title. Relogin please.", pPlayer->GetGUID());
            }
            else
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterWhisper("You can not do it!", pPlayer->GetGUID());
            }
            break;
	}
}

bool GossipSelect_npc_titles(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    // Show menu
    if (uiSender == GOSSIP_SENDER_MAIN)
        SendDefaultMenu_npc_titles(pPlayer, pCreature, uiAction);
    return true;
}

void AddSC_npc_titles()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "npc_titles";
    newscript->pGossipHello = &GossipHello_npc_titles;
    newscript->pGossipSelect = &GossipSelect_npc_titles;
    newscript->RegisterSelf();
}
