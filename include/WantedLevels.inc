#include <a_samp>

stock InitWantedLevels()
{
	DoInit();
	return 1;
}

new Text:tStar7, Text:tStar8, Text:tStar9, Text:tStar10, Text:tStar11, Text:tStar12;

Text:CreateStarTD( starnum )
{
	new Text:tStar = TextDrawCreate( 503.5 - ( 18 * ( starnum - 7 ) ), 102.1, "]" );

	TextDrawColor          ( tStar, 0x906210FF );
	TextDrawBackgroundColor( tStar, 0x000000AA );
	TextDrawFont           ( tStar,          2 );
	TextDrawSetShadow      ( tStar,          0 );
	TextDrawSetProportional( tStar,       true );
	TextDrawLetterSize     ( tStar,  0.6,  2.4 );
	TextDrawAlignment      ( tStar,          3 );
	TextDrawSetOutline     ( tStar,          1 );

	return tStar;
}

DoInit()
{
	tStar7  = CreateStarTD(  7 );
	tStar8  = CreateStarTD(  8 );
	tStar9  = CreateStarTD(  9 );
	tStar10 = CreateStarTD( 10 );
	tStar11 = CreateStarTD( 11 );
	tStar12 = CreateStarTD( 12 );
}

forward Wlevel_UPD(playerid);
public  Wlevel_UPD(playerid)
{
	if ( GetPlayerWantedLevel( playerid ) >= 7 ) TextDrawShowForPlayer( playerid, tStar7 ); else TextDrawHideForPlayer( playerid, tStar7 );
	if ( GetPlayerWantedLevel( playerid ) >= 8 ) TextDrawShowForPlayer( playerid, tStar8 ); else TextDrawHideForPlayer( playerid, tStar8 );
	if ( GetPlayerWantedLevel( playerid ) >= 9 ) TextDrawShowForPlayer( playerid, tStar9 ); else TextDrawHideForPlayer( playerid, tStar9 );
	if ( GetPlayerWantedLevel( playerid ) >= 10 ) TextDrawShowForPlayer( playerid, tStar10 ); else TextDrawHideForPlayer( playerid, tStar10 );
	if ( GetPlayerWantedLevel( playerid ) >= 11 ) TextDrawShowForPlayer( playerid, tStar11 ); else TextDrawHideForPlayer( playerid, tStar11 );
	if ( GetPlayerWantedLevel( playerid ) >= 12 ) TextDrawShowForPlayer( playerid, tStar12 ); else TextDrawHideForPlayer( playerid, tStar12 );
}