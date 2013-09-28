/*
 * =====================================================================================
 *
 *       Filename:  rapiscan.c
 *
 *    Description:  OSI Screen
 *
 *        Version:  1.0
 *        Created:  09/27/2013 06:25:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Suykerbuyk
 *   Organization:  
 *
 * =====================================================================================
 */
#define _WITH_GETLINE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/* 
 * Implement the following function in C++ .
 * “bool F(string s, char ch1, char ch2, int n)”
 * The function determines whether or not there exists an occurrence of ch1 and ch2 
 * separated by a distance of no more than n in the given string s, where s is ascii 
 * and user entered (your function needs to work on any input.) The function must be 
 * efficient and **optimized** for both space and time. Please state what the 
 * complexity of your solution is.
 *
 * Examples:
 * “abcdefg”, ‘b’, ‘d’, 2 --> true
 * “abcdefg”, ‘b’, ‘d’, 20 --> true
 * “abcdefg”, ‘b’, ‘e’, 1 --> false
 */
int test_function ( const char* s, const char ch1, const char ch2, const int n)
{
	int x = 0;
	const char* s2 = NULL;
	while (*s != 0)
	{
		while (*s++ == ch1)
		{
			s2 = s;
			x  = 0;
			while ( (*s2 != 0) && (x++ < n))
			{
				if (*s2++ == ch2)
				{
					return (1);
				}
			}
		}
	}
	return(0);
}

char get_chk_char(const char* msg)
{
	char  buff[1024]; /*  must be big enough to flush input stream */
	char* input;

	fprintf(stdout, msg);
	input = fgets(buff, sizeof(buff)/sizeof(buff[0]), stdin);
	if ((NULL == input) || (*input == '\n'))
	{
		fprintf(stderr, "No input received. Exiting.\n");
		exit(1);
	}
	return (*input);
}

int get_chk_len(const char* msg)
{
	int chk_len;
	fprintf(stdout, msg);
	if (0 >= fscanf(stdin, "%d", &chk_len))
	{
		fprintf(stderr, "No appropriate input given, exiting.\n");
		exit (1);
	}
	return (chk_len);
}

const char* get_chk_str(const char* msg, char** input_buffer)
{
	size_t len = 0;
	char*  last_char=NULL;

	if (*input_buffer != NULL)
	{
		fprintf(stderr, \
			"Programming error! %s:%d\n",__FILE__, __LINE__);
		fprintf(stderr, \
			" Input buffer should be NULL to avoid memory leaks.\n");
		exit(255);
	}

	fprintf(stdout, "Enter the reference string to scan: ");
	if (0 >= getline(input_buffer, &len, stdin) 
			|| (*input_buffer[0] == '\n'))
	{
		fprintf(stderr, "No appropriate input given, exiting.\n");
		exit (1);
	}

	last_char = *input_buffer + strlen(*input_buffer) -1;
	if (*last_char == '\n')
	{
		*last_char = 0;
	}

	return (*input_buffer);
}
int main (int argc, const char** argv)
{
	const char* chk_string = NULL;
	char ch1, ch2 = 0;
	int  n;
	char* inbuffer = NULL;
	const char* result_txt = NULL;

	if (argc > 1)
	{
		chk_string = argv[1];
	}
	else
	{
		chk_string = \
		   get_chk_str("Enter the reference string to scan: ",\
			        &inbuffer);
	}

	if (argc > 2)
		ch1 = *argv[2];
	else 
		ch1 = get_chk_char("Enter the first character to scan for: ");

	if (argc > 3)
		ch2 = *argv[3];
	else 
		ch2 = get_chk_char("Enter the second character to scan for: ");

	if ((argc < 5) || (0 >= (n = atoi(argv[4]))))
	{
		n = get_chk_len("Enter the max span length to scan: ");
	}

	result_txt = test_function(chk_string, ch1, ch2, n) ? "true" : "false";
	fprintf(stdout, " \"%s\", '%c', '%c', %d  --> %s\n", chk_string, ch1, ch2, n, result_txt); 

	if (inbuffer != NULL)
		free (inbuffer);
}
