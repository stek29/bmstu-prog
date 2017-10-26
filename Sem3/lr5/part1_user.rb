require_relative 'part1_src'

if $PROGRAM_NAME == __FILE__
  loop do
    puts 'Введите X и Z: '
    x, z, * = gets.chomp.split.map(&:to_f)
    puts calc_y(x, z)
  end
end
