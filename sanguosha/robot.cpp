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
	cout << "===========�����˳������" << endl;
}
robot::robot(role a)
{
	name = &robotrole;
	HPnow = name->HP;
}
robot::robot() {};
void robot::annother()
{
	cout << "�����˵Ļغ�" << endl;
	kill = 0;
	for (int i = 0; i < 2; i++)
	{
		rbt_lst[handNUM++] = pd.front();
		pd.pop();
	}
	if (lbssnum == 1)
	{
		cout << "��������������˵��ֲ�˼���ж�ʱ��" << endl;
		card ls = pd.front();
		pd.pop();
		pd.push(ls);
		if (ls.colorNUM == 0 and ls.huaseNUM == 2)
		{
			cout << "��ɫΪ���ң������˲����������ƽ׶Σ�" << endl;
		}
		else
		{
			cout << "��ɫΪ" << color_lst[ls.colorNUM] << huase_lst[ls.huaseNUM] << "���������������ƽ׶Σ�" << endl;
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
		cout << "����������" << handNUM - HPnow << "����" << endl;
	}
	else
	{
		cout << "�����˲���Ҫ���ƣ�" << endl;
	}
	while (handNUM > HPnow)
	{
		srand = rand() % handNUM;
		cout << "������������" << rbt_lst[srand].name << endl;
		pd.push(rbt_lst[srand]);
		for (int i = srand; i < handNUM - 1; i++)
		{
			rbt_lst[i] = rbt_lst[i + 1];
		}
		handNUM--;
	}
	cout << "���������ƽ׶ν�����" << endl;
	lbsse = false;
	return;
}
void robot::defence(int n, int colornum)
{
	//��ͨ�������޷��ߣ�������ͨ�������ʵ�����ܻ��߿�Ѫ,�з��ߣ��鿴����
	if (n == 0 or numOfDefencer == 0)
	{
		int i = 0;
		for (i; i < handNUM; i++)
		{
			if (rbt_lst[i].name == "��")break;
		}
		if (i == handNUM)
		{
			cout << "������û�г�������һ��Ѫ��" << endl;
			HPnow -= 1;
			return;
		}
		else
		{
			cout << "�����˳���" << endl;
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
		if (defencer.name == "������")
		{
			cout << "�����˷������ߣ�������" << endl;
			card cc = pd.front();
			pd.pop();
			pd.push(cc);
			if (cc.colorNUM == 0)
			{
				cout << "��������Ч������Ϊ��" << color_lst[cc.colorNUM] << huase_lst[cc.huaseNUM] << ",��������Ϊ����һ����" << endl;
				return;
			}
			else
			{
				cout << "������û��Ч������Ϊ��" << color_lst[cc.colorNUM] << huase_lst[cc.huaseNUM] << endl;
				int i = 0;
				for (i; i < handNUM; i++)
				{
					if (rbt_lst[i].name == "��")break;
				}
				if (i == handNUM)
				{
					cout << "������û�г�������һ��Ѫ��" << endl;
					HPnow -= 1;
					if (name->id == 1)delta(1);
					return;
				}
				else
				{
					cout << "�����˳���" << endl;
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
		else if (defencer.name == "������")
		{
			cout << "�����˷��������ܣ�" << endl;
			if (colornum == 1)
			{
				cout << "���������ܵ�Ч������ɫɱ��Ч��" << endl;
				return;
			}
			else
			{
				cout << "�����ܶԺ�ɫɱ��Ч��" << endl;
				int i = 0;
				for (i; i < handNUM; i++)
				{
					if (rbt_lst[i].name == "��")break;
				}
				if (i == handNUM)
				{
					cout << "������û�г�������һ��Ѫ��" << endl;
					HPnow -= 1;
					if (name->id == 1)delta(1);
					return;
				}
				else
				{
					cout << "�����˳���" << endl;
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
		if (rbt_lst[i].name == "ɱ")
		{
			cout << "�����˳ɹ���ɱ��" << endl;
			pd.push(rbt_lst[i]);
			for (int j = i; j < handNUM; j++)rbt_lst[j] = rbt_lst[j + 1];
			handNUM--;
			return true;
		}
	}
	if (weapon.name == "�ɰ���ì" and handNUM >= 2)
	{
		int fa, fb;
		fa = rand() % handNUM;
		fb = rand() % handNUM;
		while(fb == fa)fb = rand() % handNUM;
		if (fa > fb) { int ffc = fa; fa = fb; fb = ffc; }
		pd.push(rbt_lst[fa]); pd.push(rbt_lst[fb]);
		cout << "���������ã�" << rbt_lst[fa].name << ',' << rbt_lst[fb].name << "�����ɰ���ì��" << endl;
		for (int i = fb; i < handNUM - 1; i++)rbt_lst[i] = rbt_lst[i + 1]; handNUM--;
		for (int i = fa; i < handNUM - 1; i++)rbt_lst[i] = rbt_lst[i + 1]; handNUM--;
		cout << "�������ɰ���ì�����ɹ���" << endl;
		return true;
	}
	return li;
}
bool robot::is_wxkj_used()
{
	int i = 0; bool iii = false;
	for (i; i < handNUM; i++)
	{
		if (rbt_lst[i].name == "��и�ɻ�")
		{
			iii = true;
			break;
		}
	}
	if (iii)
	{
		for (int j = i; j < handNUM - 1; j++)rbt_lst[j] = rbt_lst[j + 1];
		cout << "������ʹ������и�ɻ���" << endl;
		if (name->id == 2)
		{
			cout << "�����˷�������Ӣ�ļ��ܣ���һ����" << endl;
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
	cout << "�����˷���������" << weapon.name << "��������ɱ��";
	if(used !=-1)
	{ 
		if (weapon.name == "�������")
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
		else if (weapon.name == "��׽�")
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
		else if (weapon.name == "����˫�ɽ�")
		{
			if ((*human)->name->sex != name->sex)
			{
				int choice = rand() % 2;
				if (choice == 0)
				{
					cout << "����˫�ɽ������ɹ����û�������һ���ƣ�" << endl;
					rbt_lst[handNUM++] = pd.front();
					pd.pop();
					cout << "���������������ǣ�" << rbt_lst[handNUM - 1].name << endl;
				}
				else
				{
					cout << "����˫�ɽ������ɹ������������������һ���ƣ�" << endl;
					int srand = rand() % (*human)->handNUM;
					pd.push((*human)->player_lst[srand]);
					cout << "�����������������ǣ�" << (*human)->player_lst[srand].name << endl;
					for (int i = srand; i < (*human)->handNUM - 1; i++)
					{
						(*human)->player_lst[i] = (*human)->player_lst[i + 1];
					}
					(*human)->handNUM -= 1;
				}
			}
			else
			{
				cout << "�����˵Ĵ���˫�ɽ�������Ч��" << endl;
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
		else if (weapon.name == "������")
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
					cout << "��⵽��������С�����ţ������˷���������������" << endl;
					return;
				}
				cout << "�����������ɹ�!��������������������ƣ�����װ������" << endl;
				(*human)->HPnow += 1;
				int num = 2;
				int srand;
				if ((*human)->numOfWeapon != 0)
				{
					cout << "����������������������" << (*human)->weapon.name << endl;
					pd.push((*human)->weapon);
					(*human)->weapon = card();
					(*human)->numOfWeapon = 0;
					num--;
				}
				if ((*human)->numOfDefencer != 0)
				{
					cout << "���������������ķ��ߣ�" << (*human)->defencer.name << endl;
					pd.push((*human)->defencer);
					(*human)->defencer = card();
					(*human)->numOfDefencer = 0;
					num--;
				}
				if (num > 0 and (*human)->numofhorse > 0)
				{
					cout << "������������������" << (*human)->defencer.name << endl;
					pd.push((*human)->horse);
					(*human)->horse = card();
					(*human)->numofhorse = 0;
					num--;
				}
				if (num == 0 or (*human)->handNUM == 0)
				{
					cout << "�����˺�����Ч������" << endl;
					return;
				}
				else
				{
					num = (num <= (*human)->handNUM) ? num : (*human)->handNUM;
					cout << "���������ȥ����" << num << "����" << endl;
					for (int k = 0; k < num; k++)
					{
						srand = rand() % (*human)->handNUM;
						pd.push((*human)->player_lst[srand]);
						cout << "���������������ǣ�" << (*human)->player_lst[srand].name << endl;
						for (int i = srand; i < (*human)->handNUM - 1; i++)
						{
							(*human)->player_lst[i] = (*human)->player_lst[i + 1];
						}
						(*human)->handNUM -= 1;
					}
					cout << "������Ч������" << endl;
					return;
				}

			}

		}
		else if (weapon.name == "��ʯ��")
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
				if ((*human)->defencer.name == "������" and ss.huaseNUM == 1)
				{
					cout << "�����˺���������ʯ���޷�����" << endl;
					return;
				}
				else
				{
					if (handNUM < 2)
					{
						cout << "����������С��2��ȡ��������ʯ����" << endl;
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
						cout << "�����˹�ʯ�������ɹ���ǿ������һ��Ѫ��" << endl;
						return;
					}
				}
			}
		}
		else if (weapon.name == "�������µ�")
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
				if ((*human)->defencer.name == "������" and ss.huaseNUM == 1)
				{
					cout << "�����˺������������˵��������µ��޷�������" << endl;
					return;
				}
				int ppnum = 0; bool sure_use = false;
				for (ppnum; ppnum < handNUM; ppnum++)
				{
					if (rbt_lst[ppnum].name == "ɱ")
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
					cout << "�����˷����������µ�������ɱ��" << endl;
					(*human)->defence(1, ss.colorNUM);
					ppnum = 0; sure_use = false;
					for (ppnum; ppnum < handNUM; ppnum++)
					{
						if (rbt_lst[ppnum].name == "ɱ")
						{
							sure_use = true;
							break;
						}
					}
				}
				if ((*human)->HPnow == HPbefore)cout << "�������޷�������ɱ��" << endl;
				cout << "�������µ�Ч��������ϣ�" << endl;
			}
		}
		else if (weapon.name == "���컭�")
		{
			cout << "����ģʽ���ƣ�û����Ӹ�������Ч����" << endl;
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
		else if (weapon.name == "���빭")
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
				cout << "���빭Ч��������������������һ�����" << (*human)->horse.name << endl;
				pd.push((*human)->horse);
				(*human)->numofhorse = 0;
			}
		}
	}
	else
	{
		if (weapon.name == "�������")(*human)->defence(1, pd.back().colorNUM);
		else if (weapon.name == "��׽�")(*human)->defence(0, pd.back().colorNUM);
		else if (weapon.name == "����˫�ɽ�")
		{
			if ((*human)->name->sex != name->sex)
			{
				int choice = rand() % 2;
				if (choice == 0)
				{
					cout << "����˫�ɽ������ɹ����û�������һ���ƣ�" << endl;
					rbt_lst[handNUM++] = pd.front();
					pd.pop();
					cout << "���������������ǣ�" << rbt_lst[handNUM - 1].name << endl;
				}
				else
				{
					cout << "����˫�ɽ������ɹ������������������һ���ƣ�" << endl;
					int srand = rand() % (*human)->handNUM;
					pd.push((*human)->player_lst[srand]);
					cout << "�����������������ǣ�" << (*human)->player_lst[srand].name << endl;
					for (int i = srand; i < (*human)->handNUM - 1; i++)
					{
						(*human)->player_lst[i] = (*human)->player_lst[i + 1];
					}
					(*human)->handNUM -= 1;
				}
			}
			else
			{
				cout << "�����˵Ĵ���˫�ɽ�������Ч��" << endl;
			}
			(*human)->defence(1, pd.back().colorNUM);
		}
		else if (weapon.name == "������")
		{
			int HPbefore = (*human)->HPnow;
			(*human)->defence(1, pd.back().colorNUM);
			if ((*human)->HPnow < HPbefore)
			{
				if ((*human)->numOfWeapon + (*human)->numOfDefencer + (*human)->numofhorse + (*human)->handNUM < 2)
				{
					cout << "��⵽��������С�����ţ������˷���������������" << endl;
					return;
				}
				cout << "�����������ɹ�!��������������������ƣ�����װ������" << endl;
				(*human)->HPnow += 1;
				int num = 2;
				int srand;
				if ((*human)->numOfWeapon != 0)
				{
					cout << "����������������������" << (*human)->weapon.name << endl;
					pd.push((*human)->weapon);
					(*human)->weapon = card();
					(*human)->numOfWeapon = 0;
					num--;
				}
				if ((*human)->numOfDefencer != 0)
				{
					cout << "���������������ķ��ߣ�" << (*human)->defencer.name << endl;
					pd.push((*human)->defencer);
					(*human)->defencer = card();
					(*human)->numOfDefencer = 0;
					num--;
				}
				if (num > 0 and (*human)->numofhorse > 0)
				{
					cout << "������������������" << (*human)->defencer.name << endl;
					pd.push((*human)->horse);
					(*human)->horse = card();
					(*human)->numofhorse = 0;
					num--;
				}
				if (num == 0 or (*human)->handNUM == 0)
				{
					cout << "�����˺�����Ч������" << endl;
					return;
				}
				else
				{
					num = (num <= (*human)->handNUM) ? num : (*human)->handNUM;
					cout << "���������ȥ����" << num << "����" << endl;
					for (int k = 0; k < num; k++)
					{
						srand = rand() % (*human)->handNUM;
						pd.push((*human)->player_lst[srand]);
						cout << "���������������ǣ�" << (*human)->player_lst[srand].name << endl;
						for (int i = srand; i < (*human)->handNUM - 1; i++)
						{
							(*human)->player_lst[i] = (*human)->player_lst[i + 1];
						}
						(*human)->handNUM -= 1;
					}
					cout << "������Ч������" << endl;
					return;
				}

			}

		}
		else if (weapon.name == "��ʯ��")
		{
			int HPbefore = (*human)->HPnow;
			card cc = pd.back();
			(*human)->defence(1, cc.colorNUM);
			if ((*human)->HPnow == HPbefore)
			{
				if ((*human)->defencer.name == "������" and cc.colorNUM == 1)
				{
					cout << "�����˺���������ʯ���޷�����" << endl;
					return;
				}
				else
				{
					if (handNUM < 2)
					{
						cout << "����������С��2��ȡ��������ʯ����" << endl;
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
						cout << "�����˹�ʯ�������ɹ���ǿ������һ��Ѫ��" << endl;
						return;
					}
				}
			}
		}
		else if (weapon.name == "�������µ�")
		{
			int HPbefore = (*human)->HPnow;
			card ss = pd.back();
			(*human)->defence(1, ss.colorNUM);
			if ((*human)->HPnow == HPbefore)
			{
				if ((*human)->defencer.name == "������" and ss.huaseNUM == 1)
				{
					cout << "�����˺������������˵��������µ��޷�������" << endl;
					return;
				}
				int ppnum = 0; bool sure_use = false;
				for (ppnum; ppnum < handNUM; ppnum++)
				{
					if (rbt_lst[ppnum].name == "ɱ")
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
					cout << "�����˷����������µ�������ɱ��" << endl;
					(*human)->defence(1, ss.colorNUM);
					ppnum = 0; sure_use = false;
					for (ppnum; ppnum < handNUM; ppnum++)
					{
						if (rbt_lst[ppnum].name == "ɱ")
						{
							sure_use = true;
							break;
						}
					}
				}
				if ((*human)->HPnow == HPbefore)cout << "�������޷�������ɱ��" << endl;
				cout << "�������µ�Ч��������ϣ�" << endl;
			}
		}
		else if (weapon.name == "���컭�")
		{
			cout << "����ģʽ���ƣ�û����Ӹ�������Ч����" << endl;
			card cc = pd.back();
			(*human)->defence(1, cc.colorNUM);
		}
		else if (weapon.name == "���빭")
		{
			int HPbefore = (*human)->HPnow;
			card cc = pd.back();
			(*human)->defence(1, cc.colorNUM);
			if ((*human)->HPnow < HPbefore and (*human)->numofhorse >0)
			{
				cout << "���빭Ч��������������������һ�����" << (*human)->horse.name << endl;
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
		cout << "�����˿���" << x << "��Ѫ, �������μ��ܣ���" << xx << "����!" << endl;
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
	cout << "�����˽������״̬��" << endl;
	while (HPnow <= 0 and n<handNUM)
	{
		if (rbt_lst[n].name == "��")
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
		cout << "�����˳ɹ����" << endl;
		if(name->id == 1)delta(get_num_before_bs);
		get_num_before_bs = 0;
	}
	else
	{
		cout << "������������" << endl;
	}

}
