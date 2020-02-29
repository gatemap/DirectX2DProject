#pragma once
#include "Skill.h"

class Pokemon
{
protected:
	//Psychic : ������
	enum class POKEMONTYPE {
		Normal, Grass, Poison, Fire, Flying, Water, Bug, Electric,
		Psychic, Ground, Fairy, Fighting, Rock, Steel, Ice, Ghost, Dragon
	};

	//Paralysis : ����
	enum class POKEMONSTATE {
		Normal, Poison, Freeze, Paralysis, Sleep, Burn
	};

	struct Status {
		int att, def, speed, special;		//����, ���, �ӵ�, Ư��
	};

	struct PokeComponent {
		int num;					//���ϸ� ��ȣ
		POKEMONTYPE type1, type2;	//���ϸ� Ÿ��
		POKEMONSTATE state;			//���ϸ� ����
		string name, nick;			//���ϸ� ��Ī, ��Ī
		int	exp, level;				//����ġ, ����
		//Status status;			//���ϸ� �ɷ�ġ
		float height, weight;		//Ű, ������
		string explanation;			//���ϸ� ����
		Skill	skill;				//���ϸ� ���� ��ų
		bool	wild;				//�߻�? Ʈ���̳� ���ϸ�?
	};
public:
	Pokemon();
	~Pokemon();
};

