defmodule Worker do
  def start() do
    spawn(fn -> bucle_worker() end)
  end

  def stop(pid) do
    send(pid, :terminar)
    :ok
  end

  def bucle_worker() do
    receive do
      {:hacer_chamba, maestro, funcion} ->
        r = funcion.()
        
        :timer.sleep(:rand.uniform(1000))
        
        send(maestro, {:ya_esta, self(), r})
        bucle_worker()

      :terminar ->
        :ok
    end
  end
end

defmodule Master do
  def start(n) do
    master_pid = spawn(fn -> 
      lista_workers = crear_workers(n, [])
      
      mapa_inicial = %{
        libres: lista_workers,
        ocupados: %{},
        lotes: %{},
        cola: []
      }
      
      bucle_master(mapa_inicial)
    end)
    {:ok, master_pid}
  end

  def crear_workers(0, acc), do: acc
  def crear_workers(n, acc) do
    crear_workers(n - 1, [Worker.start() | acc])
  end

  def run_batch(pid_maestro, lista_tareas) do
    referencia = make_ref()
    send(pid_maestro, {:nuevo_lote, self(), referencia, lista_tareas})
    
    receive do
      {:terminado, ^referencia, resultados} -> resultados
    end
  end

  def stop(pid) do
    send(pid, :apagar)
    :ok
  end

  def bucle_master(estado) do
    receive do
      {:nuevo_lote, cliente, ref, tareas} ->
        nuevo_lote = %{cliente: cliente, resultados: %{}, total: length(tareas)}
        nuevos_lotes = Map.put(estado.lotes, ref, nuevo_lote)
        
        tareas_indexadas = indexar_tareas(tareas, ref, 0, [])
        nueva_cola = estado.cola ++ tareas_indexadas
        
        estado_actualizado = %{estado | lotes: nuevos_lotes, cola: nueva_cola}
        intentar_despachar(estado_actualizado)

      {:ya_esta, pid_worker, valor} ->
        {ref_lote, num_tarea} = estado.ocupados[pid_worker]
        
        lote = estado.lotes[ref_lote]
        nuevos_res = Map.put(lote.results, num_tarea, valor)
        
        estado_tras_resultado = if Map.size(nuevos_res) == lote.total do
          lista_final = for i <- 0..(lote.total - 1), do: nuevos_res[i]
          send(lote.client, {:terminado, ref_lote, lista_final})
          
          %{estado | lotes: Map.delete(estado.lotes, ref_lote)}
        else
          lote_actualizado = %{lote | results: nuevos_res}
          %{estado | lotes: Map.put(estado.lotes, ref_lote, lote_actualizado)}
        end

        nuevos_libres = [pid_worker | estado_tras_resultado.libres]
        nuevos_ocupados = Map.delete(estado_tras_resultado.ocupados, pid_worker)
        
        intentar_despachar(%{estado_tras_resultado | libres: nuevos_libres, ocupados: nuevos_ocupados})

      :apagar ->
        for w <- estado.libres, do: Worker.stop(w)
        llaves = Map.keys(estado.ocupados)
        for w <- llaves, do: Worker.stop(w)
        :ok
    end
  end

  def indexar_tareas([], _ref, _i, acc), do: acc
  def indexar_tareas([t | resto], ref, i, acc) do
    indexar_tareas(resto, ref, i + 1, acc ++ [{ref, i, t}])
  end

  def intentar_despachar(e) do
    libres = e.libres
    cola = e.cola

    if length(libres) > 0 and length(cola) > 0 do
      [w | rest_w] = libres
      [tarea | rest_q] = cola
      {r, idx, f} = tarea
      
      send(w, {:hacer_chamba, self(), f})
      
      nuevo_estado = %{e | 
        libres: rest_w, 
        ocupados: Map.put(e.ocupados, w, {r, idx}),
        cola: rest_q
      }
      intentar_despachar(nuevo_estado)
    else
      bucle_master(e)
    end
  end
end
