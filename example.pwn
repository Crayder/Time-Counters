#include <a_samp>
#include <ptimes>

new TimeSinceConnect[MAX_PLAYERS], TimeSinceDeath[MAX_PLAYERS];

public OnPlayerConnect(playerid)
{
	TimeSinceConnect[playerid] = CreatePlayerTimer(playerid);
	return;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	if(IsValidPlayerTimer(TimeSinceDeath[playerid]))
		DestroyPlayerTimer(playerid);
	
	TimeSinceDeath[playerid] = CreatePlayerTimer(playerid);
	return 1;
}

public OnPlayerUpdate(playerid)
{
	//Kick player after being online for 10 minutes (10 * 60 = 10 minutes).
	if(GetPlayerTimerTime(playerid, TimeSinceConnect[playerid]) > (10 * 60))
		Kick(playerid);
		
	//Kill player every 5 minutes.
	if(GetPlayerTimerTime(playerid, TimeSinceDeath[playerid]) > (5 * 60))
		SetPlayerHealth(playerid, 0.0);
		
	return 1;
}
