require "spec_helper"

describe Icecrystal do
  it "has a version number" do
    expect(Icecrystal::VERSION).not_to be nil
  end

  it "has a snowflake method" do
    expect(Icecrystal::respond_to?('snowflake')).to eq(true)
  end
end
