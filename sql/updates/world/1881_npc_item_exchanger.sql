/*
Navicat MySQL Data Transfer

Source Server         : root
Source Server Version : 50140
Source Host           : localhost:3306
Source Database       : world

Target Server Type    : MYSQL
Target Server Version : 50140
File Encoding         : 65001

Date: 2014-02-22 13:38:58
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `npc_item_exchanger`
-- ----------------------------
DROP TABLE IF EXISTS `npc_item_exchanger`;
CREATE TABLE `npc_item_exchanger` (
  `type` int(3) unsigned NOT NULL DEFAULT '0',
  `active` int(3) unsigned NOT NULL DEFAULT '0',
  `text1` char(100) NOT NULL,
  `text2` char(100) NOT NULL,
  `item1id` int(11) unsigned NOT NULL DEFAULT '0',
  `item1count` int(11) unsigned NOT NULL DEFAULT '0',
  `item2id` int(11) unsigned NOT NULL DEFAULT '0',
  `item2count` int(11) unsigned NOT NULL DEFAULT '0',
  `action` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`type`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of npc_item_exchanger
-- ----------------------------
INSERT INTO `npc_item_exchanger` VALUES ('1', '1', 'Exchange Badge ro Badge', 'Here are your Badge', '29434', '1', '29434', '1', '1001');
INSERT INTO `npc_item_exchanger` VALUES ('2', '1', 'Exchange Badge ro Badge', 'Here are your Badge', '29434', '1', '29434', '1', '1002');
INSERT INTO `npc_item_exchanger` VALUES ('3', '1', 'Exchange Badge ro Badge', 'Here are your Badge', '29434', '1', '29434', '1', '1003');
INSERT INTO `npc_item_exchanger` VALUES ('4', '1', 'Exchange Badge ro Badge', 'Here are your Badge', '29434', '1', '29434', '1', '1004');
INSERT INTO `npc_item_exchanger` VALUES ('5', '1', 'Exchange Badge ro Badge', 'Here are your Badge', '29434', '1', '29434', '1', '1005');
INSERT INTO `npc_item_exchanger` VALUES ('6', '1', 'Exchange Badge ro Badge', 'Here are your Badge', '29434', '1', '29434', '1', '1006');
INSERT INTO `npc_item_exchanger` VALUES ('7', '1', 'Exchange Badge ro Badge', 'Here are your Badge', '29434', '1', '29434', '1', '1007');
INSERT INTO `npc_item_exchanger` VALUES ('8', '1', 'Exchange Badge ro Badge', 'Here are your Badge', '29434', '1', '29434', '1', '1008');
INSERT INTO `npc_item_exchanger` VALUES ('9', '1', 'Exchange Badge ro Badge', 'Here are your Badge', '29434', '1', '29434', '1', '1009');
INSERT INTO `npc_item_exchanger` VALUES ('10', '1', 'Exchange Badge ro Badge', 'Here are your Badge', '29434', '1', '29434', '1', '1010');
