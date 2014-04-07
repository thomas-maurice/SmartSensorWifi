<?php
	//Execute the update only if $_POST is received
	if (isset($_POST['mid']) && isset($_POST['mpass']) && isset($_POST['temp']) && isset($_POST['lum'])){
		//Connection's file
		include("dbconnect.php");
				
		//Extract the received data
		//$id = trim($_POST['mid']);
		//$password = trim($_POST['mpass']);
		//$temp = $_POST['temp'];
		//$lum = $_POST['lum'];
		
		//Check the user
		$check = $bdd->prepare("SELECT password FROM data WHERE id=?");
		$check->execute(array(trim($_POST['mid'])));
		$test=$check->fetch();
		//Close the request's connection
		$check->closeCursor();
		
		if ($test['password']==trim($_POST['mpass'])){
		
			//Prepare and execute the update on the DB
			//$now =date("Y-m-d H:i:s");
			$req = $bdd->prepare("UPDATE data SET timestamp=? WHERE id=?");
			$req->execute(array(date("Y-m-d H:i:s"),trim($_POST['mid'])));
			$req = $bdd->prepare("UPDATE captors SET temp=?, lum=?,timestamp=? WHERE id=? ");
			$req->execute(array(round(($_POST['temp']*0.647),1),$_POST['lum'],date("Y-m-d H:i:s"),trim($_POST['mid'])));
			
			//Printing the update informations
			echo 'Mise à jour de la table pour le capteur ' . $_POST['mid'] . '</br>';
			echo 'Température : ' . $_POST['temp'] . '</br>';
			echo 'Luminosité : ' . $_POST['lum'] . '</br>';
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