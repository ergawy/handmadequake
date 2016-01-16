#include "quakedef.h"

// he talked about the possibility of overlap between
// dest and src

// in the std lib they assume the caller knows what he 
// is doing
void Q_strcpy(uint8* dest, uint8* src)
{
	while (*src)
	{
		*dest++ = *src++;
		// he claims that pre increment produces
		// simpler assmebly language than post increment
		// , why is that? check the sub reddit
		//++src;
		//++dest;
	}

	*dest = 0;
}

void Q_strncpy(uint8* dest, uint8* src, int32 count)
{
	if (count < 0)
	{
		return;
	}

	while (*src && count)
	{
		*dest++ = *src++;
		--count;
	}

	while (count)
	{
		*dest++ = 0;
		--count;
	}

	*dest = 0;
}

int32 Q_strlen(uint8* str)
{
	int count = 0;

	while (str[count])
	{
		count++;
	}

	return count;
}

int32 Q_strcmp(uint8* s1, uint8* s2)
{
	while (*s1 == *s2)
	{
		if (!*s1)
		{
			return 0;
		}

		++s1;
		++s2;
	}

	return ((*s1 < *s2) ? -1 : 1);
}

int32 Q_atoi(uint8* str)
{
	int32 sign = 1;
	int32 val = 0;
	uint8 c;

	if (*str == '-')
	{
		sign = -1;
		str++;
	}

	if ((str[0] == '0') && ((str[1] == 'x') || (str[1] == 'X')))
	{
		str += 2;

		while (1)
		{
			c = *str;
			str++;
			if ((c >= '0') && (c <= '9'))
			{
				val = val * 16 + c - '0';
			}
			else if ((c >= 'a') && (c <= 'f'))
			{
				val = val * 16 + c - 'a' + 10;
			}
			else if ((c >= 'a') && (c <= 'f'))
			{
				val = val * 16 + c - 'A' + 10;
			}
			else
			{
				return sign * val;
			}
		}
	}

	while (1)
	{
		c = *str;
		str++;

		if (c < '0' || c > '9')
		{
			return sign * val;
		}

		val = val * 10 + c - '0';
	}
}
