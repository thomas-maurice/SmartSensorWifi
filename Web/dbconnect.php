<?php
	/* ---------------- Connection file to the database -----------------
		The connection uses the PDO method.
		In order to use it and match the informations for your own database, just replace the informations by your own in the PDO line.
	*/
	
	try
	{
		$bdd = new PDO('mysql:host=hostofthedatabase;dbname=nameofthedb', 'user', 'password');
	}
	catch(Exception $e)
	{
		die('Erreur : '.$e->getMessage());
	}
?>