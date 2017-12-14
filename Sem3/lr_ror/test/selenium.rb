require "json"
require "selenium-webdriver"
require "rspec"
include RSpec::Expectations

describe "Test lab" do

  before(:each) do
    @driver = Selenium::WebDriver.for :chrome
    @accept_next_alert = true
    @driver.manage.timeouts.implicit_wait = 30
    @verification_errors = []
  end
  
  after(:each) do
    @driver.quit
    expect(@verification_errors).to be_empty
  end
  
  it "returns n=21 for m=42" do
    @driver.get "http://localhost:3000/bin_reverser/input"
    @driver.find_element(:id, "m").clear
    @driver.find_element(:id, "m").send_keys "42"
    @driver.find_element(:name, "commit").click
    !60.times{ break if (@driver.find_element(:id, "n").text == "21" rescue false); sleep 1 }
  end

  it "returns error on negative m" do
    @driver.get "http://localhost:3000/bin_reverser/input"
    @driver.find_element(:id, "m").clear
    @driver.find_element(:id, "m").send_keys "-60"
    @driver.find_element(:name, "commit").click
    !60.times{ break if (@driver.find_element(:id, "status").text == "Error!" rescue false); sleep 1 }
  end
end
