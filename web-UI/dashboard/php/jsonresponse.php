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