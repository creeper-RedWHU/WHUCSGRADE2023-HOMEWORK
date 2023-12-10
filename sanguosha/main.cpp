//可以改进：部分数据设置成private类型，然后利用友元函数处理，更加安全
#include<string>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
//武器列表
string weapon_lst[] = { "诸葛连弩","青缸剑","雌雄双股剑","寒冰剑","贯石斧","青龙偃月刀","丈八蛇矛","方天画戟","麒麟弓" };
string defencer_lst[] = { "八卦阵","仁王盾" };
string horse_lst[] = { "+1马","-1马" };
//锦囊牌列表，记得去掉借刀杀人
string skill_lst[] = { "过河拆桥","顺手牵羊","无中生有","南蛮入侵","决斗","乐不思蜀","无懈可击","闪电","五谷丰登","借刀杀人","万箭齐发","桃园结义" };
//手牌相关部分
string huase_lst[] = { "梅花","方块","桃" };
string color_lst[] = { "红","黑" };
//角色部分
//基本角色类型role
class role;
#include"role.h"
//所有角色数组，role类型
//角色技能都写在role类中，当玩家/机器人选择后且满足触发条件后自动释放
role role_lst[2] = { role(1,"郭嘉","当你受到1点伤害后，你可以观看牌堆顶的两张牌，然后将这些牌交给任意角色。",3,1),role(2,"黄月英","当黄月英使用非转化的普通锦囊牌时，可以摸一张牌。",3,0)};
role playerrole; role robotrole; 
//卡片相关
class card;
#include"card.h"
int role_num = 2;
//机器人卡牌的种子
int choice =rand()%2;
card card_lst[107];
queue<card>pd;

//card_lst初始化
void card_lst_init()
{
	/*手牌：0-106*/
	int i = 0;
	//初始化杀
	for (i; i < 7; i++)
	{
		card_lst[i] = card("杀", 2, 1, "使用后对方需出闪，否则扣一滴血，无特殊情况一回合只能出一次");
	}
	for (i; i < 21; i++)
	{
		card_lst[i] = card("杀", 0, 1, "使用后对方需出闪，否则扣一滴血，无特殊情况一回合只能出一次");
	}
	for (i; i < 24; i++)
	{
		card_lst[i] = card("杀", 2, 0, "使用后对方需出闪，否则扣一滴血，无特殊情况一回合只能出一次");
	}
	for (i; i < 30; i++)
	{
		card_lst[i] = card("杀", 1, 0, "使用后对方需出闪，否则扣一滴血，无特殊情况一回合只能出一次");
	}
	//初始化闪
	for (i; i < 33; i++)
	{
		card_lst[i] = card("闪", 2, 0, "对方使用杀时可以闪避");
	}
	for (i; i < 45; i++)
	{
		card_lst[i] = card("闪", 1, 0, "对方使用杀时可以闪避");
	}
	//初始化桃
	for (i; i < 52; i++)
	{
		card_lst[i] = card("桃", 2, 0, "打出此牌可以回复一滴血量，满血无法使用");
	}
	for (i; i < 53; i++)
	{
		card_lst[i] = card("桃", 1, 0, "打出此牌可以回复一滴血量，满血无法使用");
	}
	//初始化锦囊牌
	for (i; i < 56; i++)
	{
		card_lst[i] = card("过河拆桥", 2, 1, "弃掉对方一张牌（未知，自选）");
	}
	for (i; i < 57; i++)
	{
		card_lst[i] = card("过河拆桥", 0, 1, "弃掉对方一张牌（未知，自选）");
	}
	for (i; i < 58; i++)
	{
		card_lst[i] = card("过河拆桥", 2, 0, "弃掉对方一张牌（未知，自选）");
	}
	for (i; i < 61; i++)
	{
		card_lst[i] = card("顺手牵羊", 2, 1, "获得对方一张牌（未知，自选）");
	}
	for (i; i < 63; i++)
	{
		card_lst[i] = card("顺手牵羊", 1, 0, "获得对方一张牌（未知，自选）");
	}
	for (i; i < 67; i++)
	{
		card_lst[i] = card("无中生有", 2, 0, "获得牌堆顶部两张牌");
	}
	for (i; i < 69; i++)
	{
		card_lst[i] = card("南蛮入侵", 2, 1, "除非打出一张【杀】，否则该角色受到【南蛮入侵】对其造成的1点伤害");
	}
	for (i; i < 70; i++)
	{
		card_lst[i] = card("南蛮入侵", 0, 1, "除非打出一张【杀】，否则该角色受到【南蛮入侵】对其造成的1点伤害");
	}
	for (i; i < 71; i++)
	{
		card_lst[i] = card("决斗", 2, 1, "由目标角色开始，其与你轮流打出【杀】，直到其中的一名角色未打出【杀】。 然后未打出【杀】的角色受到另一名角色造成的1点伤害。");
	}
	for (i; i < 72; i++)
	{
		card_lst[i] = card("决斗", 1, 1, "由目标角色开始，其与你轮流打出【杀】，直到其中的一名角色未打出【杀】。 然后未打出【杀】的角色受到另一名角色造成的1点伤害。");
	}
	for (i; i < 73; i++)
	{
		card_lst[i] = card("决斗", 0, 1, "由目标角色开始，其与你轮流打出【杀】，直到其中的一名角色未打出【杀】。 然后未打出【杀】的角色受到另一名角色造成的1点伤害。");
	}
	for (i; i < 74; i++)
	{
		card_lst[i] = card("乐不思蜀", 0, 1, "出牌阶段，对一名其他角色使用。 将【乐不思蜀】放置于该角色的判定区里，若判定结果不为红桃，则跳过其出牌阶段。");
	}
	for (i; i < 75; i++)
	{
		card_lst[i] = card("乐不思蜀", 2, 1, "出牌阶段，对一名其他角色使用。 将【乐不思蜀】放置于该角色的判定区里，若判定结果不为红桃，则跳过其出牌阶段。");
	}
	for (i; i < 76; i++)
	{
		card_lst[i] = card("乐不思蜀", 2, 0, "出牌阶段，对一名其他角色使用。 将【乐不思蜀】放置于该角色的判定区里，若判定结果不为红桃，则跳过其出牌阶段。");
	}
	for (i; i < 77; i++)
	{
		card_lst[i] = card("无懈可击", 1, 0, "抵消该锦囊对其指定的一名目标角色产生的效果。");
	}
	for (i; i < 78; i++)
	{
		card_lst[i] = card("无懈可击", 2, 1, "抵消该锦囊对其指定的一名目标角色产生的效果。");
	}
	for (i; i < 80; i++)
	{
		card_lst[i] = card("无懈可击", 0, 1, "抵消该锦囊对其指定的一名目标角色产生的效果。");
	}
	for (i; i < 81; i++)
	{
		card_lst[i] = card("闪电", 2, 1, "将闪电横置于当前回合角色判定区里。角色上方有闪电则在回合的判定阶段，进行判定；若判定结果为黑桃，则目标角色受到无来源的3点雷属性伤害，将闪电弃置。否则，将闪电移动到当前目标角色下家（闪电的目标变为该角色）的判定区。");
	}
	for (i; i < 82; i++)
	{
		card_lst[i] = card("闪电", 2, 0, "将闪电横置于当前回合角色判定区里。角色上方有闪电则在回合的判定阶段，进行判定；若判定结果为黑桃，则目标角色受到无来源的3点雷属性伤害，将闪电弃置。否则，将闪电移动到当前目标角色下家（闪电的目标变为该角色）的判定区。");
	}
	for (i; i < 84; i++)
	{
		card_lst[i] = card("五谷丰登", 2, 0, "出牌阶段，对所有角色使用。 你从牌堆亮出等同于现存角色数量的牌，每名目标角色选择并获得其中的一张。");
	}
	for (i; i < 86; i++)//dele，黑梅花
	{
		card_lst[i] = card("借刀杀人", 0, 1, "出牌阶段，对装备区里有武器牌的一名其他角色使用。该角色需对其攻击范围内，由你指定的另一名角色使用一张【杀】，否则将装备区里的武器牌交给你。");
	}
	for (i; i < 87; i++)
	{
		card_lst[i] = card("万箭齐发", 2, 0, "除非目标角色打出一张【闪】，否则该角色受到【万箭齐发】对其造成的1点伤害。");
	}
	for (i; i < 88; i++)
	{
		card_lst[i] = card("桃园结义", 2, 0, "出牌阶段，对所有角色使用。 每名目标角色回复1点体力。");
	}
	//初始化装备牌，抛弃距离值，有武器就可以抵挡-1马
	card_lst[i++] = card("八卦阵", 2, 1, "每当你需要使用 (或打出)一张【闪】时，你可以进行一次判定，若判定结果为红色，则视为你使用 (或打出)了一张【闪】;若为黑色，则你仍可以从手牌里使用 (或打出)。");
	card_lst[i++] = card("八卦阵", 0, 1, "每当你需要使用 (或打出)一张【闪】时，你可以进行一次判定，若判定结果为红色，则视为你使用 (或打出)了一张【闪】;若为黑色，则你仍可以从手牌里使用 (或打出)。");
	card_lst[i++] = card("仁王盾", 0, 1, "锁定技，黑色的【杀】对你无效。");
	card_lst[i++] = card("+1马", 0, 1, "攻击时你可以攻击距离+1");
	card_lst[i++] = card("+1马", 2, 1, "攻击时你可以攻击距离+1");
	card_lst[i++] = card("+1马", 2, 0, "攻击时你可以攻击距离+1");
	card_lst[i++] = card("-1马", 2, 0, "对手攻击时对手可以攻击距离-1");
	card_lst[i++] = card("-1马", 2, 1, "对手攻击时对手可以攻击距离-1");
	card_lst[i++] = card("-1马", 1, 0, "对手攻击时对手可以攻击距离-1");
	card_lst[i++] = card("诸葛连弩", 1, 0, "锁定技，你使用【杀】无次数限制。");
	card_lst[i++] = card("诸葛连弩", 0, 1, "锁定技，你使用【杀】无次数限制。");
	card_lst[i++] = card("青缸剑", 2, 1, "锁定技，当你使用【杀】指定一个目标后，你令其防具无效。");
	card_lst[i++] = card("雌雄双股剑", 2, 1, "你使用〔杀〕，指定了一名异性角色为目标后，在〔杀〕结算前，你可以令对方选择一项：自己弃一张手牌或者让你从牌堆摸一张牌。");
	card_lst[i++] = card("寒冰剑", 2, 1, "当你使用【杀】对目标角色造成伤害时，若该角色有牌，你可以防止此伤害，改为依次弃置其两张牌。");
	card_lst[i++] = card("贯石斧", 1, 0, "当你使用的【杀】被抵消时，你可以弃置两张牌，则此【杀】依然造成伤害。");
	card_lst[i++] = card("青龙偃月刀", 2, 1, "当你使用的【杀】被目标角色使用的【闪】抵消时，你可以对其使用【杀】（无距离限制）。");
	card_lst[i++] = card("丈八蛇矛", 2, 1, "你可以将两张手牌当【杀】使用或打出。");
	card_lst[i++] = card("方天画戟", 1, 0, "锁定技，若你使用的【杀】是你最后的手牌，则此【杀】可以多选择两个目标。");
	card_lst[i++] = card("麒麟弓", 2, 0, "当你使用【杀】对目标角色造成伤害时，你可以弃置其装备区里的一张坐骑牌。");
	cout << "手牌初始化完成！" << endl;
}
//pd初始化
void pd_init()
{
	//赋给队列
	srand(unsigned(time(0)));
	random_shuffle(card_lst, card_lst + 106);
	random_shuffle(card_lst, card_lst + 106);
	random_shuffle(card_lst, card_lst + 106);
	random_shuffle(card_lst, card_lst + 106);
	for (int i = 0; i < 105; i++)pd.push(card_lst[i]);
	return;
}
//判断是否退出
bool checknum(int um)
{
	if (um == 0)return true;
	else return false;
}
class player; class robot;
#include"player_robot.h"
robot rbt; player humani, human;
void player::play(robot* enemy)
{
	int func = 0; int zbsm_use = 0;
	cout << "=====请选择你的操作：" << endl;
	cout << "=====输入0重复当前说明：" << endl;
	cout << "=====输入1查看武将技能和当前我方武将及敌方武将血量" << endl;
	cout << "=====输入2查看当前我方和敌方装备区物品(一个人最多装备一件防具，一把武器和一匹马)" << endl;
	cout << "=====输入3显示自己的手牌，并开始使用手牌" << endl;
	cout << "=====输入4结束回合进入弃牌阶段" << endl;
	while (func != 4)
	{
		cin >> func;
		if (func == 0)
		{
			cout << "=====请选择你的操作：" << endl;
			cout << "=====输入0重复当前说明：" << endl;
			cout << "=====输入1查看武将技能和当前我方武将及敌方武将血量" << endl;
			cout << "=====输入2查看当前我方和敌方装备区物品" << endl;
			cout << "=====输入3显示自己的手牌，并开始使用手牌" << endl;
			cout << "=====输入4结束回合进入弃牌阶段" << endl;
		}
		else if (func == 1)
		{
			cout << "我方武将：" << name->name << endl;
			cout << "我方武将技能：" << name->skill << endl;
			cout << "我方武将血量：" << HPnow << '/' << name->HP << endl;
			cout << "敌方武将：" << enemy->name->name << endl;
			cout << "敌方武将技能：" << enemy->name->skill << endl;
			cout << "敌方武将血量：" << enemy->HPnow << '/' << enemy->name->HP << endl;
		}
		else if (func == 2)
		{
			cout << "我方装备有" << numOfWeapon << "把武器";
			if (numOfWeapon == 0)cout << '.' << endl;
			else
			{
				cout << ":" << weapon.name << endl;
			}
			cout << "我方装备有" << numOfDefencer << "副防具";
			if (numOfDefencer == 0)cout << '.' << endl;
			else
			{
				cout << ":" << defencer.name << endl;
			}
			cout << "我方装备有" << numofhorse << "匹马";
			if (numofhorse == 0)cout << '.' << endl;
			else
			{
				cout << ":" << horse.name << endl;
			}
			cout << "敌方装备有" << enemy->numOfWeapon << "把武器";
			if (enemy->numOfWeapon == 0)cout << '.' << endl;
			else
			{
				cout << ":" << enemy->weapon.name << endl;
			}
			cout << "敌方装备有" << enemy->numOfDefencer << "副防具";
			if (enemy->numOfDefencer == 0)cout << '.' << endl;
			else
			{
				cout << ":" << enemy->defencer.name << endl;
			}
			cout << "敌方装备有" << enemy->numofhorse << "匹马";
			if (enemy->numofhorse == 0)cout << '.' << endl;
			else
			{
				cout << ":" << enemy->horse.name << endl;
			}
		}
		else if (func == 3)
		{
			//1.展示自己的手牌
			cout << "序号/名字/功能/花色" << endl; int used = 0;
			for (int i = 0; i < handNUM; i++)
			{
				cout << i + 1 << '/' << player_lst[i].name << '/' << player_lst[i].explain << '/' << color_lst[player_lst[i].colorNUM] << '/' << huase_lst[player_lst[i].huaseNUM] << endl;
			}
			//特判：如果装备了丈八蛇矛而且可以发动，那么询问
			if (weapon.name == "丈八蛇矛" and kill == 0 and handNUM >= 2 and zbsm_use == 0)
			{
				int f = 0;
				cout << "丈八蛇矛效果：" << weapon.explain << endl;;
				cout << "检测到您装备了丈八蛇矛，输入0使用，输入1不使用："; cin >> f;
				if (f == 0)
				{
					cout << "丈八蛇矛发动成功!" << endl;
					cout << "当前手牌：" << endl;
					cout << "序号/名字/功能" << endl;
					for (int i = 0; i < handNUM; i++)
					{
						cout << i + 1 << '/' << player_lst[i].name << '/' << player_lst[i].explain << endl;
					}
					cout << "请输入弃置牌的编号："; int a; cin >> f >> a;
					pd.push(player_lst[a - 1]);
					pd.push(player_lst[f - 1]);
					f -= 1; a -= 1;
					//防止修改牌的时候出错，先修改小的序号，再修改大的序号
					if (f < a)
					{
						int c = f;
						f = a;
						a = c;
					}
					for (int i = a; i < handNUM - 1; i++)
					{
						player_lst[i] = player_lst[i + 1];
					}
					handNUM -= 1;
					for (int i = f - 1; i < handNUM - 1; i++)
					{
						player_lst[i] = player_lst[i + 1];
					}
					handNUM -= 1;
					kill = 1;
					enemy->defence(1, 0);
				}
				else
				{
					cout << "您放弃使用丈八蛇矛！" << endl; zbsm_use = 1;
				}
			}
			//2.获取手牌号，调用出牌函数
			if (!judge() or !enemy->judge())
			{
				//添加濒死状态检包效果：检测包里的桃的数量能不能回复到1血
				if (!judge())check_bs();
				if (!enemy->judge())enemy->check_bs();
				if (!judge() or !enemy->judge())
				{
					return;
				}
			}
			cout << "请选择使用的手牌序号：";
			cin >> used;
			if (used > 0 and used <= handNUM)
			{
				card a = player_lst[used - 1];
				used -= 1;
				if (find(weapon_lst, weapon_lst + sizeof(weapon_lst) / sizeof(weapon_lst[0]), a.name) != weapon_lst + sizeof(weapon_lst) / sizeof(weapon_lst[0]))
				{
					weapon = a;
					numOfWeapon = 1;
					cout << "您装备了" << weapon.name << '!' << endl;
					for (int i = used; i < handNUM - 1; i++)
					{
						player_lst[i] = player_lst[i + 1];
					}
					handNUM -= 1;
				}
				else if (find(defencer_lst, defencer_lst + sizeof(defencer_lst) / sizeof(defencer_lst[0]), a.name) != defencer_lst + sizeof(defencer_lst) / sizeof(defencer_lst[0]))
				{
					numOfDefencer = 1;
					defencer = a;
					cout << "您装备了" << defencer.name << '!' << endl;
					for (int i = used; i < handNUM - 1; i++)
					{
						player_lst[i] = player_lst[i + 1];
					}
					handNUM -= 1;
				}
				else if (find(horse_lst, horse_lst + sizeof(horse_lst) / sizeof(horse_lst[0]), a.name) != horse_lst + sizeof(horse_lst) / sizeof(horse_lst[0])) {
					numofhorse = 1;
					horse = a;
					cout << "您装备了" << horse.name << "!" << endl;
					for (int i = used; i < handNUM - 1; i++)
					{
						player_lst[i] = player_lst[i + 1];
					}
					handNUM -= 1;
				}
				else if (find(skill_lst, skill_lst + sizeof(skill_lst) / sizeof(skill_lst[0]), a.name) != skill_lst + sizeof(skill_lst) / sizeof(skill_lst[0]))
				{
					bool jd_if = false; bool dis = true;
					if (name->id == 2 and player_lst[used].name!= "无懈可击")
					{
						if (player_lst[used].name == "桃园结义" and (enemy->HPnow != enemy->name->HP or HPnow != name->HP))
						{
							cout << "您发动黄月英的技能！摸一张牌:" << pd.front().name << endl;
							player_lst[handNUM++] = pd.front();
							pd.pop();
						}
						else if (player_lst[used].name != "乐不思蜀" and player_lst[used].name != "闪电" and player_lst[used].name != "借刀杀人")
						{
							cout << "您发动黄月英的技能！摸一张牌:" << pd.front().name << endl;
							player_lst[handNUM++] = pd.front();
							pd.pop();
						}
						else if (player_lst[used].name == "借刀杀人" and enemy->numOfWeapon > 0)
						{
							cout << "您发动黄月英的技能！摸一张牌:" << pd.front().name << endl;
							player_lst[handNUM++] = pd.front();
							pd.pop();
						}
					}
					if (!enemy->is_wxkj_used())
					{
						if (player_lst[used].name == "无中生有")
						{
							cout << "无中生有发动成功！您从牌堆顶获得2张牌！" << endl;
							player_lst[handNUM++] = pd.front();
							cout << "您获得的牌是：" << pd.front().name << endl;
							pd.pop();
							player_lst[handNUM++] = pd.front();
							cout << "您获得的牌是：" << pd.front().name << endl;
							pd.pop();
						}
						else if (player_lst[used].name == "决斗")
						{
							cout << "您发动了决斗！将由对方开始先出杀" << endl;
							//编写一个出杀函数
							int func = 0;
							jd_if = true;
						}
						else if (player_lst[used].name == "顺手牵羊")
						{
							cout << "您发动了顺手牵羊！" << endl;
							int fff = 0; bool geti = false;
							if (enemy->numOfDefencer > 0 and !geti)
							{
								cout << "敌方装备有：" << enemy->defencer.name << endl;
								cout << "按0获取，按1取消:";
								cin >> fff;
								if (fff == 0)
								{
									cout << "您成功获取一张防具：" << enemy->defencer.name << endl;
									cout << "顺手牵羊发动完毕" << endl;
									player_lst[handNUM++] = enemy->defencer;
									enemy->defencer = card();
									enemy->numOfDefencer = 0;
									geti = true;
								}
							}
							else
							{
								cout << "敌方没有装备防具！无法获得" << endl;
							}
							if (enemy->numofhorse > 0 and !geti)
							{
								cout << "敌方装备有：" << enemy->horse.name << endl;
								cout << "按0获取，按1取消:";
								cin >> fff;
								if (fff == 0)
								{
									cout << "您成功获取一张马：" << enemy->horse.name << endl;
									cout << "顺手牵羊发动完毕" << endl;
									player_lst[handNUM++] = enemy->horse;
									enemy->horse = card();
									enemy->numofhorse = 0;
									geti = true;
								}
							}
							else if (!geti)
							{
								cout << "敌方没有装备马！无法获得" << endl;
							}
							if (enemy->numOfWeapon > 0 and !geti)
							{
								cout << "敌方装备有：" << enemy->weapon.name << endl;
								cout << "按0获取，按1取消:";
								cin >> fff;
								if (fff == 0)
								{
									cout << "您成功获取一张武器牌：" << enemy->weapon.name << endl;
									cout << "顺手牵羊发动完毕" << endl;
									player_lst[handNUM++] = enemy->weapon;
									enemy->weapon = card();
									enemy->numOfWeapon = 0;
									geti = true;
								}
							}
							else if (!geti)
							{
								cout << "敌方没有装备武器！无法获得" << endl;
							}
							if (enemy->handNUM == 0 and !geti)
							{
								cout << "机器人没有手牌，顺手牵羊发动失败！" << endl;
								dis = false;
							}
							else if (enemy->handNUM > 0 and !geti)
							{
								cout << "机器人有" << enemy->handNUM << "张牌," << "输入你想得到的牌的编号：";
								cin >> fff;
								cout << "顺手牵羊发动成功，获得敌人的：" << enemy->rbt_lst[fff - 1].name << endl;
								player_lst[handNUM++] = enemy->rbt_lst[fff - 1];
								for (int i = fff - 1; i < enemy->handNUM - 1; i++)
								{
									enemy->rbt_lst[i] = enemy->rbt_lst[i + 1];
								}
								enemy->handNUM--;
							}
						}
						else if (player_lst[used].name == "过河拆桥")
						{
							cout << "您发动了过河拆桥！" << endl;
							int fff = 0; bool geti = false;
							if (enemy->numOfDefencer > 0 and !geti)
							{
								cout << "敌方装备有：" << enemy->defencer.name << endl;
								cout << "按0过河拆桥掉它的防具，按1取消:";
								cin >> fff;
								if (fff == 0)
								{
									cout << "您成功拆取一张防具：" << enemy->defencer.name << endl;
									cout << "过河拆桥发动完毕" << endl;
									enemy->defencer = card();
									enemy->numOfDefencer = 0;
									geti = true;
								}
							}
							else if (!geti)
							{
								cout << "敌方没有装备防具！无法使用过河拆桥！" << endl;
							}
							if (enemy->numofhorse > 0 and !geti)
							{
								cout << "敌方装备有：" << enemy->horse.name << endl;
								cout << "按0使用过河拆桥，按1取消:";
								cin >> fff;
								if (fff == 0)
								{
									cout << "您成功拆取一张马：" << enemy->horse.name << endl;
									cout << "过河拆桥发动完毕" << endl;
									enemy->horse = card();
									enemy->numofhorse = 0;
									geti = true;
								}
							}
							else if (!geti)
							{
								cout << "敌方没有装备马！无法使用过河拆桥！" << endl;
							}
							if (enemy->numOfWeapon > 0 and !geti)
							{
								cout << "敌方装备有：" << enemy->weapon.name << endl;
								cout << "按0获取，按1取消:";
								cin >> fff;
								if (fff == 0)
								{
									cout << "您成功拆取一张武器牌：" << enemy->weapon.name << endl;
									cout << "过河拆桥发动完毕" << endl;
									enemy->weapon = card();
									enemy->numOfWeapon = 0;
									geti = true;
								}
							}
							else if (!geti)
							{
								cout << "敌方没有装备武器！无法使用过河拆桥！" << endl;
							}
							if (enemy->handNUM == 0 and !geti)
							{
								cout << "机器人没有手牌，过河拆桥发动失败！" << endl;
								dis = false;
							}
							else if (enemy->handNUM > 0 and !geti)
							{
								cout << "机器人有" << enemy->handNUM << "张牌," << "输入你想拆掉牌的编号：";
								cin >> fff;
								cout << "过河拆桥发动成功，拆掉敌人的：" << enemy->rbt_lst[fff - 1].name << endl;
								for (int i = fff - 1; i < enemy->handNUM - 1; i++)
								{
									enemy->rbt_lst[i] = enemy->rbt_lst[i + 1];
								}
								enemy->handNUM -= 1;
							}
						}
						else if (player_lst[used].name == "南蛮入侵")
						{
							cout << "您发动了南蛮入侵！效果：" << player_lst[used].explain << endl;
							if (enemy->jd_kill())
							{
								cout << "机器人已经出杀！" << endl;
							}
							else
							{
								cout << "机器人没有出杀，扣一滴血！" << endl;
								enemy->HPnow -= 1;
								if (enemy->name->id == 1)enemy->delta(1);
							}
							cout << "南蛮入侵发动结束！" << endl;
						}
						else if (player_lst[used].name == "乐不思蜀")
						{
							if (enemy->lbssnum == 0)
							{
								cout << "乐不思蜀发动成功！" << endl;
								enemy->lbssnum = 1;
							}
							else
							{
								cout << "对方判定区已经有一张乐不思蜀了" << endl;
								dis = false;
							}
						}
						else if (player_lst[used].name == "闪电")
						{
							cout << "闪电发动成功！" << endl;
							sd = 1;
						}
						else if (player_lst[used].name == "五谷丰登")
						{
							cout << "五谷丰登发动成功！" << endl; int ff = 0;
							card a, b;
							a = pd.front(); pd.pop();
							b = pd.front(); pd.pop();
							cout << "第1张牌：" << color_lst[a.colorNUM] << huase_lst[a.huaseNUM] << ',' << a.name << endl;
							cout << "第2张牌：" << color_lst[b.colorNUM] << huase_lst[b.huaseNUM] << ',' << b.name << endl;
							cout << "您选择的牌号："; cin >> ff;
							if (ff == 1)
							{
								player_lst[handNUM++] = a;
								enemy->rbt_lst[enemy->handNUM++] = b;
							}
							else
							{
								player_lst[handNUM++] = b;
								enemy->rbt_lst[enemy->handNUM++] = a;
							}
							cout << "五谷丰登发动结束！" << endl;
						}
						else if (player_lst[used].name == "借刀杀人")
						{
							if (enemy->numOfWeapon == 1)
							{
								dis = true;
								cout << "发动成功！" << endl;
								if (enemy->jd_kill()) 
								{
									cout << "发动结束！机器人成功出杀！您未获得武器！" << endl;
									player* huma = &human;
									enemy->weapon_kill(&huma,-1);
								}
								else
								{
									cout<< "发动结束！机器人没有成功出杀！您获得武器："<<enemy->weapon.name << endl;
									card pausei = enemy->weapon;
									enemy->weapon = card();
									enemy->numOfWeapon = 0;
									player_lst[handNUM++] = pausei;
								}
							}
							else
							{
								cout << "对面没有武器，无法发动！" << endl; dis = false;
							}
						}
						else if (player_lst[used].name == "万箭齐发")
						{
							cout << "万箭齐发发动成功！" << endl;
							enemy->defence(1, 0);
						}
						else if (player_lst[used].name == "桃园结义")
						{
							if (enemy->HPnow != enemy->name->HP or HPnow != name->HP)
							{
								cout << "桃园结义发动成功！场上所有未满血的人加一滴血！" << endl;
								if (enemy->HPnow != enemy->name->HP)
								{
									cout << "当前机器人血量：" << enemy->HPnow << '/' << enemy->name->HP << endl;
									enemy->HPnow += 1;
									cout << "现在机器人血量：" << enemy->HPnow << '/' << enemy->name->HP << endl;
								}
								if (HPnow != name->HP)
								{
									cout << "当前您血量：" << HPnow << '/' << name->HP << endl;
									HPnow += 1;
									cout << "现在您血量：" << HPnow << '/' << name->HP << endl;
								}
							}
							else
							{
								dis = false;
								cout << "当前场上没有人扣血，无法使用！" << endl;
							}
						}
						else if (player_lst[used].name == "无懈可击")
						{
							cout << "不能主动使用无懈可击！" << endl;
							dis = false;
						}
					}
					else
					{
						cout << "您的" << player_lst[used].name << "发动失败！" << endl;
						dis = true;
					}
					//如果是满足dis：丢弃的条件，那么把这张牌放到牌堆底部。
					if (dis)
					{
						pd.push(player_lst[used]);
						for (int i = used; i < handNUM - 1; i++)
						{
							player_lst[i] = player_lst[i + 1];
						}
						handNUM -= 1;
					}
					if (jd_if)
					{
						bool fini = false; bool kd = enemy->jd_kill(); int funn;
						while (kd and !fini)
						{
							cout << "机器人出了一张杀！" << endl;
							cout << "当前手牌：" << endl;
							cout << "序号/名字/功能" << endl;
							for (int i = 0; i < handNUM; i++)
							{
								cout << i + 1 << '/' << player_lst[i].name << '/' << player_lst[i].explain << endl;
							}
							cout << "请输出你的杀手牌的编号：";
							cin >> funn;
							if (player_lst[funn - 1].name == "杀")
							{
								cout << "您成功出了一张杀！" << endl;
								pd.push(player_lst[funn - 1]);
								for (int i = funn - 1; i < handNUM - 1; i++)
								{
									player_lst[i] = player_lst[i + 1];
								}
								handNUM--;
							}
							else
							{
								cout << "您无法打出一张杀，扣一滴血！" << endl;
								HPnow -= 1;
								fini = true;
								if (name->id == 1)delta(1);
								break;
							}
							kd = enemy->jd_kill();
						}
						if (!kd)
						{
							cout << "决斗结束，机器人无法继续出杀，扣一滴血！" << endl;
							enemy->HPnow -= 1;
							if (enemy->name->id == 1)enemy->delta(1);
						}
						jd_if = false;
					}
				}
				else
				{
					//如果出杀，则调用机器人的防御函数，检视机器人有没有闪，没有则扣一点血
					if (a.name == "杀")
					{
						bool distance = (enemy->horse.name == "-1马" and (horse.name != "+1马" and numOfWeapon == 0));
						if (numOfWeapon == 0 and kill == 0 and !distance)
						{
							pd.push(player_lst[used]);
							for (int i = used; i < handNUM - 1; i++)
							{
								player_lst[i] = player_lst[i + 1];
							}
							handNUM -= 1;
							kill = 1;
							enemy->defence(1, a.colorNUM);
						}
						else if ((numOfWeapon == 1 and kill == 0) or (numOfWeapon == 1 and weapon.name == "诸葛连弩"))
						{
							weapon_kill(&enemy, used);
						}
						if (kill == 1)
						{
							cout << "每回合无特殊情况只能对对手使用一次杀！" << endl;
						}
						if (distance)
						{
							cout << "对方装备了-1马，您的攻击距离不够，无法攻击！" << endl;
						}
					}
					else if (a.name == "闪")
					{
						cout << "不能主动出闪！" << endl;
					}
					else
					{
						if (HPnow == name->HP)
						{
							cout << "当前满血，不需使用桃" << endl;
						}
						else
						{
							HPnow += 1;
							cout << "当前血量：" << HPnow << '/' << name->HP << endl;
							pd.push(player_lst[used]);
							for (int i = used; i < handNUM - 1; i++)
							{
								player_lst[i] = player_lst[i + 1];
							}
							handNUM -= 1;
						}
					}
				}
			}
			else
			{
				cout << "请输入有效的手牌编号！" << endl;
			}
		}
		else if (func == 4)
		{
			break;
		}
		else
		{
			cout << "请按照指令输入" << endl;
		}
		if (!judge() or !enemy->judge())
		{
			//添加濒死状态检包效果：检测包里的桃的数量能不能回复到1血
			if (!judge())check_bs();
			if (!enemy->judge())enemy->check_bs();
			if (!judge() or !enemy->judge())
			{
				return;
			}
		}
	}
	finish();
	return;
}
void robot::play(player* human)
{
	//机器人出牌逻辑：
	//先出防具和武器，再出锦囊，最后出杀和桃，
	//原则：尽量出完，不留牌。
	int i = 0;
	if (!human->judge() or !judge())
	{
		//添加濒死状态检包效果：检测包里的桃的数量能不能回复到1血
		if (!human->judge())human->check_bs();
		if (!judge())check_bs();
		if (!human->judge() or !judge())
		{
			return;
		}
	}
	while (i < handNUM)
	{
		bool useing = false; bool is_jd = false;
		//defencer
		if (rbt_lst[i].name == "八卦阵" or rbt_lst[i].name == "仁王盾")
		{
			cout << "机器人装备了防具：" << rbt_lst[i].name << endl;
			defencer = rbt_lst[i];
			numOfDefencer = 1;
			useing = true;
		}
		//horse
		else if (find(horse_lst, horse_lst + sizeof(horse_lst) / sizeof(horse_lst[0]), rbt_lst[i].name) != horse_lst + sizeof(horse_lst) / sizeof(horse_lst[0]))
		{
			cout << "机器人装备了马：" << rbt_lst[i].name << endl;
			horse = rbt_lst[i];
			numofhorse = 1;
			useing = true;
		}
		//weapon
		else if (find(weapon_lst, weapon_lst + sizeof(weapon_lst) / sizeof(weapon_lst[0]), rbt_lst[i].name) != weapon_lst + sizeof(weapon_lst) / sizeof(weapon_lst[0]))
		{
			cout << "机器人装备了武器：" << rbt_lst[i].name << endl;
			weapon = rbt_lst[i];
			numOfWeapon = 1;
			useing = true;
		}
		//jinnang
		else if (find(skill_lst, skill_lst + sizeof(skill_lst) / sizeof(skill_lst[0]), rbt_lst[i].name) != skill_lst + sizeof(skill_lst) / sizeof(skill_lst[0]) and rbt_lst[i].name != "无懈可击")
		{
			cout << "机器人使用了" << rbt_lst[i].name << endl;
			bool nameing = human->is_wxkj_used();
			if (!nameing)
			{
				if (rbt_lst[i].name == "无中生有")
				{
					cout << "无中生有发动成功！机器人从牌堆顶获得2张牌！" << endl;
					rbt_lst[handNUM++] = pd.front();
					pd.pop();
					rbt_lst[handNUM++] = pd.front();
					pd.pop();
					useing = true;
				}
				else if (rbt_lst[i].name == "顺手牵羊")
				{
					int fff = 0; bool geti = false;
					if (human->numOfDefencer > 0 and !geti)
					{
						cout << "机器人成功获取您的防具：" << human->defencer.name << endl;
						cout << "机器人顺手牵羊发动完毕" << endl;
						rbt_lst[handNUM++] = human->defencer;
						human->defencer = card();
						human->numOfDefencer = 0;
						geti = true;
						useing = true;
					}
					if (human->numofhorse > 0 and !geti)
					{
						cout << "机器人成功获取您的一张马：" << human->horse.name << endl;
						cout << "顺手牵羊发动完毕" << endl;
						rbt_lst[handNUM++] = human->horse;
						human->horse = card();
						human->numofhorse = 0;
						geti = true;
						useing = true;
					}
					if (human->numOfWeapon > 0 and !geti)
					{
						cout << "敌人成功获取您武器牌：" << human->weapon.name << endl;
						cout << "顺手牵羊发动完毕" << endl;
						rbt_lst[handNUM++] = human->weapon;
						human->weapon = card();
						human->numOfWeapon = 0;
						geti = true;
						useing = true;
					}
					if (human->handNUM == 0 and !geti)
					{
						cout << "您没有手牌，顺手牵羊发动失败！" << endl;
						useing = false;
					}
					else if (human->handNUM > 0 and !geti)
					{
						fff = rand() % (human->handNUM);
						cout << "机器人获得您的:" << human->player_lst[fff].name << endl;
						rbt_lst[handNUM++] = human->player_lst[fff];
						for (int i = fff - 1; i < human->handNUM - 1; i++)
						{
							human->player_lst[i] = human->player_lst[i + 1];
						}
						human->handNUM--;
						useing = true;
					}
				}
				else if (rbt_lst[i].name == "过河拆桥")
				{
					int fff = 0; bool geti = false;
					if (human->numOfDefencer > 0 and !geti)
					{
						cout << "机器人成功拆取您一张防具：" << human->defencer.name << endl;
						cout << "过河拆桥发动完毕" << endl;
						human->defencer = card();
						human->numOfDefencer = 0;
						geti = true; useing = true;
					}
					if (human->numofhorse > 0 and !geti)
					{
						cout << "机器人成功拆取您一张马：" << human->horse.name << endl;
						cout << "过河拆桥发动完毕" << endl;
						human->horse = card();
						human->numofhorse = 0;
						geti = true; useing = true;
					}
					if (human->numOfWeapon > 0 and !geti)
					{
						cout << "机器人成功拆取一张武器牌：" << human->weapon.name << endl;
						cout << "过河拆桥发动完毕" << endl;
						human->weapon = card();
						human->numOfWeapon = 0;
						geti = true; useing = true;
					}
					if (human->handNUM == 0 and !geti)
					{
						cout << "您没有手牌，过河拆桥发动失败！" << endl;
						useing = false;
					}
					else if (human->handNUM > 0 and !geti)
					{
						fff = rand() % (human->handNUM);
						cout << "过河拆桥发动成功，拆掉您的：" << human->player_lst[fff].name << endl;
						for (int i = fff; i < human->handNUM - 1; i++)
						{
							human->player_lst[i] = human->player_lst[i + 1];
						}
						human->handNUM -= 1; useing = true;
					}
				}
				else if (rbt_lst[i].name == "南蛮入侵")
				{
					cout << "机器人发动了南蛮入侵！效果：" << rbt_lst[i].explain << endl;
					if (human->jd_kill())
					{
						cout << "您已经出杀！" << endl;
					}
					else
					{
						cout << "您没有出杀，扣一滴血！" << endl;
						human->HPnow -= 1;
						if (human->name->id == 1)human->delta(1);
					}
					cout << "南蛮入侵发动结束！" << endl;

					useing = true;
				}
				else if (rbt_lst[i].name == "乐不思蜀")
				{
					if (human->lbssnum == 0)
					{
						cout << "机器人对您的乐不思蜀发动成功！" << endl;
						human->lbssnum = 1;
						useing = true;
					}
				}
				else if (rbt_lst[i].name == "闪电")
				{
					cout << "机器人的闪电发动成功！" << endl;
					sd = 1; useing = true;
				}
				else if (rbt_lst[i].name == "五谷丰登")
				{
					cout << "机器人的五谷丰登发动成功！" << endl;
					int ff = rand() % 2;
					card a, b;
					a = pd.front(); pd.pop();
					b = pd.front(); pd.pop();
					cout << "第1张牌：" << a.name << endl;
					cout << "第2张牌：" << b.name << endl;

					if (ff == 0)
					{
						cout << "机器人选择的牌：" << a.name << endl;
						rbt_lst[handNUM++] = a;
						human->player_lst[human->handNUM++] = b;
					}
					else
					{
						cout << "机器人选择的牌：" << b.name << endl;
						rbt_lst[handNUM++] = b;
						human->player_lst[human->handNUM++] = a;
					}
					cout << "五谷丰登发动结束！" << endl;
					useing = true;
				}
				else if (rbt_lst[i].name == "借刀杀人")
				{
					if (human->numOfWeapon == 1)
					{
						useing = true;
						cout << "发动成功！" << endl;
						if (human->jd_kill())
						{
							cout << "发动结束！您成功出杀！机器人未获得武器！" << endl;
							robot* enemy = &rbt;
							human->weapon_kill(&enemy,-1);
						}
						else
						{
							cout << "发动结束！您没有成功出杀！机器人获得武器：" << human->weapon.name << endl;
							card pausei = human->weapon;
							human->weapon = card();
							human->numOfWeapon = 0;
							rbt_lst[handNUM++] = pausei;
						}
					}
					else
					{
						cout << "对面没有武器，无法发动！" << endl;useing = false;
					}
				}
				else if (rbt_lst[i].name == "万箭齐发")
				{
					cout << "万箭齐发发动成功！" << endl;
					human->defence(1, 0);
				}
				else if (rbt_lst[i].name == "桃园结义")
				{
					if (HPnow != name->HP)
					{
						useing = true;
						cout << "桃园结义发动成功！场上所有未满血的人加一滴血！" << endl;
						if (HPnow != name->HP)
						{
							cout << "当前机器人血量：" << HPnow << '/' << name->HP << endl;
							HPnow += 1;
							cout << "现在机器人血量：" << HPnow << '/' << name->HP << endl;
						}
						if (human->HPnow != human->name->HP)
						{
							cout << "当前您血量：" << human->HPnow << '/' << human->name->HP << endl;
							human->HPnow += 1;
							cout << "现在您血量：" << human->HPnow << '/' << human->name->HP << endl;
						}
					}

				}
				else if (rbt_lst[i].name == "决斗")
				{
					useing = true; is_jd = true;
				}
			}
			else
			{
				cout << rbt_lst[i].name << "发动失败！" << endl;
				useing = true;
			}
			if (name->id == 2 and useing == true and rbt_lst[i].name!="乐不思蜀" and rbt_lst[i].name != "闪电") {
				cout << "机器人发动黄月英的技能！摸一张牌" << endl;
				rbt_lst[handNUM++] = pd.front();
				pd.pop();
			}
		}
		//桃
		else if (rbt_lst[i].name == "桃" and name->HP > HPnow)
		{
			HPnow++;
			cout << "机器人使用了桃！现在的血量：" << HPnow << '/' << name->HP << endl;
			useing = true;
		}
		if (useing)
		{
			pd.push(rbt_lst[i]);
			for (int j = i; j < handNUM - 1; j++)
			{
				rbt_lst[j] = rbt_lst[j + 1];
			}
			handNUM -= 1;
		}
		if (!useing)i++;
		if (!human->judge() or !judge())return;
		if (is_jd)
		{
			bool li = human->jd_kill();
			while (li)
			{
				if (!jd_kill())break;
				li = human->jd_kill();
			}
			if (li)
			{
				cout << "决斗您胜利了！机器人扣一滴血！" << endl;
				HPnow--;
				if (name->id == 1)delta(1);
			}
			else
			{
				cout << "决斗机器人胜利了！您扣一滴血！" << endl;
				human->HPnow--;
				if (human->name->id == 1)human->delta(1);
			}
			cout << "决斗结束！" << endl;
			is_jd = false;
		}
		if (!human->judge() or !judge())
		{
			//添加濒死状态检包效果：检测包里的桃的数量能不能回复到1血
			if (!human->judge())human->check_bs();
			if (!judge())check_bs();
			if (!human->judge() or !judge())
			{
				break;
			}
		}
	}
	i = 0;
	while (i < handNUM)
	{
		bool distance = (human->horse.name == "-1马" and (horse.name != "+1马" and numOfWeapon == 0));
		if (rbt_lst[i].name == "杀" and numOfWeapon == 0 and kill == 0 and !distance)
		{
			cout << "机器人使用了杀！" << endl;
			human->defence(1, rbt_lst[i].colorNUM);
			pd.push(rbt_lst[i]);
			for (int j = i; j < handNUM - 1; j++)
			{
				rbt_lst[j] = rbt_lst[j + 1];
			}
			handNUM -= 1;
			kill = 1;
		}
		else if ((numOfWeapon == 1 and kill == 0) or (numOfWeapon == 1 and weapon.name == "诸葛连弩"))
		{
			weapon_kill(&human, i);
		}
		
		i++;
		if (!human->judge() or !judge())
		{
			//添加濒死状态检包效果：检测包里的桃的数量能不能回复到1血
			if (!human->judge())human->check_bs();
			if (!judge())check_bs();
			if (!human->judge() or !judge())
			{
				return;
			}
		}
	}
	if (weapon.name == "丈八蛇矛" and kill == 0 and handNUM >= 2)
	{
		cout << "机器人丈八蛇矛发动成功!" << endl;
		int a = rand() % handNUM, f = rand() % handNUM;
		pd.push(rbt_lst[a]);
		pd.push(rbt_lst[f]);
		cout << "机器人弃置：" << rbt_lst[a].name << "," << rbt_lst[f].name << endl;
		//防止修改牌的时候出错，先修改小的序号，再修改大的序号
		if (f < a)
		{
			int c = f;
			f = a;
			a = c;
		}
		for (int j = a; j < handNUM - 1; j++)
		{
			rbt_lst[j] = rbt_lst[j + 1];
		}
		handNUM -= 1;
		for (int j = f - 1; j < handNUM - 1; j++)
		{
			rbt_lst[j] = rbt_lst[j + 1];
		}
		handNUM -= 1;
		kill = 1;
		human->defence(1, 0);
	}
}
int main()
{
	int a;
	cout << "====================================================" << endl;
	cout << "======欢迎来到文字版三国杀（对战机器人版）!=========" << endl;
	cout << "======操作：按1进入游戏,任何时刻按0退出游戏=========" << endl;
	cin >> a;
	if (checknum(a))return 0;
	card_lst_init();
	while (a == 1)
	{
		pd_init();
		int num;
		cout << "========选择你的角色=========" << endl;
		cout << "序号/" << "角色名称/" << "血量/" << "技能说明" << endl;
		for (int i = 0; i < role_num; i++)
		{
			cout << role_lst[i].id << '/' << role_lst[i].name << '/' << role_lst[i].HP << '/' << role_lst[i].skill << endl;
		}
		cout << "=========================" << endl;
		cout << "你选择的角色序号是："; cin >> num;
		if (checknum(num))return 0;
		choice = rand() % 2;
		cout << "机器人选择的角色序号是：" << choice+1<<endl;
		cout << "===========游戏正式开始==============" << endl;
		playerrole = role_lst[num - 1];
		player human(playerrole);//后续可被替换
		robotrole = role_lst[choice];
		robot rbt(robotrole);//后续可被替换
		human.init();
		rbt.init();
		while (rbt.judge() and human.judge())
		{
			if (human.judge() and rbt.judge())human.annother();
			if (human.sd == 1 and human.judge() and rbt.judge())
			{
				int aaaa=1;
				for (int nn = 0; nn < human.handNUM; nn++)
				{
					if (human.player_lst[nn].name == "无懈可击")
					{
						cout << "闪电即将判定，是否使用无懈可击？(按0使用，按1不使用)：" << endl;
						cin >> aaaa;
						if (aaaa == 0)
						{
							cout << "无懈可击使用成功！" << endl;
							pd.push(human.player_lst[nn]);
							for (int nnn = nn; nnn < human.handNUM - 1; nnn++)human.player_lst[nnn] = human.player_lst[nnn + 1];
							human.handNUM -= 1;
							break;
						}
						break;
					}
				}
				if (aaaa == 1)
				{
					cout << "接下来进行您的闪电的判定：" << endl;
					card ls = pd.front();
					pd.pop();
					pd.push(ls);
					if (ls.colorNUM == 1 and ls.huaseNUM == 2)
					{
						cout << "花色为黑桃！您扣三滴血！" << endl;
						human.HPnow -= 3;
					}
					else
					{
						cout << "花色为" << color_lst[ls.colorNUM] << huase_lst[ls.huaseNUM] << "！闪电没有生效！" << endl;
						rbt.sd = 1;
					}
				}
				human.sd = 0;
				if (!human.judge() or !rbt.judge())
				{
					//添加濒死状态检包效果：检测包里的桃的数量能不能回复到1血
					if (!human.judge())human.check_bs();
					if (!rbt.judge())rbt.check_bs();
					if (!human.judge() or !rbt.judge())
					{
						break;
					}
				}
			}
			if (!human.lbsse and human.judge() and rbt.judge())
			{
				human.play(&rbt);
			}
			if (rbt.judge() and human.judge())
			{
				human.finish();
			}
			if(human.judge() and rbt.judge())rbt.annother();
			if (rbt.sd == 1 and human.judge() and rbt.judge())
			{
				int aaaa = 1;
				for (int nn = 0; nn < rbt.handNUM; nn++)
				{
					if (rbt.rbt_lst[nn].name == "无懈可击")
					{
						aaaa = 0;
						cout << "机器人使用无懈可击消除了闪电！" << endl;
						pd.push(rbt.rbt_lst[nn]);
						for (int nnn = nn; nnn < rbt.handNUM - 1; nnn++)rbt.rbt_lst[nnn] = rbt.rbt_lst[nnn + 1];
						rbt.handNUM -= 1;
						break;
					}
				}
				if (aaaa == 1)
				{
					cout << "接下来进行机器人的闪电的判定：" << endl;
					card ls = pd.front();
					pd.pop();
					pd.push(ls);
					if (ls.colorNUM == 1 and ls.huaseNUM == 2)
					{
						cout << "花色为黑桃！机器人扣三滴血！" << endl;
						rbt.HPnow -= 3;
					}
					else
					{
						cout << "花色为" << color_lst[ls.colorNUM] << huase_lst[ls.huaseNUM] << "！闪电没有生效！" << endl;
						human.sd = 1;
					}
				}
				rbt.sd = 0;
				if (!human.judge() or !rbt.judge())
				{
					//添加濒死状态检包效果：检测包里的桃的数量能不能回复到1血
					if (!human.judge())human.check_bs();
					if (!rbt.judge())rbt.check_bs();
					if (!human.judge() or !rbt.judge())
					{
						break;
					}
				}
			}
			if (!rbt.lbsse and human.judge() and rbt.judge())
			{
				rbt.play(&human);
			}
			if (human.judge() and rbt.judge())
			{
				rbt.finish();
			}
		}
		if(!rbt.judge())
		{
			cout << "你赢了"<<endl;
		}
		if(!human.judge())
		{
			cout << "机器人赢了"<<endl;
		}
		cout << "游戏结束！感谢游玩！按任意键退出！" << endl;
		system("pause");
		a = 0;
	}
	return 0;
}
