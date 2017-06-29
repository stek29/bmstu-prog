unit Main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, SimpleDB, Vcl.ExtCtrls, Vcl.Grids, DealType,
  System.Generics.Collections;

type CharSet = Set of Char;
  
type
  TFormMain = class(TForm)
    LabelProgName: TLabel;
    Panel1: TPanel;
    EditCountry: TLabeledEdit;
    EditProduct: TLabeledEdit;
    ButtonSelect: TButton;
    ButtonCntFromNam: TButton;
    ButtonPlot: TButton;
    Panel3: TPanel;
    Label1: TLabel;
    LabelLargestCnt: TLabel;
    ButtonFind: TButton;
    Grid: TStringGrid;
    ButtonReset: TButton;
    EditVolume: TLabeledEdit;
    EditYear: TLabeledEdit;
    ButtonAdd: TButton;
    ImagePlot: TImage;
    RadioImport: TRadioButton;
    RadioExport: TRadioButton;
    RadioAny: TRadioButton;
    GroupBox1: TGroupBox;
    ButtonDelete: TButton;
    procedure FormCreate(Sender: TObject);
    procedure ButtonSelectClick(Sender: TObject);
    procedure ButtonCntFromNamClick(Sender: TObject);
    procedure ButtonFindClick(Sender: TObject);
    procedure ButtonPlotClick(Sender: TObject);
    procedure ButtonAddClick(Sender: TObject);
    procedure ButtonResetClick(Sender: TObject);
    procedure FormResize(Sender: TObject);
    procedure ButtonDeleteClick(Sender: TObject);
    procedure GridDblClick(Sender: TObject);
  private
    DB: SimpleDBC;
    Volumes: Array[MIN_YEAR..MAX_YEAR] of Integer;  // Plot's cache
    function CheckEdit(Edit: TLabeledEdit; cs: CharSet): Boolean;
    procedure ResetEdits;
    procedure OutputReset;
    procedure AppendDeal(tDeal: DealT);
    function TryLoadDeal(Var tDeal: DealT; nofail: Boolean): Boolean;
    procedure Plot;
  end;
var
  FormMain: TFormMain;

implementation
{$R *.dfm}

procedure TFormMain.FormCreate(Sender: TObject);
begin
  DB := SimpleDBC.Create('ImportExport.db');

  OutputReset;
end;

procedure TFormMain.OutputReset;
Var i: Integer;
begin
  ImagePlot.Visible := False;
  ImagePlot.Picture.Assign(nil);

  Grid.Visible := False;
  Grid.RowCount := 1;

  Grid.Rows[0][0] := 'Наименование';
  Grid.Rows[0][1] := 'Объем';
  Grid.Rows[0][2] := 'Год';
  Grid.Rows[0][3] := 'Страна';
  Grid.Rows[0][4] := 'Направление';
end;

procedure TFormMain.ButtonFindClick(Sender: TObject);
Var Countries: TDictionary<String, Integer>;
Var tDeal: DealT;
Var maxVolume, volume: Integer;
Var maxCountry: String;
begin
  Countries := TDictionary<String, Integer>.Create;
  tDeal := nullDeal;
  tDeal.mask := MASK_EXPORT;
  DB.SelectSetup(tDeal);

  maxVolume := nullDeal.volume;
  maxCountry := nullDeal.country;

  while DB.SelectNext(tDeal) do begin
    if Countries.TryGetValue(tDeal.country, volume) then begin
      tDeal.volume := tDeal.volume + volume;
    end;
    Countries.AddOrSetValue(tDeal.country, tDeal.volume);
    if tDeal.volume > maxVolume then begin
      maxVolume := tDeal.volume;
      maxCountry := tDeal.country;
    end;
  end;

  LabelLargestCnt.Caption := maxCountry; //+ ' (' + IntToStr(maxVolume) + ')';

  Countries.Free;
end;

procedure TFormMain.ButtonCntFromNamClick(Sender: TObject);
Var tDeal: DealT;
Var index: Integer;
begin
  begin
    TryLoadDeal(tDeal, True);
    DB.SelectSetup(tDeal);
    OutputReset;
    Grid.Visible := True;

    while DB.SelectNext(tDeal) do begin
      index := Grid.Cols[3].IndexOf(tDeal.country);
      tDeal.year := nullDeal.year;
      if index = -1 then
        AppendDeal(tDeal)
      else begin
        tDeal.volume := tDeal.volume + StrToInt(Grid.Rows[index][1]);
        Grid.Rows[index][1] := IntToStr(tDeal.volume);
      end;
    end;
  end;
end;

procedure TFormMain.ButtonDeleteClick(Sender: TObject);
Var tDeal: DealT;
begin
  if TryLoadDeal(tDeal, False) then begin
    DB.SelectSetup(tDeal);
    if DB.DeleteNext(tDeal) then
      Grid.Rows[Grid.Row].Clear;
  end;
end;

procedure TFormMain.ButtonSelectClick(Sender: TObject);
Var VolumeSum: Integer;
Var tDeal: DealT;
begin
  TryLoadDeal(tDeal, True);
  DB.SelectSetup(tDeal);

  VolumeSum := 0;

  OutputReset;
  Grid.Visible := True;

  while DB.SelectNext(tDeal) do begin
    AppendDeal(tDeal);
    VolumeSum := VolumeSum + tDeal.volume;
  end;
  if Grid.RowCount > 1 then begin
    tDeal := nullDeal;
    tDeal.volume := VolumeSum;
    AppendDeal(tDeal);
  end;
end;

procedure TFormMain.ButtonPlotClick(Sender: TObject);
Var tYear: Integer;
Var tDeal: DealT;
begin
  TryLoadDeal(tDeal, True);
  DB.SelectSetup(tDeal);

  for tYear := MIN_YEAR to MAX_YEAR do
    Volumes[tYear] := 0;

  with tDeal do begin
    while DB.SelectNext(tDeal) do
      if (year >= MIN_YEAR) and (year <= MAX_YEAR)  then
        Volumes[year] := Volumes[year] + volume;
  end;
  Plot;
end;

procedure TFormMain.FormResize(Sender: TObject);
begin
  if ImagePlot.Visible then
    Plot;
end;

procedure TFormMain.GridDblClick(Sender: TObject);
begin
  if (Grid.Row > 0) and (Grid.Rows[Grid.Row][2] <> '') then begin // непустой год
    EditProduct.Text := Grid.Rows[Grid.Row][0];
    EditVolume.Text  := Grid.Rows[Grid.Row][1];
    EditYear.Text    := Grid.Rows[Grid.Row][2];
    EditCountry.Text := Grid.Rows[Grid.Row][3];
    if Grid.Rows[Grid.Row][4] = 'Импорт' then
      RadioImport.Checked := True
    else
      RadioExport.Checked := True;
  end;
end;

procedure TFormMain.Plot;
Var tDeal: DealT;
Var tYear: Word;
Var tVolume: Integer;

Var maxVolume, minVolume: Integer;
Var minYear, maxYear: Word;

Const PaddingLeft   = 40;
Const PaddingRight  = 30;
Const PaddingTop    = 50;
Const PaddingBottom = 30;
Const PlotPadding   = 15;

Var PixelPerVolume:  Real;
Var PixelPerYear:    Real;

Var NVLines: Integer; Const MaxNVLines = 10;  // число вертикальных и горизонтальных
Var NHLines: Integer; Const MaxNHLines = 10;  // линий в сетке

Const DotRadius = 2;

Var X, Y : Array [0..1] of Integer;
begin
  tYear := MIN_YEAR;
  minYear := MIN_YEAR;
  maxYear := MIN_YEAR;
  minVolume := Volumes[tYear];  // := 0
  maxVolume := Volumes[tYear];  // := 0
  while (Volumes[tYear] = 0) and (tYear <= MAX_YEAR) do
    Inc(tYear);

  if tYear <= MAX_YEAR then begin
    minYear := tYear;
    maxYear := tYear;

    minVolume := Volumes[tYear];
    maxVolume := Volumes[tYear];

    for tYear := (tYear+1) to MAX_YEAR do
      if Volumes[tYear] <> 0 then begin
        maxYear := tYear;
        if Volumes[tYear] > maxVolume then
          maxVolume := Volumes[tYear];
        if Volumes[tYear] < minVolume then
          minVolume := Volumes[tYear];
      end;
  end;

  OutputReset;
  ImagePlot.Visible := True;
  ImagePlot.Canvas.Brush.Color := clWhite;
  ImagePlot.Canvas.Rectangle(
    0, 0,
    ImagePlot.Width - 1, ImagePlot.Height - 1
  );

  if minYear = maxYear then begin
    X[0] := ImagePlot.Width div 2;
    Y[0] := ImagePlot.Height div 2;
    X[0] := X[0] - ImagePlot.Canvas.TextWidth('Недостаточно данных') div 2;
    Y[0] := Y[0] - ImagePlot.Canvas.TextHeight('Недостаточно данных') div 2;
    ImagePlot.Canvas.TextOut(
      X[0], Y[0], 'Недостаточно данных'
    )
  end else begin
    X[0] := (ImagePlot.Width + 30 + PlotPadding) div 2; // Для линии слева от текста
    Y[0] := PaddingTop div 2;
    X[0] := X[0] - ImagePlot.Canvas.TextWidth('- Зависимость объема экспорта от года') div 2;
    Y[0] := Y[0] - ImagePlot.Canvas.TextHeight('- Зависимость объема экспорта от года') div 2;
    ImagePlot.Canvas.TextOut(
      X[0], Y[0], '- Зависимость объема экспорта от года'
    );

    X[0] := X[0] - (30 + PlotPadding);
    X[1] := X[0] + 30;
    Y[0] := PaddingTop div 2;
    ImagePlot.Canvas.MoveTo(X[0], Y[0]);
    ImagePlot.Canvas.LineTo(X[1], Y[0]);

    ImagePlot.Canvas.Brush.Color := clRed;
    ImagePlot.Canvas.Rectangle(X[0] - DotRadius, Y[0] - DotRadius,
                               X[0] + DotRadius, Y[0] + DotRadius);
    ImagePlot.Canvas.Rectangle(X[1] - DotRadius, Y[0] - DotRadius,
                               X[1] + DotRadius, Y[0] + DotRadius);
    ImagePlot.Canvas.Brush.Color := clWhite;

    ImagePlot.Canvas.Pen.Style := psDot;
    ImagePlot.Canvas.Pen.Width := 1;
    ImagePlot.Canvas.Pen.Color := clGray;

    if MaxNVLines > (maxYear - minYear) then
      NVLines := maxYear - minYear
    else
      NVLines := MaxNVLines;
    PixelPerYear := ((ImagePlot.Width - (PaddingLeft + PaddingRight
        + 2 * PlotPadding)) / (maxYear - minYear));
    Y[0] := PaddingTop;
    Y[1] := ImagePlot.Height - PaddingBottom;
    tYear := minYear;
    while tYear <= maxYear do begin
      X[0] := PaddingLeft + PlotPadding + Round((tYear - minYear) * PixelPerYear);
      ImagePlot.Canvas.MoveTo(X[0], Y[0]);
      ImagePlot.Canvas.LineTo(X[0], Y[1]);
      X[0] := X[0] - ImagePlot.Canvas.TextWidth(IntToStr(tYear));
      ImagePlot.Canvas.TextOut(X[0], Y[1], IntToStr(tYear));
      tYear := tYear + (maxYear - minYear) div NVLines;
    end;

    if MaxNHLines > (MaxVolume - MinVolume + 1) then
      NHLines := MaxVolume - MinVolume + 1
    else
      NHLines := MaxNHLines;
    PixelPerVolume := (ImagePlot.Height - (PaddingTop + PaddingBottom
        + 2 * PlotPadding)) / (MaxVolume - MinVolume + 1);
    X[0] := PaddingLeft;
    X[1] := ImagePlot.Width - PaddingRight;
    tVolume := MinVolume;
    while tVolume <= (MaxVolume + 1) do begin
      Y[0] := ImagePlot.Height - (PaddingBottom + PlotPadding
        + Round((tVolume - MinVolume) * PixelPerVolume));
      ImagePlot.Canvas.MoveTo(X[0], Y[0]);
      ImagePlot.Canvas.LineTo(X[1], Y[0]);
      ImagePlot.Canvas.TextOut(X[0] - ImagePlot.Canvas
        .TextWidth(IntToStr(tVolume)), Y[0], IntToStr(tVolume));
      tVolume := tVolume + (MaxVolume - MinVolume + 1) div NHLines;
    end;

    ImagePlot.Canvas.Brush.Color := clRed;
    ImagePlot.Canvas.Pen.Color := clBlack;
    ImagePlot.Canvas.Pen.Style := psSolid;

    X[0] := PaddingLeft + PlotPadding;
    Y[0] := ImagePlot.Height - (PaddingBottom + PlotPadding +
      Round((Volumes[minYear] - minVolume) * PixelPerVolume));

    for tYear := minYear to maxYear do
      if Volumes[tYear] <> 0 then begin
        X[1] := X[0];
        Y[1] := Y[0];
        X[0] := PaddingLeft + PlotPadding + Round((tYear - minYear) * PixelPerYear);
        Y[0] := ImagePlot.Height - (PaddingBottom + PlotPadding +
            Round((Volumes[tYear] - minVolume) * PixelPerVolume));
        ImagePlot.Canvas.MoveTo(X[1], Y[1]);
        ImagePlot.Canvas.LineTo(X[0], Y[0]);
        ImagePlot.Canvas.Rectangle(X[1] - DotRadius, Y[1] - DotRadius,
                                   X[1] + DotRadius, Y[1] + DotRadius);
      end;
   ImagePlot.Canvas.Rectangle(X[0] - DotRadius, Y[0] - DotRadius,
                              X[0] + DotRadius, Y[0] + DotRadius);

  end;
end;

procedure TFormMain.AppendDeal;
begin
  Grid.RowCount := Grid.RowCount + 1;
  Grid.Rows[Grid.RowCount - 1].Clear;
  if tDeal.product <> nullDeal.product then
    Grid.Rows[Grid.RowCount - 1][0] := tDeal.product;
  if tDeal.volume <> nullDeal.volume then
    Grid.Rows[Grid.RowCount - 1][1] := IntToStr(tDeal.volume);
  if tDeal.year <> nullDeal.year then
    Grid.Rows[Grid.RowCount - 1][2] := IntToStr(tDeal.year);
  if tDeal.country <> nullDeal.country then
    Grid.Rows[Grid.RowCount - 1][3] := tDeal.country;
  case tDeal.mask of
    MASK_EXPORT: Grid.Rows[Grid.RowCount - 1][4] := 'Экспорт';
    MASK_IMPORT: Grid.Rows[Grid.RowCount - 1][4] := 'Импорт';
  end;
end;

function TFormMain.CheckEdit;
Var l, i: Integer;
Var Fail: Boolean;
begin
  Fail := False;
  l := Length(Edit.Text);
  if (l > 0) and (l <= MAX_STR_LEN) then begin
    if cs <> [] then begin
      i := 1;
      while (not Fail) and (i < l) do begin
        if not (upcase(Edit.Text[i]) in cs) then
          Fail := True;
        i := i + 1;
      end;
    end;
  end else
    Fail := True;

  Result := Fail;
end;

procedure TFormMain.ResetEdits;
begin
  EditProduct.Clear;
  EditVolume.Clear;
  EditYear.Clear;
  EditCountry.Clear;
  RadioAny.Checked := True;
end;

procedure TFormMain.ButtonAddClick(Sender: TObject);
var fail: Boolean;
var Year: Integer;
Var TmpDeal: DealT;
begin
  if TryLoadDeal(TmpDeal, False) then
    if TmpDeal.mask = MASK_ANY then
      GroupBox1.SetFocus
    else
      DB.Insert(TmpDeal);
end;

function TFormMain.TryLoadDeal;
var fail: Boolean;
var Year: Integer;
begin
  tDeal := nullDeal;
  fail := False;
  if nofail or not fail then begin
    fail := CheckEdit(EditProduct, ['A'..'Z', ' ']); 
    if fail then begin Result := True; if not nofail then EditProduct.SetFocus; end;
  end;
  if not fail then tDeal.product := EditProduct.Text;

  if nofail or not fail then begin
    fail := CheckEdit(EditVolume, ['0'..'9']); 
    if fail then begin Result := True; if not nofail then EditVolume.SetFocus; end;
  end;
  if not fail then tDeal.volume := StrToInt(EditVolume.Text);

  if nofail or not fail then begin
    fail := CheckEdit(EditYear,    ['0'..'9']);
    if not fail then begin
      Year := StrToInt(EditYear.Text);
      if not ((Year>=MIN_YEAR) and (Year<=MAX_YEAR)) then begin
        fail := True;
        EditYear.SetFocus;
      end;
    end;
    if fail then begin Result := True; if not nofail then EditYear.SetFocus; end;
  end;
  if not fail then tDeal.year := Year;

  if nofail or not fail then begin
    fail := CheckEdit(EditCountry, ['A'..'Z']); 
    if fail then begin Result := True; if not nofail then EditCountry.SetFocus; end;
  end;
  if not fail then tDeal.country := EditCountry.Text;
  
  if nofail or not fail then begin
         if RadioImport.Checked then tDeal.mask := MASK_IMPORT
    else if RadioExport.Checked then tDeal.mask := MASK_EXPORT
    else if RadioAny   .Checked then tDeal.mask := MASK_ANY   ;
  end;
end;

procedure TFormMain.ButtonResetClick(Sender: TObject);
begin
  ResetEdits;
end;

end.
