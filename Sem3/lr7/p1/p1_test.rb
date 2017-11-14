require 'minitest/autorun'
require 'stringio'

require_relative 'src'

# Test for string filtering function
class TestStrFilter < MiniTest::Test
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

# Tests for file filtering function
class TestFileFilter < MiniTest::Test
  def test_oneline
    f_file = StringIO.new('alas', 'r')
    h_file = StringIO.new('', 'w')

    filter_file(f_file, h_file)

    assert_equal 'ls', h_file.string.chomp
  end
end
