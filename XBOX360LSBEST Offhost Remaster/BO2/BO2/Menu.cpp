//here are the offhost options, overall look and which buttons do what for navigating the offhost and which sub menus it has/how it navigates through those sub menus
//the overall look changes were made by Dev
//I didnt touch the aimbot or other actual cool stuff yet, only the visual look and configured the menu navigation so it fits to XBOX360LSBEST OffHost menu
//the killfeed message thing was ported from Appendum, the only offhost to seemingly have such a special option which also works as non host! It took way longer then it would have needed to port it over... a lot of trial and error...

#include "stdafx.h"
#include <string> //needed for the killfeed printing if you wanna do it via a variable instead of direct text
#include<list> //for my custom little list of option names, i think... 
#include <iostream>


using namespace std;


UIItems_s UIItems;
int SelectedPlayer = -1;

BOOL negativeBoolean = FALSE;
char* aimbotstatus="Aimbot Active";
static bool AntiaimButtonPressed = false;
static bool ESPButtonPressed = false;
char* espstatus="ESP Active";

//how the following works: I got a pointer that goes up in value. The pointer points to a item in a list, the pointed to item will be displayed in the message. If the pointer is higher then the overall list size it gets reset to 0 > goes to the start again
//this seems atleast for me like the easiest way to implement the messages. This can be changed and made more effective if one really wants to.

//aimbot type
char* AimbotTypesList[0x2] = { "Aimbot Type: ^2AutoWall", "Aimbot Type: ^2Visible" };
static int currentIndex = 1;

//silentaim
char* TargetTypesList[0x2] = { "SilentAim: ^1OFF", "SilentAim: ^2ON" };
static int SilentAimIndex = 0;

//aimbone
char* AimTagsList[0x10] = { "AimBone Set To: ^2j_helmet", "AimBone Set To: ^2j_head", "AimBone Set To: ^2j_neck", "AimBone Set To: ^2j_shoulder_le", "AimBone Set To: ^2j_shoulder_ri", "AimBone Set To: ^2j_mainroot", "AimBone Set To: ^2j_elbow_le", "AimBone Set To: ^2j_elbow_ri", "AimBone Set To: ^2j_wrist_le", "AimBone Set To: ^2j_wrist_ri", "AimBone Set To: ^2j_spineupper", "AimBone Set To: ^2j_spinelower", "AimBone Set To: ^2j_knee_le", "AimBone Set To: ^2j_knee_ri", "AimBone Set To: ^2j_ankle_le", "AimBone Set To: ^2j_ankle_ri" };
static int AimboneIndex = 1;

//antiaim
//still need to make the presets actually be correct. Implement next own anti aim methods.
char* SpinbotTypesOutputList[0x7] = { "SpinBot: ^2Z + Y", "SpinBot: ^2Z + Y + High X", "SpinBot: ^2Z + Y + LOW X", "SpinBot: ^2Spin All Angles", "SpinBot: ^2Riot Shield (moon walk)", "SpinBot: ^2Anti-Aim", "SpinBot: ^1OFF" };
static int currentindexAntiaimX = 0;
static int currentindexAntiaimY = 0;




void Menu::ResetVars() {
	UIItems.optionPress = false;
	UIItems.leftPress = false;
	UIItems.rightPress = false;
}
//activate option via a press
int Menu::GetOption() {
	if (UIItems.optionPress)
		
		return UIItems.currentOption;
		
	else
		return 0;
}

Menu::Menu(char* optionText, DWORD font, float fontScale) {
	this->option = optionText;
	this->font = font;
	this->fontScale = fontScale;
}

void Menu::AddOption(char* optionName) {
	UIItems.optionCount++;

	if (UIItems.currentOption <= UIItems.maxOptions && UIItems.optionCount <= UIItems.maxOptions) {
		if (UIItems.currentOption == UIItems.optionCount) {
			Render::DrawShader(UIItems.m_PosX, ((UIItems.m_PosY + 56.0f) + (UIItems.optionCount * 22.0f)), UIItems.m_Width, 22.0f, CG::dwWhite, colorScrollbar);
		}

		Render::DrawText(optionName, (UIItems.m_PosX + 10), ((UIItems.m_PosY + 77.0f) + (UIItems.optionCount * 22.0f)), this->font, this->fontScale, colorWhite);
	}
	else if ((UIItems.optionCount > (UIItems.currentOption - UIItems.maxOptions)) && UIItems.optionCount <= UIItems.currentOption) {
		if (UIItems.currentOption == UIItems.optionCount) {
			Render::DrawShader(UIItems.m_PosX, ((UIItems.m_PosY + 56.0f) + ((UIItems.optionCount - (UIItems.currentOption - UIItems.maxOptions)) * 22.0f)), UIItems.m_Width, 22.0f, CG::dwWhite, colorScrollbar);
		}

		Render::DrawText(optionName, (UIItems.m_PosX + 10), ((UIItems.m_PosY + 77.0f) + ((UIItems.optionCount - (UIItems.currentOption - UIItems.maxOptions)) * 22.0f)), this->font, this->fontScale, colorWhite);
	}
}




inline Menu Menu::Option() {
	AddOption(this->option);

	return *this;
}

inline Menu Menu::Toggle(BOOL* toChange) {
	AddOption(this->option);

	//this gets toggled when one changes a toggle option > need to make a notify instead of the text next to the option
	if (UIItems.currentOption <= UIItems.maxOptions && UIItems.optionCount <= UIItems.maxOptions) {
		Render::DrawString(*toChange ? "" : "", ((UIItems.m_PosX + UIItems.m_Width) - 10.0f), ((UIItems.m_PosY + 77.0f) + (UIItems.optionCount * 22.0f)), this->font, this->fontScale, UIItems.currentOption == UIItems.optionCount ? colorWhite : *toChange ? colorGreen : colorRed, JustifyRight);
	}
	else if ((UIItems.optionCount > (UIItems.currentOption - UIItems.maxOptions)) && UIItems.optionCount <= UIItems.currentOption) {
		Render::DrawString(*toChange ? "" : "", ((UIItems.m_PosX + UIItems.m_Width) - 10.0f), ((UIItems.m_PosY + 77.0f) + ((UIItems.optionCount - (UIItems.currentOption - UIItems.maxOptions)) * 22.0f)), this->font, this->fontScale, UIItems.currentOption == UIItems.optionCount ? colorWhite : *toChange ? colorGreen : colorRed, JustifyRight);
	}

	if (UIItems.currentOption == UIItems.optionCount && UIItems.optionPress) {
		*toChange = !*toChange;
		// Check if the option count is 1 (indicating the button was pressed)
if (UIItems.optionCount == 1 && UIItems.submenu == MAIN_MENU) {
    // Toggle the AntiaimButtonPressed flag
    AntiaimButtonPressed = !AntiaimButtonPressed;

    // Check the state of AntiaimButtonPressed to determine which message to print
    if (AntiaimButtonPressed) {
        // Button was pressed, print the second message
        aimbotstatus = "Aimbot: ^1OFF";
		
    } else {
        // Button was pressed again, print the first message
        aimbotstatus = "Aimbot: ^2ON";
    }

    // Send the appropriate message
    AuthProvider::GetFunction(BO2_MP_TU18_CG_GameMessage)(0, aimbotstatus);
} 

else if (UIItems.optionCount == 2 && UIItems.submenu == MAIN_MENU) {//im manually setting the esp states because i was too lazy to create a own function for that. as Todd Howard once said "It just works."
    // Toggle the AntiaimButtonPressed flag
    ESPButtonPressed = !ESPButtonPressed;

    // Check the state of AntiaimButtonPressed to determine which message to print
    if (ESPButtonPressed) {
        // Button was pressed, print the second message
        espstatus = "ESP: ^1OFF";
		CG::dwESPDrawAxis = FALSE;
		CG::dwESPBoxType = FALSE;
		CG::dwESPBones = FALSE;
		CG::dwESPWeapon = FALSE;
		CG::dwSnaplines = FALSE;
    } else {
        // Button was pressed again, print the first message
        espstatus = "ESP: ^2ON";
		CG::dwESPDrawAxis = TRUE;
		CG::dwESPBoxType = BOX_TYPE_2D;
		CG::dwESPBones = TRUE;
		CG::dwESPWeapon = TRUE;
		CG::dwSnaplines = TRUE;
    }

    // Send the appropriate message
    AuthProvider::GetFunction(BO2_MP_TU18_CG_GameMessage)(0, espstatus);
} 
	} //my special message after a click for any toggles > on or off stuff

	

	return *this;
}

template<typename T>
inline Menu Menu::ArrayEditor(T arr, int* identifier, int len) {
	AddOption(this->option);

	sprintf(this->temp, "[%s]", arr);


	//this would render the text for the options otherwise, not neede in this case
	if (UIItems.currentOption <= UIItems.maxOptions && UIItems.optionCount <= UIItems.maxOptions) {
		//Render::DrawString(this->temp, ((UIItems.m_PosX + UIItems.m_Width) - 10.0f), ((UIItems.m_PosY + 77.0f) + (UIItems.optionCount * 22.0f)), this->font, this->fontScale, colorWhite, JustifyRight);
	}
	else if ((UIItems.optionCount > (UIItems.currentOption - UIItems.maxOptions)) && UIItems.optionCount <= UIItems.currentOption) {
		//Render::DrawString(this->temp, ((UIItems.m_PosX + UIItems.m_Width) - 10.0f), ((UIItems.m_PosY + 77.0f) + ((UIItems.optionCount - (UIItems.currentOption - UIItems.maxOptions)) * 22.0f)), this->font, this->fontScale, colorWhite, JustifyRight);
	}

	if (UIItems.currentOption == UIItems.optionCount && UIItems.optionPress) {//change option if certain key was pressed. here the button is optionPress > "A"
		*identifier -= 1;

		if(UIItems.optionCount==4 && UIItems.submenu == MAIN_MENU){
    AuthProvider::GetFunction(BO2_MP_TU18_CG_GameMessage)(0, AimbotTypesList[currentIndex]);
    
    // Increment the index to point to the next option
    currentIndex++;

    // Loop back to the beginning if we reach the end of the list
    if (currentIndex > 1) {
        currentIndex = 0;
    }
		} 
		else if(UIItems.optionCount==7 && UIItems.submenu == MAIN_MENU){
		AuthProvider::GetFunction(BO2_MP_TU18_CG_GameMessage)(0, TargetTypesList[SilentAimIndex]);
    
    // Increment the index to point to the next option
    SilentAimIndex++;

    // Loop back to the beginning if we reach the end of the list
    if (SilentAimIndex > 1) {
        SilentAimIndex = 0;
    }
	}
		

		else if(UIItems.optionCount==6 && UIItems.submenu == MAIN_MENU){
		AuthProvider::GetFunction(BO2_MP_TU18_CG_GameMessage)(0, AimTagsList[AimboneIndex]);
    
    // Increment the index to point to the next option
    AimboneIndex++;

    // Loop back to the beginning if we reach the end of the list
    if (AimboneIndex > 10) {
        AimboneIndex = 0;
    }
	}

		//this cluster fuck of yandere dev code is just to switch between the different kinds of antiaim configs
		else if(UIItems.optionCount==3 && UIItems.submenu == MAIN_MENU){
			AuthProvider::GetFunction(BO2_MP_TU18_CG_GameMessage)(0, SpinbotTypesOutputList[currentindexAntiaimX]);
    
		CG::dwAntiAim = TRUE;
		CG::dwAntiAimPitch = 2; //SpinBot: ^2Z + Y, meant to be up/down but this isnt the correct index yet, go change it yourself!
		CG::dwAntiAimYaw = 2;//left or right
    // Increment the index to point to the next option
    currentindexAntiaimX++;

    
    if (currentindexAntiaimX == 1) {
        CG::dwAntiAimPitch = 2;//SpinBot: ^2Z + Y High X
		CG::dwAntiAimYaw = 2;
		
    }
	else if(currentindexAntiaimX == 2){
	CG::dwAntiAimPitch = 0;
		CG::dwAntiAimYaw = 2;
		
	}
	else if(currentindexAntiaimX == 3){
	CG::dwAntiAimPitch = 1;
		CG::dwAntiAimYaw = 2;
		
	}
	else if(currentindexAntiaimX == 4){
	CG::dwAntiAimPitch = 2;
		CG::dwAntiAimYaw = 1;
		
	}
	else if(currentindexAntiaimX == 5){
	CG::dwAntiAimPitch = 3;
		CG::dwAntiAimYaw = 0;
	}
	else if(currentindexAntiaimX == 6){
	CG::dwAntiAimPitch = 0;
		CG::dwAntiAimYaw = 0;
	}
	else if(currentindexAntiaimX == 7){
	CG::dwAntiAim = FALSE;
	currentindexAntiaimX=0;// Loop back to the beginning if we reach the end of the list. If we dont then we get a crash, and we wouldnt want that now, did we?
	}
	
	}

		//my custom message for the other options which aint just toggles but rather stuff that gets selected from a list

		
		if (*identifier < 0)
			*identifier = (len - 1);
		
	}

	//change option if certain key was pressed
	//uncheck if you intent to use the dpad buttons
	//if (UIItems.currentOption == UIItems.optionCount && UIItems.rightPress) { 
		//*identifier += 1;
		//if (*identifier > (len - 1))
			//*identifier = 0;
	//}

	return *this;
}

template<typename T>
inline Menu Menu::Editor(T* toEdit, T increments, T min, T max) {
	AddOption(this->option);

	if (is_same<T, float>::value) {
		sprintf(this->temp, "[%.0f]", *toEdit);
	}
	if (is_same<T, unsigned char>::value) {
		sprintf(this->temp, "[%d]", *toEdit);
	}
	if (is_same<T, int>::value) {
		sprintf(this->temp, "[%d]", *toEdit);
	}
	if (std::is_same<T, char*>::value) {
		sprintf(this->temp, "[%s]", *toEdit);
	}

	if (UIItems.currentOption <= UIItems.maxOptions && UIItems.optionCount <= UIItems.maxOptions) {
		Render::DrawString(this->temp, ((UIItems.m_PosX + UIItems.m_Width) - 10.0f), ((UIItems.m_PosY + 77.0f) + (UIItems.optionCount * 22.0f)), this->font, this->fontScale, colorWhite, JustifyRight);
	}
	else if ((UIItems.optionCount > (UIItems.currentOption - UIItems.maxOptions)) && UIItems.optionCount <= UIItems.currentOption) {
		Render::DrawString(this->temp, ((UIItems.m_PosX + UIItems.m_Width) - 10.0f), ((UIItems.m_PosY + 77.0f) + ((UIItems.optionCount - (UIItems.currentOption - UIItems.maxOptions)) * 22.0f)), this->font, this->fontScale, colorWhite, JustifyRight);
	}

	if (UIItems.currentOption == UIItems.optionCount && UIItems.leftPress) {
		*toEdit -= increments;
		if (*toEdit < min)
			*toEdit = max;
	}

	if (UIItems.currentOption == UIItems.optionCount && UIItems.rightPress) {
		*toEdit += increments;
		if (*toEdit > max)
			*toEdit = min;
	}

	return *this;
}

inline Menu Menu::Submenu(int submenu) {
	AddOption(this->option);

	if (UIItems.currentOption == UIItems.optionCount && UIItems.optionPress) {
		UIItems.lastSubmenu[UIItems.submenuLevel] = UIItems.submenu;
		UIItems.lastOption[UIItems.submenuLevel] = UIItems.currentOption;
		UIItems.currentOption = 1;
		UIItems.submenu = submenu;
		UIItems.submenuLevel++;
	}
	return *this;
}

inline Menu Menu::PlayerSubmenu(int submenu) {
	AddOption(this->option);

	if (UIItems.currentOption == UIItems.optionCount && UIItems.optionPress) {
		UIItems.lastSubmenu[UIItems.submenuLevel] = UIItems.submenu;
		UIItems.lastOption[UIItems.submenuLevel] = UIItems.currentOption;
		SelectedPlayer = (UIItems.currentOption - 1);
		UIItems.currentOption = 1;
		UIItems.submenu = submenu;
		UIItems.submenuLevel++;
	}
	return *this;
}

template<typename T>
inline Menu Menu::Callback(T function) {
	if (UIItems.currentOption == UIItems.optionCount && UIItems.optionPress)
		function();
	return *this;
}

template<typename T, typename A>
inline Menu Menu::Callback(T function, A a) {
	if (UIItems.currentOption == UIItems.optionCount && UIItems.optionPress)
		function(a);
	return *this;
}

template<typename T, typename A, typename B>
inline Menu Menu::Callback(T function, A a, B b) {
	if (UIItems.currentOption == UIItems.optionCount && UIItems.optionPress)
		function(a, b);
	return *this;
}

template<typename T, typename A, typename B, typename C>
inline Menu Menu::Callback(T function, A a, B b, C c) {
	if (UIItems.currentOption == UIItems.optionCount && UIItems.optionPress)
		function(a, b, c);
	return *this;
}

inline Menu Menu::ChangeBoolean(BOOL* toChange, BOOL value) {
	if (UIItems.currentOption == UIItems.optionCount && UIItems.optionPress)
		*toChange = value;
	return *this;
}



bool buttonFinished;
void Menu::HandleInput() {
	XINPUT_STATE state;
	XInputGetState(0, &state);
	short button = state.Gamepad.wButtons;

	if (!buttonFinished)
	{
		if (state.Gamepad.bLeftTrigger >= 100 && button & XINPUT_GAMEPAD_RIGHT_THUMB) {
			if (UIItems.submenu == CLOSED) {
				UIItems.lastSubmenu[UIItems.submenuLevel] = UIItems.submenu;
				UIItems.lastOption[UIItems.submenuLevel] = UIItems.currentOption;
				UIItems.currentOption = 1;
				UIItems.submenu = MAIN_MENU;
				UIItems.submenuLevel++;
				UIItems.submenuLevel = 0;
				UIItems.currentOption = 1;
			}

			buttonFinished = true;
		}

		if (button != 0 && UIItems.submenu != CLOSED) {
			if (button & XINPUT_GAMEPAD_A) { //changes what counts to select some option button wise
				UIItems.optionPress = true;
				
			}
			else if (button & XINPUT_GAMEPAD_B) {
				if (UIItems.submenu == MAIN_MENU) {
					UIItems.submenu = CLOSED;
				}
				else {
					if (UIItems.submenu > MAIN_MENU) {
						UIItems.submenu = UIItems.lastSubmenu[UIItems.submenuLevel - 1];
						UIItems.currentOption = UIItems.lastOption[UIItems.submenuLevel - 1];//dev___1_
						UIItems.submenuLevel--;
					}
				}
			}
			else if (button & XINPUT_GAMEPAD_DPAD_UP) {
				UIItems.currentOption--;
				UIItems.currentOption = UIItems.currentOption < 1 ? UIItems.optionCount : UIItems.currentOption;
			}
			else if (button & XINPUT_GAMEPAD_DPAD_DOWN) {
				UIItems.currentOption++;
				UIItems.currentOption = UIItems.currentOption > UIItems.optionCount ? 1 : UIItems.currentOption;
			}
			else if (button & XINPUT_GAMEPAD_DPAD_LEFT) {
				UIItems.leftPress = true;
			}
			else if (button & XINPUT_GAMEPAD_DPAD_RIGHT) {
				UIItems.rightPress = true;
			}

			buttonFinished = true;
		}
	}

	if (button == 0 && buttonFinished) {
		buttonFinished = false;
	}
}
//these are the headings i guess, //22.08.2024 i stil dont know why i needed to fill these with data/why its this order. i know it didnt want to work otherwise but still... why? 
char* tabs[7] = { NULL, "^4XBOX360LSBEST OffHost:", "A", "B", "C", "^4Clients:", "D"};


//this is the sub menu logic, so it knows into which submenu it goes when going though sub menus INSIDE sub menus.
int Menu::ReturnCorrectSubmenu() {
	int currentSub = UIItems.submenu;

	if (currentSub == CLIENT_MANAGER)
		currentSub = CLIENTS;

	return currentSub;
}

void Menu::HandleMenu() {
	UIItems.m_PosX = ((UIItems.dwScreenCenterX - (UIItems.m_Width / 2)));
	UIItems.m_PosY = (UIItems.dwScreenCenterY - (((UIItems.maxOptions * 22.0f) + 40) / 2));

	if (UIItems.submenu > CLOSED) {
		//fixed the large black bar in client list
		float height = (UIItems.maxOptions * 12.5f);

		
		//the background in the different sections of the offhost
		if (UIItems.submenu == MAIN_MENU)
			height = (5 * 22.0f);
		else if (UIItems.submenu == CLIENT_MANAGER)
			height = (4 * 7.0f);
		
		//overall background of the offhost
		Render::DrawShader(UIItems.m_PosX, UIItems.m_PosY, UIItems.m_Width, (height + 160.0f), CG::dwWhite, colorBackground);
		//permanent heading, not needed for us
		//FLOAT textwidth = ((R_TextWidth(0, "XBOX360LSBEST Offhost:", 0x7FFFFFFF, CG::dwSmallFont) / 2) * 1.1f);
		//Render::DrawText("XBOX360LSBEST Offhost:", (UIItems.m_PosX + (UIItems.m_Width / 2) - textwidth), (UIItems.m_PosY + 35.0f), CG::dwSmallFont, 1.1f, colorBlue); //why twice?


		//only need this sub menu for myself
		//atm not a clue why this is here
		if (UIItems.submenu == CLIENT_MANAGER) {
			FLOAT submenuTextLength = ((R_TextWidth(0, netInfo[SelectedPlayer].Gamertag, 0x7FFFFFFF, CG::dwSmallFont) / 2) * 0.95f);
			Render::DrawText(netInfo[SelectedPlayer].Gamertag, (UIItems.m_PosX + (UIItems.m_Width / 2) - submenuTextLength), (UIItems.m_PosY + 63.0f), CG::dwSmallFont, 0.95f, colorBlue);
		
		}//not needed, delete later
		else {
			int currentSub = UIItems.submenu;
			//to go to the correct sub menu if you got multiple sub menus in eachother i guess...
			if (UIItems.submenu > CLIENTS) {
				currentSub = ReturnCorrectSubmenu();
			}

			FLOAT submenuTextLength = ((R_TextWidth(0, tabs[currentSub], 0x7FFFFFFF, CG::dwSmallFont) / 2) * 0.95f);
			Render::DrawText(tabs[currentSub], (UIItems.m_PosX + (UIItems.m_Width / 2) - submenuTextLength), (UIItems.m_PosY + 63.0f), CG::dwSmallFont, 0.95f, colorWhite);
		}

		//the top and bottom line, gone cause i dont need it
		//Render::DrawShader((UIItems.m_PosX + 2.0f), (UIItems.m_PosY + 70.0f), (UIItems.m_Width - 4.0f), 2.0f, CG::dwWhite, colorGrey); //Header grey line
		//Render::DrawShader((UIItems.m_PosX + 2.0f), ((UIItems.m_PosY + 83.0f) + height), (UIItems.m_Width - 4.0f), 2.0f, CG::dwWhite, colorGrey); //Bottom grey line

		//if you delete this shit it kinda glitches out at the bottom of the menu, no clue why lol
		//this is used for the buttons on the menu which appear inside the menu itself. just leave the " empy and this shit aint visible and stops ruining the overall look
		//the shit is actually dumb as you would normally have on the bottom left the instructions anyways, and with this youd have instructions twice... aka its dumb
		char pBottomText[250];

		if (UIItems.submenu == MAIN_MENU) {
			RtlSnprintf(pBottomText, 100, "");
		}
		else {
			RtlSnprintf(pBottomText, 100, "");
		}

		FLOAT submenuTextLength = ((R_TextWidth(0, pBottomText, 0x7FFFFFFF, CG::dwSmallFont) / 2) * 0.85f);
		Render::DrawText(pBottomText, (UIItems.m_PosX + (UIItems.m_Width / 2) - submenuTextLength), (((UIItems.m_PosY + 83.0f) + height) + 30.0f), CG::dwSmallFont, 0.95f, colorWhite);
	}

	UIItems.optionCount = 0;

	switch (UIItems.submenu) {
		//here you basicall determine what the options of the sub menu are
		//i basically only use the MAIN_MENU for the whole offhost because that is enough, exception beeing the clientmanager
	case MAIN_MENU:
		Menu("Toggle Aimbot").Toggle(&CG::dwAimbot);
		Menu("Toggle ESP").Toggle(&CG::dwESPDrawAllies);//only turns off friendly esp but thanks to setting it on click every esp option manually off we deactivate ALL esp stuff lol, its dumb but works lol
		Menu("Toggle SpinBot").ArrayEditor(SpinbotTypesX[CG::dwAntiAimPitch], (int*)&CG::dwAntiAimPitch, ARRAYSIZE(SpinbotTypesX)); //toggle through types and doing so cheeky as i set the type that set currently on click...
		Menu("Toggle AimbotType").ArrayEditor(AimbotTypes[CG::dwAimbotType], (int*)&CG::dwAimbotType, ARRAYSIZE(AimbotTypes));//same as antiaim
		Menu("Toggle FakeLag").Toggle(&CG::customToggleOption); //here is normally the fakelag, need to add fake lag yet, for now a option that does NOTHING
		Menu("Toggle AimBone").ArrayEditor(AimTags[CG::dwAimTag], (int*)&CG::dwAimTag, ARRAYSIZE(AimTags));//same as antiaim
		Menu("Toggle SilentAim").ArrayEditor(TargetTypes[CG::dwTargetType], (int*)&CG::dwTargetType, ARRAYSIZE(TargetTypes));
		//here is a sub menu, you can see this by the term ".Submenu" lol
		//it calls the sub menu we defined before
		Menu("Client List").Submenu(CLIENTS);
		break;


		


		//this is used to get the client names into this section of the menu. its the tab where all players are listed and thus need to grab all current players
		//this shitter is the logic to get those people and uses a basic for loop to go through all players that are in ur lobby and siplays them into the submenu
	case CLIENTS:
		for (int i = 0; i < 18; i++) {
			if (netInfo[i].XUID != 0) {
				Menu(netInfo[i].Gamertag).PlayerSubmenu(CLIENT_MANAGER);
			}
			else {
				Menu("*Invalid Client").Option();//""is the name if the client field is empty
			}
		}
		break;

		//here i define what i want for options inside my sub menu i used in the MAIN_MENU
		//im using only prebuilt options at this point as its enough. im only calling the different functions basically
	case CLIENT_MANAGER:
		Menu("Prioritize Client").Toggle(&pInfo[SelectedPlayer].Prioritized);
		Menu("Dont Shoot Client").Toggle(&pInfo[SelectedPlayer].Whitelisted);
		Menu("Kick Client").Option().Callback(Game::OffhostKick, SelectedPlayer);//kick doesent work for now, its a feature
		Menu("Migrate Client").Option().Callback(Game::GiveMigrationScreen, SelectedPlayer);
		break;

	}
	Menu(NULL).ResetVars();
}

//toggle options, why? no clue yet, and i also dont care for my ce as those options aint needed... except no sway/no recoil...
void Menu::HandleOptions() {
	if (CG::bInGameCached && CG::bLobbyInitialized) {
		Game::ToggleNoRecoil(&CG::NoRecoil);
		Game::ToggleNoSway(&CG::NoSway);
		Game::ToggleVSAT(&CG::VSAT);
		Game::ToggleThirdPerson(&CG::ThirdPerson);
		Game::SetFOV(CG::fFovValue);
	}
}



void Menu::Update() {
	//width of the overall menu and thus also text placement
	UIItems.m_Width = 300;
	//max options visible at a time. its 8 as that was the number of players visible in the client tab
	UIItems.maxOptions = 8;

	Structs::UpdateStructures();

	if (!Game::UserInGame()) {
		for (int i = 0; i < 18; i++) {
			pInfo[i].Whitelisted = FALSE;
			pInfo[i].Prioritized = FALSE;
			pInfo[i].Wallbangable = FALSE;
			pInfo[i].Visible = FALSE;
			pInfo[i].Bone = "";
		}
	}

	HandleInput();
	HandleMenu();
	HandleOptions();


	//this is the notify that happens if you inject the menu. there is a checker box as there is the first "" empty after the "0". here would go a symbol... im so fucking tired right now as I allways do this around 20/21 pm after a workday...
	if (bReadyToNotify) {
		UI_OpenToastPopup(0, "", "XBOX360LSBEST OffHost:", "BO2 Aimbot + ESP Loaded!", 2500);
		*(DWORD*)0x826A5FBC = 0x60000000;//unlimited class items after the notify, you could do more memory editing here, seems to work good enough.
		//nopping all cheat protection, thanks to this source: www.se7ensins.com/forums/threads/bo2-tu18-offsets-list-w-some-bytes.1659296
		*(DWORD*)0x82497EB0 = 0x60000000;
		*(DWORD*)0x82497F30 = 0x60000000;
		*(DWORD*)0x82497EE0 = 0x60000000;
		*(DWORD*)0x82497EC8 = 0x60000000;
		*(DWORD*)0x825996AC = 0x60000000;
		*(DWORD*)0x8259A65C = 0x60000000; //should be all needed ones, please correct me if im wrong, i dont need this just yet, delete if you dont wanna do console commands

		*(DWORD*)0x82003f70 = 0x00000000; //for showing host, doing it just as XBOX360LSBEST did in his shittool
		*(BYTE*)0x83C5A3BB = 0x01; //this sets the show host shit to true
		

		bReadyToNotify = FALSE;
	}

	char* controlsText = nullptr;

	if (UIItems.submenu == CLOSED) {
		controlsText = va("");
	}
	else {
		controlsText = va("");
	}

	FLOAT controlsTextLength = ((R_TextWidth(0, controlsText, 0x7FFFFFFF, CG::dwSmallFont) / 2) * 1.0f);
	Render::DrawText(controlsText, ((UIItems.dwScreenMaxX / 2) - controlsTextLength), (UIItems.dwScreenMaxY - 20.0f), CG::dwSmallFont, 1.0f, colorWhite);
}