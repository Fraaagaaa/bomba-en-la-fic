defmodule Eratostenes do
  def primos(n) when is_integer(n) and n < 2, do: []
  def primos(n) when is_integer(n) do
    pid_inicial = spawn(fn -> ultimo(self()) end)
    
    enviar_rango(2, n, pid_inicial)
    
    send(pid_inicial, :fin)

    receive do
      {:resultado, lista_primos} -> lista_primos
    end
  end


  def enviar_rango(actual, n, _pid) when actual > n, do: :ok
  def enviar_rango(actual, n, pid) do
    send(pid, {:numero, actual})
    enviar_rango(actual + 1, n, pid)
  end

  def filtro(p, siguiente, padre) do
    receive do
      {:numero, n} ->
        if rem(n, p) != 0 do
          send(siguiente, {:numero, n})
        end
        filtro(p, siguiente, padre)

      :fin ->
        send(siguiente, :fin)
        receive do
          {:resultado, lista_acumulada} ->
            send(padre, {:resultado, [p | lista_acumulada]})
        end
    end
  end

  def ultimo(padre) do
    receive do
      {:numero, n} ->
        nuevo_ultimo = spawn(fn -> ultimo(self()) end)
        filtro(n, nuevo_ultimo, padre)

      :fin ->
        send(padre, {:resultado, []})
    end
  end
end
