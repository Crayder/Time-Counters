#include <a_samp>
#include <YSI\y_iterate>

#if !defined MAX_COUNTERS
	#define MAX_COUNTERS 500
#endif

#define INVALID_COUNTER (-1)

enum pc_CounterMode {COUNTER_MODE_SECONDS, COUNTER_MODE_MINUTES}

static
	//Player
	Iterator:pc_pCounter[MAX_PLAYERS]<MAX_COUNTERS>,
	pc_pTimeSet[MAX_PLAYERS][MAX_COUNTERS],
	pc_CounterMode:pc_pMode[MAX_PLAYERS][MAX_COUNTERS],
	//Global
	Iterator:pc_Counter<MAX_COUNTERS>,
	pc_TimeSet[MAX_COUNTERS],
	pc_CounterMode:pc_Mode[MAX_COUNTERS];

//Player
stock StartPlayerCounter(playerid, pc_CounterMode:countermode = COUNTER_MODE_SECONDS)
{
	if(!IsPlayerConnected(playerid))
		return INVALID_COUNTER;

	new counterid = _:Iter_Free(pc_pCounter[playerid]);	
	if(counterid == cellmin)
		return INVALID_COUNTER;

	pc_pTimeSet[playerid][counterid] = gettime();
	pc_pMode[playerid][counterid] = countermode;
	Iter_Add(pc_pCounter[playerid], counterid);	
	return counterid;
}

stock StopPlayerCounter(playerid, counterid)
{
	if(!IsPlayerConnected(playerid) || !IsValidPlayerCounter(playerid, counterid))
		return 0;

	pc_pTimeSet[playerid][counterid] = 0;
	Iter_Remove(pc_pCounter[playerid], counterid);	
	return 1;
}

stock GetPlayerCounterTime(playerid, counterid)
{
	if(!IsPlayerConnected(playerid) || !IsValidPlayerCounter(playerid, counterid))
		return -1;	
		
	if(pc_pMode[playerid][counterid] == COUNTER_MODE_SECONDS)
		return gettime() - pc_pTimeSet[playerid][counterid];
	if(pc_pMode[playerid][counterid] == COUNTER_MODE_MINUTES)
		return (gettime() - pc_pTimeSet[playerid][counterid]) / 60;
	
	return -1;
}

stock IsValidPlayerCounter(playerid, counterid)
	return Iter_Contains(pc_pCounter[playerid], counterid) ? 1 : 0;

//Global
stock StartCounter(pc_CounterMode:countermode = COUNTER_MODE_SECONDS)
{
	new counterid = _:Iter_Free(pc_Counter);	
	if(counterid == cellmin)
		return INVALID_COUNTER;

	pc_TimeSet[counterid] = gettime();
	pc_Mode[playerid][counterid] = countermode;
	Iter_Add(pc_Counter, counterid);	
	return counterid;
}

stock StopCounter(counterid)
{
	if(!IsValidCounter(counterid))
		return 0;

	pc_TimeSet[counterid] = 0;
	Iter_Remove(pc_Counter, counterid);	
	return 1;
}

stock GetCounterTime(counterid)
{
	if(!IsValidCounter(counterid))
		return -1;
		
	if(pc_Mode[counterid] == COUNTER_MODE_SECONDS)
		return gettime() - pc_TimeSet[counterid];
	if(pc_Mode[counterid] == COUNTER_MODE_MINUTES)
		return (gettime() - pc_TimeSet[counterid]) / 60;
	
	return -1;
}

stock IsValidCounter(counterid)
	return Iter_Contains(pc_Counter, counterid) ? 1 : 0;

stock ConvertSeconds(unix, &secs, &mins, &hours)
{
	hours = unix / 3600;
	mins = (unix - (hours * 3600)) / 60;
	secs = unix % 60;
}

//Hook Method 7 becaue it's the only one I know by heart. It is like the best though.
public OnPlayerConnect(playerid)
{
    Iter_Clear(pc_pCounter[playerid]);

    #if defined PT_OnPlayerConnect
        return PT_OnPlayerConnect(playerid);
    #else
        return 1;
    #endif
}


public OnGameModeInit()
{
    Iter_Init(pc_pCounter);

    #if defined PT_OnGameModeInit
        return PT_OnGameModeInit();
    #else
        return 1;
    #endif
}

#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect PT_OnPlayerConnect

#if defined PT_OnPlayerConnect
    forward PT_OnPlayerConnect(playerid);
#endif


#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif

#define OnGameModeInit PT_OnGameModeInit

#if defined PT_OnGameModeInit
    forward PT_OnGameModeInit();
#endif
