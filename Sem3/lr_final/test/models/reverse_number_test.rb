require 'test_helper'

class ReverseNumberTest < ActiveSupport::TestCase
  test 'should not allow duplicates' do
    orig = ReverseNumber.create(m_int: 15)

    assert_raises ActiveRecord::RecordNotUnique do
      ReverseNumber.create(m_int: 15)
    end
  end

  test 'should find after creation' do
    created = ReverseNumber.find_or_create_by(m_int: 42)
    found = ReverseNumber.find_by(m_int: 42)

    assert_not found.nil?
    assert_equal created.n_int, found.n_int
  end

  test 'does not allow invalid m' do
    assert_not ReverseNumber.create(m_int: -33).valid?
  end

  test 'gives correct results' do
    x90 = ReverseNumber.find_or_create_by(m_int: 90)
    assert_equal x90.n_int, 45
  end
end
