class ApplicationController < ActionController::Base
  protect_from_forgery with: :exception

  private

  def logged_in?
    !current_user.nil?
  end

  def current_user
    @current_user ||= User.find(session[:user_id]) if session[:user_id]
  end

  def require_login
    unless logged_in?
      flash[:login] = 'Please log in'
      redirect_to signin_path
    end
  end

  helper_method :logged_in?, :current_user, :require_login
end
