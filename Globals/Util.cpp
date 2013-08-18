#include "Util.h"

std::vector<std::string> Split(std::string Input, char Delimiter)
{
	std::vector<std::string> Results;

	std::string Temp;
	for(unsigned int x=0; x<Input.size(); x++)
	{
		if(Input[x]==Delimiter)
		{
			if(Temp.size()>0)
			{
				Results.push_back(Temp);
				Temp.clear();
			}
		}
		else
		{
			Temp+=Input[x];
		}
	}
	if(Temp.size()>0)
	{
		Results.push_back(Temp);
		Temp.clear();
	}

	return Results;
}