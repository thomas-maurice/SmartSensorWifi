<?php
	try
	{
		$bdd = new PDO('mysql:host=nameofhost;dbname=nameofdb', 'user', 'password');
	}
	catch(Exception $e)
	{
		die('Erreur : '.$e->getMessage());
	}
?>