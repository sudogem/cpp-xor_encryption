/* TURBO C CSC11 Project  */
/* Coded by Arman Ortega  */
#include <stdio.h>
#include <dos.h>
#include <io.h>
#include <sys\stat.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCKSIZE 3
#ifndef true
   #define true 1
#endif
#ifndef false
  #define false 0
#endif


void encrypt(void);
void decrypt(void);
void menu(void);
int fileexists(char *filename);

int key; /* ENCRYPTION KEY */
char mkey[20];

int fileexists(char *filename) {
   return (!access(filename,0));
}

void menu(void) {
 char choice[2];
 int c;


 do{
   clrscr();
   printf("A Simple Encryption Program using XOR \n");
   printf("[1] - Encrypt \n");
   printf("[2] - Decrypt \n");
   printf("[3] - Exit \n");
   printf("Enter your choice here:");
   choice[0] = 2;
   strcpy(choice,cgets(choice));
   c = atoi(choice);
     switch(c){
	case 1: encrypt(); break;
	case 2: decrypt(); break;
	case 3: printf("\n\nSorry, my response is limited. Program terminated...");
		      getch(); break;
     }
  }while(c!=1 && c!=2 && c!=3);
}

void encrypt(void) {
   FILE *in , *out;
   char inputfile[20];
   char outputfile[20];
   char ch;
   char *ch2;
   char c,s[10];
   int i,handle;
   int iscreate = false; /* ASSUMING THE FILE HAS NOT BEN CREATED YET  :D */

   clrscr();
   printf("Enter the file to be encrypt:");
   gets(inputfile);

   printf("\nLoading file ...Please wait...");delay(2000);
   if ((in = fopen(inputfile,"r")) == NULL ) {
      printf("Cannot open file.");
      getch();
      exit(0);
   }

   /* ****************   LOAD THE PLAIN TEXT MESSAGE ***************** */
   printf("\n\nMessage: \n\n");

   while(!feof(in)){
       ch = getc(in);
       printf("%c",ch);
   }
   printf("\nEnter the key:");
   gets(mkey);
   key = atoi(mkey);
   printf("\nPress any key to start the encryption...");getch();

   /* *************** ENCRYPT THE MESSAGE by xoring it *************** */
   printf("\nEncryption process begin...\n\n");
   rewind(in);
   ch = getc(in);
   while(!feof(in)){
     ch = getc(in);
     for(i = 0;i <BLOCKSIZE; i++) {

     }
     printf("%c",ch^key);
   }
   printf("\n\nEncryption done successfully!!!\n");

   printf("Enter the output file for the encrypted message:");
   gets(outputfile);

   /* CHECK IF THE FILE iS ALREADY EXIST */
   if (fileexists(outputfile)) {
      printf("File %s already exist.\n" , outputfile);
      printf("Would you like to replace the existing file[y/n]?");
      c = toupper(getche());
	if (c == 'Y') {
	   handle = creat(outputfile,S_IREAD | S_IWRITE);
	   iscreate = true;
	}
   }
   else {
      if (!fileexists(outputfile)) {
	  handle = creat(outputfile,S_IREAD | S_IWRITE);
	  iscreate = true;
      }
   }
   /* CHECK THE FILE HANDLE   */
   if (handle == -1) {
	printf("creating file error.");
	getch();
	exit(0);
   }

   if (iscreate) {
      if ((out = fopen(outputfile,"w")) == NULL ) {
	 printf("Cannot open file.");
	 getch();
	 exit(0);
      }
      rewind(in);
      while((ch = fgetc(in)) != EOF ){
	 ch = ch ^ key;
	 fputc(ch,out);
      }
   }
   printf("\nKage bunshin no jutso!!!");
   fclose(out);
   fclose(in);
   getch();
}

void decrypt(void) {
FILE *in, *out;
char ch;
char inputfile[20];
char outputfile[20];
char c;
int handle;
int iscreate = false;

      clrscr();
      printf("Enter the encrypted file :");
      gets(inputfile);
      /* ****************   LOAD THE ENCRYPTED MESSAGE ***************** */
      if ((in = fopen(inputfile,"r")) == NULL ) {
	 printf("Cannot open file.");
	 getch();
	 exit(0);
      }
     /* *****************   LOAD THE ENCRYPTED TEXT MESSAGE ***************** */
     printf("\n\nMessage: \n\n");
     while((ch = fgetc(in)) != EOF ){
	fputc(ch,stdout);
     }

      printf("\nEnter the key:");
      gets(mkey);
      key = atoi(mkey);

      printf("\nPress any key to start the decryption...");getch();

      printf("Decryption process begin :\n\n");
      rewind(in);
      while((ch = fgetc(in)) != EOF ){
	 ch = ch ^ key;
	 fputc(ch,stdout);
      }

      printf("\n\nDecryption done successfully!!!\n");

      printf("Enter the output file for the decrypted message:");
      gets(outputfile);

      /* CHECK IF THE FILE iS ALREADY EXIST */
      if (fileexists(outputfile)) {
      printf("File %s already exist.\n" , outputfile);
      printf("Would you like to replace the existing file[y/n]?");
      c = toupper(getche());
	if (c == 'Y') {
	   handle = creat(outputfile, S_IWRITE);
	   iscreate = true;
	}
      }
      else {
	 if (!fileexists(outputfile)) {
	     handle = creat(outputfile, S_IWRITE);
	     iscreate = true;
	 }
      }
      /* CHECK THE FILE HANDLE   */
      if (handle == -1) {
	printf("file error.");
	getch();
	exit(0);
      }

      if (iscreate) {
	   if ((out = fopen(outputfile,"w")) == NULL ) {
	       printf("Cannot open file.");
	       getch();
	       exit(0);
	   }
	   rewind(in);
	   while((ch = fgetc(in)) != EOF ){
	       ch = ch ^ key;
	       fputc(ch,out);
	   }
      }

      printf("\nKage bunshin no jutso!!!");
      fclose(in);
      fclose(out);
      getch();
}

void main(void) {
 menu();
}

