// Kelton
// Program Project 4 - Passphrase Generator

import java.io.FileNotFoundException;
import java.util.Scanner;

class PassphraseGenerator {
    private WordBank wordBank;
    private Scanner scnr;

    /*
     * Returns true or false, based on whether the user would like to continue
     * @param scnr Scanner object to get input from
     * @returns a Boolean, true for continue, false for don't continue
     */
    private Boolean promptForContinue(Scanner scnr) {
        char inputChar = 'a'; // default value that doesn't satisfy loop exit condition

        while (Character.toLowerCase(inputChar) != 'y' && Character.toLowerCase(inputChar) != 'n') {
            System.out.print("Do you want to continue? (Y/N): ");
            inputChar = scnr.next().charAt(0);
        }

        scnr.nextLine(); // remove a remaining newline to avoid a double printing bug on subsequent inputs
        return (Character.toLowerCase(inputChar) == 'y');
    }

    /*
     * Gets an integer input from the user
     * @param scnr Scanner object to get input from
     * @returns an integer from scanner object
     */
    private int getUserInt(Scanner scnr) {
        while (!scnr.hasNextInt()) {
            System.out.print("Error! Please enter an integer: ");
            scnr.nextLine();
        }

        int inputInt = scnr.nextInt();
        scnr.nextLine(); // remove the newline to avoid a double printing bug on subsequent inputs
        return inputInt;
    }

    /*
     * Constructs a PassphraseGenerator with a given filename and word size
     * @param fileName a String filename to load words from
     * @param scnr a Scanner object for user input
     * @param wordSize an int to specify loading words of a given size, or -1 to load all words
     */
    public PassphraseGenerator(String fileName, Scanner scnr, int wordSize) {
        this.scnr = scnr;
        
        Boolean cont = true; 
        while (cont) { // loop until we can open a file
            try {
                wordBank = new WordBank(fileName, wordSize);
                cont = false; // stop looping, we opened a file
            } catch (FileNotFoundException e) { // assignment instructions say to handle the error in this class, this handling allows operation to continue even if the default filename doesn't work
                System.out.println("File reading error: " + e.getMessage());
                System.out.print("Please enter a filename to try again: ");
                fileName = scnr.nextLine();
            }
        }
    }

    /*
     * Constructs a Passphrase generator with a given filename including all word sizes
     * @param fileName a String filename to load words from
     * @param scnr a scanner object for user input
     */
    public PassphraseGenerator(String fileName, Scanner scnr) {
        this(fileName, scnr, -1);
    }

    /*
     * Creates and returns a String passphrase with the given amount of random words that
     * have the given amount of letters per word
     * @param words integer amount of words to include per passphrase, minimum 1
     * @param lettersPerWord integer amount of letters per word, minimum 1
     * @returns a String passphrase generated with the given parameters
     */
    public String generatePassphrase(int words, int lettersPerWord) {
        words = Math.max(1, words);
        lettersPerWord = Math.max(1, lettersPerWord);

        if (wordBank.hasWordsOfSize(lettersPerWord)) { // first, check that we have words of the given size
            String passPhrase = "";
            for (int i = 0; i < words; i++) { // then loop 'words' times and add a word of the given size to the end of the passphrase each time
                passPhrase += wordBank.getWord(lettersPerWord);
            }
            return passPhrase;
        } else {
            System.out.println("No words of size " + lettersPerWord + " to pick from.");
            return "";
        }
    }

    /*
     * Starts the passphrase generator, receiving user input and continuing until the user decides to quit
     */
    public void start() {
        System.out.println("Welcome to the Random Passphrase Generator");
        
        do {
            int passphrasesToGenerate = 0;
            do {
                System.out.print("How many passphrases to generate? ");
                passphrasesToGenerate = getUserInt(scnr);
            } while (passphrasesToGenerate < 1);

            int wordsPerPhrase = 0;
            do {
                System.out.print("How many words per passphrase? ");
                wordsPerPhrase = getUserInt(scnr);
            } while (wordsPerPhrase < 1);

            int lengthPerWord = 0;
            do {
                System.out.print("How many characters per word? ");
                lengthPerWord = getUserInt(scnr);

                if (!wordBank.hasWordsOfSize(lengthPerWord)) { 
                    // specific error message in this case, as it's not necessarily obvious
                    System.out.print("No words of that length. ");
                }
            } while (!wordBank.hasWordsOfSize(lengthPerWord));

            System.out.println("Here are the random passphrases:");
            for (int i = 0; i < passphrasesToGenerate; i++) {
                System.out.println(generatePassphrase(wordsPerPhrase, lengthPerWord));
            }
        } while (promptForContinue(scnr));

        System.out.println("Goodbye!");
    }
}
