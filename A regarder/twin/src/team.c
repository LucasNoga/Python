#include "team.h"

#define TEAMZ 10 /*- Il y a 10 teams en tout, pas faire gafe sinon ca pose un probleme -*/

int Nb_Team_Courant;
int Gars_Par_Team[TEAMZ];

int nb_team()
{
  int i;
  int retour=0;
  int alors[TEAMZ];

  for (i=0;i<TEAMZ;i++) alors[i]=PASENCORE;

  for(i=0;i<MAXIMUM;i++)
    if (alors[team[i]]==PASENCORE) {
      retour++;
      alors[team[i]]=DEJAPASSE;
    }

  return retour;

}

void init_nb_team()
{

  Nb_Team_Courant=nb_team();

}

void init_nb_gpt()
{
  int i;
  /*- Init a -1 s'il y a personne dans le team -*/
  for (i=0;i<TEAMZ;i++) Gars_Par_Team[i]=-1;

  /*- Sinon, on se demerde pour mettre le nombre de personne qu'il faut -*/
  for (i=0;i<MAXIMUM;i++) {
    if (Gars_Par_Team[team[i]]==(-1)) Gars_Par_Team[team[i]]=1;
    else                              Gars_Par_Team[team[i]]++;
  }
}

void init_team(void)
{

  init_nb_gpt();
  init_nb_team();

}

int nb_gars(int mon_team)
{
  int i;
  int retour=0;

  for(i=0;i<MAXIMUM;i++)
    if (team[i]==mon_team) retour++;

  return retour;
}


int nb_gars_restant(int mon_team)
{
  return Gars_Par_Team[mon_team];
}

int nb_team_restants()
{

  int i;
  int retour=0;
  int alors[TEAMZ];

  for (i=0;i<TEAMZ;i++) alors[i]=PASENCORE;

  for(i=0;i<MAXIMUM;i++)
    if ((etat[i]==ENCORE_EN_COURSE)&&
	(alors[team[i]]==PASENCORE)) {
      retour++;
      alors[team[i]]=DEJAPASSE;
    }

  return retour;

}

void eliminer(int joueur)
{
  Gars_Par_Team[team[joueur]]--;

#ifdef DEBUG
  printf("team %d, reste %d gars\n",team[joueur],Gars_Par_Team[team[joueur]]);
#endif

  if (Gars_Par_Team[team[joueur]]==0) Nb_Team_Courant--;
}

int winner_team()
{
  return (Nb_Team_Courant==1);
}
