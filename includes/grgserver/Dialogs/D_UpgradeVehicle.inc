ShowDialog:UPGRADEVEHICLE(playerID)
{
	new options[1024];
	AddLine(options, LanguageString(playerID, 395));
	AddLine(options, LanguageString(playerID, 375));
	CreateDialog(playerID, "UPGRADEVEHICLE", DIALOG_STYLE_LIST, LanguageString(playerID, 374), options, LanguageString(playerID, 177), LanguageString(playerID, 165));
}

DialogResponse:UPGRADEVEHICLE(playerID, response, listItem, inputText[])
{
	if (!strcmp(inputText, LanguageString(playerID, 395)))// Front headlights
	{
		PVar:playerID[UPGRADEVEHICLE_LIGHTTYPE] = 1;
		ShowDialog:UPGRADEVEHICLE_LIGHT(playerID);
	}
	if (!strcmp(inputText, LanguageString(playerID, 375)))// Neon lights
	{
		PVar:playerID[UPGRADEVEHICLE_LIGHTTYPE] = 2;
		ShowDialog:UPGRADEVEHICLE_LIGHT(playerID);
	}
}