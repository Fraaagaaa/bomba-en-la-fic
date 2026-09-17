defmodule Federation.Fixtures do
  def setup_federation() do
    node_name = Federation.Server.current_server_name()

    users =
      case node_name do
        "enterprise" ->
          %{
            "spock" => %{full_name: "Spock", avatar: "img/spock.png"},
            "picard" => %{full_name: "Jean-Luc Picard", avatar: "img/picard.png"},
            "data" => %{full_name: "Data", avatar: "img/data.png"},
            "troi" => %{full_name: "Deanna Troi", avatar: "img/troi.png"}
          }

        "cimitar" ->
          %{
            "pretor" => %{full_name: "Pretor Shinzon", avatar: "img/shinzon.png"},
            "virrey" => %{full_name: "Virrey Vkruk", avatar: "img/vkruk.png"}
          }

        _ ->
          %{}
      end

    {:ok, _pid} = Federation.Server.start_link(users)
    IO.puts("\n🚀 Servidor '#{node_name}' iniciado y listo para la federación.\n")
  end
end
