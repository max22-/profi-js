var inputs = ["I1", "I2", "I3"];
var outputs = ["O1", "O2", "O7"];

function _CConfigure()
{
    alert("Hello");
    alert(PInput["I1"]);
    alert("End");
}

function _CSimStart()
{
    alert("SimStart");
    var PInput = {}
    inputs.forEach(function(i) {
        PInput[i] = pinput(i);
    });
    SimStart(PInput);
}


function CConfigure(PUser)
{

}

function CSimStart(PInput, POutput, PUser)
{
    alert(PInput["I1"]);
}

function CCalculate(PInput, POutput, PUser)
{
    
}

function CSimStop(PInput, POutput, PUser)
{

}

