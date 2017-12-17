class UsersController < ApplicationController
  before_action :require_login, except: %i[new create]
  before_action :set_current_user, only: %i[destroy show edit update]

  def new
    @user = User.new
  end

  def create
    @user = User.new(allowed_params)
    if @user.save
      session[:user_id] = @user.id
      redirect_to root_url, notice: 'Thank you for signing up!'
    else
      render :new
    end
  end

  def destroy
    @user.destroy
    session[:user_id] = nil
    redirect_to root_url, notice: 'User was deleted'
  end

  def update
    permitted = params.require(:user)
                      .permit(:password, :password_confirmation, :old_password)

    if @user.update_password(permitted)
      redirect_to users_url, notice: 'Password changed successfully'
    else
      render :edit
    end
  end

  def show; end

  def edit; end

  private

  def allowed_params
    params.require(:user).permit(:username, :password, :password_confirmation)
  end

  def set_current_user
    @user = current_user
  end
end
