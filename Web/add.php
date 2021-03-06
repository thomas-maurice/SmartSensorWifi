<!DOCTYPE html>
<!--Ink header format -->
<html lang="fr">
    
    <head>
        <meta charset="utf-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
        <title>Ajout d'un capteur</title>
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
        
        <!-- Ink required css -->
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
		<!-- Main frame-->
		<div class="ink-grid">
            <header>
                <h1>Ajouter un capteur</h1>
                <?php 
                	include("dbconnect.php"); //Database connection file
	                include("nav.php"); // Navbar
                ?>
            </header>
		
					<?php
					// Check if the adding is really required
					if (isset($_POST['name'])){
						// ------------ Check is the user is registred ----------------
						if (isset($_COOKIE['login']) && isset($_COOKIE['password']) ){
							$check=$bdd->prepare("SELECT login, password FROM users");
                        	$check->execute();
                        	$data=$check->fetch();
                        	$check->closeCursor();
                        	if($_COOKIE['login']==$data['login'] && $_COOKIE['password']==$data['password']){
	                    // ------------ End of checking ----------------
	                        	
	                        	$i=0; // Using to know how many fields must be added
	                        	// --------------- Insert the name and the password of each new captors in the database ------------------
	                        	while( ($_POST['name'][$i] != NULL) && ($_POST['password'][$i] != NULL) ){
	                        		$up1=$_POST['name'][$i];
	                        		$up2=$_POST['password'][$i];	                        		
	                        		$req = $bdd->prepare("INSERT INTO data(name,password) VALUES(?,?)");
	                        		$req->execute(array($up1,$up2));
	                        		echo "Capteur ". $up1 . " ajouté à la base" . "</br>";
		                        	$i++;
		                        	$req->closeCursor();
		                        }
		                        // --------------- End of Insertion -------------------
		                    }
						}
					}
					// If the adding is not required, show the submitting form
					else{
					?>
						<!-- Send the information to itself by POST -->
		    			<form action="add.php" method="post">
		        			<div id="champs">
					        	<input name="name[]" type=text placeholder="Nom du capteur"><input name="password[]" type=text placeholder="Mot de passe du capteur">				
		        			</div>
						    <button type="button" onclick="addField()" >+</button>
					        <button type="submit" class="ink-button">Envoyer</button>
					        <!-- New field by javascript -->
					        <script type="text/javascript" src="addfield.js"></script>						        
		    			</form>
			   <?php } ?>
        </div>
        <?php include("footer.php"); ?>
	</body>
</html>