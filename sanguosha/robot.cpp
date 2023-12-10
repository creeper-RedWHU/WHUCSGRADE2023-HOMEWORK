#include<iostream>
#include<string>
#include<algorithm>
#include<queue>
using namespace std;
class role;
#include"role.h"
class card;
#include"card.h"
class player; class robot;
#include"player_robot.h"
void robot::init()
{
	handNUM = 4;
	for (int i = 0; i < 4; i++)
	{
		rbt_lst[i] = pd.front();
		pd.pop();
	}
	cout << "===========机器人抽牌完毕" << endl;
}
robot::robot(role a)
{
	name = &robotrole;
	HPnow = name->HP;
}
robot::robot() {};
void robot::annother()
{
	cout << "机器人的回合" << endl;
	kill = 0;
	for (int i = 0; i < 2; i++)
	{
		rbt_lst[handNUM++] = pd.front();
		pd.pop();
	}
	if (lbssnum == 1)
	{
		cout << "接下来进入机器人的乐不思蜀判定时间" << endl;
		card ls = pd.front();
		pd.pop();
		pd.push(ls);
		if (ls.colorNUM == 0 and ls.huaseNUM == 2)
		{
			cout << "花色为红桃！机器人不用跳过出牌阶段！" << endl;
		}
		else
		{
			cout << "花色为" << color_lst[ls.colorNUM] << huase_lst[ls.huaseNUM] << "！机器人跳过出牌阶段！" << endl;
			lbsse = true;
		}
		lbssnum = 0;
	}
}
bool robot::judge()
{
	if (HPnow <= 0)  return false;
	else return true;
}
void robot::finish()
{
	int srand;
	if (handNUM > HPnow)
	{
		cout << "机器人弃掉" << handNUM - HPnow << "张牌" << endl;
	}
	else
	{
		cout << "机器人不需要弃牌！" << endl;
	}
	while (handNUM > HPnow)
	{
		srand = rand() % handNUM;
		cout << "机器人弃掉了" << rbt_lst[srand].name << endl;
		pd.push(rbt_lst[srand]);
		for (int i = srand; i < handNUM - 1; i++)
		{
			rbt_lst[i] = rbt_lst[i + 1];
		}
		handNUM--;
	}
	cout << "机器人弃牌阶段结束！" << endl;
	lbsse = false;
	return;
}
void robot::defence(int n, int colornum)
{
	//普通防御（无防具）函数：通过检包来实现闪避或者扣血,有防具：查看防具
	if (n == 0 or numOfDefencer == 0)
	{
		int i = 0;
		for (i; i < handNUM; i++)
		{
			if (rbt_lst[i].name == "闪")break;
		}
		if (i == handNUM)
		{
			cout << "机器人没有出闪，扣一滴血！" << endl;
			HPnow -= 1;
			return;
		}
		else
		{
			cout << "机器人出闪" << endl;
			pd.push(rbt_lst[i]);
			for (int j = i; j < handNUM - 1; j++)
			{
				rbt_lst[j] = rbt_lst[j + 1];
			}
			handNUM--;
			return;
		}
	}
	else
	{
		if (defencer.name == "八卦阵")
		{
			cout << "机器人发动防具：八卦阵" << endl;
			card cc = pd.front();
			pd.pop();
			pd.push(cc);
			if (cc.colorNUM == 0)
			{
				cout << "八卦阵生效，该牌为：" << color_lst[cc.colorNUM] << huase_lst[cc.huaseNUM] << ",机器人视为出了一张闪" << endl;
				return;
			}
			else
			{
				cout << "八卦阵没生效，该牌为：" << color_lst[cc.colorNUM] << huase_lst[cc.huaseNUM] << endl;
				int i = 0;
				for (i; i < handNUM; i++)
				{
					if (rbt_lst[i].name == "闪")break;
				}
				if (i == handNUM)
				{
					cout << "机器人没有出闪，扣一滴血！" << endl;
					HPnow -= 1;
					if (name->id == 1)delta(1);
					return;
				}
				else
				{
					cout << "机器人出闪" << endl;
					pd.push(rbt_lst[i]);
					for (int j = i; j < handNUM - 1; j++)
					{
						rbt_lst[j] = rbt_lst[j + 1];
					}
					handNUM--;
					return;
				}
			}
		}
		else if (defencer.name == "仁王盾")
		{
			cout << "机器人发动仁王盾！" << endl;
			if (colornum == 1)
			{
				cout << "由于仁王盾的效果，黑色杀无效！" << endl;
				return;
			}
			else
			{
				cout << "仁王盾对红色杀无效！" << endl;
				int i = 0;
				for (i; i < handNUM; i++)
				{
					if (rbt_lst[i].name == "闪")break;
				}
				if (i == handNUM)
				{
					cout << "机器人没有出闪，扣一滴血！" << endl;
					HPnow -= 1;
					if (name->id == 1)delta(1);
					return;
				}
				else
				{
					cout << "机器人出闪" << endl;
					pd.push(rbt_lst[i]);
					for (int j = i; j < handNUM - 1; j++)
					{
						rbt_lst[j] = rbt_lst[j + 1];
					}
					handNUM--;
					return;
				}
			}
		}
	}
}
bool robot::jd_kill()
{
	bool li = false;
	for (int i = 0; i < handNUM; i++)
	{
		if (rbt_lst[i].name == "杀")
		{
			cout << "机器人成功出杀！" << endl;
			pd.push(rbt_lst[i]);
			for (int j = i; j < handNUM; j++)rbt_lst[j] = rbt_lst[j + 1];
			handNUM--;
			return true;
		}
	}
	if (weapon.name == "丈八蛇矛" and handNUM >= 2)
	{
		int fa, fb;
		fa = rand() % handNUM;
		fb = rand() % handNUM;
		while(fb == fa)fb = rand() % handNUM;
		if (fa > fb) { int ffc = fa; fa = fb; fb = ffc; }
		pd.push(rbt_lst[fa]); pd.push(rbt_lst[fb]);
		cout << "机器人弃置：" << rbt_lst[fa].name << ',' << rbt_lst[fb].name << "发动丈八蛇矛！" << endl;
		for (int i = fb; i < handNUM - 1; i++)rbt_lst[i] = rbt_lst[i + 1]; handNUM--;
		for (int i = fa; i < handNUM - 1; i++)rbt_lst[i] = rbt_lst[i + 1]; handNUM--;
		cout << "机器人丈八蛇矛发动成功！" << endl;
		return true;
	}
	return li;
}
bool robot::is_wxkj_used()
{
	int i = 0; bool iii = false;
	for (i; i < handNUM; i++)
	{
		if (rbt_lst[i].name == "无懈可击")
		{
			iii = true;
			break;
		}
	}
	if (iii)
	{
		for (int j = i; j < handNUM - 1; j++)rbt_lst[j] = rbt_lst[j + 1];
		cout << "机器人使用了无懈可击！" << endl;
		if (name->id == 2)
		{
			cout << "机器人发动黄月英的技能！摸一张牌" << endl;
			rbt_lst[handNUM++] = pd.front();
			pd.pop();
		}
		return iii;
	}
	else
	{
		return false;
	}
}
void robot::weapon_kill(player** human, int used)
{
	cout << "机器人发动武器：" << weapon.name << "，对您出杀！";
	if(used !=-1)
	{ 
		if (weapon.name == "诸葛连弩")
		{
			card cc = rbt_lst[used];
			kill = 0;
			pd.push(rbt_lst[used]);
			for (int i = used; i < handNUM - 1; i++)
			{
				rbt_lst[i] = rbt_lst[i + 1];
			}
			handNUM -= 1;
			(*human)->defence(1, cc.colorNUM);
		}
		else if (weapon.name == "青缸剑")
		{
			card cc = rbt_lst[used];
			pd.push(rbt_lst[used]);
			for (int i = used; i < handNUM - 1; i++)
			{
				rbt_lst[i] = rbt_lst[i + 1];
			}
			handNUM -= 1;
			kill = 1;
			(*human)->defence(0, cc.colorNUM);
		}
		else if (weapon.name == "雌雄双股剑")
		{
			if ((*human)->name->sex != name->sex)
			{
				int choice = rand() % 2;
				if (choice == 0)
				{
					cout << "雌雄双股剑发动成功！让机器人摸一张牌！" << endl;
					rbt_lst[handNUM++] = pd.front();
					pd.pop();
					cout << "机器人摸到的牌是：" << rbt_lst[handNUM - 1].name << endl;
				}
				else
				{
					cout << "雌雄双股剑发动成功！机器人让您随机少一张牌！" << endl;
					int srand = rand() % (*human)->handNUM;
					pd.push((*human)->player_lst[srand]);
					cout << "机器人弃掉您的牌是：" << (*human)->player_lst[srand].name << endl;
					for (int i = srand; i < (*human)->handNUM - 1; i++)
					{
						(*human)->player_lst[i] = (*human)->player_lst[i + 1];
					}
					(*human)->handNUM -= 1;
				}
			}
			else
			{
				cout << "机器人的雌雄双股剑发动无效！" << endl;
			}
			card cc = rbt_lst[used];
			pd.push(rbt_lst[used]);
			for (int i = used; i < handNUM - 1; i++)
			{
				rbt_lst[i] = rbt_lst[i + 1];
			}
			handNUM -= 1;
			kill = 1;
			(*human)->defence(1, cc.colorNUM);
		}
		else if (weapon.name == "寒冰剑")
		{
			int HPbefore = (*human)->HPnow;
			card cc = rbt_lst[used];
			pd.push(rbt_lst[used]);
			for (int i = used; i < handNUM - 1; i++)
			{
				rbt_lst[i] = rbt_lst[i + 1];
			}
			handNUM -= 1;
			kill = 1;
			(*human)->defence(1, cc.colorNUM);
			if ((*human)->HPnow < HPbefore)
			{
				if ((*human)->numOfWeapon + (*human)->numOfDefencer + (*human)->numofhorse + (*human)->handNUM < 2)
				{
					cout << "检测到您的牌数小于两张，机器人放弃发动寒冰剑！" << endl;
					return;
				}
				cout << "寒冰剑发动成功!机器人最多弃置您两张牌（包含装备和马）" << endl;
				(*human)->HPnow += 1;
				int num = 2;
				int srand;
				if ((*human)->numOfWeapon != 0)
				{
					cout << "机器人弃置了您的武器：" << (*human)->weapon.name << endl;
					pd.push((*human)->weapon);
					(*human)->weapon = card();
					(*human)->numOfWeapon = 0;
					num--;
				}
				if ((*human)->numOfDefencer != 0)
				{
					cout << "机器人弃置了您的防具：" << (*human)->defencer.name << endl;
					pd.push((*human)->defencer);
					(*human)->defencer = card();
					(*human)->numOfDefencer = 0;
					num--;
				}
				if (num > 0 and (*human)->numofhorse > 0)
				{
					cout << "机器人弃置了您的马：" << (*human)->defencer.name << endl;
					pd.push((*human)->horse);
					(*human)->horse = card();
					(*human)->numofhorse = 0;
					num--;
				}
				if (num == 0 or (*human)->handNUM == 0)
				{
					cout << "机器人寒冰剑效果结束" << endl;
					return;
				}
				else
				{
					num = (num <= (*human)->handNUM) ? num : (*human)->handNUM;
					cout << "机器人随机去掉您" << num << "张牌" << endl;
					for (int k = 0; k < num; k++)
					{
						srand = rand() % (*human)->handNUM;
						pd.push((*human)->player_lst[srand]);
						cout << "机器人弃掉的牌是：" << (*human)->player_lst[srand].name << endl;
						for (int i = srand; i < (*human)->handNUM - 1; i++)
						{
							(*human)->player_lst[i] = (*human)->player_lst[i + 1];
						}
						(*human)->handNUM -= 1;
					}
					cout << "寒冰剑效果结束" << endl;
					return;
				}

			}

		}
		else if (weapon.name == "贯石斧")
		{
			int HPbefore = (*human)->HPnow;
			card cc = rbt_lst[used];
			pd.push(rbt_lst[used]);
			card ss = rbt_lst[used];
			for (int i = used; i < handNUM - 1; i++)
			{
				rbt_lst[i] = rbt_lst[i + 1];
			}
			handNUM -= 1;
			kill = 1;
			(*human)->defence(1, cc.colorNUM);
			if ((*human)->HPnow == HPbefore)
			{
				if ((*human)->defencer.name == "仁王盾" and ss.huaseNUM == 1)
				{
					cout << "特殊伤害抵消，贯石斧无法发动" << endl;
					return;
				}
				else
				{
					if (handNUM < 2)
					{
						cout << "机器人手牌小于2，取消发动贯石斧！" << endl;
						return;
					}
					else
					{
						int a = rand() % handNUM; int func = rand() % handNUM;
						while (func == a)
						{
							func = rand() % handNUM;
						}
						if (func < a)
						{
							int c = a;
							a = func;
							func = a;
						}
						pd.push(rbt_lst[a]);
						pd.push(rbt_lst[func]);
						for (int i = a; i < handNUM - 1; i++)
						{
							rbt_lst[i] = rbt_lst[i + 1];
						}
						handNUM -= 1;
						for (int i = func - 1; i < handNUM - 1; i++)
						{
							rbt_lst[i] = rbt_lst[i + 1];
						}
						handNUM -= 1;
						(*human)->HPnow -= 1;
						cout << "机器人贯石斧发动成功！强制您扣一滴血！" << endl;
						return;
					}
				}
			}
		}
		else if (weapon.name == "青龙偃月刀")
		{
			int HPbefore = (*human)->HPnow;
			pd.push(rbt_lst[used]);
			card ss = rbt_lst[used];
			for (int i = used; i < handNUM - 1; i++)
			{
				rbt_lst[i] = rbt_lst[i + 1];
			}
			handNUM -= 1;
			kill = 1;
			(*human)->defence(1, ss.colorNUM);
			if ((*human)->HPnow == HPbefore)
			{
				if ((*human)->defencer.name == "仁王盾" and ss.huaseNUM == 1)
				{
					cout << "特殊伤害抵消，机器人的青龙偃月刀无法发动！" << endl;
					return;
				}
				int ppnum = 0; bool sure_use = false;
				for (ppnum; ppnum < handNUM; ppnum++)
				{
					if (rbt_lst[ppnum].name == "杀")
					{
						sure_use = true;
						break;
					}
				}
				while (sure_use and (*human)->HPnow == HPbefore)
				{
					pd.push(rbt_lst[ppnum]);
					card ss = rbt_lst[ppnum];
					for (int i = ppnum; i < handNUM - 1; i++)
					{
						rbt_lst[i] = rbt_lst[i + 1];
					}
					handNUM -= 1;
					cout << "机器人发动青龙偃月刀对您出杀！" << endl;
					(*human)->defence(1, ss.colorNUM);
					ppnum = 0; sure_use = false;
					for (ppnum; ppnum < handNUM; ppnum++)
					{
						if (rbt_lst[ppnum].name == "杀")
						{
							sure_use = true;
							break;
						}
					}
				}
				if ((*human)->HPnow == HPbefore)cout << "机器人无法继续出杀！" << endl;
				cout << "青龙偃月刀效果发挥完毕！" << endl;
			}
		}
		else if (weapon.name == "方天画戟")
		{
			cout << "由于模式限制，没有添加该武器的效果！" << endl;
			card cc = rbt_lst[used];
			pd.push(rbt_lst[used]);
			for (int i = used; i < handNUM - 1; i++)
			{
				rbt_lst[i] = rbt_lst[i + 1];
			}
			handNUM -= 1;
			kill = 1;
			(*human)->defence(1, cc.colorNUM);
		}
		else if (weapon.name == "麒麟弓")
		{
			int HPbefore = (*human)->HPnow;
			card cc = rbt_lst[used];
			pd.push(rbt_lst[used]);
			for (int i = used; i < handNUM - 1; i++)
			{
				rbt_lst[i] = rbt_lst[i + 1];
			}
			handNUM -= 1;
			kill = 1;
			(*human)->defence(1, cc.colorNUM);
			if ((*human)->HPnow < HPbefore and (*human)->numofhorse >0)
			{
				cout << "麒麟弓效果发动！机器人弃置您一张坐骑：" << (*human)->horse.name << endl;
				pd.push((*human)->horse);
				(*human)->numofhorse = 0;
			}
		}
	}
	else
	{
		if (weapon.name == "诸葛连弩")(*human)->defence(1, pd.back().colorNUM);
		else if (weapon.name == "青缸剑")(*human)->defence(0, pd.back().colorNUM);
		else if (weapon.name == "雌雄双股剑")
		{
			if ((*human)->name->sex != name->sex)
			{
				int choice = rand() % 2;
				if (choice == 0)
				{
					cout << "雌雄双股剑发动成功！让机器人摸一张牌！" << endl;
					rbt_lst[handNUM++] = pd.front();
					pd.pop();
					cout << "机器人摸到的牌是：" << rbt_lst[handNUM - 1].name << endl;
				}
				else
				{
					cout << "雌雄双股剑发动成功！机器人让您随机少一张牌！" << endl;
					int srand = rand() % (*human)->handNUM;
					pd.push((*human)->player_lst[srand]);
					cout << "机器人弃掉您的牌是：" << (*human)->player_lst[srand].name << endl;
					for (int i = srand; i < (*human)->handNUM - 1; i++)
					{
						(*human)->player_lst[i] = (*human)->player_lst[i + 1];
					}
					(*human)->handNUM -= 1;
				}
			}
			else
			{
				cout << "机器人的雌雄双股剑发动无效！" << endl;
			}
			(*human)->defence(1, pd.back().colorNUM);
		}
		else if (weapon.name == "寒冰剑")
		{
			int HPbefore = (*human)->HPnow;
			(*human)->defence(1, pd.back().colorNUM);
			if ((*human)->HPnow < HPbefore)
			{
				if ((*human)->numOfWeapon + (*human)->numOfDefencer + (*human)->numofhorse + (*human)->handNUM < 2)
				{
					cout << "检测到您的牌数小于两张，机器人放弃发动寒冰剑！" << endl;
					return;
				}
				cout << "寒冰剑发动成功!机器人最多弃置您两张牌（包含装备和马）" << endl;
				(*human)->HPnow += 1;
				int num = 2;
				int srand;
				if ((*human)->numOfWeapon != 0)
				{
					cout << "机器人弃置了您的武器：" << (*human)->weapon.name << endl;
					pd.push((*human)->weapon);
					(*human)->weapon = card();
					(*human)->numOfWeapon = 0;
					num--;
				}
				if ((*human)->numOfDefencer != 0)
				{
					cout << "机器人弃置了您的防具：" << (*human)->defencer.name << endl;
					pd.push((*human)->defencer);
					(*human)->defencer = card();
					(*human)->numOfDefencer = 0;
					num--;
				}
				if (num > 0 and (*human)->numofhorse > 0)
				{
					cout << "机器人弃置了您的马：" << (*human)->defencer.name << endl;
					pd.push((*human)->horse);
					(*human)->horse = card();
					(*human)->numofhorse = 0;
					num--;
				}
				if (num == 0 or (*human)->handNUM == 0)
				{
					cout << "机器人寒冰剑效果结束" << endl;
					return;
				}
				else
				{
					num = (num <= (*human)->handNUM) ? num : (*human)->handNUM;
					cout << "机器人随机去掉您" << num << "张牌" << endl;
					for (int k = 0; k < num; k++)
					{
						srand = rand() % (*human)->handNUM;
						pd.push((*human)->player_lst[srand]);
						cout << "机器人弃掉的牌是：" << (*human)->player_lst[srand].name << endl;
						for (int i = srand; i < (*human)->handNUM - 1; i++)
						{
							(*human)->player_lst[i] = (*human)->player_lst[i + 1];
						}
						(*human)->handNUM -= 1;
					}
					cout << "寒冰剑效果结束" << endl;
					return;
				}

			}

		}
		else if (weapon.name == "贯石斧")
		{
			int HPbefore = (*human)->HPnow;
			card cc = pd.back();
			(*human)->defence(1, cc.colorNUM);
			if ((*human)->HPnow == HPbefore)
			{
				if ((*human)->defencer.name == "仁王盾" and cc.colorNUM == 1)
				{
					cout << "特殊伤害抵消，贯石斧无法发动" << endl;
					return;
				}
				else
				{
					if (handNUM < 2)
					{
						cout << "机器人手牌小于2，取消发动贯石斧！" << endl;
						return;
					}
					else
					{
						int a = rand() % handNUM; int func = rand() % handNUM;
						while (func == a)
						{
							func = rand() % handNUM;
						}
						if (func < a)
						{
							int c = a;
							a = func;
							func = a;
						}
						pd.push(rbt_lst[a]);
						pd.push(rbt_lst[func]);
						for (int i = a; i < handNUM - 1; i++)
						{
							rbt_lst[i] = rbt_lst[i + 1];
						}
						handNUM -= 1;
						for (int i = func - 1; i < handNUM - 1; i++)
						{
							rbt_lst[i] = rbt_lst[i + 1];
						}
						handNUM -= 1;
						(*human)->HPnow -= 1;
						cout << "机器人贯石斧发动成功！强制您扣一滴血！" << endl;
						return;
					}
				}
			}
		}
		else if (weapon.name == "青龙偃月刀")
		{
			int HPbefore = (*human)->HPnow;
			card ss = pd.back();
			(*human)->defence(1, ss.colorNUM);
			if ((*human)->HPnow == HPbefore)
			{
				if ((*human)->defencer.name == "仁王盾" and ss.huaseNUM == 1)
				{
					cout << "特殊伤害抵消，机器人的青龙偃月刀无法发动！" << endl;
					return;
				}
				int ppnum = 0; bool sure_use = false;
				for (ppnum; ppnum < handNUM; ppnum++)
				{
					if (rbt_lst[ppnum].name == "杀")
					{
						sure_use = true;
						break;
					}
				}
				while (sure_use and (*human)->HPnow == HPbefore)
				{
					pd.push(rbt_lst[ppnum]);
					card ss = rbt_lst[ppnum];
					for (int i = ppnum; i < handNUM - 1; i++)
					{
						rbt_lst[i] = rbt_lst[i + 1];
					}
					handNUM -= 1;
					cout << "机器人发动青龙偃月刀对您出杀！" << endl;
					(*human)->defence(1, ss.colorNUM);
					ppnum = 0; sure_use = false;
					for (ppnum; ppnum < handNUM; ppnum++)
					{
						if (rbt_lst[ppnum].name == "杀")
						{
							sure_use = true;
							break;
						}
					}
				}
				if ((*human)->HPnow == HPbefore)cout << "机器人无法继续出杀！" << endl;
				cout << "青龙偃月刀效果发挥完毕！" << endl;
			}
		}
		else if (weapon.name == "方天画戟")
		{
			cout << "由于模式限制，没有添加该武器的效果！" << endl;
			card cc = pd.back();
			(*human)->defence(1, cc.colorNUM);
		}
		else if (weapon.name == "麒麟弓")
		{
			int HPbefore = (*human)->HPnow;
			card cc = pd.back();
			(*human)->defence(1, cc.colorNUM);
			if ((*human)->HPnow < HPbefore and (*human)->numofhorse >0)
			{
				cout << "麒麟弓效果发动！机器人弃置您一张坐骑：" << (*human)->horse.name << endl;
				pd.push((*human)->horse);
				(*human)->numofhorse = 0;
			}
		}
	}
}
void robot::delta(int x)
{
	int xx = x * 2;
	if (HPnow > 0)
	{
		cout << "机器人扣了" << x << "滴血, 发动郭嘉技能，摸" << xx << "张牌!" << endl;
		for (int i = 0; i < xx; i++)
		{
			rbt_lst[handNUM++] = pd.front();
			pd.pop();
		}
	}
	else
	{
		get_num_before_bs = x;
		check_bs();
	}
}
void robot::check_bs()
{
	int n = 0;
	//after:
	cout << "机器人进入濒死状态！" << endl;
	while (HPnow <= 0 and n<handNUM)
	{
		if (rbt_lst[n].name == "桃")
		{
			handNUM--;
			rbt_lst[n] = rbt_lst[handNUM];
			HPnow++;
		}
		else
		{
			n++;
		}
	}
	if (HPnow > 0 )
	{
		cout << "机器人成功复活！" << endl;
		if(name->id == 1)delta(get_num_before_bs);
		get_num_before_bs = 0;
	}
	else
	{
		cout << "机器人死亡！" << endl;
	}

}
