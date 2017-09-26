# Morse Converter

This project uses a binary search tree to store each letter of the alphabet in morse code
by reading it from an existing file, "MorseText.txt".
The tree is then used to translate each sentence that is read from file "Convert.txt". 
The time complexity is generally low (NlogN) because we are using a binary search tree that has
a search time complexity of O(logN).
