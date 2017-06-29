program Project;
{$R *.res}

Uses Root;

function f1(x: Root.MType) : Root.MType;
Begin
  f1 := x*x + sin(x/2) - 1;
End;

function f2(x: Root.MType) : Root.MType;
Begin
  f2 := arctan(x) + x - 1;
End;

Const eps = 0.001;
Const a = 0;
Const b = 10;

begin
  Write('x^2 + sin(x/2) = 1 : ');
  WriteLn(Root.froot(f1, a, b, eps):5:3);

  Write('arctg(x) + x = 1 : ');
  WriteLn(Root.froot(f2, a, b, eps):5:3);
end.
