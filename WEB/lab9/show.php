<?php session_start(); 
if (!isset($_SESSION['session_name'])){
	header('location: index.php');
	exit();
}
?>
SESSION<br>
<?php
	if (isset($_SESSION['session_name'])){
		echo $_SESSION['session_name'];
	}
?>
<div>
	<img src="pika.jpg" width="250" height="300">
</div>	
<a href="logout.php">logout</a>
