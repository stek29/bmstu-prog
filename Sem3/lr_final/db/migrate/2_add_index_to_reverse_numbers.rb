class AddIndexToReverseNumbers < ActiveRecord::Migration[5.1]
  def change
    add_index :reverse_numbers, :m_int, unique: true
  end
end
