require 'icecrystal/version'
require 'icecrystal/icecrystal'

include Icecrystal

# Why rubocop, why :cry:
module Icecrystal
  def to_time(snowflake)
    Time.at(seconds(snowflake), microsec(snowflake))
  end
end
