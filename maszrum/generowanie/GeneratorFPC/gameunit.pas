unit GameUnit;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, ParamUnit, DiceUnit;

type
    GameRound = class(TObject)
    var
       fields       : Integer;
       middle       : Integer;
       posP1, posP2 : Integer;
    public
          constructor Create; overload;
          destructor Destroy; override;
          function Play(dic : Dice; params : Parameter; var steps : Integer) : boolean;
    end;

implementation

constructor GameRound.Create;
begin

end;

destructor GameRound.Destroy;
begin

end;

function GameRound.Play(dic : Dice; params : Parameter; var steps : Integer) : boolean;
var
   flag : boolean;
   tmp  : Integer;
begin
     steps := 0;
     fields := 2*params.getFieldsCount()+1;
     middle := fields div 2;
     posP1 := params.getP1StartPos()+middle;
     posP2 := params.getP2StartPos()+middle;
     flag := false;
     repeat
        inc(steps);
        posP1 := posP1 + dic.Throw();
        posP1 := posP1 mod fields;
        if posP1 = middle then
        begin
            flag := true;
            break;
        end;

        posP2 := posP2 + dic.Throw();
        posP2 := posP2 mod fields;
        if posP2 = middle then
        begin
            flag := false;
            break;
        end;
     until (2137<>2137);
     Play := flag;
end;

end.

