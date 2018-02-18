#!/usr/local/bin/perl 

####################################################################
# recherche.cgi v1.0                                               #
#     - Moteur de recherche interne pour le site                   #
#                                                                  #
####################################################################


####################################################################
# A modifier ici les chemins de fichiers et des repertoires        #
####################################################################

# repertoire ou se trouvent les fichiers txt
$fichier_options="/usr/home/websys/options";

# URL du script cgi 
$recherchecgi="recherche.cgi";

$rep_donnees="/usr/home/websys/data";

$home_url="http://maths.ml.org";

#nom et numero de version du script
$version ="recherche.cgi v1.0 - avril 1998";




#######################
# programme principal

sub main_prog {
	&Parse_Form;

	&Lecture_Options;
	&Liste_Rubriques;
	&Recherche_Mots_Cles;
	&Affiche_Resultats;
}





###################################################
# Affiche le formulaire HTML pour la modification

sub Affiche_Resultats {

print "Content-Type: text/html\n\n";

print <<EOF;
<HTML>
<HEAD>
	<!-- creee dynamiquement par $version -->
   <TITLE>$nom_site: Moteur de Recherche</TITLE>
   <META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">
   <META NAME="GENERATOR" CONTENT="$version">
</HEAD>
<BODY TEXT="$text" BGCOLOR="$bgcolor" LINK="$link" VLINK="$vlink" ALINK="$alink" BACKGROUND=\"$background\">
EOF


if (@mots_cles) {

	#compteur de pages trouves
	local $cpt=0;

	print "<P><H3>R&eacute;sultats:</H3>\n";
	print "<UL>\n";
	foreach $key (keys %include) {
		if ($include{$key} eq 'yes') {
			#print "titre: $titre{$key}\n";
			@tete = split (/:/,$titre{$key});
			$tete = pop(@tete);
			$tete =~ s/_/ /g; 
			$url = $titre{$key};
			$url =~ s/:/\//g;

			#print "<LI><A HREF=\"$home_url/$key\">$titre{$key}</A>\n";
			print "<LI><A HREF=\"$home_url/$url/\">$tete</A>\n" if ($titre{$key});
			$cpt++ if ($titre{$key});
		}
	}

	print "</UL>\n";
	print "<CENTER><I>";
	if ($cpt == 0) {
	 print "D&eacute;sol&eacute;! On n'a rien trouv&eacute;. Veuillez reessayer."; 
		}
		elsif ($cpt == 1)  { 
			print "On a trouv&eacute; 1 page";
			}
			else {
				print "On a trouv&eacute; $cpt pages";
				}

	print "</I></CENTER>\n";
}

print "<P><CENTER>\n";
print "<FORM ACTION=\"$recherchecgi\" METHOD=\"POST\">\n";
print "<INPUT TYPE=\"TEXT\" NAME=\"mots_cles\" VALUE=\"";

$i=0;
	foreach $mot(@mots_cles) {
		print $mot;
		$i++;
		if (!($i == @mots_cles)) {
			print " ";
			}
	}

print "\" SIZE=\"30\">\n";
print "<INPUT TYPE=\"SUBMIT\" VALUE=\"Rechercher\">\n";
print "</FORM>\n";
print "</CENTER>\n\n";
print "		<!-- creee dynamiquement par $version --> \n\n";

print "</BODY></HTML>\n";

}

##############################################
# Lecture des donnees du formulaire HTML

sub Parse_Form {
	read(STDIN, $buffer, $ENV{'CONTENT_LENGTH'});
	@pairs = split(/&/, $buffer);
	
	foreach $pair(@pairs) {
		($nom,$valeur) = split(/=/, $pair);
		
		$nom =~ tr/+/ /;
		$nom =~ s/%([a-fA-F0-9][a-fA-F0-9])/pack("C", hex($1))/eg;

		$valeur =~ tr/+/ /;
		$valeur =~ s/%([a-fA-F0-9][a-fA-F0-9])/pack("C", hex($1))/eg;

		$valeur =~ s/<!--([^>]|\n)*-->/ /g;
		$valeur =~ s/&/&amp;/g;
		$valeur =~ s/é/&eacute;/g;
		$valeur =~ s/è/&egrave;/g;
		$valeur =~ s/ê/&ecirc;/g;
		$valeur =~ s/ä/&auml;/g;
		$valeur =~ s/ë/&euml;/g;
		$valeur =~ s/ç/&ccedil;/g;
		$valeur =~ s/à/&agrave;/g;
		$FORM{$nom} = $valeur;


		}

}

##############################################
# Lecture du fichier options

sub Lecture_Options {

	local @opt;

	open (OPTIONS, "$fichier_options") or die "Impossible d'ouvrir $fichier_options: $!";
	@opt=<OPTIONS>;
	close(OPTIONS);

	foreach $ligne (@opt) {	

		if ($ligne =~ /^BGCOLOR>(.*)/i) { $bgcolor = $1; }	
			elsif ($ligne =~ /^BACKGROUND>(.*)/i) { $background = $1; }
			elsif ($ligne =~ /^TEXT>(.*)/i) { $text = $1; }
			elsif ($ligne =~ /^LINK>(.*)/i) { $link = $1; }
			elsif ($ligne =~ /^VLINK>(.*)/i) { $vlink = $1; }
			elsif ($ligne =~ /^ALINK>(.*)/i) { $alink = $1; }
			elsif ($ligne =~ /^EMAIL_AUTEUR>(.*)/i) { $email_auteur = $1; }
			elsif ($ligne =~ /^NOM_AUTEUR>(.*)/i) { $nom_auteur = $1; }
			elsif ($ligne =~ /^NOM_SITE>(.*)/i) { $nom_site = $1; }
			elsif ($ligne =~ /^DATE_COPYRIGHT>(.*)/i) { $date_copyright = $1; }


	}
}	


##################################
# Recupere la liste des rubriques

sub Liste_Rubriques {

	opendir(DONNEES,"$rep_donnees") or die "Impossile d'ouvrir $rep_donnees:
	$!";
	@rubriques = sort grep(!/^\./,readdir(DONNEES));
	closedir(DONNEES);
}


sub Recherche_Mots_Cles {

	@mots_cles = split(/\s+/, $FORM{'mots_cles'});

 foreach $fichier (@rubriques) {

      open(FICH,"$rep_donnees/$fichier");
      @lignes = <FICH>;
      close(FICH);

      $string = join(' ',@lignes);
      	foreach $mot (@mots_cles) {
               if (!($string =~ /$mot/i)) {
                  $include{$fichier} = 'no';
  		  last;
               }
               else {
                  $include{$fichier} = 'yes';
               }
         }
      if ($string =~ /^TITRE>(.+)/i) {
         $titre{$fichier} = "$1";
      }
  }	
}
   





# appel du programme principal
&main_prog;


