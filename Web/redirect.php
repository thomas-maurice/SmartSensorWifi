<?php    
/* ----------------- Redirection file used in case of login and logout -------------------
						Case of login : Create a cookie with login and password given by POST. Timed for 1 hour.
						Case of lougout : Set the previous cookie to destroyed state and set the time left to 0 (or negative time).
-----------------------------------------------------------------------------------------*/  
  header('Location: index.php');
  if( isset($_POST['login']) ) setcookie('login', $_POST['login'], time() + 3600, null, null, false, true);
  if( isset($_POST['password']) ) setcookie('password', $_POST['password'], time() + 3600, null, null, false, true);
  if ( isset($_POST['logout']) ){
  	setcookie('login', 'destroyed', time() - 3600, null, null, false, true);
	setcookie('password', 'destroyed', time() - 3600, null, null, false, true);
  }      
?>