defmodule Federation.Server do
  use GenServer

  def start_link(initial_users \\ %{}) do
    initial_state = %{
      users: initial_users,
      inboxes: Map.new(Map.keys(initial_users), fn u -> {u, []} end)
    }
    GenServer.start_link(__MODULE__, initial_state, name: __MODULE__)
  end

  def get_profile(requester_id, target_id) do
    GenServer.call(__MODULE__, {:get_profile, requester_id, target_id})
  end

  def post_message(sender_id, receiver_id, message) do
    GenServer.call(__MODULE__, {:post_message, sender_id, receiver_id, message})
  end

  def retrieve_messages(user_id) do
    GenServer.call(__MODULE__, {:retrieve_messages, user_id})
  end

  def current_server_name do
    Node.self() |> to_string() |> String.split("@") |> List.first()
  end

  @impl true
  def init(state) do
    {:ok, state}
  end

  @impl true
  def handle_call({:get_profile, requester_id, target_id}, _from, state) do
    with {:ok, req_user, req_server} <- parse_id(requester_id),
         true <- is_local_server?(req_server),
         true <- user_exists?(state, req_user),
         {:ok, tgt_user, tgt_server} <- parse_id(target_id) do

      if is_local_server?(tgt_server) do
        case get_user(state, tgt_user) do
          nil -> {:reply, {:error, :usuario_no_registrado}, state}
          profile -> {:reply, {:ok, profile}, state}
        end
      else
        remote_node = server_to_node(tgt_server)
        try do
          result = GenServer.call({__MODULE__, remote_node}, {:internal_get_profile, target_id}, 5000)
          {:reply, result, state}
        catch
          :exit, _ -> {:reply, {:error, :servidor_remoto_inacesible}, state}
        end
      end
    else
      {:error, :formato_invalido} -> {:reply, {:error, :formato_id_invalido}, state}
      false -> {:reply, {:error, :usuario_no_registrado}, state}
    end
  end

  @impl true
  def handle_call({:post_message, sender_id, receiver_id, message}, _from, state) do
    with {:ok, sender_user, sender_server} <- parse_id(sender_id),
         true <- is_local_server?(sender_server),
         true <- user_exists?(state, sender_user),
         {:ok, tgt_user, tgt_server} <- parse_id(receiver_id) do

      if is_local_server?(tgt_server) do
        if user_exists?(state, tgt_user) do
          new_state = add_message(state, tgt_user, %{from: sender_id, text: message})
          {:reply, {:ok, :sent}, new_state}
        else
          {:reply, {:error, :usuario_no_registrado}, state}
        end
      else
        remote_node = server_to_node(tgt_server)
        try do
          result = GenServer.call({__MODULE__, remote_node}, {:internal_post_message, sender_id, receiver_id, message}, 5000)
          {:reply, result, state}
        catch
          :exit, _ -> {:reply, {:error, :servidor_remoto_inacesible}, state}
        end
      end
    else
      {:error, :formato_invalido} -> {:reply, {:error, :formato_id_invalido}, state}
      false -> {:reply, {:error, :usuario_no_registrado}, state}
    end
  end

  @impl true
  def handle_call({:retrieve_messages, user_id}, _from, state) do
    with {:ok, user, server} <- parse_id(user_id),
         true <- is_local_server?(server),
         true <- user_exists?(state, user) do
      {:reply, {:ok, Map.get(state.inboxes, user, [])}, state}
    else
      {:error, :formato_invalido} -> {:reply, {:error, :formato_id_invalido}, state}
      false -> {:reply, {:error, :usuario_no_registrado}, state}
    end
  end

  @impl true
  def handle_call({:internal_get_profile, target_id}, _from, state) do
    {:ok, tgt_user, _} = parse_id(target_id)
    case get_user(state, tgt_user) do
      nil -> {:reply, {:error, :usuario_no_registrado}, state}
      profile -> {:reply, {:ok, profile}, state}
    end
  end

  @impl true
  def handle_call({:internal_post_message, sender_id, receiver_id, message}, _from, state) do
    {:ok, recv_user, _} = parse_id(receiver_id)
    if user_exists?(state, recv_user) do
      new_state = add_message(state, recv_user, %{from: sender_id, text: message})
      {:reply, {:ok, :sent}, new_state}
    else
      {:reply, {:error, :usuario_no_registrado}, state}
    end
  end

  defp parse_id(id) do
    case String.split(id, "@") do
      [user, server] -> {:ok, user, server}
      _ -> {:error, :formato_invalido}
    end
  end

  defp is_local_server?(server_name), do: current_server_name() == server_name

  defp server_to_node(server_name) do
    host = Node.self() |> to_string() |> String.split("@") |> Enum.at(1) || "localhost"
    String.to_atom("#{server_name}@#{host}")
  end

  defp user_exists?(state, user), do: Map.has_key?(state.users, user)
  defp get_user(state, user), do: Map.get(state.users, user)

  defp add_message(state, user, message) do
    current = Map.get(state.inboxes, user, [])
    put_in(state.inboxes[user], [message | current])
  end
end
