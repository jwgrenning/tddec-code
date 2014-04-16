#---
# Excerpted from "Test-Driven Development for Embedded C",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material, 
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose. 
# Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
#---
# ==========================================
#   Unity Project - A Test Framework for C
#   Copyright (c) 2007 Mike Karlesky, Mark VanderVoord, Greg Williams
#   [Released under MIT License. Please refer to license.txt for details]
# ========================================== 

HERE = File.expand_path(File.dirname(__FILE__)) + '/'

require 'rake'
require 'rake/clean'
require 'rake/testtask'
require HERE + 'rakefile_helper'

include RakefileHelpers

# Load default configuration, for now
DEFAULT_CONFIG_FILE = 'gcc.yml'
configure_toolchain(DEFAULT_CONFIG_FILE)

desc "Test unity with it's own unit tests"
task :unit do
  run_tests get_unit_test_files
end

Rake::TestTask.new(:scripts) do |t|
  t.pattern = 'test/test_*.rb'
  t.verbose = true
end

desc "Generate test summary"
task :summary do
  report_summary
end

desc "Build and test Unity"
task :all => [:clean, :scripts, :unit, :summary]
task :default => [:clobber, :all]
task :ci => [:no_color, :default]
task :cruise => [:no_color, :default]

desc "Load configuration"
task :config, :config_file do |t, args|
  configure_toolchain(args[:config_file])
end

task :no_color do
  $colour_output = false
end
