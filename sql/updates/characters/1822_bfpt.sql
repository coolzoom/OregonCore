SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `bfpt`
-- ----------------------------
DROP TABLE IF EXISTS `bfpt`;
CREATE TABLE `bfpt` (
  `guid` int(11) NOT NULL,
  `first` tinyint(3) NOT NULL,
  `second` tinyint(3) NOT NULL,
  `third` tinyint(3) NOT NULL,
  PRIMARY KEY (`guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;