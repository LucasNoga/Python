/* Module de gestion des chaines de caracteres */

#include "my_string.h"

char *
concat_chaine (char *debut, char *fin)
{
  char *retour;
  int l1, l2, l;

  l1 = strlen (debut);

  l2 = strlen (fin);

  l = l1 + l2;

  retour = (char *) calloc (sizeof (char), l + 1);

  strcpy (retour, debut);

  strcpy (retour + l1, fin);

  retour[l] = 0;

  return retour;

}

int 
test_it (int argv, char **argc)
{
  char *moi;

  if (argv != 3)
    return 1;

  moi = concat_chaine (argc[1], argc[2]);

  printf ("%s\n", moi);

  free (moi);

  return 0;
}
