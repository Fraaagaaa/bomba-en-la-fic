% Ejemplos listas

legnth([]) -> 0;
legnth([_ | T]) -> 1 + legnth(T).
map(F, []) -> [];
map(F, [H | T]) -> [F(H) | map(F, T)].

part([], _, L1, L2) -> {L1, L2};
part([H | T], P, L1, L2) ->
    if H<Piv -> part(T, Piv, [H | L1], L2);
       true -> part(T, Piv, L1, [H | L2])
    end.

qsort([]) -> [];
qsort([H | T]) ->
    {L1, L2} = part(T, H, [], []),
    qsort(L1) ++ [H] ++ qsort(L2).


% Errores
{error, "otrotipo"}
% Se puede comprobar con patter matching

Case v of 
    {error, Error} -> ...;
    {ok, Resultado} -> ...;
end.

match v with
    Error e ->
    Resultado r ->
end.


% funciones

fun (Arg1, Arg2, ..., ArgN) ->
        <Cuerpo>
end


qsort([]) ->[];
qsort([H | T]) ->
    qsort([x || x <- T, x < H]) ++
    [H] ++
    qsort([x || x <- T, x >= H]).
