class BinReverserController < ApplicationController
  def input
    # nothing interesting in input
  end

  def view
    m_int = params[:m].to_i
    redirect_to bin_reverser_input_url if m_int.nil?
    m_bin = m_int.to_s 2
    n_bin = m_bin.reverse

    @num_m = { int: m_int, bin_str: m_bin }
    @num_n = { int: n_bin.to_i(2), bin_str: n_bin }

    respond_to do |format|
      format.html
      format.json { render json: { num_m: @num_m, num_n: @num_n } }
    end
  end
end
