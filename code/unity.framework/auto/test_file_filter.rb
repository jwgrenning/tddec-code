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

require'yaml'

module RakefileHelpers
  class TestFileFilter
    def initialize(all_files = false)
      @all_files = all_files
      if not @all_files == true
        if File.exist?('test_file_filter.yml')
          filters = YAML.load_file( 'test_file_filter.yml' )
          @all_files, @only_files, @exclude_files = 
            filters[:all_files], filters[:only_files], filters[:exclude_files] 
        end
      end
    end		
    attr_accessor :all_files, :only_files, :exclude_files
  end
end
