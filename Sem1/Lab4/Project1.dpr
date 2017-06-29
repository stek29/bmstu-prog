program Project1;
{$R *.res}

Const N = 3;

Var points : array[1..N] of Single;
Var i : Integer;
Var imax, imin : Integer;
Var pmax, pmin : Single;
Var diff : Single;

Begin
    WriteLn('Введите массив:');
    for i := 1 to N do 
        Read(points[i]);
    ReadLn;
    
    imax := 1; imin := 1;
    pmax := points[1]; pmin := points[1];
    
    for i := 2 to N do begin
        if (points[i] >  pmax) then begin
            pmax := points[i];
            imax := i;
        end;
        if (points[i] <= pmin) then begin
            pmin := points[i];
            imin := i;
        end;
    end;
    
    WriteLn('Массив:');
    for i := 1 to N do 
        Write(points[i], ' ');
    WriteLn;
    
    diff := pmax - pmin;
    WriteLn('Максимальное расстояние: ', diff);
    WriteLn('(Между ', imax, ' и ', imin, ' точками)');
    
    ReadLn;
End.

