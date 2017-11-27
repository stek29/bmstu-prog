module BinRevHelper
  def make_n_m(m_int)
    m_bin = m_int.to_s 2
    n_bin = m_bin.reverse
    n_int = n_bin.to_i 2

    {
      num_m: { int: m_int, bin: m_bin },
      num_n: { int: n_int, bin: n_bin }
    }
  end

  def to_i_or_nil(str, base = 10)
    Integer(str, base)
  rescue ArgumentError
    nil
  end
end
