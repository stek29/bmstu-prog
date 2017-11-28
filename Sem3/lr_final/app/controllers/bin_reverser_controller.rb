class BinReverserController < ApplicationController
  include BinReverserHelper

  before_action :parse_params, only: :view

  def input; end

  def view
    @result = ReverseNumber.new(
      m_int: @m_int,
      m_bin: @m_int.to_s(2),
      n_bin: @m_int.to_s(2).reverse.to_i(2).to_s(2),
      n_int: @m_int.to_s(2).reverse.to_i(2)
    )
  end

  private

  def parse_params
    @m_int = to_i_or_nil(params[:m])
    error = if @m_int.nil?
               'M is not Integer'
             elsif !@m_int.positive?
               'M should be greater than zero'
             end
    unless error.nil?
      flash[:danger] = error
      redirect_to bin_reverser_input_url
    end
  end

end
