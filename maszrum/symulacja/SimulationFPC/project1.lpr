program Application;

uses ParamUnit, DiceUnit, GameUnit;

var
   par       : Parameter;
   dic       : Dice;
   game      : GameRound;
   i, n      : Integer;
   result    : Real;
   count     : Real;

begin
     n := 1000;
     //n := trunc(n);

     par := Parameter.Create();
     dic := Dice.Create;
     game := GameRound.Create();
     try
        par.Load('./input');
        dic.Load(par);
        randomize;

        result := 0.0;
        count := 0.0;
        for i := 1 to n do
        begin
             if (game.Play(dic, par)) then
             begin
                  writeln(StdErr, i, ' - Player 1 won!');
                  result := result + 1.0;
                  count := count + 1.0;
             end else begin
                 writeln(StdErr, i, ' - Player 2 won!');
                 count := count + 1.0;
             end;
        end;
        writeln((result/count):2:16);
     finally
            game.Destroy;
            dic.Destroy;
            par.Destroy;
     end;
end.

