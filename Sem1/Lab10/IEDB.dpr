program IEDB;

uses
  Forms,
  Main in 'Main.pas' {FormMain},
  DealType in 'DealType.pas',
  SimpleDB in 'SimpleDB.pas';

{$R *.res}
begin
  Application.Initialize;
  Application.CreateForm(TFormMain, FormMain);
  Application.Run;
end.
