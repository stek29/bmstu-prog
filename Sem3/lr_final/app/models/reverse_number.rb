class ReverseNumber < ApplicationRecord
  validate :m_int_valid

  private

  def m_int_valid
    if self.m_int.nil?
      errors.add :m_int, 'cannot be nil'
    elsif !self.m_int.positive?
      errors.add :m_int, 'must be positive'
    end
  end
end
