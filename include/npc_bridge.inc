/**********************************************************************
********* NPC Bridge by Whiteagle @ SA:MP 0.3 - 2009 **********
**********************************************************************/
/*
NPCMessage(TheNPCId, "This is a sample SendChat", 0); // SendChat("This is a sample SendChat")

NPCMessage(TheNPCId, "/mycommand", 1); // SendCommand("/mycommand")

NPCMessage(TheNPCId, "1 TestRecording", 2); // StartRecordingPlayback(PLAYER_RECORDING_TYPE_DRIVER,"TestRecording");

NPCMessage(TheNPCId, "StopRecordingPlayback", 3); // StopRecordingPlayback();

NPCMessage(TheNPCId, "PauseRecordingPlayback", 4); // PauseRecordingPlayback();

NPCMessage(TheNPCId, "ResumeRecordingPlayback", 5); // ResumeRecordingPlayback();
*/
stock ClientMessageBridge(text[])
{
	if(strfind(text, SECRETCODE) != -1)
	{
		new Message[128];
		/*new CurrentChange;
		new start = TOTALCHARS+5;
  		for(new i = start; i <= 128; i++)
		{
				CurrentChange = i - TOTALCHARS;
				Message[CurrentChange] = text[i];
		}*/
		/* This code wasnt made by me as it belongs to the strtok function <Backwardsman97 told me that :D>*/
		new length = strlen(text);
		new idx = TOTALCHARS+5;
		while ((idx < length) && (text[idx] <= ' '))
		{
			idx++;
		}
		new offset = idx;
		while ((idx < length) && ((idx - offset) < (sizeof(Message) - 1)))
		{
			Message[idx - offset] = text[idx];
			idx++;
		}
		/* End of the strtok */
		new ActionId = strval(text[1]);
		if(ActionId == 0) return SendChat(Message);
		else if(ActionId == 1) return SendCommand(Message);
		else if(ActionId == 2)
		{
			new type = strval(Message[0]);
			if(type == 1 || type == 2)
			{
			    new Recording[sizeof(Message)];
			   	/* strtok part2 */
				idx = 2;
				while ((idx < length) && (text[idx] <= ' '))
				{
					idx++;
				}
				offset = idx;
				while ((idx < length) && ((idx - offset) < (sizeof(Recording) - 1)))
				{
					Recording[idx - offset] = Message[idx];
					idx++;
				}
				/* End of the strtok */
				return StartRecordingPlayback(type,Recording);
			}
			else
			{
				print("Error: Type does not exist!");
				return 1;
			}
		}
		else if(ActionId == 3) return StopRecordingPlayback();
		else if(ActionId == 4) return PauseRecordingPlayback();
		else if(ActionId == 5) return ResumeRecordingPlayback();
		else
		{
			printf("ActionId (%d) is not correct", ActionId);
			return 1;
		}
	}
	else
	{
		print("No Code");
		return 1;
 	}
}

stock NPCMessage(TheNPCId, Message[], Action[])
{
	new ActionId;
	if(strcmp(Action, "SendChat", true) == 0) ActionId = 0;
	else if(strcmp(Action, "SendCommand", true) == 0) ActionId = 1;
	else if(strcmp(Action, "StartRecordingPlayback", true) == 0) ActionId = 2;
	else if(strcmp(Action, "StopRecordingPlayback", true) == 0) ActionId = 3;
	else if(strcmp(Action, "PauseRecordingPlayback", true) == 0) ActionId = 4;
	else if(strcmp(Action, "ResumeRecordingPlayback", true) == 0) ActionId = 5;
	else return print("ERROR: ActionID not defined!");
	new MessageToSend[128];
	format(MessageToSend, sizeof(MessageToSend), "[%d] %s %s", ActionId, SECRETCODE, Message);
	if(IsPlayerNPC(TheNPCId))
	{
		SendClientMessage(TheNPCId,0xFFFFFFAA,MessageToSend);
		return 1;
	}
	else
	{
	    printf("Error: NPC %d is not connect!", TheNPCId);
		return 1;
	}
}