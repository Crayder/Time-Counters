#include <a_samp>
#include <YSI\y_iterate>

#if !defined MAX_PTIMES
	#define MAX_PTIMES 500
#endif

#define INVALID_PTIMER (-1)

static Iterator:pt_Timer[MAX_PLAYERS]<MAX_PTIMES>;
static pt_TimeSet[MAX_PLAYERS][MAX_PTIMES];

stock CreatePlayerTimer(playerid)
{
	if(!IsPlayerConnected(playerid))
		return INVALID_PTIMER;

	new timerid = _:Iter_Free(pt_Timer[playerid]);	
	if(timerid == cellmin)
		return INVALID_PTIMER;

	pt_TimeSet[playerid][timerid] = gettime();
	Iter_Add(pt_Timer[playerid], timerid);	
	return timerid;
}

stock DestroyPlayerTimer(playerid)
{
	if(!IsPlayerConnected(playerid) || !IsValidPlayerTimer(playerid, timerid))
		return 0;

	pt_TimeSet[playerid][timerid] = 0;
	Iter_Remove(pt_Timer[playerid], timerid);	
	return 1;
}

stock GetPlayerTimerTime(playerid, timerid)
{
	if(!IsPlayerConnected(playerid) || !IsValidPlayerTimer(playerid, timerid))
		return -1;
		
	return gettime() - pt_TimeSet[playerid][timerid];
}

stock IsValidPlayerTimer(playerid, timerid)
	return Iter_Contains(pt_Timer[playerid], timerid) ? 1 : 0;

stock ConvertSeconds(unix, &secs, &mins, &hours)
{
	hours = unix / 3600;
	mins = (unix - (hours * 3600)) / 60;
	secs = unix % 60;
}

//Hook Method 7 becaue it's the only one I know by heart. It is like the best though.
public OnPlayerConnect(playerid)
{
    Iter_Clear(pt_Timer[playerid]);

    #if defined PT_OnPlayerConnect
        return PT_OnPlayerConnect(playerid);
    #else
        return 1;
    #endif
}


public OnGameModeInit()
{
    Iter_Init(pt_Timer);

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
