#pragma once
#ifndef _CARD_H
#define _CARD_H
//¿¨²¿·Ö
class card
{
public:
	string name, explain;
	int huaseNUM, colorNUM;
	card() {};
	card(string name, int huase, int color, string explain) :colorNUM(color), huaseNUM(huase), name(name), explain(explain) {};
};
extern string huase_lst[];
extern string color_lst[];
extern role role_lst[2];
extern int role_num;
extern int choice;
extern queue<card>pd;
extern string defencer_lst[];
extern string weapon_lst[];
extern string skill_lst[];
extern string horse_lst[];
extern role playerrole;
extern role robotrole;
#endif // !_CARD_H