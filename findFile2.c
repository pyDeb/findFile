#define _XOPEN_SOURCE 700
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <stdbool.h>

char *filename;

char *getBaseName(char *fullpath)
{
	char *basename = (char *)malloc(256);
	memset(basename, '\0', 256);
	bool status = false;
	for(int i = strlen(fullpath) - 1, j = 256, k = 0; j > 0; i--, j--, k++)
	{
		if(fullpath[i] == '/')
		{
			status = true;
			break;
		}

		basename[k] = fullpath[i];
	}

	if(!status)
		return NULL;

	for(int i = 0, j = strlen(basename) - 1; i < j; i++, j--)
	{
		char temp;
		temp = basename[i];
		basename[i] = basename[j];
		basename[j] = temp;
		
	}

	return basename;
}


int processEntry(const char* fpath, const struct stat* stat, int flags, struct FTW* ftw)
{ 
	if(strlen(fpath) == 1)
		if(fpath[0] == '.')
			return 0;

	
	char *basename;
	if((basename = getBaseName(fpath)) == NULL)
	{
		printf("The length of base file is too large for me to process :(\n");
		return -1;
	}

	if(strcmp(basename, filename) == 0)
		printf("File found at %s\n", fpath);

	return 0;
}

int main(int argc, char *argv[])
{

	if(argc < 2)
	{
		printf("Usage: %s <filename> <target-directory>\ntarget-directory is optional tho.\n", argv[0]);
		return 1;
	}

	filename = (char *)malloc(256);
	memset(filename, '\0', 256);
	snprintf(filename, 256, "%s", argv[1]);

	if (nftw((argc < 3) ? "." : argv[2], processEntry, 25, 0) == -1) 
	{
		printf("Call to nftw failed\n");
		return 1;
	}

	return 0;
}
