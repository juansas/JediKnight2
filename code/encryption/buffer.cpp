/*
This file is part of Jedi Knight 2.

    Jedi Knight 2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    Jedi Knight 2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Jedi Knight 2.  If not, see <http://www.gnu.org/licenses/>.
*/
// Copyright 2001-2013 Raven Software

#include "encryption.h"

#ifdef _ENCRYPTION_

#pragma warning (disable : 4514)	//unref inline removed
#pragma warning (disable : 4711)	//func selected for auto inline

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"

const int	BufferIncrease = 1024;

cBuffer::cBuffer(int InitIncrease)
:Buffer(NULL),
 Size(0),
 Pos(0),
 ActualSize(0),
 FreeNextAdd(false)
{
	Increase = InitIncrease;
}

char *cBuffer::Add(char *Data, int Amount)
{
	if (FreeNextAdd)
	{
		Free();
		FreeNextAdd = false;
	}

	if (Pos + Amount >= ActualSize)
	{
		ActualSize += Amount;

		ActualSize -= ActualSize % Increase;
		ActualSize += Increase;

		Buffer = (char *)realloc(Buffer, ActualSize);
	}

	if (Data)
	{
		memcpy(Buffer+Pos, Data, Amount);
	}

	Pos += Amount;
	Size += Amount;

	return Buffer + Pos - Amount;
}

void cBuffer::Read(void)
{
	ResetPos();
}

char *cBuffer::Read(int Amount)
{
	Pos += Amount;

	if (Pos < Size)
	{
		return Buffer + Pos - Amount;
	}

	return NULL;
}

size_t cBuffer::strcspn(const char *notin)
{
        const char *s1, *s2;

        for (s1 = Buffer+Pos; *s1; s1++) 
		{
                for(s2 = notin; *s2 != *s1 && *s2; s2++)
				{
				}
                if (*s2)
				{
                        break;
				}
        }
        return s1 - Buffer + Pos;
}

void cBuffer::Free(void)
{
	if (Buffer)
	{
		free(Buffer);
		Buffer = NULL;
		Size= 0;
		Pos = 0;
		ActualSize = 0;
	}
}
#endif
