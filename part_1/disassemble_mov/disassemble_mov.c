#include <stdio.h>
#include <windows.h>


typedef unsigned __int8 u8;
typedef unsigned __int64 u64;

//Opcodes
typedef 0x88 MOV;



int
main(int argc, char** argv)
{
	char* [16] registers = {"al", "cl", "dl", "bl", "ah", "ch", "dh", "bh", "ax", "cx", "dx", "bx", "sp", "bp", "si", "di"}
	FILE* outFile = fopen("output.asm", "w");
	fprintf(outFile, "bits 16\n\n");
	
	FILE* file = fopen(argv[1]);
	if(!file) { fprintf(stderr, "Failed to find file"); }
	else
	{
		fseek(file, 0, SEEK_END);
		u64 fileSize = ftell(file);
		rewind(file);

		u8* fileBuffer = malloc(fileSize);
		if(fileBuffer == 0 || fread(fileBuffer, 1, fileSize, file) != fileSize) fprintf(stderr, "Failed to read input binary.\n");
		else
		{
			int cursor = 0;
			while(cursor != fileSize)
			{
				switch(fileBuffer[cursor])
				{
					case (MOV | 0x0):
						fprintf(outFIle, "mov ");
						cursor++;
						switch(fileBuffer[cursor]>>5)
						{
							case 0x3: fprintf(outFile, "%s, %s\n", registers[8+fileBuffer[cursor]&0x7], registers[8+(fileBuffer[cursor]&0x3F)>>3]); break;
						} break;
					case (MOV | 0x1):
						fprintf(outFile, "mov ");
						cursor++;
						switch(fileBuffer[cursor]>>5)
						{
							case 0x3: fprintf(outFile, "%s, %s\n", registers[fileBuffer[cursor]&0x7], registers[(fileBuffer[cursor]&0x3F)>>3]); break;
						} break;
					case (MOV | 0x2):
						fprintf(outFile, "mov ");
						cursor++;
						switch(fileBuffer[cursor]>>5)
						{
							case 0x3: fprintf(outFile, "%s, %s\n", registers[8+(fileBuffer[cursor]&0x3F)>>3], registers[8+fileBuffer[cursor]&0x7]); break;
						} break;
					case (MOV | 0x3):
						fprintf(outFile, "mov ");
						cursor++;
						switch(fileBuffer[cursor]>>5)
						{
							case 0x3: fprintf(outFile, "%s, %s\n", registers[(fileBuffer[cursor]&0x3F)>>3], registers[fileBuffer[cursor]&0x7]); break;
						} break;


		fclose(outFile);
		fclose(file);

	return 0;
}
