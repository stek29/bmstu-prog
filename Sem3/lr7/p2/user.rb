require_relative 'int_num'
require_relative 'multi_num'

puts 'Enter int for IntNum:'
i_num = IntNum.new gets.chomp
i_num.do_puts
puts format('i_num.int value: %d', i_num.int)
puts format('Number of digits: %d', i_num.int_n_digits)

puts 'Enter int and real for MultiNum:'
m_num = MultiNum.new(*gets.chomp.split)
m_num.do_puts
puts format('m_num.int value: %d', m_num.int)
puts format('m_num.real value: %f', m_num.real)
puts format('Number of digits: %d', i_num.int_n_digits)
