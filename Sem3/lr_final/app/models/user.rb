class User < ApplicationRecord
  has_secure_password

  validates :username, presence: true, uniqueness: true

  validates :password, length: { in: 6..20 }

  def update_password(options)
    if self.authenticate options.delete(:old_password)
      self.update(options)
    else
      errors.add(:password)
      false
    end
  end
end
