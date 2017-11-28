class BinReverserController < ApplicationController
  include BinReverserHelper

  before_action :parse_params, only: :view

  def input; end

  def view
    @result = ReverseNumber.find_or_create_by(m_int: @m_int)

    unless @result.valid?
      flash[:errors] = @result.errors.messages
      redirect_to bin_reverser_input_url
    end
  end

  private

  def parse_params
    @m_int = to_i_or_nil(params[:m])
  end

end
