#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cros_gentools.h"
#include "cros_message.h"
#include "cros_service.h"
#include "md5.h"

char* cRosGentoolsMD5(char* filename)
{
	char* filename_tokenized = (char*)malloc(strlen(filename)+1);
	strcpy(filename_tokenized, filename);
	strtok(filename_tokenized, ".");
	char* file_ext = strtok(NULL,".");

	if(strcmp(file_ext,FILEEXT_MSG) == 0)
	{
	  cRosMessage msg;
	  cRosMessageInit(&msg);
	  cRosMessageBuild(&msg,filename);
	  char *md5sum = calloc(strlen(msg.md5sum)+1,sizeof(char));
	  strcpy(md5sum,msg.md5sum);
	  cRosMessageRelease(&msg);
	  return md5sum;
	}

	if(strcmp(file_ext,FILEEXT_SRV) == 0)
	{
      cRosService srv;
      cRosServiceInit(&srv);
      cRosServiceBuild(&srv,filename);
      char *md5sum = calloc(strlen(srv.md5sum)+1,sizeof(char));
      strcpy(md5sum,srv.md5sum);
      cRosServiceRelease(&srv);
      return md5sum;
	}

	free(filename_tokenized);
	return NULL;
}

int cRosGentoolsSHA1(char* filename)
{
	//FILE * fp = fopen(filename, "r");
	//fclose(fp);
	return 0;
}

int cRosGentoolsFulltext(char* filename)
{
	char* full_text = NULL;;

	char* filename_tokenized = (char*)malloc(strlen(filename)+1);
	strcpy(filename_tokenized, filename);
	strtok(filename_tokenized, ".");
	char* file_ext = strtok(NULL,".");

	if(strcmp(file_ext,FILEEXT_MSG) == 0)
	{
		msgDep messageDependencies;
		cRosMessageDef msg;
		initCrosMsg(&msg);
		initCrosDep(&messageDependencies);
		getFileDependenciesMsg(filename, &msg, &messageDependencies);
		full_text = computeFullTextMsg(&msg, &messageDependencies);
	}

	if(strcmp(file_ext,FILEEXT_SRV) == 0)
	{
		msgDep messageDependencies;
		cRosSrvDef srv;
		initCrosSrv(&srv);
		initCrosDep(&messageDependencies);
		getFileDependenciesSrv(filename, &srv, &messageDependencies);
		full_text = computeFullTextSrv(&srv, &messageDependencies);
	}

	printf("%s",full_text);

	free(filename_tokenized);
	//free(full_text);
  return 1;
}
