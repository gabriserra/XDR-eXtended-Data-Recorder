// -------------------------
// MAIN.JS
// It contains main js function
// -----------------------

$(document).ready(function(){
    toggleTooltip();
});

// toggle on boostrap tooltip
function toggleTooltip() {
    $('[data-toggle="tooltip"]').tooltip(); 
}
