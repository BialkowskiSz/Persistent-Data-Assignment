/* This program will read and save results of matches.
    Author: Szymon Bialkowski
    Date: 11/04/2016    */

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#define NUM_OF_TEAMS 20

struct st_match {
    char team1[20];
    char team2[20];
    int goals1;
    int goals2;  };


struct st_points {
    char team[15];
    int points;  };


int main()
{
    FILE *f;
    register int i=0, j=0, z=0;
    struct st_match match;
    struct st_points team_points={0};
    struct st_points team_array[20]={0};
    char strings[200]=" ";
    int tell=0;

    f = fopen("results.bin", "rw+b");
    if(f==NULL)
    {
        printf("You are missing the results.bin file.\n");
        exit(0);
    }
    else
    {
            for(j=0; j<20; j++)
            {
                fseek(f, tell, SEEK_SET);
                fread(match.team1, sizeof(match.team1), 1, f);
                fread(match.team2, sizeof(match.team2), 1, f);
                fread(&match.goals1, sizeof(int), 1, f);
                fread(&match.goals2, sizeof(int), 1, f);
                tell = ftell(f);
                strcpy(team_points.team, match.team1);
                if(strstr(strings, match.team1) == NULL)
                {
                    team_points.points = 0;
                    fseek(f, 0, SEEK_SET);
                    for(i=0; i<380; i++)
                    {

                        fread(match.team1, sizeof(match.team1), 1, f);
                        fread(match.team2, sizeof(match.team2), 1, f);
                        fread(&match.goals1, sizeof(int), 1, f);
                        fread(&match.goals2, sizeof(int), 1, f);
                        if(strcmp(match.team1, team_points.team) == 0)
                        {
                            if(match.goals1 > match.goals2)
                            {
                                team_points.points = team_points.points + 3;
                            }
                            else if(match.goals1 == match.goals2)
                            {
                                team_points.points = team_points.points + 1;
                            }
                        }
                        else if(strcmp(match.team2, team_points.team) == 0)
                        {
                            if(match.goals1 < match.goals2)
                            {
                                team_points.points = team_points.points + 3;
                            }
                            else if(match.goals1 == match.goals2)
                            {
                                team_points.points = team_points.points + 1;
                            }
                        }
                    }
                        strcpy(team_array[z].team, team_points.team);
                        team_array[z].points = team_points.points;
                        z++;
                        strcat(strings, team_points.team);

                }
                strcpy(team_points.team, match.team2);
                if(strstr(strings, match.team2) == NULL)
                {
                    team_points.points = 0;
                    fseek(f, 0, SEEK_SET);
                    for(i=0; i<380; i++)
                    {
                        fread(match.team1, sizeof(match.team1), 1, f);
                        fread(match.team2, sizeof(match.team2), 1, f);
                        fread(&match.goals1, sizeof(int), 1, f);
                        fread(&match.goals2, sizeof(int), 1, f);
                        if(strcmp(match.team1, team_points.team) == 0)
                        {
                            if(match.goals1 > match.goals2)
                            {
                                team_points.points = team_points.points + 3;
                            }
                            else if(match.goals1 == match.goals2)
                            {
                                team_points.points = team_points.points + 1;
                            }
                        }
                        else if(strcmp(match.team2, team_points.team) == 0)
                        {
                            if(match.goals1 < match.goals2)
                            {
                                team_points.points = team_points.points + 3;
                            }
                            else if(match.goals1 == match.goals2)
                            {
                                team_points.points = team_points.points + 1;
                            }
                        }
                    }
                        strcpy(team_array[z].team, team_points.team);
                        team_array[z].points = team_points.points;
                        z++;
                        strcat(strings, team_points.team);
                }
            }

        }
        for(i=0; i<(NUM_OF_TEAMS-1); i++)
        {

            for(j=0, z=0; j<(NUM_OF_TEAMS-1); j++)
            {
                if(team_array[j].points > team_array[j+1].points)
                {
                    strcpy(team_points.team, team_array[j+1].team);
                    strcpy(team_array[j+1].team, team_array[j].team);
                    strcpy(team_array[j].team, team_points.team);
                    team_points.points = team_array[j+1].points;
                    team_array[j+1].points = team_array[j].points;
                    team_array[j].points = team_points.points;
                    z++;
                }
            }
            if(z==0)
            {
                break;
            }
        }

        printf("\t\t*****LEAGUE TABLE*****\n\nTeams:\t\t\t         \tPoints\n");
        for(i=(NUM_OF_TEAMS-1); i>-1; i--)
        {
            printf("_________________________________________________________\n");
            printf("%d: %s\t\t|\t\t", (20-i),  team_array[i].team);
            printf("%d\t\t|\n", team_array[i].points);
        }
        printf("_________________________________________________________\n");

    fclose(f);
    return(0);



}
