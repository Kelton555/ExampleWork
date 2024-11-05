// Kelton
// Project 2

import java.util.Random;

public class GameCharacter {
    private Random randGen;

    private String name;
    private int health;
    private int mana;
    private int strength;
    private int speed;
    private int armor;
    
    // constructors
    public GameCharacter(String characterName, int characterHealth, int characterMana, int characterStrength, int characterSpeed, int characterArmor) {
        name = characterName;
        health = characterHealth;
        mana = characterMana;
        strength = characterStrength;
        speed = characterSpeed;
        armor = characterArmor;

        randGen = new Random();
    }

    // e.g. "Adventurer James: 10HP, 5MP, 5STR, 3SPD, 1ARM"
    public String toString() {
        return name + ": " + health + "HP, " + mana + "MP, " + strength + "STR, " + speed + "SPD, " + armor + "ARM";
    }

    public int attack() {
        int damage = strength; // set damage equal to strength at baseline
        
        int randomModifier = randGen.nextInt(5);
        randomModifier -= 2; // [-2:2]

        damage += randomModifier;
        
        // calculate a multiplier for damage based on the character's speed and a random number 1-10
        // speed is allowed to be negative, if it is damage may be lowered
        double multiplier = 1.0d + ((double)((randGen.nextInt(10) + 1) * speed) / 100.0d);
        damage = (int)Math.round((double)damage * multiplier);

        damage = Math.max(damage, 0); // damage cannot be negative

        // the character will gain log{2.5}(damage) mana (floored) each time they attack
        // the character cannot lose mana from attacking, only gain it
        mana += Math.max((int)Math.floor(Math.log10((double)damage) / Math.log10(2.5d)), 0); 
        
        return damage;
    }

    public void defend(int attackStrength) {
        // speed is allowed to be negative, if it is then the character may take extra damage
        if (speed >= 0) {
            // firstly, speed is multiplied by a random number (0 inclusive to ensure there's always a chance to hit)
            // then, it's compared with a random number to ensure that there's a non-zero chance of a low speed character dodging
            if ((speed * randGen.nextInt(7)) > randGen.nextInt(21)) {
                attackStrength = 0;
            }
        } else { // speed is negative
            // the same check as for dodging, except when speed is negative it will multiply by 1.5x
            if (Math.abs((speed * randGen.nextInt(7))) > randGen.nextInt(21)) {
                attackStrength *= 1.5;
            }
        }

        // armor is also allowed to be negative, if it is the character may take extra damage
        if (armor >= 0) {
            for (int i = 0; i < armor; i++) {
                if (randGen.nextInt(3) == 0) {// 1/3 chance
                    attackStrength -= 1;
                }
            }
        } else { // armor is negative
            attackStrength = (int)Math.round((double)attackStrength * (1.0d + Math.abs((double)armor / 10.0d)));
        }
        
        attackStrength = Math.max(attackStrength, 0); // damage taken can never be negative
        health -= attackStrength;
        health = Math.max(health, 0); // health constrained to 0 or higher
    }

    public void heal() {
        if (mana >= 1) {
            mana -= 1;
            health += randGen.nextInt(5); // [0:4]
        }
    }

    public void strengthen() {
        if (mana >= 2) {
            mana -= 2;
            strength += randGen.nextInt(3); // [0:2]
        }
    }

    public void toughen() {
        if (mana >= 2) {
            mana -= 2;
            armor += randGen.nextInt(4); // [0:3]
        }
    }

    // getter methods
    public String getName() {
        return name;
    }

    public int getHealth() {
        return health;
    }

    public int getMana() {
        return mana;
    }

    public int getStrength() {
        return strength;
    }

    public int getSpeed() {
        return speed;
    }

    public int getArmor() {
        return armor;
    }

    // setter methods
    public void setName(String characterName) {
        name = characterName;
    }

    public void setHealth(int characterHealth) {
        health = Math.max(characterHealth, 0); // only positive values and zero are allowed for health
    }

    public void setMana(int characterMana) {
        mana = Math.max(characterMana, 0); // only positive values and zero are allowed for mana
    }

    public void setStrength(int characterStrength) {
        strength = Math.max(characterStrength, 0); // only positive values and zero are allowed for strength
    }

    public void setSpeed(int characterSpeed) {
        speed = characterSpeed;
    }

    public void setArmor(int characterArmor) {
        armor = characterArmor;
    }
}
