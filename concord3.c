#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "emalloc.h"
#include "seng265-list.h"

const int MAX_KEYWORD_LEN = 40;
const int MAX_LINE_LEN    = 100;

/* prints all text of node_t in linked-list */
void printList(node_t *head) {
	while (head != NULL) {
		printf("%s\n", head->text);
		head = head->next;
	}
}

/* prints all keys and lines of node_k in linked-list */
void printListK(node_k *head) {
	while (head != NULL) {
		printf("key: %s\n", head->keyword);
		printf("line: %s\n", head->line);
		head = head->next;
	}
}

/* prints all chars of node_c in linked-list */
void printListC(node_c *head) {
	while (head != NULL) {
		printf("%c", head->ch);
		head = head->next;
	}
	printf("\n");
}

/* frees all nodes in node_t linked-list */
void freeList(node_t *head) {
	node_t *temp = NULL;
	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	} 
}

/* frees all nodes in node_k linked-list */
void freeListK(node_k *head) {
	node_k *temp = NULL;
	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}
}

/* returns all uppercase version of word */
char* make_upper(char *word) {
	int len = strlen(word);
	char *upper = (char*)emalloc(MAX_KEYWORD_LEN * sizeof(char));
	strncpy(upper, word, MAX_KEYWORD_LEN);
	for (int i = 0; i < len; i++) {
		upper[i] = toupper(word[i]);
	}
	return upper;
}

/* returns all lowercase version of word */
char *make_lower(char *word) {
	int len = strlen(word);
	char *lower = (char*)emalloc(MAX_KEYWORD_LEN * sizeof(char));
	strncpy(lower, word, MAX_KEYWORD_LEN);
	for (int i = 0; i < len; i++) {
		lower[i] = tolower(word[i]);
	}
	return lower;
}

/* creates and returns linked-list of node_t storing all exclusion words from input file */
node_t* loadExclusionWords(node_t *exclusion_words) {
	char *cur_line = (char*)emalloc(MAX_KEYWORD_LEN * sizeof(char));
	node_t *temp_node = NULL;
	while (fgets(cur_line, sizeof(char) * MAX_KEYWORD_LEN, stdin)) {
		int line_len = strlen(cur_line);
		if (cur_line[line_len-1] == '\n') {
			cur_line[line_len-1] = 0;
		}
		if (strcmp(cur_line, "1") == 0) {
			printf("Input is version 1, concord3 expected version 2\n");
			exit(0);
			continue;
		} else if (strcmp(cur_line, "2") == 0) {
			continue;
		} else if (strcmp(cur_line, "\'\'\'\'") == 0) {
			continue;
		} else if (strcmp(cur_line, "\"\"\"\"") == 0) {
			break;
		}
		temp_node = new_node(make_lower(cur_line));
		exclusion_words = add_inorder(exclusion_words, temp_node);
	}
	free(cur_line);
	if (exclusion_words == NULL) {
		return 0;
	} else {
		return exclusion_words;
	}
}

/* creates and returns linked-list of node_t storing all index lines from input file */
node_t* loadIndexLines(node_t *index_lines) {
	char *cur_line = (char*)emalloc(MAX_LINE_LEN * sizeof(char));
	node_t *temp_node = NULL;
	while (fgets(cur_line, MAX_LINE_LEN+1, stdin)) {
		int line_len = strlen(cur_line);
		if (cur_line[line_len-1] == '\n') {
			cur_line[line_len-1] = 0;
		}
		temp_node = new_node(cur_line);
		index_lines = add_end(index_lines, temp_node);
	}
	free(cur_line);
	if (index_lines == NULL) {
		return 0;
	} else {
		return index_lines;
	}
}

/* creates and returns linked-list of node_t storing all words
in input lines not found in exclusion_words from input file */
node_t* nonExclusionWords(node_t *exclusion_words, node_t *index_lines, node_t *non_exclusion_words) {
	char *line = (char*)emalloc(MAX_LINE_LEN * sizeof(char));
	char *index_word = (char*)emalloc(MAX_KEYWORD_LEN * sizeof(char));
	char *excl_word = (char*)emalloc(MAX_KEYWORD_LEN * sizeof(char));
	node_t *curr_excl = NULL;
	node_t *curr_lines = NULL;
	curr_lines = index_lines;
	int appears;
	while(curr_lines != NULL) {
		strncpy(line, curr_lines->text, MAX_LINE_LEN);
		char *word = strtok(line, " ");
		while (word != NULL) {
			strncpy(index_word, word, MAX_KEYWORD_LEN);
			curr_excl = exclusion_words;
			appears = 0;
			while (curr_excl != NULL) {
				if (strcmp(make_lower(index_word), curr_excl->text) == 0) {
					appears = 1;
				}
				curr_excl = curr_excl->next;
			}
			if (appears == 0) {
				if (contains(non_exclusion_words, make_lower(index_word)) == 0) {
					non_exclusion_words = add_inorder(non_exclusion_words, new_node(index_word));
				}
			}
			word = strtok(NULL, " ");
		}
		curr_lines = curr_lines->next;
	}
	free(line);
	free(excl_word);
	return non_exclusion_words;
}

/* creates and returns linked-list of node_k storing all index lines with
assosiated key */
node_k *makeKeyAndLine(node_t *non_exclusion_words, node_t *index_lines, node_k *keywords) {
	char *line = (char*)emalloc(MAX_LINE_LEN * sizeof(char));
	char *linecpy = (char*)emalloc(MAX_LINE_LEN * sizeof(char));
	char *word = (char*)emalloc(MAX_KEYWORD_LEN * sizeof(char));
	node_t *non_exl = NULL;
	node_t *curr_lines = NULL;
	non_exl = non_exclusion_words;
	while (non_exl != NULL) {
		strncpy(word, non_exl->text, MAX_KEYWORD_LEN);
		curr_lines = index_lines;
		while (curr_lines != NULL) {
			strncpy(line, curr_lines->text, MAX_LINE_LEN);
			strncpy(linecpy, curr_lines->text, MAX_LINE_LEN);
			char *tok_word = strtok(linecpy, " ");
			while (tok_word != NULL) {
				if (strcmp(word, tok_word) == 0) {
					keywords = add_inorder_k_2(keywords, new_node_k(word, line));
				}
				tok_word = strtok(NULL, " ");
			}
			curr_lines = curr_lines->next;
		}
		non_exl = non_exl->next;
	}
	free(line);
	free(word);
	return keywords;
}

/* capitalizes keyword in node_k and returns it */
node_k* highlightKeyword(node_k *upper_keyword, node_k *keywords) {
	char *key = (char*)emalloc(MAX_KEYWORD_LEN * sizeof(char));
	strncpy(key, keywords->keyword, MAX_KEYWORD_LEN);
	key = make_upper(key);
	node_k *temp = NULL;
	temp = new_node_k(key, keywords->line);
	upper_keyword = add_inorder_k(upper_keyword, temp);
	free(key);
	return upper_keyword;
}

/* capitalizes and returns all keywords in lines/keys */
node_k* highlightAllKeywords(node_k *upper_keyword_in_line, node_k *upper_keyword_in_lines_and_key) {
	while (upper_keyword_in_line != NULL) {
		upper_keyword_in_lines_and_key = highlightKeyword(upper_keyword_in_lines_and_key, upper_keyword_in_line);
		upper_keyword_in_line = upper_keyword_in_line->next;
	}
	return upper_keyword_in_lines_and_key;
}

node_k* highlightKeywordsInLines(node_k *keywords, node_k *upper_keyword_in_line) {
	char *space = " ";
	while (keywords != NULL) {
		char *upper_keyword_line = (char*)emalloc(MAX_LINE_LEN * sizeof(char));
		char *word = strtok(keywords->line, " ");
		while (word != NULL) {
			if (strncmp(make_lower(word), make_lower(keywords->keyword), MAX_KEYWORD_LEN) == 0) {
				strncat(upper_keyword_line, make_upper(word), MAX_KEYWORD_LEN);
			} else {
				strncat(upper_keyword_line, word, MAX_KEYWORD_LEN);
			}
			strncat(upper_keyword_line, space, MAX_LINE_LEN);
			word = strtok(NULL, " ");
		}
		int line_len = strlen(upper_keyword_line);
		if (upper_keyword_line[line_len-1] == ' ') {
			upper_keyword_line[line_len-1] = 0;
		}
		node_k *temp = NULL;
		temp = new_node_k(keywords->keyword, upper_keyword_line);
		upper_keyword_in_line = add_inorder_k(upper_keyword_in_line, temp);
		keywords = keywords->next;
	}
	return upper_keyword_in_line;
}

node_c* makeLineChars(node_k *upper_keyword_in_lines_and_key) {
	char *temp_line = (char*)emalloc(MAX_LINE_LEN * sizeof(char));
	strncpy(temp_line, upper_keyword_in_lines_and_key->line, MAX_LINE_LEN);
	node_c *line_chars = NULL;
	int i = 0;
	while(temp_line[i] != '\0') {
		node_c *temp = NULL;
		temp = new_node_c(temp_line[i]);
		line_chars = add_end_c(line_chars, temp);
		i++;
	}
	free(temp_line);
	return line_chars;
}

void printOutput(node_k *upper_keyword_in_lines_and_key, node_c *line_chars) {
	char *key = (char*)emalloc(MAX_KEYWORD_LEN * sizeof(char));
	char *line = (char*)emalloc(MAX_LINE_LEN * sizeof(char));
	char *buffer = (char*)emalloc(MAX_LINE_LEN * sizeof(char));
	strncpy(key, upper_keyword_in_lines_and_key->keyword, MAX_KEYWORD_LEN);
	strncpy(line, upper_keyword_in_lines_and_key->line, MAX_LINE_LEN);

	char *result = strstr(line, key);
	int index = result - line;

	int val = 29 - index;
	if (val > 0) {
		for (int q = 0; q < val; q++) {
			strcat(buffer, " ");
		}
	} else {
		int num = abs(val);
		line += num;
	}
	strcat(buffer, line);
	
	// if length before keyword is > 20: then find first space after 8th column
	if (index > 19) {
		int pos = 0;
		int first_space;
		for (pos = 8; pos < 29; pos++) {
			if (buffer[pos] == ' ') {
				first_space = pos;
				break;
			}
		}
		for (int b = 0; b <= first_space; b++) {
			buffer[b] = ' ';
		}
	}
	
	// if length after and including keyword > 30: then find last space before 61 columnm
	int temp_len = strlen(buffer);
	if (temp_len > 60) {
		int idx = 0;
		int last_space;
		for (idx = 60; idx > 30; idx--) {
			if (buffer[idx] == ' ') {
				last_space = idx;
				break;
			}
		}
		buffer[last_space] = '\0';
	}
	printf("%s\n", buffer);
}

void makeListLineChars(node_k *upper_keyword_in_lines_and_key, node_c *line_chars) {
	while (upper_keyword_in_lines_and_key != NULL) {
		line_chars = makeLineChars(upper_keyword_in_lines_and_key);
		printOutput(upper_keyword_in_lines_and_key, line_chars);
		upper_keyword_in_lines_and_key = upper_keyword_in_lines_and_key->next;
	}
}

int main() {
	node_t *exclusion_words = NULL;
	exclusion_words = loadExclusionWords(exclusion_words);

	node_t *index_lines = NULL;
	index_lines = loadIndexLines(index_lines);

	node_t *non_exclusion_words = NULL;
	non_exclusion_words = nonExclusionWords(exclusion_words, index_lines, non_exclusion_words);

	node_k *keywords = NULL;
	keywords = makeKeyAndLine(non_exclusion_words, index_lines, keywords);

	node_k *upper_keyword_in_line = NULL;
	upper_keyword_in_line = highlightKeywordsInLines(keywords, upper_keyword_in_line);

	node_k *upper_keyword_in_lines_and_key = NULL;
	upper_keyword_in_lines_and_key = highlightAllKeywords(upper_keyword_in_line, upper_keyword_in_lines_and_key);

	node_c *line_chars = NULL;
	makeListLineChars(upper_keyword_in_lines_and_key, line_chars);


	freeList(exclusion_words);
	freeList(index_lines);
	freeList(non_exclusion_words);
	freeListK(keywords);
	freeListK(upper_keyword_in_line);
	freeListK(upper_keyword_in_lines_and_key);

	return (0);
}
