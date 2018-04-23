/*****************************************************************************/
/* MIDI Sysex creator for changing the cable name of USB-MIDI converter      */
/*                                                                           */
/* Copyright (C) 2016 Laszlo Arvai                                           */
/* All rights reserved.                                                      */
/*                                                                           */
/* This software may be modified and distributed under the terms             */
/* of the GNU General Public License.  See the LICENSE file for details.     */
/*****************************************************************************/

/*****************************************************************************/
/* Includes                                                                  */
/*****************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/*****************************************************************************/
/* Constants                                                                 */
/*****************************************************************************/
#define HEADER_SIZE 4
#define MAX_CABLE_NAME_LENGTH 16

uint8_t l_sysex_header[HEADER_SIZE] = {0xf0, 0x7d, 0x1a, 0x55 };
uint8_t l_sysex_end = 0xf7;

/*****************************************************************************/
/* Functions                                                                 */
/*****************************************************************************/
int main(int argc, char* argv[])
{
	FILE* file;
	int pos;

	// check command line arguments
	if (argc != 3)
	{
		printf("USAGE: SysexGen filename.syx \"Cable Name\"\n");
		exit(-1);
	}

	// check cable name length
	if (strlen(argv[2]) > MAX_CABLE_NAME_LENGTH)
	{
		printf("ERROR: Cable name is too long.\n");
		exit(-1);
	}


	// create file
	file = fopen(argv[1], "wb");

	// write file header
	fwrite(l_sysex_header, sizeof(uint8_t), HEADER_SIZE, file);

	// write cable name
	pos = 0;
	while (argv[2][pos] != '\0')
	{
		fwrite(&argv[2][pos], sizeof(uint8_t), 1, file);

		pos++;
	}

	// write end of the sysex message
	fwrite(&l_sysex_end, sizeof(uint8_t), 1, file);

	// close file
	fclose(file);

	printf("Finished creating Sysex file.\n");

  return 0;
}

