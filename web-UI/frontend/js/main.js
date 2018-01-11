// -------------------------
// MAIN.JS
// It contains main js function
// -----------------------

$(document).ready(function(){
    check_if_logged();
    $("#form-login").vindicate("init");
    $("#form-signup").vindicate("init");
});

// -------------------------------------
// CHECK USER FUNCTION
// -------------------------------------

// Change navbar link if already logged in
function check_if_logged() {
    ajax_req(
        php_redir,
        "",     
        check_succ, 
        check_err
    );
}

// Action done in case of success
function check_succ(reply) {
    console.log(reply);
    if (reply.error == false) {
        $("#btn-login").hide();
        $("#btn-signup").hide();
    } else {
        $("#btn-dashboard").hide();
    }
}

// Action done in case of failure
function check_err() {
    $("#btn-dashboard").hide();
}

// -------------------------------------
// SUBMIT LOGIN FORM SUCCESS
// -------------------------------------

// Submit validation form login
function submit_login() {
    $("#form-login").vindicate("validate");

    ajax_req(
        php_login,
        $("#form-login").serialize(),     
        login_succ, 
        login_err
    );
}

// Action done in case of success
function login_succ(reply) {
    console.log(reply);
    if (reply.error == false) {
        window.location.replace(rel_dash_path);
    } else {
        $(".login-error-title").html("Error: ");
        $(".login-error-text").html(reply.message);
        show_alert(".alert-login");
    }
}

// Action done in case of failure
function login_err() {
    $(".login-error-title").html("Error: ");
    $(".login-error-text").html("server unreachable.");
    show_alert(".alert-login");
}

// -------------------------------------
// SUBMIT SIGNUP FORM SUCCESS
// -------------------------------------

// Submit validation form sign up
function submit_signup() {
    $("#form-signup").vindicate("validate");
    data = new FormData(document.getElementById('form-signup'));

    ajax_req_file(
        php_signup,
        data,     
        signup_succ, 
        signup_err
    );
}

// Action done in case of success
function signup_succ(reply) {
    if (reply.error == false) {
        $(".signup-success-title").html("Success: ");
        $(".signup-success-text").html(reply.message);
        show_alert(".alert-signup-succ");
        $("#form-signup :input").prop('disabled', true);
        $(".btn-secondary").prop('disabled', false);
    } else {
        $(".signup-error-title").html("Error: ");
        $(".signup-error-text").html(reply.message);
        show_alert(".alert-signup");
    }
}

// Action done in case of failure
function signup_err() {
    $(".signup-error-title").html("Error: ");
    $(".signup-error-text").html("server unreachable.");
    show_alert(".alert-signup");
}

// -------------------------------------
// UTILITY
// -------------------------------------

function ajax_req(dest, info, succ, err) {
    $.ajax({
        type: "POST",
        url: dest,
        xhrFields: { withCredentials: true },
        data: info,
        dataType: "json",
        success: succ,
        error: err
    });
}

function ajax_req_file(dest, info, succ, err) {
    $.ajax({
        type: "POST",
        url: dest,
        xhrFields: { withCredentials: true },
        data: info,
        dataType: "json",
        processData: false,
        contentType: false,
        success: succ,
        error: err
    });
}

function show_alert(htmlclass) {
    $(htmlclass).removeClass("d-none");
    $(htmlclass).addClass("show");
}