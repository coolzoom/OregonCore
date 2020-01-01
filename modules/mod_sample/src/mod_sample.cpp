#include "ScriptMgr.h"
#include "Config/Config.h"
#include "Player.h"
#include "Chat.h"

class modsample : public PlayerScript
{
public:
	modsample() : PlayerScript("modsample") { }

	void OnLogin(Player* player, bool firstLogin) override
	{
		if (sConfig.GetBoolDefault("modsample.enableHelloWorld", false)) {
            ChatHandler(player->GetSession()).SendSysMessage("Module Is working!!");
        }
	}
};

void Addmod_sampleScripts()
{
	new modsample();
}