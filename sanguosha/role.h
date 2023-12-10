#pragma once
#ifndef _ROLE_H
#define _ROLE_H
class role
{
public:
	//sex:0Å®£¬1ÄÐ
	string name; int id; string skill; int HP; int sex;
	role() {};
	role(int id, string name, string skill, int HP, int sex) :id(id), skill(skill), name(name), HP(HP), sex(sex) {};
};
#endif // !_ROLE_H
