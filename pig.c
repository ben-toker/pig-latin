#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

//gets input from stdin by dynamically doubling string when the limit (cur_size) is hit.
char* input() {

int cur_char;
int cur_size = 10;
int cur_cap = 0;

char* line = malloc(cur_size * sizeof(char));

while((cur_char = getchar()) != '\n' && cur_char!=EOF) {
	
	line[cur_cap] = cur_char;

	if(++cur_cap == cur_size) {
		line = realloc(line, (cur_size *= 2) * sizeof(char));
	}

}

line = realloc(line, (cur_cap + 1) * sizeof(char));
line[cur_cap] = '\0';

return line;

}

//capitalizes given word by lowering the case of all chars and raising the case of the first character.
char* capitalize(char* word) {

        for(int i=0; i<(int)strlen(word); i++) {
		if(isupper(word[i]) && isalpha(word[i])) {
                	word[i] = tolower(word[i]);
		}
        }
        word[0] = toupper(word[0]);
return word;
}

//extra credit : Pog Latin. Returns word with a pog at the end.
char* poglatin(char* word) {
	word = realloc(word, (strlen(word) + 4) * sizeof(char));
	strcat(word,"pog");
	return word;

}

//function that computes any and all pig-latin transformations.
char* piglatin(char* word) {


	char vowels[] = {'a','e','i','o','u'};

	bool vowel = false;

	//check for first letter vowel
	for(int a=0; a<(int)(strlen(vowels)); a++) {
		if(tolower(word[0]) == vowels[a]) {
			vowel = true;
		}
	}

	//transformation
	if(vowel) {
		word = realloc(word, (strlen(word) + 4) * sizeof(char));
		strcat(word, "yay");
		return word;
	}
	else {
	int change_index = 0;
	int a =0;
	while(!vowel && a<(int)strlen(word)) {
		for(int b=0; b<(int)(strlen(vowels)); b++) {
			if(tolower(word[a]) == vowels[b] || (a!=0 && (tolower(word[a]) == 'y'))) {
				vowel = true;
				change_index = a;
			}
		}
		a++;
	}

	//move everything before vowel to after it and add "ay"
	char* new_string = calloc((strlen(word) + 3), sizeof(char));

	char end_string[change_index + 1];
	end_string[0] = '\0';

	strncpy(new_string,&word[change_index], (strlen(word) - change_index));
	strncpy(end_string,word,change_index);
	
	end_string[change_index] = '\0';

	strcat(new_string,end_string);

	strcat(new_string,"ay");

	free(word);
	return new_string;


	}


}


int main(int argc,char* argv[]) {

bool pog = false;

//command line input

char* known_args[3] = {"-h","-?","-pog"};

if(argc > 1) {
	bool unknown_val_found = false;
	for(int i=0; i<3; i++) {
		if((strstr(argv[1], known_args[i])) != 0) {
		unknown_val_found = true;
	}
}
	if(strcmp(argv[1],"-pog") == 0) {
		pog = true;
	}

	else if(strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"-?") == 0 || unknown_val_found) {
	printf("%s %s%s\n","You inputted",argv[1],". Run ./pig and press enter. After, please enter a string of any length. A pig-latin translation of that string will print out. If you instead want pog-latin instead of piglatin, simply run ./pig -pog to get a fun translation. Enjoy!");
	
exit(1);

}
	
}




//input cluster ; getting line from stdin
char* line = input();
int cur_char = 0;
while(cur_char <(int)strlen(line) - 1) {
	//prints any leading whitespace.
	while(!isalpha(line[cur_char])) {
		printf("%c", line[cur_char++]);
	}

	//gets next word
	int cur_word_length = 0;
	char* cur_word = malloc(101 * sizeof(char));
	cur_word[0] = '\0';
	while(isalpha(line[cur_char])) {
		strncat(cur_word,&line[cur_char],1);
		cur_word_length++;
		cur_char++;
	}
	cur_word[cur_word_length] = '\0';

	//cur_word received
	bool exists_upper = false;
	if(isupper(cur_word[0])){
		exists_upper = true;
	}

	//pog or pig
	if(pog) {
		cur_word = poglatin(cur_word);
	}
	else {
		cur_word = piglatin(cur_word);
	}
	if(exists_upper) {
		cur_word = capitalize(cur_word);
	}

	printf("%s", cur_word);
	free(cur_word);

}
if(!isalpha(line[strlen(line)-1])) {
	printf("%c",line[strlen(line)-1]);
}
printf("\n");




free(line);
return 0;

}
