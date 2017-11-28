require 'test_helper'

class BinReverserControllerTest < ActionDispatch::IntegrationTest
  test "should get input" do
    get bin_reverser_input_url
    assert_response :success
  end
end
