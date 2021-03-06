ShowDialog:Register_Birthdate(playerID)
{
	CreateDialog(playerID, "Register_Birthdate", DIALOG_STYLE_INPUT, LanguageString(playerID, StringID:253("Enter birthdate")), LanguageString(playerID, StringID:254("Enter your birthdate in the format DD.MM.YYYY.\n\nExample: 05.02.1990")), LanguageString(playerID, StringID:177("Next")), LanguageString(playerID, StringID:171("Back")));
}

DialogResponse:Register_Birthdate(playerID, response, listItem, inputText[])
{
	if (response)
	{
		new day;
		new month;
		new year;
		if (sscanf(inputText, "p<.>ddd", day, month, year))
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:40("Please use the format DD.MM.YYYY!"));
			ShowDialog:Register_Birthdate(playerID);
		}
		else
		{
			if (day > 0 && day <= 31 && month > 0 && month <=12 && year > 1900 && year < 2100)
			{
				SetPVarStr:playerID[BIRTHDATE][STRINGLENGTH_DATETIME]("%d-%02d-%02d", year, month, day);
				ShowDialog:Register_Location(playerID);
			}
			else
			{
				SendClientMessageEx(playerID, COLOR_ERROR, StringID:41("Invalid date!"));
				ShowDialog:Register_Birthdate(playerID);
			}
		}
	}
	else
	{
		ShowDialog:Register_Gender(playerID);
	}
}