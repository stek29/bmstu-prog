Rails.application.routes.draw do
  root 'x_proxy#input'

  get 'x_proxy/input'

  match 'x_proxy/output', via: %i[get post]
end
