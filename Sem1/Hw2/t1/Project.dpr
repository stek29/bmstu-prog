program Project;
{$R *.res}

Const N = 5;
Var a : array[1..N] of Real;
Var tmp : Real;
Var i, j,k : Byte;

Begin
  WriteLn('Enter array: (5)');
  for i := 1 to n do read(a[i]);
  for i := 1 to n do Write(a[i]:7:1);
  WriteLn;

  for i := 2 to n do begin
    tmp := a[i];
    j := i - 1;
    while (j > 0) and (abs(a[j]) > abs(tmp)) do begin
      a[j + 1] := a[j];
      j := j - 1;
    end;
    a[j + 1] := tmp;
  end;

  WriteLn('Sorted array:');
  for i := 1 to n do Write(a[i]:7:2);
  WriteLn;
End.
