require 'test_helper'

class BinReverserControllerTest < ActionController::TestCase
  test 'should get input' do
    get bin_reverser_input_url
    assert_response :success
  end

  test 'should redirect to input if m is missing' do
    get bin_reverser_view_url
    assert_redirected_to bin_reverser_input_url
  end

  test 'should get view' do
    get bin_reverser_view_url, params: { m: 15 }
    assert_response :success
  end

  test 'should return correct answer' do
    get bin_reverser_view_url, params: { m: 42 }

    assert_select '#m', /42/
    assert_select '#m_bin', /0*#{42.to_s(2)}/

    assert_select '#n', /21/
    assert_select '#n_bin', /0*#{21.to_s(2)}/
  end
end
