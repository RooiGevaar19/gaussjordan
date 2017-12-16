unit DiceUnit;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, ParamUnit;

type
    Dice = class(TObject)
         var
            values : array of Integer;
         public
               constructor Create; overload;
               destructor Destroy; override;
               procedure Load(params : Parameter);
               function Throw() : Integer;
    end;

implementation

constructor Dice.Create;
begin
  SetLength(values, 0);
end;

destructor Dice.Destroy;
begin
  SetLength(values, 0);
end;

procedure Dice.Load(params : Parameter);
var
   i, j, k : Integer;
begin
     SetLength(values, params.getSumStrength());
     j := 0;
     for i := 0 to params.getWallCount()-1 do
         for k := 1 to params.getWallStrength(i) do
         begin
              values[j] := params.getWallValue(i);
              Inc(j);
         end;
end;

function Dice.Throw() : Integer;
begin
     Throw := values[Random(Length(values))];
end;

end.

