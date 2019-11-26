#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Rooms
{
public:
	Rooms(const string& name = "");
	Rooms*GetNorth();
	Rooms*GetSouth();
	Rooms*GetEast();
	Rooms*GetWest();
	void SetNorth(Rooms*next);
	void SetSouth(Rooms*next);
	void SetEast(Rooms*next);
	void SetWest(Rooms*next);

private:
	Rooms* m_pNorth;
	Rooms* m_pSouth;
	Rooms* m_pWest;
	Rooms* m_pEast;

	string m_Name;
	vector<string> RoomInv;

};

Rooms* Rooms::GetNorth()
{
	return m_pNorth;
}
void Rooms::SetNorth(Rooms*next)
{
	m_pNorth = next;
}
void Rooms::SetSouth(Rooms*next)
{
	m_pSouth = next;
}
void Rooms::SetEast(Rooms*next)
{
	m_pEast = next;
}
void Rooms::SetWest(Rooms*next)
{
	m_pWest = next;
}
class Map
{
public:
	Map();
	~Map();
	void RoomInfo();

private:
	Rooms* m_pHead;
};
Map::Map()
{
	Rooms* pNewRoom = new Rooms("Lobby");
	Rooms* pNewRoom2 = new Rooms(" Room1");
	Rooms* pNewRoom3 = new Rooms("Room2");
	Rooms* pNewRoom4 = new Rooms("Room3");
	Rooms* pNewRoom5 = new Rooms("Room4");
	Rooms* pNewRoom6 = new Rooms("Room5");
	Rooms* pNewRoom7 = new Rooms("Room6");
	Rooms* pNewRoom8 = new Rooms("Room7");
	Rooms* pNewRoom9 = new Rooms("Room8");
	Rooms* pNewRoom10 = new Rooms("Room9");


	pNewRoom->SetNorth(pNewRoom5);
	pNewRoom->SetEast(pNewRoom2);
	pNewRoom->SetWest(pNewRoom8);
	pNewRoom2->SetEast(pNewRoom);
	pNewRoom2->SetNorth(pNewRoom3);
	pNewRoom3->SetSouth(pNewRoom2);
	pNewRoom3->SetEast(pNewRoom5);
	pNewRoom3->SetNorth(pNewRoom4);
	pNewRoom4->SetSouth(pNewRoom3);
	pNewRoom4->SetEast(pNewRoom6);
	pNewRoom5->SetSouth(pNewRoom);
	pNewRoom5->SetEast(pNewRoom3);
	pNewRoom5->SetWest(pNewRoom9);
	pNewRoom5->SetNorth(pNewRoom6);
	pNewRoom6->SetSouth(pNewRoom5);
	pNewRoom6->SetEast(pNewRoom4);
	pNewRoom6->SetWest(pNewRoom10);
	pNewRoom6->SetNorth(pNewRoom7);
	pNewRoom7->SetSouth(pNewRoom6);
	pNewRoom8->SetEast(pNewRoom);
	pNewRoom8->SetNorth(pNewRoom9);
	pNewRoom9->SetSouth(pNewRoom8);
	pNewRoom9->SetEast(pNewRoom5);
	pNewRoom9->SetNorth(pNewRoom10);
	pNewRoom10->SetSouth(pNewRoom9);
	pNewRoom10->SetEast(pNewRoom6);
}
class Hero
{
	

public:
	void SetCurRoom(Rooms* next);
	void WalkNorth();
	void WalkSouth();
	void WalkEast();
	void WalkWest();
	
private:
	vector<string> inventory;
	Rooms*CurrRoom;
};

void Hero::SetCurRoom(Rooms*next)
{
	
	CurrRoom = 0;
}

int main()
{
	Rooms myrooms;
	int choice;

	do
	{
		
		cout << "1 - Go north.";
		cout << "2 - Go south.";
		cout << "3 - Go east.";
		cout << "4 - Go west.";
		cin >> choice;

		switch (choice)
		{
		
		case 1: myrooms.GetNorth(); break;
		case 2: myrooms.GetSouth(); break;
		case 3: myrooms.GetEast(); break;
		case 4: myrooms.GetWest(); break;
		}
	} while (choice != 0);
	return 0;
}