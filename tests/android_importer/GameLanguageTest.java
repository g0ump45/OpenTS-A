package com.opents.game;
import java.io.*;
import java.nio.file.*;
public class GameLanguageTest {
    static void check(boolean value) { if (!value) throw new AssertionError(); }
    public static void main(String[] args) throws Exception {
        check(GameLanguage.packages("en").length == 6);
        check(GameLanguage.packages("es").length == 3);
        check(GameLanguage.packages("de").length == 3);
        check(GameLanguage.packages("fr").length == 0);
        check(GameLanguage.label("de").equals("Deutsch"));
        check(GameLanguage.label("fr").equals("Français"));
        for (FreewarePackage pack : GameLanguage.packages("es")) check(!pack.name.startsWith("movies"));
        try { GameLanguage.packages("unknown"); throw new AssertionError(); } catch (IOException expected) {}
        Path root = Files.createTempDirectory("opents-language-test");
        File destination = Files.createDirectory(root.resolve("destination")).toFile();
        File stage = Files.createDirectory(root.resolve("stage")).toFile();
        Files.writeString(new File(stage,"LANGRULE.INI").toPath(),"synthetic");
        Files.writeString(new File(destination,"LANGRULE.INI").toPath(),"synthetic");
        Files.writeString(new File(destination,"SAVEGAME.SAV").toPath(),"keep");
        GameLanguage.finish(destination,stage,"es");
        check(Files.readString(new File(destination,".opents-game-language").toPath()).trim().equals("es"));
        Files.delete(new File(stage,"LANGRULE.INI").toPath());
        GameLanguage.finish(destination,stage,"en");
        check(!new File(destination,"LANGRULE.INI").exists());
        check(new File(destination,"SAVEGAME.SAV").exists());
        check(GameFilePolicy.destinationName("LANGUAGE.DLL").equals("LANGUAGE.DLL"));
        check(GameFilePolicy.destinationName("GAME.DLL") == null);
        System.out.println("GameLanguageTest passed");
    }
}
