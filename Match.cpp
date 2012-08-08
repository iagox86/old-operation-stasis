#include "Match.h"

#include <ctype.h>

int Match(const char *mask, const char *name) 
{ 
	int wild=0, q=0; 
	const char *m=mask, *n=name, *ma=mask, *na=name; 
 
	for(;;) 
	{ 
		if (*m == '*') 
		{ 
		while (*m == '*') ++m; 
			 wild = 1; 
			 ma = m; 
		na = n; 
		} 
 

		if (!*m) 
		{ 
			if (!*n) 
				return 1; 
 
			for (--m; (m > mask) && (*m == '?'); --m) ; 
 
			if ((*m == '*') && (m > mask) && (m[-1] != '\\')) 
				return 1; 
			if (!wild) 
				return 0; 

			m = ma; 
		}
		else if (!*n) 
		{ 
			 while(*m == '*') ++m; 
			 return (*m == 0); 
		} 
		
		if ((*m == '\\') && ((m[1] == '*') || (m[1] == '?'))) 
		{ 
			++m; 
			q = 1; 
		} 
		else 
		{ 
			q = 0; 
		} 


		if ((tolower(*m) != tolower(*n)) && ((*m != '?') || q)) 
		{ 
			 if (!wild) return 0; 
			 m = ma; 
			 n = ++na; 
		} 
		else 
		{ 
			 if (*m) ++m; 
			 if (*n) ++n; 
		} 
	} 
} 


inline char *RemoveSingleChar(char *String, int Location)
{
	for(int i = Location; String[i] != '\0'; i++)
		String[i] = String[i + 1];

	return String;
}

inline char *InsertSingleChar(char *String, int Location, char Char)
{
	int i;

	char Temp = String[Location];
	char OldTemp;
	String[Location] = Char;

	for(i = Location + 1; Temp != '\0'; i++)
	{
		OldTemp = Temp;
		Temp = String[i];
		String[i] = OldTemp;
	}

	String[i] = '\0';

	return String;
}

bool ReplaceAll(const char *Find, const char *ReplaceChar, char *String)
{
	if(Replace(Find, ReplaceChar, String))
	{
		while(Replace(Find, ReplaceChar, String))
		{
		}
		return true;
	}
	
	return false;
}

bool Replace(const char *Find, const char *Replace, char *String)
{
	// Make sure that Outbuf is large enough to hold the new string!
	// This will process ? wildcards, but NOT *!

	// Returns true if a replacement was made, false otherwise

	int i = 0;
	int j = 0;

	// as much as I don't want to do it, I'm going to use a string library function here:
	// (feel free to change it, but I'm sure that this is faster than what mine would be :))
	char FindWild[1024];

	while(Find[i] != '\0')
	{
		if(Find[i] == '*')
			FindWild[i] = '?';	
		else
			FindWild[i] = Find[i];

		i++;
	}

	FindWild[i] = '*';
	FindWild[i + 1] = '\0';
	// Reset our loop variable
	i = 0;
	
	while(String[i] != '\0')
	{
		// While we aren't done String
		if(Match(FindWild, String + i))
		{
			// Great, we have a match!

			// Remove find characters from string
			j = 0;
			while(Find[j] != '\0')
			{
				RemoveSingleChar(String, i);
				j++;
			}

			j = 0;
			while(Replace[j] != '\0')
			{
				// If for some reason you want to insert the string backwards, just remove
				// "+ j" from the next line :D

				InsertSingleChar(String, i + j, Replace[j]);
				j++;
			}
			return true;
		}
	// can't forget to increment!
	i++;
	}

	return false;
}  
