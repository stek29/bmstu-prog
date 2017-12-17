Rails.application.routes.draw do
  get 'sessions/new'

  resources :users
  resource :sessions, only: %i[new create destroy]

  get 'signup', to: 'users#new', as: 'signup'
  get 'signin', to: 'sessions#new', as: 'signin'
  get 'signout', to: 'sessions#destroy', as: 'signout'

  root 'bin_reverser#input'

  get 'bin_reverser/input'
  match 'bin_reverser/view', via: %i[get post]
  get 'bin_reverser/dump_all'
end
