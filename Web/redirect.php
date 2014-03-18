<?php      
  header('Location: index.php');
  if( isset($_POST['login']) ) setcookie('login', $_POST['login'], time() + 3600, null, null, false, true);
  if( isset($_POST['password']) ) setcookie('password', $_POST['password'], time() + 3600, null, null, false, true);
  if ( isset($_POST['logout']) ){
  	setcookie('login', 'destroyed', time() - 3600, null, null, false, true);
	setcookie('password', 'destroyed', time() - 3600, null, null, false, true);
  }      
?>