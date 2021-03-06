/* $Id$ */
/*
    ------------------------------------------------------------------------------------
    LICENSE:
    ------------------------------------------------------------------------------------
    This file is part of The Open Ragnarok Project
    Copyright 2007 - 2009 The Open Ragnarok Team
    For the latest information visit http://www.open-ragnarok.org
    ------------------------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the Free Software
    Foundation; either version 2 of the License, or (at your option) any later
    version.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with
    this program; if not, write to the Free Software Foundation, Inc., 59 Temple
    Place - Suite 330, Boston, MA 02111-1307, USA, or go to
    http://www.gnu.org/copyleft/lesser.txt.
    ------------------------------------------------------------------------------------
*/
#ifndef __OPENRO_RO_STRUCTURES_H
#define __OPENRO_RO_STRUCTURES_H

struct CharAttributes {
	unsigned char Str;
	unsigned char Agi;
	unsigned char Vit;
	unsigned char Int;
	unsigned char Dex;
	unsigned char Luk;
};

struct InventoryItem {
	short index;
	short id;
	char type;
	char identified;
	short type_equip;
	short equipped;
	char broken;
	char upgrade;
	short amount;
	unsigned int expire;
	char cards[12]; // Packet 0295 uses 12 bytes. All others uses 8.
};

struct HotkeyInfo {
	char type;
	int id;
	short lvl;
};

struct CharInformation {
	unsigned int id;
	unsigned int base_xp;
	int zeny;
	unsigned int job_xp;
	unsigned int job_lv;
	// unsigned int opt1;
	// unsigned int opt2;
	unsigned int option;
	unsigned int karma;
	unsigned int manner;
	unsigned short status_point;
	unsigned short hp;
	unsigned short max_hp;
	unsigned short sp;
	unsigned short max_sp;
	unsigned short speed;
	unsigned short Class;
	unsigned short hair;
	unsigned short weapon;
	unsigned short base_lv;
	unsigned short skill_point;
	unsigned short head_bottom;
	unsigned short shield;
	unsigned short head_top;
	unsigned short head_mid;
	unsigned short head_color;
	unsigned short clothes_color;
	char name[24];
	CharAttributes attributes;
	unsigned short slot;
	unsigned short rename;
};

struct SkillInformation {
	unsigned short id;
	unsigned int target_type;
	unsigned short level;
	unsigned short sp;
	unsigned short range;
	char name[24];
	char up;
};

struct ActorInfo {
	unsigned int id;
	unsigned short walk_speed;
	unsigned short opt1;
	unsigned short opt2;
	unsigned short option;
	unsigned short type;
	unsigned short hair_style;
	unsigned short weapon;
	unsigned short lowhead;
	unsigned short shield;
	unsigned short tophead;
	unsigned short midhead;
	unsigned short hair_color;
	unsigned short clothes_color;
	unsigned short head_dir;
	unsigned int guildID;
	unsigned short emblemID;
	unsigned short manner;
	unsigned short opt3;
	unsigned char karma;
	unsigned char sex;
	unsigned short coord_x, coord_y, dir;
	unsigned char unknown1;
	unsigned char unknown2;
	unsigned char act;
	unsigned short lv;
	unsigned int ticks;
};

#endif /* __OPENRO_RO_STRUCTURES_H */
