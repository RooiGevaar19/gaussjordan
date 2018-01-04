program Application;

uses ParamUnit, DiceUnit, GameUnit, SysUtils;

var
   par        : Parameter;
   dic        : Dice;
   game       : GameRound;
   i, n, step : Integer;
   result     : Real;
   count      : Real;

begin
     //n := 1000;
     //n := trunc(n);
     writeln(StdErr, '=== SIMULATION ===');
     par := Parameter.Create();
     dic := Dice.Create;
     game := GameRound.Create();
     try
        writeln(StdErr, 'Load the dice and start parameters.');
        par.Load(ParamStr(1));
        par.setFieldsCount(StrToInt(ParamStr(2)));
        par.setP1StartPos(StrToInt(ParamStr(2)));
        par.setP2StartPos(StrToInt(ParamStr(2))*(-1));
        dic.Load(par);
        writeln(StdErr, 'Randomize engine intialization.');
        randomize;

        result := 0.0;
        count := 0.0;
        writeln(StdErr, 'Start a simulation.');
        for i := 1 to StrToInt(ParamStr(3)) do
        begin
             if (game.Play(dic, par, step)) then
             begin
                  writeln(StdErr, i, ' - Player 1 won in ', step,' turns!');
                  result := result + 1.0;
                  count := count + 1.0;
             end else begin
                 writeln(StdErr, i, ' - Player 2 won in ', step,' turns!');
                 count := count + 1.0;
             end;
        end;
        writeln(FloatToStr(result/count));
        writeln(StdErr, 'Success.');
     finally
            game.Destroy;
            dic.Destroy;
            par.Destroy;
     end;
     //readln;
end.

