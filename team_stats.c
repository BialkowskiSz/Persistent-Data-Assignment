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

struct st_team {
    int played;
    int win;
    int draw;
    int loss;
    int goals_scored;
    int goals_lost;
                };




int main(int argc, char *argv[])
{
    FILE *f;
    register int i=0, j=0;
    struct st_match match;
    struct st_team team = {0};
    char team_name[15];

    f = fopen("results.bin", "rw+b");
    if(f==NULL)
    {
        printf("You are missing the results.bin file.\n");
    }
    else
    {

        printf("Please enter the name of the team.\n");
        scanf("%15s", team_name);

        for(i=0; i<NUM_OF_TEAMS; i++)
        {
            fread(match.team1, sizeof(match.team1), 1, f);
            fread(match.team2, sizeof(match.team2), 1, f);
            fread(&match.goals1, sizeof(int), 1, f);
            fread(&match.goals2, sizeof(int), 1, f);
            if(strcmp(match.team1, team_name)==0 ||
               strcmp(match.team2, team_name)==0)
            {
                j++;
            }
        }
        if(j<1)
        {
            printf("Your team is not valid. Please try again.\n");
            exit(0);
        }
        else
        {
            fseek(f, 0, SEEK_SET);
            for(i=0; i<380; i++)
            {
                fread(match.team1, sizeof(match.team1), 1, f);
                fread(match.team2, sizeof(match.team2), 1, f);
                fread(&match.goals1, sizeof(int), 1, f);
                fread(&match.goals2, sizeof(int), 1, f);
                if(strcmp(match.team1, team_name) == 0)
                {
                    team.played++;
                    team.goals_scored = team.goals_scored + match.goals1;
                    team.goals_lost = team.goals_lost + match.goals2;
                    if(match.goals1 > match.goals2)
                        team.win++;
                    else if(match.goals1 == match.goals2)
                        team.draw++;
                    else
                        team.loss++;
                }
                else if(strcmp(match.team2, team_name) == 0)
                {
                    team.played++;
                    team.goals_scored = team.goals_scored + match.goals2;
                    team.goals_lost = team.goals_lost + match.goals1;
                    if(match.goals1 < match.goals2)
                        team.win++;
                    else if(match.goals1 == match.goals2)
                    team.draw++;
                    else
                        team.loss++;
                }
            }
            printf("Team : %s.\n", team_name);
            printf("Match Played: %d.\n", team.played);
            printf("Win: %d.\n", team.win);
            printf("Draw: %d\n", team.draw);
            printf("Loss: %d\n", team.loss);
            printf("Scored: %d\n", team.goals_scored);
            printf("Conceided: %d\n", team.goals_lost);
        }

    }

    fclose(f);
    return(0);



}
