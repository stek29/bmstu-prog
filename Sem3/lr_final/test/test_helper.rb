require File.expand_path('../../config/environment', __FILE__)
require 'rails/test_help'
require_relative 'support/test_password_helper'

class ActiveSupport::TestCase
  # Setup all fixtures in test/fixtures/*.yml for all tests in alphabetical order.
  fixtures :all

  # Add more helper methods to be used by all tests here...
end

ActiveRecord::FixtureSet.context_class.send :include, TestPasswordHelper
