Rails.application.routes.draw do
  root 'bin_reverser#input'

  get 'bin_reverser/input'

  get 'bin_reverser/view'
end
