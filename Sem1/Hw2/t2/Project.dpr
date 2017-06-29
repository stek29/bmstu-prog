program Project;
{$R *.res}

Const N = 8;

Var a : Array [1..N, 1..N] of Integer;
Var i, j : Byte;
Var found : Boolean;
Var minEl : Integer;
Var product : Real;

begin
  Randomize;
  WriteLn('Matrix: ');
  for i := 1 to N do begin
    for j := 1 to i do begin
      a[i, j] := random(5) - random(10);
      Write(a[i, j]:3);
    end;
    for j := (i + 1) to N do begin
      a[i, j] := random(7) - random(10);
      Write(a[i, j]:3);
    end;
    WriteLn;
  end;

  minEl := a[1, N];
  for i := 1 to N do
    for j := (i + 1) to N do
      if a[i, j] < minEl then
        minEl := a[i, j];

  product := 1; found := false;
  Write('Elements: ');
  for i := 1 to N do
    for j := 1 to (i - 1) do
      if a[i, j] < minEl then begin
        Write(a[i, j]:3);
        product := product * a[i, j];
        if not found then found := true;
      end;

  if found then begin
    WriteLn; WriteLn('Product: ', product:10:0);
  end else
    WriteLn('None');
end.
