defmodule FederationTest do
  use ExUnit.Case
  doctest Federation

  test "greets the world" do
    assert Federation.hello() == :world
  end
end
