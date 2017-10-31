require_relative 'src'

if $PROGRAM_NAME == __FILE__
  def user_integrate(start_x, end_x, eps, &func)
    puts "Eps is #{eps}"
    value, iteration_cnt = integrate(start_x, end_x, eps: eps, &func)
    puts "∫f = #{value} – calculated in #{iteration_cnt} iterations"
  end

  f_x = ->(x) { Math.log(x) / x }
  user_integrate 1, 2, 1e-2, &f_x
  user_integrate 1, 2, 1e-3, &f_x
  user_integrate 1, 2, 1e-4, &f_x
end
