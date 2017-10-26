require 'minitest/autorun'
require_relative 'part2_src'

# Tests for part2
class TestPart2 < MiniTest::Test
  def test_oborona
    assert_equal(
      fix_string('о-оо моя оборона'),
      'о-ое моя оборона'
    )
    assert_equal(
      fix_string('солнечный зайчик незрячего мира'),
      'солнечный зайчик тезрячеге мира'
    )
  end

  def test_commie
    assert_equal(
      fix_string('Он наступит скоро надо только подождать'),
      'Он таступит скоре таде тольке подождать'
    )
  end

  def test_empty
    assert_equal fix_string(''), ''
  end
end
