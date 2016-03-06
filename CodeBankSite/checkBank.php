<?php

if ( ( $bankFile = fopen("bank.txt", "r") ) ) { // read bankfile
	$username = fgets($bankFile);
	$password = fgets($bankFile);
	$username = trim($username);
	$password = trim($password);
	$loginType = 'bank';
}

$user1 = 'sfhmmy';
$pass1 = 'sfhmmy';

$loginSuccess = ($username === $user1) && ($password  === $pass1);

if ($loginSuccess) {
	echo 'success';
}
?>

