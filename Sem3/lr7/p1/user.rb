require_relative 'src'

H_FILENAME = 'h.txt'.freeze
F_FILENAME = 'f.txt'.freeze

printf 'Create file F? [yN] '
if gets.chomp.casecmp('y').zero?
  puts 'Enter file F contents'
  File.open(F_FILENAME, 'w') do |f_file|
    loop do
      line = gets.to_s.chomp
      break if line.empty?
      f_file.puts line
    end
  end
end

h_file = File.open(H_FILENAME, 'w')

filter_file File.new(F_FILENAME), h_file

h_file.close

puts "\nFile F:"
File.new(F_FILENAME).each_line { |l| puts l }

puts "\nFile H:"
File.new(H_FILENAME).each_line { |l| puts l }
