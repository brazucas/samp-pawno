/*
							Seifader - Screen Fader by Seif
*/
/*x---------------------------------Important-------------------------------------x*/
//**INCLUDES**//
#include <a_samp>
//**PRAGMAS**//

//**MISC**//

/*x---------------------------------Defining-------------------------------------x*/
//**COLORS*//

	//Some colors I made
#define GREEN 			0x21DD00FF
#define RED 			0xE60000FF
#define ADMIN_RED 		0xFB0000FF
#define YELLOW 			0xFFFF00FF
#define ORANGE 			0xF97804FF
#define LIGHTRED 		0xFF8080FF
#define LIGHTBLUE 		0x00C2ECFF
#define PURPLE 			0xB360FDFF
#define BLUE 			0x1229FAFF
#define LIGHTGREEN 		0x38FF06FF
#define DARKPINK 		0xE100E1FF
#define DARKGREEN 		0x008040FF
#define ANNOUNCEMENT 	0x6AF7E1FF
#define GREY 			0xCECECEFF
#define PINK 			0xD52DFFFF
#define DARKGREY    	0x626262FF
#define AQUAGREEN   	0x03D687FF
#define WHITE 			0xFFFFFFFF
//**MISC**//
#define SLOW_FADE       0
#define NORMAL_FADE     1
#define FAST_FADE       2
#define VERY_FAST       3

#define MAX_PLAYERS_FADER 50

//**VARIABLES**//
new colorfade[MAX_PLAYERS_FADER];
new Text:screenfade[MAX_PLAYERS_FADER];
// **FORWARDS** //
forward ScreenFade(playerid, color, speed);
forward ScreenFadeColor(playerid, color, speed);
forward OnPlayerScreenFade(playerid, color, speed);
forward OnPlayerScreenColorFade(playerid, color, speed);
// **NATIVES** //
/*
	native Seifader_OnInit();
	native Seifader_OnExit();
	native FadePlayerScreen(playerid, color, speed); // speed = SLOW_FADE, FAST_FADE, NORMAL_FADE
	native FadePlayerScreenToColor(playerid, color, speed); // speed = SLOW_FADE, FAST_FADE, NORMAL_FADE
	native Seifader_OnPlayerDisconnect(playerid);
*/
/*x---------------------------------CallBacks-------------------------------------x*/
stock Seifader_OnInit()
{
    for(new all = 0; all < MAX_PLAYERS_FADER; all++)
	{
	    screenfade[all] = TextDrawCreate(0.0, 0.0, "_");
		TextDrawFont(screenfade[all], 1);
		TextDrawLetterSize(screenfade[all], 0.0, 50.0);
		TextDrawUseBox(screenfade[all], true);
		TextDrawColor(screenfade[all], 0);
		TextDrawBoxColor(screenfade[all], 0);
		colorfade[all] = 0;
	}
}

stock Seifader_OnExit()
{
    for(new all = 0; all < MAX_PLAYERS_FADER; all++) TextDrawDestroy(screenfade[all]);
}

stock Seifader_OnPlayerDisconnect(playerid)
{
	TextDrawHideForPlayer(playerid, screenfade[playerid]);
}

stock FadePlayerScreen(playerid, color, speed)
{
    colorfade[playerid] = color;
    TextDrawBoxColor(screenfade[playerid], color);
	TextDrawShowForPlayer(playerid, screenfade[playerid]);
	SetTimerEx("ScreenFade", 100, 0, "ddd", playerid, color, speed);
}

stock FadePlayerScreenToColor(playerid, color, speed)
{
	color -= 255;
	colorfade[playerid] = color;
    TextDrawBoxColor(screenfade[playerid], color);
	TextDrawShowForPlayer(playerid, screenfade[playerid]);
	SetTimerEx("ScreenFadeColor", 100, 0, "ddd", playerid, color, speed);
}

stock InstantanFade(playerid)
{
	TextDrawHideForPlayer(playerid, screenfade[playerid]);
}

public ScreenFade(playerid, color, speed)
{
	if(IsPlayerConnected(playerid))
	{
		if (color <= (colorfade[playerid] - 255))
		{
			TextDrawHideForPlayer(playerid, screenfade[playerid]);
			OnPlayerScreenFade(playerid, color, speed);
		}
		else
		{
			if (speed == SLOW_FADE) color--;
			else if (speed == NORMAL_FADE) color -= 15;
			else if (speed == FAST_FADE) color -= 50;
			else color=0;		
			if (color <= (colorfade[playerid] - 255)) color = (colorfade[playerid] - 255);
			TextDrawBoxColor(screenfade[playerid], color);
			TextDrawShowForPlayer(playerid, screenfade[playerid]);
			SetTimerEx("ScreenFade", 100, 0, "ddd", playerid, color, speed);
		}
	}
}

public ScreenFadeColor(playerid, color, speed)
{
	if(IsPlayerConnected(playerid))
	{
		if (color >= (colorfade[playerid] + 255))
		{
			OnPlayerScreenColorFade(playerid, color, speed);
		}
		else
		{
			if (speed == SLOW_FADE) color++;
			else if (speed == NORMAL_FADE) color += 15;
			else if (speed == FAST_FADE) color += 50;
			else color=255;		
			if (color >= (colorfade[playerid] + 255)) return;
			TextDrawBoxColor(screenfade[playerid], color);
			TextDrawShowForPlayer(playerid, screenfade[playerid]);
			SetTimerEx("ScreenFadeColor", 100, 0, "ddd", playerid, color, speed);
		}
	}	
}

/*public OnPlayerScreenFade(playerid, color, speed)
{
	return 1;
}

public OnPlayerScreenColorFade(playerid, color, speed)
{
	return 1;
}*/