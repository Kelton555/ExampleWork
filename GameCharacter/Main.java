// Kelton
// Project 2

import javax.swing.text.StyledEditorKit;

public class Main {
    public static void main(String[] args) {
        GameCharacter gameCharacter1 = new GameCharacter("Adventurer James", 10, 10, 3, 3, 3);
        GameCharacter gameCharacter2 = new GameCharacter("Senator Bill", 15, 7, 3, 2, 2);

        System.out.println("Competitor 1: " + gameCharacter1);
        System.out.println("Competitor 2: " + gameCharacter2);
        System.out.println(); // formatting for cleaner output

        System.out.println(gameCharacter1.getName() + " seems to be in great shape for today's battle! (+3 health, +1 mana)");
        gameCharacter1.setHealth(gameCharacter1.getHealth() + 3);
        gameCharacter1.setMana(gameCharacter1.getMana() + 1);

        System.out.println(gameCharacter2.getName() + " is amped for the fight! (+1 speed; +1 strength)");
        gameCharacter2.setSpeed(gameCharacter2.getSpeed() + 1);
        gameCharacter2.setStrength(gameCharacter2.getStrength() + 1);

        System.out.println(gameCharacter1.getName() + " copies " + gameCharacter2.getName() + "'s armor!");
        gameCharacter1.setArmor(gameCharacter2.getArmor());
        System.out.println(); // formatting for cleaner output

        System.out.println("Both competitors will receive new titles before the fight!");
        gameCharacter1.setName(gameCharacter1.getName() + " - The Hunter");
        gameCharacter2.setName(gameCharacter2.getName() + " - The Destroyer");

        System.out.println(); // formatting for cleaner output
        System.out.println("And lastly, before the fight, the competitors will be given a chance to cast spells.");
        
        System.out.println(gameCharacter1.getName() + " casts Heal and Strengthen!");
        gameCharacter1.heal();
        gameCharacter1.strengthen();

        System.out.println(gameCharacter2.getName() + " casts Toughen!");
        gameCharacter2.toughen();

        System.out.println(); // formatting for cleaner output
        System.out.println("Here's how our competitors stand now:");
        System.out.println("Competitor 1: " + gameCharacter1);
        System.out.println("Competitor 2: " + gameCharacter2);

        System.out.println("Let the battle begin!");
        System.out.println(); // formatting for cleaner output

        int turn = 1;
        while (gameCharacter1.getHealth() > 0 && gameCharacter2.getHealth() > 0) {
            System.out.println("Turn " + turn);

            // 1 can use spells
            if (turn % 3 == 0 && gameCharacter1.getMana() >= 1) {
                int currentHealth = gameCharacter1.getHealth();
                gameCharacter1.heal();
                System.out.println(gameCharacter1.getName() + " casts Heal and heals " + (gameCharacter1.getHealth() - currentHealth) + "HP!");
            } else if (turn % 3 == 1 && gameCharacter1.getMana() >= 2) {
                int currentArmor = gameCharacter1.getArmor();
                gameCharacter1.toughen();
                System.out.println(gameCharacter1.getName() + " casts Toughen and gains " + (gameCharacter1.getArmor() - currentArmor) + " Armor!");
            }

            // 1 attacks 2
            int attackStrength = gameCharacter1.attack();
            int startingHealth = gameCharacter2.getHealth();
            gameCharacter2.defend(attackStrength);
            System.out.print(gameCharacter1.getName() + " attacks " + gameCharacter2.getName() + " with " + attackStrength + " damage! ");
            System.out.println(gameCharacter2.getName() + " took " + (startingHealth - gameCharacter2.getHealth()) + " damage!");
            if (gameCharacter2.getHealth() == 0) {
                break;
            }

            // 2 can use spells
            if (turn % 3 == 1 && gameCharacter2.getMana() >= 2) {
                int currentStrength = gameCharacter2.getStrength();
                gameCharacter2.strengthen();
                System.out.println(gameCharacter2.getName() + " casts Strengthen and gains " + (gameCharacter2.getStrength() - currentStrength) + " Strenth!");
            } else if (turn % 3 == 2 && gameCharacter2.getMana() >= 2) {
                int currentArmor = gameCharacter2.getArmor();
                gameCharacter2.toughen();
                System.out.println(gameCharacter2.getName() + " casts Toughen and gains " + (gameCharacter2.getArmor() - currentArmor) + " Armor!");
            }

            // 2 attacks 1
            attackStrength = gameCharacter2.attack();
            startingHealth = gameCharacter1.getHealth();
            gameCharacter1.defend(attackStrength);
            System.out.print(gameCharacter2.getName() + " attacks " + gameCharacter1.getName() + " with " + attackStrength + " damage! ");
            System.out.println(gameCharacter1.getName() + " took " + (startingHealth - gameCharacter1.getHealth()) + " damage!");
            if (gameCharacter1.getHealth() == 0) {
                break;
            }

            // post-round stats
            System.out.println("Competitor standings at the end of turn " + turn + ":");
            System.out.println("Competitor 1: " + gameCharacter1);
            System.out.println("Competitor 2: " + gameCharacter2);
            System.out.println(); // formatting for cleaner output
            turn++;
        }

        if (gameCharacter1.getHealth() == 0 && gameCharacter2.getHealth() == 0) {
            System.out.println(); // formatting for cleaner output
            System.out.println("Both competitors have fallen. The battle ended on turn " + turn + ".");
        } else if (gameCharacter1.getHealth() == 0) {
            System.out.println(); // formatting for cleaner output
            System.out.println("Competitor 1, " + gameCharacter1.getName() + ", has fallen. The battle ended on turn " + turn + ".");
        } else if (gameCharacter2.getHealth() == 0) {
            System.out.println(); // formatting for cleaner output
            System.out.println("Competitor 2, " + gameCharacter2.getName() + ", has fallen. The battle ended on turn " + turn + ".");
        }

        System.out.println(); // formatting for cleaner output
        System.out.println("Final Standings:");
        System.out.println("Competitor 1: " + gameCharacter1);
        System.out.println("Competitor 2: " + gameCharacter2);
    }
}
