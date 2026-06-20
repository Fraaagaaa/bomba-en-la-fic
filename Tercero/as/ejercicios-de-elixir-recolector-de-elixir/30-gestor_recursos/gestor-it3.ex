defmodule Gestor do
  def start(lista_recursos) do
    pid = spawn(Gestor, :loop, [lista_recursos, %{}, %{}])
    :global.register_name(:gestor, pid)
    :ok
  end

  def alloc do
    call({:alloc, self()})
  end

  def release(res) do
    call({:release, self(), res})
  end

  def avail do
    call({:avail, self()})
  end

  defp call(msg) do
    case :global.whereis_name(:gestor) do
      :undefined ->
        {:error, :gestor_no_disponible}

      pid ->
        send(pid, msg)

        receive do
          resp -> resp
        after
          5000 -> {:error, :timeout}
        end
    end
  end

  def loop(disponibles, asignados, clientes) do
    receive do
      {:alloc, from} ->
        case disponibles do
          [res | resto] ->
            {clientes, ref} =
              case Map.get(clientes, from) do
                nil ->
                  ref = Process.monitor(from)
                  {Map.put(clientes, from, {ref, [res]}), ref}

                {ref, recursos} ->
                  {Map.put(clientes, from, {ref, [res | recursos]}), ref}
              end

            send(from, {:ok, res})
            loop(resto, Map.put(asignados, res, from), clientes)

          [] ->
            send(from, {:error, :sin_recursos})
            loop(disponibles, asignados, clientes)
        end

      {:release, from, res} ->
        case Map.fetch(asignados, res) do
          {:ok, ^from} ->
            {ref, recursos} = Map.get(clientes, from)
            nuevos_recursos = List.delete(recursos, res)

            clientes =
              if nuevos_recursos == [] do
                Process.demonitor(ref, [:flush])
                Map.delete(clientes, from)
              else
                Map.put(clientes, from, {ref, nuevos_recursos})
              end

            send(from, :ok)

            loop(
              [res | disponibles],
              Map.delete(asignados, res),
              clientes
            )

          _ ->
            send(from, {:error, :recurso_no_reservado})
            loop(disponibles, asignados, clientes)
        end

      {:avail, from} ->
        send(from, length(disponibles))
        loop(disponibles, asignados, clientes)

      {:DOWN, _ref, :process, pid, _reason} ->
        case Map.get(clientes, pid) do
          nil ->
            loop(disponibles, asignados, clientes)

          {_ref, recursos} ->
            IO.puts("[Gestor] Cliente caído. Liberando: #{inspect(recursos)}")

            nuevos_disponibles = recursos ++ disponibles

            nuevos_asignados =
              Enum.reduce(recursos, asignados, fn res, acc ->
                Map.delete(acc, res)
              end)

            nuevos_clientes = Map.delete(clientes, pid)

            loop(nuevos_disponibles, nuevos_asignados, nuevos_clientes)
        end
    end
  end
end
