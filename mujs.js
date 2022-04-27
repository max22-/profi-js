var inputs = ["CLK", "RST"];
var outputs = ["Q0", "Q1", "Q2", "Q3", "Q4", "Q5", "Q6", "Q7", "ABS"];
var user = ["CLK_OLD", "RST_OLD", "COUNT"];

function CConfigure()
{
    alert("Rien à configurer");
}

function CSimStart()
{
    PUser_set("COUNT", 0);
    outputs.forEach(function(i) { POutput(i, 0) });
}

function CCalculate()
{
    if(PInput("RST") < 2.5 && PUser_get("RST_OLD") > 2.5) {
        PUser.set("COUNT", 0);
        outputs.forEach(function (o) { POutput(o, 0) });
    }

    PUser_set("RST_OLD", PInput("RST"));

    if(PInput("CLK") > 2.5 && PUser_get("CLK_OLD") < 2.5) {
        var count = PUser_get("COUNT");
        count = (count + 1) % 256;
        PUser_set("COUNT", count);
        POutput("ABS", count);
        for(var i = 0; i < 8; i++) {
            POutput("Q" + i, (count & (1<< i)) != 0 ? 5 : 0);
        }
    }
    PUser_set("CLK_OLD", PInput("CLK"));
}

function CSimStop()
{

}

