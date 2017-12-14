program Application;

uses ParamUnit, DiceUnit;

type
    TIntegerArr   = array of Integer;
    TIntegerArr2D = array of array of Integer;
    //TDoubleArr2D  = array of array of Extended;

var
   par          : Parameter;
   dic          : Dice;
   xs           : TIntegerArr2D;
   walls        : TIntegerArr;
   i, j, x      : Integer;
   anythingleft : Boolean;

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
     par := Parameter.Create();
     dic := Dice.Create;
     SetLength(xs, 1, 4);
     try
        par.Load('./input');
        dic.Load(par);
        walls := dic.GetFields();

        i := 0;
        xs[i][0] := i+1;
        xs[i][1] := 0;             // 0 - P0, 1 - P2
        xs[i][2] := par.getP1StartPos();
        xs[i][3] := par.getP2StartPos();
        //{*
        //repeat
              anythingleft := false;
              for j in walls do
              begin
                   if not (Exists((xs[i][1] + 1) mod 2, xs[i][2]+j, xs[i][3]+j)) then
                   begin
                        Inc(i);
                        anythingleft := true;
                        SetLength(xs, i+1, 4);
                        xs[i][0] := i+1;
                        xs[i][1] := (xs[i-1][1] + 1) mod 2;
                        xs[i][2] := xs[i-1][2]+j;
                        xs[i][3] := xs[i-1][3]+j;
                   end;
              end;
        //until (not (anythingleft)) or (i = 10);
        //*}


        for x := Low(xs) to High(xs) do
        begin
             writeln('Prop ', xs[x][0], ' - P', xs[x][1],' (', xs[x][2],', ',xs[x][3],') ');
        end;
        finally
            SetLength(xs, 0, 0);
            dic.Destroy;
            par.Destroy;
        end;
end.

