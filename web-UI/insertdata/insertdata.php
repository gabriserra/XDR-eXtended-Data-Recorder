<?php
// -------------------------------------
// INSERTDATA.PHP
// permit to insert raw user data in
// SQL database
// -------------------------------------

// -----------------------------------
// JSON OBJECT SAMPLE
// -----------------------------------
/*
    '{  
        "mail" : 
            "user@example.it",
        "trip" : {
            "meters" : 50,
            "starttime" : "2018-01-07 07:30:00",
            "secondslength" : 120 
        },
        "stat" : {
            "numberacc" : 2,
            "worstacc" : 5,
            "numberbra" : 1,
            "worstbra" : 3,
            "numbercur" : 8 
        },
        "evaluation" : {
            "pointstotal" : 2,
            "pointsacceleration" : 5,
            "pointsbraking" : 1,
            "pointssteering" : 3,
            "pointsspeed" : 8 
        },
        "crash" : {
            "crashtime" : "2018-01-07 07:30:00",
            "intensity" : 5,
            "stationary" : 0,
        }
    }';
*/

// -------------------------------------
// REQUIRE
// -------------------------------------
require_once "assets/dbmanager.php";
require_once "assets/jsonresponse.php";

// -------------------------------------
// PHP SERVER MAIN CODE
// -------------------------------------

// GET DATA
// INSERT TRIP & RETRIEVE ID
// INSERT STAT
// INSERT EVALUATION
// INSERT CRASH (NOT MANDATORY)
// RETRIEVE RESUME
// CALCULATE NEW RESUME
// UPDATE RESUME
// CLOSE & SUCCESS REPLY

$data_array = json_decode($_POST['content'], true);
$trip_id = insert_trip($data_array['email'], $data_array['trip']);
insert_stat($trip_id, $data_array['stat']);
insert_evaluation($trip_id, $data_array['evaluation']);
insert_crash($trip_id, $data_array['crash']);
$resume = get_resume_points($data_array['email']);
$new_resume = calculate_new_resume($resume, $data_array['trip'], $data_array['evaluation']);
update_resume_data($data_array['email'], $new_resume);
close_and_reply();

// -------------------------------------
// DB QUERY FUNCTIONS
// -------------------------------------

// insert trip data and return the trip id
function insert_trip($email, $trip) {
    global $my_database;

    $query_string = 
        "INSERT INTO `xdr_trip` (`id`, `email`, `meters`, `starttime`, `secondslength`) 
        VALUES (NULL, 
                '" . $email . "', 
                '" . $trip['meters'] . "', 
                '" . $trip['starttime'] . "',
                '" . $trip['secondslength'] . "');";

    $my_result = $my_database->send_query($query_string);

    if (!$my_result)
        launch_error("Problem inserting trip data.");

    $my_id = $my_database->get_last_id();
}

// insert stat data into DB
function insert_stat($trip_id, $stat) {
    global $my_database;

    $query_string = 
        "INSERT INTO `xdr_stat` (`id`, `numberacc`, `worstacc`, `numberbra`, `worstbra`, `numbercur`) 
        VALUES ('" . $trip_id . "', 
                '" . $stat['numberacc'] . "', 
                '" . $stat['worstacc'] . "', 
                '" . $stat['numberbra'] . "',
                '" . $stat['worstbra'] . "',
                '" . $stat['numbercur'] . "');";

    $my_result = $my_database->send_query($query_string);

    if (!$my_result)
        launch_error("Problem inserting stat data.");
}

// insert evaluation data into db
function insert_evaluation($trip_id, $evaluation) {
    global $my_database;

    $query_string = 
        "INSERT INTO `xdr_evaluation` (`id`, `pointstotal`, `pointsacceleration`, `pointsbraking`, `pointssteering`, `pointsspeed`) 
        VALUES ('" . $trip_id . "', 
                '" . $evaluation['pointstotal'] . "', 
                '" . $evaluation['pointsacceleration'] . "', 
                '" . $evaluation['pointsbraking'] . "',
                '" . $evaluation['pointssteering'] . "',
                '" . $evaluation['pointsspeed'] . "');";

    $my_result = $my_database->send_query($query_string);

    if (!$my_result)
        launch_error("Problem inserting evaluation data.");
}

// insert crash data into db if crash data is not null
function insert_crash($trip_id, $crash) {
    global $my_database;

    if($crash == null)
        return;

    $query_string = 
        "INSERT INTO `xdr_crash` (`id`, `crashtime`, `intensity`, `stationary`) 
        VALUES ('" . $trip_id . "', 
                '" . $evaluation['crashtime'] . "', 
                '" . $evaluation['intensity'] . "', 
                '" . $evaluation['stationary'] . "');";

    $my_result = $my_database->send_query($query_string);

    if (!$my_result)
        launch_error("Problem inserting crash data.");
}

// get all resume info of a user
function get_resume_points($email) {
    global $my_database;

    $query_string = "SELECT * FROM user WHERE email = '" . $email . "'";
    $my_result = $my_database->send_query($query_string);
    
    if ($my_result->num_rows != 1)
        launch_error("Read user data failed.");
    
    $resume = $my_result->fetch_array();
    return $resume;
}

// calculate new resume data starting from new trip and old resume data
function calculate_new_resume($resume, $trip, $evaluation) {
    $driven_hour = $resume['drivenhours'];
    $triplen_hour = $trip['secondslength'] / 3600;
    $total_driven_hour = $driven_hour + $triplen_hour;

    $new_resume['pointstotal'] = ($resume['pointstotal'] * $driven_hour +
                                  $evaluation['pointstotal'] * $triplen_hour) 
                                    / $total_driven_hour;

    $new_resume['pointsacceleration'] = ($resume['pointsacceleration'] * $driven_hour +
                                         $evaluation['pointsacceleration'] * $triplen_hour) 
                                            / $total_driven_hour;
    
    $new_resume['pointsbraking'] = ($resume['pointsbraking'] * $driven_hour +
                                    $evaluation['pointsbraking'] * $triplen_hour) 
                                        / $total_driven_hour;

    $new_resume['pointssteering'] = ($resume['pointssteering'] * $driven_hour +
                                     $evaluation['pointssteering'] * $triplen_hour) 
                                        / $total_driven_hour;

    $new_resume['pointsspeed'] = ($resume['pointsspeed'] * $driven_hour +
                                  $evaluation['pointsspeed'] * $triplen_hour) 
                                    / $total_driven_hour;

    $new_resume['drivenhours'] = $total_driven_hour;

    return $new_resume;
}

// update resume data of user
function update_resume_data($email, $new_resume) {
    global $my_database;

    $query_string = "UPDATE `xdr_resume` SET 
                        `pointstotal` = '" . $new_resume['pointstotal'] . "', 
                        `pointsacceleration` = '" . $new_resume['pointsacceleration'] . "',
                        `pointsbraking` = '" . $new_resume['pointsbraking'] . "',
                        `pointssteering` = '" . $new_resume['pointssteering'] . "',
                        `pointsspeed` = '" . $new_resume['pointsspeed'] . "',
                        `drivenhours` = '" . $new_resume['drivenhours'] . "'
                    WHERE `xdr_resume`.`email` = '" . $email . "';";
    
    $my_result = $my_database->send_query($query_string);

    if (!$my_result)
        launch_error("Problem updating resume data.");
}

// reply to script caller & close the connection with db
function close_and_reply() {
    launch_response("Data inserted with success!");
    $my_database->close_connection();
}




