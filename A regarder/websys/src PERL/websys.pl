#!/usr/bin/perl 

####################################################################
# websys.pl v1.0                                                   #
#                                                                  #
# Publication Scientifique sur Internet                            #
#     - programme en Perl qui genere entierement le catalogue      #
#       du site avec differentes hierarchies comme dans Yahoo!     #
#                                                                  #
####################################################################



####################################################################
# A modifier ici les chemins des fichiers et des repertoires       #
####################################################################

# nom du fichier pour les pages HTML
$page_html="index.html";

# repertoire ou se trouvent les fichiers txt
$rep_donnees="/home/websys/data";

# repertoire ou se trouvent les fichiers txt
$fichier_options="/home/websys/options"; 

# repertoire du site web
$home_dir="/home/websys/public_html";

# URL du site
$home_url="http://maths.ml.org";


# repertoire pour les fichiers PostScript
$ps_url="http://www.info.iut-tlse3.fr/~aproje10/fichiers/ps";

# repertoire pour les fichiers PDF
$pdf_url="http://www.info.iut-tlse3.fr/~aproje10/fichiers/pdf";




# Notice:
#
# Ce script est execute par la ligne de commande
# $ ./websys.pl
# Il est cependant possible de l'executer via un formulaire HTML mais
# ceci n'est pas preferable pour des raisons de securite
#
# - SL
###################################################################


#nom et numero de version du script
$version="websys.pl v1.0 - avril 1998";


$VERBOSE = 0;
$maxcat = 0;



###################################################################
# Lecture du fichier des options (couleur de fond, nom auteur...)
&Lecture_Options;

# Creation des Index des pages HTML
&Creation_Generale_INDEX;

# Generation des pages HTML a partir de fichiers texte qui seront 
# placees dans differents repertoires selon leur hierarchie 
&Creation_Generale_HTML;
###################################################################


###############################################################
# Message en cas d'Erreur de lecture ou d'ecriture du Fichier

sub Erreur_Fichier {
	
	print "Erreur Fichier: $_[0]\n\n";
	print "Impossible d'ouvrir \"$_[0]\" !!!\n";
	print "Soit le fichier ou le repertoire n'existe pas,";
	print "soit les permissions (chmod) sont mal configurees.\n";
	exit;
}


##################################
# Lecture du fichier donnees TXT

sub Lecture_Donnees {
	$fichier_donnees = $_[0];

	open (FICHIER, "$fichier_donnees") or die ("Impossible d'ouvrir $fichier_donnees: $!");
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
			$synopsis[$nbsujets] =~ tr/\n\n/<P>/;
			$nbsujets++; 
			}


	}	
	@t_titre = split (/:/,$titre_html);
	$maxcat = @t_titre if ($maxcat < @t_titre);
	$titre_html =~ tr/_/ /;

 	local 	$double =0;

	foreach $i(@theme) {
		$double = 1 if ($t_titre[0] eq $i);
		}

	print "\$t_titre : $t_titre[0]\n" if ($VERBOSE == 1);
	push @theme, $t_titre[0] if ($double != 1);

}



##############################################
# Lecture des fichiers options (HTML BODY...)

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
		$COPYRIGHT = $COPYRIGHT." Tous droits r&eacute;serv&eacute;s. E-mail: "; 
		$COPYRIGHT = $COPYRIGHT."<A HREF=\"mailto:$email_auteur\">$nom_auteur</A>";
		$COPYRIGHT = $COPYRIGHT."</SMALL></CENTER>\n";
		}
		else { 
			$nom_site = ""; 
			$COPYRIGHT ="";
			}

}


############################################
# Creation du repertoire si il n'existe pas

sub Creation_Repertoire {
	local @pwd =@_;
	local @args;
	local $rep;
 	print "\@pwd @pwd\n";	
	$dir = $home_dir;
	foreach $rep(@pwd) {
		$dir = "$dir/$rep";
		print "\$dir $dir \n";
	 	if (! -e $dir) {
			@args = ("mkdir","$dir");
			system (@args) == 0 or die "Echec system @args : $!\n";
			print "Creation_Repertoire: mkdir $dir \n";
	 	}
	}

}

############################################################################
# Creation du fichier HTML a partir des fichiers de donnees de $rep_donnees

sub Creation_Fichier_HTML {

	local @rubriques;
	local $rub;
	print "titre $titre_html \n";
	$dir = $titre_html;
	$dir =~ s/ /_/g;
	$dir =~ s/:/\//g;
 	$dir = "$home_dir/$dir";	
	$titre_html =~ s/:/: /g;
	$titre_html =~ tr/_/ /;
	$mots_cles = $titre_html;
	$mots_cles =~ tr/:/, /;
	print "Fichier_HTML \$dir $dir\n";
	# Generation du Fichier HTML
	open (FICH,">$dir/$page_html") or die ("Impossible d'ouvrir $dir/$page_html : $!");
	print FICH "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2//EN\">\n";


	print FICH "\n<!--   cette page est generee par $version   -->\n\n";

	print FICH "<HTML>\n<HEAD>\n<TITLE>$nom_site: ";
	print FICH "$titre_html";
	print FICH "</TITLE>\n";
	print FICH "<META NAME=\"AUTHOR\" CONTENT=\"$nom_auteur\">\n";
	print FICH "<META NAME=\"GENERATOR\" CONTENT=\"$version\">\n";
	print FICH "<META NAME=\"KEYWORDS\" CONTENT=\"$nom_site, $mots_cles\">\n";
	print FICH "</HEAD>\n";
	print FICH $HTML_BODY,"\n";
	print FICH "\n<!--   cette page est generee par $version   -->\n\n";
	print FICH "<H3><A HREF=\"$home_url/\">$nom_site:</A> ";
	
	@rubriques = @t_titre;
	$rub=pop (@rubriques);
	$rub =~ tr/_/ /;
	$url = $home_url;


	foreach $rubrique(@rubriques) {
		$url = "$url/$rubrique";
		print FICH "<A HREF=\"$url/\">";
		$rubrique =~ tr/_/ /;
		print FICH "$rubrique:</A> ";
		}

	print FICH "$rub</H3>\n\n";
#################################
	local $pwd=$dir;

	local @ls;
	local @sous_categorie;
	opendir(LS,"$pwd") || &Erreur_Fichier($pwd);
	@ls = sort grep(!/^\./,readdir(LS));
	closedir(LS);

	foreach $fichier(@ls) {
		push (@sous_categorie,$fichier) if (-d "$pwd/$fichier");	

		}
	

		local $taille = @sous_categorie;
		local $t = @sous_categorie;
		local @col = @sous_categorie;
		local	$x;
		$taille += 1;
		$x = int $taille/2;
		
		if ($taille > 1) {
		print FICH "\n<!--   cette page est generee par $version   -->\n\n";
		print FICH "\t<!-- debut INDEX -->\n";
		print FICH "<TABLE>\n";
		print FICH "<TR>\n<TD VALIGN=\"TOP\" WIDTH=\"50%\">\n<UL>\n";
		for ($k=0;$k<$x;$k++) {
		print FICH "<LI><A HREF=\"$url/$rub/$col[$k]/\"><B>$col[$k]</B></A>\n"; 
		}
		print FICH "</UL>\n</TD>\n\n<TD VALIGN=\"TOP\" WIDTH=\"50%\">\n<UL>\n";
		for ($l=$k;$l<$t;$l++) {
			print FICH "<LI><A HREF=\"$url/$rub/$col[$l]/\"><B>$col[$l]</B></A>\n";
			}
		print FICH "</UL>\n</TD>\n</TR>\n</TABLE>\n\n";
		print FICH "\t<!-- fin INDEX -->\n";
		print FICH "<HR>\n";
		}
		print FICH "\n<!--   cette page est generee par $version   -->\n\n";

#####################################

 	print FICH "\t<!----------------- debut des SUJETS ------------------->\n\n";
	print FICH "<P>\n";
	for ($i=1;$i<$nbsujets;$i++) {
 		print FICH "\t<!-- debut SUJET No. $i -->\n";
		print FICH "<H4>$sujet[$i] </H4>\n";
		print FICH "<BLOCKQUOTE>\n<SMALL>Versions: ";
		print FICH "<A HREF=\"$ps_url/$fichier_ps[$i]\">PostScript</A> et ";
		print FICH "<A HREF=\"$pdf_url/$fichier_pdf[$i]\">PDF</A> ";
		print FICH "</SMALL>\n";
		print FICH "<P>\n$synopsis[$i]\n</BLOCKQUOTE>\n\n";
 		print FICH "\t<!-- fin SUJET No. $i -->\n\n";
		}

	print FICH "$COPYRIGHT\n</BODY>\n</HTML>\n";
	print FICH "\n<!--   cette page est generee par $version   -->\n\n";
	close(FICH);

}



################################################
#
sub Creation_Generale_HTML {

	opendir(DONNEES,"$rep_donnees") or die("Impossible d'ouvrir $rep_donnees : $!");
	@donnees = sort grep(!/^\./,readdir(DONNEES));
	closedir(DONNEES);
	
	foreach $fichier(@donnees) {
		&Lecture_Donnees("$rep_donnees/$fichier");	
		print "\$t_titre @t_titre \n";
		&Creation_Fichier_HTML;
	}

}


##########################################
# ls  - liste les fichiers du repertoire

sub ls {
    	local @sous_cat;
    	local $cat ="" ;
  	local @ls;
  	
	$pwd = "$home_dir/$_[0]";
    	opendir(LS,"$pwd") || &Erreur_Fichier("$pwd");
	@ls = sort grep(!/^\./,readdir(LS));
	closedir(LS);

	if ($#ls >= 0) {
		foreach $fichier(@ls) {
			push (@sous_cat,$fichier) if (-d "$pwd/$fichier");	
			}
 	}
	return(@sous_cat);

}




##########################
#
sub Fichier_INDEX {

	local @ls;
    	local @sous_categorie;
    	local $rep_local = "$_[0]";
    	local $pwd = "$home_dir/$_[0]";
    	local $titre;
	local $fichier;
    
	&Creation_Repertoire;

	opendir(LS,"$pwd") || &Erreur_Fichier($pwd);
	@ls = sort grep(!/^\./,readdir(LS));
	closedir(LS);

	foreach $fichier(@ls) {
		push (@sous_categorie,$fichier) if (-d "$pwd/$fichier");	
		}
	
	$page_index = "$pwd/$page_html";
	$titre = $rep_local;
	$titre =~ s/\//: /g;

	if ($VERBOSE == 1) {
		print "Fichier_INDEX:\t\@sous_categorie : @sous_categorie\n";
		print "\t\t\t\$page_index: $page_index\n";
		print "\t\t\t\$rep_local : $rep_local \n";
		print "\t\t\t\$#ls $#ls\n";
		print "\t\t\t @ls\n\n";
		}

	if ($#sous_categorie >= 0) {
		print "Fichier_INDEX: Creation index $pwd \n";
		
		open (IND, ">$page_index") || &Erreur_Fichier($page_index);
		print IND "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2//EN\">\n";
		print IND "\n<!--   cette page est generee par $version   -->\n\n";
		print IND "<HTML>\n<HEAD>\n<TITLE>$nom_site: INDEX de $titre";
		print IND "</TITLE>\n";
		print IND "<META NAME=\"AUTHOR\" CONTENT=\"$nom_auteur\">\n";
		print IND "<META NAME=\"GENERATOR\" CONTENT=\"$version\">\n";
		$titre =~ s/:/, /g;
		print IND "<META NAME=\"KEYWORDS\" CONTENT=\"$nom_site, $titre, ";
		
		foreach $mots(@sous_categorie) {
			$mots =~ tr/_/ /;
			print IND "$mots, " if ($mots);
			}
		
		print IND "\">\n</HEAD>\n";
		print IND $HTML_BODY,"\n<H3>";
		print IND "\n<!--   cette page est generee par $version   -->\n\n";
		print IND "<A HREF=\"$home_url\">$nom_site</A>: ";
		
		local $url = $rep_local;	
		$url =~ s/$home_dir//g;
		print "Fichier INDEX: \$url : $url\n" if ($VERBOSE == 1);	
		@arbre = split (/\//,$url);	
		local $arb_fin = pop (@arbre);
		local $arb_cum = $home_url;
		
		foreach $arb(@arbre) {
			$arb_cum = "$arb_cum/$arb";
			print IND "<A HREF=\"$arb_cum\">";
			$arb =~ tr/_/ /;
			print IND "$arb</A>: ";
			}
	
		$arb_fin =~ tr/_/ /;
		print IND "$arb_fin</H3>\n";

		print IND "<H3><UL>\n";

		foreach $cat(@sous_categorie) {
			if ($cat) {
				$cat =~ tr/ /_/;
				print IND "<LI><A HREF=\"$home_url/$rep_local/$cat/\">";
				$cat =~ tr/_/ /;
				print IND "$cat</A></LI>\n";
				}
			}
		
		print IND "</UL></H3>\n";
		print IND "$COPYRIGHT</BODY>\n</HTML>\n";
		print IND "\n<!--   cette page est generee par $version   -->\n\n";
		close(IND);
		}

}


###############################
#
sub Creation_Fichier_INDEX {

	local $cat1;
	local $cat2;
	local $cat3;
	
	foreach $cat1(@theme) {
		&Fichier_INDEX($cat1);
		foreach $cat2(&ls($cat1)) {
			&Fichier_INDEX("$cat1/$cat2");
			foreach $cat3(&ls("$cat1/$cat2")) {
				&Fichier_INDEX("$cat1/$cat2/$cat3");
				}
			}

		}	

}

###############################
#
sub Creation_Generale_INDEX {

	opendir(DONNEES,"$rep_donnees") or die("Impossible d'ouvrir $rep_donnees : $!");
	@donnees = sort grep(!/^\./,readdir(DONNEES));
	closedir(DONNEES);

	foreach $fichier(@donnees) {
		&Lecture_Donnees("$rep_donnees/$fichier");	
	}
		&Creation_Fichier_INDEX;

}


