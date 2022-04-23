// Elements
var slider = document.getElementById("range");
var output = document.getElementById("output");
var selectedIndex = 0;
let list = [
    "Wipes color from end to end.",
    "Rainbow colors that slowly cycle across LEDs.",
    "Theater-style crawling lights with rainbow effect.",
    "Display alternating stripes.",
    "Sliding bar across LEDs.",
]

// Display the default slider value
output.innerHTML = slider.value;

// Update the current slider value (each time you drag the slider handle)
slider.oninput = function () {
    output.innerHTML = this.value;
}

// Update footer text describing LED pattern based off button pressed
function changeText(button) {
    var x = button.id;
    switch (x) {
        case '1':
            document.getElementById("text").innerHTML = list[x - 1];
            selectedIndex = 0;
            break;
        case '2':
            document.getElementById("text").innerHTML = list[x - 1];
            selectedIndex = 1;
            break;
        case '3':
            document.getElementById("text").innerHTML = list[x - 1];
            selectedIndex = 2;
            break;
        case '4':
            document.getElementById("text").innerHTML = list[x - 1];
            selectedIndex = 3;
            break;
        case '5':
            document.getElementById("text").innerHTML = list[x - 1];
            selectedIndex = 4;
            break;
        default:
            break;
    }
}


// Send selected index to arduino via BLE module
function changeLED() {
}