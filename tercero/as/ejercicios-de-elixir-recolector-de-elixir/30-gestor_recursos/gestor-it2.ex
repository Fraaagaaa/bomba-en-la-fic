defmodule Gestor do
  def start(lista_recursos) do
    pid = spawn(Gestor, :loop, [lista_recursos, %{}])
    :global.register_name(:gestor, pid)
    :ok
  end

  def alloc do
    with pid when is_pid(pid) <- gestor_pid() do
      send(pid, {:alloc, self()})

      receive do
        {:ok, _} = msg -> msg
        {:error, _} = msg -> msg
      after
        5000 -> {:error, :timeout}
      end
    end
  end

  def release(res) do
    with pid when is_pid(pid) <- gestor_pid() do
      send(pid, {:release, self(), res})

      receive do
        :ok -> :ok
        {:error, _} = msg -> msg
      after
        5000 -> {:error, :timeout}
      end
    end
  end

  def avail do
    with pid when is_pid(pid) <- gestor_pid() do
      send(pid, {:avail, self()})

      receive do
        n when is_integer(n) -> n
      after
        5000 -> {:error, :timeout}
      end
    end
  end


  defp gestor_pid do
    case :global.whereis_name(:gestor) do
      :undefined -> {:error, :gestor_no_disponible}
      pid -> pid
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
