#!/usr/local/bin/perl -w

####################################################################
# options.cgi                                                      #
#     - modifie les parametres HTML <BODY>, couleurs,              #
#       image de fond, nom du site...                              #
#                                                                  #
####################################################################


####################################################################
# A modifier ici les chemins de fichiers et des repertoires        #
####################################################################

# repertoire ou se trouvent les fichiers txt
$fichier_options="/usr/home/websys/data/options";

# URL du script cgi pour les parametres HTML, couleur
$optionscgi="http://maths.ml.org/cgi-bin/options.cgi";


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
$version ="options.cgi v1.0 - avril 1998";



#######################
# programme principal

sub main_opt {
&Parse_Form;

if ( $ENV{'QUERY_STRING'} =~ /mise_a_jour/i) {
	&Mise_a_jour;
	}
&Lecture_Options;
&Affiche_Formulaire;

}


#########################################################
# Cree le nouveau $fichier_options en ecrasant l'ancien

sub Mise_a_jour {

	open(FICH,">$fichier_options") or die "Impossible d'ouvrir $fichier_options: $!\n";
	print FICH "BACKGROUND>$FORM{'background'}\n" if ($FORM{'background'});
	print FICH "BGCOLOR>$FORM{'bgcolor'}\n" if ($FORM{'bgcolor'});
	print FICH "TEXT>$FORM{'text'}\n" if ($FORM{'text'});
	print FICH "LINK>$FORM{'link'}\n" if ($FORM{'link'});
	print FICH "ALINK>$FORM{'alink'}\n" if ($FORM{'alink'});
	print FICH "VLINK>$FORM{'vlink'}\n" if ($FORM{'vlink'});
	print FICH "NOM_AUTEUR>$FORM{'nom_auteur'}\n" if ($FORM{'nom_auteur'});
	print FICH "NOM_SITE>$FORM{'nom_site'}\n" if ($FORM{'nom_site'});
	print FICH "EMAIL_AUTEUR>$FORM{'email_auteur'}\n" if ($FORM{'email_auteur'});
	print FICH "DATE_COPYRIGHT>$FORM{'date_copyright'}\n" if ($FORM{'date_copyright'});
	close(FICH);
}


###################################################
# Affiche le formulaire HTML pour la modification

sub Affiche_Formulaire {

print "Content-Type: text/html\n\n";

print <<EOF;
<HTML>
<HEAD>
   <TITLE>$nom_site: Options Generales</TITLE>
   <META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">
   <META NAME="GENERATOR" CONTENT="$version">
</HEAD>
<BODY TEXT="$text" BGCOLOR="$bgcolor" LINK="$link" VLINK="$vlink" ALINK="$alink">

<H3>$nom_site : Options G&eacute;n&eacute;rales</H3>

	<!-- creee dynamiquement par $version ->

<BLOCKQUOTE>&nbsp;
<H3>Exemple de Lien: <A HREF="http://www.yahoo.fr">Yahoo! France</A></H3>
<FORM METHOD="POST" ACTION="$optionscgi?mise_a_jour">
<BR>BGCOLOR: <INPUT NAME="bgcolor" TYPE="TEXT" VALUE="$bgcolor">
<BR>BACKGROUND: <INPUT NAME="background" TYPE="TEXT" VALUE="$background">
<BR>TEXT: <INPUT NAME="text" TYPE="TEXT" VALUE="$text">
<BR>LINK: <INPUT NAME="link" TYPE="TEXT" VALUE="$link">
<BR>VLINK: <INPUT NAME="vlink" TYPE="TEXT" VALUE="$vlink">
<BR>ALINK: <INPUT NAME="alink" TYPE="TEXT" VALUE="$alink">

<P>Nom Auteur: <INPUT NAME="nom_auteur" TYPE="TEXT" VALUE="$nom_auteur">
<BR>E-mail Auteur: <INPUT NAME="email_auteur" TYPE="TEXT" VALUE="$email_auteur">
<BR>Nom Site: <INPUT NAME="nom_site" TYPE="TEXT" VALUE="$nom_site">
<BR>Date Copyright: <INPUT NAME="date_copyright" TYPE="TEXT" VALUE="$date_copyright">
<BR>&nbsp;
<BR><INPUT TYPE="SUBMIT" VALUE="mise-a-jour">


</BLOCKQUOTE>


</FORM>
<CENTER>Copyright &copy; $date_copyright. $nom_site. Tous droits r&eacute;serv&eacute;s.
E-mail: <A HREF="mailto:$email_auteur">$nom_auteur</A></CENTER>

</BODY>
</HTML>
EOF

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
		$valeur =~ s/é/&eacute;/g;
		$valeur =~ s/è/&egrave;/g;
		$valeur =~ s/ê/&ecirc;/g;
		$valeur =~ s/ä/&auml;/g;
		$valeur =~ s/ë/&euml;/g;
		$valeur =~ s/ç/&ccedil;/g;
		$valeur =~ s/à/&agrave;/g;
		$valeur =~ s/&/&amp;/g;
		$FORM{$nom} = $valeur;


		}

}

##############################################
# Lecture du fichier options

sub Lecture_Options {

	local @opt;

	open (OPTIONS, "$fichier_options"); ## ||  &Erreur_Fichier($fichier_options);
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

# appel du programme principal
&main_opt;


