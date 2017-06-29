program Project;
{$R *.res}

Type NodePtr = ^Node;
  Node = record
    val : Real;
    next : NodePtr;
  end;

Var first : NodePtr;
Var p, q : NodePtr;
Var s : String;
Var code : Integer;

Begin
  first := nil; p := nil;
  WriteLn('Enter numbers (empty to stop): ');
  ReadLn(s);
  while Length(s) > 0 do begin
    New(q);
    Val(s, q^.val, code);

    q^.next := nil;
    if (first = nil) then first := q
    else p^.next := q;
    p := q;
    ReadLn(s);
  end;

  Write('Neg: ');
  q := first;
  while q <> nil do begin
    if q^.val < 0 then Write(q^.val:6:2);
    q := q^.next;
  end;
  WriteLn;

  Write('Not: ');
  while first <> nil do begin
    if first^.val >= 0 then Write(first^.val:6:2);
    q := first^.next;
    Dispose(first);
    first := q;
  end;
  WriteLn;
End.
