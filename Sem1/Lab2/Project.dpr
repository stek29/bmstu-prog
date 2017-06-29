Program lab2;

Var x, y : real;
Var belongs : boolean = false;
Begin
    Write('x, y: ');
    ReadLn(x, y); 
    if (x >= -1) and (x <= 0) and (y >= 0) and (y <= 1) then
        if y <= x + 1 then 
            if y <= sqrt(1 - sqr(x + 1)) then
                belongs := true;
    
    if belongs then
        WriteLn('Принадлежит')
    else
        WriteLn('Не принадлежит');
End.

