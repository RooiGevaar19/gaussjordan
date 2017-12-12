unit ParamUnit;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils;

type
  Parameter = class(TObject)

    var
    fieldsCount      : Integer;            // 2N + 1
    p1start, p2start : Integer;
    wallCount        : Integer;
    wall, prop       : array of integer;
  private
  public
    constructor Create; overload;
    destructor Destroy; override;
    procedure Load(inp : String);
    function getFieldsCount() : Integer;
    function getP1StartPos() : Integer;
    function getP2StartPos() : Integer;
    function getWallCount() : Integer;
    function getWallValue(index : Integer) : Integer;
    function getWallStrength(index : Integer) : Integer;
    procedure setFieldsCount(x : Integer);
    procedure setP1StartPos(x : Integer);
    procedure setP2StartPos(x : Integer);
    procedure setWallCount(x : Integer);
    procedure setWallValue(index, x : Integer);
    procedure setWallStrength(index, x : Integer);
    function getSumStrength() : Integer;
  //published
    //property FieldCount : integer read GetFieldsCount write SetFieldsCount default 0;
  end;

implementation

constructor Parameter.Create;
begin
     SetLength(wall, 0);
     SetLength(prop, 0);
end;

destructor Parameter.Destroy;
begin
     //SetLength(wall, 0);
     //SetLength(prop, 0);
     wall := nil;
     prop := nil;
end;

procedure Parameter.Load(inp : String);
var
   input       : TextFile;
   L           : TStringList;
   varl, tmp   : String;
   i, Code, Im : Integer;
begin
     AssignFile(input, inp);
     Reset(input);

     // liczba pól
     readln(input, tmp);
     self.setFieldsCount(StrToInt(tmp));

     // pola startowe
     readln(input, varl);
     L := TStringList.Create;
     L.Delimiter := #9;
     L.QuoteChar := '"';
     L.StrictDelimiter := false;
     L.DelimitedText := varl;
     p1start := StrToInt(L.Strings[0]);
     p2start := StrToInt(L.Strings[1]);
     L.Free;

     // liczba ścian
     readln(input, wallCount);

     // ściany
     SetLength(wall, wallCount);
     readln(input, varl);
     L := TStringList.Create;
     L.Delimiter := #9;
     L.QuoteChar := '"';
     L.StrictDelimiter := false;
     L.DelimitedText := varl;
     for i := 0 to wallCount-1 do wall[i] := StrToInt(L.Strings[i]);
     L.Free;

     // prawdopodobieństwa do ścian
     SetLength(prop, wallCount);
     readln(input, varl);
     L := TStringList.Create;
     L.Delimiter := #9;
     L.QuoteChar := '"';
     L.StrictDelimiter := false;
     L.DelimitedText := varl;
     for i := 0 to wallCount-1 do prop[i] := StrToInt(L.Strings[i]);
     L.Free;

     CloseFile(input);
end;

function Parameter.getFieldsCount() : Integer;
begin
    getFieldsCount := fieldsCount;
end;

function Parameter.getP1StartPos() : Integer;
begin
    getP1StartPos := p1start;
end;

function Parameter.getP2StartPos() : Integer;
begin
    getP2StartPos := p2start;
end;

function Parameter.getWallCount() : Integer;
begin
     getWallCount := wallCount;
end;

function Parameter.getWallValue(index : Integer) : Integer;
begin
     getWallValue := wall[index];
end;

function Parameter.getWallStrength(index : Integer) : Integer;
begin
     getWallStrength := prop[index];
end;

function Parameter.getSumStrength() : Integer;
var
   s, i : Integer;
begin
     s := 0;
     for i := 0 to wallCount-1 do s := s + prop[i];
     getSumStrength := s;
end;

procedure Parameter.setFieldsCount(x : Integer);
begin
     fieldsCount := x;
end;

procedure Parameter.setP1StartPos(x : Integer);
begin
     p1start := x;
end;

procedure Parameter.setP2StartPos(x : Integer);
begin
     p2start := x;
end;

procedure Parameter.setWallCount(x : Integer);
begin
     wallCount := x;
end;

procedure Parameter.setWallValue(index, x : Integer);
begin
     wall[index] := x;
end;

procedure Parameter.setWallStrength(index, x : Integer);
begin
     prop[index] := x;
end;

end.

