/*
 * Andre Augusto Giannotti Scota - 27/10/2005
 * (andre.scota@gmail.com)
 *
 * Um simples e escroto dumper para arquivos. Pois foi mais rapido fazer esse programa
 * do que descobrir a sintax do xd/od para fazer a mesma coisa.
 *
 * MIT License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>

void usage(char *exec)
{
	fprintf(stderr, "%s file_to_dump offset\nSaida redirecionada para STDERRO.\n", exec);
	return;
}

int dump(void *data, size_t lenData, char *outDump, size_t lenOutDump)
{
	unsigned int c = 0, maxBuf = 0;
	unsigned char buffer[16] = {0};
	char *dataWalker = NULL;

	dataWalker = (char *)data;

	for(; lenData > (size_t)0;){

		if(lenData > (size_t)16) maxBuf = 16;
		else                     maxBuf = lenData;

		memcpy(buffer, dataWalker, maxBuf);

		for(c = 0; c < maxBuf; c++){
			sprintf(outDump, "%02X ", buffer[c]);
			outDump += 3;
		}

		sprintf(outDump++, "\t");

		for(c = 0; c < maxBuf; c++)
			sprintf(outDump++, "%c", isprint(buffer[c]) ? buffer[c] : '.');

		dataWalker += maxBuf;
		lenData -= maxBuf;

		sprintf(outDump++, "\n");
	}
	return(1);
}

int main(int argc, char *argv[])
{
	int fdIn = 0;
	char lineReaded[255] = {0}, lineDumped[512] = {0};
	unsigned long offset = 0L, offsetStep = 0L;
	ssize_t sizeReaded = 0;

	if(argc != 3){
		usage(argv[0]);
		return(1);
	}

	fdIn = open(argv[1], O_RDONLY);
	if(fdIn == -1){
		fprintf(stderr, "Erro opening: [%s] [%s].\n", argv[1], strerror(errno));
		return(1);
	}

	offsetStep = atol(argv[2]);
	if(offsetStep > 16){
		fprintf(stderr, "Erro: Offset must be igual or less than 16.\n");
		return(1);
	}

	for(offset = 0L; ; offset += offsetStep){
		memset(lineReaded, 0, 255);
		memset(lineDumped, 0, 512);

		sizeReaded = read(fdIn, lineReaded, offsetStep);

		if(sizeReaded == 0)
			break;

		dump(lineReaded, sizeReaded, lineDumped, 512);

		fprintf(stderr, "%09ld: %s", offset, lineDumped);
	}

	return(0);
}
