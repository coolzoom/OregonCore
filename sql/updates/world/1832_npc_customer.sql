INSERT INTO `creature_template` VALUES (735006, 0, 0, 0, 22957, 0, 22957, 0, 'Customer', NULL, NULL, 0, 70, 70, 100000, 100000, 0, 0, 100000, 35, 35, 1, 1.5, 1, 1, 100000, 100000, 0, 100000, 500, 500, 0, 0, 0, 0, 0, 0, 0, 100000, 100000, 50000, 7, 0, 0, 0, 0, 10000, 10000, 10000, 10000, 10000, 10000, 0, 0, 0, 0, 0, 0, 0, '', 1, 3, 0, 1, 0, 0, 0, 'npc_customer');

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `npc_customer`
-- ----------------------------
DROP TABLE IF EXISTS `npc_customer`;
CREATE TABLE `npc_customer` (
  `type` int(3) unsigned NOT NULL DEFAULT '0',
  `active` int(3) unsigned NOT NULL DEFAULT '0',
  `text` char(100) NOT NULL,
  `cost_gold` int(11) unsigned NOT NULL DEFAULT '0',
  `cost_honor` int(11) unsigned NOT NULL DEFAULT '0',
  `cost_ap` int(11) unsigned NOT NULL DEFAULT '0',
  `cost_itemid` int(11) unsigned NOT NULL DEFAULT '0',
  `constitemcount` int(11) unsigned NOT NULL DEFAULT '0',
  `action` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`type`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of npc_customer
-- ----------------------------
INSERT INTO `npc_customer` VALUES ('1', '1', 'Change My Race', '0', '0', '0', '0', '0', '1001');
INSERT INTO `npc_customer` VALUES ('2', '1', 'Customize Character', '0', '0', '0', '0', '0', '1002');
INSERT INTO `npc_customer` VALUES ('3', '1', 'Change My Name. It kick You.', '0', '0', '0', '0', '0', '1003');
