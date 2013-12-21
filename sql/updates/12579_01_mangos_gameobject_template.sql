ALTER TABLE db_version CHANGE COLUMN required_12562_01_mangos_playercreateinfo_action required_12579_01_mangos_gameobject_template bit;

ALTER TABLE `gameobject_template` ADD `AIName` char(64) NOT NULL DEFAULT '' AFTER `maxgold`;
