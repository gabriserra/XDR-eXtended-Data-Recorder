<?php
// -------------------------------------
// LOGOUT.PHP
// contains php script to logout from
// server
// -------------------------------------

header('Access-Control-Allow-Origin: https://gabriserra.github.io');
header('Access-Control-Allow-Credentials: true');

// header path location
define("HOME_PATH", "https://gabriserra.github.io/XDR-eXtended-Data-Recorder/");

// session start/init
session_check();

// destroy session
session_destroy();

//readdress to calling page
header("Location: " . HOME_PATH);

// Start PHP session or fill with empty one
function session_check() {
    if (!isset($_SESSION))
        session_start();
    else
        $_SESSION = array();
}

?>
