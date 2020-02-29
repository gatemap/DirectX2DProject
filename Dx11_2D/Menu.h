#pragma once

class Menu
{
	Sprite*	selectFrame[9];

	int		menuNum;
	vector<Sprite*> menu;
	bool	menuOn;
public:
	Menu();
	~Menu();

	void Init();
	void Update();
	void Render();

	//Getter& Setter
	bool GetMenuOn() { return menuOn; }
};