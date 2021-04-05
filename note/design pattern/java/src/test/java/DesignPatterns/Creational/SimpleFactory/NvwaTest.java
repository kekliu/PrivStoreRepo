package DesignPatterns.Creational.SimpleFactory;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class NvwaTest {

    @Test
    void createCreature() {
        Creature creature;
        creature = Nvwa.createCreature("M");
        creature.speak();
        creature = Nvwa.createCreature("W");
        creature.speak();
        creature = Nvwa.createCreature("R");
        creature.speak();
        creature = Nvwa.createCreature(null);
        assertNull(creature);
    }
}