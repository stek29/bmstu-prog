def filter_by_prev_char(s, prev = 'a')
  s.chars.each_cons(2).map do |p, c|
    c if p == prev
  end.compact.join
end
