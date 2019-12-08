INSERT INTO `creature_template` (`entry`, `heroic_entry`, `KillCredit1`, `KillCredit2`, `modelid_A`, `modelid_A2`, `modelid_H`, `modelid_H2`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `baseattacktime`, `rangeattacktime`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `class`, `race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `RacialLeader`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES (735005, 0, 0, 0, 15990, 0, 15990, 0, 'Exchanger', NULL, NULL, 0, 70, 70, 100000, 100000, 0, 0, 100000, 35, 35, 1, 1.5, 1, 1, 100000, 100000, 0, 100000, 500, 500, 0, 0, 0, 0, 0, 0, 0, 100000, 100000, 50000, 7, 0, 0, 0, 0, 10000, 10000, 10000, 10000, 10000, 10000, 0, 0, 0, 0, 0, 0, 0, '', 1, 3, 0, 1, 0, 0, 0, 'npc_exchanger');

/*
Navicat MySQL Data Transfer

Source Server         : root
Source Server Version : 50140
Source Host           : localhost:3306
Source Database       : world

Target Server Type    : MYSQL
Target Server Version : 50140
File Encoding         : 65001

Date: 2014-02-09 20:03:35
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `npc_exchanger`
-- ----------------------------
DROP TABLE IF EXISTS `npc_exchanger`;
CREATE TABLE `npc_exchanger` (
  `type` int(3) unsigned NOT NULL DEFAULT '0',
  `active` int(3) unsigned NOT NULL DEFAULT '0',
  `text1` char(100) NOT NULL,
  `text2` char(100) NOT NULL,
  `data1` int(11) unsigned NOT NULL DEFAULT '0',
  `data2` int(11) unsigned NOT NULL DEFAULT '0',
  `data3` int(11) unsigned NOT NULL DEFAULT '0',
  `action` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`type`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of npc_exchanger
-- ----------------------------
INSERT INTO `npc_exchanger` VALUES ('1', '1', '1000 Honor To 100 AP', 'Here are your 100 AP', '1000', '100', '0', '1001');
INSERT INTO `npc_exchanger` VALUES ('2', '1', '100 AP To 1000 Honor', 'Here are your 1000 Honor', '100', '1000', '0', '1002');
INSERT INTO `npc_exchanger` VALUES ('3', '1', '1000 Honor To 10 Badges', 'Here are your 10 Badges', '1000', '10', '29434', '1003');
INSERT INTO `npc_exchanger` VALUES ('4', '1', '100 AP To 10 Badge', 'Here are your 10 Badges', '100', '10', '29434', '1004');
INSERT INTO `npc_exchanger` VALUES ('5', '1', '1 Badge To 100 Honor', 'Here are your 100 Honor', '1', '100', '29434', '1005');
INSERT INTO `npc_exchanger` VALUES ('6', '1', '1 Badge To 10 AP', 'Here are your 10 AP', '1', '10', '29434', '1006');
INSERT INTO `npc_exchanger` VALUES ('7', '1', '10 Gold to 1 Badge', 'Here are your 1 Badge', '10', '1', '29434', '1007');
INSERT INTO `npc_exchanger` VALUES ('8', '1', '1 Badge To 10 Gold', 'Here are your 10 Gold', '1', '10', '29434', '1008');
INSERT INTO `npc_exchanger` VALUES ('9', '1', '10 Gold To 100 Honor', 'Here are your 100 Honor', '10', '100', '0', '1009');
INSERT INTO `npc_exchanger` VALUES ('10', '1', '100 Honor To 10 Gold', 'Here are your 10 Gold', '100', '10', '0', '1010');
INSERT INTO `npc_exchanger` VALUES ('11', '1', '10 Gold To 10 AP', 'Here are your 10 AP', '10', '10', '0', '1011');
INSERT INTO `npc_exchanger` VALUES ('12', '1', '10 AP To 10 Gold', 'Here are your 10 Gold', '10', '10', '0', '1012');

