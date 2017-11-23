require 'bundler/gem_tasks'
require 'rspec/core/rake_task'

require 'rake/extensiontask'

Rake::ExtensionTask.new 'isbilen' do |ext|
  ext.lib_dir = 'lib/isbilen'
end

RSpec::Core::RakeTask.new(:spec)

require 'rubocop/rake_task'
RuboCop::RakeTask.new(:spec)

task default: :spec
