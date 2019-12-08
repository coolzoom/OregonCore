SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `vip`
-- ----------------------------
DROP TABLE IF EXISTS `vip`;
CREATE TABLE `vip` (
  `guid` int(11) NOT NULL,
  `DateOfStart` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`guid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
