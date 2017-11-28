Rails.application.routes.draw do
  root 'bin_reverser#input'

  get 'bin_reverser/input'

  match 'bin_reverser/view', via: %i[get post]

  get 'bin_reverser/dump_all'
end
