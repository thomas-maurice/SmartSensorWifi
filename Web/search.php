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
        <script type="text/javascript" src="Chart.js"></script>

        
        
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
                	include("dbconnect.php"); //Database connection
	                include("nav.php");	// Navbar
                ?>
            </header>
			<div class="ink-form column-group gutters large-100 medium-100 small-100">
				<?php
				// Check if the user is a validated user
				if (isset($_COOKIE['login']) && isset($_COOKIE['password']) ){
					$check=$bdd->prepare("SELECT login, password FROM users");
                	$check->execute();
                	$data=$check->fetch();
                	$check->closeCursor();
                	if($_COOKIE['login']==$data['login'] && $_COOKIE['password']==$data['password']){
                		// ---------------- If informations are requested ---------------
						if (isset($_POST['id']) || isset($_POST['name'])){
						  ?>
						  	<!-- Show the informations designed || Left column-->
							<div class="ink-form large-50 medium-50 small-100">
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
						  	// Extract the informations from the database, searching by ID
							if(isset($_POST['id'])){
								$req = $bdd->prepare('SELECT data.id, data.name, captors.temp, captors.lum, captors.timestamp FROM data,captors WHERE data.id=? AND data.id=captors.id ORDER BY data.id');
								$req->execute(array((int)$_POST['id']));
							}
							// Extract the informations from the database, searching by name
							else{
								$req = $bdd->prepare('SELECT data.id, data.name, captors.temp, captors.lum, captors.timestamp FROM data,captors WHERE data.name=? AND data.id=captors.id ORDER BY data.name');
								$req->execute(array($_POST['name']));
							}
								// Display the extracted informations
								$i=0;
								$chart_temp; // Chart temperature array
								$chart_lum; // Chart lightning array
								while ($donnees = $req->fetch()){
									echo '<tr>';
								    echo '<td>' . '<center>' . $donnees['id'] . '</center>' . '</td>';
									echo '<td>' . '<center>' . $donnees['name'] . '</center>' . '</td>';
									echo '<td>' . '<center>' . $donnees['temp'] . '</center>' . '</td>';
									echo '<td>' . '<center>' . $donnees['lum'] . '</center>' . '</td>';
									echo '<td>' . '<center>' . $donnees['timestamp'] . '</center>' . '</td>';
									echo '</tr>';
									$chart_lum[$i]=$donnees['lum']; // Save the lighning's informations for the chart
									$chart_temp[$i]=$donnees['temp']; // Save the temperature's informations for the chart
									$i++;
								}
								$req->closeCursor();
				?>
							</tbody>
							</table>
							</div>
							<!-- Display the chart || Right column -->
							<div class="ink-form large-50 medium-50 small-100">
							<h4> <center>Graphique des 10 dernières mesures du capteur</center></h4>
							<small><center>10 correspond à la valeur la plus récente</center></small>
							<canvas id="chart" width="600" height="400">
							</canvas>
							<?php
								for($i = 0;$i <=9;$i++){
									if ($chart_lum[$i] == NULL)
										$chart_lum[$i] = 0;
									if ($chart_temp[$i] == NULL)
										$chart_temp[$i] = 0;
								}
							?>
							<!-- Javascript displaying the chart using Chart.js -->
							<script type="text/javascript">
							// Display the chart in "chart" div
							var ctxChart = document.getElementById("chart").getContext("2d");
							// Adding the data to the chart
							var data = {
								labels : ["1","2","3","4","5","6","7","8","9","10"],
								datasets : [
									{
										fillColor : "rgba(255,140,0,0.5)",
										strokeColor : "rgba(255,140,0,1)",
										data : [<?php
											for($i =0;$i <=8;$i++){
												echo $chart_lum[$i].',';
											}
											echo $chart_lum[9];
											echo ']';
										?>
									},
									{
										fillColor : "rgba(0,191,255,0.5)",
										strokeColor : "rgba(0,191,255,1)",
										data : [<?php
											for($i =0;$i <=8;$i++){
												echo $chart_temp[$i].',';
											}
											echo $chart_temp[9];
											echo ']';
										?>
									}
								]
							}	
							new Chart(ctxChart).Bar(data,{});
							</script>
							<!-- Caption -->
							<center><small><font color="#FF8C00">Luminosité</font></small></br>
							<small><font color="#00BFFF">Temperature</font></small></center>
							</div>
						</div>
	           <?php }
	           // -------------- If nothing is requested, display the search selector ------------
	           	else {?>
						<!-- By ID -->
						<form action="search.php" method="post" class="ink-form">
							<p>Recherche par ID : </p>
							<select name="id">'
							<fieldset class="column-group gutters">
		    					<div class="control-group large-33 medium-33 small-100">
			    					<div class="control-group gutters required">
				    					<div class="control medium-20">
		    			<?php
		    				// Extracts the informations from the DB and displays it
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
				    	<!-- By name -->
				    	<form action="search.php" method="post" class="ink-form">
							<p>Recherche par nom : </p>
							<select name="name">'
							<fieldset class="column-group gutters">
		    					<div class="control-group large-33 medium-33 small-100">
			    					<div class="control-group gutters required">
				    					<div class="control medium-20">
		    			<?php
		    				// Extracts the informations from the DB and displays it
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