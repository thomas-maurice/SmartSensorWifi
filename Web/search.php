<!DOCTYPE html>
<html lang="fr">
    
    <head>
        <meta charset="utf-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
        <title>Recherche d'un capteur</title>
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
                <h1>Rechercher un capteur</h1>
                <?php 
                	include("dbconnect.php"); 
	                include("nav.php");
                ?>
            </header>
			<div class="ink-form large-100 medium-100 small-100">
				<?php
				if (isset($_COOKIE['login']) && isset($_COOKIE['password']) ){
					$check=$bdd->prepare("SELECT login, password FROM users");
                	$check->execute();
                	$data=$check->fetch();
                	$check->closeCursor();
                	if($_COOKIE['login']==$data['login'] && $_COOKIE['password']==$data['password']){
						if (isset($_POST['id']) || isset($_POST['name'])){
						  ?>
							<div class="ink-form large-100 medium-100 small-100">
		    				<h3> Informations sur le capteur demandé </h3>
			    			<table class="ink-table bordered">
				    		<thead>
					    	<tr>
						    	<th>ID</th>
						    	<th>Nom</th>
						    	<th>Temperature</th>
						    	<th>Luminosité</th>
						    	<th>Date</th>
						    </tr>
						    </thead>                            
						    <tbody>
						  <?php
							if(isset($_POST['id'])){
								$req = $bdd->prepare('SELECT id, name, temp, lum, timestamp FROM data WHERE id=? ORDER BY id');
								$req->execute(array((int)$_POST['id']));
							}
							else{
								$req = $bdd->prepare('SELECT id, name, temp, lum, timestamp FROM data WHERE name=? ORDER BY id');
								$req->execute(array($_POST['name']));
							}
								while ($donnees = $req->fetch()){
									echo '<tr>';
								    echo '<td>' . '<center>' . $donnees['id'] . '</center>' . '</td>';
									echo '<td>' . '<center>' . $donnees['name'] . '</center>' . '</td>';
									echo '<td>' . '<center>' . $donnees['temp'] . '</center>' . '</td>';
									echo '<td>' . '<center>' . $donnees['lum'] . '</center>' . '</td>';
									echo '<td>' . '<center>' . $donnees['timestamp'] . '</center>' . '</td>';
									echo '</tr>';
								}
								$req->closeCursor();
				?>
							</tbody>
							</table>
							</div>
	           <?php }
	           	else {?>
						<form action="search.php" method="post" class="ink-form">
							<p>Recherche par ID : </p>
							<select name="id">'
							<fieldset class="column-group gutters">
		    					<div class="control-group large-33 medium-33 small-100">
			    					<div class="control-group gutters required">
				    					<div class="control medium-20">
		    			<?php
		    				$value = $bdd->query('SELECT id FROM data ORDER BY id');
		    				while ($data = $value->fetch()){
		        				echo'<option value="'.$data['id'].'">'.$data['id'].'</option>';
		        			}
		        			$value->closeCursor();
		        		?>
				    					</div>
				    				</div>
				    			</div>
				    		</fieldset>
				    		</select>
				    		<button type="submit" class="ink-button">Envoyer</button>
				    	</form>
				    	<form action="search.php" method="post" class="ink-form">
							<p>Recherche par nom : </p>
							<select name="name">'
							<fieldset class="column-group gutters">
		    					<div class="control-group large-33 medium-33 small-100">
			    					<div class="control-group gutters required">
				    					<div class="control medium-20">
		    			<?php
		    				$value = $bdd->query('SELECT name FROM data ORDER BY name');
		    				while ($data = $value->fetch()){
		        				echo'<option value="'.$data['name'].'">'.$data['name'].'</option>';
		        			}	
		        			$value->closeCursor();
		        		?>
				    					</div>
				    				</div>
				    			</div>
				    		</fieldset>
				    		</select>
				    		<button type="submit" class="ink-button">Envoyer</button>
				    	</form>
			 <?php } 
				 }
			   }
			    ?>
			</div>
        </div>
	</body>
	<?php include("footer.php"); ?>
</html>