class UsersController < ApplicationController
  before_action :require_login, except: %i[new create]
  before_action :set_user, only: %i[destroy show edit update]
  before_action :validate_edit, only: %i[destroy edit update]

  def new
    @user = User.new
  end

  def create
    @user = User.new(allowed_params)
    if @user.save
      session[:user_id] = @user.id
      redirect_to root_path, notice: 'Thank you for signing up!'
    else
      render :new
    end
  end

  def destroy
    session[:user_id] = nil if same_user
    @user.destroy
    redirect_to root_path, notice: 'User was deleted'
  end

  def update
    permitted = params.require(:user)
                      .permit(:password, :password_confirmation, :old_password)

    if @user.update_password(permitted)
      redirect_to @user, notice: 'Password changed successfully'
    else
      render :edit
    end
  end

  def show; end

  def edit; end

  def index
    @users = User.all
  end

  private

  def allowed_params
    params.require(:user).permit(:username, :password, :password_confirmation)
  end

  def set_user
    @current_user = current_user
    @user = User.find(params[:id])
  end

  def validate_edit
    unless same_user
      redirect_to users_path, notice: "You're not allowed to edit this user"
    end
  end

  helper_method :same_user

  def same_user
    @user == @current_user
  end
end
