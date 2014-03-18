<!DOCTYPE html>
<html lang="fr">
    
    <head>
        <meta charset="utf-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
        <title>
            Smart Sensor Wifi. Check your Sensor !
        </title>
        <meta name="description" content="Webpage monitoring of the project">
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
                <h1>Smart Sensor Wifi<small>Maliar Benoit & Maurice Thomas</small></h1>
                <?php 
                	include("connexion.php"); 
	                include("nav.php");
                ?>    
            </header>
            
            <div class="column-group gutters">
            <?php
					if( isset($_COOKIE['login']) && isset($_COOKIE['password']) ){
					  if($_COOKIE['login']!='destroyed' && $_COOKIE['password']!='destroyed'){

						$check=$bdd->prepare("SELECT login, password FROM admin");
						$check->execute();
						$data=$check->fetch();
						$check->closeCursor();
						if($_COOKIE['login']==$data['login'] && $_COOKIE['password']==$data['password']){
		    				//Select all data in the db with prepared request
		    				$req = $bdd->prepare('SELECT id, name, temp, lum FROM data');
		    				$req->execute();
		    ?>
		    				<div class="ink-form large-50 medium-50 small-100">
			    				<p><table class="ink-table">
				    			<thead>
					    			<tr>
						    			<th>ID</th>
						    			<th>Identifiant</th>
						    			<th>Temperature</th>
						    			<th>Luminosité</th>
						    		</tr>
						    	</thead>                            
						    	<tbody>
							    	<?php
								    	while ($donnees = $req->fetch()){
									    	echo '<tr>';
									    	echo '<td>' . '<center>' . $donnees['id'] . '</center>' . '</td>';
									    	echo '<td>' . '<center>' . $donnees['name'] . '</center>' . '</td>';
									    	echo '<td>' . '<center>' . $donnees['temp'] . '</center>' . '</td>';
									    	echo '<td>' . '<center>' . $donnees['lum'] . '</center>' . '</td>';
									    	echo '</tr>';
									    }
									    $req->closeCursor();
									?>
								</tbody>
								</table></p> 
							</div>
							<div class="large-50 medium-50 small-100">
								<p>
									Chuck Norris once kicked a baby elephant into puberty. Crop circles are Chuck Norris' way of telling the world that sometimes corn needs to lie the f*ck down.
								</p>
							</div>
		    	  <?php }
		    	  		else
		    	  		{
		    	  			echo "Vous n'avez pas la permission !"; ?>	
		    	  			<form action="redirect.php" method="POST">
	                        <input type="hidden" value="logout" name="logout">
	                        <input type="submit"  class='ink-button' value="Retour">
	                    <?php
	                    }
		    	  }
		    	}
				else{ ?>
				<div class="ink-form large-50 medium-50 small-100">
	    			<form action="redirect.php" method="post" class="ink-form">
	        			<fieldset class="column-group gutters">
	        				<div class="control-group large-33 medium-33 small-100">
	        					<div class="control-group gutters required">
		        					<div class="control medium-20">
			        					<input name=login type=text placeholder="Login">
			        				</div>
	        					</div>
	        				</div>
	        				<div class="control-group large-33 medium-33 small-100">
			        			<div class="control required">
				        			<input name=password type=password placeholder="Password">
			        			</div>
				        	</div>
				        	<div class="control-group large-33 medium-33 small-100">
					        	<div class="column">
				        			<div class="control">
				        				<button type="submit" class="ink-button">Envoyer</button>
				        			</div>
				        		</div>
				        	</div 	
		  				</fieldset>	
	    			</form>
	    		</div
		<?php } ?>	                            
            </div>
        </div>               
        <footer>
            <div class="ink-grid">
                <nav class="ink-navigation push-left medium-100 small-100 small-push-left">
                    <ul class="menu horizontal">
                        <li><a href="#">Link</a></li>
                    </ul>
                </nav>
                <p class="push-right small-100">GNU GPL. 2014</p>
            </div>
        </footer>
    </body>
</html>