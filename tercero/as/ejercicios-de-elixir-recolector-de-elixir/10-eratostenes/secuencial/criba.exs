defmodule Eratostenes do
  def primos(n) do
    if n < 2 do
      []
    else
      numeros = crear_lista_numeros(2, n, [])
      hacer_la_criba(numeros)
    end
  end

  def crear_lista_numeros(actual, limite, lista_acumulada) do
    if actual > limite do
      lista_acumulada
    else
      nueva_lista = lista_acumulada ++ [actual]
      crear_lista_numeros(actual + 1, limite, nueva_lista)
    end
  end

  def hacer_la_criba(lista) do
    case lista do
      [] -> []
      [cabeza | cola] ->
        el_resto_limpio = filtrar_multiplos(cola, cabeza, [])
        [cabeza] ++ hacer_la_criba(el_resto_limpio)
    end
  end

  def filtrar_multiplos(lista_a_filtrar, p, aux) do
    case lista_a_filtrar do
      [] -> aux
      [h | t] ->
        if rem(h, p) == 0 do
          filtrar_multiplos(t, p, aux)
        else
          filtrar_multiplos(t, p, aux ++ [h])
        end
    end
  end
end
