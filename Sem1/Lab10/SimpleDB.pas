unit SimpleDB;
interface
  uses DealType;

  Type SimpleDBC = Class
      fileH: File of DealT;
      constructor Create(fileName: string; wipe: Boolean=False);
      destructor Destroy; override;
    public
      // Добавляет запись
      procedure Insert(deal: DealT);
      // "Настройка" для последующего поиска
      procedure SelectSetup(deal: DealT);
      // Устанавливает res в первый найденный элемент или nullDeal
      function SelectNext(Var res: DealT): Boolean;
      // Находит, а затем удаляет
      function DeleteNext(Var res: DealT): Boolean;
    private
      fileLength: Word;
      cachedFPos: Word;
      selectPos : Word;
      insertPos : Word;
      lookingFor: DealT;
  End;
implementation

  procedure hotfix(DBFrom: SimpleDBC);
  Var DBTo: SimpleDBC;
  Var tDeal: DealT;
  begin
    DBTo := SimpleDBC.Create('ImportExport2.db', True);
    DBFrom.SelectSetup(nullDeal);
    while DBFrom.SelectNext(tDeal) do begin
      if tDeal.mask <> MASK_ANY then
        DBTo.Insert(tDeal);
    end;
    DBTo.Free;
  end;

  constructor SimpleDBC.Create;
  Var needsRewrite: Boolean;
  Var tDeal: DealT;
  begin
    AssignFile(fileH, fileName);
    if not wipe then begin
      {$I-} Reset(fileH); {$I+}
      needsRewrite := (IOResult <> 0);
    end else needsRewrite := True;

    if needsRewrite then begin
        ReWrite(fileH);
        Reset(fileH);
        tDeal := nullDeal;
        tDeal.year := 0;
        tDeal.mask := MASK_TOMBSTONE;
        Write(fileH, tDeal);
        fileLength := 1;
        insertPos := 1;
    end else begin
      fileLength := FileSize(fileH);
      Read(fileH, tDeal);
      if tDeal.year > 0 then
        insertPos := tDeal.year
      else
        insertPos := fileLength;
    end;

    cachedFPos := 1;
    selectPos  := 1;
    lookingFor := nullDeal;
    //if not wipe then hotfix(Self);
  end;

  destructor SimpleDBC.Destroy;
  begin
    CloseFile(fileH);
    inherited;
  end;

  procedure SimpleDBC.Insert;
  Var tDeal : DealT;
  begin
    if cachedFPos <> insertPos then
      Seek(fileH, insertPos);
    if insertPos <> fileLength then begin
      Read(fileH, tDeal);
      Seek(fileH, 0);
      Write(fileH, tDeal);
      Seek(fileH, insertPos);
    end;

    Write(fileH, deal);
    cachedFPos := insertPos + 1;
    if insertPos <> fileLength then begin
      if tDeal.year > 0 then
        insertPos := tDeal.year
      else
        insertPos := fileLength;
    end else begin
      Inc(fileLength);
      insertPos := fileLength;
    end;
  end;

  procedure SimpleDBC.SelectSetup;
  begin
    selectPos := 1;
    lookingFor := deal;
  end;

  function SimpleDBC.SelectNext;
  Var found: Boolean;
  Var deal: DealT;
  begin
    res := nullDeal;
    found := False;

    if cachedFPos <> selectPos then
      Seek(fileH, selectPos);
    while not (found or EOF(fileH)) do begin
      Read(fileH, deal);
      Inc(selectPos); Inc(cachedFPos);
      if deal.mask <> MASK_TOMBSTONE then
        found := DealCmp(lookingFor, deal);
    end;
    cachedFPos := selectPos;
    if found then
      res := deal;
    Result := found;
  end;

  function SimpleDBC.DeleteNext;
  Var deal: DealT;
  begin
    if SelectNext(res) then begin
      Result := True;
      deal := res;
      deal.mask := MASK_TOMBSTONE;
      if insertPos <> fileLength then
        deal.year := insertPos
      else
        deal.year := 0;
      insertPos := selectPos - 1;
      Seek(fileH, insertPos);
      Write(fileH, deal);
      Seek(fileH, 0);
      Read(fileH, deal);
      deal.year := insertPos;
      Seek(fileH, 0);
      Write(fileH, deal);
      cachedFPos := 1;
    end else
      Result := True;
  end;
end.
