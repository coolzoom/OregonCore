#include "Player.h"

class maxskills : public PlayerScript
{
public:

	maxskills() : PlayerScript("maxskills") { }
};

void Addmax_skillsScripts()
{
	new maxskills;
}