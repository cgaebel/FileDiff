// FileDiff.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Precondition - All files are the same size.		*/
/* Precondition - The codebase starts at 0x00400000 */
int main(int argc, char** argv)
{
	int i, j;
	int lastDiff = 0;

	/* We can't compare less than two files, now can we? */
	if(argc < 3)
		return -1;

	/* The number of files we're diffing */
	int numFiles = argc - 1;

	/* The files we're diffing */
	FILE**	toDiff		= (FILE**)calloc(numFiles, sizeof(FILE*));
	/* The bytes read from each file */
	int*	bytesRead	= (int*) calloc(numFiles, sizeof(int));
	/* Temporary storage for the current character we're comparing. */
	char*	temp		= (char*)calloc(numFiles, sizeof(char));

	/* Open all the files. */
	for(i = 0; i < numFiles; i++)
		if(fopen_s(&(toDiff[i]), argv[i+1], "rb"))
			return 0;

	for(i = 0; bytesRead[0] = fread_s(&(temp[0]), 1, 1, 1, toDiff[0]); i++)
	{
		/* Read from all the files */
		for(j = 1; j < numFiles; ++j)
			bytesRead[j] = fread_s(&(temp[j]), 1, 1, 1, toDiff[j]);

		/* Are there any differences? */
		bool difference = false;
		for(j = 1; (j < numFiles) && (!difference); ++j)
			if(temp[0] != temp[j])
				difference = true;

		/* Okay, there's a difference... print it. */
		if(difference)
		{
			if(i != (lastDiff + 1))
				printf("Difference found at address 0x00%x\n", i + 0x00400000);

			lastDiff = i;
		}

		/* Clear the buffer */
		memset(temp, 0, numFiles);
	}

	/* Close all the files */
	for(int i = 0; i < NUMBER_OF_FILES; i++)
		fclose(toDiff[i]);

	/* Clean up the heap */
	free(toDiff);
	free(bytesRead);
	free(temp);

	return 0;
}

#ifdef __cplusplus
}
#endif