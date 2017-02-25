/* This program will scramble a file.
  Author: Szymon Bialkowski
  Date: 24/04/2016  */

  #include <stdio.h>
  #include <strings.h>
  #include <stdlib.h>


  int main(int argc, char *argv[])
  {
      FILE *f;          //2 file pointers
      FILE *f1;
      long size;
      register long i;
      char filename[50];
      char buffer[3]="\0";
      char temp;

      if(strstr(*(argv+1), ".sbl") != NULL)
      {
        printf("Cannot encrypt an already encrypted file.\n");
        exit(0);
      }

      system("cls");
      f = fopen(*(argv+1), "r+b");
      if(f==NULL)
      {
          printf("\nCouldn't find or open file. Ensure filename is correct and exists.\n");
          exit(0);
      }

      else
      {
          strcpy(filename, *(argv+1));
          strcat(filename, ".sbl");    //Adds .sbl to the end
          f1 = fopen(filename, "wb");
          if(f1==NULL)
          {
            printf("Unable to create encrypted file.\n");
          }
          else
          {
              fseek(f, 0, SEEK_END);
              if(ftell(f) %2 == 1)    //Works out if No. of bytes is odd
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
                  *(buffer) = *(buffer+1);    //Swaps the bytes
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
              printf("Your decrypted file has been successfuly encrypted.\n");
          }//end of else

      }//end of else
      return(0);

  }//end of main()
