program matrixgenerator;

uses ParamUnit, DiceUnit;

type
    //TIntegerArr   = array of Integer;
    TIntegerArr2D = array of array of Integer;
    //TDoubleArr2D  = array of array of Extended;

var
   params       : Parameter;
   dic          : Dice;
   xs           : TIntegerArr2D;
   //output       : TDoubleArr2D;
   anythingleft : boolean;
   count        : Integer;
   i, j, x      : Integer;

function Exists (player, posP1, posP2 : Integer) : boolean;
var
   x    : Integer;
   flag : Boolean;
begin
     flag := false;
     for x := Low(xs) to High(xs) do
     begin
         if (player = xs[x][1])
         and (posP1 = xs[x][2])
         and (posP2 = xs[x][3])
         then begin
             flag := true;
             break;
         end;
     end;
     Exists := flag;
end;

begin
     params.Create;
     dic.Create;
     SetLength(xs, 1, 4);
     try
     params.Load('./input');
     dic.Load(params);
     i := 0;
     xs[i][0] := i+1;
     xs[i][1] := 0;             // 0 - P0, 1 - P2
     xs[i][2] := params.getP1StartPos();
     xs[i][3] := params.getP2StartPos();
     repeat
         anythingleft := false;
         for j in dic.GetFields() do
         begin
             if not (Exists((xs[i][1] + 1) mod 2, xs[i][2]+j, xs[i][3]+j)) then
             begin
                 Inc(i);
                 anythingleft := true;
                 SetLength(xs, i, 4);
                 xs[i][0] := i+1;
                 xs[i][1] := (xs[i-1][1] + 1) mod 2;
                 xs[i][2] := xs[i-1][2]+j;
                 xs[i][3] := xs[i-1][3]+j;
             end;
         end;
     until not (anythingleft);


     for x := Low(xs) to High(xs) do
     begin
        writeln('Prop ', xs[x][0], ' - P', xs[x][1],' (', xs[x][2],', ',xs[x][3],') ');
     end;
     finally
     dic.Destroy();
     params.Destroy;
     SetLength(xs, 0, 0);
     end;
end.

