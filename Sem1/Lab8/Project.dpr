program Project;

{$R *.res}

Const FilenameFrom = 'F.dat';
Const FilenameTo = 'G.txt';
Const MaxAuthorLen = 20;
Const MaxTitleLen = 40;


Type Book = Record 
  Author : String[MaxAuthorLen];
  Title : String[MaxTitleLen];
  Year : Integer;
End;

Var i, BooksToRead : Integer;
Var abook : Book;
Var F : File of Book;
Var G : Text;


Begin
  AssignFile(F, FilenameFrom);
  AssignFile(G, FilenameTo);
                                            //Rewrite(F);CloseFile(F);
  {$I-} Reset(F); {$I+}

  if (IOResult <> 0)
                                            //or (FileSize(F) < 2)
   then begin
    Rewrite(F);
    
    WriteLn('Error with ', FilenameFrom);

    Write('Enter book count: ');
    ReadLn(BooksToRead);

    for i := 1 to BooksToRead do begin
      with abook do begin
        Write('Author: '); ReadLn(Author);
        Write('Title: '); ReadLn(Title);
        Write('Year: '); ReadLn(Year);
      end;
      Write(F, abook);
    end;

    Reset(F);
  end;

  WriteLn('Books in ', FilenameFrom, ': ');
  while not Eof(F) do begin
    Read(F, abook);
    with abook do begin
      WriteLn('Author: ', Author);
      WriteLn('Title: ', Title);
      WriteLn('Year: ', Year);
      WriteLn;
    end;
  end;

  Rewrite(G);
  for i := (FileSize(F) - 1) downto 0 do begin
    Seek(F, i);
    Read(F, abook);
    WriteLn(G, abook.Title);
  end;
  
  WriteLn('---------------------------------------------');

  Reset(G);
  WriteLn('Books in ', FilenameTo, ': ');
  while not Eof(G) do begin
    ReadLn(G, abook.Title);
    WriteLn(abook.Title);
  end;

  CloseFile(G);
  CloseFile(F);
  ReadLn;
End.
