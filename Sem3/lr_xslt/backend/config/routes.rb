Rails.application.routes.draw do
  root 'bin_rev#index', via: %i[get post]
end
