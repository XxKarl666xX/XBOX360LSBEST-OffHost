#pragma once


//here you define the sub menu names, im not sure if the order matters at all
enum Submenu_s {
	CLOSED = 0,
	MAIN_MENU = 1,
	MISCELLANEOUS = 2,
	AIMBOT = 3,
	VISUALS = 4,
	CLIENTS = 5, //this is my "custom" sub menu which can be seen in Menu.cpp at the MAIN_MENU section. any other shit can be deleted...
	CLIENT_MANAGER = 6,
	GAMERTAG_MANAGER = 7,
	SPINBOT_MENU = 8
};

struct UIItems_s {
	int currentOption;
	int maxOptions;
	int optionCount;
	int submenu;
	int submenuLevel;
	int lastSubmenu[20];
	int lastOption[20];
	bool optionPress;
	bool leftPress;
	bool rightPress;

	DWORD dwScreenMaxX, dwScreenMaxY;
	DWORD dwScreenCenterX, dwScreenCenterY;

	float m_PosX, m_PosY, m_Width;
};

class Menu {
private:
	char* option;
	DWORD font;
	float fontScale;

	char temp[50];
public:

	void ResetVars();
	int GetOption();
	Menu(char* optionText = NULL, DWORD font = CG::dwSmallFont, float fontScale = 0.75f);//size of text overall
	void AddOption(char* optionName);
	inline Menu Option();
	inline Menu Toggle(BOOL* toChange);
	template<typename T>
	inline Menu ArrayEditor(T arr, int* identifier, int len);
	template<typename T>
	inline Menu Editor(T* toEdit, T increments, T min, T max);
	inline Menu Submenu(int submenu);
	inline Menu PlayerSubmenu(int submenu);
	template<typename T>
	inline Menu Callback(T function);
	template<typename T, typename A>
	inline Menu Callback(T function, A a);
	template<typename T, typename A, typename B>
	inline Menu Callback(T function, A a, B b);
	template<typename T, typename A, typename B, typename C>
	inline Menu Callback(T function, A a, B b, C c);
	inline Menu ChangeBoolean(BOOL* toChange, BOOL value);
	template<typename T>
	inline Menu SetGamertag(T function);

	static void HandleInput();
	static int ReturnCorrectSubmenu();
	static void HandleMenu();
	static void HandleOptions();
	static void Update();
};

extern UIItems_s UIItems;
extern int SelectedPlayer;