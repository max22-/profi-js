function NumInputs()
{
    return inputs.length;
}

function NumOutputs()
{
    return outputs.length;
}

function GetInputName(c)
{
    return inputs[c];
}

function GetOutputName(c)
{
    return outputs[c];
}

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

