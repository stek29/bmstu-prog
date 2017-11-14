# rubocop:disable Metrics/MethodLength, Metrics/AbcSize

def integrate(start_x, end_x, initial_n: 100, eps: 1e-5)
  start_x = start_x.to_f
  end_x = end_x.to_f
  dist = end_x - start_x

  raise ArgumentError, 'end_x > start_x' if dist < 0

  curr = Float::NAN
  n = initial_n
  iteration_cnt = 0

  loop do
    prev = curr
    curr = 0
    curr_x = start_x
    step = dist / n

    n.times do
      curr += yield curr_x
      curr_x += step
    end
    curr *= step

    iteration_cnt += n

    break if (curr - prev).abs < eps

    n += initial_n
  end

  [curr, iteration_cnt]
end
