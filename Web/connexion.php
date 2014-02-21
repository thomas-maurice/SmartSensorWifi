<?php
	try
	{
		$bdd = new PDO('mysql:host=localhost;dbname=Smart', 'root', 'root');
	}
	catch(Exception $e)
	{
		die('Erreur : '.$e->getMessage());
	}
?>