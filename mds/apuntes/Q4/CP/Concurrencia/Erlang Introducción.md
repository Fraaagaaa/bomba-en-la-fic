## Hola Mundo!
``` erl
-module(hola_mundo). %Nombre del módulo
-export([hola/0]) % Funciones que exporta el módulo y el nº de parámetros que reciben

hola() ->            % Función hola
	io:format("Hola Mundo!~n").
	    % Llamada a la función format del módulo io
```

### Compilación y ejecución

``` bash
$ elrc hola_mundo.erl
$ erl
Erlang/OPT 17 [erts-6.2] [source] [64-bit] [smp:4:4] [async-threads:10] [kernel-poll:false]

Eshell V6.2 (abort with ^G)
1> hola_mundo:hola().
Hola Mundo!
ok
2>
```

## Factorial
``` elr
-module(factorial).
-export([fact/1]). % exporta la función fact con 1 arg

fact(N) ->
	if N==0 -> 1;
		true -> N*fact(N->1)
	end.
```

## Variables
Las variables **empiezan por mayúscula** y al contrario que en caml no se puede reutilizar su nombre:
``` erl
1> N=0.
0
2> N.
0
3> N=1.
** exception error: no match of right hand side value 1
4>
```
### Factorial con patter matching
``` elr
-module(factorial).
-export([fact/1]). % exporta la función fact con 1 arg

fact(0) ->
	1;
fact(N) ->
	N*fact(N-1).
```

## Funciones

Forma general de las funciones

```
function(Pattern1, Pattern2, ...) -> %
	<expresion>,
	...
	<expresion>;
...
function(PatternM, PatternN, ...) -> %
	<expresion>,
	...
	<expresion>.