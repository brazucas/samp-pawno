/*
								seif_walk - Walking styles by Seif
*/
/*x---------------------------------Important-------------------------------------x*/
//**INCLUDES**//
#include <a_samp>
/*x---------------------------------Defining-------------------------------------x*/
//**DEFINES**//
#define WALK_DEFAULT    0
#define WALK_NORMAL     1
#define WALK_PED        2
#define WALK_GANGSTA    3
#define WALK_GANGSTA2   4
#define WALK_OLD        5
#define WALK_FAT_OLD    6
#define WALK_FAT        7
#define WALK_LADY      	8
#define WALK_LADY2      9
#define WALK_WHORE      10
#define WALK_WHORE2     11
#define WALK_DRUNK     	12

#define BRZ_PLAYERS 50

//**VARIABLES**//
new walktime[BRZ_PLAYERS];
new walking_delay[BRZ_PLAYERS];
new bool:walking[BRZ_PLAYERS];
new WalkStyle[BRZ_PLAYERS];
/*x---------------------------------CallBacks-------------------------------------x*/
Walk_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if (((newkeys & KEY_WALK && newkeys & KEY_UP) || (newkeys & KEY_WALK && newkeys & KEY_DOWN) || (newkeys & KEY_WALK && newkeys & KEY_LEFT) || (newkeys & KEY_WALK && newkeys & KEY_RIGHT))
		|| ((oldkeys & KEY_WALK && newkeys & KEY_UP) || (oldkeys & KEY_WALK && newkeys & KEY_DOWN) || (oldkeys & KEY_WALK && newkeys & KEY_LEFT) || (oldkeys & KEY_WALK && newkeys & KEY_RIGHT))
		|| ((newkeys & KEY_WALK && oldkeys & KEY_UP) || (newkeys & KEY_WALK && oldkeys & KEY_DOWN) || (newkeys & KEY_WALK && oldkeys & KEY_LEFT) || (newkeys & KEY_WALK && oldkeys & KEY_RIGHT))
		&& GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
			walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
}

WalkAnimCheck(playerid)
{
	if(IsPlayerConnected(playerid))
	{
		new keys, updown, leftright;
		GetPlayerKeys(playerid,keys,updown,leftright);
		//if( (keys & KEY_ACTION) || (keys & KEY_JUMP) || (keys & KEY_FIRE) || (keys & KEY_CROUCH) || (keys & KEY_SPRINT) || (keys & KEY_HANDBRAKE) || (keys & KEY_SECONDARY_ATTACK) || GetPlayerSpecialAction(playerid)==SPECIAL_ACTION_DUCK )
		if(keys)
		{
			if(walking[playerid]){
			
				ClearAnimations(playerid);
				KillTimer(walktime[playerid]), walking[playerid]=false;	

				walking_delay[playerid]=50;
				
				/*if(keys & KEY_JUMP) ApplyAnimation(playerid,"PED","JUMP_LAUNCH",4.0,0,0,0,0,1);
				else if(keys & KEY_SPRINT) ApplyAnimation(playerid,"PED","RUN_PLAYER",4.0,0,0,0,0,1); 
				else if(keys & KEY_CROUCH) ApplyAnimation(playerid,"PED","WEAPON_CROUCH",4.0,0,0,0,0,1); 
				else if(keys & KEY_FIRE) ApplyAnimation(playerid,"PED","FIGHTA_1",4.0,0,0,0,0,1); 
				else ApplyAnimation(playerid,"PED","WALK_player",4.0,0,0,0,0,1);*/
			}
		}
		else
		{
			if(walking_delay[playerid]){ 
				walking_delay[playerid]--;
			}
			else if(GetPlayerAnimationIndex(playerid)==1250||GetPlayerAnimationIndex(playerid)==1538||GetPlayerAnimationIndex(playerid)==1539){
				walking_delay[playerid]=10;
			}			
			else if((updown != 0) || ((leftright != 0) && (!updown))){
				walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;				
			}	
		}	
	}
}

forward WalkAnim(playerid);
public WalkAnim(playerid)
{
	if(IsPlayerConnected(playerid))
	{
		new keys, updown, leftright;
		GetPlayerKeys(playerid,keys,updown,leftright);
		if(GetPVarInt(playerid,"Andar")==1)
		{
			if( (keys & KEY_ACTION) || (keys & KEY_JUMP) || (keys & KEY_FIRE) || (keys & KEY_CROUCH) || (keys & KEY_SPRINT) || (keys & KEY_HANDBRAKE) || (keys & KEY_SECONDARY_ATTACK) || GetPlayerSpecialAction(playerid)==SPECIAL_ACTION_DUCK  )
			{
				/*if(keys & KEY_JUMP) ApplyAnimation(playerid,"PED","JUMP_LAUNCH",4.0,0,0,0,0,1);
				else if(keys & KEY_SPRINT) ApplyAnimation(playerid,"PED","RUN_PLAYER",4.0,0,0,0,0,1); 
				else if(keys & KEY_CROUCH) ApplyAnimation(playerid,"PED","WEAPON_CROUCH",4.0,0,0,0,0,1); 
				else if(keys & KEY_FIRE) ApplyAnimation(playerid,"PED","FIGHTA_1",4.0,0,0,0,0,1); 
				else ApplyAnimation(playerid,"PED","WALK_player",4.0,0,0,0,0,1); */
				
				walking_delay[playerid]+=50;				
				ClearAnimations(playerid);
				KillTimer(walktime[playerid]), walking[playerid]=false;
			}
			else
			{
				switch(GetPlayerWalkingStyle(playerid))
				{
					case WALK_NORMAL:
					{
						if ((updown & KEY_UP) || (updown & KEY_DOWN) || (leftright & KEY_LEFT) || (leftright & KEY_RIGHT))
						{
							KillTimer(walktime[playerid]), walking[playerid]=false;
							ApplyAnimation(playerid,"PED","WALK_player",4.1,1,1,1,1,1);
							walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
						}
						else ApplyAnimation(playerid,"PED","WALK_player",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
					}
					case WALK_PED:
					{
						if ((updown & KEY_UP) || (updown & KEY_DOWN) || (leftright & KEY_LEFT) || (leftright & KEY_RIGHT))
						{
							KillTimer(walktime[playerid]), walking[playerid]=false;
							ApplyAnimation(playerid,"PED","WALK_civi",4.1,1,1,1,1,1);
							walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
						}
						else ApplyAnimation(playerid,"PED","WALK_civi",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
					}
					case WALK_GANGSTA:
					{
						if ((updown & KEY_UP) || (updown & KEY_DOWN) || (leftright & KEY_LEFT) || (leftright & KEY_RIGHT))
						{
							KillTimer(walktime[playerid]), walking[playerid]=false;
							ApplyAnimation(playerid,"PED","WALK_gang1",4.1,1,1,1,1,1);
							walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
						}
						else ApplyAnimation(playerid,"PED","WALK_gang1",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
					}
					case WALK_GANGSTA2:
					{
						if ((updown & KEY_UP) || (updown & KEY_DOWN) || (leftright & KEY_LEFT) || (leftright & KEY_RIGHT))
						{
							KillTimer(walktime[playerid]), walking[playerid]=false;
							ApplyAnimation(playerid,"PED","WALK_gang2",4.1,1,1,1,1,1);
							walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
						}
						else ApplyAnimation(playerid,"PED","WALK_gang2",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
					}
					case WALK_OLD:
					{
						if ((updown & KEY_UP) || (updown & KEY_DOWN) || (leftright & KEY_LEFT) || (leftright & KEY_RIGHT))
						{
							KillTimer(walktime[playerid]), walking[playerid]=false;
							ApplyAnimation(playerid,"PED","WALK_old",4.1,1,1,1,1,1);
							walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
						}
						else ApplyAnimation(playerid,"PED","WALK_old",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
					}
					case WALK_FAT_OLD:
					{
						if ((updown & KEY_UP) || (updown & KEY_DOWN) || (leftright & KEY_LEFT) || (leftright & KEY_RIGHT))
						{
							KillTimer(walktime[playerid]), walking[playerid]=false;
							ApplyAnimation(playerid,"PED","WALK_fatold",4.1,1,1,1,1,1);
							walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
						}
						else ApplyAnimation(playerid,"PED","WALK_fatold",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
					}
					case WALK_FAT:
					{
						if ((updown & KEY_UP) || (updown & KEY_DOWN) || (leftright & KEY_LEFT) || (leftright & KEY_RIGHT))
						{
							KillTimer(walktime[playerid]), walking[playerid]=false;
							ApplyAnimation(playerid,"PED","WALK_fat",4.1,1,1,1,1,1);
							walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
						}
						else ApplyAnimation(playerid,"PED","WALK_fat",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
					}
					case WALK_LADY:
					{
						if ((updown & KEY_UP) || (updown & KEY_DOWN) || (leftright & KEY_LEFT) || (leftright & KEY_RIGHT))
						{
							KillTimer(walktime[playerid]), walking[playerid]=false;
							ApplyAnimation(playerid,"PED","WOMAN_walknorm",4.1,1,1,1,1,1);
							walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
						}
						else ApplyAnimation(playerid,"PED","WOMAN_walknorm",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
					}
					case WALK_LADY2:
					{
						if ((updown & KEY_UP) || (updown & KEY_DOWN) || (leftright & KEY_LEFT) || (leftright & KEY_RIGHT))
						{
							KillTimer(walktime[playerid]), walking[playerid]=false;
							ApplyAnimation(playerid,"PED","WOMAN_walkbusy",4.1,1,1,1,1,1);
							walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
						}
						else ApplyAnimation(playerid,"PED","WOMAN_walkbusy",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
					}
					case WALK_WHORE:
					{
						if ((updown & KEY_UP) || (updown & KEY_DOWN) || (leftright & KEY_LEFT) || (leftright & KEY_RIGHT))
						{
							KillTimer(walktime[playerid]), walking[playerid]=false;
							ApplyAnimation(playerid,"PED","WOMAN_walkpro",4.1,1,1,1,1,1);
							walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
						}
						else ApplyAnimation(playerid,"PED","WOMAN_walkpro",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
					}
					case WALK_WHORE2:
					{
						if ((updown & KEY_UP) || (updown & KEY_DOWN) || (leftright & KEY_LEFT) || (leftright & KEY_RIGHT))
						{
							KillTimer(walktime[playerid]), walking[playerid]=false;
							ApplyAnimation(playerid,"PED","WOMAN_walksexy",4.1,1,1,1,1,1);
							walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
						}
						else ApplyAnimation(playerid,"PED","WOMAN_walksexy",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
					}
					case WALK_DRUNK:
					{
						if ((updown & KEY_UP) || (updown & KEY_DOWN) || (leftright & KEY_LEFT) || (leftright & KEY_RIGHT))
						{
							KillTimer(walktime[playerid]), walking[playerid]=false;
							ApplyAnimation(playerid,"PED","WALK_drunk",4.1,1,1,1,1,1);
							walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
						}
						else ApplyAnimation(playerid,"PED","WALK_drunk",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
					}
				}
			}	
		}
		else
		{
			switch(GetPlayerWalkingStyle(playerid))
			{
				case WALK_NORMAL:
				{
					if ((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
					{
						KillTimer(walktime[playerid]), walking[playerid]=false;
						ApplyAnimation(playerid,"PED","WALK_player",4.1,1,1,1,1,1);
						walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
					}
					else ApplyAnimation(playerid,"PED","WALK_player",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
				}
				case WALK_PED:
				{
					if ((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
					{
						KillTimer(walktime[playerid]), walking[playerid]=false;
						ApplyAnimation(playerid,"PED","WALK_civi",4.1,1,1,1,1,1);
						walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
					}
					else ApplyAnimation(playerid,"PED","WALK_civi",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
				}
				case WALK_GANGSTA:
				{
					if ((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
					{
						KillTimer(walktime[playerid]), walking[playerid]=false;
						ApplyAnimation(playerid,"PED","WALK_gang1",4.1,1,1,1,1,1);
						walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
					}
					else ApplyAnimation(playerid,"PED","WALK_gang1",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
				}
				case WALK_GANGSTA2:
				{
					if ((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
					{
						KillTimer(walktime[playerid]), walking[playerid]=false;
						ApplyAnimation(playerid,"PED","WALK_gang2",4.1,1,1,1,1,1);
						walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
					}
					else ApplyAnimation(playerid,"PED","WALK_gang2",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
				}
				case WALK_OLD:
				{
					if ((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
					{
						KillTimer(walktime[playerid]), walking[playerid]=false;
						ApplyAnimation(playerid,"PED","WALK_old",4.1,1,1,1,1,1);
						walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
					}
					else ApplyAnimation(playerid,"PED","WALK_old",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
				}
				case WALK_FAT_OLD:
				{
					if ((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
					{
						KillTimer(walktime[playerid]), walking[playerid]=false;
						ApplyAnimation(playerid,"PED","WALK_fatold",4.1,1,1,1,1,1);
						walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
					}
					else ApplyAnimation(playerid,"PED","WALK_fatold",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
				}
				case WALK_FAT:
				{
					if ((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
					{
						KillTimer(walktime[playerid]), walking[playerid]=false;
						ApplyAnimation(playerid,"PED","WALK_fat",4.1,1,1,1,1,1);
						walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
					}
					else ApplyAnimation(playerid,"PED","WALK_fat",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
				}
				case WALK_LADY:
				{
					if ((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
					{
						KillTimer(walktime[playerid]), walking[playerid]=false;
						ApplyAnimation(playerid,"PED","WOMAN_walknorm",4.1,1,1,1,1,1);
						walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
					}
					else ApplyAnimation(playerid,"PED","WOMAN_walknorm",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
				}
				case WALK_LADY2:
				{
					if ((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
					{
						KillTimer(walktime[playerid]), walking[playerid]=false;
						ApplyAnimation(playerid,"PED","WOMAN_walkbusy",4.1,1,1,1,1,1);
						walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
					}
					else ApplyAnimation(playerid,"PED","WOMAN_walkbusy",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
				}
				case WALK_WHORE:
				{
					if ((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
					{
						KillTimer(walktime[playerid]), walking[playerid]=false;
						ApplyAnimation(playerid,"PED","WOMAN_walkpro",4.1,1,1,1,1,1);
						walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
					}
					else ApplyAnimation(playerid,"PED","WOMAN_walkpro",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
				}
				case WALK_WHORE2:
				{
					if ((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
					{
						KillTimer(walktime[playerid]), walking[playerid]=false;
						ApplyAnimation(playerid,"PED","WOMAN_walksexy",4.1,1,1,1,1,1);
						walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
					}
					else ApplyAnimation(playerid,"PED","WOMAN_walksexy",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
				}
				case WALK_DRUNK:
				{
					if ((keys & KEY_WALK && updown & KEY_UP) || (keys & KEY_WALK && updown & KEY_DOWN) || (keys & KEY_WALK && leftright & KEY_LEFT) || (keys & KEY_WALK && leftright & KEY_RIGHT))
					{
						KillTimer(walktime[playerid]), walking[playerid]=false;
						ApplyAnimation(playerid,"PED","WALK_drunk",4.1,1,1,1,1,1);
						walktime[playerid] = SetTimerEx("WalkAnim",200,0,"d",playerid), walking[playerid]=true;
					}
					else ApplyAnimation(playerid,"PED","WALK_drunk",4.0,0,0,0,0,1), KillTimer(walktime[playerid]), walking[playerid]=false;
				}
			}
		}
	}
	return 1;
}

stock SetPlayerWalkingStyle(playerid, style)
{
	WalkStyle[playerid] = style;
}

stock GetPlayerWalkingStyle(playerid)
{
	return WalkStyle[playerid];
}