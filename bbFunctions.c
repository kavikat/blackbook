/*
    author@Kavika Tavui
    this file contains all functions for bb.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "record.h"

int debugmode;

/*
    populates struct with user data  
*/

int addRecord (struct record ** start, char name[],char address[],int yob, char num[])
{
  struct record *temp = NULL;
  struct record *temp2 = NULL;


  	if (debugmode == 1)
      {
		      printf("\nint addRecord(struct record ** person,char name[ ],char address[ ],int bDay, char telno[ ])\n\n");
	    }

  temp = (struct record*) malloc(sizeof(struct record));

  temp->next = NULL;
  strcpy(temp->name, name);
  strcpy(temp->address, address);
  temp->yearofbirth = yob;
  strcpy(temp->telno, num);

  if(*start == NULL)
    {
      *start = temp;
    }

  else
    {
      temp2 = *start;

        while(temp2->next != NULL)
        {
            temp2 = temp2->next;
        }
      temp2->next = temp;
    }

    printf("***New contact added***\n\n");

	return 1;
}

/*
    allows for multi line entry
 */

int getField(char buff[], char terminate)
{
  int i = 0;
  char ch = getchar();
  while (ch != terminate)
  {
    buff[i] = ch;
    i++;
    ch = getchar();
  }
  while (i > 0 && isspace(buff[i-1]))
  {
    i--;
  }
  buff[i] = 0;

  return 0;
}

/*
 tokenizes new lines
 */

int getFileField(FILE* fp, char buff[], char terminate)
{
  int i = 0;
  char ch = (char)fgetc(fp);
  while (ch != terminate && ch != EOF)
  {
    buff[i] = ch;
    i++;
    ch = (char)fgetc(fp);
  }
  while (i > 0 && isspace(buff[i-1]))
  {
    i--;
  }
  buff[i] = 0;

  return 0;
}

/*
  alter ecord
 */

int modifyRecord(struct record * start, char name[], char address[], char telno[])
{
     struct record *listPointer = start;
  if (debugmode == 1)
  {
    printf(
        "\nmodifyRecord(struct record * next,char name[ ],char address[ ], char telno[ ])\n\n");
  }

   while (listPointer != NULL)
     {
       if (strcmp(name, listPointer->name)== 0)
       {
          strcpy(listPointer->address, address);
          strcpy(listPointer->telno, telno);
       }
       listPointer = listPointer->next;
     }
  return 0;
}

/*
    displays results
 */

int printRecord(struct record * start, char name[])
  {
     struct record *listPointer = start;
  if (debugmode == 1)
  {
    printf("\nprintRecord(struct record * start, char name[])\n\n");
  }

  while (listPointer != NULL)
  {
      if (strcmp(name, listPointer->name)== 0)
      {
      printf("Name: %s\n", listPointer->name);
      printf("Address: %s\n", listPointer->address);
      printf("Birth Year: %d\n", listPointer->yearofbirth);
      printf("Telephone Number: %s\n", listPointer->telno);
      }
        listPointer = listPointer->next;
  }

  return 0;
}

/*
    displays all records
 */

void printAllRecords(struct record * start)
  {
     struct record *listPointer = NULL;

  if (debugmode == 1)
  {
    printf("\nprintAllRecords(struct record * start)\n\n");
  }

      if (start == NULL) {
          printf("No Records found\n");
      }
      else
      {
          listPointer = start;

         while(listPointer != NULL)
         {
            printf("Name: %s\n", listPointer->name);
            printf("Address: %s\n", listPointer->address);
            printf("Birth Year: %d\n", listPointer->yearofbirth);
            printf("Telephone Number: %s\n", listPointer->telno);
            printf("\n");

            listPointer = listPointer->next;
         }
      }
      printf("\n");
}

/*
deletes record
 */

int deleteRecord(struct record ** start, char name[])
{

    struct record *listPointer = *start;
    struct record *previous = NULL;
    struct record *temp;
  if (debugmode == 1)
  {
    printf("\ndeleteRecord(struct record ** start, char name[])\n\n");
  }

  while (listPointer != NULL)
  {
    if (strcmp(name, listPointer->name)== 0)
    {
        temp = listPointer;
        listPointer = listPointer->next;

        if (previous != NULL)
           previous->next = temp->next;
        else
           *start = temp->next;

        free(temp);
    }
    else
    {
       previous = listPointer;
       listPointer = listPointer->next;
    }
  }

  return 0;
}
/*
clears all linked list references
 */
void cleanup(struct record** start)
{
  struct record* listPointer = *start;
  while (listPointer != NULL)
  {
    *start = listPointer->next;
    free(listPointer);
    listPointer = *start;
  }
}

/*
  reads from file
 */

int readfile(struct record ** start, char filename[])
{
    char name[25], address[80], telno[15];
    int bDay = 0;
    FILE *addbook;
    char temp;

    addbook =fopen("addbook.txt", "r");

  if (debugmode == 1)
  {
    printf("\nint readfile(struct record ** start, char filename[])\n\n");
  }
    if (!addbook)
    {
        printf("ERROR! No file present\n");
        return 0;
    }

    while (!feof(addbook))
    {
       getFileField(addbook, name, '\n');
       getFileField(addbook, address, '!');
       if (fscanf(addbook, "%i", &bDay) != 1)
          break;
       temp = fgetc(addbook);
       while (temp != '\n' && temp != EOF) temp = fgetc(addbook);
       getFileField(addbook, telno, '\n');


       addRecord (start,name,address,bDay,telno);

    }
    fclose(addbook);
    printf("\nRead from file...\n");

  return 0;
}

/*
writes to file
 */

int writefile(struct record * start, char filename[])
{
    struct record *listPointer = NULL;
    FILE *addbook;
    addbook =fopen("addbook.txt", "w");

    if (!addbook)
    {
        printf("ERROR! Failed to write file\n");
        return 0;
    }

  if (debugmode == 1)
  {
    printf("\nint writefile(struct record ** start, char filename[])\n\n");
  }
    listPointer = start;

    while(listPointer != NULL)
    {

        fprintf(addbook, "%s\n", listPointer->name);
        fprintf(addbook, "%s!\n", listPointer->address);
        fprintf(addbook, "%i\n", listPointer->yearofbirth);
        fprintf(addbook, "%s\n", listPointer->telno);
        listPointer = listPointer->next;
    }
    printf("Successfully wrote to file");
    fclose(addbook);

  return 0;
}
