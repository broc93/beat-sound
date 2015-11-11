# beat-sound
Beats synthetizer with C++ and SFML library. Generates two sinusoidal sound waves with slightly different frequency

Asks the user to insert the two frequencies of the file to be generated.
Creates an array (with 44100 samples/sec) of the amplitude of the sum of the two sinusoidal waves.
Using SFML library reproduces the sound in loop, with a 100ms sleep between each run.
