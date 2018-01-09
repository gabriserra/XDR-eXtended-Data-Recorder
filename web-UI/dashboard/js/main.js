// -------------------------
// MAIN.JS
// It contains main js function
// -----------------------

get_user_data();

$(document).ready(function(){
    toggle_tooltip();
    get_lasttrip_data();
    gauge_build();
});

// -------------------------------------
// REDIRECT USER FUNCTION
// -------------------------------------

// Change navbar link if already logged in
function get_user_data() {
    ajax_req(
        "php/redirect.php", 
        "",     
        get_succ, 
        get_err
    );
}

// Action done in case of success
function get_succ(reply) {
    if (reply.error == false)
        prepare_page(reply.message);
    //else
        //window.location.replace("http://localhost/XDR/web-UI/frontend/");
}

// Action done in case of failure
function get_err() {
    alert("Server unreachable.");
    window.location.replace("http://localhost/XDR/web-UI/frontend/");
    // maybe something more in future...
}

// prepare page with custom user data
function prepare_page(userdata) {
    $('.nav-user-a').attr("title", userdata.username + " - Logout");
    $('.nav-avatar').attr("src", "img/uploads/" + userdata.avatar);
    $('.card-avatar').attr("src", "img/uploads/" + userdata.avatar);
    $('.cover-img').css('background-image', 'url( img/uploads/' + userdata.cover + ')');
    $('.card-name').html(userdata.name + " " + userdata.surname);
    $('.card-text').html(userdata.bio);
}

// -------------------------------------
// GET LAST TRIP DATA
// -------------------------------------

// Change navbar link if already logged in
function get_lasttrip_data() {
    ajax_req(
        "php/gethome.php", 
        "",     
        get_lasttrip_succ, 
        get_lasttrip_err
    );
}

// Action done in case of success
function get_lasttrip_succ(reply) {
    if (reply.error == false)
        prepare_page(reply.message);
    //else
        //window.location.replace("http://localhost/XDR/web-UI/frontend/");
}

// Action done in case of failure
function get_lasttrip_err() {
    alert("Server unreachable.");
    window.location.replace("http://localhost/XDR/web-UI/frontend/");
    // maybe something more in future...
}

// -------------------------------------
// GAUGE OPTIONS
// -------------------------------------

var opts = {
    angle: -0.1, // The span of the gauge arc
    lineWidth: 0.2, // The line thickness
    radiusScale: 1, // Relative radius
    pointer: {
      length: 0.5, // // Relative to gauge radius
      strokeWidth: 0.035, // The thickness
      color: '#000000' // Fill color
    },
    minValue: 0,
    limitMax: false,     // If false, max value increases automatically if value > maxValue
    limitMin: true,     // If true, the min value of the gauge will be fixed
    colorStart: '#6FADCF',   // Colors
    colorStop: '#8FC0DA',    // just experiment with them
    strokeColor: '#E0E0E0',  // to see which ones work best for you
    generateGradient: true,
    highDpiSupport: true,     // High resolution support
    percentColors: [[0.0, "#a9d70b" ], [0.50, "#f9c802"], [1.0, "#ff0000"]]
  };

// -------------------------------------
// GAUGES BUILD
// -------------------------------------

function gauge_build() {    
    var gauge_tot = new Gauge(document.getElementById("gauge-total")).setOptions(opts);
    var gauge_acc = new Gauge(document.getElementById("gauge-acc")).setOptions(opts);
    var gauge_bra = new Gauge(document.getElementById("gauge-bra")).setOptions(opts);
    var gauge_ste = new Gauge(document.getElementById("gauge-ste")).setOptions(opts);
    var gauge_ovr = new Gauge(document.getElementById("gauge-ovr")).setOptions(opts);
    gauge_tot.setTextField(document.getElementById("textfield-tot"));
    gauge_acc.setTextField(document.getElementById("textfield-acc"));
    gauge_bra.setTextField(document.getElementById("textfield-bra"));
    gauge_ste.setTextField(document.getElementById("textfield-ste"));
    gauge_ovr.setTextField(document.getElementById("textfield-ovr"));
    gauge_tot.maxValue = 100;
    gauge_tot.set(50);
    gauge_bra.set(50);
    gauge_acc.set(50);
    gauge_ste.set(50);
    gauge_ovr.set(50);
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

// toggle on boostrap tooltip
function toggle_tooltip() {
    $('[data-toggle="tooltip"]').tooltip(); 
}