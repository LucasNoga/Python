#!/usr/local/bin/perl -w

####################################################################
# affiche.pl v0.1                                                  #
#         Affiche la rubrique demandee avec ses articles pour      #
#         modification                                             #
#                                                                  #
# a2gee2 - mars 1998                                               #
####################################################################


####################################################################
# A modifier que les chemins de ces deux variables seulement       #
####################################################################

# URL du script cgi pour la modification des rubriques
$modcgi="http://maths.ml.org/cgi-bin/mod.pl";

# URL du script cgi pour la creation des sous-rubriques
$ajoutcgi="http://maths.ml.org/cgi-bin/ajoutrubrique.pl";

# repertoire ou se trouvent les fichiers txt
$rep_donnees="/usr/home/websys/data";

# repertoire ou se trouvent les fichiers txt
$fichier_options="/usr/home/websys/options";


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
$version="affiche.pl v1.0 - avril 1998";


&Lecture_Options;

print "Content-Type: text/html\n\n";	

if ($ENV{'QUERY_STRING'} =~ /affiche=(.*)/i) {
	$fichier_donnees = $1; 
	&Lecture_Donnees;
	}
else { &Echec_Prog;}



################################################################################
# Lecture du fichier donnees TXT

sub Lecture_Donnees {
open (FICHIER, "$rep_donnees/$fichier_donnees") or die ("Impossible d'ouvrir $fichier_donnees: $!");
@opt=<FICHIER>;
close(FICHIER);
	
	$nbsujets = 1;
	foreach $ligne (@opt) {	

		if ($ligne =~ /^TITRE>(.*)/i) { $titre_html = $1; }	

		elsif ($ligne =~ /^SUJET>(.*)/i) { $sujet[$nbsujets] = $1; }
		elsif ($ligne =~ /^FICHIER_PS>(.*)/i) { $fichier_ps[$nbsujets] = $1; }
		elsif ($ligne =~ /^FICHIER_PDF>(.*)/i) { $fichier_pdf[$nbsujets] = $1; }
		elsif ($ligne =~ /^SYNOPSIS>(.*)/i) { 
			$synopsis[$nbsujets] = $1; 
			$synopsis[$nbsujets] =~ s/&eacute;/é/g;
			$synopsis[$nbsujets] =~ s/&egrave;/è/g;
			$synopsis[$nbsujets] =~ s/&ecirc;/ê/g;
			$synopsis[$nbsujets] =~ s/&euml;/ë/g;
			$synopsis[$nbsujets] =~ s/&auml;/ä/g;
			$synopsis[$nbsujets] =~ s/&ccedil;/ç/g;
			$synopsis[$nbsujets] =~ s/&agrave;/à/g;
			$synopsis[$nbsujets] =~ s/&amp;/&/g;
			$nbsujets++; 
			}


		}	
	$titre_html =~ tr/_/ /;

	&Affiche_Formulaire;

}


######################################################################
# Affiche un formulaire pour la modification de la rubrique avec les
# donnees actuelles par defaut

sub Affiche_Formulaire {

	#local @rubriques;
	#local $rub;
	

	$titre_html =~ s/:/: /g;

#	$titre_html =~ tr/_/ /;

	# Generation du Fichier HTML
	print "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2//EN\">\n";

	print "$HTML_BODY\n<HEAD>\n<TITLE>";
	print "Modification: $titre_html";
	print "</TITLE>\n";
	print "<META NAME=\"GENERATOR\" CONTENT=\"$version\">\n";
	print "</HEAD>\n";
	print  $HTML_BODY,"\n";
	print "\n<!-- creee dynamiquement par $version ->\n";
	print "<H3><U>Modification:</U> $titre_html</H3>\n";	

	$titre_html=~ s/ /_/g;
	$titre_html=~ s/:_/:/g;
	print "<FORM ACTION=\"$ajoutcgi?creer=$titre_html\" METHOD=\"POST\">\n";
	print "<INPUT TYPE=\"SUBMIT\" VALUE=\"Ajouter une sous-rubrique\">\n";
	print "</FORM>\n<HR WIDTH=\"600\">\n<P>\n";

 	print "\t<!----------------- debut des ARTICLES ------------------->\n\n";
	print "<P><FORM ACTION=\"$modcgi?rubrique=$fichier_donnees\" METHOD=\"POST\">\n";
	#for ($i=1;$i<$nbsujets+1;$i++) {
	for ($i=1;$i<$nbsujets;$i++) {
 		print "\t<!-- debut SUJET No. $i -->\n";
		print "<H4>Sujet No. $i </H4>\n";
		print "<INPUT TYPE=\"TEXT\" VALUE=\"$sujet[$i]\" NAME=\"sujet$i\">\n";
		print "<BLOCKQUOTE>\n<SMALL>Versions: ";
		print "PS: <INPUT TYPE=\"TEXT\" VALUE=\"$fichier_ps[$i]\" NAME=\"ps$i\">\n";
		print "PDF: <INPUT TYPE=\"TEXT\" VALUE=\"$fichier_pdf[$i]\" NAME=\"pdf$i\">\n";
		print "</SMALL>\n";
		print "<P>\n";
		print "<textarea wrap name=\"synopsis$i\" rows=10 cols=\"50\">$synopsis[$i]</textarea>\n</BLOCKQUOTE>\n\n";
 		print "\t<!-- fin SUJET No. $i -->\n\n";
		}

	# pour l'adjonction d'une nouvelle article

 	print "\t<!-- debut SUJET No. $i -->\n";
	print "<H4>Sujet No. $i </H4>\n";
	print "<INPUT TYPE=\"TEXT\" NAME=\"sujet$i\">\n";
	print "<BLOCKQUOTE>\n<SMALL>Versions: ";
	print "PS: <INPUT TYPE=\"TEXT\" NAME=\"ps$i\">\n";
	print "PDF: <INPUT TYPE=\"TEXT\" NAME=\"pdf$i\">\n";
	print "</SMALL>\n";
	print "<P>\n";
	print "<textarea wrap name=\"synopsis$i\" rows=10 cols=\"50\"></textarea>\n</BLOCKQUOTE>\n\n";
 	print "\t<!-- fin SUJET No. $i -->\n\n";




	print "<INPUT TYPE=\"HIDDEN\" NAME=\"titre_html\" VALUE=\"$titre_html\">\n";
	print "<INPUT TYPE=\"SUBMIT\" VALUE=\"mise-a-jour\"> - \n";
	print "<INPUT TYPE=\"RESET\" VALUE=\"recommencer\">\n";
	print "</FORM>\n";
	print "\n\t<!-------------------------------------------------------->\n\n";
	print "$COPYRIGHT\n";
	print "</BODY>\n</HTML>\n";

}


##########################################################
# Lecture du fichier option pour recuperer les parametres 
# HTML <BODY>, couleurs, image de fonds, copyright...

sub Lecture_Options {

	local @opt;
	local $bgcolor;
	local $background;
	local $text;
	local $link;
	local $vlink;
	local $alink;
	local $date_copyright;

	open (OPTIONS, "$fichier_options") or die ("Impossible d'ouvrir $fichier_options:  $!"); 
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
	
	$HTML_BODY = "<BODY ";
	$HTML_BODY = $HTML_BODY."BACKGROUND=\"$background\" " if ($background);
	$HTML_BODY = $HTML_BODY."BGCOLOR=\"$bgcolor\" " if ($bgcolor);
	$HTML_BODY = $HTML_BODY."TEXT=\"$text\" " if ($text);
	$HTML_BODY = $HTML_BODY."LINK=\"$link\" " if ($link);
	$HTML_BODY = $HTML_BODY."VLINK=\"$vlink\" " if ($vlink);
	$HTML_BODY = $HTML_BODY."ALINK=\"$alink\" " if ($alink);
	$HTML_BODY = $HTML_BODY." >\n";

	if ($nom_site) {
		$COPYRIGHT = "<CENTER><SMALL>Copyright &copy; $date_copyright. $nom_site.";
		$COPYRIGHT .=" Tous droits r&eacute;serv&eacute;s. E-mail: "; 
		$COPYRIGHT .="<A HREF=\"mailto:$email_auteur\">$nom_auteur</A>";
		$COPYRIGHT .="</SMALL></CENTER>\n";
		}
		else { 
			$nom_site = ""; 
			$COPYRIGHT ="";
			}

}


################################################
# Message d'erreur en cas d'echec du programme

sub Echec_Prog {

	print <<EOF;

<HTML>
<HEAD>
   <TITLE>Modification: Echec Programme</TITLE>	
   <META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">
   <META NAME="GENERATOR" CONTENT="$version">
</HEAD>
<BODY TEXT="#000000" BGCOLOR="#FFFFFF" LINK="#0000EF" VLINK="#51188E" ALINK="#F

<!-- creee dynamiquement par $version ->

<H3>Le programme a &eacute;chou&eacute;. Veuillez recommencer.</H3>
</BODY>
</HTML>


EOF
}

