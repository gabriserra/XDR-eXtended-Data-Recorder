<?php
// -------------------------------------
// LOGOUT.PHP
// contains php script to logout from
// server
// -------------------------------------


// session start/init
session_check();

// destroy session
session_destroy();

//readdress to calling page
header("Location: " . $_SERVER['HTTP_REFERER']);

// Start PHP session or fill with empty one
function session_check() {
    if (!isset($_SESSION))
        session_start();
    else
        $_SESSION = array();
}

?>
