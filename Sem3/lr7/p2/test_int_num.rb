require 'minitest/autorun'

require_relative 'int_num'

# IntNum tests
class TestIntNum < Minitest::Test
  POSITIVE = 42
  NEGATIVE = -228

  def setup
    @int_num_positive = IntNum.new POSITIVE
    @int_num_negative = IntNum.new NEGATIVE
  end

  def test_n_digits
    assert_equal 2, @int_num_positive.int_n_digits
    assert_equal 3, @int_num_negative.int_n_digits
  end

  def test_attr
    assert_equal POSITIVE, @int_num_positive.int
    assert_equal NEGATIVE, @int_num_negative.int
  end

  def test_do_puts
    assert_output(/#{POSITIVE.to_s}/) do
      @int_num_positive.do_puts
    end

    assert_output(/#{NEGATIVE.to_s}/) do
      @int_num_negative.do_puts
    end
  end

  def test_duck_init
    assert_equal 123, IntNum.new('123').int
  end
end
