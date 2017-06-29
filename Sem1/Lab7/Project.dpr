program Project;
{$R *.res}

Function isPrime(num: Integer) : Boolean;
Var i : Integer;
Var f : Boolean;
Begin
  f := true;
  for i := 2 to (num div 2) do
    if ((num mod i) = 0) then
      f := false;
  isprime := f;
End;

Var i, n : Integer;
Var ans : Integer;

begin
  ans := 0;
  Write('N: '); ReadLn(n);

  for i := 1 to (n div 2) do
    if isprime(i) and isprime(N-i) then
      ans := i;

  if ans <> 0 then
    WriteLn(ans, ' + ', n - ans)
  else
    WriteLn('Wrong');
  ReadLn;
end.
