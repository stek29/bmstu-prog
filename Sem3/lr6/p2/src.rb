def integrate_enum(start_x, end_x, n: 100, &blk)
  size = start_x - end_x
  raise ArgumentError, 'end_x > start_x' if size < 0

  iteration_cnt = 0

  Enumerator.new do |yielder|
    iteration_cnt += n
    yielder << [start_x.step(end_x, size / n).lazy.map(&blk).sum, iteration_cnt]
    n *= 2
  end
end

def integrate(start_x, end_x, n: 100, eps: 1e-5, &blk)
  integrate_enum(start_x, end_x, n: n, &blk)
    .lazy
    .each_cons(2)
    .drop_while { |prev, curr| (curr - prev).abs > eps }
    .first
end
