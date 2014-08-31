<?
	echo "Sensor\n";
	if(isset($_POST['temp'])) {
		echo 'temp:'.$_POST['temp'] . '\n';
	}
	if(isset($_POST['lum'])) {
		echo 'lum:'.$_POST['lum'] . '\n';
	}
?>
