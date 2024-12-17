// Kelton
// Program Project 4 - Passphrase Generator

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Random;
import java.util.Scanner;

class WordBank {
    private ArrayList<String> wordBank; // stores the word bank
    private HashMap<Integer, Integer> wordsOfSizes; // stores the amount of words of each size
    private HashSet<Integer> wordSizes; // stores the sizes of words stored, as specified in rubric
    private Random randGen; // used to randomly pull from word bank

    /*
     * Loads a line deliminated text file by filename into the word bank
     * Only loads words of a specified length, unless -1 is specified as length
     * @param fileName String filename to read from
     * @param wordSize length of words to include, or -1 to include all words
     */
    private void loadFile(String fileName, int wordSize) throws FileNotFoundException {
        FileInputStream fbInputStream = new FileInputStream(fileName);
        Scanner scnr = new Scanner(fbInputStream);

        while (scnr.hasNextLine()) { // while there are lines
            if (wordSize == -1) { // if we're accepting all words, simply add it to the list
                String word = scnr.nextLine();
                wordBank.add(word); // add word to bank

                wordSizes.add(word.length()); // add word size to HashSet

                // if the word length already exists in the hash map, increment it
                // otherwise, set it to 1
                if (wordsOfSizes.containsKey(word.length())) {
                    wordsOfSizes.put(word.length(), (int)wordsOfSizes.get(word.length()) + 1);
                } else {
                    wordsOfSizes.put(word.length(), 1);
                }
            } else { // otherwise, check that it's the desired size
                String word = scnr.nextLine();
                if (word.length() == wordSize) { // only if word is of proper size
                    wordBank.add(word); // add word to bank

                    wordSizes.add(word.length()); // add word size to HashSet

                    // if the word length already exists in the hash map, increment it
                    // otherwise, set it to 1
                    if (wordsOfSizes.containsKey(word.length())) {
                        wordsOfSizes.put(word.length(), (int)wordsOfSizes.get(word.length()) + 1);
                    } else {
                        wordsOfSizes.put(word.length(), 1);
                    }
                }
            }
        }

        scnr.close();
    }

    /*
     * Constructs a WordBank object with a given filename and word size
     * @param fileName String name of the file to read words from
     * @param wordSize integer length of words to include, or -1 to include all words
     */
    public WordBank(String fileName, int wordSize) throws FileNotFoundException {
        wordsOfSizes = new HashMap<Integer, Integer>();
        wordSizes = new HashSet<Integer>(); // the hashset is unnecessary, as you can check for the presence of a key in the hashmap, but the rubric specifies a hashset specifically so i've used one as well
        randGen = new Random();
        wordBank = new ArrayList<String>();

        if (wordSize <= 0) { // coerce all invalid word sizes into -1
            wordSize = -1;
        }

        loadFile(fileName, wordSize);
    }

    /*
     * Constructs a WordBank object with the given filename including all words of all sizes
     * @param fileName String name of file to read words from
     */
    public WordBank(String fileName) throws FileNotFoundException {
        this(fileName, -1);
    }

    /*
     * Gets a random word from the word bank
     * @returns a random String word
     */
    public String getWord() {
        return wordBank.get(randGen.nextInt(wordBank.size()));
    }

    /*
     * Gets a random word from the word bank of a specified size
     * @param wordSize the length of word to return
     * @returns a random word of specified size, or an empty string if none exist
     */
    public String getWord(int wordSize) {
        if (wordSizes.contains(wordSize)) {
            // we first generate an index as if we were working with a list of exclusively the right sized words
            int sizedWordIndex = randGen.nextInt((int)wordsOfSizes.get(wordSize));
            int sizedWordsSeen = 0;
            int i;

            // then, we traverse the full list until we reach a correctly sized word with the correct 'index'
            // incrementing the 'index' by 1 each time we find a correctly sized word, but have not yet reached the right index
            for (i = 0; i < wordBank.size(); i++) {
                if (wordBank.get(i).length() == wordSize) {
                    if (sizedWordsSeen == sizedWordIndex) {
                        break;
                    }
                    sizedWordsSeen++;
                }
            }    

            return wordBank.get(i);
        } else {
            return ""; // there are no words of that length
        }
    }

    /*
     * Checks if a given word is in the word bank
     * @param wordToCheck the String word to check for in the word bank
     * @returns a Boolean, true if in the word bank, false if not in the word bank
     */
    public Boolean isWordInBank(String wordToCheck) {
        Boolean isInBank = false; // i'm going to do a linear search instead of maintaining a second hashmap
        
        // loop through the entire bank; if we find it, say we found it and leave early
        // otherwise, fall through and return false
        for (int i = 0; i < wordBank.size(); i++) {
            if (wordBank.get(i).equals(wordToCheck)) {
                isInBank = true;
                break;
            }
        }

        return isInBank;
    }

    /*
     * Checks if the word bank contains words of a given size
     * @param wordSize size of words to query the word bank for
     * @returns a Boolean, true if bank has word(s) of that size, false if it does not
     */
    public Boolean hasWordsOfSize(int wordSize) {
        return wordSizes.contains(wordSize); // could also be achieved by checking for a key in the hashmap
    }
}
