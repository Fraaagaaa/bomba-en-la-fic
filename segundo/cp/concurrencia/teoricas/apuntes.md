``` erl
link(pidB)

spawn_link(...)
process_flag(trap_exit, true)

recive('EXIT', PID, REASON)
end
```
# Ejercicio 1 de los ejercicios de erlang
```erl
register(N) ->
    N ! {register, self()}.

send(N, Msg) ->
    N ! {send, Msg}.


loop(L) -> %L = lista de los procesos registrados
    recive
        {register, from} ->
            loop(From | L);
        {send, Msg} ->
            sendToAll(L, Msg);
            loop(L);
end

sendToAll([], _) -> ok.
sendToAll([P | Ps], Msg) ->
    P ! Msg,
    sendToAll(Ps, Msg).
```


# Ejercicio 2 de los ejercicios de erlang
``` erl
-module(store).
-export([start/0, store/2, get/2]).
-export([loop/0]).

%% API

sotre(S, p) ->
    S ! {sotre, p}.

get(S, F)
    S ! {get, F, self()},
    recive
        {get_reply, R} ->
            R.
end.

loop(L) ->
    recive
        {store, p} ->
            loop([P | L]).
        {get, F, From} ->
            case search(F, L) of
                not_found ->
                    From ! {get_reply, {error, no_product}},
                    loop(L).
                {ok, P, NL} ->
                    From ! {get_reply, {ok, P}},
                    loop(NL).
            end
end.

search(F, L) ->
    search(L, F, []).

search([], F, Acc) -> not_found;
search([P | Ps], F, Acc) ->
    case F(P) of
        true ->
            {ok, P, Acc ++ Ps};
        false ->
            search(Ps, F, [P | Acc]);
    end.

```

# Ejercicio 3 de los ejercicios de erlang

``` erl
height(Tree) ->
    Tree ! {height, self()},
    recive
        {height_reply, H} ->
            H.
end.

loop(Children) ->
    recive
        {add_child, Children_Tree} ->
            loop(Children ++ [Child_Tree]);
        {height, From} ->
            Hs = [heights(T) || T <-Children],
            From ! {height_reply, 1 + maximum(Hs)},
            loop(Children)
end.

maximum([]) -> 0;
maximum([H | Hs]) ->
    maxHs = maximum(Hs),
    if H > maxHs -> H
    true -> maxHs
end.
```
