-module(ring).
-export([start/1, send/3, stop/1, loop/1, loop/2]).

start(N) ->
    Pids = [spawn(ring, loop, [I]) || I <- lists:seq(0, N-1)], % I es el ID que se va a usar en el print
    conectar(Pids),
    hd(Pids).

conectar([First | Tail]) ->
    List = Tail ++ [First],
    unir_puntos([First | Tail], List).

unir_puntos([], []) -> ok;
unir_puntos([P | Ps], [Next | Nexts]) -> % Le dice cual es el siguiente a cada proceso
    P ! {set_next, Next},
    unir_puntos(Ps, Nexts).

send(Pid, N, Msg) ->
    Pid ! {msg, N - 1, Msg}, 
    ok.

stop(Pid) ->
    Pid ! stop,
    ok.

loop(Id) ->
    receive
        {set_next, Next} -> loop(Id, Next)
    end.

loop(Id, Next) ->
    receive
        {msg, Left, Msg} ->
            io:format("~w receiving message ~p with ~w left~n", [Id, Msg, Left]),
            if 
                Left > 0 -> Next ! {msg, Left - 1, Msg};
                true -> ok 
            end,
            loop(Id, Next);

        stop ->
            Next ! stop,
            ok
    end.
