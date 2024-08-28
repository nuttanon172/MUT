<?php
    if (isset($_POST['login'])){
        session_start();
        if ($_POST['username'] == 'natthanon' && $_POST['password'] == 'abc'){
            $_SESSION['session_name']='natthanon';
            header('location: show.php');exit();
        }
        else if ($_POST['username'] == 'fluke' && $_POST['password'] == 'abc'){
            $_SESSION['session_name']='fluke';
            header('location: show.php');exit();
        }
        else
            unset($_SESSION['session_name']);
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <form action="index.php" method="post">
        username:<input type="text" name="username"><br>
        password:<input type="text" name="password"><br>
        <input type="submit" name="login" value="login">
    </form>
</body>
</html>