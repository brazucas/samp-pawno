/* First Person Include
 *
 * (c) Copyright 2012, Aeronix (Jack_Wilson)
 * This file is not to be redistributed for any reason, or resold.
 *
 * native SyncCamera(playerid);
 * native SetFirstPerson(playerid);
 * native GetViewMode(playerid);
 *
 */
 
#if defined _FirstPerson_included
	#endinput
#endif 

#define	BRAZUCAS_PLAYERS	50

#define	MODE_THIRDPERSON	1
#define	MODE_FIRSTPERSON	2

#define	SERVER_OBJECT	0
#define	PLAYER_OBJECT	1

#include <YSI\y_hooks>

#define INVALID_DATA -1.11 // mindegy..

enum FPSInfo{
	objectId,
	objectType
}
new FPS_Camera[BRAZUCAS_PLAYERS][FPSInfo];

new Float:FPS_Coord[212][4] = 
{
	{0.330000,0.029999,0.460000},//400
	{0.500000,-0.059999,0.500000},//401
	{0.540000,-0.349999,0.449999},//402
	{0.430000,1.450000,1.029999},//403
	{0.460000,-0.129999,0.610000},//404
	{0.430000,INVALID_DATA,0.430000},//405
	{1.379999,2.559999,INVALID_DATA},//406
	{0.600000,2.890000,0.779999},//407
	{0.439999,2.730000,0.589999},//408
	{0.460000,1.059999,0.500000},//409
	{0.419999,-0.170000,0.569999},//410
	{0.490000,0.050000,0.409999},//411
	{0.460000,-0.129999,0.419999},//412
	{0.490000,0.779999,0.709999},//413
	{0.439999,0.959999,0.899999},//414
	{0.419999,INVALID_DATA,0.340000},//415
	{0.419999,0.949999,0.800000},//416
	{0.439999,3.269999,INVALID_DATA},//417
	{0.519999,0.460000,0.569999},//418
	{0.409999,-0.209999,INVALID_DATA},//419
	{0.519999,0.059999,0.529999},//420
	{0.449999,0.109999,0.389999},//421
	{0.409999,0.070000,0.479999},//422
	{0.579999,0.670000,0.769999},//423
	{0.0,0.2,1.0},//424
	{INVALID_DATA,2.549999,INVALID_DATA},//425
	{0.519999,0.059999,0.529999},//426
	{0.379999,1.100000,0.930000},//427
	{0.649999,0.649999,0.769999},//428
	{0.490000,-0.500000,0.400000},//429
	{0.400000,0.519999,INVALID_DATA},//430
	{0.709999,4.730000,1.330000},//431
	{0.379999,2.769999,INVALID_DATA},//432
	{0.490000,1.159999,1.240000},//433
	{0.259999,-0.449999,0.409999},//434
	{INVALID_DATA,INVALID_DATA,INVALID_DATA},//435
	{0.400000,-0.170000,0.540000},//436
	{0.209999,4.289999,INVALID_DATA},//437
	{0.460000,0.419999,0.439999},//438
	{0.490000,-0.540000,0.400000},//439
	{0.500000,0.750000,0.569999},//440
	{0.059999,-0.070000,INVALID_DATA},//441
	{0.490000,0.270000,0.469999},//442
	{0.389999,2.880000,1.029999},//443
	{0.540000,0.349999,1.340000},//444
	{0.479999,-0.029999,0.509999},//445
	{0.689999,0.250000,INVALID_DATA},//446
	{0.419999,0.949999,INVALID_DATA},//447
	{0.0,0.23,0.8},//448
	{0.460000,3.359999,INVALID_DATA},//449
	{INVALID_DATA,INVALID_DATA,INVALID_DATA},//450
	{0.529999,-0.200000,0.340000},//451
	{0.500000,2.980000,INVALID_DATA},//452
	{0.409999,1.570000,INVALID_DATA},//453
	{-0.560000,2.730000,INVALID_DATA},//454
	{0.490000,1.169999,1.220000},//455
	{0.419999,1.389999,0.889999},//456
	{0.340000,-0.270000,0.550000},//457
	{0.449999,0.140000,0.419999},//458
	{0.490000,0.779999,0.709999},//459
	{0.319999,0.280000,INVALID_DATA},//460
	{0.0,0.27,1.0},//461
	{0.0,0.27,1.0},//462
	{0.0,0.27,1.0},//463
	{INVALID_DATA,INVALID_DATA,INVALID_DATA},//464
	{INVALID_DATA,INVALID_DATA,INVALID_DATA},//465
	{0.500000,0.150000,0.529999},//466
	{0.460000,0.109999,0.519999},//467
	{0.0,0.2,0.9},//468
	{0.419999,0.949999,INVALID_DATA},//469
	{0.529999,-0.039999,0.720000},//470
	{0.0, -0.5, 0.9},//471
	{-0.200000,-0.159999,INVALID_DATA},//472
	{INVALID_DATA,0.579999,INVALID_DATA},//473
	{0.490000,-0.300000,0.560000},//474
	{0.419999,-0.129999,0.439999},//475
	{INVALID_DATA,-0.449999,INVALID_DATA},//476
	{0.550000,-0.250000,0.460000},//477
	{0.439999,0.090000,0.529999},//478
	{0.490000,-0.070000,0.629999},//479
	{0.409999,-0.280000,0.430000},//480
	{0.0,0.22,1.13},//481
	{0.469999,0.529999,0.540000},//482
	{0.379999,1.649999,0.509999},//483
	{INVALID_DATA,-5.010000,INVALID_DATA},//484
	{0.150000,-0.449999,INVALID_DATA},//485
	{INVALID_DATA,-0.389999,INVALID_DATA},//486
	{0.460000,1.620000,INVALID_DATA},//487
	{0.449999,0.730000,INVALID_DATA},//488
	{0.500000,-0.090000,0.750000},//489
	{0.529999,0.460000,0.750000},//490
	{0.430000,-0.280000,0.439999},//491
	{0.460000,0.140000,0.550000},//492
	{-0.670000,0.600000,INVALID_DATA},//493
	{0.479999,-0.289999,0.449999},//494
	{0.490000,INVALID_DATA,0.620000},//495
	{0.479999,-0.250000,0.529999},//496
	{0.460000,1.620000,INVALID_DATA},//497
	{0.730000,1.379999,1.049999},//498
	{0.449999,0.209999,0.629999},//499
	{0.449999,-0.239999,0.589999},//500
	{INVALID_DATA,INVALID_DATA,INVALID_DATA},//501
	{0.419999,-0.119999,0.449999},//502
	{0.409999,-0.289999,0.479999},//503
	{0.460000,0.180000,INVALID_DATA},//504
	{0.500000,-0.090000,0.750000},//505
	{0.469999,-0.340000,0.370000},//506
	{0.540000,0.050000,0.500000},//507
	{0.540000,1.419999,0.409999},//508
	{INVALID_DATA,-0.479999,INVALID_DATA},//509
	{0.0,0.39,1.25},//510
	{0.419999,2.009999,INVALID_DATA},//511
	{INVALID_DATA,-0.219999,INVALID_DATA},//512
	{INVALID_DATA,-0.910000,INVALID_DATA},//513
	{0.449999,1.600000,0.910000},//514
	{0.560000,1.340000,0.819999},//515
	{0.469999,0.070000,0.540000},//516
	{0.509999,-0.019999,0.519999},//517
	{0.509999,0.070000,0.449999},//518
	{0.349999,5.179999,INVALID_DATA},//519
	{INVALID_DATA,2.839999,INVALID_DATA},//520
	{0.0,0.34,1.0},//521
	{0.0,0.27,1.0},//522
	{0.0,0.27,1.0},//523
	{0.490000,1.450000,0.500000},//524
	{0.509999,0.259999,1.029999},//525
	{0.469999,-0.079999,0.389999},//526
	{0.409999,-0.019999,0.579999},//527
	{0.500000,-0.140000,0.670000},//528
	{0.490000,-0.079999,0.620000},//529
	{INVALID_DATA,-0.319999,INVALID_DATA},//530
	{INVALID_DATA,-0.460000,INVALID_DATA},//531
	{1.009999,3.000000,INVALID_DATA},//532
	{0.479999,-0.239999,0.500000},//533
	{0.589999,0.029999,0.370000},//534
	{0.419999,0.009999,0.569999},//535
	{0.519999,-0.219999,0.349999},//536
	{0.460000,5.130000,INVALID_DATA},//537
	{0.709999,5.989999,INVALID_DATA},//538
	{INVALID_DATA,0.349999,INVALID_DATA},//539
	{0.519999,-0.059999,0.389999},//540
	{0.479999,-0.119999,0.400000},//541
	{0.509999,-0.150000,0.519999},//542
	{0.449999,0.090000,0.569999},//543
	{0.600000,2.509999,0.870000},//544
	{0.330000,-0.340000,0.479999},//545
	{0.569999,-0.159999,0.509999},//546
	{0.519999,INVALID_DATA,0.589999},//547
	{0.649999,4.570000,INVALID_DATA},//548
	{0.469999,0.250000,0.490000},//549
	{0.519999,0.050000,0.400000},//550
	{0.490000,0.109999,0.519999},//551
	{0.620000,0.639999,1.000000},//552
	{0.430000,9.529999,INVALID_DATA},//553
	{0.540000,0.100000,0.689999},//554
	{0.439999,-0.170000,0.379999},//555
	{0.540000,0.100000,1.309999},//556
	{0.540000,INVALID_DATA,1.320000},//557
	{0.540000,-0.239999,0.569999},//558
	{0.479999,-0.189999,0.469999},//559
	{0.479999,0.109999,0.540000},//560
	{0.519999,0.090000,0.490000},//561
	{0.509999,-0.050000,0.519999},//562
	{0.419999,2.640000,INVALID_DATA},//563
	{0.059999,-0.070000,INVALID_DATA},//564
	{0.479999,-0.059999,0.430000},//565
	{0.540000,0.090000,0.550000},//566
	{0.509999,0.250000,0.379999},//567
	{0.0,0.0,1.0},//568
	{INVALID_DATA,INVALID_DATA,INVALID_DATA},//569
	{INVALID_DATA,1.960000,INVALID_DATA},//570
	{INVALID_DATA,-0.180000,INVALID_DATA},//571
	{INVALID_DATA,-0.620000,INVALID_DATA},//572
	{0.560000,2.029999,0.829999},//573
	{0.230000,0.550000,0.759999},//574
	{0.500000,0.059999,0.709999},//575
	{0.469999,-0.159999,0.589999},//576
	{1.289999,21.059999,INVALID_DATA},//577
	{0.469999,3.430000,0.680000},//578
	{0.460000,-0.159999,0.800000},//579
	{0.540000,-0.009999,0.720000},//580
	{INVALID_DATA,-0.400000,INVALID_DATA},//581
	{0.419999,0.560000,0.720000},//582
	{INVALID_DATA,-1.009999,1.090000},//583
	{INVALID_DATA,INVALID_DATA,INVALID_DATA},//584
	{0.469999,INVALID_DATA,0.680000},//585
	{INVALID_DATA,-0.419999,INVALID_DATA},//586
	{0.519999,-0.239999,0.449999},//587
	{0.699999,2.289999,1.159999},//588
	{0.419999,-0.019999,0.750000},//589
	{INVALID_DATA,INVALID_DATA,INVALID_DATA},//590
	{INVALID_DATA,INVALID_DATA,INVALID_DATA},//591
	{0.560000,12.510000,INVALID_DATA},//592
	{0.319999,0.029999,INVALID_DATA},//593
	{0.059999,-0.070000,INVALID_DATA},//594
	{0.479999,0.899999,INVALID_DATA},//595
	{0.519999,0.059999,0.529999},//596
	{0.519999,0.059999,0.529999},//597
	{0.519999,0.059999,0.540000},//598
	{0.500000,-0.090000,0.750000},//599
	{0.519999,0.059999,0.500000},//600
	{0.529999,-0.300000,INVALID_DATA},//601
	{0.479999,-0.119999,0.409999},//602
	{0.519999,-0.419999,0.349999},//603
	{0.500000,0.150000,0.529999},//604
	{0.449999,0.090000,0.569999},//605
	{INVALID_DATA,INVALID_DATA,INVALID_DATA},//606
	{INVALID_DATA,INVALID_DATA,INVALID_DATA},//607
	{INVALID_DATA,INVALID_DATA,INVALID_DATA},//608
	{0.730000,1.379999,1.049999},//609
	{INVALID_DATA,INVALID_DATA,INVALID_DATA},//610
	{INVALID_DATA,INVALID_DATA,INVALID_DATA}//611

};

hook OnPlayerConnect(playerid)
{
	FPS_Camera[playerid][objectId] = CreateObject(19300, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	FPS_Camera[playerid][objectType] = SERVER_OBJECT;
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	DestroyCameraObject(playerid);
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	SyncCamera(playerid);
}

hook OnPlayerSpawn(playerid)
{
	SyncCamera(playerid);
}
	
public SyncCamera(playerid)
{
	if(GetPVarInt(playerid, "FirstPerson") == 1)
	{
		SetCameraBehindPlayer(playerid);
		if(!IsPlayerInAnyVehicle(playerid))
		{
			DestroyCameraObject(playerid);					
			FPS_Camera[playerid][objectId] = CreateObject(19300, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			FPS_Camera[playerid][objectType] = SERVER_OBJECT;
			AttachObjectToPlayer(FPS_Camera[playerid][objectId], playerid, 0.0, 0.15, 0.65, 0.0, 0.0, 0.0);
			AttachCameraToObject(playerid, FPS_Camera[playerid][objectId]);
		}
		else if(IsPlayerInAnyVehicle(playerid))
		{
			DestroyCameraObject(playerid);
			new slot = GetVehicleModel(GetPlayerVehicleID(playerid))-400;
			if(FPS_Coord[slot][0] == INVALID_DATA || INVALID_DATA == FPS_Coord[slot][1] || INVALID_DATA == FPS_Coord[slot][2] ) {		
				FPS_Camera[playerid][objectId] = CreatePlayerObject(playerid,19300, 0.0000, -1282.9984, 10.1493, 0.0000, -1, -1, 100);
				AttachPlayerObjectToVehicle(playerid,FPS_Camera[playerid][objectId],GetPlayerVehicleID(playerid),-0.314999, -0.195000,0.510000, 0.000000, 0.000000, 0.000000);
			}
			else if(GetPlayerVehicleSeat(playerid)!=0 && GetPlayerVehicleSeat(playerid)!=1){
				FPS_Camera[playerid][objectId] = CreatePlayerObject(playerid,0, 0.0,0.0,0.0,0.0,0.0,0.0);
				AttachPlayerObjectToVehicle(playerid,FPS_Camera[playerid][objectId],GetPlayerVehicleID(playerid),(GetPlayerVehicleSeat(playerid)==2)?(-FPS_Coord[slot][0]):(FPS_Coord[slot][0]),-1,FPS_Coord[slot][2], 0.000000, 0.000000, 0.000000);			
			}
			else{			
				FPS_Camera[playerid][objectId] = CreatePlayerObject(playerid,0, 0.0,0.0,0.0,0.0,0.0,0.0);
				switch(GetVehicleModel(GetPlayerVehicleID(playerid))){
					case 522,461,462,463,521,523,510,481,448: AttachPlayerObjectToVehicle(playerid,FPS_Camera[playerid][objectId],GetPlayerVehicleID(playerid),FPS_Coord[slot][0],(GetPlayerVehicleSeat(playerid)==0)?(FPS_Coord[slot][1]):(-FPS_Coord[slot][1]),FPS_Coord[slot][2], 0.000000, 0.000000, 0.000000);
					default: AttachPlayerObjectToVehicle(playerid,FPS_Camera[playerid][objectId],GetPlayerVehicleID(playerid),(GetPlayerVehicleSeat(playerid)==0)?(-FPS_Coord[slot][0]):(FPS_Coord[slot][0]),FPS_Coord[slot][1],FPS_Coord[slot][2], 0.000000, 0.000000, 0.000000);
				}				
			}	
			FPS_Camera[playerid][objectType] = PLAYER_OBJECT;			
			AttachCameraToPlayerObject(playerid,FPS_Camera[playerid][objectId]);
		}
		else
		{
			SetCameraBehindPlayer(playerid);
		}
	}
	return 1;
}

stock DestroyCameraObject(playerid){
	switch(FPS_Camera[playerid][objectType]){
		case SERVER_OBJECT:DestroyObject(FPS_Camera[playerid][objectId]);
		case PLAYER_OBJECT:DestroyPlayerObject(playerid,FPS_Camera[playerid][objectId]);
	}
	return 1;
}

stock Test_FirstPerson(playerid,Float:x,Float:y,Float:z){
	DestroyCameraObject(playerid);
	FPS_Camera[playerid][objectId] = CreatePlayerObject(playerid,0,0.0,0.0,0.0,0.0,0.0,0.0);
	FPS_Camera[playerid][objectType] = PLAYER_OBJECT;
	AttachPlayerObjectToVehicle(playerid,FPS_Camera[playerid][objectId],GetPlayerVehicleID(playerid),x,y,z, 0.000000, 0.000000, 0.000000);
	AttachCameraToPlayerObject(playerid,FPS_Camera[playerid][objectId]);
	new tmsg[128];format(tmsg,sizeof(tmsg),"Model:%d|Seatid:%d|X:%f|Y:%f|Z:%f",GetVehicleModel(GetPlayerVehicleID(playerid)),GetPlayerVehicleSeat(playerid),x,y,z);SendClientMessage(playerid,0x808080FF,tmsg);	
	return 1;
}

public SetFirstPerson(playerid, status)
{
	if(status)
	{
		SetPVarInt(playerid, "FirstPerson", 1);
		SyncCamera(playerid);
		
	}
	else if(!status)
	{
		DestroyCameraObject(playerid);
	    DeletePVar(playerid, "FirstPerson");
		SetCameraBehindPlayer(playerid);
	}
}

public GetViewMode(playerid)
{
	if(GetPVarInt(playerid, "FirstPerson") == 1)
	{
		return MODE_FIRSTPERSON;
	}
	else
	{
		return MODE_THIRDPERSON;
	}
}

forward SyncCamera(playerid);
forward CameraPosition(playerid);
forward SetFirstPerson(playerid);
forward GetViewMode(playerid);