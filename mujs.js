var inputs = ["I1", "I2", "I3"];
var outputs = ["O1", "O2", "O7"];
var user = ["U1", "U2"];

function _gen_PInput()
{
    var PInput = {};
    for(var i = 0; i < inputs.length; i++)
        PInput[inputs[i]] = pinput(i);
    return PInput;
}

function _gen_POutput()
{
    var POutput = {};
    for(var i = 0; i < outputs.length; i++)
        POutput[outputs[i]] = 0;

    return POutput;
}

function _gen_PUser()
{
    var PUser = {};
    for(var i = 0; i < user.length; i++)
        PUser[user[i]] = puser_get(i);
    return PUser;
}

function _write_POutput(POutput)
{
    for(var i = 0; i < outputs.length; i++)
        poutput(i, POutput[outputs[i]]);
}

function _write_PUser(PUser)
{
    for(var i = 0; i < user.length; i++)
        puser_set(i, PUser[user[i]]);
}

function _CConfigure()
{
    var PUser = _gen_PUser();
    CConfigure(PUser);
    _write_PUser(PUser);
}

function _CSimStart()
{
    var PInput = _gen_PInput();
    var POutput = _gen_POutput();
    var PUser = _gen_PUser();
    CSimStart(PInput, POutput, PUser);
    _write_POutput(POutput);
    _write_PUser(PUser);
}

function _CCalculate()
{
    var PInput = _gen_PInput();
    var POutput = _gen_POutput();
    var PUser = _gen_PUser();
    CCalculate(PInput, POutput, PUser);
    _write_POutput(POutput);
    _write_PUser(PUser);
}

function _CSimStop()
{
    var PInput = _gen_PInput();
    var POutput = _gen_POutput();
    var PUser = _gen_PUser();
    CSimStop(PInput, POutput, PUser);
    _write_POutput(POutput);
    _write_PUser(PUser);
}




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

