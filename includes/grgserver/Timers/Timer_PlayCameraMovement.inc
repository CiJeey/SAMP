Timer:PlayCameraMovement(playerID, movementID)
{
	MySQLQuery("SELECT * FROM `cameramovements` WHERE `ID` = '%d'", movementID);
	mysql_store_result();
	new Float:startMoveX = floatstr(GetMySQLField("StartMoveX"));
	new Float:startMoveY = floatstr(GetMySQLField("StartMoveY"));
	new Float:startMoveZ = floatstr(GetMySQLField("StartMoveZ"));
	new Float:endMoveX = floatstr(GetMySQLField("EndMoveX"));
	new Float:endMoveY = floatstr(GetMySQLField("EndMoveY"));
	new Float:endMoveZ = floatstr(GetMySQLField("EndMoveZ"));
	new Float:startLookX = floatstr(GetMySQLField("StartLookX"));
	new Float:startLookY = floatstr(GetMySQLField("StartLookY"));
	new Float:startLookZ = floatstr(GetMySQLField("StartLookZ"));
	new Float:endLookX = floatstr(GetMySQLField("EndLookX"));
	new Float:endLookY = floatstr(GetMySQLField("EndLookY"));
	new Float:endLookZ = floatstr(GetMySQLField("EndLookZ"));
	new time = strval(GetMySQLField("Time"));
	new waitEnd = strval(GetMySQLField("WaitEnd"));
	mysql_free_result();
	if (!endMoveX && !endMoveY && !endMoveZ)
	{
		endMoveX = startMoveX;
		endMoveY = startMoveY;
		endMoveZ = startMoveZ;
	}
	InterpolateCameraPos(playerID, startMoveX, startMoveY, startMoveZ, endMoveX, endMoveY, endMoveZ, time, CAMERA_CUT);
	if (!endLookX && !endLookY && !endLookZ)
	{
		endLookX = startLookX;
		endLookY = startLookY;
		endLookZ = startLookZ;
	}
	InterpolateCameraLookAt(playerID, startLookX, startLookY, startLookZ, endLookX, endLookY, endLookZ, time, CAMERA_CUT);
	if (waitEnd < 0)
	{
		TogglePlayerControllable(playerID, true);
	}
	else
	{
		SetTimerEx("Timer_ResetCameraMovement", time + waitEnd, false, "d", playerID);
	}
}