program Project;

{$R *.res}

Var s : String[40];
Var wstart, wend, i : Word;
Var wmaxlen, wmaxstart : Word;

begin
  WriteLn('Enter string: ');
  ReadLn(s);

  WriteLn('String:');
  WriteLn(s);

  i := 1;
  wmaxlen := 0; wmaxstart := 1;
  while s[i] <> '.' do begin
    while s[i] = ' ' do i := i + 1;
    wstart := i;
    while (s[i] <> ' ') and (s[i] <> '.') do i := i + 1;
    wend := i;

    if (wend - wstart) > wmaxlen then begin
      wmaxstart := wstart;
      wmaxlen := wend - wstart;
    end;
  end;

  WriteLn('Word: ', Copy(s, wmaxstart, wmaxlen));
  WriteLn('length: ', wmaxlen);

  Delete(s, wmaxstart, wmaxlen);
  WriteLn('Corrected string:');
  WriteLn(s);

end.
