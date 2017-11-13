require 'minitest/autorun'
require_relative 'src'

# Tests for lr7p1
class TestCharFilter < MiniTest::Test
  def test_a
    assert_equal 'l', (filter_by_prev_char 'lala')
  end

  def test_not_a
    assert_equal 'doge', (filter_by_prev_char 'xdxoxgxe', 'x')
  end

  def test_repeat
    assert_equal 'aa', (filter_by_prev_char 'aaa')
  end

  def test_newline
    assert_equal "\nb", (filter_by_prev_char "a\nab")
  end
end
