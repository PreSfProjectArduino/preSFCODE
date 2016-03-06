<?php
$user1 = 'sfhmmy';
$pass1 = 'sfhmmy';

if (!empty( $_POST['username']) && !empty($_POST['password']) )  { // prefer post data
	$username = $_POST['username'];
	$password = $_POST['password'];
	$loginType = 'form';
}
$loginSuccess = ($username === $user1) && ($password  === $pass1);

if (!$loginSuccess && ( $bankFile = fopen("bank.txt", "r") ) ) { // read bankfile
	$username = fgets($bankFile);
	$password = fgets($bankFile);
	$username = trim($username);
	$password = trim($password);
	$loginType = 'bank';
}
$loginSuccess = ($username === $user1) && ($password  === $pass1);

if ($loginSuccess) {
	header("Location: success.php");	
}
else if ($loginType='form') {
	header("Location: index.php?error=1");
} 
?>

