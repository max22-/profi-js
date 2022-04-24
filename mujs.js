var inputs = ["I1", "I2", "I3"];
var outputs = ["O1", "O2", "O7"];

function CConfigure()
{
    alert("Hello");
    alert(PInput["I1"]);
    alert("End");
}

function CSimStart()
{
    alert("SimStart");
    var PInput = {}
    inputs.forEach(function(i) {
        PInput[i] = pinput(i);
    });
    SimStart(PInput);
}

function SimStart(PInput)
{
    alert(PInput["I1"]);
}