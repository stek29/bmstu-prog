require 'minitest/autorun'

require_relative 'int_num'
require_relative 'multi_num'

# MultiNum tests
class TestMultiNum < Minitest::Test
  REAL = 13.37
  INT = 228

  def setup
    @number = MultiNum.new INT, REAL
  end

  def test_n_digits
    assert_equal 3, @number.int_n_digits
  end

  def test_attr
    assert_equal INT, @number.int
    assert_equal REAL, @number.real
  end

  def test_do_puts
    r_int = INT.to_s
    # real has '.' => should be quoted in regex
    r_real = Regexp.quote(REAL.to_s)
    # INT.*REAL or REAL.*INT
    regex = /(#{r_int}.*#{r_real}|#{r_real}.*#{r_int})/

    assert_output regex do
      @number.do_puts
    end
  end

  def test_duck_init
    number = MultiNum.new '123', '-14.3'
    assert_equal(123, number.int)
    assert_equal(-14.3, number.real)
  end

  def test_inheritance
    assert MultiNum < IntNum
  end
end
