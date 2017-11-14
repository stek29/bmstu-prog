class BinReverserController < ApplicationController
  def input
    # nothing interesting in input
  end

  def view
    redirect_to bin_reverser_input_url unless params[:m]

    @m_i = params[:m].to_i
    @n_i = @m_i.to_s(2).reverse.to_i(2)
  end
end
