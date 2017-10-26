def calc_y(x, z)
  raise TypeError unless x.is_a?(Numeric) && z.is_a?(Numeric)
  (x**2 + 2 * Math.exp(x)) * Math.cos(6 * z.to_f / x - 5)
end
