#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define DEFAULT_PATH_SIZE 255

long get_file_length(FILE **file) {
	fseek((*file), 0, SEEK_END);
	long length = ftell(*file);
	fseek((*file), 0, SEEK_SET);

	return length;
}

int validate_input(int argc, char **argv) {
	
	if(argc < 2) {
		printf("You must enter a file to be read.\n");
		return 0;
	}

	return 1;

}

int is_absolute_path(char *str) {
	
	if(str[0] == '/') {
		return 1;
	}

	return 0;
}

char *format_file_path(char *filename) {
	char *path;

	if(is_absolute_path(filename)) {
	
		path = filename;
	
	} else {

		char *cwd = malloc(DEFAULT_PATH_SIZE * sizeof(char));
		path = calloc(DEFAULT_PATH_SIZE, sizeof(char));
		
		cwd = getcwd(cwd, DEFAULT_PATH_SIZE);
		
		strcat(path, cwd);
		strcat(path, "/\0");
		strcat(path, filename);
	
	}

	return path;
}

void read_content(char *filename) {
	
	char *path = format_file_path(filename);
	
	FILE *file = fopen(path, "r");

	if (file == NULL) {
		printf("ERROR: Could not find file: %s\n", filename);
		return;
	}

	long length = get_file_length(&file);

	char *buffer = malloc(length * sizeof(char));
	if (buffer != NULL) {
		fread(buffer, 1, length, file);
		printf("%s", buffer);
	}

	fclose(file);
	free(path);
}

int main(int argc, char *argv[]) {

	int i;

	if( !validate_input(argc, argv) ) {
		return 0;
	}

	for (i = 1; i < argc; i ++) {
		read_content(argv[i]);	
	}

	return 0;
}
