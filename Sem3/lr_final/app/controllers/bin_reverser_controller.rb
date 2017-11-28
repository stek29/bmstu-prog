class BinReverserController < ApplicationController
  include BinReverserHelper

  before_action :parse_params, only: :view

  def input; end

  def view
    found = ReverseNumber.find_by(m_int: @m_int)

    created = ReverseNumber.create(make_n_m(@m_int)) if found.nil?

    if found.nil? && !created.valid?
      flash[:errors] = created.errors.messages
      redirect_to bin_reverser_input_url and return
    end

    @result = found || created
    @was_found = !found.nil?
  end

  private

  def parse_params
    @m_int = to_i_or_nil(params[:m])
  end

end
