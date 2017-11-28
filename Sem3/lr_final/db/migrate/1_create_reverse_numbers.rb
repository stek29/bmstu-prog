class CreateReverseNumbers < ActiveRecord::Migration[5.1]
  def change
    create_table(:reverse_numbers,
                 id: false,
                 primary_key: :m_int
                ) do |t|
      t.integer :m_int
      t.string :m_bin
      t.integer :n_int
      t.string :n_bin
    end
  end
end
