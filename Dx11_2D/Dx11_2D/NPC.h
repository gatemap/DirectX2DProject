#pragma once
class NPC
{
	enum class NPCDirect {
		Ready = -1, Face, Left, Right, Back
	};
	struct tagNPCType {
		bool fixed;
		bool fighter;
		Clip* c;
		Sprite* s;
		Animation<NPCDirect>* a;
	};

	map<string, tagNPCType*> npc;

public:
	NPC();
	~NPC();
};