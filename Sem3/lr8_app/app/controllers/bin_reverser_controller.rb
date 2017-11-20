class BinReverserController < ApplicationController
  def input
    # nothing interesting in inputg
  end

  def view
    redirect_to bin_reverser_input_url unless params[:m]

    @m_i = params[:m].to_i

    @m_bin_str = @m_i.to_s 2
    @n_bin_str = @m_bin_str.reverse
    @n_i = @n_bin_str.to_i 2
  end
end
