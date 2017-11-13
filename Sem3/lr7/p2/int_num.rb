# Class holding integer number
class IntNum
  attr_reader :int

  def initialize(num)
    @int = num.to_i
  end

  def do_puts
    puts self
  end

  def int_n_digits
    @int.abs.to_s.size
  end

  def to_s
    format('<IntNum %d>', @int)
  end
end
