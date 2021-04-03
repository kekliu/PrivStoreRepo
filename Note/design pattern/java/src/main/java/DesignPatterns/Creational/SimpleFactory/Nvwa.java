package DesignPatterns.Creational.SimpleFactory;

public class Nvwa {
    public static Creature createCreature(String type) {
        Creature creature = null;
        if ("M".equals(type)) {
            creature = new Man();
        } else if ("W".equals(type)) {
            creature = new Woman();
        } else if ("R".equals(type)) {
            creature = new Robot();
        }
        return creature;
    }
}
