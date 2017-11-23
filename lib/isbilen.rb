module Isbilen
  VERSION = '0.3.0'.freeze

  def to_time(snowflake)
    Time.at(seconds(snowflake), microsec(snowflake))
  end
end

require 'isbilen/isbilen'
