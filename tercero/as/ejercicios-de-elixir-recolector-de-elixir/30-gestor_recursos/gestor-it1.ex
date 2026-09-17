defmodule Gestor do
  def start(lista_recursos) do
    pid = spawn(Gestor, :loop, [lista_recursos, %{}])
    Process.register(pid, :gestor)
    :ok
  end

  def alloc do
    send(:gestor, {:alloc, self()})

    receive do
      {:ok, _} = msg -> msg
      {:error, _} = msg -> msg
    after
      5000 -> {:error, :timeout}
    end
  end

  def release(res) do
    send(:gestor, {:release, self(), res})

    receive do
      :ok -> :ok
      {:error, _} = msg -> msg
    after
      5000 -> {:error, :timeout}
    end
  end

  def avail do
    send(:gestor, {:avail, self()})

    receive do
      n when is_integer(n) -> n
    after
      5000 -> {:error, :timeout}
    end
  end

  def loop(disponibles, asignados) do
    receive do
      {:alloc, from} ->
        case disponibles do
          [res | resto] ->
            send(from, {:ok, res})
            loop(resto, Map.put(asignados, res, from))

          [] ->
            send(from, {:error, :sin_recursos})
            loop(disponibles, asignados)
        end

      {:release, from, res} ->
        case Map.fetch(asignados, res) do
          {:ok, ^from} ->
            send(from, :ok)
            loop([res | disponibles], Map.delete(asignados, res))

          _ ->
            send(from, {:error, :recurso_no_reservado})
            loop(disponibles, asignados)
        end

      {:avail, from} ->
        send(from, length(disponibles))
        loop(disponibles, asignados)
    end
  end
end
