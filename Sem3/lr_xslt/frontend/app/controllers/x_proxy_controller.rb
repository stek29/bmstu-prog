require 'open-uri'

class XProxyController < ApplicationController
  include XProxyHelper

  before_action :parse_params, only: :output
  before_action :validate_params, only: :output

  def input
    @renderers = RENDERERS
  end

  def output
    xml = open make_url(@m_int)

    case @renderer
    when :client
      render xml: insert_xslt_instruction(xml).to_xml
    when :raw
      render xml: xml
    when :server
      @result = apply_xslt_transform(xml).to_html
    end
  end

  private

  RENDERERS = {
    client: 'Client-side XSLT',
    server: 'Server-side XSLT',
    raw: 'Passthrough'
  }.freeze

  def parse_params
    @m_int = params[:m]
    @renderer =  params[:render_at].to_s.to_sym
  end

  def validate_params
    err = if @m_int.nil?
            'm_int is missing'
          elsif !RENDERERS.keys.include? @renderer
            "Invalid renderer: #{@renderer}"
          end

    unless err.nil?
      flash[:danger] = err
      redirect_to x_proxy_input_url
    end
  end
end
