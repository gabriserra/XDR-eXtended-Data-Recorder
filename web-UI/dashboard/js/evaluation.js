// -------------------------
// EVALUATION.JS
// It contains all js code to
// fill up evaluation page
// -----------------------

const MAX_CRASH_PER_PAGE = 4;
const CAL_FIRST_DAY = 0;
const CAL_LAST_DAY = 41;

get_user_data();

$(document).ready(function(){
    toggle_tooltip();
    homeChartDraw();
});

// -------------------------------------
// REDIRECT USER FUNCTION
// -------------------------------------

// AJAX-REQ
// Change navbar link if already logged in
function get_user_data() {
    ajax_req(
        "php/redirect.php", 
        "",     
        get_succ, 
        get_err
    );
}

// AJAX-REP
// Action done in case of success
function get_succ(reply) {
    if (reply.error == false)
        prepare_page(reply.message);
    //else
        //window.location.replace("http://localhost/XDR/web-UI/frontend/");
}

// AJAX-ERR
// Action done in case of failure
function get_err() {
    alert("Server unreachable.");
    window.location.replace("http://localhost/XDR/web-UI/frontend/");
    // maybe something more in future...
}

// Build page with user data
function prepare_page(userdata) {
    $('.nav-user-a').attr("title", userdata.username + " - Logout");
    $('.nav-avatar').attr("src", "img/uploads/" + userdata.avatar);
}

// -----------------------------
// DATE PICKER BUILDER FUNCTION
// -----------------------------

// build the datepicker
function datepicker_build() {
    $('#datetimepicker').datetimepicker({
        format: 'DD/MM/YYYY',
        inline: true
    });
}

// -----------------------------
// DATE PICKER AJAX FUNCTION
// -----------------------------

// AJAX-REQ
// register event function
function datepickerview_event_register() {
    $('#datetimepicker').on('dp.update', function(e){
        if(e.change == 'M' || e.change == null) {
            var initdata = $('.datepicker-days tbody td').eq(CAL_FIRST_DAY).attr("data-day");
            var lastdata = $('.datepicker-days tbody td').eq(CAL_LAST_DAY).attr("data-day");
            var serialized = "init="+initdata+"&last="+lastdata;
            ajax_req("php/getcrash.php", serialized, datepicker_fill, datepicker_fill_error);
        }
    });
}

// trigger datepicker update event
function datepickerupdate_event_trigger() {
    $('#datetimepicker').trigger('dp.update');
}

// AJAX-REP
// fill with notify icon after user view change
function datepicker_fill(reply) {
    if(reply.error == true)
        alert(reply.message);
    else
        for(var i = 0; i < $('.datepicker-days tbody td').length; i++)
            if(reply.crashdates.includes($('.datepicker-days tbody td').eq(i).attr("data-day")))   
                $( ".datepicker-days tbody td" ).eq(i).addClass( "notify");
}

// AJAX-ERR
// alert with an error in case of server error
function datepicker_fill_error(reply) {
    alert("Unable to fill calendar - Server unrechable!");
}

// --------------------------
// CRASH TABLE AJAX FUNCTION
// --------------------------

// AJAX-REQ
// register event function
function datepickerchange_event_register() {
    $('#datetimepicker').on('dp.change', function(e){
        var date;

        if(e != null)
            date = moment(e.date).format('L');
        else
            date = moment();

        var serialized = "date="+date;
        ajax_req("php/getcrash.php", serialized, table_fill, table_fill_error);
        datepickerupdate_event_trigger();
    });
}

// trigger datepicker change event
function datepickerchange_event_trigger() {
    $('#datetimepicker').trigger('dp.change');
}

// AJAX-REP
// crash table fill
function table_fill(reply) {
    if(reply.error == true) {
        table_fill_empty();
        return;
    }
    
    pagination_reset();
    pagination_create(reply.crashinfos.length);
    table_reset();

    for(var i = 0; i < reply.crashinfos.length; i++) {
        $('.crash-table tbody').append(`
        <tr style="display: none;">
            <th>`+reply.crashinfos[i].number+`</th>
            <td>`+reply.crashinfos[i].crashtime+`</td>
            <td>`+reply.crashinfos[i].intensity+`</td>
            <td>`+Boolean(reply.crashinfos[i].stationary)+`</td>
        </tr>
        `);
    }

    show_rows(0);
}

// AJAX-ERR
// alert with an error in case of server error
function table_fill_error() {
    table_fill_empty();
    alert("Unable to fill table - Server unrechable!");
}

// --------------------------
// TABLE UTILITY FUNCTION
// --------------------------

// reset table content
function table_reset() {
    $('.crash-table tbody').html("");
}

// fill the table with empty row
function table_fill_empty() {
    pagination_reset();
    $('.crash-table tbody').html(`
        <tr>
            <th>-</th>
            <td>-</td>
            <td>-</td>
            <td>-</td>
        </tr>`);
}

// show only limited number of rows
function show_rows(init_number) {
    for(var i = 0; i < $('.crash-table tbody tr').length; i++) {
        if(i >= init_number && i < MAX_CRASH_PER_PAGE+init_number)
            $('.crash-table tbody tr').eq(i).css("display", "table-row");
        else
            $('.crash-table tbody tr').eq(i).css("display", "none");
    }
}

// ---------------------------
// PAGINATION UTILITY FUNCTION
// ----------------------------

// reset pagination to default one
function pagination_reset() {
    $('.pagination').html(`<li class="page-item active">
                                <a class="page-link" href="javascript:pagechange(1)">1</a>
                        </li>`);
}

// create button for pagination
function pagination_create(number) {
    if(number > MAX_CRASH_PER_PAGE) {
        for(var i = 0; i < (number % MAX_CRASH_PER_PAGE); i++) {
            $('.pagination').append(`
                <li class="page-item">
                    <a class="page-link" href="javascript:pagechange(`+(i+2)+`)">`+(i+2)+`</a>
                </li>
            `);
        }
    }
}

// display the selected page
function pagechange(pagenum) {
    $('.pagination li').removeClass("active");
    $('.pagination li').eq(pagenum-1).addClass("active");
    show_rows((pagenum-1) * MAX_CRASH_PER_PAGE);
}

// -------------------------------------
// GENERAL UTILITY
// -------------------------------------

// make an ajax req
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

// --------
// BUILD GAUGE
// --------------

// -------------------
// OPTION
// ----------------

var opts = {
    angle: -0.1, // The span of the gauge arc
    lineWidth: 0.2, // The line thickness
    radiusScale: 1, // Relative radius
    pointer: {
      length: 0.5, // // Relative to gauge radius
      strokeWidth: 0.035, // The thickness
      color: '#000000' // Fill color
    },
    limitMax: false,     // If false, max value increases automatically if value > maxValue
    limitMin: false,     // If true, the min value of the gauge will be fixed
    colorStart: '#6FADCF',   // Colors
    colorStop: '#8FC0DA',    // just experiment with them
    strokeColor: '#E0E0E0',  // to see which ones work best for you
    generateGradient: true,
    highDpiSupport: true,     // High resolution support
    percentColors: [[0.0, "#a9d70b" ], [0.50, "#f9c802"], [1.0, "#ff0000"]]
  };

  $(document).ready(function(){
    var target = document.getElementById('gauge-total'); // your canvas element
    var gauge = new Gauge(target).setOptions(opts); // create sexy gauge!
    gauge.maxValue = 100; // set max gauge value
    gauge.setTextField(document.getElementById("preview-textfield"));
    gauge.setMinValue(0);  // Prefer setter over gauge.minValue = 0
    gauge.animationSpeed = 32; // set animation speed (32 is default value)
    gauge.set(50); // set actual value
});

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