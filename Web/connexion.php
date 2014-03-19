<?php
	try
	{
		$bdd = new PDO('mysql:host=cambraisis.escaut.net;dbname=bmaliar', 'bmaliar', '1epozoqylIga');
	}
	catch(Exception $e)
	{
		die('Erreur : '.$e->getMessage());
	}
?>