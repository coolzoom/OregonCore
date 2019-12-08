#include "ScriptPCH.h"
#include "World.h"

bool GossipHello_npc_transmogrification(Player *pPlayer, Creature *pCreature)
{
	// Пункты меню
	pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual T1", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
	pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual T2", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
	pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual T3", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 30);
	pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual T4", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 40);
	pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual T5", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 50);
	pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual T6", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 60);
	pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual A1", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 70);
	pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual A2", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 80);
	pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual A3", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 90);
	pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual A4", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 100);
	pPlayer->ADD_GOSSIP_ITEM(0, "Delete Transmogrifications", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 110);

	// Показывать меню
	pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
	return true;
}
void UpdateGear(Player *pPlayer )
{
	// Отправляем обновление полей игрока
	pPlayer->SendUpdateToPlayer(pPlayer);

	// Релоадим вид игрока
	WorldPacket data(SMSG_FORCE_DISPLAY_UPDATE, 8);
	data << pPlayer->GetGUID();
	pPlayer->SendMessageToSet(&data,true);

	// Визуальный эффект (как Ваниш)
	pPlayer->CastSpell(pPlayer, 24222, true);
}
bool GossipSelect_npc_transmogrification(Player *pPlayer, Creature *pCreature, uint32 sender, uint32 action )
{
	// Не разрешать в комбате
    if (pPlayer->isInCombat())
    {
		pPlayer->CLOSE_GOSSIP_MENU();
		pCreature->MonsterWhisper("You are in combat!", pPlayer->GetGUID());
		return false;
    }

	// Проверка наличия голда
	if (pPlayer->GetMoney() < sWorld.getConfig(CONFIG_TRANS_GOLD))
	{
		pPlayer->CLOSE_GOSSIP_MENU();
		pCreature->MonsterWhisper("You have not enough gold!", pPlayer->GetGUID());
		return false;
	}

	// Проверка наличия хонора
	if (pPlayer->GetHonorPoints() < sWorld.getConfig(CONFIG_TRANS_HONOR))
	{
		pPlayer->CLOSE_GOSSIP_MENU();
		pCreature->MonsterWhisper("You have not enough honor!", pPlayer->GetGUID());
		return false;
	}

	// Проверка наличия Апа
	if (pPlayer->GetArenaPoints() < sWorld.getConfig(CONFIG_TRANS_AP))
	{
		pPlayer->CLOSE_GOSSIP_MENU();
		pCreature->MonsterWhisper("You have not enough arena points!", pPlayer->GetGUID());
		return false;
	}

	// Проверка наличия Рейтинга
	if (pPlayer->GetMaxPersonalArenaRatingRequirement() < sWorld.getConfig(CONFIG_TRANS_RATING))
	{
		pPlayer->CLOSE_GOSSIP_MENU();
		pCreature->MonsterWhisper("You have not enough arena rating!", pPlayer->GetGUID());
		return false;
	}

	// Проверка наличия Итемов
	if (pPlayer->HasItemCount(sWorld.getConfig(CONFIG_TRANS_ITEM), sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true))
	{
		pPlayer->CLOSE_GOSSIP_MENU();
		pCreature->MonsterWhisper("You have not enough items!", pPlayer->GetGUID());
		return false;
	}

	// Проверяем наличие одетого Эквипа
	if (!pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_HEAD) || 
		!pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_SHOULDERS) || 
		!pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_CHEST) || 
		!pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_WRISTS) || 
		!pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_HANDS) || 
		!pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_WAIST) || 
		!pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_LEGS) || 
		!pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_FEET))
	{
		pPlayer->CLOSE_GOSSIP_MENU();
		pCreature->MonsterWhisper("You does not have full equipment!", pPlayer->GetGUID());
		return false;
	}

	// Типы итемов
		// Щлем 346
		// Плечи 378
		// Тело 410
		// Брас 474
		// Перчи 490
		// Пояс 426
		// Штаны 442
		// Тапок 458

	//Иды классов:
		// Дру 11
		// Маг 8
		// Прист 5
		// Шам 7
		// Вар 1
		// Хант 3
		// Пал 2
		// Рог 4
		// Лок 9

	// Присваиваем переменные -> Изменяемые итемы
	Item *oldItem1 = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_HEAD);
	Item *oldItem2 = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_SHOULDERS);
	Item *oldItem3 = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_CHEST);
	Item *oldItem4 = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_WRISTS);
	Item *oldItem5 = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_HANDS);
	Item *oldItem6 = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_WAIST);
	Item *oldItem7 = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_LEGS);
	Item *oldItem8 = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0 ,EQUIPMENT_SLOT_FEET);

	switch (action)
	{
		// Процесс Трансмогрификации
		case GOSSIP_ACTION_INFO_DEF + 10: // T1
		{
			// Подменю
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warrior", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11); // Вар
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Paladin", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12); // Пал
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Hunter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13); // Хант
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Rogue", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14); // Рог
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Priest", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15); // Прист
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Shaman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 16); // Шам
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Mage", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17); // Маг
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warlock", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18); // Лок
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Druid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 19); // Дру

			// Показывать меню
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 20: // T2
		{
			// Подменю
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warrior", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21); // Вар
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Paladin", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 22); // Пал
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Hunter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 23); // Хант
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Rogue", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 24); // Рог
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Priest", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 25); // Прист
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Shaman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 26); // Шам
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Mage", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 27); // Маг
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warlock", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 28); // Лок
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Druid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 29); // Дру

			// Показывать меню
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 30: // T3
		{
			// Подменю
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warrior", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31); // Вар
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Paladin", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 32); // Пал
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Hunter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 33); // Хант
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Rogue", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 34); // Рог
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Priest", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 35); // Прист
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Shaman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 36); // Шам
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Mage", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 37); // Маг
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warlock", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 38); // Лок
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Druid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 39); // Дру

			// Показывать меню
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 40: // Т4
		{
			// Подменю
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warrior", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 41); // Вар
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Paladin", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 42); // Пал
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Hunter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 43); // Хант
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Rogue", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 44); // Рог
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Priest", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 45); // Прист
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Shaman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 46); // Шам
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Mage", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 47); // Маг
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warlock", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 48); // Лок
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Druid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 49); // Дру

			// Показывать меню
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 50: // Т5
		{
			// Подменю
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warrior", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 51); // Вар
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Paladin", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 52); // Пал
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Hunter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 53); // Хант
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Rogue", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 54); // Рог
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Priest", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 55); // Прист
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Shaman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 56); // Шам
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Mage", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 57); // Маг
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warlock", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 58); // Лок
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Druid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 59); // Дру

			// Показывать меню
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 60: // T6
		{
			// Подменю
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warrior", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 61); // Вар
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Paladin", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 62); // Пал
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Hunter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 63); // Хант
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Rogue", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 64); // Рог
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Priest", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 65); // Прист
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Shaman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 66); // Шам
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Mage", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 67); // Маг
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warlock", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 68); // Лок
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Druid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 69); // Дру

			// Показывать меню
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 70: // A1
		{
			// Подменю
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warrior", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 71); // Вар
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Paladin", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 72); // Пал
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Hunter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 73); // Хант
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Rogue", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 74); // Рог
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Priest", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 75); // Прист
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Shaman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 76); // Шам
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Mage", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 77); // Маг
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warlock", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 78); // Лок
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Druid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 79); // Дру

			// Показывать меню
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 80: // А2
		{
			// Подменю
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warrior", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 81); // Вар
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Paladin", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 82); // Пал
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Hunter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 83); // Хант
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Rogue", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 84); // Рог
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Priest", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 85); // Прист
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Shaman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 86); // Шам
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Mage", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 87); // Маг
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warlock", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 88); // Лок
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Druid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 89); // Дру

			// Показывать меню
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 90: // А3
		{
			// Подменю
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warrior", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 91); // Вар
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Paladin", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 92); // Пал
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Hunter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 93); // Хант
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Rogue", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 94); // Рог
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Priest", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 95); // Прист
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Shaman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 96); // Шам
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Mage", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 97); // Маг
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warlock", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 98); // Лок
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Druid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 99); // Дру

			// Показывать меню
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 100: // А4
		{
			// Подменю
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warrior", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 101); // Вар
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Paladin", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 102); // Пал
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Hunter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 103); // Хант
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Rogue", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 104); // Рог
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Priest", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 105); // Прист
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Shaman", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 106); // Шам
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Mage", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 107); // Маг
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Warlock", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 108); // Лок
			pPlayer->ADD_GOSSIP_ITEM(0, "Make Visual Druid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 109); // Дру

			// Показывать меню
			pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 11: // Вар Т1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16866); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16868); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16865); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16861); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16863); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16864); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16867); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16862); // Тапок

			oldItem1->SetFakeEntry(16866);
			oldItem2->SetFakeEntry(16868);
			oldItem3->SetFakeEntry(16865);
			oldItem4->SetFakeEntry(16861);
			oldItem5->SetFakeEntry(16863);
			oldItem6->SetFakeEntry(16864);
			oldItem7->SetFakeEntry(16867);
			oldItem8->SetFakeEntry(16862);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 12: // Пал Т1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16854); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16856); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16853); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16857); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16860); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16858); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16855); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16859); // Тапок

			oldItem1->SetFakeEntry(16854);
			oldItem2->SetFakeEntry(16856);
			oldItem3->SetFakeEntry(16853);
			oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(16860);
			oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(16855);
			oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 13: // Хант Т1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16846); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16848); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16845); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16850); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16852); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16851); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16847); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16849); // Тапок

			oldItem1->SetFakeEntry(16846);
			oldItem2->SetFakeEntry(16848);
			oldItem3->SetFakeEntry(16845);
			oldItem4->SetFakeEntry(16850);
			oldItem5->SetFakeEntry(16852);
			oldItem6->SetFakeEntry(16851);
			oldItem7->SetFakeEntry(16847);
			oldItem8->SetFakeEntry(16849);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 14: // Рог Т1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16821); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16823); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16820); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16825); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16826); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16827); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16822); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16824); // Тапок

			oldItem1->SetFakeEntry(16821);
			oldItem2->SetFakeEntry(16823);
			oldItem3->SetFakeEntry(16820);
			oldItem4->SetFakeEntry(16825);
			oldItem5->SetFakeEntry(16826);
			oldItem6->SetFakeEntry(16827);
			oldItem7->SetFakeEntry(16822);
			oldItem8->SetFakeEntry(16824);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 15: // Прист Т1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16813); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16816); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16815); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16819); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16812); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16817); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16814); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16811); // Тапок

			oldItem1->SetFakeEntry(16813);
			oldItem2->SetFakeEntry(16816);
			oldItem3->SetFakeEntry(16815);
			oldItem4->SetFakeEntry(16819);
			oldItem5->SetFakeEntry(16812);
			oldItem6->SetFakeEntry(16817);
			oldItem7->SetFakeEntry(16814);
			oldItem8->SetFakeEntry(16811);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 16: // Шам Т1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16842); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16844); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16841); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16840); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16839); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16838); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16843); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16837); // Тапок

			oldItem1->SetFakeEntry(16842);
			oldItem2->SetFakeEntry(16844);
			oldItem3->SetFakeEntry(16841);
			oldItem4->SetFakeEntry(16840);
			oldItem5->SetFakeEntry(16839);
			oldItem6->SetFakeEntry(16838);
			oldItem7->SetFakeEntry(16843);
			oldItem8->SetFakeEntry(16837);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 17: // Маг Т1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16795); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16797); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16798); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16799); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16801); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16802); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16796); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16800); // Тапок

			oldItem1->SetFakeEntry(16795);
			oldItem2->SetFakeEntry(16797);
			oldItem3->SetFakeEntry(16798);
			oldItem4->SetFakeEntry(16799);
			oldItem5->SetFakeEntry(16801);
			oldItem6->SetFakeEntry(16802);
			oldItem7->SetFakeEntry(16796);
			oldItem8->SetFakeEntry(16800);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 18: // Лок Т1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16808); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16807); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16809); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16804); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16805); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16806); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16810); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16803); // Тапок

			oldItem1->SetFakeEntry(16808);
			oldItem2->SetFakeEntry(16807);
			oldItem3->SetFakeEntry(16809);
			oldItem4->SetFakeEntry(16804);
			oldItem5->SetFakeEntry(16805);
			oldItem6->SetFakeEntry(16806);
			oldItem7->SetFakeEntry(16810);
			oldItem8->SetFakeEntry(16803);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 19: // Дру Т1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16834); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16836); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16833); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16830); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16831); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16828); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16835); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16829); // Тапок

			oldItem1->SetFakeEntry(16834);
			oldItem2->SetFakeEntry(16836);
			oldItem3->SetFakeEntry(16833);
			oldItem4->SetFakeEntry(16830);
			oldItem5->SetFakeEntry(16831);
			oldItem6->SetFakeEntry(16828);
			oldItem7->SetFakeEntry(16835);
			oldItem8->SetFakeEntry(16829);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 21: // Вар Т2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16963); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16961); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16966); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16959); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16964); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16960); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16962); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16965); // Тапок

			oldItem1->SetFakeEntry(16963);
			oldItem2->SetFakeEntry(16961);
			oldItem3->SetFakeEntry(16966);
			oldItem4->SetFakeEntry(16959);
			oldItem5->SetFakeEntry(16964);
			oldItem6->SetFakeEntry(16960);
			oldItem7->SetFakeEntry(16962);
			oldItem8->SetFakeEntry(16965);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 22: // Пал Т2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16955); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16953); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16958); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16951); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16956); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16952); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16954); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16957); // Тапок

			oldItem1->SetFakeEntry(16955);
			oldItem2->SetFakeEntry(16953);
			oldItem3->SetFakeEntry(16958);
			oldItem4->SetFakeEntry(16951);
			oldItem5->SetFakeEntry(16956);
			oldItem6->SetFakeEntry(16952);
			oldItem7->SetFakeEntry(16954);
			oldItem8->SetFakeEntry(16957);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 23: // Хант Т2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16939); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16937); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16942); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16935); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16940); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16936); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16938); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16941); // Тапок

			oldItem1->SetFakeEntry(16939);
			oldItem2->SetFakeEntry(16937);
			oldItem3->SetFakeEntry(16942);
			oldItem4->SetFakeEntry(16935);
			oldItem5->SetFakeEntry(16940);
			oldItem6->SetFakeEntry(16936);
			oldItem7->SetFakeEntry(16938);
			oldItem8->SetFakeEntry(16941);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 24: // Рог Т2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16908); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16832); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16905); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16911); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16907); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16910); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16909); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16906); // Тапок

			oldItem1->SetFakeEntry(16908);
			oldItem2->SetFakeEntry(16832);
			oldItem3->SetFakeEntry(16905);
			oldItem4->SetFakeEntry(16911);
			oldItem5->SetFakeEntry(16907);
			oldItem6->SetFakeEntry(16910);
			oldItem7->SetFakeEntry(16909);
			oldItem8->SetFakeEntry(16906);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 25: // Прист Т2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16921); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16924); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16923); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16926); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16920); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16925); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16922); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16919); // Тапок

			oldItem1->SetFakeEntry(16921);
			oldItem2->SetFakeEntry(16924);
			oldItem3->SetFakeEntry(16923);
			oldItem4->SetFakeEntry(16926);
			oldItem5->SetFakeEntry(16920);
			oldItem6->SetFakeEntry(16925);
			oldItem7->SetFakeEntry(16922);
			oldItem8->SetFakeEntry(16919);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 26: // Шам Т2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16947); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16945); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16950); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16943); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16948); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16944); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16946); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16949); // Тапок

			oldItem1->SetFakeEntry(16947);
			oldItem2->SetFakeEntry(16945);
			oldItem3->SetFakeEntry(16950);
			oldItem4->SetFakeEntry(16943);
			oldItem5->SetFakeEntry(16948);
			oldItem6->SetFakeEntry(16944);
			oldItem7->SetFakeEntry(16946);
			oldItem8->SetFakeEntry(16949);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 27: // Маг Т2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16914); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16917); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16916); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16918); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16913); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16818); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16915); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16912); // Тапок

			oldItem1->SetFakeEntry(16914);
			oldItem2->SetFakeEntry(16917);
			oldItem3->SetFakeEntry(16916);
			oldItem4->SetFakeEntry(16918);
			oldItem5->SetFakeEntry(16913);
			oldItem6->SetFakeEntry(16818);
			oldItem7->SetFakeEntry(16915);
			oldItem8->SetFakeEntry(16912);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 28: // Лок Т2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16929); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16932); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16931); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16934); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16928); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16933); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16930); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16927); // Тапок

			oldItem1->SetFakeEntry(16929);
			oldItem2->SetFakeEntry(16932);
			oldItem3->SetFakeEntry(16931);
			oldItem4->SetFakeEntry(16934);
			oldItem5->SetFakeEntry(16928);
			oldItem6->SetFakeEntry(16933);
			oldItem7->SetFakeEntry(16930);
			oldItem8->SetFakeEntry(16927);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 29: // Дру Т2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16900); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 16902); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16897); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 16904); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16899); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16903); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16901); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16898); // Тапок

			oldItem1->SetFakeEntry(16900);
			oldItem2->SetFakeEntry(16902);
			oldItem3->SetFakeEntry(16897);
			oldItem4->SetFakeEntry(16904);
			oldItem5->SetFakeEntry(16899);
			oldItem6->SetFakeEntry(16903);
			oldItem7->SetFakeEntry(16901);
			oldItem8->SetFakeEntry(16898);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 31: // Вар Т3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 22418); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 22419); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 22416); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 22421); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 22417); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(22418);
			oldItem2->SetFakeEntry(22419);
			oldItem3->SetFakeEntry(22416);
			oldItem4->SetFakeEntry(22423);
			oldItem5->SetFakeEntry(22421);
			oldItem6->SetFakeEntry(22422);
			oldItem7->SetFakeEntry(22417);
			oldItem8->SetFakeEntry(22420);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 32: // Пал Т3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 22428); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 22429); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 22425); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22424); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 22426); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22431); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 22427); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22430); // Тапок

			oldItem1->SetFakeEntry(22428);
			oldItem2->SetFakeEntry(22429);
			oldItem3->SetFakeEntry(22425);
			oldItem4->SetFakeEntry(22424);
			oldItem5->SetFakeEntry(22426);
			oldItem6->SetFakeEntry(22431);
			oldItem7->SetFakeEntry(22427);
			oldItem8->SetFakeEntry(22430);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 33: // Хант Т3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 22438); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 22439); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 22436); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22443); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 22441); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22442); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 22437); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22440); // Тапок

			oldItem1->SetFakeEntry(22438);
			oldItem2->SetFakeEntry(22439);
			oldItem3->SetFakeEntry(22436);
			oldItem4->SetFakeEntry(22443);
			oldItem5->SetFakeEntry(22441);
			oldItem6->SetFakeEntry(22442);
			oldItem7->SetFakeEntry(22437);
			oldItem8->SetFakeEntry(22440);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 34: // Рог Т3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 22478); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 22479); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 22476); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22483); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 22481); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22482); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 22477); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22480); // Тапок

			oldItem1->SetFakeEntry(22478);
			oldItem2->SetFakeEntry(22479);
			oldItem3->SetFakeEntry(22476);
			oldItem4->SetFakeEntry(22483);
			oldItem5->SetFakeEntry(22481);
			oldItem6->SetFakeEntry(22482);
			oldItem7->SetFakeEntry(22477);
			oldItem8->SetFakeEntry(22480);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 35: // Прист Т3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 22514); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 22515); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 22512); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22517); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 22519); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22518); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 22513); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22516); // Тапок

			oldItem1->SetFakeEntry(22514);
			oldItem2->SetFakeEntry(22515);
			oldItem3->SetFakeEntry(22512);
			oldItem4->SetFakeEntry(22517);
			oldItem5->SetFakeEntry(22519);
			oldItem6->SetFakeEntry(22518);
			oldItem7->SetFakeEntry(22513);
			oldItem8->SetFakeEntry(22516);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 36: // Шам Т3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 22466); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 22467); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 22464); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22471); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 22469); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22470); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 22465); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22468); // Тапок

			oldItem1->SetFakeEntry(22466);
			oldItem2->SetFakeEntry(22467);
			oldItem3->SetFakeEntry(22464);
			oldItem4->SetFakeEntry(22471);
			oldItem5->SetFakeEntry(22469);
			oldItem6->SetFakeEntry(22470);
			oldItem7->SetFakeEntry(22465);
			oldItem8->SetFakeEntry(22468);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 37: // Маг Т3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 22498); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 22499); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 22496); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22503); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 22501); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22502); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 22497); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22500); // Тапок

			oldItem1->SetFakeEntry(22498);
			oldItem2->SetFakeEntry(22499);
			oldItem3->SetFakeEntry(22496);
			oldItem4->SetFakeEntry(22503);
			oldItem5->SetFakeEntry(22501);
			oldItem6->SetFakeEntry(22502);
			oldItem7->SetFakeEntry(22497);
			oldItem8->SetFakeEntry(22500);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 38: // Лок Т3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 22506); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 22507); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 22504); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22511); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 22509); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22510); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 22505); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22508); // Тапок

			oldItem1->SetFakeEntry(22506);
			oldItem2->SetFakeEntry(22507);
			oldItem3->SetFakeEntry(22504);
			oldItem4->SetFakeEntry(22511);
			oldItem5->SetFakeEntry(22509);
			oldItem6->SetFakeEntry(22510);
			oldItem7->SetFakeEntry(22505);
			oldItem8->SetFakeEntry(22508);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 39: // Дру Т3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 22490); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 22491); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 22488); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22495); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 22493); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22494); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 22489); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22492); // Тапок

			oldItem1->SetFakeEntry(22490);
			oldItem2->SetFakeEntry(22491);
			oldItem3->SetFakeEntry(22488);
			oldItem4->SetFakeEntry(22495);
			oldItem5->SetFakeEntry(22493);
			oldItem6->SetFakeEntry(22494);
			oldItem7->SetFakeEntry(22489);
			oldItem8->SetFakeEntry(22492);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 41: // Вар Т4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 29011); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 29016); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 29012); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 29017); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 29015); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(29011);
			oldItem2->SetFakeEntry(29016);
			oldItem3->SetFakeEntry(29012);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(29017);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(29015);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 42: // Пал Т4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 29068); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 29070); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 29066); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 29067); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 29069); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(29068);
			oldItem2->SetFakeEntry(29070);
			oldItem3->SetFakeEntry(29066);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(29067);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(29069);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 43: // Хант Т4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 29081); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 29084); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 29082); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 29085); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 29083); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(29081);
			oldItem2->SetFakeEntry(29084);
			oldItem3->SetFakeEntry(29082);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(29085);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(29083);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 44: // Рог Т4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 29044); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 29047); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 29045); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 29048); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 29046); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(29044);
			oldItem2->SetFakeEntry(29047);
			oldItem3->SetFakeEntry(29045);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(29048);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(29046);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 45: // Прист Т4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 29049); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 29054); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 29050); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 29055); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 29053); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(29049);
			oldItem2->SetFakeEntry(29054);
			oldItem3->SetFakeEntry(29050);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(29055);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(29053);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 46: // Шам Т4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 29040); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 29043); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 29038); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 29039); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 29042); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(29040);
			oldItem2->SetFakeEntry(29043);
			oldItem3->SetFakeEntry(29038);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(29039);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(29042);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 47: // Маг Т4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 29076); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 29079); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 29077); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 29080); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 29078); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(29076);
			oldItem2->SetFakeEntry(29079);
			oldItem3->SetFakeEntry(29077);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(29080);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(29078);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 48: // Лок Т4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 28963); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 28967); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 28964); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 28968); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 28966); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(28963);
			oldItem2->SetFakeEntry(28967);
			oldItem3->SetFakeEntry(28964);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(28968);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(28966);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 49: // Дру Т4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 29098); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 29100); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 29096); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 29097); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 29099); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(29098);
			oldItem2->SetFakeEntry(29100);
			oldItem3->SetFakeEntry(29096);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(29097);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(29099);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 51: // Вар Т5
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30120); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30122); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30118); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 ,  30119); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30121); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(30120);
			oldItem2->SetFakeEntry(30122);
			oldItem3->SetFakeEntry(30118);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(30119);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(30121);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 52: // Пал Т5
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30136); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30138); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30134); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 30135); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30137); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(30136);
			oldItem2->SetFakeEntry(30138);
			oldItem3->SetFakeEntry(30134);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(30135);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(30137);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 53: // Хант Т5
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30141); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30143); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30139); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 30140); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30142); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(30141);
			oldItem2->SetFakeEntry(30143);
			oldItem3->SetFakeEntry(30139);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(30140);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(30142);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 54: // Рог Т5
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30146); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30149); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30144); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 30145); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30148); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(30146);
			oldItem2->SetFakeEntry(30149);
			oldItem3->SetFakeEntry(30144);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(30145);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(30148);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 55: // Прист Т5
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30161); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30163); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30159); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 30160); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30162); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(30161);
			oldItem2->SetFakeEntry(30163);
			oldItem3->SetFakeEntry(30159);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(30160);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(30162);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 56: // Шам Т5
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30171); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30173); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30169); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 30170); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30172); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(30171);
			oldItem2->SetFakeEntry(30173);
			oldItem3->SetFakeEntry(30169);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(30170);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(30172);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 57: // Маг Т5
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30206); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30210); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30196); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 30205); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30207); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(30206);
			oldItem2->SetFakeEntry(30210);
			oldItem3->SetFakeEntry(30196);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(30205);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(30207);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 58: // Лок Т5
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30212); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30215); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30214); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 30211); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30213); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(30212);
			oldItem2->SetFakeEntry(30215);
			oldItem3->SetFakeEntry(30214);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(30211);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(30213);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 59: // Дру Т5
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30233); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30235); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30231); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 30232); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30234); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(30233);
			oldItem2->SetFakeEntry(30235);
			oldItem3->SetFakeEntry(30231);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(30232);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(30234);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 61: // Вар Т6
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30972); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30979); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30975); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 34441); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 30969); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 34546); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30977); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 34569); // Тапок

			oldItem1->SetFakeEntry(30972);
			oldItem2->SetFakeEntry(30979);
			oldItem3->SetFakeEntry(30975);
			oldItem4->SetFakeEntry(34441);
			oldItem5->SetFakeEntry(30969);
			oldItem6->SetFakeEntry(34546);
			oldItem7->SetFakeEntry(30977);
			oldItem8->SetFakeEntry(34569);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 62: // Пал Т6
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30988); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30996); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30992); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 34432); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 30992); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 34487); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30994); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 34559); // Тапок

			oldItem1->SetFakeEntry(30988);
			oldItem2->SetFakeEntry(30996);
			oldItem3->SetFakeEntry(30992);
			oldItem4->SetFakeEntry(34432);
			oldItem5->SetFakeEntry(30992);
			oldItem6->SetFakeEntry(34487);
			oldItem7->SetFakeEntry(30994);
			oldItem8->SetFakeEntry(34559);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 63: // Хант Т6
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31003); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 31006); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 31004); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 34443); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31001); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 34549); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 31005); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 34570); // Тапок

			oldItem1->SetFakeEntry(31003);
			oldItem2->SetFakeEntry(31006);
			oldItem3->SetFakeEntry(31004);
			oldItem4->SetFakeEntry(34443);
			oldItem5->SetFakeEntry(31001);
			oldItem6->SetFakeEntry(34549);
			oldItem7->SetFakeEntry(31005);
			oldItem8->SetFakeEntry(34570);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 64: // Рог Т6
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31027); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 31030); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 31028); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 34448); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31026); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 34558); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 31029); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 34575); // Тапок

			oldItem1->SetFakeEntry(31027);
			oldItem2->SetFakeEntry(31030);
			oldItem3->SetFakeEntry(31028);
			oldItem4->SetFakeEntry(34448);
			oldItem5->SetFakeEntry(31026);
			oldItem6->SetFakeEntry(34558);
			oldItem7->SetFakeEntry(31029);
			oldItem8->SetFakeEntry(34575);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 65: // Прист Т6
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31063); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 31069); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 31066); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 34435); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31060); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 34527); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 31068); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 34562); // Тапок

			oldItem1->SetFakeEntry(31063);
			oldItem2->SetFakeEntry(31069);
			oldItem3->SetFakeEntry(31066);
			oldItem4->SetFakeEntry(34435);
			oldItem5->SetFakeEntry(31060);
			oldItem6->SetFakeEntry(34527);
			oldItem7->SetFakeEntry(31068);
			oldItem8->SetFakeEntry(34562);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 66: // Шам Т6
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31014); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 31023); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 31017); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 34437); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31008); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 34542); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 31020); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 34566); // Тапок

			oldItem1->SetFakeEntry(31014);
			oldItem2->SetFakeEntry(31023);
			oldItem3->SetFakeEntry(31017);
			oldItem4->SetFakeEntry(34437);
			oldItem5->SetFakeEntry(31008);
			oldItem6->SetFakeEntry(34542);
			oldItem7->SetFakeEntry(31020);
			oldItem8->SetFakeEntry(34566);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 67: // Маг Т6
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31056); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 31059); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 31057); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 34447); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31055); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 34557); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 31058); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 34574); // Тапок

			oldItem1->SetFakeEntry(31059);
			oldItem2->SetFakeEntry(16856);
			oldItem3->SetFakeEntry(31057);
			oldItem4->SetFakeEntry(34447);
			oldItem5->SetFakeEntry(31055);
			oldItem6->SetFakeEntry(34557);
			oldItem7->SetFakeEntry(31058);
			oldItem8->SetFakeEntry(34574);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 68: // Лок Т6
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31051); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 31054); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 31052); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 34436); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31050); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 34541); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 31053); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 34564); // Тапок

			oldItem1->SetFakeEntry(31051);
			oldItem2->SetFakeEntry(31054);
			oldItem3->SetFakeEntry(31052);
			oldItem4->SetFakeEntry(34436);
			oldItem5->SetFakeEntry(31050);
			oldItem6->SetFakeEntry(34541);
			oldItem7->SetFakeEntry(31053);
			oldItem8->SetFakeEntry(34564);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 69: // Дру Т6
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31037); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 31047); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 31041); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 34445); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31032); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 34554); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 31045); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 34571); // Тапок

			oldItem1->SetFakeEntry(31037);
			oldItem2->SetFakeEntry(31047);
			oldItem3->SetFakeEntry(31041);
			oldItem4->SetFakeEntry(34445);
			oldItem5->SetFakeEntry(31032);
			oldItem6->SetFakeEntry(34554);
			oldItem7->SetFakeEntry(31045);
			oldItem8->SetFakeEntry(34571);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 71: // Вар A1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 24545); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 24546); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 24544); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 ,  24549); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 24547); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(24545);
			oldItem2->SetFakeEntry(24546);
			oldItem3->SetFakeEntry(24544);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(24549);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(24547);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 72: // Пал A1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 27704); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 27706); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 27702); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 27703); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 27705); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(27704);
			oldItem2->SetFakeEntry(27706);
			oldItem3->SetFakeEntry(27702);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(27703);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(27705);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 73: // Хант A1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 28331); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 28333); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 28334); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 28335); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 28332); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(28331);
			oldItem2->SetFakeEntry(28333);
			oldItem3->SetFakeEntry(28334);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(28335);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(28332);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 74: // Рог A1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 25830); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 25832); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 25831); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 25834); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 25833); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(25830);
			oldItem2->SetFakeEntry(25832);
			oldItem3->SetFakeEntry(25831);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(25834);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(25833);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 75: // Прист A1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 27708); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 27710); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 27711); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 27707); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 27709); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(27708);
			oldItem2->SetFakeEntry(27710);
			oldItem3->SetFakeEntry(27711);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(27707);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(27709);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 76: // Шам A1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 25998); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 25999); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 25997); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 26000); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 26001); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(25998);
			oldItem2->SetFakeEntry(25999);
			oldItem3->SetFakeEntry(25997);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(26000);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(26001);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 77: // Маг A1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 25855); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 25854); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 25856); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 25857); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 25858); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(25855);
			oldItem2->SetFakeEntry(25854);
			oldItem3->SetFakeEntry(25856);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(25857);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(25858);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 78: // Лок A1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 24553); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 24554); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 24552); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 24556); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 24555); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(24553);
			oldItem2->SetFakeEntry(24554);
			oldItem3->SetFakeEntry(24552);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(24556);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(24555);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 79: // Дру A1
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 28127); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 28129); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 28130); // Тело
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 22423); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 28126); // Перчи
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 22422); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 28128); // Штаны
			//pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 22420); // Тапок

			oldItem1->SetFakeEntry(28127);
			oldItem2->SetFakeEntry(28129);
			oldItem3->SetFakeEntry(28130);
			//oldItem4->SetFakeEntry(16857);
			oldItem5->SetFakeEntry(28126);
			//oldItem6->SetFakeEntry(16858);
			oldItem7->SetFakeEntry(28128);
			//oldItem8->SetFakeEntry(16859);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 81: // Вар A2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 30488); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 30490); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 30486); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 32818); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 30487); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 32805); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 30489); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 32793); // Тапок

			oldItem1->SetFakeEntry(30488);
			oldItem2->SetFakeEntry(30490);
			oldItem3->SetFakeEntry(30486);
			oldItem4->SetFakeEntry(32818);
			oldItem5->SetFakeEntry(30487);
			oldItem6->SetFakeEntry(32805);
			oldItem7->SetFakeEntry(30489);
			oldItem8->SetFakeEntry(32793);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 82: // Пал A2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31997); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 31996); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 31992); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 32819); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31993); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 32806); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 31995); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 32794); // Тапок

			oldItem1->SetFakeEntry(31997);
			oldItem2->SetFakeEntry(31996);
			oldItem3->SetFakeEntry(31992);
			oldItem4->SetFakeEntry(32819);
			oldItem5->SetFakeEntry(31993);
			oldItem6->SetFakeEntry(32806);
			oldItem7->SetFakeEntry(31995);
			oldItem8->SetFakeEntry(32794);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 83: // Хант A2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31962); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 31964); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 31960); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 32809); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31961); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 32797); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 31963); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 32785); // Тапок

			oldItem1->SetFakeEntry(31962);
			oldItem2->SetFakeEntry(31964);
			oldItem3->SetFakeEntry(31960);
			oldItem4->SetFakeEntry(32809);
			oldItem5->SetFakeEntry(31961);
			oldItem6->SetFakeEntry(32797);
			oldItem7->SetFakeEntry(31963);
			oldItem8->SetFakeEntry(32785);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 84: // Рог A2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31999); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 32001); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 32002); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 32814); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31998); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 32801); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 32000); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 32790); // Тапок

			oldItem1->SetFakeEntry(31999);
			oldItem2->SetFakeEntry(32001);
			oldItem3->SetFakeEntry(32002);
			oldItem4->SetFakeEntry(32814);
			oldItem5->SetFakeEntry(31998);
			oldItem6->SetFakeEntry(32801);
			oldItem7->SetFakeEntry(32000);
			oldItem8->SetFakeEntry(32790);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 85: // Прист A2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 32016); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 32018); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 32019); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 32980); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 32015); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 32979); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 32017); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 32981); // Тапок

			oldItem1->SetFakeEntry(32016);
			oldItem2->SetFakeEntry(32018);
			oldItem3->SetFakeEntry(32019);
			oldItem4->SetFakeEntry(32980);
			oldItem5->SetFakeEntry(32015);
			oldItem6->SetFakeEntry(32979);
			oldItem7->SetFakeEntry(32017);
			oldItem8->SetFakeEntry(32981);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 86: // Шам A2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 32006); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 32008); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 32004); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 32816); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 32005); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 32803); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 32007); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 32791); // Тапок

			oldItem1->SetFakeEntry(32006);
			oldItem2->SetFakeEntry(32008);
			oldItem3->SetFakeEntry(32004);
			oldItem4->SetFakeEntry(32816);
			oldItem5->SetFakeEntry(32005);
			oldItem6->SetFakeEntry(32803);
			oldItem7->SetFakeEntry(32007);
			oldItem8->SetFakeEntry(32791);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 87: // Маг A2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 32048); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 32047); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 32050); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 32820); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 32049); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 32807); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 32051); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 32795); // Тапок

			oldItem1->SetFakeEntry(32048);
			oldItem2->SetFakeEntry(32047);
			oldItem3->SetFakeEntry(32050);
			oldItem4->SetFakeEntry(32820);
			oldItem5->SetFakeEntry(32049);
			oldItem6->SetFakeEntry(32807);
			oldItem7->SetFakeEntry(32051);
			oldItem8->SetFakeEntry(32795);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 88: // Лок A2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31974); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 31976); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 31977); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 32811); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31973); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 32799); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 31975); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 32787); // Тапок

			oldItem1->SetFakeEntry(31974);
			oldItem2->SetFakeEntry(31976);
			oldItem3->SetFakeEntry(31977);
			oldItem4->SetFakeEntry(32811);
			oldItem5->SetFakeEntry(31973);
			oldItem6->SetFakeEntry(32799);
			oldItem7->SetFakeEntry(31975);
			oldItem8->SetFakeEntry(32787);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 89: // Дру A2
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 31968); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 31971); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 31972); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 32812); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31967); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 32800); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 31969); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 32788); // Тапок

			oldItem1->SetFakeEntry(31968);
			oldItem2->SetFakeEntry(31971);
			oldItem3->SetFakeEntry(31972);
			oldItem4->SetFakeEntry(32812);
			oldItem5->SetFakeEntry(31967);
			oldItem6->SetFakeEntry(32800);
			oldItem7->SetFakeEntry(31969);
			oldItem8->SetFakeEntry(32788);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 91: // Вар A3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 33730); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 33732); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 33728); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 33813); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 33729); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 33811); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 33731); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 33812); // Тапок

			oldItem1->SetFakeEntry(33730);
			oldItem2->SetFakeEntry(33732);
			oldItem3->SetFakeEntry(33728);
			oldItem4->SetFakeEntry(33813);
			oldItem5->SetFakeEntry(33729);
			oldItem6->SetFakeEntry(33811);
			oldItem7->SetFakeEntry(33731);
			oldItem8->SetFakeEntry(33812);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 92: // Пал A3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 33724); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 33726); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 33722); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 33904); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 33723); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 33903); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 33725); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 33905); // Тапок

			oldItem1->SetFakeEntry(33724);
			oldItem2->SetFakeEntry(33726);
			oldItem3->SetFakeEntry(33722);
			oldItem4->SetFakeEntry(33904);
			oldItem5->SetFakeEntry(33723);
			oldItem6->SetFakeEntry(33903);
			oldItem7->SetFakeEntry(33725);
			oldItem8->SetFakeEntry(33905);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 93: // Хант A3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 33666); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 33668); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 33664); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 33876); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 33665); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 33877); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 33667); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 33878); // Тапок

			oldItem1->SetFakeEntry(33666);
			oldItem2->SetFakeEntry(33668);
			oldItem3->SetFakeEntry(33664);
			oldItem4->SetFakeEntry(33876);
			oldItem5->SetFakeEntry(33665);
			oldItem6->SetFakeEntry(33877);
			oldItem7->SetFakeEntry(33667);
			oldItem8->SetFakeEntry(33878);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 94: // Рог A3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 33701); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 33703); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 33704); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 33893); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 33700); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 33891); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 33702); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 33892); // Тапок

			oldItem1->SetFakeEntry(33701);
			oldItem2->SetFakeEntry(33703);
			oldItem3->SetFakeEntry(33704);
			oldItem4->SetFakeEntry(33893);
			oldItem5->SetFakeEntry(33700);
			oldItem6->SetFakeEntry(33891);
			oldItem7->SetFakeEntry(33702);
			oldItem8->SetFakeEntry(33892);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 95: // Прист A3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 33745); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 33747); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 33748); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 33901); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 33744); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 33900); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 33746); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 33902); // Тапок

			oldItem1->SetFakeEntry(33745);
			oldItem2->SetFakeEntry(33747);
			oldItem3->SetFakeEntry(33748);
			oldItem4->SetFakeEntry(33901);
			oldItem5->SetFakeEntry(33744);
			oldItem6->SetFakeEntry(33900);
			oldItem7->SetFakeEntry(33746);
			oldItem8->SetFakeEntry(33902);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 96: // Шам A3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 33708); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 33710); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 33706); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 33906); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 33707); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 33907); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 33709); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 33908); // Тапок

			oldItem1->SetFakeEntry(33708);
			oldItem2->SetFakeEntry(33710);
			oldItem3->SetFakeEntry(33706);
			oldItem4->SetFakeEntry(33906);
			oldItem5->SetFakeEntry(33707);
			oldItem6->SetFakeEntry(33907);
			oldItem7->SetFakeEntry(33709);
			oldItem8->SetFakeEntry(33908);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 97: // Маг A3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 33758); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 33757); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 33760); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 33913); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 33759); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 33912); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 33761); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 33914); // Тапок

			oldItem1->SetFakeEntry(33758);
			oldItem2->SetFakeEntry(33757);
			oldItem3->SetFakeEntry(33760);
			oldItem4->SetFakeEntry(33913);
			oldItem5->SetFakeEntry(33759);
			oldItem6->SetFakeEntry(33912);
			oldItem7->SetFakeEntry(33761);
			oldItem8->SetFakeEntry(33914);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 98: // Лок A3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 33677); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 33679); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 33680); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 33883); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 33676); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 33882); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 33678); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 33884); // Тапок

			oldItem1->SetFakeEntry(33677);
			oldItem2->SetFakeEntry(33679);
			oldItem3->SetFakeEntry(33680);
			oldItem4->SetFakeEntry(33883);
			oldItem5->SetFakeEntry(33676);
			oldItem6->SetFakeEntry(33882);
			oldItem7->SetFakeEntry(33678);
			oldItem8->SetFakeEntry(33884);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 99: // Дру A3
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 33691); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 33693); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 33694); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 33887); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 33690); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 33885); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 33692); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 33886); // Тапок

			oldItem1->SetFakeEntry(33691);
			oldItem2->SetFakeEntry(33693);
			oldItem3->SetFakeEntry(33694);
			oldItem4->SetFakeEntry(33887);
			oldItem5->SetFakeEntry(33690);
			oldItem6->SetFakeEntry(33885);
			oldItem7->SetFakeEntry(33692);
			oldItem8->SetFakeEntry(33886);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 101: // Вар A4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 35068); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 35070); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 35066); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 35176); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 35067); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 35161); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 35069); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 35146); // Тапок

			oldItem1->SetFakeEntry(35068);
			oldItem2->SetFakeEntry(35070);
			oldItem3->SetFakeEntry(35066);
			oldItem4->SetFakeEntry(35176);
			oldItem5->SetFakeEntry(35067);
			oldItem6->SetFakeEntry(35161);
			oldItem7->SetFakeEntry(35069);
			oldItem8->SetFakeEntry(35146);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 102: // Пал A4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 35029); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 35031); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 35027); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 35175); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 35028); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 35160); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 35030); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 35145); // Тапок

			oldItem1->SetFakeEntry(35029);
			oldItem2->SetFakeEntry(35031);
			oldItem3->SetFakeEntry(35027);
			oldItem4->SetFakeEntry(35175);
			oldItem5->SetFakeEntry(35028);
			oldItem6->SetFakeEntry(35160);
			oldItem7->SetFakeEntry(35030);
			oldItem8->SetFakeEntry(35145);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 103: // Хант A4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 34992); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 34994); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 34990); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 35166); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 34991); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 35151); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 34993); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 35136); // Тапок

			oldItem1->SetFakeEntry(34992);
			oldItem2->SetFakeEntry(34994);
			oldItem3->SetFakeEntry(34990);
			oldItem4->SetFakeEntry(35166);
			oldItem5->SetFakeEntry(34991);
			oldItem6->SetFakeEntry(35151);
			oldItem7->SetFakeEntry(34993);
			oldItem8->SetFakeEntry(35136);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 104: // Рог A4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 35033); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 35035); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 35036); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 35171); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 35032); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 35156); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 35034); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 35141); // Тапок

			oldItem1->SetFakeEntry(35033);
			oldItem2->SetFakeEntry(35035);
			oldItem3->SetFakeEntry(35036);
			oldItem4->SetFakeEntry(35171);
			oldItem5->SetFakeEntry(35032);
			oldItem6->SetFakeEntry(35156);
			oldItem7->SetFakeEntry(35034);
			oldItem8->SetFakeEntry(35141);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 105: // Прист A4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 35084); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 35086); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 35087); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 35174); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 35083); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 35159); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 35085); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 35144); // Тапок

			oldItem1->SetFakeEntry(35084);
			oldItem2->SetFakeEntry(35086);
			oldItem3->SetFakeEntry(35087);
			oldItem4->SetFakeEntry(35174);
			oldItem5->SetFakeEntry(35083);
			oldItem6->SetFakeEntry(35159);
			oldItem7->SetFakeEntry(35085);
			oldItem8->SetFakeEntry(35144);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 106: // Шам A4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 35044); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 35046); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 35042); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 35177); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 35043); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 35162); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 35045); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 35147); // Тапок

			oldItem1->SetFakeEntry(35044);
			oldItem2->SetFakeEntry(35046);
			oldItem3->SetFakeEntry(35042);
			oldItem4->SetFakeEntry(35177);
			oldItem5->SetFakeEntry(35043);
			oldItem6->SetFakeEntry(35162);
			oldItem7->SetFakeEntry(35045);
			oldItem8->SetFakeEntry(35147);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 107: // Маг A4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 35097); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 35096); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 35099); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 35179); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 35098); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 35164); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 35100); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 35149); // Тапок

			oldItem1->SetFakeEntry(35097);
			oldItem2->SetFakeEntry(35096);
			oldItem3->SetFakeEntry(35099);
			oldItem4->SetFakeEntry(35179);
			oldItem5->SetFakeEntry(35098);
			oldItem6->SetFakeEntry(35164);
			oldItem7->SetFakeEntry(35100);
			oldItem8->SetFakeEntry(35149);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 108: // Лок A4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 35004); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 35006); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 35007); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 35168); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 35003); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 35153); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 35005); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 35138); // Тапок

			oldItem1->SetFakeEntry(35004);
			oldItem2->SetFakeEntry(35006);
			oldItem3->SetFakeEntry(35007);
			oldItem4->SetFakeEntry(35168);
			oldItem5->SetFakeEntry(35003);
			oldItem6->SetFakeEntry(35153);
			oldItem7->SetFakeEntry(35005);
			oldItem8->SetFakeEntry(35138);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		break;
		case GOSSIP_ACTION_INFO_DEF + 109: // Дру A4
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 34999); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 35001); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 35002); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 32788); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 34998); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 35154); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 35000); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 35139); // Тапок

			oldItem1->SetFakeEntry(34999);
			oldItem2->SetFakeEntry(35001);
			oldItem3->SetFakeEntry(35002);
			oldItem4->SetFakeEntry(32788);
			oldItem5->SetFakeEntry(34998);
			oldItem6->SetFakeEntry(35154);
			oldItem7->SetFakeEntry(35000);
			oldItem8->SetFakeEntry(35139);

			// Обновить вид, взять плату
			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->ModifyMoney((-1)*sWorld.getConfig(CONFIG_TRANS_GOLD) * 10000);
			pPlayer->ModifyHonorPoints((-1)*sWorld.getConfig(CONFIG_TRANS_HONOR));
			pPlayer->ModifyArenaPoints((-1)*sWorld.getConfig(CONFIG_TRANS_AP));
			pPlayer->DestroyItemCount((-1)*sWorld.getConfig(CONFIG_TRANS_ITEM),(-1)*sWorld.getConfig(CONFIG_TRANS_ITEMCOUNT), true);
			return true;
		}
		case GOSSIP_ACTION_INFO_DEF + 110: // Уделение трансов
		{
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , oldItem1->GetEntry()); // Шлем
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , oldItem2->GetEntry()); // Плечи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , oldItem3->GetEntry()); // Тело
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , oldItem4->GetEntry()); // Брас
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , oldItem5->GetEntry()); // Перчи
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , oldItem6->GetEntry()); // Пояс
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , oldItem7->GetEntry()); // Штаны
			pPlayer->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , oldItem8->GetEntry()); // Тапок

			oldItem1->DeleteFakeEntry();
			oldItem2->DeleteFakeEntry();
			oldItem3->DeleteFakeEntry();
			oldItem4->DeleteFakeEntry();
			oldItem5->DeleteFakeEntry();
			oldItem6->DeleteFakeEntry();
			oldItem7->DeleteFakeEntry();
			oldItem8->DeleteFakeEntry();

			UpdateGear(pPlayer); pPlayer->CLOSE_GOSSIP_MENU();
			return true;
		}
		break;
	}
	return true;
}
void AddSC_npc_transmogrification()
{
	Script *newscript;
	newscript = new Script;
	newscript->Name="npc_transmogrification";
	newscript->pGossipHello = &GossipHello_npc_transmogrification;
	newscript->pGossipSelect = &GossipSelect_npc_transmogrification;
	newscript->RegisterSelf();
}