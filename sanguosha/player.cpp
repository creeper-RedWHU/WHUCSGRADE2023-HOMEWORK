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
	cout << "==========��ҳ������" << endl;
}
void player::finish()
{
	int discard = 0;
	while (HPnow < handNUM)
	{
		cout << "��ǰ��������" << handNUM << ',' << "��ǰѪ����" << HPnow << endl;
		cout << "��ǰ���ƣ�" << endl;
		cout << "���/����/����/��ɫ" << endl;
		for (int i = 0; i < handNUM; i++)
		{
			cout << i + 1 << '/' << player_lst[i].name << '/' << player_lst[i].explain << '/' << color_lst[player_lst[i].colorNUM] << '/' << huase_lst[player_lst[i].huaseNUM] << endl;
		}
		cout << "����" << handNUM - HPnow << "����" << endl;
		cout << "������ȥ�����Ƶ����:";
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
			cout << "��������ȷ��������ţ�" << endl;
		}
	}
	cout << "��ǰ������С�ڵ���Ѫ������������" << endl;
	cout << "��ĻغϽ���" << endl;
	lbsse = false;
	return;
}
bool player::jd_kill()
{
	
	for (int i = 0; i < handNUM; i++)
	{
		if (player_lst[i].name == "ɱ")
		{
			cout << "��⵽����ɱ����0��ɱ����1����ɱ��";
			int a; cin >> a;
			if (a == 0)
			{
				cout << endl << "���ɹ���ɱ��" << endl;
				for (int j = i; j < handNUM - 1; j++)player_lst[j] = player_lst[j + 1];
				handNUM--;
				return true;
			}
			else
			{
				cout << "������ɱ��" << endl;
				return false;
			}
		}
	}
	if (weapon.name == "�ɰ���ì" and handNUM >= 2)
	{
		cout << "�������ƣ�" << endl;
		cout << "���/����/����/��ɫ" << endl; int used = 0;
		for (int i = 0; i < handNUM; i++)
		{
			cout << i + 1 << '/' << player_lst[i].name << '/' << player_lst[i].explain << '/' << color_lst[player_lst[i].colorNUM] << '/' << huase_lst[player_lst[i].huaseNUM] << endl;
		}
		cout << "��⵽����װ���ɰ���ì�������������ڵ���2���Ƿ�ʹ�ã���0ʹ�ã�1����:";
		int aaa; cin >> aaa;
		if (aaa == 0)
		{
			int fa, fb;
			cout << "���붪�����Ƶı�ţ��ÿո��������"; cin >> fa >> fb;
			fa--; fb--;
			if (fa > fb) { int ffc = fa; fa = fb; fb = ffc; }
			pd.push(player_lst[fb]);pd.push(player_lst[fa]);
			for (int i = fb; i < handNUM - 1; i++)player_lst[i] = player_lst[i + 1]; handNUM--;
			for (int i = fa; i < handNUM - 1; i++)player_lst[i] = player_lst[i + 1]; handNUM--;
			cout << "�ɰ���ì�����ɹ���" << endl;
			return true;
		}
		else
		{
			cout << "������ʹ���ɰ���ì��" << endl;
		}
	}
	cout << "���޷���ɱ��" << endl; return false;
}
bool player::judge()
{
	if (HPnow <= 0)  return false;
	else return true;
}
void player::annother()
{
	cout << "��Ļغ�" << endl;
	kill = 0;
	//ÿ�غϿ�ʼǰ��������
	for (int i = 0; i < 2; i++)
	{
		player_lst[handNUM++] = pd.front();
		pd.pop();
	}
	if (lbssnum == 1)
	{
		cout << "���������������ֲ�˼���ж�ʱ��" << endl;
		card ls = pd.front();
		pd.pop();
		pd.push(ls);
		if (ls.colorNUM == 0 and ls.huaseNUM == 2)
		{
			cout << "��ɫΪ���ң��������������ƽ׶Σ�" << endl;
		}
		else
		{
			cout << "��ɫΪ" << color_lst[ls.colorNUM] << huase_lst[ls.huaseNUM] << "�����������ƽ׶Σ�" << endl;
			lbsse = true;
		}
		lbssnum = 0;
	}

}
void player::weapon_kill(robot** enemy, int used)
{
	if(used !=-1)
	{ 
		if (weapon.name == "�������")
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
		else if (weapon.name == "��׽�")
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
		else if (weapon.name == "����˫�ɽ�")
		{
			if ((*enemy)->name->sex != name->sex)
			{
				int choice = rand() % 2;
				if (choice == 0)
				{
					cout << "����˫�ɽ������ɹ���������һ���ƣ�" << endl;
					player_lst[handNUM++] = pd.front();
					pd.pop();
					cout << "�����������ǣ�" << player_lst[handNUM - 1].name << endl;
				}
				else
				{
					cout << "����˫�ɽ������ɹ����û����������һ���ƣ�" << endl;
					int srand = rand() % (*enemy)->handNUM;
					pd.push((*enemy)->rbt_lst[srand]);
					cout << "���������������ǣ�" << (*enemy)->rbt_lst[srand].name << endl;
					for (int i = srand; i < (*enemy)->handNUM - 1; i++)
					{
						(*enemy)->rbt_lst[i] = (*enemy)->rbt_lst[i + 1];
					}
					(*enemy)->handNUM -= 1;
				}
			}
			else
			{
				cout << "����˫�ɽ�������Ч��" << endl;
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
		else if (weapon.name == "������")
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
				cout << "=====������Ч����" << weapon.explain << endl;
				cout << "=====�Ƿ񷢶�������Ч������1��������0ȡ�����Է�����" << (*enemy)->numOfWeapon + (*enemy)->numOfDefencer + (*enemy)->numofhorse + (*enemy)->handNUM << "����)" << endl;
				int func; cin >> func;
				if (func == 0)return;
				else if (func == 1)
				{
					cout << "=====�����ɹ�!������û����������ƣ�����װ������" << endl;
					(*enemy)->HPnow += 1;
					int num = 2;
					int a; int srand;
					if ((*enemy)->numOfWeapon != 0)
					{
						cout << "=====��ǰ��������װ������" << (*enemy)->weapon.name << ",��0���ã���1������:";
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
						cout << "=====��ǰ��������װ������" << (*enemy)->defencer.name << ",��0���ã���1������:";
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
						cout << "=====��ǰ��������װ����" << (*enemy)->horse.name << ",��0���ã���1������:";
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
						cout << "������Ч������" << endl;
						return;
					}
					else
					{
						num = (num <= (*enemy)->handNUM) ? num : (*enemy)->handNUM;
						cout << "���ȥ��������" << num << "����" << endl;
						for (int k = 0; k < num; k++)
						{
							srand = rand() % (*enemy)->handNUM;
							pd.push((*enemy)->rbt_lst[srand]);
							cout << "���������������ǣ�" << (*enemy)->rbt_lst[srand].name << endl;
							for (int i = srand; i < (*enemy)->handNUM - 1; i++)
							{
								(*enemy)->rbt_lst[i] = (*enemy)->rbt_lst[i + 1];
							}
							(*enemy)->handNUM -= 1;
						}
						cout << "������Ч������" << endl;
					}
				}
			}

		}
		else if (weapon.name == "��ʯ��")
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
				if ((*enemy)->defencer.name == "������" and ss.colorNUM == 1)
				{
					cout << "�����˺���������ʯ���޷�����" << endl;
					return;
				}
				else
				{
					cout << "�Ƿ񷢶���ʯ����(������������2)��0������1ȡ����";
					int func; cin >> func;
					if (func == 1 or handNUM < 2)
					{
						cout << "��ȡ��������ʯ����(������С��2)" << endl;
						return;
					}
					else
					{
						cout << "��ǰ���ƣ�" << endl;
						cout << "���/����/����/��ɫ" << endl;
						for (int i = 0; i < handNUM; i++)
						{
							cout << i + 1 << '/' << player_lst[i].name << '/' << player_lst[i].explain << '/' << color_lst[player_lst[i].colorNUM] << '/' << huase_lst[player_lst[i].huaseNUM] << endl;
						}
						cout << endl << "��ʯ�������ɹ�����������Ҫ�������Ƶ���ţ�";
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
						cout << endl << "��ʯ�������ɹ���";
						return;
					}
				}
			}
		}
		else if (weapon.name == "�������µ�")
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
				if ((*enemy)->defencer.name == "������" and pd.back().colorNUM == 1)
				{
					cout << "�����˺��������������µ��޷�������" << endl;
					return;
				}
				cout << "����ʹ���������Ƿ񷢶��������µ�Ч��������ɱ����0��������1�˳�:";
				cin >> func;
				while (func == 0 and (*enemy)->HPnow == HPbefore)
				{
					cout << "��ǰ���ƣ�" << endl;
					cout << "���/����/����/��ɫ" << endl;
					for (int i = 0; i < handNUM; i++)
					{
						cout << i + 1 << '/' << player_lst[i].name << '/' << player_lst[i].explain << '/' << color_lst[player_lst[i].colorNUM] << '/' << huase_lst[player_lst[i].huaseNUM] << endl;
					}
					cout << "����ɱ�����Ƶı�ţ�";
					cin >> pm;
					if (player_lst[pm - 1].name == "ɱ")
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
						cout << "������ɱ�����Ƶı�ţ�" << endl;
					}
					cout << "����ʹ���������Ƿ񷢶��������µ�Ч��������ɱ����0��������1�˳�:";
					cin >> func;

				}
				cout << "�������µ�Ч��������ϣ�" << endl;
			}
		}
		else if (weapon.name == "���컭�")
		{
			cout << "����ģʽ���ƣ�û����Ӹ�������Ч����" << endl;
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
		else if (weapon.name == "���빭")
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
				cout << "���빭Ч�����������ö���һ�����" << (*enemy)->horse.name << endl;
				pd.push((*enemy)->horse);
				(*enemy)->numofhorse = 0;
			}
		}
	}
	else
	{
		if (weapon.name == "�������")(*enemy)->defence(1,pd.back().colorNUM);
		else if (weapon.name == "��׽�")(*enemy)->defence(0, 0);
		else if (weapon.name == "����˫�ɽ�")
		{
			if ((*enemy)->name->sex != name->sex)
			{
				int choice = rand() % 2;
				if (choice == 0)
				{
					cout << "����˫�ɽ������ɹ���������һ���ƣ�" << endl;
					player_lst[handNUM++] = pd.front();
					pd.pop();
					cout << "�����������ǣ�" << player_lst[handNUM - 1].name << endl;
				}
				else
				{
					cout << "����˫�ɽ������ɹ����û����������һ���ƣ�" << endl;
					int srand = rand() % (*enemy)->handNUM;
					pd.push((*enemy)->rbt_lst[srand]);
					cout << "���������������ǣ�" << (*enemy)->rbt_lst[srand].name << endl;
					for (int i = srand; i < (*enemy)->handNUM - 1; i++)
					{
						(*enemy)->rbt_lst[i] = (*enemy)->rbt_lst[i + 1];
					}
					(*enemy)->handNUM -= 1;
				}
			}
			else
			{
				cout << "����˫�ɽ�������Ч��" << endl;
			}
			(*enemy)->defence(1, pd.back().colorNUM);
		}
		else if (weapon.name == "������")
		{
			int HPbefore = (*enemy)->HPnow;
			(*enemy)->defence(1, pd.back().colorNUM);
			if ((*enemy)->HPnow < HPbefore)
			{
				cout << "=====������Ч����" << weapon.explain << endl;
				cout << "=====�Ƿ񷢶�������Ч������1��������0ȡ�����Է�����" << (*enemy)->numOfWeapon + (*enemy)->numOfDefencer + (*enemy)->numofhorse + (*enemy)->handNUM << "����)" << endl;
				int func; cin >> func;
				if (func == 0)return;
				else if (func == 1)
				{
					cout << "=====�����ɹ�!������û����������ƣ�����װ������" << endl;
					(*enemy)->HPnow += 1;
					int num = 2;
					int a; int srand;
					if ((*enemy)->numOfWeapon != 0)
					{
						cout << "=====��ǰ��������װ������" << (*enemy)->weapon.name << ",��0���ã���1������:";
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
						cout << "=====��ǰ��������װ������" << (*enemy)->defencer.name << ",��0���ã���1������:";
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
						cout << "=====��ǰ��������װ����" << (*enemy)->horse.name << ",��0���ã���1������:";
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
						cout << "������Ч������" << endl;
						return;
					}
					else
					{
						num = (num <= (*enemy)->handNUM) ? num : (*enemy)->handNUM;
						cout << "���ȥ��������" << num << "����" << endl;
						for (int k = 0; k < num; k++)
						{
							srand = rand() % (*enemy)->handNUM;
							pd.push((*enemy)->rbt_lst[srand]);
							cout << "���������������ǣ�" << (*enemy)->rbt_lst[srand].name << endl;
							for (int i = srand; i < (*enemy)->handNUM - 1; i++)
							{
								(*enemy)->rbt_lst[i] = (*enemy)->rbt_lst[i + 1];
							}
							(*enemy)->handNUM -= 1;
						}
						cout << "������Ч������" << endl;
					}
				}
			}
		}
		else if (weapon.name == "��ʯ��")
		{
			int HPbefore = (*enemy)->HPnow;
			(*enemy)->defence(1, pd.back().colorNUM);
			if ((*enemy)->HPnow == HPbefore)
			{
				if ((*enemy)->defencer.name == "������" and pd.back().colorNUM== 1)
				{
					cout << "�����˺���������ʯ���޷�����" << endl;
					return;
				}
				else
				{
					cout << "�Ƿ񷢶���ʯ����(������������2)��0������1ȡ����";
					int func; cin >> func;
					if (func == 1 or handNUM < 2)
					{
						cout << "��ȡ��������ʯ����(������С��2)" << endl;
						return;
					}
					else
					{
						cout << "��ǰ���ƣ�" << endl;
						cout << "���/����/����/��ɫ" << endl;
						for (int i = 0; i < handNUM; i++)
						{
							cout << i + 1 << '/' << player_lst[i].name << '/' << player_lst[i].explain << '/' << color_lst[player_lst[i].colorNUM] << '/' << huase_lst[player_lst[i].huaseNUM] << endl;
						}
						cout << endl << "��ʯ�������ɹ�����������Ҫ�������Ƶ���ţ�";
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
						cout << endl << "��ʯ�������ɹ���";
						return;
					}
				}
			}
		}
		else if (weapon.name == "�������µ�")
		{
			int HPbefore = (*enemy)->HPnow;
			(*enemy)->defence(1, pd.back().colorNUM);
			int func = 0; int pm = 0;
			if ((*enemy)->HPnow == HPbefore)
			{
				if ((*enemy)->defencer.name == "������" and pd.back().colorNUM == 1)
				{
					cout << "�����˺��������������µ��޷�������" << endl;
					return;
				}
				cout << "����ʹ���������Ƿ񷢶��������µ�Ч��������ɱ����0��������1�˳�:";
				cin >> func;
				while (func == 0 and (*enemy)->HPnow == HPbefore)
				{
					cout << "��ǰ���ƣ�" << endl;
					cout << "���/����/����/��ɫ" << endl;
					for (int i = 0; i < handNUM; i++)
					{
						cout << i + 1 << '/' << player_lst[i].name << '/' << player_lst[i].explain << '/' << color_lst[player_lst[i].colorNUM] << '/' << huase_lst[player_lst[i].huaseNUM] << endl;
					}
					cout << "����ɱ�����Ƶı�ţ�";
					cin >> pm;
					if (player_lst[pm - 1].name == "ɱ")
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
						cout << "������ɱ�����Ƶı�ţ�" << endl;
					}
					cout << "����ʹ���������Ƿ񷢶��������µ�Ч��������ɱ����0��������1�˳�:";
					cin >> func;

				}
				cout << "�������µ�Ч��������ϣ�" << endl;
			}
		}
		else if (weapon.name == "���컭�")
		{
			cout << "����ģʽ���ƣ�û����Ӹ�������Ч����" << endl;
			(*enemy)->defence(1, pd.back().colorNUM);
		}
		else if (weapon.name == "���빭")
		{
			int HPbefore = (*enemy)->HPnow;
			(*enemy)->defence(1, pd.back().colorNUM);
			if ((*enemy)->HPnow < HPbefore and (*enemy)->numofhorse >0)
			{
				cout << "���빭Ч�����������ö���һ�����" << (*enemy)->horse.name << endl;
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
		if (defencer.name == "������")
		{
			cout << "���������ߣ�������" << endl;
			card cc = pd.front();
			pd.pop();
			pd.push(cc);
			if (cc.colorNUM == 0)
			{
				cout << "��������Ч������Ϊ��" << color_lst[cc.colorNUM] << huase_lst[cc.huaseNUM] << ",����Ϊ����һ����" << endl;
				return;
			}
			else
			{
				cout << "������û��Ч������Ϊ��" << color_lst[cc.colorNUM] << huase_lst[cc.huaseNUM] << endl;
			}
		}
		else if (defencer.name == "������")
		{
			cout << "�����������ܣ�" << endl;
			if (colornum == 1)
			{
				cout << "���������ܵ�Ч������ɫɱ��Ч��" << endl;
				return;
			}
			else
			{
				cout << "�����ܶԺ�ɫɱ��Ч��" << endl;
			}
		}
	}
	cout << "����Ҫ������" << endl;
	cout << "��ǰ���ƣ�" << endl;
	cout << "���/����/����/��ɫ" << endl;
	for (int i = 0; i < handNUM; i++)
	{
		cout << i + 1 << '/' << player_lst[i].name << '/' << player_lst[i].explain << '/' << color_lst[player_lst[i].colorNUM] << '/' << huase_lst[player_lst[i].huaseNUM] << endl;
	}
	cout << "��0��������1�����������û������0Ҳ��Ч������" << endl;
	int a; cin >> a;
	if (a == 1)
	{
		cout << "��û��������һ��Ѫ��" << endl;
		HPnow -= 1;
		if (name->id == 1)delta(1);
		return;
	}
	else
	{
		int i = 0;
		for (i; i < handNUM; i++)if (player_lst[i].name == "��")break;
		if (i == handNUM)
		{
			cout << "��û��������һ��Ѫ" << endl;
			HPnow -= 1;
			if (name->id == 1)delta(1);
			return;
		}
		else
		{
			cout << "����������" << endl;
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
		if (player_lst[i].name == "��и�ɻ�")
		{
			cout << "��⵽������и�ɻ����Ƿ�ʹ�ã���1ʹ�ã�0ȡ��:";
			int a; cin >> a;
			if (a == 1)
			{
				cout << "ʹ����и�ɻ��ɹ��������˵Ľ�����ʧЧ��" << endl;
				pd.push(player_lst[i]);
				for (int j = i; j < handNUM - 1; j++)player_lst[j] = player_lst[j + 1];
				handNUM--;
				if (name->id == 2)
				{
					cout << "����������Ӣ�ļ��ܣ���һ����:" << pd.front().name << endl;
					player_lst[handNUM++] = pd.front();
					pd.pop();
				}
				return true;
			}
			else
			{
				cout << "��ȡ��ʹ����и�ɻ���" << endl;
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
		cout << "������" << x << "��Ѫ, �������μ��ܣ���" << xx << "����!" << endl;
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
	cout << "���������״̬�������Զ�ʹ��ʣ���������" << endl;
	while (HPnow <= 0 and n < handNUM)
	{
		if (player_lst[n].name == "��")
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
		cout << "���ɹ����" << endl;
		if (name->id == 1)delta(get_num_before_bs);
		get_num_before_bs = 0;
	}
	else
	{
		cout << "��������" << endl;
	}
}
