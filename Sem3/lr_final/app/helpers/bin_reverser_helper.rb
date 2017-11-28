module BinReverserHelper
  def to_i_or_nil(str, base = 10)
    Integer(str, base)
  rescue ArgumentError
    nil
  end

  def make_n_m(m_int)
    return {} unless m_int.is_a? Integer

    m_bin = m_int.to_s 2
    n_int = m_bin.reverse.to_i 2
    n_bin = n_int.to_s 2

    {
      m_int: m_int, m_bin: m_bin,
      n_int: n_int, n_bin: n_bin
    }
  end

end
