require 'spec_helper'

describe Isbilen do
  it 'has a version number' do
    expect(described_class::VERSION).not_to be nil
  end

  context 'snowflake method' do
    it 'exists' do
      expect(described_class.respond_to?('snowflake')).to eq(true)
    end
    it 'and requires integer' do
      expect { described_class.snowflake('a-string') }.to raise_error(TypeError)
    end
  end

  it 'has a valid? method' do
    expect(described_class.respond_to?('valid?')).to eq(true)
  end

  it 'has a seconds method' do
    expect(described_class.respond_to?('seconds')).to eq(true)
  end

  it 'has a microsec method' do
    expect(described_class.respond_to?('microsec')).to eq(true)
  end

  it 'has a instance_id method' do
    expect(described_class.respond_to?('instance_id')).to eq(true)
  end

  it 'has a version method' do
    expect(described_class.respond_to?('version')).to eq(true)
  end

  context 'Snowflake' do
    let(:instance_id) { 823_764 }
    let(:snowflake) { described_class.snowflake(instance_id) }

    it 'is a valid snowflake' do
      expect(described_class.valid?(snowflake)).to be true
    end

    it 'is version 1' do
      expect(described_class.version(snowflake)).to eq 0
    end

    it 'keeps instance_id safe' do
      expect(described_class.instance_id(snowflake)).to eq instance_id
    end

    it 'has a timestamp within a second from now' do
      expect((described_class.seconds(snowflake) - Time.now.to_i).abs).to be < 2
    end
  end
end
