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

function PInput(name) 
{
    var n = inputs.indexOf(name);
    if(n == -1) {
        alert("Input " + name + " doesn't exist");
        return 0;
    }
    else return pinput(n);
}

function POutput(name, val)
{
    var n = outputs.indexOf(name);
    if(n == -1) {
        alert("Output " + name + "doesn't exist");
        return;
    }
    else poutput(n, val);
}

function PUser_get(name)
{
    var n = user.indexOf(name);
    if(n == -1) {
        alert("User variable " + name + " doesn't exist");
        return 0;
    }
    else return puser_get(n);
}

function PUser_set(name, val)
{
    var n = user.indexOf(name);
    if(n == -1) {
        alert("User variable " + name + "doesn't exist");
        return;
    }
    else puser_set(n, val);
}
