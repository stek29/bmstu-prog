require 'test_helper'

class BinRevControllerTest < ActionDispatch::IntegrationTest
  test 'calculates n correctly' do
    get '/', params: {format: 'xml', m: 1337}
    assert_match /1253/, response.parsed_body
  end

  test 'gives different results for different n' do
    get '/', params: {format: 'xml', m: 6}
    resp_1 = response.parsed_body

    get '/', params: {format: 'xml', m: 42}
    resp_2 = response.parsed_body

    assert_not_equal resp_1, resp_2
  end
end
