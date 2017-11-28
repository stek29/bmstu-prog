Rails.application.routes.draw do
  get 'bin_reverser/input'

  match 'bin_reverser/view', via: %i[get post]
end
