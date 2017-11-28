require 'test_helper'
require 'nokogiri'

class XProxyControllerTest < ActionDispatch::IntegrationTest
  test 'should get input' do
    get x_proxy_input_url
    assert_response :success
  end

  test 'should redirect with invalid params' do
    get x_proxy_output_url
    assert_redirected_to x_proxy_input_url
  end

  test 'should generate different pages for different m' do
    get x_proxy_output_url, params: { render_at: 'server', m: 10 }
    resp_1 = response.parsed_body

    get x_proxy_output_url, params: { render_at: 'server', m: 20 }
    resp_2 = response.parsed_body

    assert_not_equal resp_1, resp_2
  end

  test 'should return XML with raw renderer' do
    get x_proxy_output_url, params: { render_at: 'raw', m: 42 }
    xml = Nokogiri::XML(response.parsed_body)
    n_int_x = xml.xpath('//num-n/int')
    assert_match /21/, n_int_x.inner_html
  end

  test 'should return html with server renderer' do
    get x_proxy_output_url, params: { render_at: 'server', m: 42 }
    assert_select '#m-int', /42/
    assert_select '#n-int', /21/
  end
end
