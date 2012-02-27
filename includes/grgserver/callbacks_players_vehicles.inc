public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if (IsPlayerNPC(playerid))
	{
		return true;
	}
	if (!ispassenger)
	{
		SetVehicleEngineState(vehicleid, false);
		if (!vehicles[vehicleid][VEHICLE_SAVEID] && !permissions[playerid][PERMISSION_MAPPER])
		{
			SendClientMessage(playerid, COLOR_ERROR, "Dieses Fahrzeug kann nur von der Gruppe 'Mapper' verwendet werden!");
			RemovePlayerFromVehicle(playerid);
		}
		new ownerUserID = strval(GetMySQLValue("savedvehicles", "OwnerUserID", "ID", val2str(vehicles[vehicleid][VEHICLE_SAVEID])));
		if (!ownerUserID)
		{
			ShowDialog(playerid, DIALOG_BUYVEHICLE, FormatMoney(floatstr(GetMySQLValue("savedvehicles", "Price", "ID", val2str(vehicles[vehicleid][VEHICLE_SAVEID])))));
		}
		if (ownerUserID != GetUserID(playerid))
		{
			SendClientMessage(playerid, COLOR_ERROR, "Dieses Fahrzeug geh�rt bereits ein anderer Spieler");
			RemovePlayerFromVehicle(playerid);
		}
	}
	if (GetPVarInt(playerid, "RadioOn") && GetPVarInt(playerid, "LastRadioStation"))
	{
		PlayRadioStation(playerid, GetPVarInt(playerid, "LastRadioStation"));
	}
	return true;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !IsPlayerNPC(playerid))
	{
		SetVehicleEngineState(vehicleid, false);
	}
	SaveVehicle(vehicleid, GetPlayerInterior(playerid));
	StopRadioStation(playerid);
	return true;
}

public OnVehicleDeath(vehicleid, killerid)
{
	if (vehicles[vehicleid][VEHICLE_SAVEID])
	{
		MySQLQuery("DELETE FROM `savedvehicles` WHERE `ID` = '%d'", vehicles[vehicleid][VEHICLE_SAVEID]);
		MySQLQuery("DELETE FROM `vehiclecomponents` WHERE `ID` = '%d'", vehicles[vehicleid][VEHICLE_SAVEID]);
		vehicles[vehicleid][VEHICLE_SAVEID] = 0;
	}
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	if (vehicles[vehicleid][VEHICLE_SAVEID])
	{
		MySQLQuery("REPLACE INTO `vehiclecomponents` (`VehicleID`, `Slot`, `Component`) VALUES('%d', '%d', '%d')", vehicles[vehicleid][VEHICLE_SAVEID], GetVehicleComponentType(componentid), componentid);
	}
	return true;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	if (vehicles[vehicleid][VEHICLE_SAVEID])
	{
		MySQLQuery("UPDATE `savedvehicles` SET `Paintjob` = '%d' WHERE `ID` = '%d'", paintjobid, vehicles[vehicleid][VEHICLE_SAVEID]);
	}
	return true;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	if (vehicles[vehicleid][VEHICLE_SAVEID])
	{
		MySQLQuery("UPDATE `savedvehicles` SET `Color1` = '%d', `Color2` = '%d' WHERE `ID` = '%d'", color1, color2, vehicles[vehicleid][VEHICLE_SAVEID]);
	}
	return true;
}

public OnVehicleSpawn(vehicleid)
{
	DestroyVehicle(vehicleid);
}