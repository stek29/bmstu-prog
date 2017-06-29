program Project;
{$R *.res}

Const contain = [2, 6, 3]; ncontain = [1, 7, 9];
Var count : Integer;
Var number : Int64;
Var tmpnum : Int64;
Var contains : Boolean;
Var i, n : Byte;

begin
  {Write('Numbers to read: '); }ReadLn(n);

  count := 0;
  for i := 1 to n do begin
    ReadLn(number);
    tmpnum := number;
    contains := false;
    while (tmpnum <> 0) and not ((tmpnum mod 10) in ncontain) do begin
      tmpnum := tmpnum div 10;
      contains := contains or ((tmpnum mod 10) in contain);
    end;
    if (tmpnum = 0) and contains then begin
      WriteLn(number);
      count := count + 1;
    end;
  end;

  WriteLn('Count: ', count);
end.
