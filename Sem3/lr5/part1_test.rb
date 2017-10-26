require 'minitest/autorun'
require_relative 'part1_src'

# Tests for part1
class TestPart1 < MiniTest::Test
  def test_not_numeric
    assert_raises(TypeError) { calc_y 'The answer', 42 }

    assert_raises(TypeError) { calc_y 1337, %w[l e e t] }
  end

  def test_valid
    assert_in_delta calc_y(5, 6), -189.39, 0.01
    assert_in_delta calc_y(1.2, 3.4), 6.818, 0.001
  end

  def test_zero_div
    assert calc_y(0, 0).nan?
  end
end
