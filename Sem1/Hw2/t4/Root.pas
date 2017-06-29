Unit Root;

Interface
    Type MType = Extended;
    Type func = function (x: MType) : MType;
    Function froot(f: func; a, b : MType; const e : MType) : MType;

Implementation
    Function froot(f: func; a, b : MType; const e : MType) : MType;
    Var dx, xi : MType;
    Begin
        repeat
            dx := b - a;
            xi := a + dx/2;
            if (f(a) > 0) = (f(xi) > 0) then
                a := xi
            else
                b := xi;
        until dx <= e;
        froot := xi;
    End;
End.