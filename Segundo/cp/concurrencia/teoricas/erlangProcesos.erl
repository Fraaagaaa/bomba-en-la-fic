% Procesos

Pid = spawn(Modulo, Función, Argumentos).

f(x, y) -> x + y.
Pid = spawn(Modulo, f, [2, 3]).
% El único que sabe el pid es el proceso que lo creó.


% Envio de mensajes
Pid ! Mensaje.
Pid ! {hola, "hello world"}.

Pid ! Mensaje.
Pid ! {adios, "adios"}.
% Los procesos tienen un mailbox, una cola de mensajes que van llegando. El proceso puede leer los mensajes con la función receive.

recive
    {hola, str} ->
        io:format("Recibido: " ++ str);
    {adios, str} ->
        io:format("Recibido otro: " ++ str);
end.
% Cuando se lee el mensaje se borra del mailbox
% Se eliminan en el orden en el que están en la función recive, no en el orden en que llegan
% Si nos envian un mensaje que no encaja, 


self() % Devuelve el pid del proceso actual
Pid ! {hello, "adada", self()}.

recive
    {hola, str} ->
        io:format("Recibido: " ++ str);
    {adios, str} ->
        io:format("Recibido otro: " ++ str);
    {hello, str, From} -> From ! {ok, "recibido el mensaje"};
end.
