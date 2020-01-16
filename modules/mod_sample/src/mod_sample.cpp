#include "ScriptMgr.h"
#include "Config/Config.h"
#include "Player.h"
#include "World.h"
#include "Chat.h"

class modsample : public PlayerScript
{
public:
	modsample() : PlayerScript("modsample") { }

	void OnLogin(Player* player, bool firstLogin) override
	{

		std::string mod = sWorld.GetModuleStringConfig("modsample.stringtest");
		uint32 number = sWorld.GetModuleIntConfig("modsample.intTest", 10032);

		if (sWorld.GetModuleBoolConfig("modsample.enableHelloWorld", "1"))
		{
			ChatHandler(player->GetSession()).SendSysMessage("Module Is working!!");
			ChatHandler(player->GetSession()).SendSysMessage(mod.c_str());
			player->AddAura(number, player);
		}
		else
			ChatHandler(player->GetSession()).SendSysMessage("Module Is Not working!!");



	}
};

void Addmod_sampleScripts()
{
	new modsample();
}