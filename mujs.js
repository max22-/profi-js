var inputs = ["I1", "I2", "I3"];
var outputs = ["O1", "O2", "O7"];
var user = ["U1", "U2"];

function CConfigure(PUser)
{
    alert(PUser["U1"]);
}

function CSimStart(PInput, POutput, PUser)
{
}

function CCalculate(PInput, POutput, PUser)
{
//    alert(JSON.stringify([POutput["O1"], PInput["I1"], PInput["I2"]]));
    POutput["O1"] = PInput["I1"] + PInput["I2"];
}

function CSimStop(PInput, POutput, PUser)
{

}

