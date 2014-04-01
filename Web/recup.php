<?php

	//Execute the update only if Json's $_POST is received
	if (isset($_POST['mid']) && isset($_POST['mpass'])){
		//Connection's file
		include("connexion.php");
				
		//Extract the received data
		$id = $_POST['mid'];
		$password = $_POST['mpass'];
		$temp = $_POST['temp'];
		$lum = $_POST['lum'];
		
		//Check the user
		$check = $bdd->prepare("SELECT password FROM captors WHERE id=?");
		$check->execute(array($id));
		$test=$check->fetch();
		//Close the request's connection
		$check->closeCursor();
		
		if ($test['password']==$password && $password!=NULL && $test['password']!=NULL){
		
			//Prepare and execute the update on the DB
			$now =$today = date("Y-m-d H:i:s");
			$req = $bdd->prepare("UPDATE data SET temp=?, lum=?,timestamp=? WHERE id=?");
			$req->execute(array($temp,$lum,$now,$id));
			
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