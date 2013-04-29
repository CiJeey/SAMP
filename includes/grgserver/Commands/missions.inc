CMD:missions(playerID, params[], StringID:94("Show available missions"))
{
	switch (PVar:playerID[JOBID])
	{
		case JOB_TAXI, JOB_ADAC, JOB_PARAMEDIC, JOB_POLICE, JOB_TRUCKER:
		{
			ShowDialog:Accept(playerID);
		}
		default:
		{
			return COMMAND_PERMISSION_DENIED;
		}
	}
	return COMMAND_OK;
}