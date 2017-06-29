Program lab5;

Const ALL_CHARS_LEN = 6;
Const ALL_CHARS : array [0..(ALL_CHARS_LEN-1)] of Char = ('%', '*', '$', '@', '+', 'O'); 


Const Nn = 10; 
Var mat : Array [1..nn, 1..nn] of Char; 


Var n, i, j : Integer;

Begin 
    Write('Enter N: '); ReadLn(n);
    Randomize; 
    for i := 1 to n do 
        for j := 1 to n do
            mat[i,j] := ALL_CHARS[random(ALL_CHARS_LEN)];
    
    WriteLn('Original');
    for i := 1 to n do begin 
        for j := 1 to n do
            write(mat[i,j]:2);
        writeln;
    end;
    
    WriteLn('Rotated');
    for i := n downto 1 do begin
        for j := n downto 1 do
            write(mat[i,j]:2);
        writeln;
    end;
    
    ReadLn;
End.


