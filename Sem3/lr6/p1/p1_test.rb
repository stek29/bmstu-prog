require 'minitest/autorun'
require_relative 'src'

# Tests for part1
class TestPart1 < MiniTest::Test
  def test_no_block
    assert_raises(LocalJumpError) { integrate(0, 5) }
  end

  def test_wrong_order
    assert_raises(ArgumentError) { integrate(10, 0) { |x| x } }
  end

  def test_eps
    exact_value = Math.log(2)**2 / 2
    func = ->(x) { Math.log(x) / x }

    assert_in_delta integrate(1, 2, eps: 1e-4, &func)[0], exact_value, 1e-2
    assert_in_delta integrate(1, 2, eps: 1e-6, &func)[0], exact_value, 1e-4
  end
end
