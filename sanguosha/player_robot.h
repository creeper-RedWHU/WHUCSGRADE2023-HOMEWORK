#pragma once
#ifndef _PLAYER_ROBOT_H
#define _PLAYER_ROBOT_H
class robot
{
public:
	robot() ;
	int numOfWeapon = 0, numOfDefencer = 0, handNUM = 0, kill = 0, HPnow, numofhorse = 0, lbssnum = 0, sd = 0;
	robot(role a);
	int get_num_before_bs = 0;
	card weapon, defencer, horse;
	role* name;
	bool lbsse;
	void annother();
	bool judge();
	void play(player* human);
	void finish();
	void init();
	card rbt_lst[50];
	void defence(int n, int colornum);//0:���ӷ���
	bool jd_kill();//�����ĳ�ɱ���оͳ�return true��û�оͿ�Ѫ������false
	bool is_wxkj_used();//������и�ɻ��ͷ���true
	void weapon_kill(player** human, int used);
	void delta(int x);//�ǹ��Σ������յ�x���˺���ʱ�򼤻
	void check_bs();//����״̬�������
};
class player
{
public:
	player();
	int get_num_before_bs = 0;
	int numOfWeapon = 0, numOfDefencer = 0, handNUM = 0, kill = 0, HPnow, numofhorse = 0, lbssnum = 0, sd = 0;
	card weapon, defencer, horse;
	card player_lst[50];
	player(role a);
	role* name;
	bool lbsse = false;
	void annother();//��ʼ�µĻغ�
	bool judge();
	void finish();
	void play(robot* enemy);
	void init();
	//��������ʱ������������ʹ��ɱ
	void weapon_kill(robot** enemy, int used);
	void defence(int n, int colornum);//0:���ӷ���
	bool is_wxkj_used();//������и�ɻ��ͷ���true
	bool jd_kill();//�����ĳ�ɱ���оͳ�return true��û�оͿ�Ѫ������false
	void delta(int x);
	void check_bs();//����״̬�������
};
#endif // !_PLAYER_ROBOT_H
