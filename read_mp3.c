/* This program will display information of a
    specific MP3 file on screen.
    Author: Szymon Bialkowski
    Date: 08/04/2016    */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

struct st_mp3 {
    char title[30];
    char artist[30];
    char album[30];
    char year[5];
    char comment[30];
    int genre;  };

struct st_genre_file    {
    int genre_num;
    char genre_name[40];
                };


int main(int argc, char *argv[])
{
    FILE *f;
    FILE *f1;
    struct st_mp3 song;
    struct st_genre_file genre;
    register int i;
    char tag[4]="";

    system("cls");
    if(strstr(*(argv+1), ".mp3") == NULL)
    {
      printf("Your file is not an .mp3 file.\n");
      exit(0);
    }

    f = fopen(*(argv+1), "rb");
    if(f==NULL)
    {
        printf("\nCouldn't find or open file. Ensure filename = song_name.mp3\n");
    }
    else
    {
        fseek(f, -128, SEEK_END);
        fread(tag, 3, 1, f);

        if((strcmp(tag, "TAG")) == 0)
        {
            f1 = fopen("Genre.txt", "rw+b");

            fread(song.title, sizeof(song.title), 1, f);
            fread(song.artist, sizeof(song.artist), 1, f);
            fread(song.album, sizeof(song.album), 1, f);
            fread(song.year, sizeof(char), 4, f);
            fread(song.comment, sizeof(song.comment), 1, f);
            fread(&song.genre, sizeof(song.genre), 1, f);
            *(song.year+4) = '\0';

            printf("Title: ");
            if(strlen(song.title) == 0)
                printf("Unknown.\n");
            else
                printf("%s.\n", song.title);

            printf("Artist: ");
            if(strlen(song.artist) == 0)
                printf("Unknown.\n");
            else
                printf("%s.\n", song.artist);

            printf("Album: ");
            if(strlen(song.album) == 0)
                printf("Unknown.\n");
            else
                printf("%s.\n", song.album);

            printf("Release Year: ");
            if(strlen(song.year) == 0)
                printf("Unknown.\n");
            else
                printf("%s.\n", song.year);

            printf("Comment: ");
            if(strlen(song.comment) == 0)
                printf("Unknown.\n");
            else
                printf("%s.\n", song.comment);

            if(f1==NULL)
            {
                printf("You are missing the Genre.txt file. Cannot print Genre.\n");
            }
            else
            {
                for(i=0; i<=125; i++)
                {
                    fscanf(f1, "%d", &genre.genre_num);
                    fgets(genre.genre_name, 40, f1);
                    if(genre.genre_num==song.genre)
                    {
                        printf("Genre: %s\n",  genre.genre_name);
                        break;
                    }
                }
            }
        }
        else
        {
            printf("\nYour file does not contain the correct tag. ");
            printf("Try with another file.\n");
        }
        fclose(f);
        fclose(f1);

    }
    return(0);
}//end of main()
