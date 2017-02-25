/* This program will unscramble a file.
  Author: Szymon Bialkowski
  Date: 25/04/2016  */

  #include <stdio.h>
  #include <strings.h>
  #include <stdlib.h>
  #define SIZE_OF_EXTRA_TAG 4


  int main(int argc, char *argv[])
  {
      FILE *f;
      FILE *f1;
      long size;
      register long i;
      char filename[50];
      char buffer[3]="\0";
      int lenght=0;
      char temp;

      system("cls");
      if(strstr(*(argv+1), ".sbl") == NULL)
      {
        printf("Cannot decrypt an normal file.\n");
        exit(0);
      }

      f = fopen(*(argv+1), "r+b");
      if(f==NULL)
      {
          printf("\nCouldn't find or open file. Ensure filename is correct and exists.\n");
      }
      else
      {
          strcpy(filename, *(argv+1));
          lenght = (strlen(filename)) - SIZE_OF_EXTRA_TAG;
          *(filename+lenght) = '\0';
          f1 = fopen(filename, "wb");
          if(f1==NULL)
          {
            printf("Unable to create decrypted file.\n");
          }
          else
          {
              fseek(f, 0, SEEK_END);
              if(ftell(f) %2 == 1)
              {
                size = ((ftell(f)-1) /2);
              }
              else
              {
                size = (ftell(f) / 2);
              }
              rewind(f);
              rewind(f1);
              for(i=0; i<size; i++)
              {
                  fread(buffer, 1, 2, f);
                  temp = *(buffer);
                  *(buffer) = *(buffer+1);
                  *(buffer+1) = temp;
                  fwrite(buffer, 1, 2, f1);
              }

              fseek(f, 0, SEEK_END);
              if(ftell(f1) < ftell(f))
              {
                  fseek(f, -1, SEEK_END);
                  fread(&temp, 1, 1, f);
                  fwrite(&temp, 1 ,1, f1);
              }
              printf("Your encrypted file has been successfully decrypted.\n");
          }//end of else


      }//end of else
      return(0);

  }//end of main()
