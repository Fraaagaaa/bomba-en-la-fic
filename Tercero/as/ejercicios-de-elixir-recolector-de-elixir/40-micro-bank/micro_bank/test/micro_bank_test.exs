defmodule MicroBankTest do
  use ExUnit.Case
  alias MicroBank.Server

  setup do
    pid = GenServer.whereis(Server)

    {:ok, server_pid: pid}
  end

  test "consulta de saldo inicial" do
    assert Server.ask("Juan") >= 0
  end

  test "operaciones de ingreso y retiro" do
    saldo_inicial = Server.ask("Juan")
    Server.deposit("Juan", 50)
    assert Server.ask("Juan") == saldo_inicial + 50
  end

  test "resiliencia: el supervisor levanta el servidor tras un fallo" do
    old_pid = GenServer.whereis(Server)
    assert is_pid(old_pid)

    Process.flag(:trap_exit, true)
    Process.exit(old_pid, :kill)

    :timer.sleep(50)

    new_pid = GenServer.whereis(Server)

    assert new_pid != nil
    assert new_pid != old_pid
    assert Process.alive?(new_pid)
  end
end
