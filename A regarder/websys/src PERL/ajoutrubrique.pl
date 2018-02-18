#!/usr/local/bin/perl  

####################################################################
# ajoutrubrique.pl v0.1                                            #
#         Adjonction d'un sous-rubrique                            #
#               - creation su sous-repertoire                      #
#               - creation du fichier txt pour stocker les donnees #
#                                                                  #
####################################################################


####################################################################
# A modifier ici les chemins des fichiers et des repertoires       #
####################################################################

# URL du script cgi pour la modification des rubriques
$modcgi="http://maths.ml.org/cgi-bin/mod.pl";

# URL du script cgi pour la creation des sous-rubriques
$ajoutcgi="http://maths.ml.org/cgi-bin/ajoutrubrique.pl";

# repertoire ou se trouvent les fichiers txt
$rep_donnees="/usr/home/websys/data";

# fichier qui contient un chiffre incremente a chaque nouvelle rubrique
$fich_data="/usr/home/websys/cpt.txt";

# repertoire pour le web
$home_dir="/usr/home/websys/public_html";


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
$version="ajoutrubrique.pl v1.0 - avril 1998";



###########################################
# Lecture des donnees du formulaire  web

sub Parse_Form 
{
	
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



&Parse_Form;


print "Content-Type: text/html\n\n";

if ($ENV{'QUERY_STRING'} =~ /creer=(.*)/i) {
	$pere=$1;
	&Affiche_Formulaire;
	}
	elsif ($ENV{'QUERY_STRING'} =~ /ajout=(.*)/i) {
		$pere=$1;
		&Creer_Rubrique;
		}
		else {
			&Erreur_Prog;
			}




################################################
# Message d'erreur en cas d'echec du programme

sub Erreur_Prog 
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


##########################################################
# Affiche le formulaire pour la nouvelle rubrique a creer

sub Affiche_Formulaire 
{

	$titre_html=$pere;
	$titre_html=~ s/:/: /g;
	$titre_html=~ s/_/ /g;
	
	print <<EOF;

<HTML>
<HEAD>
   <TITLE>Nouvelle Rubrique: $titre_html </TITLE>	
   <META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">
   <META NAME="GENERATOR" CONTENT="$version">
</HEAD>
<BODY TEXT="#000000" BGCOLOR="#FFFFFF" LINK="#0000EF" VLINK="#51188E" ALINK="#FF0000">

	<!-- creee dynamiquement par $version ->
	
<FORM ACTION="$ajoutcgi?ajout=$pere" METHOD="POST">
<H3>Ajouter une nouvelle rubrique</H3>
<H4>$titre_html: <INPUT TYPE="TEXT"  NAME="nouvellerubrique"></H4>

	<!----------------- debut des SUJETS ------------------->

	<!-- debut SUJET No. 1 -->
<H4>Sujet No. 1 </H4>
<INPUT TYPE="TEXT"  NAME="sujet1">
<BLOCKQUOTE>
<SMALL>Versions: PS: <INPUT TYPE="TEXT" NAME="ps1">
PDF: <INPUT TYPE="TEXT" NAME="pdf1">
</SMALL>
<P>
<textarea wrap name="synopsis1" rows=10 cols="50"></textarea>
</BLOCKQUOTE>

	<!-- fin SUJET No. 1 -->

	<!-- debut SUJET No. 2 -->
<H4>Sujet No. 2 </H4>
<INPUT TYPE="TEXT" NAME="sujet2">
<BLOCKQUOTE>
<SMALL>Versions: PS: <INPUT TYPE="TEXT" NAME="ps2">
PDF: <INPUT TYPE="TEXT" NAME="pdf2">
</SMALL>
<P>
<textarea wrap name="synopsis2" rows=10 cols="50"></textarea>
</BLOCKQUOTE>

	<!-- fin SUJET No. 2 -->

	<!-- debut SUJET No. 3 -->
<H4>Sujet No. 3 </H4>
<INPUT TYPE="TEXT" NAME="sujet3">
<BLOCKQUOTE>
<SMALL>Versions: PS: <INPUT TYPE="TEXT" NAME="ps3">
PDF: <INPUT TYPE="TEXT" NAME="pdf3">
</SMALL>
<P>
<textarea wrap name="synopsis3" rows=10 cols="50"></textarea>
</BLOCKQUOTE>

	<!-- fin SUJET No. 3 -->

	<!-- debut SUJET No. 4 -->
<H4>Sujet No. 4 </H4>
<INPUT TYPE="TEXT" NAME="sujet4">
<BLOCKQUOTE>
<SMALL>Versions: PS: <INPUT TYPE="TEXT" NAME="ps4">
PDF: <INPUT TYPE="TEXT" NAME="pdf4">
</SMALL>
<P>
<textarea wrap name="synopsis4" rows=10 cols="50"></textarea>
</BLOCKQUOTE>

	<!-- fin SUJET No. 4 -->

	<!-- debut SUJET No. 5 -->
<H4>Sujet No. 5 </H4>
<INPUT TYPE="TEXT" NAME="sujet4">
<BLOCKQUOTE>
<SMALL>Versions: PS: <INPUT TYPE="TEXT" NAME="ps4">
PDF: <INPUT TYPE="TEXT" NAME="pdf4">
</SMALL>
<P>
<textarea wrap name="synopsis5" rows=10 cols="50"></textarea>
</BLOCKQUOTE>

	<!-- fin SUJET No. 4 -->

<INPUT TYPE="SUBMIT" VALUE="Creer La Nouvelle Rubrique"> 
<INPUT TYPE="RESET" VALUE="recommencer">
</FORM>

	<!-------------------------------------------------------->

</BODY>
</HTML>

EOF

}


#####################################################
# Recupere les donnees passees par le formulaire web

sub Recup_Donnees 
{
	$nbsujets=10;
	$nouvellerubrique= $FORM{'nouvellerubrique'};
	$nouvellerubrique=~ s/ê/e/g;
	$nouvellerubrique=~ s/ë/e/g;
	$nouvellerubrique=~ s/é/e/g;
	$nouvellerubrique=~ s/è/e/g;
	$nouvellerubrique=~ s/ç/c/g;
	$nouvellerubrique=~ s/ù/u/g;
	$nouvellerubrique=~ s/à/a/g;
	$nouvellerubrique=~ s/ /_/g;
	
	$titre_html = "$pere:$nouvellerubrique";
	for ($i=1;$i<=$nbsujets;$i++) { 

		$sujet[$i] = $FORM{"sujet$i"}; 	
		$ps[$i] = $FORM{"ps$i"};
		$pdf[$i] = $FORM{"pdf$i"};
		$synopsis[$i] = $FORM{"synopsis$i"};
	}

}

##################################################
# Cree le fichier TXT

sub Ecriture_Donnees 
{
	open (FICH,">$rep_donnees/$unfichier") or die "Impossible d'ouvrir $fichier_donnees: $!\n";
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

############################
# Cree la nouvelle rubrique

sub Creer_Rubrique 
{

	&Recup_Donnees;
	&Nom_Fichier;
	&Creer_Repertoire;
	&Ecriture_Donnees;
	&Affiche_HTML;

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



#########################################################
# recupere un numero  pour nommer le nouveau fichier TXT

sub Nom_Fichier 
{

	local $data;

	open (FICH,$fich_data) or die "Impossible d'ouvrir $data: $!\n";
	$data=<FICH>;
	close<FICH>;

	# incrementer le compteur
	$data++;

	open (FICH,">$fich_data") or die "Impossible d'ouvrir $data: $!\n";
	print FICH "$data\n";
	close<FICH>;

	$unfichier= "rub$data";



}


######################################################
# Creation du repertoire par appel du system (mkdir)
#
sub Creer_Repertoire 
{

	@pwd = split (/:/,$titre_html);
	local $dir = $home_dir;


	foreach $rep(@pwd) {
		$dir .="/$rep";
			if (! -e $dir) {
				@args =("mkdir", "$dir");	
				system(@args) == 0 or die "Echec system @args: $!\n";
			}

	}


}
