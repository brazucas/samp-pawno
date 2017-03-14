/*x---------------------------------Important-------------------------------------x*/
//**INCLUDES**//
#include <a_samp>
/*x---------------------------------Defining-------------------------------------x*/
//**VARIABLES**//
new Text:Text[200];
new Text:Text2[100];
new gametextdrawforplayer;
new gametextdraw;
//**FORWARDS**//
forward GameTextRemoval(textid);
forward GameTextRemoval2(textid);
//**NATIVES**//
/*
native DisplayTextForPlayer(playerid, text[], time, font);
native DisplayTextForAll(text[], time, font);
*/
/*x---------------------------------CallBacks-------------------------------------x*/
stock DisplayTextForPlayer(playerid, text[], time, font, style) // Max Fonts: 3(0-3)   <->   Max Styles: 12(1-12)
{
	if (gametextdrawforplayer >= 199) gametextdrawforplayer = 0;
	gametextdrawforplayer++;
	new Float:TEXTX,Float:TEXTY;
    if (style == 1) TEXTX = 318, TEXTY = 196;
    else if (style == 2) TEXTX = 246, TEXTY = 142;
    else if (style == 3) TEXTX = 401, TEXTY = 376;
    else if (style == 4) TEXTX = 1, TEXTY = 376;
    else if (style == 5) TEXTX = 575, TEXTY = 54;
    else if (style == 6) TEXTX = 318, TEXTY = 432;
    else if (style == 7) TEXTX = 9, TEXTY = 150;
    else if (style == 8) TEXTX = 371, TEXTY = 415;
    else if (style == 9) TEXTX = 87, TEXTY = 209;
    else if (style == 10) TEXTX = 83, TEXTY = 127;
    else if (style == 11) TEXTX = 330, TEXTY = 134;
    else if (style == 12) TEXTX = 331, TEXTY = 152;
    else TEXTX = 246, TEXTY = 142;
    Text[gametextdrawforplayer] = TextDrawCreate(TEXTX,TEXTY,text);

	
    if(style==1)
    {		
	TextDrawAlignment(Text[gametextdrawforplayer],2);
	TextDrawBackgroundColor(Text[gametextdrawforplayer],0x000000ff);
	TextDrawFont(Text[gametextdrawforplayer],1);
	TextDrawLetterSize(Text[gametextdrawforplayer],0.449999,2.000000);
	TextDrawColor(Text[gametextdrawforplayer],0xffffffff);
	TextDrawSetProportional(Text[gametextdrawforplayer],1);
	TextDrawSetShadow(Text[gametextdrawforplayer],1);
    }		
    else if(style==7)
    {		
	TextDrawUseBox(Text[gametextdrawforplayer],1);
	TextDrawBoxColor(Text[gametextdrawforplayer],0x00000066);
	TextDrawTextSize(Text[gametextdrawforplayer],260.000000,0.000000);
	TextDrawAlignment(Text[gametextdrawforplayer],0);
	TextDrawBackgroundColor(Text[gametextdrawforplayer],0x000000ff);
	TextDrawFont(Text[gametextdrawforplayer],font);
	TextDrawLetterSize(Text[gametextdrawforplayer],0.5,1.5);
	TextDrawColor(Text[gametextdrawforplayer],0xffffffcc);
	TextDrawSetOutline(Text[gametextdrawforplayer],0);
	TextDrawSetProportional(Text[gametextdrawforplayer],1);
	TextDrawSetShadow(Text[gametextdrawforplayer],0);
    }
    else if(style==8)
    { 
        TextDrawAlignment(Text[gametextdrawforplayer],2);
        TextDrawBackgroundColor(Text[gametextdrawforplayer],0x000000ff);
        TextDrawFont(Text[gametextdrawforplayer],1);
        TextDrawLetterSize(Text[gametextdrawforplayer],0.499999,2.100000);
        TextDrawColor(Text[gametextdrawforplayer],0xffffffff);
        TextDrawSetProportional(Text[gametextdrawforplayer],1);
        TextDrawSetShadow(Text[gametextdrawforplayer],1);
    }
    else if(style==5)
    {
	TextDrawAlignment(Text[gametextdrawforplayer], 2);
	TextDrawBackgroundColor(Text[gametextdrawforplayer], 255);
	TextDrawFont(Text[gametextdrawforplayer],font);
	TextDrawLetterSize(Text[gametextdrawforplayer], 0.310000, 1.100000);
	TextDrawColor(Text[gametextdrawforplayer], -1);
	TextDrawSetOutline(Text[gametextdrawforplayer], 1);
	TextDrawSetProportional(Text[gametextdrawforplayer], 1);
	TextDrawSetShadow(Text[gametextdrawforplayer], 1);
    }			
    else if(style==6)
    { 
	TextDrawAlignment(Text[gametextdrawforplayer],2);
	TextDrawBackgroundColor(Text[gametextdrawforplayer],0x000000ff);
	TextDrawFont(Text[gametextdrawforplayer],font);
	TextDrawLetterSize(Text[gametextdrawforplayer],0.299999,1.100000);
	TextDrawColor(Text[gametextdrawforplayer],0xffffffff);
	TextDrawSetProportional(Text[gametextdrawforplayer],1);
	TextDrawSetShadow(Text[gametextdrawforplayer],1);
    }
    else if(style==9)
    {
	TextDrawUseBox(Text[gametextdrawforplayer],1);
	TextDrawBoxColor(Text[gametextdrawforplayer],0xffff0033);
	TextDrawTextSize(Text[gametextdrawforplayer],304.000000,85.000000);
	TextDrawAlignment(Text[gametextdrawforplayer],2);
	TextDrawBackgroundColor(Text[gametextdrawforplayer],0x000000ff);
	TextDrawFont(Text[gametextdrawforplayer],font);
	TextDrawLetterSize(Text[gametextdrawforplayer],0.199999,1.400000);
	TextDrawColor(Text[gametextdrawforplayer],0x00000066);
	TextDrawSetProportional(Text[gametextdrawforplayer],1);
	TextDrawSetShadow(Text[gametextdrawforplayer],0);
    }
    else if(style==10)
    {
	TextDrawUseBox(Text[gametextdrawforplayer],1);
	TextDrawBoxColor(Text[gametextdrawforplayer],0x00000033);
	TextDrawTextSize(Text[gametextdrawforplayer],174.000000,155.000000);
	TextDrawAlignment(Text[gametextdrawforplayer],2);
	TextDrawBackgroundColor(Text[gametextdrawforplayer],0x000000ff);
	TextDrawFont(Text[gametextdrawforplayer],font);
	TextDrawLetterSize(Text[gametextdrawforplayer],0.249999,1.100000);
	TextDrawColor(Text[gametextdrawforplayer],0xffffffff);
	TextDrawSetProportional(Text[gametextdrawforplayer],1);
	TextDrawSetShadow(Text[gametextdrawforplayer],1);
    }
    else if(style==11)
    {
	TextDrawUseBox(Text[gametextdrawforplayer],1);
	TextDrawBoxColor(Text[gametextdrawforplayer],0x00000033);
	TextDrawTextSize(Text[gametextdrawforplayer],82.000000,301.000000);
	TextDrawAlignment(Text[gametextdrawforplayer],2);
	TextDrawBackgroundColor(Text[gametextdrawforplayer],0x000000ff);
	TextDrawFont(Text[gametextdrawforplayer],font);
	TextDrawLetterSize(Text[gametextdrawforplayer],0.299999,1.600002);
	TextDrawColor(Text[gametextdrawforplayer],0xffffffff);
	TextDrawSetProportional(Text[gametextdrawforplayer],1);
	TextDrawSetShadow(Text[gametextdrawforplayer],1);
    }
    else if(style==12)
    {
	TextDrawAlignment(Text[gametextdrawforplayer],2);
	TextDrawBackgroundColor(Text[gametextdrawforplayer],0x000000ff);
	TextDrawFont(Text[gametextdrawforplayer],font);
	TextDrawLetterSize(Text[gametextdrawforplayer],0.199999,1.000000);
	TextDrawColor(Text[gametextdrawforplayer],0xffffffff);
	TextDrawSetProportional(Text[gametextdrawforplayer],1);
	TextDrawSetShadow(Text[gametextdrawforplayer],0);
    }		
    else
    {		
	if(style==3) TextDrawBackgroundColor(Text[gametextdrawforplayer],0x000000ff);		
	TextDrawBackgroundColor(Text[gametextdrawforplayer],0x000000ff);
	TextDrawFont(Text[gametextdrawforplayer],font);
	TextDrawLetterSize(Text[gametextdrawforplayer],0.500000,2.000000);
	TextDrawColor(Text[gametextdrawforplayer],0xffffffff);
	if(style!=3) TextDrawSetOutline(Text[gametextdraw],1);
	TextDrawSetProportional(Text[gametextdrawforplayer],1);
	TextDrawSetShadow(Text[gametextdrawforplayer],1);
    }



    TextDrawShowForPlayer(playerid,Text[gametextdrawforplayer]);
    SetTimerEx("GameTextRemoval",time*1001,false,"d",gametextdrawforplayer);
}

stock DisplayTextForAll(text[], time, font, style) // Max Fonts: 3(0-3)   <->   Max Styles: 12(1-12)
{
	if (gametextdraw >= 99) gametextdraw = 0;
	gametextdraw++;
	new Float:TEXTX,Float:TEXTY;
    if (style == 1) TEXTX = 318, TEXTY = 196;
    else if (style == 2) TEXTX = 246, TEXTY = 142;
    else if (style == 3) TEXTX = 401, TEXTY = 376;
    else if (style == 4) TEXTX = 1, TEXTY = 376;
    else if (style == 5) TEXTX = 575, TEXTY = 54;
    else if (style == 6) TEXTX = 318, TEXTY = 432;
    else if (style == 7) TEXTX = 9, TEXTY = 150;
    else if (style == 8) TEXTX = 371, TEXTY = 413;
    else if (style == 9) TEXTX = 87, TEXTY = 209;
    else if (style == 10) TEXTX = 83, TEXTY = 127;
    else if (style == 11) TEXTX = 390, TEXTY = 192;
    else if (style == 12) TEXTX = 391, TEXTY = 210;
    else TEXTX = 246, TEXTY = 142;
    Text2[gametextdraw] = TextDrawCreate(TEXTX,TEXTY,text);

    if(style==1)
    {		
	TextDrawAlignment(Text2[gametextdraw],2);
	TextDrawBackgroundColor(Text2[gametextdraw],0x000000ff);
	TextDrawFont(Text2[gametextdraw],1);
	TextDrawLetterSize(Text2[gametextdraw],0.449999,2.000000);
	TextDrawColor(Text2[gametextdraw],0xffffffff);
	TextDrawSetProportional(Text2[gametextdraw],1);
	TextDrawSetShadow(Text2[gametextdraw],1);
    }
    else if(style==7)
    {
	TextDrawUseBox(Text2[gametextdraw],1);
	TextDrawBoxColor(Text2[gametextdraw],0x00000066);
	TextDrawTextSize(Text2[gametextdraw],260.000000,0.000000);
	TextDrawAlignment(Text2[gametextdraw],0);
	TextDrawBackgroundColor(Text2[gametextdraw],0x000000ff);
	TextDrawFont(Text2[gametextdraw],font);
	TextDrawLetterSize(Text2[gametextdraw],0.5,1.5);
	TextDrawColor(Text2[gametextdraw],0xffffffcc);
	TextDrawSetOutline(Text2[gametextdraw],0);
	TextDrawSetProportional(Text2[gametextdraw],1);
	TextDrawSetShadow(Text2[gametextdraw],0);
    }
    else if(style==8)
    { 
        TextDrawAlignment(Text2[gametextdraw],2);
        TextDrawBackgroundColor(Text2[gametextdraw],0x000000ff);
        TextDrawFont(Text2[gametextdraw],1);
        TextDrawLetterSize(Text2[gametextdraw],0.499999,2.100000);
        TextDrawColor(Text2[gametextdraw],0xffffffff);
        TextDrawSetProportional(Text2[gametextdraw],1);
        TextDrawSetShadow(Text2[gametextdraw],1);
    }
    else if(style==5)
    {
	TextDrawAlignment(Text2[gametextdraw], 2);
	TextDrawBackgroundColor(Text2[gametextdraw], 255);
	TextDrawFont(Text2[gametextdraw],font);
	TextDrawLetterSize(Text2[gametextdraw], 0.310000, 1.100000);
	TextDrawColor(Text2[gametextdraw], -1);
	TextDrawSetOutline(Text2[gametextdraw], 1);
	TextDrawSetProportional(Text2[gametextdraw], 1);
	TextDrawSetShadow(Text2[gametextdraw], 1);
    }	
    else if(style==6)
    { 
	TextDrawAlignment(Text2[gametextdraw],2);
	TextDrawBackgroundColor(Text2[gametextdraw],0x000000ff);
	TextDrawFont(Text2[gametextdraw],1);
	TextDrawLetterSize(Text2[gametextdraw],0.299999,1.100000);
	TextDrawColor(Text2[gametextdraw],0xffffffff);
	TextDrawSetProportional(Text2[gametextdraw],1);
	TextDrawSetShadow(Text2[gametextdraw],1);
    }
    else if(style==9)
    { 
	TextDrawUseBox(Text2[gametextdraw],1);
	TextDrawBoxColor(Text2[gametextdraw],0xffff0033);
	TextDrawTextSize(Text2[gametextdraw],304.000000,85.000000);
	TextDrawAlignment(Text2[gametextdraw],2);
	TextDrawBackgroundColor(Text2[gametextdraw],0x000000ff);
	TextDrawFont(Text2[gametextdraw],font);
	TextDrawLetterSize(Text2[gametextdraw],0.199999,1.400000);
	TextDrawColor(Text2[gametextdraw],0x00000066);
	TextDrawSetProportional(Text2[gametextdraw],1);
	TextDrawSetShadow(Text2[gametextdraw],0);
    }
    else if(style==10)
    {
	TextDrawUseBox(Text2[gametextdraw],1);
	TextDrawBoxColor(Text2[gametextdraw],0x00000033);
	TextDrawTextSize(Text2[gametextdraw],174.000000,155.000000);
	TextDrawAlignment(Text2[gametextdraw],2);
	TextDrawBackgroundColor(Text2[gametextdraw],0x000000ff);
	TextDrawFont(Text2[gametextdraw],font);
	TextDrawLetterSize(Text2[gametextdraw],0.249999,1.100000);
	TextDrawColor(Text2[gametextdraw],0xffffffff);
	TextDrawSetProportional(Text2[gametextdraw],1);
	TextDrawSetShadow(Text2[gametextdraw],1);
    }
    else if(style==11)
    {
	TextDrawUseBox(Text2[gametextdraw],1);
	TextDrawBoxColor(Text2[gametextdraw],0x00000033);
	TextDrawTextSize(Text2[gametextdraw],82.000000,301.000000);
	TextDrawAlignment(Text2[gametextdraw],2);
	TextDrawBackgroundColor(Text2[gametextdraw],0x000000ff);
	TextDrawFont(Text2[gametextdraw],font);
	TextDrawLetterSize(Text2[gametextdraw],0.299999,1.600002);
	TextDrawColor(Text2[gametextdraw],0xffffffff);
	TextDrawSetProportional(Text2[gametextdraw],1);
	TextDrawSetShadow(Text2[gametextdraw],1);
    }
    else if(style==12)
    {
	TextDrawAlignment(Text2[gametextdraw],2);
	TextDrawBackgroundColor(Text2[gametextdraw],0x000000ff);
	TextDrawFont(Text2[gametextdraw],font);
	TextDrawLetterSize(Text2[gametextdraw],0.199999,1.000000);
	TextDrawColor(Text2[gametextdraw],0xffffffff);
	TextDrawSetProportional(Text2[gametextdraw],1);
	TextDrawSetShadow(Text2[gametextdraw],0);
    }	
    else
    {
	if(style==3) TextDrawBackgroundColor(Text2[gametextdraw],0x000000ff);
	TextDrawBackgroundColor(Text2[gametextdraw],0x000000ff);
	TextDrawFont(Text2[gametextdraw],font);
	TextDrawLetterSize(Text2[gametextdraw],0.500000,2.000000);
	TextDrawColor(Text2[gametextdraw],0xffffffff);
	if(style!=3) TextDrawSetOutline(Text2[gametextdraw],1);
	TextDrawSetProportional(Text2[gametextdraw],1);
	TextDrawSetShadow(Text2[gametextdraw],1);
    }


    TextDrawShowForAll(Text2[gametextdraw]);
    SetTimerEx("GameTextRemoval2",time*1001,false,"d",gametextdraw);
}

public GameTextRemoval(textid)
{
	TextDrawHideForAll(Text[textid]);
	TextDrawDestroy(Text[textid]);
	return true;
}

public GameTextRemoval2(textid)
{
	TextDrawHideForAll(Text2[textid]);
	TextDrawDestroy(Text2[textid]);
	return true;
}

