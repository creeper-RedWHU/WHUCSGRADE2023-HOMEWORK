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
player::player() {};
player::player(role a)
{
	name = &playerrole;
	HPnow = name->HP;
}
void player::init()
{
	for (int i = 0; i < 4; i++)
	{
		player_lst[i] = pd.front();
		pd.pop();
	}
	this->handNUM = 4;
	cout << "==========玩家抽牌完毕" << endl;
}
void player::finish()
{
	int discard = 0;
	while (HPnow < handNUM)
	{
		cout << "当前手牌数：" << handNUM << ',' << "当前血量：" << HPnow << endl;
		cout << "当前手牌：" << endl;
		cout << "序号/名字/功能/花色" << endl;
		for (int i = 0; i < handNUM; i++)
		{
			cout << i + 1 << '/' << player_lst[i].name << '/' << player_lst[i].explain << '/' << color_lst[player_lst[i].colorNUM] << '/' << huase_lst[player_lst[i].huaseNUM] << endl;
		}
		cout << "请弃" << handNUM - HPnow << "张牌" << endl;
		cout << "请输入去掉的牌的序号:";
		cin >> discard;
		if (discard >= 1 and discard <= handNUM)
		{
			pd.push(player_lst[discard - 1]);
			for (int i = discard - 1; i < this->handNUM - 1; i++)
			{
				player_lst[i] = player_lst[i + 1];
			}
			handNUM--;
		}
		else
		{
			cout << "请输入正确的手牌序号！" << endl;
		}
	}
	cout << "当前手牌数小于等于血量，无需弃牌" << endl;
	cout << "你的回合结束" << endl;
	lbsse = false;
	return;
}
bool player::jd_kill()
{
	
	for (int i = 0; i < handNUM; i++)
	{
		if (player_lst[i].name == "杀")
		{
			cout << "检测到您有杀，按0出杀，按1不出杀：";
			int a; cin >> a;
			if (a == 0)
			{
				cout << endl << "您成功出杀！" << endl;
				for (int j = i; j < handNUM - 1; j++)player_lst[j] = player_lst[j + 1];
				handNUM--;
				return true;
			}
			else
			{
				cout << "您不出杀！" << endl;
				return false;
			}
		}
	}
	if (weapon.name == "丈八蛇矛" and handNUM >= 2)
	{
		cout << "您的手牌：" << endl;
		cout << "序号/名字/功能/花色" << endl; int used = 0;
		for (int i = 0; i < handNUM; i++)
		{
			cout << i + 1 << '/' << player_lst[i].name << '/' << player_lst[i].explain << '/' << color_lst[player_lst[i].colorNUM] << '/' << huase_lst[player_lst[i].huaseNUM] << endl;
		}
		cout << "检测到您有装备丈八蛇矛，且手牌数大于等于2，是否使用？按0使用，1放弃:";
		int aaa; cin >> aaa;
		if (aaa == 0)
		{
			int fa, fb;
			cout << "输入丢弃手牌的编号（用空格隔开）："; cin >> fa >> fb;
			fa--; fb--;
			if (fa > fb) { int ffc = fa; fa = fb; fb = ffc; }
			pd.push(player_lst[fb]);pd.push(player_lst[fa]);
			for (int i = fb; i < handNUM - 1; i++)player_lst[i] = player_lst[i + 1]; handNUM--;
			for (int i = fa; i < handNUM - 1; i++)player_lst[i] = player_lst[i + 1]; handNUM--;
			cout << "丈八蛇矛发动成功！" << endl;
			return true;
		}
		else
		{
			cout << "您放弃使用丈八蛇矛！" << endl;
		}
	}
	cout << "您无法出杀！" << endl; return false;
}
bool player::judge()
{
	if (HPnow <= 0)  return false;
	else return true;
}
void player::annother()
{
	cout << "你的回合" << endl;
	kill = 0;
	//每回合开始前摸两张牌
	for (int i = 0; i < 2; i++)
	{
		player_lst[handNUM++] = pd.front();
		pd.pop();
	}
	if (lbssnum == 1)
	{
		cout << "接下来进入您的乐不思蜀判定时间" << endl;
		card ls = pd.front();
		pd.pop();
		pd.push(ls);
		if (ls.colorNUM == 0 and ls.huaseNUM == 2)
		{
			cout << "花色为红桃！您不用跳过出牌阶段！" << endl;
		}
		else
		{
			cout << "花色为" << color_lst[ls.colorNUM] << huase_lst[ls.huaseNUM] << "！您跳过出牌阶段！" << endl;
			lbsse = true;
		}
		lbssnum = 0;
	}

}
void player::weapon_kill(robot** enemy, int used)
{
	if(used !=-1)
	{ 
		if (weapon.name == "诸葛连弩")
		{
			card cc = player_lst[used];
			kill = 0;
			pd.push(player_lst[used]);
			for (int i = used; i < handNUM - 1; i++)
			{
				player_lst[i] = player_lst[i + 1];
			}
			handNUM -= 1;
			(*enemy)->defence(1, cc.colorNUM);
		}
		else if (weapon.name == "青缸剑")
		{
			card cc = player_lst[used];
			pd.push(player_lst[used]);
			for (int i = used; i < handNUM - 1; i++)
			{
				player_lst[i] = player_lst[i + 1];
			}
			handNUM -= 1;
			kill = 1;
			(*enemy)->defence(0, cc.colorNUM);
		}
		else if (weapon.name == "雌雄双股剑")
		{
			if ((*enemy)->name->sex != name->sex)
			{
				int choice = rand() % 2;
				if (choice == 0)
				{
					cout << "雌雄双股剑发动成功！让您摸一张牌！" << endl;
					player_lst[handNUM++] = pd.front();
					pd.pop();
					cout << "您摸到的牌是：" << player_lst[handNUM - 1].name << endl;
				}
				else
				{
					cout << "雌雄双股剑发动成功！让机器人随机少一张牌！" << endl;
					int srand = rand() % (*enemy)->handNUM;
					pd.push((*enemy)->rbt_lst[srand]);
					cout << "机器人弃掉的牌是：" << (*enemy)->rbt_lst[srand].name << endl;
					for (int i = srand; i < (*enemy)->handNUM - 1; i++)
					{
						(*enemy)->rbt_lst[i] = (*enemy)->rbt_lst[i + 1];
					}
					(*enemy)->handNUM -= 1;
				}
			}
			else
			{
				cout << "雌雄双股剑发动无效！" << endl;
			}
			card cc = player_lst[used];
			pd.push(player_lst[used]);
			for (int i = used; i < handNUM - 1; i++)
			{
				player_lst[i] = player_lst[i + 1];
			}
			handNUM -= 1;
			kill = 1;
			(*enemy)->defence(1, cc.colorNUM);
		}
		else if (weapon.name == "寒冰剑")
		{
			int HPbefore = (*enemy)->HPnow;
			card cc = player_lst[used];
			pd.push(player_lst[used]);
			for (int i = used; i < handNUM - 1; i++)
			{
				player_lst[i] = player_lst[i + 1];
			}
			handNUM -= 1;
			kill = 1;
			(*enemy)->defence(1, cc.colorNUM);
			if ((*enemy)->HPnow < HPbefore)
			{
				cout << "=====寒冰剑效果：" << weapon.explain << endl;
				cout << "=====是否发动寒冰剑效果？按1发动，按0取消（对方还有" << (*enemy)->numOfWeapon + (*enemy)->numOfDefencer + (*enemy)->numofhorse + (*enemy)->handNUM << "张牌)" << endl;
				int func; cin >> func;
				if (func == 0)return;
				else if (func == 1)
				{
					cout << "=====发动成功!最多弃置机器人两张牌（包含装备和马）" << endl;
					(*enemy)->HPnow += 1;
					int num = 2;
					int a; int srand;
					if ((*enemy)->numOfWeapon != 0)
					{
						cout << "=====当前机器人有装备武器" << (*enemy)->weapon.name << ",按0弃置，按1不弃置:";
						cin >> a;
						if (a == 0)
						{
							pd.push((*enemy)->weapon);
							(*enemy)->weapon = card();
							(*enemy)->numOfWeapon = 0;
							num--;
						}
					}
					if ((*enemy)->numOfDefencer != 0)
					{
						cout << "=====当前机器人有装备防具" << (*enemy)->defencer.name << ",按0弃置，按1不弃置:";
						cin >> a;
						if (a == 0)
						{
							pd.push((*enemy)->defencer);
							(*enemy)->defencer = card();
							(*enemy)->numOfDefencer = 0;
							num--;
						}
					}
					if (num > 0 and (*enemy)->numofhorse > 0)
					{
						cout << "=====当前机器人有装备马" << (*enemy)->horse.name << ",按0弃置，按1不弃置:";
						cin >> a;
						if (a == 0)
						{
							pd.push((*enemy)->horse);
							(*enemy)->horse = card();
							(*enemy)->numofhorse = 0;
							num--;
						}
					}
					if (num == 0 or (*enemy)->handNUM == 0)
					{
						cout << "寒冰剑效果结束" << endl;
						return;
					}
					else
					{
						num = (num <= (*enemy)->handNUM) ? num : (*enemy)->handNUM;
						cout << "随机去掉机器人" << num << "张牌" << endl;
						for (int k = 0; k < num; k++)
						{
							srand = rand() % (*enemy)->handNUM;
							pd.push((*enemy)->rbt_lst[srand]);
							cout << "机器人弃掉的牌是：" << (*enemy)->rbt_lst[srand].name << endl;
							for (int i = srand; i < (*enemy)->handNUM - 1; i++)
							{
								(*enemy)->rbt_lst[i] = (*enemy)->rbt_lst[i + 1];
							}
							(*enemy)->handNUM -= 1;
						}
						cout << "寒冰剑效果结束" << endl;
					}
				}
			}

		}
		else if (weapon.name == "贯石斧")
		{
			int HPbefore = (*enemy)->HPnow;
			card cc = player_lst[used];
			pd.push(player_lst[used]);
			card ss = player_lst[used];
			for (int i = used; i < handNUM - 1; i++)
			{
				player_lst[i] = player_lst[i + 1];
			}
			handNUM -= 1;
			kill = 1;
			(*enemy)->defence(1, cc.colorNUM);
			if ((*enemy)->HPnow == HPbefore)
			{
				if ((*enemy)->defencer.name == "仁王盾" and ss.colorNUM == 1)
				{
					cout << "特殊伤害抵消，贯石斧无法发动" << endl;
					return;
				}
				else
				{
					cout << "是否发动贯石斧？(需手牌数大于2)按0发动，1取消：";
					int func; cin >> func;
					if (func == 1 or handNUM < 2)
					{
						cout << "您取消发动贯石斧！(或手牌小于2)" << endl;
						return;
					}
					else
					{
						cout << "当前手牌：" << endl;
						cout << "序号/名字/功能/花色" << endl;
						for (int i = 0; i < handNUM; i++)
						{
							cout << i + 1 << '/' << player_lst[i].name << '/' << player_lst[i].explain << '/' << color_lst[player_lst[i].colorNUM] << '/' << huase_lst[player_lst[i].huaseNUM] << endl;
						}
						cout << endl << "贯石斧发动成功！请输入你要丢弃的牌的序号：";
						int a; cin >> a >> func;
						if (func < a)
						{
							int c = a;
							a = func;
							func = a;
						}
						pd.push(player_lst[a - 1]);
						pd.push(player_lst[func - 1]);
						for (int i = a - 1; i < handNUM - 1; i++)
						{
							player_lst[i] = player_lst[i + 1];
						}
						handNUM -= 1;
						for (int i = func; i < handNUM - 1; i++)
						{
							player_lst[i] = player_lst[i + 1];
						}
						handNUM -= 1;
						(*enemy)->HPnow -= 1;
						cout << endl << "贯石斧发动成功！";
						return;
					}
				}
			}
		}
		else if (weapon.name == "青龙偃月刀")
		{
			int HPbefore = (*enemy)->HPnow;
			pd.push(player_lst[used]);
			card ss = player_lst[used];
			for (int i = used; i < handNUM - 1; i++)
			{
				player_lst[i] = player_lst[i + 1];
			}
			handNUM -= 1;
			kill = 1;
			(*enemy)->defence(1, ss.colorNUM);
			int func = 0; int pm = 0;
			if ((*enemy)->HPnow == HPbefore)
			{
				if ((*enemy)->defencer.name == "仁王盾" and pd.back().colorNUM == 1)
				{
					cout << "特殊伤害抵消，青龙偃月刀无法发动！" << endl;
					return;
				}
				cout << "敌人使用了闪，是否发动青龙偃月刀效果继续出杀？按0继续，按1退出:";
				cin >> func;
				while (func == 0 and (*enemy)->HPnow == HPbefore)
				{
					cout << "当前手牌：" << endl;
					cout << "序号/名字/功能/花色" << endl;
					for (int i = 0; i < handNUM; i++)
					{
						cout << i + 1 << '/' << player_lst[i].name << '/' << player_lst[i].explain << '/' << color_lst[player_lst[i].colorNUM] << '/' << huase_lst[player_lst[i].huaseNUM] << endl;
					}
					cout << "输入杀的手牌的编号：";
					cin >> pm;
					if (player_lst[pm - 1].name == "杀")
					{
						pd.push(player_lst[pm - 1]);
						card ss = player_lst[pm - 1];
						for (int i = pm - 1; i < handNUM - 1; i++)
						{
							player_lst[i] = player_lst[i + 1];
						}
						handNUM -= 1;
						(*enemy)->defence(1, ss.colorNUM);
					}
					else
					{
						cout << "请输入杀的手牌的编号！" << endl;
					}
					cout << "敌人使用了闪，是否发动青龙偃月刀效果继续出杀？按0继续，按1退出:";
					cin >> func;

				}
				cout << "青龙偃月刀效果发挥完毕！" << endl;
			}
		}
		else if (weapon.name == "方天画戟")
		{
			cout << "由于模式限制，没有添加该武器的效果！" << endl;
			card cc = player_lst[used];
			pd.push(player_lst[used]);
			for (int i = used; i < handNUM - 1; i++)
			{
				player_lst[i] = player_lst[i + 1];
			}
			handNUM -= 1;
			kill = 1;
			(*enemy)->defence(1, cc.colorNUM);
		}
		else if (weapon.name == "麒麟弓")
		{
			int HPbefore = (*enemy)->HPnow;
			card cc = player_lst[used];
			pd.push(player_lst[used]);
			for (int i = used; i < handNUM - 1; i++)
			{
				player_lst[i] = player_lst[i + 1];
			}
			handNUM -= 1;
			kill = 1;
			(*enemy)->defence(1, cc.colorNUM);
			if ((*enemy)->HPnow < HPbefore and (*enemy)->numofhorse >0)
			{
				cout << "麒麟弓效果发动！弃置对面一张坐骑：" << (*enemy)->horse.name << endl;
				pd.push((*enemy)->horse);
				(*enemy)->numofhorse = 0;
			}
		}
	}
	else
	{
		if (weapon.name == "诸葛连弩")(*enemy)->defence(1,pd.back().colorNUM);
		else if (weapon.name == "青缸剑")(*enemy)->defence(0, 0);
		else if (weapon.name == "雌雄双股剑")
		{
			if ((*enemy)->name->sex != name->sex)
			{
				int choice = rand() % 2;
				if (choice == 0)
				{
					cout << "雌雄双股剑发动成功！让您摸一张牌！" << endl;
					player_lst[handNUM++] = pd.front();
					pd.pop();
					cout << "您摸到的牌是：" << player_lst[handNUM - 1].name << endl;
				}
				else
				{
					cout << "雌雄双股剑发动成功！让机器人随机少一张牌！" << endl;
					int srand = rand() % (*enemy)->handNUM;
					pd.push((*enemy)->rbt_lst[srand]);
					cout << "机器人弃掉的牌是：" << (*enemy)->rbt_lst[srand].name << endl;
					for (int i = srand; i < (*enemy)->handNUM - 1; i++)
					{
						(*enemy)->rbt_lst[i] = (*enemy)->rbt_lst[i + 1];
					}
					(*enemy)->handNUM -= 1;
				}
			}
			else
			{
				cout << "雌雄双股剑发动无效！" << endl;
			}
			(*enemy)->defence(1, pd.back().colorNUM);
		}
		else if (weapon.name == "寒冰剑")
		{
			int HPbefore = (*enemy)->HPnow;
			(*enemy)->defence(1, pd.back().colorNUM);
			if ((*enemy)->HPnow < HPbefore)
			{
				cout << "=====寒冰剑效果：" << weapon.explain << endl;
				cout << "=====是否发动寒冰剑效果？按1发动，按0取消（对方还有" << (*enemy)->numOfWeapon + (*enemy)->numOfDefencer + (*enemy)->numofhorse + (*enemy)->handNUM << "张牌)" << endl;
				int func; cin >> func;
				if (func == 0)return;
				else if (func == 1)
				{
					cout << "=====发动成功!最多弃置机器人两张牌（包含装备和马）" << endl;
					(*enemy)->HPnow += 1;
					int num = 2;
					int a; int srand;
					if ((*enemy)->numOfWeapon != 0)
					{
						cout << "=====当前机器人有装备武器" << (*enemy)->weapon.name << ",按0弃置，按1不弃置:";
						cin >> a;
						if (a == 0)
						{
							pd.push((*enemy)->weapon);
							(*enemy)->weapon = card();
							(*enemy)->numOfWeapon = 0;
							num--;
						}
					}
					if ((*enemy)->numOfDefencer != 0)
					{
						cout << "=====当前机器人有装备防具" << (*enemy)->defencer.name << ",按0弃置，按1不弃置:";
						cin >> a;
						if (a == 0)
						{
							pd.push((*enemy)->defencer);
							(*enemy)->defencer = card();
							(*enemy)->numOfDefencer = 0;
							num--;
						}
					}
					if (num > 0 and (*enemy)->numofhorse > 0)
					{
						cout << "=====当前机器人有装备马" << (*enemy)->horse.name << ",按0弃置，按1不弃置:";
						cin >> a;
						if (a == 0)
						{
							pd.push((*enemy)->horse);
							(*enemy)->horse = card();
							(*enemy)->numofhorse = 0;
							num--;
						}
					}
					if (num == 0 or (*enemy)->handNUM == 0)
					{
						cout << "寒冰剑效果结束" << endl;
						return;
					}
					else
					{
						num = (num <= (*enemy)->handNUM) ? num : (*enemy)->handNUM;
						cout << "随机去掉机器人" << num << "张牌" << endl;
						for (int k = 0; k < num; k++)
						{
							srand = rand() % (*enemy)->handNUM;
							pd.push((*enemy)->rbt_lst[srand]);
							cout << "机器人弃掉的牌是：" << (*enemy)->rbt_lst[srand].name << endl;
							for (int i = srand; i < (*enemy)->handNUM - 1; i++)
							{
								(*enemy)->rbt_lst[i] = (*enemy)->rbt_lst[i + 1];
							}
							(*enemy)->handNUM -= 1;
						}
						cout << "寒冰剑效果结束" << endl;
					}
				}
			}
		}
		else if (weapon.name == "贯石斧")
		{
			int HPbefore = (*enemy)->HPnow;
			(*enemy)->defence(1, pd.back().colorNUM);
			if ((*enemy)->HPnow == HPbefore)
			{
				if ((*enemy)->defencer.name == "仁王盾" and pd.back().colorNUM== 1)
				{
					cout << "特殊伤害抵消，贯石斧无法发动" << endl;
					return;
				}
				else
				{
					cout << "是否发动贯石斧？(需手牌数大于2)按0发动，1取消：";
					int func; cin >> func;
					if (func == 1 or handNUM < 2)
					{
						cout << "您取消发动贯石斧！(或手牌小于2)" << endl;
						return;
					}
					else
					{
						cout << "当前手牌：" << endl;
						cout << "序号/名字/功能/花色" << endl;
						for (int i = 0; i < handNUM; i++)
						{
							cout << i + 1 << '/' << player_lst[i].name << '/' << player_lst[i].explain << '/' << color_lst[player_lst[i].colorNUM] << '/' << huase_lst[player_lst[i].huaseNUM] << endl;
						}
						cout << endl << "贯石斧发动成功！请输入你要丢弃的牌的序号：";
						int a; cin >> a >> func;
						if (func < a)
						{
							int c = a;
							a = func;
							func = a;
						}
						pd.push(player_lst[a - 1]);
						pd.push(player_lst[func - 1]);
						for (int i = a - 1; i < handNUM - 1; i++)
						{
							player_lst[i] = player_lst[i + 1];
						}
						handNUM -= 1;
						for (int i = func; i < handNUM - 1; i++)
						{
							player_lst[i] = player_lst[i + 1];
						}
						handNUM -= 1;
						(*enemy)->HPnow -= 1;
						cout << endl << "贯石斧发动成功！";
						return;
					}
				}
			}
		}
		else if (weapon.name == "青龙偃月刀")
		{
			int HPbefore = (*enemy)->HPnow;
			(*enemy)->defence(1, pd.back().colorNUM);
			int func = 0; int pm = 0;
			if ((*enemy)->HPnow == HPbefore)
			{
				if ((*enemy)->defencer.name == "仁王盾" and pd.back().colorNUM == 1)
				{
					cout << "特殊伤害抵消，青龙偃月刀无法发动！" << endl;
					return;
				}
				cout << "敌人使用了闪，是否发动青龙偃月刀效果继续出杀？按0继续，按1退出:";
				cin >> func;
				while (func == 0 and (*enemy)->HPnow == HPbefore)
				{
					cout << "当前手牌：" << endl;
					cout << "序号/名字/功能/花色" << endl;
					for (int i = 0; i < handNUM; i++)
					{
						cout << i + 1 << '/' << player_lst[i].name << '/' << player_lst[i].explain << '/' << color_lst[player_lst[i].colorNUM] << '/' << huase_lst[player_lst[i].huaseNUM] << endl;
					}
					cout << "输入杀的手牌的编号：";
					cin >> pm;
					if (player_lst[pm - 1].name == "杀")
					{
						pd.push(player_lst[pm - 1]);
						card ss = player_lst[pm - 1];
						for (int i = pm - 1; i < handNUM - 1; i++)
						{
							player_lst[i] = player_lst[i + 1];
						}
						handNUM -= 1;
						(*enemy)->defence(1, ss.colorNUM);
					}
					else
					{
						cout << "请输入杀的手牌的编号！" << endl;
					}
					cout << "敌人使用了闪，是否发动青龙偃月刀效果继续出杀？按0继续，按1退出:";
					cin >> func;

				}
				cout << "青龙偃月刀效果发挥完毕！" << endl;
			}
		}
		else if (weapon.name == "方天画戟")
		{
			cout << "由于模式限制，没有添加该武器的效果！" << endl;
			(*enemy)->defence(1, pd.back().colorNUM);
		}
		else if (weapon.name == "麒麟弓")
		{
			int HPbefore = (*enemy)->HPnow;
			(*enemy)->defence(1, pd.back().colorNUM);
			if ((*enemy)->HPnow < HPbefore and (*enemy)->numofhorse >0)
			{
				cout << "麒麟弓效果发动！弃置对面一张坐骑：" << (*enemy)->horse.name << endl;
				pd.push((*enemy)->horse);
				(*enemy)->numofhorse = 0;
			}
		}
	}
}
void player::defence(int n, int colornum)
{
	if (n == 0 or numOfDefencer == 0);
	else
	{
		if (defencer.name == "八卦阵")
		{
			cout << "您发动防具：八卦阵" << endl;
			card cc = pd.front();
			pd.pop();
			pd.push(cc);
			if (cc.colorNUM == 0)
			{
				cout << "八卦阵生效，该牌为：" << color_lst[cc.colorNUM] << huase_lst[cc.huaseNUM] << ",您视为出了一张闪" << endl;
				return;
			}
			else
			{
				cout << "八卦阵没生效，该牌为：" << color_lst[cc.colorNUM] << huase_lst[cc.huaseNUM] << endl;
			}
		}
		else if (defencer.name == "仁王盾")
		{
			cout << "您发动仁王盾！" << endl;
			if (colornum == 1)
			{
				cout << "由于仁王盾的效果，黑色杀无效！" << endl;
				return;
			}
			else
			{
				cout << "仁王盾对红色杀无效！" << endl;
			}
		}
	}
	cout << "您需要出闪！" << endl;
	cout << "当前手牌：" << endl;
	cout << "序号/名字/功能/花色" << endl;
	for (int i = 0; i < handNUM; i++)
	{
		cout << i + 1 << '/' << player_lst[i].name << '/' << player_lst[i].explain << '/' << color_lst[player_lst[i].colorNUM] << '/' << huase_lst[player_lst[i].huaseNUM] << endl;
	}
	cout << "按0出闪，按1不出闪（如果没有闪按0也无效果）：" << endl;
	int a; cin >> a;
	if (a == 1)
	{
		cout << "您没有闪，扣一滴血！" << endl;
		HPnow -= 1;
		if (name->id == 1)delta(1);
		return;
	}
	else
	{
		int i = 0;
		for (i; i < handNUM; i++)if (player_lst[i].name == "闪")break;
		if (i == handNUM)
		{
			cout << "您没有闪！扣一滴血" << endl;
			HPnow -= 1;
			if (name->id == 1)delta(1);
			return;
		}
		else
		{
			cout << "您出了闪！" << endl;
			for (i; i < handNUM - 1; i++)
			{
				player_lst[i] = player_lst[i + 1];
			}
			handNUM--;
			return;
		}
	}
}
bool player::is_wxkj_used()
{
	for (int i = 0; i < handNUM; i++)
	{
		if (player_lst[i].name == "无懈可击")
		{
			cout << "检测到您有无懈可击，是否使用？按1使用，0取消:";
			int a; cin >> a;
			if (a == 1)
			{
				cout << "使用无懈可击成功，机器人的锦囊牌失效！" << endl;
				pd.push(player_lst[i]);
				for (int j = i; j < handNUM - 1; j++)player_lst[j] = player_lst[j + 1];
				handNUM--;
				if (name->id == 2)
				{
					cout << "您发动黄月英的技能！摸一张牌:" << pd.front().name << endl;
					player_lst[handNUM++] = pd.front();
					pd.pop();
				}
				return true;
			}
			else
			{
				cout << "您取消使用无懈可击！" << endl;
				return false;
			}
		}
	}
	return false;
}
void player::delta(int x)
{
	int xx = x * 2;
	if (HPnow > 0)
	{
		cout << "您扣了" << x << "滴血, 发动郭嘉技能，摸" << xx << "张牌!" << endl;
		for (int i = 0; i < xx; i++)
		{
			player_lst[handNUM++] = pd.front();
			pd.pop();
		}
	}
	else
	{
		get_num_before_bs = x;
		check_bs();
	}
}
void player::check_bs()
{
	int n = 0;
	cout << "您进入濒死状态！正在自动使用剩余的桃手牌" << endl;
	while (HPnow <= 0 and n < handNUM)
	{
		if (player_lst[n].name == "桃")
		{
			handNUM--;
			player_lst[n] = player_lst[handNUM];
			HPnow++;
		}
		else
		{
			n++;
		}
	}
	if (HPnow > 0)
	{
		cout << "您成功复活！" << endl;
		if (name->id == 1)delta(get_num_before_bs);
		get_num_before_bs = 0;
	}
	else
	{
		cout << "您死亡！" << endl;
	}
}
