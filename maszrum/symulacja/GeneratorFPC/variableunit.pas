unit VariableUnit;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils;

type
    Variable : class(TObject)
    var
    public
      constructor Create; overload;
      destructor Destroy; override;
    end;

implementation

end.

