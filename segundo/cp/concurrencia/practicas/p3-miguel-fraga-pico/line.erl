-module(line).
-export([start/1, send/2, bounce/3, stop/1, loop/3]).

start(N) when N > 0 ->
    Pids = [spawn(line, loop, [Id, undefined, undefined]) || Id <- lists:seq(0, N-1)],
    conectar(Pids, undefined),
    hd(Pids).

conectar([P1, P2 | Resto], Prev) ->
    P1 ! {set, Prev, P2},
    conectar([P2 | Resto], P1);
conectar([Ultimo], Prev) ->
    Ultimo ! {set, Prev, undefined};
conectar([], _) -> 
    ok.

send(Pid, Msg) -> 
    Pid ! {send, Msg}, 
    ok.

bounce(Pid, Msg, Times) -> 
    Pid ! {bounce, Msg, Times - 1, forward}, 
    ok.

stop(Pid) -> 
    Pid ! stop, 
    ok.

loop(Id, Prev, Next) ->
    receive
        {set, P, N} -> 
            loop(Id, P, N);

        {send, Msg} ->
            io:format("~w received message ~p~n", [Id, Msg]),
            if 
                Next /= undefined -> Next ! {send, Msg}; 
                true -> ok 
            end,
            loop(Id, Prev, Next);

        {bounce, Msg, T, Dir} ->
            io:format("~w received message ~p~n", [Id, Msg]),
            if 
                T > 0 ->
                    {DestPid, NewDir} = case Dir of
                        forward when Next /= undefined -> {Next, forward};
                        forward -> {Prev, backward};
                        backward when Prev /= undefined -> {Prev, backward};
                        backward -> {Next, forward}
                    end,
                    DestPid ! {bounce, Msg, T - 1, NewDir};
                true -> 
                    ok
            end,
            loop(Id, Prev, Next);

        stop ->
            if 
                Next /= undefined -> Next ! stop; 
                true -> ok 
            end,
            ok
    end.
