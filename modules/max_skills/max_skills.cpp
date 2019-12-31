#include "Player.h"

class maxskills : public PlayerScript
{
public:
	maxskills() : PlayerScript("maxskills") { }

	void OnLogin(Player* player, bool firstLogin) override
	{
		ChatHandler(player).PSendSysMessage("Module Is working!");
	}
};

void Addmax_skillsScripts()
{
	new maxskills();
}