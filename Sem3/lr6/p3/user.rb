require_relative 'src'

puts 'minmax for (x-1)/(x+2) on [0, 2]:'
puts minmax(0, 2) { |x| (x - 1) / (x + 2) }

puts 'minmax for sin(x/2 - 1) on [-1, 1]:'
puts minmax(-1, 1, fn: ->(x) { Math.sin(x / 2 - 1) } )