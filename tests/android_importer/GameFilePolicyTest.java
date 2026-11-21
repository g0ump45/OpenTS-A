package com.opents.game;
import java.io.*;
import java.nio.file.*;
import java.util.*;

public class GameFilePolicyTest {
    private static void check(boolean value) { if (!value) throw new AssertionError(); }
    private static void checkSnowOrder(List<String> paths, int start) throws IOException {
        if (start == paths.size()) {
            check(GameFilePolicy.plan(paths).get("SNOW.INI").equals("Install/snow.ini"));
            return;
        }
        for (int index = start; index < paths.size(); index++) {
            Collections.swap(paths, start, index);
            checkSnowOrder(paths, start + 1);
            Collections.swap(paths, start, index);
        }
    }
    public static void main(String[] args) throws Exception {
        Map<String,String> plan = GameFilePolicy.plan(Arrays.asList("Install/tibsun.mix", "Install/LANGUAGE.MIX", "Install/SUN.INI", "Install/KEYBOARD.INI", "Install/game.exe", "Install/save.sav", "Install/Movies/MOVIES01.MIX"));
        check(plan.size() == 3 && plan.containsKey("TIBSUN.MIX") && plan.containsKey("MOVIES01.MIX"));
        check(GameFilePolicy.findRoot(Arrays.asList("backup/a/TIBSUN.MIX", "backup/b/TIBSUN.MIX", "TIBSUN.MIX")).equals(""));
        boolean rejected = false;
        try { GameFilePolicy.plan(Arrays.asList("one/TIBSUN.MIX", "two/TIBSUN.MIX")); } catch (IOException e) { rejected = true; }
        check(rejected);
        for (String path : Arrays.asList("../TIBSUN.MIX", "C:/TIBSUN.MIX", "/TIBSUN.MIX", "a/../../TIBSUN.MIX")) {
            rejected = false; try { GameFilePolicy.normalize(path); } catch (IOException e) { rejected = true; } check(rejected);
        }
        checkSnowOrder(new ArrayList<>(Arrays.asList("Install/TIBSUN.MIX", "Install/Maps/A/SNOW.INI", "Install/Extras/B/SNOW.INI", "Install/snow.ini")), 0);
        check(GameFilePolicy.plan(Arrays.asList("TIBSUN.MIX", "maps\\A\\SNOW.INI", "extras\\B\\snow.ini", "SNOW.INI")).get("SNOW.INI").equals("SNOW.INI"));
        check(GameFilePolicy.plan(Arrays.asList("Install/TIBSUN.MIX", "Install/Data/SNOW.INI")).get("SNOW.INI").equals("Install/Data/SNOW.INI"));
        for (List<String> paths : Arrays.asList(
                Arrays.asList("Install/TIBSUN.MIX", "Install/A/SNOW.INI", "Install/B/SNOW.INI"),
                Arrays.asList("Install/TIBSUN.MIX", "Install/SNOW.INI", "Install/snow.ini"))) {
            rejected = false;
            try { GameFilePolicy.plan(paths); } catch (IOException e) { rejected = true; }
            check(rejected);
        }
        checkSnowOrder(new ArrayList<>(Arrays.asList("Install/TIBSUN.MIX", "Install/INI/Base/SNOW.INI", "Install/Extras/SNOW.INI", "Install/snow.ini")), 0);
        List<String> client = Arrays.asList("Client/MIX/TIBSUN.MIX", "Client/INI/SNOW.INI", "Client/INI/Base/SNOW.INI",
            "Client/Maps/old/SNOW.INI", "Client/Maps/Missions/GDI1A.MAP", "Client/INI/TUTORIAL.INI", "Client/Resources/LANGUAGE.DLL");
        Map<String,String> clientPlan = GameFilePolicy.plan(client);
        check(clientPlan.get("SNOW.INI").equals("Client/INI/SNOW.INI"));
        check(clientPlan.containsKey("TUTORIAL.INI") && clientPlan.containsKey("LANGUAGE.DLL") && clientPlan.containsKey("GDI1A.MAP"));
        Collections.reverse(client);
        check(GameFilePolicy.plan(client).equals(clientPlan));
        rejected = false;
        try { GameFilePolicy.plan(Arrays.asList("A/MIX/TIBSUN.MIX", "B/MIX/TIBSUN.MIX")); }
        catch (IOException e) { rejected = true; }
        check(rejected);
        Path directory = Files.createTempDirectory("opents-import-test");
        Path target = directory.resolve("TIBSUN.MIX");
        try {
            Files.write(target, new byte[]{7});
            InputStream broken = new InputStream() { public int read() throws IOException { throw new IOException("Interrupted copy"); } };
            rejected = false;
            try { GameFilePolicy.copyAtomic(broken, directory.toFile(), "TIBSUN.MIX", 100); } catch (IOException e) { rejected = true; }
            check(rejected && Files.readAllBytes(target)[0] == 7);
            rejected = false;
            try { GameFilePolicy.copyAtomic(new ByteArrayInputStream(new byte[]{1,2}), directory.toFile(), "TIBSUN.MIX", 1); } catch (IOException e) { rejected = true; }
            check(rejected && Files.readAllBytes(target)[0] == 7);
            GameFilePolicy.copyAtomic(new ByteArrayInputStream(new byte[]{2,3}), directory.toFile(), "TIBSUN.MIX", 100);
            check(Arrays.equals(Files.readAllBytes(target), new byte[]{2,3}));
            try (java.util.stream.Stream<Path> files = Files.list(directory)) { check(files.count() == 1); }
        } finally { Files.deleteIfExists(target); Files.deleteIfExists(directory); }
        System.out.println("PASS: automatic file selection, settings/save exclusions, root detection, order-independent root precedence, ambiguous-copy rejection, traversal rejection, atomic replacement and interrupted copies");
    }
}
