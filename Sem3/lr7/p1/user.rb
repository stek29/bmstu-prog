require_relative 'src'

H_FILENAME = 'h.txt'.freeze
F_FILENAME = 'f.txt'.freeze

h_file = File.open(H_FILENAME, 'w')

File.new(F_FILENAME).each_line do |line|
  h_file.puts filter_by_prev_char(line)
end

h_file.close
