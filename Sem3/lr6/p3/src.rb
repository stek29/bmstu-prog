def minmax(a, b, step: 0.01, fn: nil, &blk)
  # select first proc
  fn = [fn, blk].find { |x| x.respond_to? :call }
  raise ArgumentError, 'No fn or block given!' if fn.nil?

  a, b, step = [a, b, step].map(&:to_f)
  raise ArgumentError, 'a must be <= b' if a > b
  raise ArgumentError, 'step must be > 0' if step <= 0

  a.step(b, step).lazy.map(&fn).minmax
end