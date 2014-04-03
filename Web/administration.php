<!DOCTYPE html>
<html lang="fr">
    
    <head>
        <meta charset="utf-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
        <title>Management</title>
        <meta name="description" content="">
        <meta name="author" content="Maliar Benoit, Maurice Thomas">
        <meta name="HandheldFriendly" content="True">
        <meta name="MobileOptimized" content="320">
        <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0">
        <link rel="shortcut icon" href="/ink/img/polytech.ico">
        <link rel="apple-touch-icon-precomposed" href="/ink/img/touch-icon.57.png">
        <link rel="apple-touch-icon-precomposed" sizes="72x72" href="/ink/img/touch-icon.72.png">
        <link rel="apple-touch-icon-precomposed" sizes="114x114" href="/ink/img/touch-icon.114.png">
        <link rel="apple-touch-startup-image" href="/ink/img/splash.320x460.png"
        media="screen and (min-device-width: 200px) and (max-device-width: 320px) and (orientation:portrait)">
        <link rel="apple-touch-startup-image" href="/ink/img/splash.768x1004.png"
        media="screen and (min-device-width: 481px) and (max-device-width: 1024px) and (orientation:portrait)">
        <link rel="apple-touch-startup-image" href="/ink/img/splash.1024x748.png"
        media="screen and (min-device-width: 481px) and (max-device-width: 1024px) and (orientation:landscape)">
        <link rel="stylesheet" type="text/css" href="/ink/css/ink.css">
        
        <!--[if IE 7 ]>
            <link rel="stylesheet" href="/ink/css/ink-ie7.css" type="text/css" media="screen" title="no title" charset="utf-8">
        <![endif]-->
        
        <script type="text/javascript" src="/ink/js/holder.js"></script>
        <script type="text/javascript" src="/ink/js/ink.min.js"></script>
        <script type="text/javascript" src="/ink/js/ink-ui.min.js"></script>
        <script type="text/javascript" src="/ink/js/autoload.js"></script>
        <script type="text/javascript" src="/ink/js/html5shiv.js"></script>
        
        
        <style type="text/css">
       		body {
                background: #ededed;
            }
            header {
                padding: 2em 0;
                margin-bottom: 2em;
            }
            header h1 {
                font-size: 2em;
            }
            header h1 small:before  {
                content: "|";
                margin: 0 0.5em;
                font-size: 1.6em;
            }
            footer {
                background: #ccc;
                color: #0003;
            }
            footer p {
                padding: 0.5em 1em 0.5em 0;
                margin: 0;        
            }

        </style>
    </head>
    
	<body>
		<div class="ink-grid">
            <header>
                <h1>Panel de gestion</h1>
                <?php 
                	include("dbconnect.php"); 
	                include("nav.php");
                ?>
            </header>
            
            <?php
            // PHP Functions
            function DiffDate($date) {
            	$now=date("Y-m-d H:i:s");
            	$d1=strtotime($date);
            	$d2=strtotime($now);
            	if ($d2 < ($d1+3601))
            		return 0;
            	else
            		return 1;
			}
            ?>
            <div class="column-group gutters">
            <?php
	        	if( isset($_COOKIE['login']) && isset($_COOKIE['password']) ){
	            	if($_COOKIE['login']!='destroyed' && $_COOKIE['password']!='destroyed'){
						$check=$bdd->prepare("SELECT login, password FROM users");
						$check->execute();
						$data=$check->fetch();
					  if ( ($data['login']==$_COOKIE['login']) && ($data['password']==$_COOKIE['password']) ){			
			?>
            	<div class="ink-form large-50 medium-50 small-100">
            <?php
						if ( isset($_POST['adduser']) && isset($_POST['addpassword']) ){
							$req=$bdd->prepare("INSERT INTO users(login,password) VALUES(?,?)");
	                        $req->execute(array($_POST['adduser'],$_POST['addpassword']));
	                        $req->closeCursor();
	                        echo '<div class="ink-form large-50 medium-50 small-100">';
	                        echo "Utilisateur ". $_POST['adduser'] . " ajouté à la base avec mot de passe " . $_POST['addpassword'] . '</div>';							
						}
						if ( isset($_POST['deluser']) ){
                    		$req = $bdd->prepare("DELETE FROM users WHERE login=?");
                    		$req->execute(array($_POST['deluser']));
	                        $req->closeCursor();                    		
	                        echo '<div class="ink-form large-50 medium-50 small-100">';                    
                    		echo "Utilisateur ". $_POST['deluser'] . " supprimé de la base" . "</div>";
						}
						else{		         	
							if ( isset($_POST['deltable']) ){
								if ( isset($_POST['deltable']) ){
		?>	
									<h3> Etes vous vraiment sûr de vouloir vider la table ? </h3>
									<p>Toutes les données seront perdues.</p>
									<form action="administration.php" method="post">
										<input name="deltables" type=hidden>
										<button type="submit" class="ink-button">Oui je le veux !</button>
									</form>
		<?php		
								}
							}
							else if ( isset($_POST['deltables']) ){
								$req = $bdd->prepare("DELETE FROM data");
								$req->execute();
								$req = $bdd->prepare("ALTER TABLE `data` AUTO_INCREMENT =1");
								$req->execute();
								$req->closeCursor();
								echo '<p>Toutes les données de la table ont été supprimés</p>';
							}
							else{
			?>
				            	<h3> Ajout d'un utilisateur </h3>
				            	<form action="administration.php" method="post">
				           			<input name="adduser" type=text placeholder="Nom de l'utilisateur">
				           			<input name="addpassword" type=text placeholder="Mot de passe">
				           			<button type="submit" class="ink-button">Envoyer</button>
				           		</form>
					            <h3> Suppression d'un utilisateur </h3>
						        <form action="administration.php" method="post">
					           		<input name="deluser" type=text placeholder="Nom de l'utilisateur">
					           		<button type="submit" class="ink-button">Envoyer</button>
					         	</form>
					            <h3> Vider les tables </h3>
					            <small>Ceci ne concerne que les tables des capteurs</small>
						        <form action="administration.php" method="post">
					           		<input name="deltable" type=hidden>
					           		<button type="submit" class="ink-button">Envoyer</button>
					         	</form>
			<?php
					        }
				        }
				      }
				      $check->closeCursor();
					}
				?>
            	</div>
            	<div class="large-50 medium-50 small-100">
			<?php
					$req2 = $bdd->prepare("SELECT timestamp, id FROM data");
					$req2->execute();
					$nb=0;
					$wg=0;
					echo '<div class="column-group gutters">' . '<div class="large-50 medium-50 small-50">';
					echo '<h3>Erreurs :</h3>';
					echo '<div style="height:260px;width:230px;border:1px solid #ccc;overflow:auto;">';
					echo '<ul>';
					while ($toulouse = $req2->fetch()){
						settype($toulouse[0],"string");
						$nb++;
						if ( DiffDate($toulouse[0]) ){
							$wg++;
							echo '<li>Capteur: ' . $toulouse[1] . '</li>';
						}
					}
					echo "</ul></div><small> Liste des capteurs n'ayant pas répondu depuis une heure.</small> </div>" .'<div class="large-50 medium-50 small-50">';
					echo '<h3><span class="ink-badge orange">' .$wg . '</span>  /<span class="ink-badge blue">' . $nb . '</span></h3>';  
					echo '</div>';
					$req2->closeCursor();
			?>
				</div>
			</div>
			<?php } ?>
	    </div>
	    <?php include("footer.php"); ?>
   </body>
</html>