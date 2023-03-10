# Testscript used to test each of the programs in "assignment_1".

echo
echo "Calling the Makefile to compile all of the modules"
make

echo "---------------------------------------------------------------"

echo
echo "Test 1, pgmEcho: Valid input file and valid output file"
echo "./pgmEcho slice0a.pgm slice1a.pgm"
./pgmEcho slice0a.pgm slice1a.pgm
echo "Return value: $?"
rm slice1a.pgm

echo
echo "Test 2, pgmEcho: No arguments input"
echo "./pgmEcho"
./pgmEcho
echo "Return value: $?"

echo
echo "Test 3, pgmEcho: One argument supplied"
echo "./pgmEcho slice0a.pgm"
./pgmEcho slice0a.pgm
echo "Return value: $?"

echo
echo "Test 4, pgmEcho: Three arguments supplied"
echo "./pgmEcho slice0a.pgm slice1a.pgm slice2a.pgm"
./pgmEcho slice0a.pgm slice1a.pgm slice2a.pgm
echo "Return value: $?"

echo "---------------------------------------------------------------"

echo
echo "Test 5, pgmRead: Inputting a file that doesn't exist"
echo "./pgmEcho image0a.pgm image1a.pgm"
./pgmEcho image0a.pgm image1a.pgm
echo "Return value: $?"

echo
echo "Test 6, pgmRead: Inputting a file with an out of bounds width value"
echo "./pgmEcho slice0a_bad_width.pgm slice1a.pgm"
./pgmEcho slice0a_bad_width.pgm slice1a.pgm
echo "Return value: $?"

echo
echo "Test 7, pgmRead: Inputting a file with an out of bounds height value"
echo "./pgmEcho slice0a_bad_height.pgm slice1a.pgm"
./pgmEcho slice0a_bad_height.pgm slice1a.pgm
echo "Return value: $?"

echo
echo "Test 8, pgmRead: Inputting a file with a bad max gray value"
echo "./pgmEcho slice0a_bad_maxGray.pgm slice1a.pgm"
./pgmEcho slice0a_bad_maxGray.pgm slice1a.pgm
echo "Return value: $?"

echo "---------------------------------------------------------------"

echo
echo "Test 9, pgmComp: Valid input files that are identical"
echo "./pgmComp slice0a.pgm sliceDifferent.pgm"
./pgmEcho slice0a.pgm sliceIdentical.pgm
echo "Return value: $?"

echo
echo "Test 10, pgmComp: Valid input files that are different"
echo "./pgmComp slice0a.pgm sliceDifferent.pgm"
./pgmEcho slice0a.pgm sliceDifferent.pgm
echo "Return value: $?"

echo
echo "Test 11, pgmComp: No arguments input"
echo "./pgmComp"
./pgmComp
echo "Return value: $?"

echo
echo "Test 12, pgmComp: One argument supplied"
echo "./pgmComp slice0a.pgm"
./pgmComp slice0a.pgm
echo "Return value: $?"

echo
echo "Test 13, pgmComp: Three arguments supplied"
echo "./pgmComp slice0a.pgm slice1a.pgm slice2a.pgm"
./pgmComp slice0a.pgm slice1a.pgm slice2a.pgm
echo "Return value: $?"

echo "---------------------------------------------------------------"

echo
echo "Test 14, pgma2b: Valid input file and valid output file"
echo "./pgma2b slice0a.pgm slice0b.pgm"
./pgma2b slice0a.pgm slice0b.pgm
echo "Return value: $?"
rm slice0b.pgm

echo
echo "Test 15, pgmb2a: Valid input file and valid output file"
echo "./pgmb2a baboon.pgm baboonAscii.pgm"
./pgmb2a baboon.pgm baboonAscii.pgm
echo "Return value: $?"
rm baboonAscii.pgm

echo "---------------------------------------------------------------"

echo
echo "Calling the Makefile to clean all of the object files"
make clean