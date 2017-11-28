class ReverseNumber < ApplicationRecord
  include ActiveModel::Serializers::Xml

  validate :m_int_valid

  before_create do
    return unless self.m_int.is_a? Integer
    return if self.n_int.is_a? Integer

    self.m_bin = self.m_int.to_s 2
    self.n_int = self.m_bin.reverse.to_i 2
    self.n_bin = self.n_int.to_s 2
  end

  private

  def m_int_valid
    if self.m_int.nil?
      errors.add :m_int, 'cannot be nil'
    elsif !self.m_int.positive?
      errors.add :m_int, 'must be positive'
    end
  end
end
