require_relative 'part2_src'

if $PROGRAM_NAME == __FILE__
  puts 'Вводите строки, разделяя слова пробелами'
  puts 'Введите пустую строку для завершения ввода'

  arr = []

  loop do
    line = gets.to_s.chomp
    break if line.empty?
    arr.push(line)
  end

  puts 'Исходные строки:'
  arr.each { |line| puts line }

  puts 'Скорректированные строки:'
  arr.each { |line| puts fix_string(line) }
end
