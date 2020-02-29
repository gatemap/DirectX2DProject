#pragma once

class Map
{
protected:
	struct tagObjType {
		Rect*	r;
		D3DXVECTOR2 pos;
		bool	explain = false;
		bool	water = false;
		int		exist = 0;
	};

	struct tagWildField {
		Rect* r;
		D3DXVECTOR2 pos;
		//bool battleField = true;
	};

	struct tagMapType {
		Sprite* s;
		D3DXVECTOR2 pos;
		D3DXVECTOR2 scale;
		tagObjType stObj;
		vector<tagObjType> obj;
		tagWildField field;
		vector<tagWildField> battle;
		bool	bikeRide;
	};

public:
	Map() {};
	~Map() {};
};