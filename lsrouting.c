/**
 *
 */

#include "lsrouting.h"

int main(int argc, char *argv[])
{
  FILE *f;
  char *filename;

  if( argc == 2 )
  {
    filename = argv[1];
    if((f = fopen(filename, "r")) == NULL)
	{
		fprintf(stdout, "File does not exist on local machine\n");
		fflush(stdout);
		return -1;
	}

	// Determine size of file
	fseek(f, 0, SEEK_END);
	int file_size = ftell(f);
	rewind(f);

	// Read file into buffer
	char* file_buf = malloc(file_size);
	fread(file_buf, sizeof(char), file_size, f);
	fclose(f);

	struct Graph* graph = createGraph(26);			// Lazy, make a graph for a full alphabet

	char *tok;
	while((tok = strtok(file_buf, ";")) != NULL)
	{
		char N1;
		char N2;
		int weight;
		sscanf(tok, "{%c,%c,%d}", &N1, &N2, &weight);
		addEdge(graph, GET_ALPHANUM(N1), GET_ALPHANUM(N2), weight);
	}

	free(file_buf);

	dijkstra(graph, 0);
    return 0;
    
  }
  else
  {
  	printf("Error: incorrect number of args\n");
  	exit(-1);
  }
}
