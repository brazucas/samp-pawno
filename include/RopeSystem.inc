/*
	print("\n--------------------------------------");
	print("         <Advanced Rope (v1)>           ");
	print("  (c) Trooper([Y]) , 2010 (Nicksoft)    ");
	print("--------------------------------------\n");
*/

#include <a_samp> 
#include <MapAndreas> 

#define players 50
#define ropelength 25 

#define dur 250

new r0pes[players][ropelength];
new r0pestime[players];
new Float:pl_pos[players][5];

stock DestroyRopes(playerid)
{
    for(new destr=0;destr<ropelength;destr++)
	{
	    if(IsValidObject(r0pes[playerid][destr]))
		{ 
			DestroyObject(r0pes[playerid][destr]);
			r0pes[playerid][destr] = INVALID_OBJECT_ID;
		}	
	}
	return 1;
}

forward RSOnPlayerDisconnect(playerid);
public RSOnPlayerDisconnect(playerid)
{
	DestroyRopes(playerid);
	return 1;
}

forward RSOnPlayerDeath(playerid);
public RSOnPlayerDeath(playerid)
{
	EndRope(playerid,true);
	return 1;
}

forward RSOnVehicleDeath(vehicleid);
public RSOnVehicleDeath(vehicleid)
{
	if(IsAvaliableHelicopter(vehicleid))
	{
	    for(new shg=0;shg<=players;shg++)
	    {
	        if(GetPVarInt(shg,"chop_id") == vehicleid && GetPVarInt(shg,"roped") == 1)
	        {
	            EndRope(shg,true);
			}
		}
	}
	return 1;
}

stock IsAvaliableHelicopter(vehicleid){
	switch(GetVehicleModel(vehicleid)){
		case 497,548,563: return 1;
	}
	return 0;
}

forward syncanim(playerid);
public syncanim(playerid)
{
	if(GetPVarInt(playerid,"roped") == 0) return 0;
	SetTimerEx("syncanim",dur,0,"i",playerid);
	ApplyAnimation(playerid,"ped","abseil",4.0,0,0,0,1,0);
	
	if( ++r0pestime[playerid] > 10 || GetVehicleSpeed(GetPVarInt(playerid,"chop_id")) > 10){
		EndRope(playerid,false);
	}
	return 1;
}

stock EndRope(playerid,bool:fordeath)
{
	if(GetPVarInt(playerid,"roped") == 1){
		DisablePlayerCheckpoint(playerid);
	}

	if(!fordeath){
		ClearAnimations(playerid);
		TogglePlayerControllable(playerid,false);
		TogglePlayerControllable(playerid,true);
	}
	
	r0pestime[playerid]=0;
    SetPVarInt(playerid,"roped",0);
    SetPVarInt(playerid,"chop_id",0);	
    DestroyRopes(playerid);
	return 1;
}

forward RSOnPlayerStateChange(playerid,newstate);
public RSOnPlayerStateChange(playerid,newstate)
{
	if(newstate == PLAYER_STATE_PASSENGER)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(IsAvaliableHelicopter(vehicleid))
		{
			SetPVarInt(playerid,"chop_id",vehicleid);
			SetPVarInt(playerid,"roped",0);
		}
		else SetPVarInt(playerid,"chop_id",0);
	}
	return 1;
}

forward RSOnPlayerEnterCheckpoint(playerid);
public RSOnPlayerEnterCheckpoint(playerid)
{
    if(GetPVarInt(playerid,"roped") == 1)
    {
        EndRope(playerid,false);
	}		
	return 1;
}

forward RSOnPlayerKeyStateChange(playerid, newkeys, oldkeys);
public RSOnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(IsPlayerNPC(playerid)) return 0;	
	if(newkeys == 128)
	{
		if(GetPVarInt(playerid,"roped") == 1)
		{
			EndRope(playerid,false);
		}
		else
		{
			if(!IsPlayerInAnyVehicle(playerid)) return 0;
			if(!IsAvaliableHelicopter(GetPlayerVehicleID(playerid))) return 0;
			if(GetPVarInt(playerid,"chop_id") != GetPlayerVehicleID(playerid)) return 0;
			if(GetPlayerVehicleSeat(playerid) == 0) return 1;
	
			GetPlayerPos(playerid,pl_pos[playerid][0],pl_pos[playerid][1],pl_pos[playerid][2]);
			GetPointZPos(pl_pos[playerid][0],pl_pos[playerid][1],pl_pos[playerid][3]);		
			pl_pos[playerid][4] = floatsub(pl_pos[playerid][2],pl_pos[playerid][3]);
			//new str[128];format(str,128,"player:%f solo:%f distancia:%f", pl_pos[playerid][2], pl_pos[playerid][3], pl_pos[playerid][4]);SendClientMessage(playerid,0xAA3333AA,str);
			if(pl_pos[playerid][4] >= ropelength) return SendClientMessage(playerid,0xAA3333AA,"Muito alto!");
			if(pl_pos[playerid][4] <= 2) return RemovePlayerFromVehicle(playerid);
			SetPVarInt(playerid,"roped",1);
			SetPlayerCheckpoint(playerid,pl_pos[playerid][0],pl_pos[playerid][1],/*floatsub(pl_pos[playerid][3],offsetz)*/pl_pos[playerid][3]+5,1.0);
			SetPlayerPos(playerid,pl_pos[playerid][0],pl_pos[playerid][1],floatsub(pl_pos[playerid][2],2));
			SetPlayerVelocity(playerid,0,0,0);
			for(new rep=0;rep!=10;rep++) ApplyAnimation(playerid,"ped","abseil",4.0,0,0,0,1,0);
			for(new cre=0;cre<=pl_pos[playerid][4];cre++)
			{
				r0pes[playerid][cre] = CreateObject(3004,pl_pos[playerid][0],pl_pos[playerid][1],floatadd(pl_pos[playerid][3],cre),87.640026855469,342.13500976563, 350.07507324219);
			}
			SetTimerEx("syncanim",dur,0,"i",playerid);
		}
	}
	return 1;
}