class BinRevController < ApplicationController
  include BinRevHelper

  before_action :check_params, only: :index

  def index
    result = if @error.nil?
               make_n_m(@m_int)
             else
               { error: @error }
             end
    respond_to do |format|
      format.xml { render xml: result.to_xml }
      format.rss { render xml: result.to_xml }
    end
  end

  protected

  def check_params
    @m_int = to_i_or_nil(params[:m])
    @error = if @m_int.nil?
               'M is not Integer'
             elsif !@m_int.positive?
               'M should be greater than zero'
             end
  end
end
