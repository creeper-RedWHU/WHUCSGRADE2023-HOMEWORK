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
	void defence(int n, int colornum);//0:无视防具
	bool jd_kill();//决斗的出杀，有就出return true，没有就扣血并返回false
	bool is_wxkj_used();//有用无懈可击就返回true
	void weapon_kill(player** human, int used);
	void delta(int x);//是郭嘉，而且收到x点伤害的时候激活。
	void check_bs();//濒死状态检包函数
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
	void annother();//开始新的回合
	bool judge();
	void finish();
	void play(robot* enemy);
	void init();
	//有武器的时候调用这个函数使用杀
	void weapon_kill(robot** enemy, int used);
	void defence(int n, int colornum);//0:无视防具
	bool is_wxkj_used();//有用无懈可击就返回true
	bool jd_kill();//决斗的出杀，有就出return true，没有就扣血并返回false
	void delta(int x);
	void check_bs();//濒死状态检包函数
};
#endif // !_PLAYER_ROBOT_H
