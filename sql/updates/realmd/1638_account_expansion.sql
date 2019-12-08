UPDATE `account` SET `expansion`=1;
ALTER TABLE `account` CHANGE `expansion` `expansion` tinyint(3) unsigned NOT NULL default '1';