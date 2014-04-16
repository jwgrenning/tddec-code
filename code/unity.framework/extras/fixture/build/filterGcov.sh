#!/bin/bash
#---
# Excerpted from "Test-Driven Development for Embedded C",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material, 
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose. 
# Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
#---
INPUT_FILE=$1
TEMP_FILE1=${INPUT_FILE}1.tmp
TEMP_FILE2=${INPUT_FILE}2.tmp
TEMP_FILE3=${INPUT_FILE}3.tmp
ERROR_FILE=$2
OUTPUT_FILE=$3
HTML_OUTPUT_FILE=$3.html
TEST_RESULTS=$4

flattenGcovOutput() {
while read line1
do
  read line2
  echo $line2 " " $line1 
  read junk
  read junk
done < ${INPUT_FILE}
}

getRidOfCruft() {
sed '-e s/^Lines.*://g' \
    '-e s/^[0-9]\./  &/g' \
    '-e s/^[0-9][0-9]\./ &/g' \
    '-e s/of.*File/ /g' \
    "-e s/'//g" \
    '-e s/^.*\/usr\/.*$//g' \
    '-e s/^.*\.$//g' 
}

getFileNameRootFromErrorFile() {
sed '-e s/gc..:cannot open .* file//g' ${ERROR_FILE}
}

writeEachNoTestCoverageFile() {
while read line
do
  echo "  0.00%  " ${line}
done 
}

createHtmlOutput() {
    echo "<table border="2" cellspacing="5" cellpadding="5">"
    echo "<tr><th>Coverage</th><th>File</th></tr>"
    sed "-e s/.*%   /<tr><td>&<\/td><td>/" \
        "-e s/[a-zA-Z0-9_]*\.[ch][a-z]*/<a href='file:\.\/&.gcov'>&<\/a><\/td><\/tr>/" 
    echo "</table>"
    sed "-e s/.*/&<br>/g" < ${TEST_RESULTS}
}


flattenGcovOutput | getRidOfCruft  > ${TEMP_FILE1}
getFileNameRootFromErrorFile | writeEachNoTestCoverageFile > ${TEMP_FILE2}
cat ${TEMP_FILE1}  ${TEMP_FILE2} | sort | uniq > ${OUTPUT_FILE}
createHtmlOutput < ${OUTPUT_FILE} > ${HTML_OUTPUT_FILE}
rm -f ${TEMP_FILE1} ${TEMP_FILE2} 
