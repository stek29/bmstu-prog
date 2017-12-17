require 'test_helper'

class UserFlowsTest < ActionDispatch::IntegrationTest
  include TestPasswordHelper

  test 'calc requires login' do
    post bin_reverser_view_path, params: { m: 42 }
    assert_redirected_to signin_path
  end

  test 'redirects to /signin from root' do
    get root_path
    assert_redirected_to signin_path
  end

  test 'can get root after sign in' do
    sign_in!

    get root_path
    assert_response :success
  end

  test 'should create users' do
    old_count = User.count
    post users_path, params: { user: { username: 'hey_now_you', password: 'are_an_all-star' } }
    new_count = User.count
    assert new_count > old_count
  end


  test 'gives different results for different n' do
    sign_in!

    get bin_reverser_view_path, params: {m: 6}
    resp_1 = response.body

    get bin_reverser_view_path, params: {m: 42}
    resp_2 = response.body

    assert_not_equal resp_1, resp_2
  end

  def sign_in!
    post '/sessions', params: { username: 'tan', password: default_password }
  end
end
