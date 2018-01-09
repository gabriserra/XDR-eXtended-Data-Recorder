<?php
// -------------------------------------
// JSONRESPONSE.PHP
// contains php function to echo
// a JSON response
// -------------------------------------

// Retrieve a JSON object with user data
function send_user_data($username, $name, $surname, $bio, $avatar, $cover) {
    echo '{  
        "error" : false, 
        "message" : { 
            "username" : "' . $username . '",
            "name" : "' . $name . '",
            "surname" : "' . $surname . '",
            "bio" : "' . $bio . '",
            "avatar" : "' . $avatar . '",
            "cover" : "' . $cover . '"} 
        }';
    exit(0);
}

// Retrieve a JSON object with last trip data
function send_trip_info($query_result) {
    echo '{  
        "error" : false, 
        "lasttripdata" : { 
            "meters" : "' . $query_result['meters'] . '",
            "starttime" : "' . $query_result['starttime'] . '",
            "secondslength" : "' . $query_result['secondslength'] . '",
            "pointstotal" : "' . $query_result['pointstotal'] . '",
            "pointsacceleration" : "' . $query_result['pointsacceleration'] . '",
            "pointsbraking" : "' . $query_result['pointsbraking'] . '",
            "pointssteering" : "' . $query_result['pointssteering'] . '",
            "pointsspeed" : "' . $query_result['pointsspeed'] . '"}
        }';
    exit(0);
}

// Retrieve a JSON object with crashes data
function send_crash_dates($query_result) {
    $response_str = 
    '{
        "error" : false, 
        "crashdates": [';

    for($i = 0; $i < mysqli_num_rows($query_result); $i++) {
        $row = $query_result->fetch_array();
        $response_str = $response_str . '"' . $row[0] . '",';
    }
        
    $response_str = substr($response_str, 0, -1);
    $response_str = $response_str . ']}';

    echo $response_str;
    exit(0);
}

// Retrieve a JSON object with crashes data
function send_crash_infos($query_result) {
    $response_str = 
    '{
        "error" : false, 
        "crashinfos": [';

    for($i = 0; $i < mysqli_num_rows($query_result); $i++) {
        $row = $query_result->fetch_array();
        $response_str = $response_str .
            '{
                "number" : ' . ($i+1) . ',
                "crashtime" : "' . $row['crashtime'] . '",
                "intensity" : "' . $row['intensity'] . '",
                "stationary" : "' . $row['stationary'] . '"
            },';
    }
        
    $response_str = substr($response_str, 0, -1);
    $response_str = $response_str . ']}';

    echo $response_str;
    exit(0);
}

// Retrieve a JSON object with an error message
function launch_error($message) {
    echo '{ "error" : true, "message" : "' . $message . '" }';
    die(-1);
}

// Retrieve a JSON object with a success message
function launch_response($message) {
    echo '{ "error" : false, "message" : "' . $message .'" }';
    exit(0);
}

?>