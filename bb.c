/*
UI for bbfunctions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "record.h"

extern int debugmode;

int addRecord (struct record **,char [],char [],int, char []);
int getField(char[], char);
int printRecord (struct record *, char []);
int modifyRecord (struct record *, char [],char [], char []);
void printAllRecords(struct record *);
int deleteRecord(struct record **, char []);
void cleanup(struct record**);
int readfile(struct record **, char []);
void writefile(struct record *, char []);

/****/

int main(int argc, char* argv[])
{
  struct record *start = NULL;

  char name[25], address[80], telno[15];
  int bDay;
  int choice = 1;

  readfile(&start, "addbook.txt");

  debugmode = 0;
  if (argc > 1 && strcmp(argv[1], "debugmode") == 0)
    {
      debugmode = 1;
      printf("Debug Mode Initialized\n\n");
    }
    else if (argc > 1)
      {
        printf("Usage: addbook [debugmode]\n");
        return 0;
      }

	while (choice < 7 && choice >= 1)
    {
		printf("*****Address Book*****\n");
		printf("1. Add a new record\n");
		printf("2. Modify a record \n");
		printf("3. Print a record \n");
		printf("4. Print all records \n");
		printf("5. Delete an existing record \n");
		printf("6. Clean up \n");
		printf("7. Quit \n");
		printf("Enter choice (1-7):");
		scanf("%i", &choice);

    while (getchar() != '\n');

		switch (choice)
    {
		case 1:
			printf("Name:");
			getField(name, '\n');

      printf("Address:\n");
      printf("***When finished entering address type '!'***\n");
			getField(address, '!');

			printf("Birth Year:");
			scanf("%d", &bDay);

      while (getchar() != '\n');

			printf("Telephone Number:");
			getField(telno, '\n');

			addRecord(&start, name, address, bDay, telno);

			break;

		case 2:
			printf("Name:");
			getField(name, '\n');

			printf("**Address**\n");
      printf("***When finished entering address type '!'***\n");
			getField(address, '!');
      while (getchar() != '\n');

			printf("Telephone Number:");
			getField(telno, '\n');

			modifyRecord(start, name, address, telno);

			break;

		case 3:
			printf("Name:");
			getField(name, '\n');

			printRecord(start, name);

			break;

		case 4:
			printAllRecords(start);

			break;

		case 5:
			printf("Name:");
			getField(name, '\n');

			deleteRecord(&start, name);

			break;

		case 6:
      cleanup(&start);

			break;

		case 7:

			break;

		default:
			printf("**Invalid Input.**\n");
      choice = 1;

			break;
		}
	}
  writefile(start, "addbook.txt");
  return(0);
}
