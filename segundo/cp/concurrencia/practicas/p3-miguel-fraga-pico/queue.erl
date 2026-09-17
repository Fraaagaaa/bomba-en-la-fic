-module(queue).

-export([empty/0, insert/2, remove/1]).

empty() ->
    {[], []}.

insert({Front, Back}, Elem) ->
    {Front, [Elem | Back]}.

remove({[], []}) ->
    empty;

remove({[Head | Tail], Back}) ->
    {ok, Head, {Tail, Back}};

remove({[], Back}) ->
    [Head | Tail] = lists:reverse(Back),
    {ok, Head, {Tail, []}}.
