var inputs = ["CLK", "RST"];
var outputs = ["Q0", "Q1", "Q2", "Q3", "Q4", "Q5", "Q6", "Q7", "ABS"];
var user = ["CLK_OLD", "RST_OLD", "COUNT"];

function CConfigure(PUser)
{
    alert("Rien à configurer");
}

function CSimStart(PInput, POutput, PUser)
{
    PUser.COUNT = 0;
    outputs.forEach(function(i) { POutput[i] = 0 });
}

function CCalculate(PInput, POutput, PUser)
{
    if(PInput.RST < 2.5 && PUser.RST_OLD > 2.5) {
        PUser.COUNT = 0;
        outputs.forEach(function (o) { POutput[o] = 0 });
    }

    PUser.RST_OLD = PInput.RST;

    if(PInput.CLK > 2.5 && PUser.CLK_OLD < 2.5) {
        var count = PUser.COUNT;
        count = (count + 1) % 256;
        PUser.COUNT = count;
        POutput.ABS = count;
        var bin = "bin: ";
        for(var i = 0; i < 8; i++) {
            POutput["Q" + i] = (count & (1<< i)) != 0 ? 5 : 0;
           bin += (count & (1<< i)) != 0 ? "1" : "0";
        }
        alert(bin);
    }
    PUser.CLK_OLD = PInput.CLK;
}

function CSimStop(PInput, POutput, PUser)
{

}

