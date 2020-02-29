#pragma once
#include "Skill.h"

class Pokemon
{
protected:
	//Psychic : 에스퍼
	enum class POKEMONTYPE {
		Normal, Grass, Poison, Fire, Flying, Water, Bug, Electric,
		Psychic, Ground, Fairy, Fighting, Rock, Steel, Ice, Ghost, Dragon
	};

	//Paralysis : 마비
	enum class POKEMONSTATE {
		Normal, Poison, Freeze, Paralysis, Sleep, Burn
	};

	struct Status {
		int att, def, speed, special;		//공격, 방어, 속도, 특수
	};

	struct PokeComponent {
		int num;					//포켓몬 번호
		POKEMONTYPE type1, type2;	//포켓몬 타입
		POKEMONSTATE state;			//포켓몬 상태
		string name, nick;			//포켓몬 명칭, 별칭
		int	exp, level;				//경험치, 레벨
		//Status status;			//포켓몬 능력치
		float height, weight;		//키, 몸무게
		string explanation;			//포켓몬 설명
		Skill	skill;				//포켓몬 보유 스킬
		bool	wild;				//야생? 트레이너 포켓몬?
	};
public:
	Pokemon();
	~Pokemon();
};

