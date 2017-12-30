// -------------------------
// MAIN.JS
// It contains main js function
// -----------------------

get_user_data();

$(document).ready(function(){
    toggle_tooltip();
    homeChartDraw();
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
    else
        window.location.replace("http://localhost/XDR/web-UI/frontend/");
}

// Action done in case of failure
function get_err() {
    alert("Server unreachable.");
    window.location.replace("http://localhost/XDR/web-UI/frontend/");
    // maybe something more in future...
}

// toggle on boostrap tooltip
function toggle_tooltip() {
    $('[data-toggle="tooltip"]').tooltip(); 
}

function prepare_page(userdata) {
    $('.nav-user-a').attr("title", "Signed in: " + userdata.username);
    $('.nav-avatar').attr("src", "img/uploads/" + userdata.avatar);
    $('.card-avatar').attr("src", "img/uploads/" + userdata.avatar);
    $('.cover-img').css('background-image', 'url( img/uploads/' + userdata.cover + ')');
    $('.card-name').html(userdata.name + " " + userdata.surname);
    $('.card-text').html(userdata.bio);
}

// draw home chart
function homeChartDraw() {
    var chart = new CanvasJS.Chart("chart-container", {
        animationEnabled: true,
        axisX: {
            valueFormatString: "DDD",
            titleFontFamily: "Roboto",
            minimum: new Date(2017, 1, 5, 23),
            maximum: new Date(2017, 1, 12, 1)
        },
        axisY: {
            gridThickness: 0,
            tickLength: 0,
            margin: 0,
            lineThickness: 0,
            valueFormatString: " "
        },
        legend: {
            fontFamily: "Roboto",
            verticalAlign: "top",
            horizontalAlign: "right",
            dockInsidePlotArea: true
        },
        toolTip: {
            shared: true
        },
        data: [{
            name: "Overall",
            legendMarkerType: "square",
            type: "area",
            color: "rgba(40,175,101,0.6)",
            markerSize: 0,
            dataPoints: [
                { x: new Date(2017, 1, 6), y: 220 },
                { x: new Date(2017, 1, 7), y: 120 },
                { x: new Date(2017, 1, 8), y: 144 },
                { x: new Date(2017, 1, 9), y: 162 },
                { x: new Date(2017, 1, 10), y: 129 },
                { x: new Date(2017, 1, 11), y: 109 },
                { x: new Date(2017, 1, 12), y: 129 }
            ]
        },
        {
            name: "Kilometers driven",
            legendMarkerType: "square",
            type: "area",
            color: "rgba(0,75,141,0.7)",
            markerSize: 0,
            dataPoints: [
                { x: new Date(2017, 1, 6), y: 42 },
                { x: new Date(2017, 1, 7), y: 34 },
                { x: new Date(2017, 1, 8), y: 29 },
                { x: new Date(2017, 1, 9), y: 42 },
                { x: new Date(2017, 1, 10), y: 53},
                { x: new Date(2017, 1, 11), y: 15 },
                { x: new Date(2017, 1, 12), y: 12 }
            ]
        }]
    });
    chart.render();
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
