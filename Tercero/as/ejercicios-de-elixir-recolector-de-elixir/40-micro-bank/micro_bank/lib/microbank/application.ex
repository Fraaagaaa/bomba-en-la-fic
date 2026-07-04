defmodule MicroBank.Application do
  use Application

  @impl true
  def start(_type, _args) do
    children = [
      {MicroBank.Server, %{"Juan" => 100}}
    ]

    opts = [strategy: :one_for_one, name: MicroBank.Supervisor]
    Supervisor.start_link(children, opts)
  end
end
