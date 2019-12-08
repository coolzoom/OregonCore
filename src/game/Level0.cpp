/*
 * Copyright (C) 2010-2012 OregonCore <http://www.oregoncore.com/>
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2012 MaNGOS <http://getmangos.com/>
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

#include "Common.h"
#include "Database/DatabaseEnv.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "World.h"
#include "Player.h"
#include "Opcodes.h"
#include "Chat.h"
#include "MapManager.h"
#include "ObjectAccessor.h"
#include "Language.h"
#include "AccountMgr.h"
#include "SystemConfig.h"
#include "revision.h"
#include "Util.h"

bool ChatHandler::HandleHelpCommand(const char* args)
{
    char* cmd = strtok((char*)args, " ");
    if (!cmd)
    {
        ShowHelpForCommand(getCommandTable(), "help");
        ShowHelpForCommand(getCommandTable(), "");
    }
    else
    {
        if (!ShowHelpForCommand(getCommandTable(), cmd))
            SendSysMessage(LANG_NO_HELP_CMD);
    }

    return true;
}

bool ChatHandler::HandleCommandsCommand(const char* args)
{
    ShowHelpForCommand(getCommandTable(), "");
    return true;
}

bool ChatHandler::HandleAccountCommand(const char* /*args*/)
{
    uint32 gmlevel = m_session->GetSecurity();
    PSendSysMessage(LANG_ACCOUNT_LEVEL, gmlevel);
    return true;
}

bool ChatHandler::HandleVipCommand(const char* /*args*/)
{
	Player *player = m_session->GetPlayer();
	uint32 player_id = player->GetGUIDLow();
	if (player->isVip())
	{
		PSendSysMessage("Your VIP status is Confirmed in session! All is OK!");
		//PSendSysMessage("Configs:");
	}
	else
	{
		PSendSysMessage("Your VIP status is NOT Confirmed in session! Talk to GM to VIP status");
		//PSendSysMessage("VIP status grands:");
	}
	if (sWorld.getConfig(CONFIG_VIP_PVE_SHOW))
		PSendSysMessage("If you have VIP status, In PVE You Have incrised rates of XP, Reputation gain, Gold loot, More Profession skills, incrised skills gain.");

	if (sWorld.getConfig(CONFIG_VIP_PVP_SHOW))
		PSendSysMessage("If you have VIP status, In PVP You Have incrised rates Honor, Arena Points, BattleGround Marks.");

	return true;
}

bool ChatHandler::HandleReferralAddCommand(const char* args)
{
	uint64 rlguid = m_session->GetPlayer()->GetGUIDLow();
	uint32 rltotaltime = m_session->GetPlayer()->GetTotalPlayedTime();

	QueryResult_AutoPtr rlInfo = CharacterDatabase.PQuery("SELECT `refferer_guid`, `referrer_name` FROM `referrals` WHERE `referral_guid` = '%u'", rlguid);
	if (rlInfo)
	{
		Field *fields = rlInfo->Fetch();
		uint64 rroldguid = fields[0].GetInt64();
		std::string rroldname = fields[1].GetCppString();

		PSendSysMessage("You have already registered referrer! Its nickname is %s", rroldname.c_str());
		return false;
	}

	if (!*args)
        return false;

    char *referrername = strtok((char*)args, " ");
    if (!referrername)
        return false;

    std::string rrname = referrername;

	if (!normalizePlayerName(rrname))
    {
        SendSysMessage(LANG_PLAYER_NOT_FOUND);
        SetSentErrorMessage(true);
        return false;
    }

	uint64 rrguid = objmgr.GetPlayerGUIDByName(rrname.c_str());
    if (!rrguid)
    {
        SendSysMessage(LANG_PLAYER_NOT_FOUND);
        SetSentErrorMessage(true);
        return false;
    }

	if (rlguid == rrguid)
	{
		PSendSysMessage("You can not to bee self Referrer!");
		return false;
	}

	CharacterDatabase.PExecute("INSERT INTO `referrals` VALUES (0, %u, 'Evrial', 0, 0, 0, 0)", rrguid);
	CharacterDatabase.PExecute("UPDATE `referrals` SET `referrer_name` = '%s' WHERE `referral_guid` = 0", rrname.c_str());
	CharacterDatabase.PExecute("UPDATE `referrals` SET `totaltime_start` = %u WHERE `referral_guid` = 0", rltotaltime);
	CharacterDatabase.PExecute("UPDATE `referrals` SET `referral_guid` = %u WHERE `referral_guid` = 0", rlguid);

	PSendSysMessage("You have registered referrer! Its nickname is %s", rrname.c_str());

	if (Player *rrplr = objmgr.GetPlayer(rrguid))
	{
		QueryResult_AutoPtr rlName = CharacterDatabase.PQuery("SELECT `name` FROM `characters` WHERE `guid` = %u", rlguid);
		if (!rlName)
			ChatHandler(rrplr).PSendSysMessage("You are REFERRER of player ID %u now! You will get a PRESENT when its Played Time will increase", rlguid);
		Field *fieldss = rlName->Fetch();
		std::string rlname = fieldss[0].GetString();
		ChatHandler(rrplr).PSendSysMessage("You are REFERRER of player %s now! You will get a PRESENT when its Played Time will increase", rlname.c_str());
	}

	return true;
}

bool ChatHandler::HandleReferralInfoCommand(const char* /*args*/)
{
	uint64 rrguid = m_session->GetPlayer()->GetGUIDLow();

	QueryResult_AutoPtr rrInfo = CharacterDatabase.PQuery("SELECT `referral_guid`, `totaltime_start` FROM `referrals` WHERE `refferer_guid` = %u", rrguid);
	if (!rrInfo)
	{
		PSendSysMessage("You have not Referrals :(");
		return true;
	}
	PSendSysMessage("Your Refferals:");
	do
	{
		Field *fields = rrInfo->Fetch();
		uint64 rlguid = fields[0].GetInt64();
		uint32 rlsttime = fields[1].GetInt32();
		QueryResult_AutoPtr rldata = CharacterDatabase.PQuery("SELECT `name`, `totaltime` FROM `characters` WHERE `guid` = %u", rlguid);
		if (!rldata)
			PSendSysMessage("ID of referal - %u, but player is not exist :(", rlguid);
		else
		{
			Field *fieldss = rldata->Fetch();
			std::string rlname = fieldss[0].GetString();
			uint32 rltime = fieldss[1].GetInt32();
			uint32 reftime = (rltime - rlsttime)/3600;
			PSendSysMessage("Name - %s, Referral time - %u hours",  rlname.c_str(), reftime);
		}
	}
	while (rrInfo->NextRow());

	return true;
}

bool ChatHandler::HandleBfptCommand(const char* /*args*/)
{
	Player *player = m_session->GetPlayer();
	uint64 pguid = player->GetGUIDLow();

	uint32 totaltime = player->GetTotalPlayedTime();
	uint32 ptime = totaltime/3600;
	PSendSysMessage("Your Total Played Time is %u hours.", ptime);

	QueryResult_AutoPtr bonusinfo = CharacterDatabase.PQuery("SELECT `guid`, `first`, `second`, `third` FROM `bfpt` WHERE `guid` = %u", pguid);
	uint32 first = 0;
	uint32 second = 0;
	uint32 third = 0;
	if (bonusinfo)
	{
		Field* fields = bonusinfo->Fetch();
		first = fields[0].GetInt32();
		second = fields[1].GetInt32();
		third = fields[2].GetInt32();
	}

	if (totaltime < sWorld.getConfig(CONFIG_BFPT_FIRST)*3600)
	{
		PSendSysMessage("For Bonus your Played Time is must bigger then %u", sWorld.getConfig(CONFIG_BFPT_FIRST));
	}
	else if (totaltime < sWorld.getConfig(CONFIG_BFPT_SECOND)*3600 && first == 0)
	{
		uint32 gold = sWorld.getConfig(CONFIG_BFPT_FIRST_GOLD)*10000;
		uint32 honor = sWorld.getConfig(CONFIG_BFPT_FIRST_HONOR);
		uint32 ap = sWorld.getConfig(CONFIG_BFPT_FIRST_AP);
		uint32 itemid = sWorld.getConfig(CONFIG_BFPT_FIRST_ITEM_ID);
		uint32 itemcount = sWorld.getConfig(CONFIG_BFPT_FIRST_ITEM_COUNT);

		if (gold > 0)
			player->ModifyMoney(gold);
		if (honor > 0)
			player->ModifyHonorPoints(honor);
		if (ap > 0)
			player->ModifyArenaPoints(ap);
		if (itemid > 0 && itemcount > 0)
		{
			ItemPosCountVec dest;
			if (Item* item = player->StoreNewItem(dest, itemid, true, 0))
				player->SendNewItem(item,itemcount,false,true);
		}
		CharacterDatabase.PExecute("INSERT INTO `bfpt` VALUES (%u, 1, 0, 0)", pguid);
		PSendSysMessage("For Big Bonus your Played Time is must bigger then %u", sWorld.getConfig(CONFIG_BFPT_SECOND));
	}
	else if (totaltime < sWorld.getConfig(CONFIG_BFPT_THIRD)*3600 && second == 0)
	{
		uint32 gold = sWorld.getConfig(CONFIG_BFPT_SECOND_GOLD)*10000;
		uint32 honor = sWorld.getConfig(CONFIG_BFPT_SECOND_HONOR);
		uint32 ap = sWorld.getConfig(CONFIG_BFPT_SECOND_AP);
		uint32 itemid = sWorld.getConfig(CONFIG_BFPT_SECOND_ITEM_ID);
		uint32 itemcount = sWorld.getConfig(CONFIG_BFPT_SECOND_ITEM_COUNT);

		if (gold > 0)
			player->ModifyMoney(gold);
		if (honor > 0)
			player->ModifyHonorPoints(honor);
		if (ap > 0)
			player->ModifyArenaPoints(ap);
		if (itemid > 0 && itemcount > 0)
		{
			ItemPosCountVec dest;
			if (Item* item = player->StoreNewItem(dest, itemid, true, 0))
				player->SendNewItem(item,itemcount,false,true);
		}
		CharacterDatabase.PExecute("UPDATE `bfpt` SET `second` = 1 WHERE `guid` = %u", pguid);
		PSendSysMessage("For Great Bonus your Played Time is must bigger then %u", sWorld.getConfig(CONFIG_BFPT_THIRD));
	}
	else if (third == 0)
	{
		uint32 gold = sWorld.getConfig(CONFIG_BFPT_THIRD_GOLD)*10000;
		uint32 honor = sWorld.getConfig(CONFIG_BFPT_THIRD_HONOR);
		uint32 ap = sWorld.getConfig(CONFIG_BFPT_THIRD_AP);
		uint32 itemid = sWorld.getConfig(CONFIG_BFPT_THIRD_ITEM_ID);
		uint32 itemcount = sWorld.getConfig(CONFIG_BFPT_THIRD_ITEM_COUNT);

		if (gold > 0)
			player->ModifyMoney(gold);
		if (honor > 0)
			player->ModifyHonorPoints(honor);
		if (ap > 0)
			player->ModifyArenaPoints(ap);
		if (itemid > 0 && itemcount > 0)
		{
			ItemPosCountVec dest;
			if (Item* item = player->StoreNewItem(dest, itemid, true, 0))
				player->SendNewItem(item,itemcount,false,true);
		}
		CharacterDatabase.PExecute("UPDATE `bfpt` SET `third` = 1 WHERE `guid` = %u", pguid);
	}
	else
		PSendSysMessage("You allready resive all bonuses for played time :)");

	return true;
}

bool ChatHandler::HandleStartCommand(const char* /*args*/)
{
    Player *chr = m_session->GetPlayer();

    if (chr->isInFlight())
    {
        SendSysMessage(LANG_YOU_IN_FLIGHT);
        SetSentErrorMessage(true);
        return false;
    }

    if (chr->isInCombat())
    {
        SendSysMessage(LANG_YOU_IN_COMBAT);
        SetSentErrorMessage(true);
        return false;
    }

    // cast spell Stuck
    chr->CastSpell(chr,7355,false);
    return true;
}

bool ChatHandler::HandleSpectatorStopCommand(const char* args)
{
	Player *plr = m_session->GetPlayer();

	if (plr->isSpectator())
	{
		plr->TeleportTo(plr->GetBattleGroundEntryPoint());
		plr->SetSpectator(false);
	}
	return true;
}

bool ChatHandler::HandleServerInfoCommand(const char* /*args*/)
{
    uint32 activeClientsNum = sWorld.GetActiveSessionCount();
    uint32 queuedClientsNum = sWorld.GetQueuedSessionCount();
    uint32 maxActiveClientsNum = sWorld.GetMaxActiveSessionCount();
    uint32 maxQueuedClientsNum = sWorld.GetMaxQueuedSessionCount();
    std::string str = secsToTimeString(sWorld.GetUptime());
    uint32 updateTime = sWorld.GetUpdateTime();

    PSendSysMessage(_FULLVERSION);
    //if (m_session)
    //    full = _FULLVERSION(REVISION_DATE,REVISION_TIME,"|cffffffff|Hurl:" REVISION_ID "|h" REVISION_ID "|h|r");
    //else
    //    full = _FULLVERSION(REVISION_DATE,REVISION_TIME,REVISION_ID);

    //SendSysMessage(full);
    //PSendSysMessage(LANG_USING_WORLD_DB,sWorld.GetDBVersion());
    PSendSysMessage(LANG_CONNECTED_USERS, activeClientsNum, maxActiveClientsNum, queuedClientsNum, maxQueuedClientsNum);
    PSendSysMessage(LANG_UPTIME, str.c_str());
    PSendSysMessage("Update time diff: %u.", updateTime);

    return true;
}

bool ChatHandler::HandleDismountCommand(const char* /*args*/)
{
    //If player is not mounted, so go out :)
    if (!m_session->GetPlayer()->IsMounted())
    {
        SendSysMessage(LANG_CHAR_NON_MOUNTED);
        SetSentErrorMessage(true);
        return false;
    }

    if (m_session->GetPlayer()->isInFlight())
    {
        SendSysMessage(LANG_YOU_IN_FLIGHT);
        SetSentErrorMessage(true);
        return false;
    }

    m_session->GetPlayer()->Unmount();
    m_session->GetPlayer()->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
    return true;
}

bool ChatHandler::HandleSaveCommand(const char* /*args*/)
{
    Player *player=m_session->GetPlayer();

    // save GM account without delay and output message (testing, etc)
    if (m_session->GetSecurity())
    {
        player->SaveToDB();
        SendSysMessage(LANG_PLAYER_SAVED);
        return true;
    }

    // save or plan save after 20 sec (logout delay) if current next save time more this value and _not_ output any messages to prevent cheat planning
    uint32 save_interval = sWorld.getConfig(CONFIG_INTERVAL_SAVE);
    if (save_interval == 0 || save_interval > 20*IN_MILLISECONDS && player->GetSaveTimer() <= save_interval - 20*IN_MILLISECONDS)
        player->SaveToDB();

    return true;
}

bool ChatHandler::HandleGMListIngameCommand(const char* /*args*/)
{
    bool first = true;

    ObjectAccessor::Guard guard(*HashMapHolder<Player>::GetLock());
    HashMapHolder<Player>::MapType &m = ObjectAccessor::Instance().GetPlayers();
    for (HashMapHolder<Player>::MapType::iterator itr = m.begin(); itr != m.end(); ++itr)
    {
        if (itr->second->GetSession()->GetSecurity() &&
            (itr->second->isGameMaster() || sWorld.getConfig(CONFIG_GM_IN_GM_LIST)) &&
            (!m_session || itr->second->IsVisibleGloballyFor(m_session->GetPlayer())))
        {
            if (first)
            {
                SendSysMessage(LANG_GMS_ON_SRV);
                first = false;
            }

            SendSysMessage(itr->second->GetName());
        }
    }

    if (first)
        SendSysMessage(LANG_GMS_NOT_LOGGED);

    return true;
}

bool ChatHandler::HandleAccountPasswordCommand(const char* args)
{
    if (!*args)
        return false;

    char *old_pass = strtok ((char*)args, " ");
    char *new_pass = strtok (NULL, " ");
    char *new_pass_c  = strtok (NULL, " ");

    if (!old_pass || !new_pass || !new_pass_c)
        return false;

    std::string password_old = old_pass;
    std::string password_new = new_pass;
    std::string password_new_c = new_pass_c;

    if (strcmp(new_pass, new_pass_c) != 0)
    {
        SendSysMessage (LANG_NEW_PASSWORDS_NOT_MATCH);
        SetSentErrorMessage (true);
        return false;
    }

    if (!sAccountMgr->CheckPassword (m_session->GetAccountId(), password_old))
    {
        SendSysMessage (LANG_COMMAND_WRONGOLDPASSWORD);
        SetSentErrorMessage (true);
        return false;
    }

    AccountOpResult result = sAccountMgr->ChangePassword(m_session->GetAccountId(), password_new);

    switch(result)
    {
        case AOR_OK:
            SendSysMessage(LANG_COMMAND_PASSWORD);
            break;
        case AOR_PASS_TOO_LONG:
            SendSysMessage(LANG_PASSWORD_TOO_LONG);
            SetSentErrorMessage(true);
            return false;
        case AOR_NAME_NOT_EXIST:                            // not possible case, don't want get account name for output
        default:
            SendSysMessage(LANG_COMMAND_NOTCHANGEPASSWORD);
            SetSentErrorMessage(true);
            return false;
    }

    return true;
}

bool ChatHandler::HandleAccountLockCommand(const char* args)
{
    if (!*args)
    {
        SendSysMessage(LANG_USE_BOL);
        return true;
    }

    std::string argstr = (char*)args;
    if (argstr == "on")
    {
        LoginDatabase.PExecute("UPDATE account SET locked = '1' WHERE id = '%d'",m_session->GetAccountId());
        PSendSysMessage(LANG_COMMAND_ACCLOCKLOCKED);
        return true;
    }

    if (argstr == "off")
    {
        LoginDatabase.PExecute("UPDATE account SET locked = '0' WHERE id = '%d'",m_session->GetAccountId());
        PSendSysMessage(LANG_COMMAND_ACCLOCKUNLOCKED);
        return true;
    }

    SendSysMessage(LANG_USE_BOL);
    return true;
}

// Display the 'Message of the day' for the realm
bool ChatHandler::HandleServerMotdCommand(const char* /*args*/)
{
    PSendSysMessage(LANG_MOTD_CURRENT, sWorld.GetMotd());
    return true;
}

