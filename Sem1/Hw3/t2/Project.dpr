program Project;
{$R *.res}

Type TCircle = object
  r: Single;
  x, y: Real;

  procedure init(r_: Single; x_, y_: Real);
  procedure print;
  function area: Real;
end;

procedure TCircle.init(r_: Single; x_: Real; y_: Real);
begin
  Self.r := r_;
  Self.x := x_;
  Self.y := y_;
end;

procedure TCircle.print;
begin
  WriteLn('[TCircle'+
    ' x:[', Self.x:5:2,']'+
    ' y:[', Self.y:5:2,']'+
    ' r:[', Self.r:5:2,']'+
    ']'
  );
end;

function TCircle.area;
begin
  area := Pi * Self.r * Self.r;
end;

Type TBall = object(TCircle)
  z: Real;
  procedure newInit(r_: Single; x_, y_, z_: Real);
  procedure newPrint;
  function volume: Real;
end;

procedure TBall.newInit(r_: Single; x_: Real; y_: Real; z_: Real);
begin
  Self.init(r_, x_, y_);
  Self.z := z_;
end;

procedure TBall.newPrint;
begin
  WriteLn('[TBall'+
    ' x:[', Self.x:5:2,']'+
    ' y:[', Self.y:5:2,']'+
    ' z:[', Self.z:5:2,']'+
    ' r:[', Self.r:5:2,']'+
    ']'
  );
end;

function TBall.volume;
begin
  volume := Self.area * Self.r * 4/3;
end;

Var Circle: TCircle;
Var Ball: TBall;
begin
  WriteLn('TCircle(5, 0, 0)');
  Circle.init(5, 0, 0);
  Circle.print;
  WriteLn('Area: ', Circle.area:9:4);
  WriteLn('TBall(6, 0, 2, -3)');
  Ball.newInit(6, 0, 2, -3);
  Ball.newPrint;
  WriteLn('Volume: ', Ball.volume:9:4);
  ReadLn;
end.
