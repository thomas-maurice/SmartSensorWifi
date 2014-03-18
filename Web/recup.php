<?php

	//Execute the update only if Json's $_POST is received
	if (isset($_POST)){
		//Connection's file
		include("connexion.php");
		
		$json = $_POST;	
		
		// Json's test
			//$json = '{"id":"1","password":"PaSsWoRd","temp":"2","lum":"3","detect":"4"}';
		//End of Json's test 
		
		//Extract the received data
		$var = json_decode($json);
		$id = $var->{'id'};
		$password = $var->{'password'};
		$temp = $var->{'temp'};
		$lum = $var->{'lum'};
		
		//Check the user
		$check = $bdd->prepare("SELECT password FROM user WHERE id=?");
		$check->execute(array($id));
		$test=$check->fetch();
		//Close the request's connection
		$check->closeCursor();
		
		if ($test['password']==$password && $password!=NULL && $test['password']!=NULL){
		
			//Prepare and execute the update on the DB
			$req = $bdd->prepare("UPDATE data SET temp=?, lum=?, WHERE id=?");
			$req->execute(array($temp,$lum,$id));
			
			//Printing the update informations
			echo 'Mise à jour de la table pour le capteur ' . $id . '</br>';
			echo 'Température : ' . $temp . '</br>';
			echo 'Luminosité : ' . $lum . '</br>';
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