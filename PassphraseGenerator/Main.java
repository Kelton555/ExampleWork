// Kelton
// Program Project 4 - Passphrase Generator

import java.util.Scanner;

class Main {
    /*
     * Main method that starts the passphrase generator
     * @param args command line arguments
     */
    public static void main(String[] args) {
        Scanner scnr = new Scanner(System.in);
        PassphraseGenerator generator = new PassphraseGenerator("words_alpha.txt", scnr); // uses the constructor that includes all words by default
        
        generator.start();
    }
}
