require 'minitest/autorun'
require_relative 'src'

# Tests for part3
class TestPart3 < MiniTest::Test
  def test_no_block
    assert_raises(ArgumentError) do
      minmax 0, 0
    end
  end

  def test_nil_fn
    assert_raises(ArgumentError) do
      minmax 0, 0, fn: nil
    end
  end

  def test_nil_fn_but_blk
    assert_equal([0, 0], minmax(0, 0) { |x| x })
  end

  def test_wrong_order
    assert_raises(ArgumentError) do
      minmax(5, 0) { |x| x }
    end
  end

  def test_negative_step
    assert_raises(ArgumentError) do
      minmax(0, 1, step: -1) { |x| x }
    end
  end

  def test_fn_blk_equal
    as_fn = minmax(0, 1, fn: ->(x) { x })
    as_blk = minmax(0, 1) { |x| x }

    assert_equal as_fn, as_blk
  end

  def test_sine_half
    f = ->(x) { Math.sin(x / 2) }

    act_min, act_max = minmax(0.5, 3.5, fn: f)

    assert_in_delta f.call(0.5), act_min
    assert_in_delta f.call(Math::PI), act_max
  end
end
