#!/usr/local/bin/perl -w 

####################################################################
# admin.pl v1.0                                                    #
#      Panneau de configuration du site web                        #
#         - affiche toutes les rubriques triees par ordre          #
#           alphabetique                                           #
#         - modification des rubriques (mod.pl)                    #
#         - modification des parametres <BODY>, couleurs,          #
#           image de fond,... (options.cgi)                        #
#                                                                  #
####################################################################

use diagnostics;


####################################################################
# A modifier que les chemins de ces deux variables seulement       #
####################################################################

# URL du script cgi
$optionscgi="http://maths.ml.org/cgi-sys/cgiwrap/quantum/options.cgi";

# repertoire ou se trouvent les fichiers txt
$rep_donnees="/home/websys/data";


$affichecgi="affiche.pl";


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
###################################################################

#nom et numero de version du script
$version ="admin.pl v1.0 - avril 1998";

##################################
# Recupere la liste des rubriques

sub Liste_Rubriques {

	opendir(DONNEES,"$rep_donnees") or die "Impossile d'ouvrir $rep_donnees: $!";
	@rubriques = sort grep(!/^\./,readdir(DONNEES));
	closedir(DONNEES);


foreach $rubrique(@rubriques) {

	open(FICH,"$rep_donnees/$rubrique") or die "Impossible d'ouvrir $rep_donnees: $!";
        while (<FICH>) {
        	if ($_ =~ /^TITRE>(.*)/i) { 
		$titre = $1; 
		$hash{"$titre"}= $rubrique;
		push @rub, $titre; 
		last; 
		}
	}
}
}


&Liste_Rubriques;

#tri par ordre alphabetique sur les rubriques
@tries = sort (@rub);


#######################
# Affiche la page HTML

print "Content-Type: text/html\n\n";

print <<ENTETE;
<HTML>
<HEAD>
   <TITLE>Administration du Site</TITLE>	
   <META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">
   <META NAME="GENERATOR" CONTENT="$version">
</HEAD>
<BODY TEXT="#000000" BGCOLOR="#FFFFFF" LINK="#0000EF" VLINK="#51188E" ALINK="#FF0000">

	<!-- creee dynamiquement par $version ->

ENTETE

print "<H3>Administration du Site:</H3>\n\n";

print "<UL>\n";
foreach $rr(@tries) {
	print "\n<LI>";
	print "<A HREF=\"$affichecgi?affiche=$hash{$rr}\">$rr</A>";
}
print "\n</UL>\n";

print "<P>\n<FORM ACTION=\"$optionscgi\" METHOD=\"POST\">\n";
print "<INPUT TYPE=\"SUBMIT\" VALUE=\"Options G&eacute;n&eacute;rales\">\n";
print "</FORM>\n";
print "</BODY></HTML>\n";


