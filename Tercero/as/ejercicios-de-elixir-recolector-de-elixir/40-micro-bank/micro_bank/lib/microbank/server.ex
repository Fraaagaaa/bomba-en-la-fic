defmodule MicroBank.Server do
  use GenServer

  def start_link(initial_state \\ %{}) do
    GenServer.start_link(__MODULE__, initial_state, name: __MODULE__)
  end

  def ask(name), do: GenServer.call(__MODULE__, {:ask, name})

  def deposit(name, amount), do: GenServer.cast(__MODULE__, {:deposit, name, amount})

  def withdraw(name, amount), do: GenServer.cast(__MODULE__, {:withdraw, name, amount})

  def stop(), do: GenServer.stop(__MODULE__)

  @impl true
  def init(state), do: {:ok, state}

  @impl true
  def handle_call({:ask, name}, _from, state) do
    saldo = Map.get(state, name, 0)
    {:reply, saldo, state}
  end

  @impl true
  def handle_cast({:deposit, name, amount}, state) do
    nuevo_saldo = Map.get(state, name, 0) + amount
    {:noreply, Map.put(state, name, nuevo_saldo)}
  end

  @impl true
  def handle_cast({:withdraw, name, amount}, state) do
    saldo_actual = Map.get(state, name, 0)

    if saldo_actual >= amount do
      {:noreply, Map.put(state, name, saldo_actual - amount)}
    else
      {:noreply, state}
    end
  end
end
