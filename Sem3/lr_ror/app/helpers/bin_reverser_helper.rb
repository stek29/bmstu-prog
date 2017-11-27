module BinReverserHelper
  def to_i_or_nil(str, base = 10)
    Integer(str, base)
  rescue ArgumentError
    nil
  end
end
