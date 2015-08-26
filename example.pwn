#include <a_samp>
#include <counters>

main(){}

new TimeSinceConnect[MAX_PLAYERS], TimeSinceDeath[MAX_PLAYERS];

public OnPlayerConnect(playerid)
{
	TimeSinceConnect[playerid] = StartPlayerCounter(playerid);
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	if(IsValidPlayerCounter(playerid, TimeSinceDeath[playerid]))
		StopPlayerCounter(playerid, TimeSinceDeath[playerid]);
	
	TimeSinceDeath[playerid] = StartPlayerCounter(playerid);
	return 1;
}

public OnPlayerUpdate(playerid)
{
	//Kick player after being online for 10 minutes (10 * 60 = 10 minutes).
	if(GetPlayerCounterTime(playerid, TimeSinceConnect[playerid]) > (10 * 60))
		Kick(playerid);
		
	//Kill player every 5 minutes.
	if(GetPlayerCounterTime(playerid, TimeSinceDeath[playerid]) > (5 * 60))
		SetPlayerHealth(playerid, 0.0);
		
	return 1;
}
