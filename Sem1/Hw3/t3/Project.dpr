program Project;
{$R *.res}

Type TTruck = object
  capacity: Integer;
  costPkm: Single;

  procedure init(cap: Integer; cost: Single);
  procedure print;
  function costPton: Real;
end;

procedure TTruck.init(cap: Integer; cost: Single);
begin
  Self.capacity := cap;
  Self.costPkm := cost;
end;

procedure TTruck.print;
begin
  WriteLn('[TTruck'+
    ' capacity:[', Self.capacity, ']'+
    ' costPkm:[', Self.costPkm:7:2, ']'+
  ']');
end;

function TTruck.costPton;
begin
  costPton := Self.costPkm / capacity;
end;

Const Nmax = 100;
Type TTruckPark = object
  number: Byte;
  arr: array[1..Nmax] of TTruck;

  procedure init(n: byte; const m: array of TTruck);
  procedure print;
  function mostEffectiveIndex: Byte;
end;

procedure TTruckPark.init(n: Byte; const m: array of TTruck);
Var i: Byte;
begin
  Self.number := n;
  for i := 0 to (n-1) do
    arr[i+1].init(m[i].capacity, m[i].costPkm);
end;

procedure TTruckPark.print;
Var i: Byte;
begin
  WriteLn('[TTruckPark number:[', Self.number, ']' + 'arr:[');
  for i := 1 to Self.number do begin
    Write('  ');
    Self.arr[i].print;
  end;
  WriteLn(']]');
end;

function TTruckPark.mostEffectiveIndex;
Var curcost, mincost: Real;
Var i, minind: Byte;
begin
  if Self.number <> 0 then begin
    minind := 1; mincost := Self.arr[1].costPton;
    for i := 2 to Self.number do begin
      curcost := Self.arr[i].costPton;
      if curcost < mincost then begin
        mincost := curcost;
        minind := i;
      end;
    end
  end else minind := 0;
  mostEffectiveIndex := minind;
end;

Var a: TTruckPark;
Var mas: array[1..5] of TTruck;
Var metind: Byte;
Begin
  mas[1].init(3, 10);
  mas[2].init(4, 11.1);
  mas[3].init(2, 4);
  mas[4].init(1, 10);
  mas[5].init(9, 3);
  a.init(5, mas);
  a.print;
  metind := a.mostEffectiveIndex;
  WriteLn('MET: Truck#', metind);
  a.arr[metind].print;
  ReadLn;
End.
