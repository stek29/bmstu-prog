def filter_by_prev_char(s, prev = 'a')
  s.chars.each_cons(2).map do |p, c|
    c if p == prev
  end.compact.join
end

def filter_file(f_file, h_file, filter_prev_char = 'a')
  f_file.each_line do |line|
    h_file.puts filter_by_prev_char(line, filter_prev_char)
  end
end