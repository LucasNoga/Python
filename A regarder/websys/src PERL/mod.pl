#!/usr/local/bin/perl  -w

####################################################################
# mod.pl v1.0                                                      #
#        Modifie la rubrique demandee via un formulaire HTML       #
#                                                                  #
####################################################################

use diagnostics;

####################################################################
# A modifier ici le chemin des repertoires                         #
####################################################################

# repertoire ou se trouvent les fichiers txt
$rep_donnees="/usr/home/websys/data";


# Notice:
#
# Ce script doit etre execute par cgiwrap avec votre user id.
# Si ce n'est pas possible, chmod 707 repertoire
# 
# Le script doit etre dans un repertoire protege par un 
# mot de passe (via .htaccess). Si ces precautions ne sont 
# pas prises, les fichiers peuvent etre modifies par une 
# personne non-autorisee.
#
# De plus, on peut restreindre l'acces aux programmes et 
# repertoires, par un simple script shell qui changera les 
# permissions (chmod 0 *.pl) et les remettra comme executable 
# pour le temps des modifications seulement.
#
# - SL
################################################

#nom et numero de version du script
$version="mod.pl v1.0 - avril 1998";


###########################################
# Lecture des donnees du formulaire  HTML
#
sub Parse_Form {
	$nbsujets=0;	

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



#####################################################
# Recupere les donnees passees par le formulaire web

sub Recup_Donnees 
{
	$nbsujets=10;

	$titre_html = $FORM{'titre_html'};
	for ($i=1;$i<=$nbsujets;$i++) 
	{
		$sujet[$i] = $FORM{"sujet$i"}; 	
		$ps[$i] = $FORM{"ps$i"};
		$pdf[$i] = $FORM{"pdf$i"};
		$synopsis[$i] = $FORM{"synopsis$i"};
	}

}


####################################################
# Cree le nouveau fichier TXT en ecrasant l'ancien

sub Ecriture_Donnees 
{
	open (FICH,">$rep_donnees/$fichier_donnees") or die "Impossible d'ouvrir $fichier_donnees: $!\n";
	print FICH "TITRE>$titre_html\n\n";
	for ($i=1;$i<=$nbsujets;$i++) 
	{
		if ($sujet[$i]) 
		{
			print FICH "SUJET>$sujet[$i]\n";
			print FICH "FICHIER_PS>$ps[$i]\n";
			print FICH "FICHIER_PDF>$pdf[$i]\n";
			print FICH "SYNOPSIS>$synopsis[$i]\n\n";
		}
	}
	close(FICH);

}


print "Content-Type: text/html\n\n";

if ($ENV{'QUERY_STRING'} =~ /rubrique=(.*)/i) {
	$fichier_donnees=$1;
	&Parse_Form;
	&Recup_Donnees;
	&Ecriture_Donnees;
	&Succes_Prog;
	}

	else {
		&Echec_Prog;
		}


################################################
# Message d'erreur en cas d'echec du programme

sub Echec_Prog 
{
	print <<EOF;

<HTML>
<HEAD>
   <TITLE>Modification: Rubrique non-trouv&eacute;</TITLE>	
   <META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">
   <META NAME="GENERATOR" CONTENT="$version">
</HEAD>
<BODY TEXT="#000000" BGCOLOR="#FFFFFF" LINK="#0000EF" VLINK="#51188E" ALINK="#FF0000">

	<!-- creee dynamiquement par $version ->

<H3>Rubrique non-trouv&eacute;</H3>
</BODY>
</HTML>

EOF


}



#####################################################
# Message de succes de creation de la sous-rubrique

sub Succes_Prog 
{


	print <<EOF;

<HTML>
<HEAD>
   <TITLE>Modification: Rubrique modifi&eacute;e</TITLE>	
   <META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">
   <META NAME="GENERATOR" CONTENT="$version">
</HEAD>
<BODY TEXT="#000000" BGCOLOR="#FFFFFF" LINK="#0000EF" VLINK="#51188E" ALINK="#FF0000">

	<!-- creee dynamiquement par $version ->

<H3>Rubrique modifi&eacute;e</H3>
</BODY>
</HTML>


EOF
}
