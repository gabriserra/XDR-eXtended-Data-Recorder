<?php

// -------------------------
// GETHOME.PHP
// It contains PHP code to
// fill up home cards 
// -----------------------

header('Access-Control-Allow-Origin: https://gabriserra.github.io');
header('Access-Control-Allow-Credentials: true');

// -------------------------------------
// REQUIRE
// -------------------------------------
require_once "assets/dbmanager.php";
require_once "assets/session.php";
require_once "assets/jsonresponse.php";

// start the current session
session_start();

// if user is not logged launch error and die
logged_user_check();

// retrieve last trip data
retrieve_last_trip();

// -------------------------------------
// UTILITY
// -------------------------------------

// Check if user is already logged in
function logged_user_check() {
    if(!is_user_logged())
        launch_error("Not yet logged.");        
}

// -------------------------------------
// GET CRASH DATE LIST
// -------------------------------------

// Retrieve and send crash dates to client
function retrieve_last_trip() {
    global $my_database;

    $query_string = "SELECT * 
                     FROM `xdr_trip` INNER JOIN `xdr_evaluation` ON (`xdr_trip`.`id` = `xdr_evaluation`.`id`)
                     WHERE `email` = '" . get_user_email() . "'
                     AND `xdr_trip`.`id` >= (SELECT MAX(`xdr_trip`.`id`)
                                FROM `xdr_trip`
                                WHERE `email` = '" . get_user_email() . "')";
    
    $my_result = $my_database->send_query($query_string);
    
    if ($my_result->num_rows == 0)
        launch_error("No trip found.");

    send_trip_info($my_result->fetch_array());
}
