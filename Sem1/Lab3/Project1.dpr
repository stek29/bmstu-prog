program Project1;
{$R *.res}

Var f1, f2, t, i : Integer;

begin
  f1 := -9;
  f2 := -9;
  i := 2;
  repeat
    t:=f1;
    f1:=f2;
    f2:=f2+t+12;
    Inc(i);
  until f2>0;
  WriteLn('#', i, ': ', f2);
  ReadLn;
End.

