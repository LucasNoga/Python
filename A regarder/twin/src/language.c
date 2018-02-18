/*- Module s'occupant du languages, cela permt une evolution tres rapide, et donc de gagner en flaxibilite... -*/

#include "language.h"

char *wordsfr[PHRASEMAX] =
{
  "Bienvenue a TwinTRIS",
  "Choisissez votre nom",
  "Jouer!",
  "Quitter",
  "Acceleration",
  "Equipes",
  "Score",
  "Lignes",
  "Bien joue",
  "Oups!",
  "Vous avez gagne!",
  "Vous avez perdu ",
  "Le vainqueur est ",
  " a ete elimine.",
  "De la part de ",
  "Appuyer sur ESPACE",
  "Nouveau Record!",
  "Le meilleur:"
};

char *wordsgb[PHRASEMAX] =
{
  "Welcome to TwinTRIS",
  "Choose your name",
  "Play! ",
  "Quit :(",
  "Increase speed",
  "Team",
  "Score",
  "Lines",
  "Well done",
  "Oups",
  "You win!",
  "You lose ",
  "The winner is ",
  " has been killed.",
  "From ",
  "Press SPACE",
  "It's a new record!",
  "The BEST:"
};

char *
say (int phrase)
{
  if (LANG == FR)
    return (wordsfr[phrase]);
  else
    return (wordsgb[phrase]);
}
