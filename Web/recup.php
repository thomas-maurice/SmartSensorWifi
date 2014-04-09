<?php
	//Execute the update only if $_POST is received
	if (isset($_POST['mid']) && isset($_POST['mpass']) && isset($_POST['temp']) && isset($_POST['lum'])){
		//Connection's file
		include("dbconnect.php");
						
		//Check the user
		$check = $bdd->prepare("SELECT password FROM data WHERE id=?");
		$check->execute(array(trim($_POST['mid'])));
		$test=$check->fetch();
		//Close the request's connection
		$check->closeCursor();
		
		if ($test['password']==trim($_POST['mpass'])){
		
			//Prepare and execute the update on the DB
			$req = $bdd->prepare("UPDATE data SET timestamp=? WHERE id=?");
			$req->execute(array(date("Y-m-d H:i:s"),trim($_POST['mid'])));
			$req = $bdd->prepare("INSERT INTO captors(temp,lum,timestamp,id) VALUES(?,?,?,?)");
			$req->execute(array(round(($_POST['temp']*0.647),1),$_POST['lum'],date("Y-m-d H:i:s"),trim($_POST['mid'])));
			
			//Printing the update informations
			echo 'Mise à jour de la table pour le capteur ' . $_POST['mid'] . '</br>';
			echo 'Température : ' . $_POST['temp'] . '</br>';
			echo 'Luminosité : ' . $_POST['lum'] . '</br>';
			
			//Delete outdated datas (older than today)
			$today = date("Y-m-d");
			$today = $today . " 00:00:01";
			echo $today;
			$req = $bdd->prepare("DELETE  captors FROM captors WHERE timestamp  <  ?");
			$req->execute(array($today));
			
			// Error info
			$errorinfo = $req->errorInfo();
			if ($errorinfo == 00000){
				print_r($errorinfo);	
			}
			//Close the request's connection
			$req->closeCursor();
		}
		else{
			echo "Permission refusée";
		}							
	}
?>