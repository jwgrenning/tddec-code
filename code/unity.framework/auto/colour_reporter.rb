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

require "#{File.expand_path(File.dirname(__FILE__))}/colour_prompt"

$colour_output = true

def report(message)
  if not $colour_output
    $stdout.puts(message)
  else
    message = message.join('\n') if (message.class == Array)
    message.each_line do |line|
      line.chomp!
      colour = case(line)
        when /(?:total\s+)?tests:?\s+(\d+)\s+(?:total\s+)?failures:?\s+\d+\s+Ignored:?/i
          ($1.to_i == 0) ? :green : :red
        when /PASS/
          :green
        when /^OK$/
          :green
        when /(?:FAIL|ERROR)/
          :red
        when /IGNORE/
          :yellow
        when /^(?:Creating|Compiling|Linking)/
          :white
        else
          :silver
      end
      colour_puts(colour, line)
    end
  end
  $stdout.flush
  $stderr.flush
end