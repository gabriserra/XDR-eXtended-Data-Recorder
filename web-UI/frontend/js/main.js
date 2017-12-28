// -------------------------
// MAIN.JS
// It contains main js function
// -----------------------

$(document).ready(function(){
    redirect_if_logged();
    toggle_tooltip();
    $("#form-login").vindicate("init");
    $("#form-signup").vindicate("init");
});

// -------------------------------------
// REDIRECT USER FUNCTION
// -------------------------------------

// Redirect user to dashboard if already logged i
function redirect_if_logged() {
    ajax_req(
        "php/redirect.php", 
        "",     
        redirect_succ, 
        redirect_err
    );
}

// Action done in case of success
function redirect_succ(reply) {
    if (reply.error == false)
        window.location.replace("http://localhost/XDR/web-UI/dashboard/");
}

// Action done in case of failure
function redirect_err() {
    // maybe something in future...
}

// -------------------------------------
// SUBMIT LOGIN FORM SUCCESS
// -------------------------------------

// Submit validation form login
function submit_login() {
    $("#form-login").vindicate("validate");

    ajax_req(
        "php/login.php", 
        $("#form-login").serialize(),     
        login_succ, 
        login_err
    );
}

// Action done in case of success
function login_succ(reply) {
    if (reply.error == false) {
        window.location.replace("http://localhost/XDR/web-UI/dashboard/");
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
    
    ajax_req(
        "php/signup.php", 
        $("#form-signup").serialize(),     
        signup_succ, 
        signup_err
    );
}

// Action done in case of success
function signup_succ(reply) {
    if (reply.error == false) {
        alert(reply.message);
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
        data: info,
        dataType: "json",
        success: succ,
        error: err
    });
}

// Toggle on boostrap tooltip
function toggle_tooltip() {
    $('[data-toggle="tooltip"]').tooltip(); 
}

function show_alert(htmlclass) {
    $(htmlclass).removeClass("d-none");
    $(htmlclass).addClass("show");
}