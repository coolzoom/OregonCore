CREATE TABLE `referrals` (
`referral_guid`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`refferer_guid`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`totaltime_start`  int(11) UNSIGNED NOT NULL DEFAULT 0 ,
`present_1`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`present_2`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
`present_3`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 ,
PRIMARY KEY (`referral_guid`)
)
ENGINE=InnoDB
DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
ROW_FORMAT=COMPACT;


ALTER TABLE `referrals`
ADD COLUMN `referrer_name`  varchar(12) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' AFTER `refferer_guid`;

