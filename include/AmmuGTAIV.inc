/*   |AAAAAAAA| \X\    /X/ |EEEEEEE| |L|        |EEEEEEE| |RRRRR\   |RRRRR\  |EEEEEEE|
	 |A|    |A|  \X\  /X/  |E|       |L|        |E|       |R|  |R|  |R|  |R| |E|
	 |A|    |A|   \X\/X/   |E|       |L|        |E|       |R|  |R|  |R|  |R| |E|
	 |AAAAAAAA|     |X|    |EEEEEE|  |L|        |EEEEEE|  |RRRRR/   |RRRRR/  |EEEEEE|
	 |A|    |A|   /X/\X\   |E|       |L|        |E|       |R| R\    |R| R\   |E|
	 |A|    |A|  /X/  \X\  |E|       |L|        |E|       |R|  R\   |R|  R\  |E|
	 |A|    |A| /X/    \X\ |EEEEEEE| |LLLLLLLL| |EEEEEEE| |R|   R\  |R|   R\ |EEEEEEE|      [FR]

 _________________________________________
||                                       ||
||        [FILTERSCRIPT] - GAMEMODE      ||
||              **********               ||
||  Name   : Ammu-nation GTA IV [English]||
||  For    : SA-MP 0.3d +                ||
||  Author : Axel Jallet aka Axelerre    ||
||                                       ||
||***************************************||
||***************************************||
||                                       ||
||   Don't remove the credits, please.   ||
||   If you modify this file, you don't  ||
||   allowed to redistribute this.       ||
||                                       ||
|| Otherwise, redistribute this any way  ||
||     you want and where you want !     ||
||                                       ||
||                ENJOY !                ||
||_______________________________________|*/
#include <a_samp>

/***** Streamer Configuration *****/
//#include <streamer> 			// Comment this line for desactivate the plugin
//#define ActivateStreamer false	// Change "true" to "false" if you don't want use Streamer
/*********************************/
#define PRESSED(%0) \
	(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
/******************************
********** TextDraws **********
******************************/
// Press KEY for see this weapon
new Text:AmmuMessage;
new Text:Background;
// Overview
new Text:AmmuBackgroundOverview;
new Text:InformationsOverview[BRAZUCAS_PLAYERS];
new Text:AmmuBuyText;
new Text:AmmuCancelText;
// Not Enough money
new Text:AmmuBackgroundNotEnough;
new Text:TextNotEnough1;
//new Text:TextNotEnough2;
new Text:TextNotLicense;
// Weapon comprada
new Text:AmmuBackgroundGunBought;
//new Text:InformationsOverview[playerid];
/******************************
****** Weapons Positions ******
******************************/
new Float:GunPlace[13][3]={
	{310.8896,-164.0021,999.5938}, // Silenced Pistol
	{309.3380,-162.9703,999.5938}, // Desert Eagle
	{309.0084,-161.7964,999.5938}, // Colt45
	{310.9264,-160.6841,999.5938}, // MP5
	{312.4876,-162.4639,999.5938}, // Escopeta
	{313.6749,-162.1720,999.5938}, // Taco de baseball
	{315.0990,-160.9105,999.5938}, // Sniper
	{316.5237,-162.3037,999.5938}, // M4
	{314.9391,-163.7813,999.5938}, // AK-47
	{310.9412,-165.7379,999.6010}, // Lanca Misseis
	{317.9167,-160.1454,999.5938}, // Colete
	{318.2814,-163.3776,999.6010}, // Grenade
	{318.2234,-161.9250,999.5938}  // Molotov
};
/******************************
************* News ************
******************************/
new PlayerLookAtGun[BRAZUCAS_PLAYERS];
new Overview[BRAZUCAS_PLAYERS];
new Timer[BRAZUCAS_PLAYERS];
/******************************
*********** Forwards **********
******************************/
forward CheckForPlayerPos(playerid);
forward PlayerToPointStripped(Float:radi, playerid, Float:x, Float:y, Float:z, Float:curx, Float:cury, Float:curz);
//==============================================================================
stock InitAmmuGTAIV()
{
	CreateObject(346, 309.98, -161.68, 999.62,   -90.00, 0.00, 262.96);
	CreateObject(348, 310.01, -162.69, 999.60,   -90.00, 0.00, 270.00);
	CreateObject(347, 310.64, -163.15, 999.62,   -90.00, 0.00, -5.00);
	CreateObject(349, 311.56, -162.50, 999.67,   -90.00, -360.00, 76.00);
	CreateObject(2038, 311.43, -162.07, 999.56,   90.00, 0.00, 0.00);
	CreateObject(353, 310.81, -161.44, 999.60,   90.00, 0.00, -4.00);
	CreateObject(2038, 310.54, -161.51, 999.58,   90.00, 0.00, 0.00);
	CreateObject(2038, 311.43, -162.07, 999.60,   90.00, 0.00, 0.00);
	CreateObject(355, 314.85, -163.16, 999.63,   -90.00, 0.00, 0.00);
	CreateObject(2038, 322.45, -177.21, 999.56,   90.00, 0.00, 0.00);
	CreateObject(2038, 315.36, -163.06, 999.56,   90.00, 0.00, 0.00);
	CreateObject(356, 315.83, -162.60, 999.60,   -90.00, 0.00, 90.00);
	CreateObject(2038, 315.77, -162.10, 999.54,   90.00, 0.00, 0.00);
	CreateObject(358, 314.77, -161.49, 999.62,   90.00, 0.00, 0.00);
	CreateObject(2038, 314.72, -161.55, 999.58,   90.00, 0.00, 0.00);
	CreateObject(336, 314.30, -162.01, 999.60,   90.00, 0.00, 0.00);
	CreateObject(2038, 314.32, -162.15, 999.56,   90.00, 0.00, 0.00);
	CreateObject(359, 311.29, -166.83, 999.60,   90.00, 0.00, 0.00);
	CreateObject(342, 318.93, -163.00, 999.75,   90.00, 0.00, 0.00);
	CreateObject(342, 319.24, -163.40, 999.75,   90.00, 0.00, 69.00);
	CreateObject(342, 319.24, -163.50, 999.75,   90.00, 0.00, 69.00);
	CreateObject(342, 319.24, -163.62, 999.75,   90.00, 0.00, 69.00);
	CreateObject(342, 319.08, -163.38, 999.75,   90.00, 0.00, 69.00);
	CreateObject(342, 319.08, -163.50, 999.75,   90.00, 0.00, 69.00);
	CreateObject(342, 319.08, -163.60, 999.75,   90.00, 0.00, 69.00);
	CreateObject(342, 318.92, -163.60, 999.75,   90.00, 0.00, 69.00);
	CreateObject(342, 318.92, -163.48, 999.75,   90.00, 0.00, 69.00);
	CreateObject(342, 318.92, -163.36, 999.75,   90.00, 0.00, 69.00);
	CreateObject(344, 318.85, -161.39, 999.96,   0.00, 0.00, 0.00);
	CreateObject(344, 319.25, -161.77, 999.96,   0.00, 0.00, 0.00);
	CreateObject(344, 319.24, -161.89, 999.96,   0.00, 0.00, 0.00);
	CreateObject(344, 319.25, -161.99, 999.96,   0.00, 0.00, 0.00);
	CreateObject(344, 319.11, -161.98, 999.96,   0.00, 0.00, 0.00);
	CreateObject(344, 319.14, -161.86, 999.96,   0.00, 0.00, 0.00);
	CreateObject(344, 319.13, -161.76, 999.96,   0.00, 0.00, 0.00);
	CreateObject(344, 318.99, -161.75, 999.96,   0.00, 0.00, 0.00);
	CreateObject(344, 318.98, -161.89, 999.96,   0.00, 0.00, 0.00);
	CreateObject(344, 318.97, -161.99, 999.96,   0.00, 0.00, 0.00);
	CreateObject(373, 318.94, -160.12, 1000.23,   -30.00, -55.00, 186.00);
	//#endif

	// "Press VEHICLE_ENTER_EXIT for see this weapon" message
	AmmuMessage = TextDrawCreate(498.000000, 22.000000 + 278.0, "Pressione ~k~~VEHICLE_ENTER_EXIT~~n~para ver esta arma.");
	TextDrawBackgroundColor(AmmuMessage, 255);
	TextDrawFont(AmmuMessage, 2);
	TextDrawLetterSize(AmmuMessage, 0.230000, 1.000000);
	TextDrawColor(AmmuMessage, -1);
	TextDrawSetOutline(AmmuMessage, 0);
	TextDrawSetProportional(AmmuMessage, 1);
	TextDrawSetShadow(AmmuMessage, 1);

	Background = TextDrawCreate(496.000000, 18.000000 + 278.0, ".");
	TextDrawBackgroundColor(Background, 255);
	TextDrawFont(Background, 1);
	TextDrawLetterSize(Background, 0.500000, 4.200000);
	TextDrawColor(Background, 0);
	TextDrawSetOutline(Background, 0);
	TextDrawSetProportional(Background, 1);
	TextDrawSetShadow(Background, 0);
	TextDrawUseBox(Background, 1);
	TextDrawBoxColor(Background, 180);
	TextDrawTextSize(Background, 614.000000, 0.000000);

	// Overview
	AmmuBackgroundOverview = TextDrawCreate(487.000000, 10.000000 + 278.0, ".");
	TextDrawBackgroundColor(AmmuBackgroundOverview, 0);
	TextDrawFont(AmmuBackgroundOverview, 1);
	TextDrawLetterSize(AmmuBackgroundOverview, 0.500000, 5.399999);
	TextDrawColor(AmmuBackgroundOverview, 0);
	TextDrawSetOutline(AmmuBackgroundOverview, 0);
	TextDrawSetProportional(AmmuBackgroundOverview, 1);
	TextDrawSetShadow(AmmuBackgroundOverview, 0);
	TextDrawUseBox(AmmuBackgroundOverview, 1);
	TextDrawBoxColor(AmmuBackgroundOverview, 170);
	TextDrawTextSize(AmmuBackgroundOverview, 624.000000, 0.000000);

	for(new playerid=0;playerid<BRAZUCAS_PLAYERS;playerid++){
		InformationsOverview[playerid] = TextDrawCreate(490.000000, 40.000000 + 278.0, "Arma - Preço (R$)");
		TextDrawBackgroundColor(InformationsOverview[playerid], 255);
		TextDrawFont(InformationsOverview[playerid], 2);
		TextDrawLetterSize(InformationsOverview[playerid], 0.270000, 1.000000);
		TextDrawColor(InformationsOverview[playerid], 378079999);
		TextDrawSetOutline(InformationsOverview[playerid], 0);
		TextDrawSetProportional(InformationsOverview[playerid], 1);
		TextDrawSetShadow(InformationsOverview[playerid], 1);
	}

	AmmuBuyText = TextDrawCreate(491.000000, 15.000000 + 278.0, "Pressione ~k~~CONVERSATION_YES~ para comprar.");
	TextDrawBackgroundColor(AmmuBuyText, 255);
	TextDrawFont(AmmuBuyText, 2);
	TextDrawLetterSize(AmmuBuyText, 0.220000, 1.200000);
	TextDrawColor(AmmuBuyText, -1);
	TextDrawSetOutline(AmmuBuyText, 0);
	TextDrawSetProportional(AmmuBuyText, 1);
	TextDrawSetShadow(AmmuBuyText, 1);

	AmmuCancelText = TextDrawCreate(491.000000, 27.000000 + 278.0, "Pressione ~k~~CONVERSATION_NO~ para cancelar.");
	TextDrawBackgroundColor(AmmuCancelText, 255);
	TextDrawFont(AmmuCancelText, 2);
	TextDrawLetterSize(AmmuCancelText, 0.220000, 1.200000);
	TextDrawColor(AmmuCancelText, -1);
	TextDrawSetOutline(AmmuCancelText, 0);
	TextDrawSetProportional(AmmuCancelText, 1);
	TextDrawSetShadow(AmmuCancelText, 1);

	// Not Enough Money
	AmmuBackgroundNotEnough = TextDrawCreate(487.000000, 11.000000 + 278.0, ".");
	TextDrawBackgroundColor(AmmuBackgroundNotEnough, 0);
	TextDrawFont(AmmuBackgroundNotEnough, 1);
	TextDrawLetterSize(AmmuBackgroundNotEnough, 0.500000, 6.199998);
	TextDrawColor(AmmuBackgroundNotEnough, 0);
	TextDrawSetOutline(AmmuBackgroundNotEnough, 0);
	TextDrawSetProportional(AmmuBackgroundNotEnough, 1);
	TextDrawSetShadow(AmmuBackgroundNotEnough, 0);
	TextDrawUseBox(AmmuBackgroundNotEnough, 1);
	TextDrawBoxColor(AmmuBackgroundNotEnough, 170);
	TextDrawTextSize(AmmuBackgroundNotEnough, 624.000000, 0.000000);

	TextNotEnough1 = TextDrawCreate(490.000000, 40.000000 + 278.0, "Voce nao tem dinheiro suficiente~n~comprar esta arma");
	TextDrawBackgroundColor(TextNotEnough1, 255);
	TextDrawFont(TextNotEnough1, 2);
	TextDrawLetterSize(TextNotEnough1, 0.160000, 1.300000);
	TextDrawColor(TextNotEnough1, 378079999);
	TextDrawSetOutline(TextNotEnough1, 0);
	TextDrawSetProportional(TextNotEnough1, 1);
	TextDrawSetShadow(TextNotEnough1, 1);

	/*TextNotEnough2 = TextDrawCreate(490.000000, 51.000000 + 278.0, "para comprar esta arma");
	TextDrawBackgroundColor(TextNotEnough2, 255);
	TextDrawFont(TextNotEnough2, 2);
	TextDrawLetterSize(TextNotEnough2, 0.170000, 1.300000);
	TextDrawColor(TextNotEnough2, 378079999);
	TextDrawSetOutline(TextNotEnough2, 0);
	TextDrawSetProportional(TextNotEnough2, 1);
	TextDrawSetShadow(TextNotEnough2, 1);*/

	TextNotLicense = TextDrawCreate(490.000000, 40.000000 + 278.0, "Voce nao tem licensa para~n~comprar esta arma");
	TextDrawBackgroundColor(TextNotLicense, 255);
	TextDrawFont(TextNotLicense, 2);
	TextDrawLetterSize(TextNotLicense, 0.170000, 1.300000);
	TextDrawColor(TextNotLicense, 378079999);
	TextDrawSetOutline(TextNotLicense, 0);
	TextDrawSetProportional(TextNotLicense, 1);
	TextDrawSetShadow(TextNotLicense, 1);

	// Weapon comprada
	AmmuBackgroundGunBought = TextDrawCreate(487.000000, 11.000000 + 278.0, ".");
	TextDrawBackgroundColor(AmmuBackgroundGunBought, 0);
	TextDrawFont(AmmuBackgroundGunBought, 1);
	TextDrawLetterSize(AmmuBackgroundGunBought, 0.500000, 5.499999);
	TextDrawColor(AmmuBackgroundGunBought, 0);
	TextDrawSetOutline(AmmuBackgroundGunBought, 0);
	TextDrawSetProportional(AmmuBackgroundGunBought, 1);
	TextDrawSetShadow(AmmuBackgroundGunBought, 0);
	TextDrawUseBox(AmmuBackgroundGunBought, 1);
	TextDrawBoxColor(AmmuBackgroundGunBought, 170);
	TextDrawTextSize(AmmuBackgroundGunBought, 624.000000, 0.000000);

	return 1;
}

stock ExitAmmuGTAIV()
{
	TextDrawHideForAll(AmmuMessage);
	TextDrawDestroy(AmmuMessage);
	TextDrawHideForAll(Background);
	TextDrawDestroy(Background);
	TextDrawHideForAll(AmmuBackgroundOverview);
	TextDrawDestroy(AmmuBackgroundOverview);
	for(new playerid=0;playerid<BRAZUCAS_PLAYERS;playerid++) TextDrawHideForAll(InformationsOverview[playerid]),TextDrawDestroy(InformationsOverview[playerid]);
	TextDrawHideForAll(AmmuBuyText);
	TextDrawDestroy(AmmuBuyText);
	TextDrawHideForAll(AmmuCancelText);
	TextDrawDestroy(AmmuCancelText);
	TextDrawHideForAll(AmmuBackgroundNotEnough);
	TextDrawDestroy(AmmuBackgroundNotEnough);
	TextDrawHideForAll(TextNotEnough1);
	TextDrawDestroy(TextNotEnough1);
	//TextDrawHideForAll(TextNotEnough2);
	//TextDrawDestroy(TextNotEnough2);
	TextDrawHideForAll(TextNotLicense);
	TextDrawDestroy(TextNotLicense);
	TextDrawHideForAll(AmmuBackgroundGunBought);
	TextDrawDestroy(AmmuBackgroundGunBought);
	return 1;
}

forward OnPlayerEnterAmmuGTAIV(playerid);
public OnPlayerEnterAmmuGTAIV(playerid)
{
	RemoveBuildingForPlayer(playerid, 1885, 310.1250, -166.2109, 998.5547, 0.25);
	RemoveBuildingForPlayer(playerid, 1885, 315.2422, -169.8984, 998.5547, 0.25);
	RemoveBuildingForPlayer(playerid, 18105, 312.9844, -163.2500, 1000.5547, 0.25);
	RemoveBuildingForPlayer(playerid, 1886, 318.8047, -158.9297, 1003.2266, 0.25);
	Timer[playerid]=SetTimerEx("CheckForPlayerPos", 100, 1, "i", playerid);
	return 1;
}

forward OnPlayerExitAmmuGTAIV(playerid);
public OnPlayerExitAmmuGTAIV(playerid)
{
	KillTimer(Timer[playerid]);
	return 1;
}

public CheckForPlayerPos(playerid)
{
	new Float:cx, Float:cy, Float:cz;
	GetPlayerPos(playerid, cx, cy, cz);

	if(PlayerToPointStripped(0.5, playerid, GunPlace[0][0],GunPlace[0][1],GunPlace[0][2], cx, cy ,cz) || PlayerToPointStripped(0.5, playerid, GunPlace[1][0],GunPlace[1][1],GunPlace[1][2], cx, cy ,cz) || PlayerToPointStripped(0.5, playerid, GunPlace[2][0],GunPlace[2][1],GunPlace[2][2], cx, cy ,cz) || PlayerToPointStripped(0.5, playerid, GunPlace[3][0],GunPlace[3][1],GunPlace[3][2], cx, cy ,cz) || PlayerToPointStripped(0.5, playerid, GunPlace[4][0],GunPlace[4][1],GunPlace[4][2], cx, cy ,cz))
	{
		if (PlayerLookAtGun[playerid] == 0)
		{
			TextDrawShowForPlayer(playerid,AmmuMessage);
			TextDrawShowForPlayer(playerid,Background);
		}
	}
	else if(PlayerToPointStripped(0.5, playerid, GunPlace[5][0],GunPlace[5][1],GunPlace[5][2], cx, cy ,cz) || PlayerToPointStripped(0.5, playerid, GunPlace[6][0],GunPlace[6][1],GunPlace[6][2], cx, cy ,cz) || PlayerToPointStripped(0.5, playerid, GunPlace[7][0],GunPlace[7][1],GunPlace[7][2], cx, cy ,cz) || PlayerToPointStripped(0.5, playerid, GunPlace[8][0],GunPlace[8][1],GunPlace[8][2], cx, cy ,cz) || PlayerToPointStripped(0.5, playerid, GunPlace[9][0],GunPlace[9][1],GunPlace[9][2], cx, cy ,cz))
	{
		if (PlayerLookAtGun[playerid] == 0)
		{
			TextDrawShowForPlayer(playerid,AmmuMessage);
			TextDrawShowForPlayer(playerid,Background);
		}
	}
	else if(PlayerToPointStripped(0.5, playerid, GunPlace[10][0],GunPlace[10][1],GunPlace[10][2], cx, cy ,cz) || PlayerToPointStripped(0.5, playerid, GunPlace[11][0],GunPlace[11][1],GunPlace[11][2], cx, cy ,cz) || PlayerToPointStripped(0.5, playerid, GunPlace[12][0],GunPlace[12][1],GunPlace[12][2], cx, cy ,cz))
	{
		if (PlayerLookAtGun[playerid] == 0)
		{
			TextDrawShowForPlayer(playerid,AmmuMessage);
			TextDrawShowForPlayer(playerid,Background);
		}
	}
	else
	{
		TextDrawHideForPlayer(playerid,AmmuMessage);
		TextDrawHideForPlayer(playerid,Background);
	}
	return 1;
}

forward OnPlayerKeyStateChangeAmmuGTAIV(playerid, newkeys, oldkeys);
public OnPlayerKeyStateChangeAmmuGTAIV(playerid, newkeys, oldkeys)
{
	if (PRESSED(KEY_SECONDARY_ATTACK))
	{
	    if ((Overview[playerid] == 1) && (PlayerLookAtGun[playerid] == 1))
	    {// If the player is already in the overview, it can't open a copy of TextDraws "Overview".
	    	if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[0][0],GunPlace[0][1],GunPlace[0][2]))
			{
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[1][0],GunPlace[1][1],GunPlace[1][2]))
			{
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[2][0],GunPlace[2][1],GunPlace[2][2]))
			{
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[3][0],GunPlace[3][1],GunPlace[3][2]))
			{
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[4][0],GunPlace[4][1],GunPlace[4][2]))
			{
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[5][0],GunPlace[5][1],GunPlace[5][2]))
			{
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[6][0],GunPlace[6][1],GunPlace[6][2]))
			{
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[7][0],GunPlace[7][1],GunPlace[7][2]))
			{
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[8][0],GunPlace[8][1],GunPlace[8][2]))
			{
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[9][0],GunPlace[9][1],GunPlace[9][2]))
			{
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[10][0],GunPlace[10][1],GunPlace[10][2]))
			{
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[11][0],GunPlace[11][1],GunPlace[11][2]))
			{
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[12][0],GunPlace[12][1],GunPlace[12][2]))
			{
			}
		}
		else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[0][0],GunPlace[0][1],GunPlace[0][2]))
		{
		    PlayerLookAtGun[playerid] = 1;
		    Overview[playerid] = 1;
 			TextDrawHideForPlayer(playerid,AmmuMessage);
			TextDrawHideForPlayer(playerid,Background);

			TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
			TextDrawSetString(InformationsOverview[playerid], "Colt45 Silenced R$ 1500");
			TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
			TextDrawShowForPlayer(playerid,AmmuBuyText);
			TextDrawShowForPlayer(playerid,AmmuCancelText);

			SetPlayerCameraPos(playerid, 312.8142, -164.1690, 1001.0139);
			SetPlayerCameraLookAt(playerid, 311.8848, -163.8041, 1000.4543);
			TogglePlayerControllable(playerid, 0);
			ApplyAnimation(playerid, "WEAPONS","SHP_Tray_Pose",1,1,0,0,0,0,1);
		}
		else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[1][0],GunPlace[1][1],GunPlace[1][2]))
		{
		    PlayerLookAtGun[playerid] = 1;
		    Overview[playerid] = 1;
 			TextDrawHideForPlayer(playerid,AmmuMessage);
			TextDrawHideForPlayer(playerid,Background);

			TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
			TextDrawSetString(InformationsOverview[playerid], "Desert Eagle R$ 2000");
			TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
			TextDrawShowForPlayer(playerid,AmmuBuyText);
			TextDrawShowForPlayer(playerid,AmmuCancelText);

			SetPlayerCameraPos(playerid, 309.0642, -164.6705, 1000.6103);
			SetPlayerCameraLookAt(playerid, 309.3775, -163.7225, 1000.1202);
			TogglePlayerControllable(playerid, 0);
			ApplyAnimation(playerid, "WEAPONS","SHP_Tray_Pose",1,1,0,0,0,0,1);
		}
		else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[2][0],GunPlace[2][1],GunPlace[2][2]))
		{
		    PlayerLookAtGun[playerid] = 1;
		    Overview[playerid] = 1;
 			TextDrawHideForPlayer(playerid,AmmuMessage);
			TextDrawHideForPlayer(playerid,Background);

			TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
			TextDrawSetString(InformationsOverview[playerid], "Colt 45 R$ 1000");
			TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
			TextDrawShowForPlayer(playerid,AmmuBuyText);
			TextDrawShowForPlayer(playerid,AmmuCancelText);

			SetPlayerCameraPos(playerid, 309.2014, -163.4594, 1000.9352);
			SetPlayerCameraLookAt(playerid, 309.5013, -162.5071, 1000.3002);
			TogglePlayerControllable(playerid, 0);
			ApplyAnimation(playerid, "WEAPONS","SHP_Tray_Pose",1,1,0,0,0,0,1);
		}
		else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[3][0],GunPlace[3][1],GunPlace[3][2]))
		{
		    PlayerLookAtGun[playerid] = 1;
		    Overview[playerid] = 1;
 			TextDrawHideForPlayer(playerid,AmmuMessage);
			TextDrawHideForPlayer(playerid,Background);

			TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
			TextDrawSetString(InformationsOverview[playerid], "MP5 R$ 3500");
			TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
			TextDrawShowForPlayer(playerid,AmmuBuyText);
			TextDrawShowForPlayer(playerid,AmmuCancelText);

			SetPlayerCameraPos(playerid, 309.2686, -160.5763, 1000.5763);
			SetPlayerCameraLookAt(playerid, 310.1933, -160.9525, 1000.0511);
			TogglePlayerControllable(playerid, 0);
			ApplyAnimation(playerid, "WEAPONS","SHP_Tray_Pose",1,1,0,0,0,0,1);
		}
		else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[4][0],GunPlace[4][1],GunPlace[4][2]))
		{
		    PlayerLookAtGun[playerid] = 1;
		    Overview[playerid] = 1;
 			TextDrawHideForPlayer(playerid,AmmuMessage);
			TextDrawHideForPlayer(playerid,Background);

			TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
			TextDrawSetString(InformationsOverview[playerid], "Escopeta R$ 2400");
			TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
			TextDrawShowForPlayer(playerid,AmmuBuyText);
			TextDrawShowForPlayer(playerid,AmmuCancelText);

			SetPlayerCameraPos(playerid, 312.1643, -163.9323, 1000.6484);
			SetPlayerCameraLookAt(playerid, 311.9574, -162.9554, 1000.1144);
			TogglePlayerControllable(playerid, 0);
			ApplyAnimation(playerid, "WEAPONS","SHP_Tray_Pose",1,1,0,0,0,0,1);
		}
		else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[5][0],GunPlace[5][1],GunPlace[5][2]))
		{
  			PlayerLookAtGun[playerid] = 1;
  			Overview[playerid] = 1;
 			TextDrawHideForPlayer(playerid,AmmuMessage);
			TextDrawHideForPlayer(playerid,Background);

			TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
			TextDrawSetString(InformationsOverview[playerid], "Taco de baseball R$ 500");
			TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
			TextDrawShowForPlayer(playerid,AmmuBuyText);
			TextDrawShowForPlayer(playerid,AmmuCancelText);

			SetPlayerCameraPos(playerid, 313.4363, -164.2698, 1000.7707);
			SetPlayerCameraLookAt(playerid, 313.7400, -163.3189, 1000.2609);
			TogglePlayerControllable(playerid, 0);
			ApplyAnimation(playerid, "WEAPONS","SHP_Tray_Pose",1,1,0,0,0,0,1);
		}
		else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[6][0],GunPlace[6][1],GunPlace[6][2]))
		{
		    PlayerLookAtGun[playerid] = 1;
		    Overview[playerid] = 1;
 			TextDrawHideForPlayer(playerid,AmmuMessage);
			TextDrawHideForPlayer(playerid,Background);

			TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
			TextDrawSetString(InformationsOverview[playerid], "Rifle Sniper R$ 4000");
			TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
			TextDrawShowForPlayer(playerid,AmmuBuyText);
			TextDrawShowForPlayer(playerid,AmmuCancelText);

			SetPlayerCameraPos(playerid, 312.7876, -160.6851, 1000.8149);
			SetPlayerCameraLookAt(playerid, 313.7592, -160.9130, 1000.3099);
			TogglePlayerControllable(playerid, 0);
			ApplyAnimation(playerid, "WEAPONS","SHP_Tray_Pose",1,1,0,0,0,0,1);
		}
		else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[7][0],GunPlace[7][1],GunPlace[7][2]))
		{
		    PlayerLookAtGun[playerid] = 1;
		    Overview[playerid] = 1;
 			TextDrawHideForPlayer(playerid,AmmuMessage);
			TextDrawHideForPlayer(playerid,Background);

			TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
			TextDrawSetString(InformationsOverview[playerid], "M4 R$ 2800");
			TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
			TextDrawShowForPlayer(playerid,AmmuBuyText);
			TextDrawShowForPlayer(playerid,AmmuCancelText);

			SetPlayerCameraPos(playerid, 316.6902, -160.3435, 1000.7562);
			SetPlayerCameraLookAt(playerid, 316.4340, -161.3082, 1000.2211);
			TogglePlayerControllable(playerid, 0);
   			ApplyAnimation(playerid, "WEAPONS","SHP_Tray_Pose",1,1,0,0,0,0,1);
		}
		else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[8][0],GunPlace[8][1],GunPlace[8][2]))
		{
		    PlayerLookAtGun[playerid] = 1;
		    Overview[playerid] = 1;
 			TextDrawHideForPlayer(playerid,AmmuMessage);
			TextDrawHideForPlayer(playerid,Background);

			TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
			TextDrawSetString(InformationsOverview[playerid], "AK-47 R$ 2800");
			TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
			TextDrawShowForPlayer(playerid,AmmuBuyText);
			TextDrawShowForPlayer(playerid,AmmuCancelText);

			SetPlayerCameraPos(playerid, 317.3647, -164.1117, 1000.7939);
			SetPlayerCameraLookAt(playerid, 316.4168, -163.7988, 1000.3392);
			TogglePlayerControllable(playerid, 0);
            ApplyAnimation(playerid, "WEAPONS","SHP_Tray_Pose",1,1,0,0,0,0,1);
		}
		else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[9][0],GunPlace[9][1],GunPlace[9][2]))
		{
		    PlayerLookAtGun[playerid] = 1;
		    Overview[playerid] = 1;
 			TextDrawHideForPlayer(playerid,AmmuMessage);
			TextDrawHideForPlayer(playerid,Background);

			TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
			TextDrawSetString(InformationsOverview[playerid], "Lanca Misseis R$ 5000");
			TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
			TextDrawShowForPlayer(playerid,AmmuBuyText);
			TextDrawShowForPlayer(playerid,AmmuCancelText);

			SetPlayerCameraPos(playerid, 313.1415, -165.2570, 1000.7438);
			SetPlayerCameraLookAt(playerid, 312.2984, -165.7917, 1000.3340);
			TogglePlayerControllable(playerid, 0);
			ApplyAnimation(playerid, "WEAPONS","SHP_Tray_Pose",1,1,0,0,0,0,1);
		}
		else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[10][0],GunPlace[10][1],GunPlace[10][2]))
		{
		    PlayerLookAtGun[playerid] = 1;
		    Overview[playerid] = 1;
 			TextDrawHideForPlayer(playerid,AmmuMessage);
			TextDrawHideForPlayer(playerid,Background);

			TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
			TextDrawSetString(InformationsOverview[playerid], "Colete R$ 500");
			TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
			TextDrawShowForPlayer(playerid,AmmuBuyText);
			TextDrawShowForPlayer(playerid,AmmuCancelText);

   			SetPlayerCameraPos(playerid, 318.0435, -158.7027, 1000.4997);
			SetPlayerCameraLookAt(playerid, 318.3025, -159.6667, 1000.2153);
			TogglePlayerControllable(playerid, 0);
			ApplyAnimation(playerid, "WEAPONS","SHP_Tray_Pose",1,1,0,0,0,0,1);
		}
		else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[11][0],GunPlace[11][1],GunPlace[11][2]))
		{
		    PlayerLookAtGun[playerid] = 1;
		    Overview[playerid] = 1;
 			TextDrawHideForPlayer(playerid,AmmuMessage);
			TextDrawHideForPlayer(playerid,Background);

			TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
			TextDrawSetString(InformationsOverview[playerid], "Granadas R$ 700");
			TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
			TextDrawShowForPlayer(playerid,AmmuBuyText);
			TextDrawShowForPlayer(playerid,AmmuCancelText);

			SetPlayerCameraPos(playerid, 318.1734, -161.1949, 1000.4863);
			SetPlayerCameraLookAt(playerid, 318.3192, -162.1825, 1000.2220);
			TogglePlayerControllable(playerid, 0);
            ApplyAnimation(playerid, "WEAPONS","SHP_Tray_Pose",1,1,0,0,0,0,1);
		}
		else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[12][0],GunPlace[12][1],GunPlace[12][2]))
		{
		    PlayerLookAtGun[playerid] = 1;
		    Overview[playerid] = 1;
 			TextDrawHideForPlayer(playerid,AmmuMessage);
			TextDrawHideForPlayer(playerid,Background);

			TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
			TextDrawSetString(InformationsOverview[playerid], "Molotov R$ 600");
			TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
			TextDrawShowForPlayer(playerid,AmmuBuyText);
			TextDrawShowForPlayer(playerid,AmmuCancelText);

   			SetPlayerCameraPos(playerid, 318.0413, -159.9501, 1000.5729);
			SetPlayerCameraLookAt(playerid, 318.2966, -160.9153, 1000.2682);
			TogglePlayerControllable(playerid, 0);
			ApplyAnimation(playerid, "WEAPONS","SHP_Tray_Pose",1,1,0,0,0,0,1);
		}
	}
	if (PRESSED(KEY_YES))
	{
		if (Overview[playerid] == 1)
		{
			if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[0][0],GunPlace[0][1],GunPlace[0][2]))
			{
				if (PegarDinheiro(playerid) < 1500)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawShowForPlayer(playerid,TextNotEnough1);
					//TextDrawShowForPlayer(playerid,TextNotEnough2);
					TextDrawHideForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else if (LicensaDeArmas(playerid) < 2)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawHideForPlayer(playerid,TextNotEnough1);
					//TextDrawHideForPlayer(playerid,TextNotEnough2);
					TextDrawShowForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else
				{
					DarArma(playerid, 23, 500);
					DarDinheiro(playerid, -1500);
					SetCameraBehindPlayer(playerid);
					TogglePlayerControllable(playerid, 1);
					PlayerPlaySound(playerid, 1052, 0, 0, 0);
					ClearAnimations(playerid);
					//PlayerLookAtGun[playerid] = 0;
					Overview[playerid] = 0;

					TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBackgroundGunBought);
					TextDrawSetString(InformationsOverview[playerid], "Colt45 Silenced comprada.");
					TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
					SetTimerEx("HideAll", 2500, 0, "i", playerid);
				}
				return 1;
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[1][0],GunPlace[1][1],GunPlace[1][2]))
			{
				if (PegarDinheiro(playerid) < 2000)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawShowForPlayer(playerid,TextNotEnough1);
					//TextDrawShowForPlayer(playerid,TextNotEnough2);
					TextDrawHideForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else if (LicensaDeArmas(playerid) < 2)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawHideForPlayer(playerid,TextNotEnough1);
					//TextDrawHideForPlayer(playerid,TextNotEnough2);
					TextDrawShowForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else
				{
					DarArma(playerid, 24, 500);
					DarDinheiro(playerid, -2000);
					SetCameraBehindPlayer(playerid);
					TogglePlayerControllable(playerid, 1);
					PlayerPlaySound(playerid, 1052, 0, 0, 0);
					//PlayerLookAtGun[playerid] = 0;
					Overview[playerid] = 0;

					TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBackgroundGunBought);
					TextDrawSetString(InformationsOverview[playerid], "Desert Eagle comprada.");
					TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
					SetTimerEx("HideAll", 2500, 0, "i", playerid);
				}
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[2][0],GunPlace[2][1],GunPlace[2][2]))
			{
				if (PegarDinheiro(playerid) < 1000)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawShowForPlayer(playerid,TextNotEnough1);
					//TextDrawShowForPlayer(playerid,TextNotEnough2);
					TextDrawHideForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else if (LicensaDeArmas(playerid) < 2)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawHideForPlayer(playerid,TextNotEnough1);
					//TextDrawHideForPlayer(playerid,TextNotEnough2);
					TextDrawShowForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else
				{
					DarArma(playerid, 22, 500);
					DarDinheiro(playerid, -1000);
					SetCameraBehindPlayer(playerid);
					TogglePlayerControllable(playerid, 1);
					PlayerPlaySound(playerid, 1052, 0, 0, 0);
    				//PlayerLookAtGun[playerid] = 0;
					Overview[playerid] = 0;

					TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBackgroundGunBought);
					TextDrawSetString(InformationsOverview[playerid], "Colt 45 comprada.");
					TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
					SetTimerEx("HideAll", 2500, 0, "i", playerid);
				}
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[3][0],GunPlace[3][1],GunPlace[3][2]))
			{
				if (PegarDinheiro(playerid) < 3500)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawShowForPlayer(playerid,TextNotEnough1);
					//TextDrawShowForPlayer(playerid,TextNotEnough2);
					TextDrawHideForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else if (LicensaDeArmas(playerid) < 5)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawHideForPlayer(playerid,TextNotEnough1);
					//TextDrawHideForPlayer(playerid,TextNotEnough2);
					TextDrawShowForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else
				{
					DarArma(playerid, 29, 1000);
					DarDinheiro(playerid, -3500);
					SetCameraBehindPlayer(playerid);
					TogglePlayerControllable(playerid, 1);
					PlayerPlaySound(playerid, 1052, 0, 0, 0);
					//PlayerLookAtGun[playerid] = 0;
					Overview[playerid] = 0;

					TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBackgroundGunBought);
					TextDrawSetString(InformationsOverview[playerid], "MP5 comprada.");
					TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
					SetTimerEx("HideAll", 2500, 0, "i", playerid);
				}
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[4][0],GunPlace[4][1],GunPlace[4][2]))
			{
				if (PegarDinheiro(playerid) < 2400)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawShowForPlayer(playerid,TextNotEnough1);
					//TextDrawShowForPlayer(playerid,TextNotEnough2);
					TextDrawHideForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else if (LicensaDeArmas(playerid) < 4)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawHideForPlayer(playerid,TextNotEnough1);
					//TextDrawHideForPlayer(playerid,TextNotEnough2);
					TextDrawShowForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else
				{
					DarArma(playerid, 25, 70);
					DarDinheiro(playerid, -2400);
					SetCameraBehindPlayer(playerid);
					TogglePlayerControllable(playerid, 1);
					PlayerPlaySound(playerid, 1052, 0, 0, 0);
					//PlayerLookAtGun[playerid] = 0;
					Overview[playerid] = 0;

					TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBackgroundGunBought);
					TextDrawSetString(InformationsOverview[playerid], "Escopeta comprada.");
					TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
					SetTimerEx("HideAll", 2500, 0, "i", playerid);
				}
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[5][0],GunPlace[5][1],GunPlace[5][2]))
			{
				if (PegarDinheiro(playerid) < 500)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawShowForPlayer(playerid,TextNotEnough1);
					//TextDrawShowForPlayer(playerid,TextNotEnough2);
					TextDrawHideForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else
				{
					DarArma(playerid, 5, 1);
					DarDinheiro(playerid, -500);
					SetCameraBehindPlayer(playerid);
					TogglePlayerControllable(playerid, 1);
					PlayerPlaySound(playerid, 1052, 0, 0, 0);
					//PlayerLookAtGun[playerid] = 0;
					Overview[playerid] = 0;

					TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBackgroundGunBought);
					TextDrawSetString(InformationsOverview[playerid], "Taco de baseball comprado.");
					TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
					SetTimerEx("HideAll", 2500, 0, "i", playerid);
				}
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[6][0],GunPlace[6][1],GunPlace[6][2]))
			{
				if (PegarDinheiro(playerid) < 4000)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawShowForPlayer(playerid,TextNotEnough1);
					//TextDrawShowForPlayer(playerid,TextNotEnough2);
					TextDrawHideForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else if (LicensaDeArmas(playerid) < 4)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawHideForPlayer(playerid,TextNotEnough1);
					//TextDrawHideForPlayer(playerid,TextNotEnough2);
					TextDrawShowForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else
				{
					DarArma(playerid, 34, 50);
					DarDinheiro(playerid, -4000);
					SetCameraBehindPlayer(playerid);
					TogglePlayerControllable(playerid, 1);
					PlayerPlaySound(playerid, 1052, 0, 0, 0);
					Overview[playerid] = 0;
					//PlayerLookAtGun[playerid] = 0;

					TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBackgroundGunBought);
					TextDrawSetString(InformationsOverview[playerid], "Rifle Sniper comprada.");
					TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
					SetTimerEx("HideAll", 2500, 0, "i", playerid);
				}
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[7][0],GunPlace[7][1],GunPlace[7][2]))
			{
				if (PegarDinheiro(playerid) < 2800)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawShowForPlayer(playerid,TextNotEnough1);
					//TextDrawShowForPlayer(playerid,TextNotEnough2);
					TextDrawHideForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else if (LicensaDeArmas(playerid) < 4)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawHideForPlayer(playerid,TextNotEnough1);
					//TextDrawHideForPlayer(playerid,TextNotEnough2);
					TextDrawShowForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else
				{
					DarArma(playerid, 31, 500);
					DarDinheiro(playerid, -2800);
					SetCameraBehindPlayer(playerid);
					TogglePlayerControllable(playerid, 1);
					PlayerPlaySound(playerid, 1052, 0, 0, 0);
					//PlayerLookAtGun[playerid] = 0;
					Overview[playerid] = 0;

    				TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBackgroundGunBought);
					TextDrawSetString(InformationsOverview[playerid], "M4 comprada.");
					TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
					SetTimerEx("HideAll", 2500, 0, "i", playerid);
				}
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[8][0],GunPlace[8][1],GunPlace[8][2]))
			{
				if (PegarDinheiro(playerid) < 2800)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawShowForPlayer(playerid,TextNotEnough1);
					//TextDrawShowForPlayer(playerid,TextNotEnough2);
					TextDrawHideForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else if (LicensaDeArmas(playerid) < 4)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawHideForPlayer(playerid,TextNotEnough1);
					//TextDrawHideForPlayer(playerid,TextNotEnough2);
					TextDrawShowForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else
				{
					DarArma(playerid, 30, 500);
					DarDinheiro(playerid, -2800);
					SetCameraBehindPlayer(playerid);
					TogglePlayerControllable(playerid, 1);
					PlayerPlaySound(playerid, 1052, 0, 0, 0);
					//PlayerLookAtGun[playerid] = 0;
					Overview[playerid] = 0;

    				TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBackgroundGunBought);
					TextDrawSetString(InformationsOverview[playerid], "AK-47 comprada.");
					TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
					SetTimerEx("HideAll", 2500, 0, "i", playerid);
				}
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[9][0],GunPlace[9][1],GunPlace[9][2]))
			{
				if (PegarDinheiro(playerid) < 5000)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawShowForPlayer(playerid,TextNotEnough1);
					//TextDrawShowForPlayer(playerid,TextNotEnough2);
					TextDrawHideForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else if (LicensaDeArmas(playerid) < 6)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawHideForPlayer(playerid,TextNotEnough1);
					//TextDrawHideForPlayer(playerid,TextNotEnough2);
					TextDrawShowForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else
				{
					DarArma(playerid, 35, 10);
					DarDinheiro(playerid, -5000);
					SetCameraBehindPlayer(playerid);
					TogglePlayerControllable(playerid, 1);
					PlayerPlaySound(playerid, 1052, 0, 0, 0);
					//PlayerLookAtGun[playerid] = 0;

 					TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBackgroundGunBought);
					TextDrawSetString(InformationsOverview[playerid], "Lanca Misseis comprado.");
					TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
					SetTimerEx("HideAll", 2500, 0, "i", playerid);
				}
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[10][0],GunPlace[10][1],GunPlace[10][2]))
			{
				if (PegarDinheiro(playerid) < 500)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawShowForPlayer(playerid,TextNotEnough1);
					//TextDrawShowForPlayer(playerid,TextNotEnough2);
					TextDrawHideForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else
				{
					SetPlayerArmourEx(playerid, 100);
					DarDinheiro(playerid, -500);
					SetCameraBehindPlayer(playerid);
					TogglePlayerControllable(playerid, 1);
					PlayerPlaySound(playerid, 1052, 0, 0, 0);
					//PlayerLookAtGun[playerid] = 0;
					Overview[playerid] = 0;

					TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBackgroundGunBought);
					TextDrawSetString(InformationsOverview[playerid], "Colete comprado.");
					TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
					SetTimerEx("HideAll", 2500, 0, "i", playerid);
				}
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[11][0],GunPlace[11][1],GunPlace[11][2]))
			{
				if (PegarDinheiro(playerid) < 700)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawShowForPlayer(playerid,TextNotEnough1);
					//TextDrawShowForPlayer(playerid,TextNotEnough2);
					TextDrawHideForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else if (LicensaDeArmas(playerid) < 5)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawHideForPlayer(playerid,TextNotEnough1);
					//TextDrawHideForPlayer(playerid,TextNotEnough2);
					TextDrawShowForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else
				{
					DarArma(playerid, 16, 5);
					DarDinheiro(playerid, -700);
					SetCameraBehindPlayer(playerid);
					TogglePlayerControllable(playerid, 1);
					PlayerPlaySound(playerid, 1052, 0, 0, 0);
					//PlayerLookAtGun[playerid] = 0;
					Overview[playerid] = 0;

					TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBackgroundGunBought);
					TextDrawSetString(InformationsOverview[playerid], "Granadas comprada.");
					TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
					SetTimerEx("HideAll", 2500, 0, "i", playerid);
				}
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[12][0],GunPlace[12][1],GunPlace[12][2]))
			{
				if (PegarDinheiro(playerid) < 600)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawShowForPlayer(playerid,TextNotEnough1);
					//TextDrawShowForPlayer(playerid,TextNotEnough2);
					TextDrawHideForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else if (LicensaDeArmas(playerid) < 5)
				{
				    TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBuyText);
					TextDrawShowForPlayer(playerid,AmmuCancelText);
				    TextDrawShowForPlayer(playerid,AmmuBackgroundNotEnough);
					TextDrawHideForPlayer(playerid,TextNotEnough1);
					//TextDrawHideForPlayer(playerid,TextNotEnough2);
					TextDrawShowForPlayer(playerid,TextNotLicense);
					SetTimerEx("ResetTextDraws", 2500, 0, "i", playerid);
				}
				else
				{
					DarArma(playerid, 18, 5);
					DarDinheiro(playerid, -600);
					SetCameraBehindPlayer(playerid);
					TogglePlayerControllable(playerid, 1);
					PlayerPlaySound(playerid, 1052, 0, 0, 0);
					//PlayerLookAtGun[playerid] = 0;
					Overview[playerid] = 0;

					TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
					TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
					TextDrawShowForPlayer(playerid,AmmuBackgroundGunBought);
					TextDrawSetString(InformationsOverview[playerid], "Molotovs comprada.");
					TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
					SetTimerEx("HideAll", 2500, 0, "i", playerid);
				}
			}
		}
	}
	if (PRESSED(KEY_NO))
	{
		if (Overview[playerid] == 1)
		{
			if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[0][0],GunPlace[0][1],GunPlace[0][2]))
			{
				SetCameraBehindPlayer(playerid);
				TogglePlayerControllable(playerid, 1);
				PlayerPlaySound(playerid, 1053, 0, 0, 0);
				ClearAnimations(playerid);
				PlayerLookAtGun[playerid] = 0;
				Overview[playerid] = 0;

				TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
				TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
				TextDrawHideForPlayer(playerid,AmmuBuyText);
				TextDrawHideForPlayer(playerid,AmmuCancelText);

				// Forcing Textdraws to hide if they appeared
				TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
				TextDrawHideForPlayer(playerid,TextNotEnough1);
				//TextDrawHideForPlayer(playerid,TextNotEnough2);
				TextDrawHideForPlayer(playerid,TextNotLicense);
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[1][0],GunPlace[1][1],GunPlace[1][2]))
			{
				SetCameraBehindPlayer(playerid);
				TogglePlayerControllable(playerid, 1);
				PlayerPlaySound(playerid, 1053, 0, 0, 0);
                PlayerLookAtGun[playerid] = 0;
				Overview[playerid] = 0;

				TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
				TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
				TextDrawHideForPlayer(playerid,AmmuBuyText);
				TextDrawHideForPlayer(playerid,AmmuCancelText);
				TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
				TextDrawHideForPlayer(playerid,TextNotEnough1);
				//TextDrawHideForPlayer(playerid,TextNotEnough2);
				TextDrawHideForPlayer(playerid,TextNotLicense);
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[2][0],GunPlace[2][1],GunPlace[2][2]))
			{
				SetCameraBehindPlayer(playerid);
				TogglePlayerControllable(playerid, 1);
				PlayerPlaySound(playerid, 1053, 0, 0, 0);
				PlayerLookAtGun[playerid] = 0;
				Overview[playerid] = 0;

				TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
				TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
				TextDrawHideForPlayer(playerid,AmmuBuyText);
				TextDrawHideForPlayer(playerid,AmmuCancelText);
				TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
				TextDrawHideForPlayer(playerid,TextNotEnough1);
				//TextDrawHideForPlayer(playerid,TextNotEnough2);
				TextDrawHideForPlayer(playerid,TextNotLicense);
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[3][0],GunPlace[3][1],GunPlace[3][2]))
			{
				SetCameraBehindPlayer(playerid);
				TogglePlayerControllable(playerid, 1);
				PlayerPlaySound(playerid, 1053, 0, 0, 0);
				PlayerLookAtGun[playerid] = 0;
				Overview[playerid] = 0;

				TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
				TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
				TextDrawHideForPlayer(playerid,AmmuBuyText);
				TextDrawHideForPlayer(playerid,AmmuCancelText);
				TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
				TextDrawHideForPlayer(playerid,TextNotEnough1);
				//TextDrawHideForPlayer(playerid,TextNotEnough2);
				TextDrawHideForPlayer(playerid,TextNotLicense);
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[4][0],GunPlace[4][1],GunPlace[4][2]))
			{
				SetCameraBehindPlayer(playerid);
				TogglePlayerControllable(playerid, 1);
				PlayerPlaySound(playerid, 1053, 0, 0, 0);
				PlayerLookAtGun[playerid] = 0;
				Overview[playerid] = 0;

				TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
				TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
				TextDrawHideForPlayer(playerid,AmmuBuyText);
				TextDrawHideForPlayer(playerid,AmmuCancelText);
				TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
				TextDrawHideForPlayer(playerid,TextNotEnough1);
				//TextDrawHideForPlayer(playerid,TextNotEnough2);
				TextDrawHideForPlayer(playerid,TextNotLicense);
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[5][0],GunPlace[5][1],GunPlace[5][2]))
			{
				SetCameraBehindPlayer(playerid);
				TogglePlayerControllable(playerid, 1);
				PlayerPlaySound(playerid, 1053, 0, 0, 0);
				PlayerLookAtGun[playerid] = 0;
				Overview[playerid] = 0;

				TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
				TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
				TextDrawHideForPlayer(playerid,AmmuBuyText);
				TextDrawHideForPlayer(playerid,AmmuCancelText);
				TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
				TextDrawHideForPlayer(playerid,TextNotEnough1);
				//TextDrawHideForPlayer(playerid,TextNotEnough2);
				TextDrawHideForPlayer(playerid,TextNotLicense);
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[6][0],GunPlace[6][1],GunPlace[6][2]))
			{
				SetCameraBehindPlayer(playerid);
				TogglePlayerControllable(playerid, 1);
				PlayerPlaySound(playerid, 1053, 0, 0, 0);
				PlayerLookAtGun[playerid] = 0;
				Overview[playerid] = 0;

				TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
				TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
				TextDrawHideForPlayer(playerid,AmmuBuyText);
				TextDrawHideForPlayer(playerid,AmmuCancelText);
				TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
				TextDrawHideForPlayer(playerid,TextNotEnough1);
				//TextDrawHideForPlayer(playerid,TextNotEnough2);
				TextDrawHideForPlayer(playerid,TextNotLicense);
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[7][0],GunPlace[7][1],GunPlace[7][2]))
			{
				SetCameraBehindPlayer(playerid);
				TogglePlayerControllable(playerid, 1);
				PlayerPlaySound(playerid, 1053, 0, 0, 0);
				PlayerLookAtGun[playerid] = 0;
				Overview[playerid] = 0;

				TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
				TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
				TextDrawHideForPlayer(playerid,AmmuBuyText);
				TextDrawHideForPlayer(playerid,AmmuCancelText);
				TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
				TextDrawHideForPlayer(playerid,TextNotEnough1);
				//TextDrawHideForPlayer(playerid,TextNotEnough2);
				TextDrawHideForPlayer(playerid,TextNotLicense);
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[8][0],GunPlace[8][1],GunPlace[8][2]))
			{
				SetCameraBehindPlayer(playerid);
				TogglePlayerControllable(playerid, 1);
				PlayerPlaySound(playerid, 1053, 0, 0, 0);
				PlayerLookAtGun[playerid] = 0;
				Overview[playerid] = 0;

				TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
				TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
				TextDrawHideForPlayer(playerid,AmmuBuyText);
				TextDrawHideForPlayer(playerid,AmmuCancelText);
				TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
				TextDrawHideForPlayer(playerid,TextNotEnough1);
				//TextDrawHideForPlayer(playerid,TextNotEnough2);
				TextDrawHideForPlayer(playerid,TextNotLicense);
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[9][0],GunPlace[9][1],GunPlace[9][2]))
			{
				SetCameraBehindPlayer(playerid);
				TogglePlayerControllable(playerid, 1);
				PlayerPlaySound(playerid, 1053, 0, 0, 0);
				PlayerLookAtGun[playerid] = 0;
				Overview[playerid] = 0;

				TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
				TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
				TextDrawHideForPlayer(playerid,AmmuBuyText);
				TextDrawHideForPlayer(playerid,AmmuCancelText);
				TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
				TextDrawHideForPlayer(playerid,TextNotEnough1);
				//TextDrawHideForPlayer(playerid,TextNotEnough2);
				TextDrawHideForPlayer(playerid,TextNotLicense);
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[10][0],GunPlace[10][1],GunPlace[10][2]))
			{
				SetCameraBehindPlayer(playerid);
				TogglePlayerControllable(playerid, 1);
				PlayerPlaySound(playerid, 1053, 0, 0, 0);
				PlayerLookAtGun[playerid] = 0;
				Overview[playerid] = 0;

				TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
				TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
				TextDrawHideForPlayer(playerid,AmmuBuyText);
				TextDrawHideForPlayer(playerid,AmmuCancelText);
				TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
				TextDrawHideForPlayer(playerid,TextNotEnough1);
				//TextDrawHideForPlayer(playerid,TextNotEnough2);
				TextDrawHideForPlayer(playerid,TextNotLicense);
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[11][0],GunPlace[11][1],GunPlace[11][2]))
			{
				SetCameraBehindPlayer(playerid);
				TogglePlayerControllable(playerid, 1);
				PlayerPlaySound(playerid, 1053, 0, 0, 0);
				PlayerLookAtGun[playerid] = 0;
				Overview[playerid] = 0;

				TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
				TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
				TextDrawHideForPlayer(playerid,AmmuBuyText);
				TextDrawHideForPlayer(playerid,AmmuCancelText);
				TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
				TextDrawHideForPlayer(playerid,TextNotEnough1);
				//TextDrawHideForPlayer(playerid,TextNotEnough2);
				TextDrawHideForPlayer(playerid,TextNotLicense);
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[12][0],GunPlace[12][1],GunPlace[12][2]))
			{
				SetCameraBehindPlayer(playerid);
				TogglePlayerControllable(playerid, 1);
				PlayerPlaySound(playerid, 1053, 0, 0, 0);
				PlayerLookAtGun[playerid] = 0;
				Overview[playerid] = 0;

				TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
				TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
				TextDrawHideForPlayer(playerid,AmmuBuyText);
				TextDrawHideForPlayer(playerid,AmmuCancelText);
				TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
				TextDrawHideForPlayer(playerid,TextNotEnough1);
				//TextDrawHideForPlayer(playerid,TextNotEnough2);
				TextDrawHideForPlayer(playerid,TextNotLicense);
			}
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[6][0],GunPlace[6][1],GunPlace[6][2]))
			{
				SetCameraBehindPlayer(playerid);
				TogglePlayerControllable(playerid, 1);
				PlayerPlaySound(playerid, 1053, 0, 0, 0);
				PlayerLookAtGun[playerid] = 0;
				Overview[playerid] = 0;

				TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
				TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
				TextDrawHideForPlayer(playerid,AmmuBuyText);
				TextDrawHideForPlayer(playerid,AmmuCancelText);
                TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
				TextDrawHideForPlayer(playerid,TextNotEnough1);
				//TextDrawHideForPlayer(playerid,TextNotEnough2);
				TextDrawHideForPlayer(playerid,TextNotLicense);
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[7][0],GunPlace[7][1],GunPlace[7][2]))
			{
				SetCameraBehindPlayer(playerid);
				TogglePlayerControllable(playerid, 1);
				PlayerPlaySound(playerid, 1053, 0, 0, 0);
				PlayerLookAtGun[playerid] = 0;
				Overview[playerid] = 0;

				TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
				TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
				TextDrawHideForPlayer(playerid,AmmuBuyText);
				TextDrawHideForPlayer(playerid,AmmuCancelText);
				TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
				TextDrawHideForPlayer(playerid,TextNotEnough1);
				//TextDrawHideForPlayer(playerid,TextNotEnough2);
				TextDrawHideForPlayer(playerid,TextNotLicense);
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[8][0],GunPlace[8][1],GunPlace[8][2]))
			{
				SetCameraBehindPlayer(playerid);
				TogglePlayerControllable(playerid, 1);
				PlayerPlaySound(playerid, 1053, 0, 0, 0);
				PlayerLookAtGun[playerid] = 0;
				Overview[playerid] = 0;

				TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
				TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
				TextDrawHideForPlayer(playerid,AmmuBuyText);
				TextDrawHideForPlayer(playerid,AmmuCancelText);
    			TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
				TextDrawHideForPlayer(playerid,TextNotEnough1);
				//TextDrawHideForPlayer(playerid,TextNotEnough2);
				TextDrawHideForPlayer(playerid,TextNotLicense);
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[9][0],GunPlace[9][1],GunPlace[9][2]))
			{
				SetCameraBehindPlayer(playerid);
				TogglePlayerControllable(playerid, 1);
				PlayerPlaySound(playerid, 1053, 0, 0, 0);
				PlayerLookAtGun[playerid] = 0;
				Overview[playerid] = 0;

				TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
				TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
				TextDrawHideForPlayer(playerid,AmmuBuyText);
				TextDrawHideForPlayer(playerid,AmmuCancelText);
				TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
				TextDrawHideForPlayer(playerid,TextNotEnough1);
				//TextDrawHideForPlayer(playerid,TextNotEnough2);
				TextDrawHideForPlayer(playerid,TextNotLicense);
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[10][0],GunPlace[10][1],GunPlace[10][2]))
			{
				SetCameraBehindPlayer(playerid);
				TogglePlayerControllable(playerid, 1);
				PlayerPlaySound(playerid, 1053, 0, 0, 0);
				PlayerLookAtGun[playerid] = 0;
				Overview[playerid] = 0;

				TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
				TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
				TextDrawHideForPlayer(playerid,AmmuBuyText);
				TextDrawHideForPlayer(playerid,AmmuCancelText);
				TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
				TextDrawHideForPlayer(playerid,TextNotEnough1);
				//TextDrawHideForPlayer(playerid,TextNotEnough2);
				TextDrawHideForPlayer(playerid,TextNotLicense);
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[11][0],GunPlace[11][1],GunPlace[11][2]))
			{
				SetCameraBehindPlayer(playerid);
				TogglePlayerControllable(playerid, 1);
				PlayerPlaySound(playerid, 1053, 0, 0, 0);
				PlayerLookAtGun[playerid] = 0;
				Overview[playerid] = 0;

				TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
				TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
				TextDrawHideForPlayer(playerid,AmmuBuyText);
				TextDrawHideForPlayer(playerid,AmmuCancelText);
				TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
				TextDrawHideForPlayer(playerid,TextNotEnough1);
				//TextDrawHideForPlayer(playerid,TextNotEnough2);
				TextDrawHideForPlayer(playerid,TextNotLicense);
			}
			else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[12][0],GunPlace[12][1],GunPlace[12][2]))
			{
				SetCameraBehindPlayer(playerid);
				TogglePlayerControllable(playerid, 1);
				PlayerPlaySound(playerid, 1053, 0, 0, 0);
				PlayerLookAtGun[playerid] = 0;
				Overview[playerid] = 0;

				TextDrawHideForPlayer(playerid,AmmuBackgroundOverview);
				TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
				TextDrawHideForPlayer(playerid,AmmuBuyText);
				TextDrawHideForPlayer(playerid,AmmuCancelText);
				TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
				TextDrawHideForPlayer(playerid,TextNotEnough1);
				//TextDrawHideForPlayer(playerid,TextNotEnough2);
				TextDrawHideForPlayer(playerid,TextNotLicense);
			}
		return 1;
		}
	return 1;
}

forward ResetTextDraws(playerid);
public ResetTextDraws(playerid)
{
 	if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[0][0],GunPlace[0][1],GunPlace[0][2]))
	{
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		PlayerLookAtGun[playerid] = 1;
		Overview[playerid] = 1;
		TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
		TextDrawHideForPlayer(playerid,TextNotEnough1);
		//TextDrawHideForPlayer(playerid,TextNotEnough2);
		TextDrawHideForPlayer(playerid,TextNotLicense);
		TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
		TextDrawSetString(InformationsOverview[playerid], "Colt45 Silenced R$ 1500");
		TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
		return 1;
	}
	else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[1][0],GunPlace[1][1],GunPlace[1][2]))
	{
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		PlayerLookAtGun[playerid] = 1;
		Overview[playerid] = 1;
		TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
		TextDrawHideForPlayer(playerid,TextNotEnough1);
		//TextDrawHideForPlayer(playerid,TextNotEnough2);
		TextDrawHideForPlayer(playerid,TextNotLicense);
		TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
		TextDrawSetString(InformationsOverview[playerid], "Desert Eagle R$ 2000");
		TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
	}
	else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[2][0],GunPlace[2][1],GunPlace[2][2]))
	{
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		PlayerLookAtGun[playerid] = 1;
		Overview[playerid] = 1;
		TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
		TextDrawHideForPlayer(playerid,TextNotEnough1);
		//TextDrawHideForPlayer(playerid,TextNotEnough2);
		TextDrawHideForPlayer(playerid,TextNotLicense);
		TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
		TextDrawSetString(InformationsOverview[playerid], "Colt45 R$ 1000");
		TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
	}
	else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[3][0],GunPlace[3][1],GunPlace[3][2]))
	{
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		PlayerLookAtGun[playerid] = 1;
		Overview[playerid] = 1;
		TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
		TextDrawHideForPlayer(playerid,TextNotEnough1);
		//TextDrawHideForPlayer(playerid,TextNotEnough2);
		TextDrawHideForPlayer(playerid,TextNotLicense);
		TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
		TextDrawSetString(InformationsOverview[playerid], "MP5 R$ 3500");
		TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
	}
	else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[4][0],GunPlace[4][1],GunPlace[4][2]))
	{
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		PlayerLookAtGun[playerid] = 1;
		Overview[playerid] = 1;
		TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
		TextDrawHideForPlayer(playerid,TextNotEnough1);
		//TextDrawHideForPlayer(playerid,TextNotEnough2);
		TextDrawHideForPlayer(playerid,TextNotLicense);
		TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
		TextDrawSetString(InformationsOverview[playerid], "Escopeta R$ 2400");
		TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
	}
	else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[5][0],GunPlace[5][1],GunPlace[5][2]))
	{
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		PlayerLookAtGun[playerid] = 1;
		Overview[playerid] = 1;
		TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
		TextDrawHideForPlayer(playerid,TextNotEnough1);
		//TextDrawHideForPlayer(playerid,TextNotEnough2);
		TextDrawHideForPlayer(playerid,TextNotLicense);
		TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
		TextDrawSetString(InformationsOverview[playerid], "Taco de baseball R$ 500");
		TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
	}
	else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[6][0],GunPlace[6][1],GunPlace[6][2]))
	{
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		PlayerLookAtGun[playerid] = 1;
		Overview[playerid] = 1;
		TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
		TextDrawHideForPlayer(playerid,TextNotEnough1);
		//TextDrawHideForPlayer(playerid,TextNotEnough2);
		TextDrawHideForPlayer(playerid,TextNotLicense);
		TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
		TextDrawSetString(InformationsOverview[playerid], "Rifle Sniper R$ 4000");
		TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
	}
	else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[7][0],GunPlace[7][1],GunPlace[7][2]))
	{
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		PlayerLookAtGun[playerid] = 1;
		Overview[playerid] = 1;
		TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
		TextDrawHideForPlayer(playerid,TextNotEnough1);
		//TextDrawHideForPlayer(playerid,TextNotEnough2);
		TextDrawHideForPlayer(playerid,TextNotLicense);
		TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
		TextDrawSetString(InformationsOverview[playerid], "M4 R$ 2800");
		TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
	}
	else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[8][0],GunPlace[8][1],GunPlace[8][2]))
	{
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		PlayerLookAtGun[playerid] = 1;
		Overview[playerid] = 1;
		TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
		TextDrawHideForPlayer(playerid,TextNotEnough1);
		//TextDrawHideForPlayer(playerid,TextNotEnough2);
		TextDrawHideForPlayer(playerid,TextNotLicense);
		TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
		TextDrawSetString(InformationsOverview[playerid], "AK-47 R$ 2800");
		TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
	}
	else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[9][0],GunPlace[9][1],GunPlace[9][2]))
	{
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		PlayerLookAtGun[playerid] = 1;
		Overview[playerid] = 1;
		TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
		TextDrawHideForPlayer(playerid,TextNotEnough1);
		//TextDrawHideForPlayer(playerid,TextNotEnough2);
		TextDrawHideForPlayer(playerid,TextNotLicense);
		TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
		TextDrawSetString(InformationsOverview[playerid], "Lanca Misseis R$ 5000");
		TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
	}
	else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[10][0],GunPlace[10][1],GunPlace[10][2]))
	{
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		PlayerLookAtGun[playerid] = 1;
		Overview[playerid] = 1;
		TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
		TextDrawHideForPlayer(playerid,TextNotEnough1);
		//TextDrawHideForPlayer(playerid,TextNotEnough2);
		TextDrawHideForPlayer(playerid,TextNotLicense);
		TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
		TextDrawSetString(InformationsOverview[playerid], "Colete R$ 500");
		TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
	}
	else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[11][0],GunPlace[11][1],GunPlace[11][2]))
	{
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		PlayerLookAtGun[playerid] = 1;
		Overview[playerid] = 1;
		TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
		TextDrawHideForPlayer(playerid,TextNotEnough1);
		//TextDrawHideForPlayer(playerid,TextNotEnough2);
		TextDrawHideForPlayer(playerid,TextNotLicense);
		TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
		TextDrawSetString(InformationsOverview[playerid], "Granadas R$ 700");
		TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
	}
	else if (IsPlayerInRangeOfPoint(playerid, 0.5, GunPlace[12][0],GunPlace[12][1],GunPlace[12][2]))
	{
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		PlayerLookAtGun[playerid] = 1;
		Overview[playerid] = 1;
		TextDrawHideForPlayer(playerid,AmmuBackgroundNotEnough);
		TextDrawHideForPlayer(playerid,TextNotEnough1);
		//TextDrawHideForPlayer(playerid,TextNotEnough2);
		TextDrawHideForPlayer(playerid,TextNotLicense);
		TextDrawShowForPlayer(playerid,AmmuBackgroundOverview);
		TextDrawSetString(InformationsOverview[playerid], "Molotov R$ 600");
		TextDrawShowForPlayer(playerid,InformationsOverview[playerid]);
	}
	return 1;
}

forward HideAll(playerid);
public HideAll(playerid)
{
	TextDrawHideForPlayer(playerid,AmmuBackgroundGunBought);
	TextDrawHideForPlayer(playerid,InformationsOverview[playerid]);
	TextDrawHideForPlayer(playerid,AmmuBuyText);
	TextDrawHideForPlayer(playerid,AmmuCancelText);
	PlayerLookAtGun[playerid] = 0;
}

public PlayerToPointStripped(Float:radi, playerid, Float:x, Float:y, Float:z, Float:curx, Float:cury, Float:curz)
{
    if(IsPlayerConnected(playerid))
	{
		new Float:tempposx, Float:tempposy, Float:tempposz;
		tempposx = (curx -x);
		tempposy = (cury -y);
		tempposz = (curz -z);
		if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi))) return 1;
	}
	return 0;
}