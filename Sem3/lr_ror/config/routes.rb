Rails.application.routes.draw do
  root 'bin_reverser#input'

  get 'bin_reverser/input'

  match 'bin_reverser/view', via: %i(get post)
end
