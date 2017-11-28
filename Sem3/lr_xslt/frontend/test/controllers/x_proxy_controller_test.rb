require 'test_helper'

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
    get x_proxy_output_url, render_at: 'server', m: 10
    resp_1 = response.parsed_body

    get x_proxy_output_url, render_at: 'server', m: 20
    resp_2 = response.parsed_body

    assert_not_equal resp_1, resp_2
  end
end
