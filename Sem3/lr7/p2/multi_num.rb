require_relative 'int_num'

# Class holding integer and real numbers
class MultiNum < IntNum
  attr_reader :real

  def initialize(int, real)
    super int
    @real = real.to_f
  end

  def to_s
    format('<MultiNum int:%d real:%f>', @int, @real)
  end
end
