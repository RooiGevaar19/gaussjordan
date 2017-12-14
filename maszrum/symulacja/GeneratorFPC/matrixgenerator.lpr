program matrixgenerator;

uses ParamUnit, VariableUnit, DiceUnit;

type
    TIntegerArr   = array of Integer;
    TIntegerArr2D = array of array of Integer;
    TDoubleArr2D  = array of array of Extended;

var
   params       : Parameter;
   dic          : Dice;
   xs           : TIntegerArr2D;
   output       : TDoubleArr2D;
   anythingleft : boolean;
   count        : Integer;
   i, j         : Integer;

function Exists (player, posP1, posP2 : Integer) : boolean;
begin

end;

end.


begin
     params.Create;
     dic.Create;
     SetLength(xs, 1, 3);
     try
        params.Load('./input');
        i := 0;
        xs[i][0] := 0;             // 0 - P0, 1 - P2
        xs[i][1] := params.getP1StartPos();
        xs[i][2] := params.getP2StartPos();
        repeat
            anythingleft := false;
            for j in dic.GetFields() do
            begin
                if not (Exists((xs[i][0] + 1) mod 2, xs[i][1]+j, xs[i][2]+j)) then
                begin
                    Inc(i);
                    anythingleft := true;
                    SetLength(xs, i, 3);
                    xs[i][0] := (xs[i-1][0] + 1) mod 2;
                    xs[i][1] := xs[i-1][1]+j;
                    xs[i][2] := xs[i-1][2]+j;
                end;
            end;
        until not (anythingleft);
     finally
        dic.Destroy();
        params.Destroy();
     end;
end.

