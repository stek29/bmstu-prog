program Project;
{$R *.res}

Type TRoom = Object
    procedure init(area, price: Single);
    procedure print;
    function pricePerMeter : Single;
    private _area, _price : Single;
  end;

procedure TRoom.init(area : Single; price: Single);
begin
  Self._area := area;
  Self._price := price;
end;

procedure TRoom.print;
begin
  WriteLn('[TRoom area:[', Self._area:5:1, '] price:[', Self._price:7:2, ']]');
end;

function TRoom.pricePerMeter;
begin
  pricePerMeter := Self._price / Self._area;
end;

Var room : TRoom;
begin
  room.init(30.5, 3000);
  WriteLn('Inited with area=30.5 and price=3000');
  room.print;
  WriteLn('Price per Meter: ', room.pricePerMeter():9:4);

  room.init(50, 9999.99);
  WriteLn('Inited with area=50 and price=9999.99');
  room.print;
  WriteLn('Price per Meter: ', room.pricePerMeter():9:4);

  ReadLn;
end.
