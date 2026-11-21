package com.opents.game;

import java.io.*;
import java.nio.file.*;
import java.nio.charset.StandardCharsets;
import java.util.*;

final class GameLanguage {
    static final String[] CODES = {"en", "es", "de", "fr"};
    static final String[] LABELS = {"English", "Español", "Deutsch", "Français"};
    static String label(String code) {
        int index = Arrays.asList(CODES).indexOf(code);
        return LABELS[index < 0 ? 0 : index];
    }
    static FreewarePackage[] packages(String code) throws IOException {
        if ("en".equals(code)) return FreewareManifest.PACKAGES;
        if ("es".equals(code) || "de".equals(code)) return java.util.Arrays.copyOf(FreewareManifest.PACKAGES, 3);
        if ("fr".equals(code)) return new FreewarePackage[0];
        throw new IOException("Unsupported game language.");
    }
    static String summary(String code) {
        if ("de".equals(code)) return "German menus, voices and movies; unit names from the source client remain English. About 2.05 GB to download; allow 4.5 GB free. Only shared files and German data are downloaded.";
        if ("fr".equals(code)) return "French text, voices and movies. About 1.68 GB to download; allow 3.5 GB free. Only French game data is downloaded.";
        return "es".equals(code)
            ? "Spanish game text, voices and movies from nacho-arg's community translation. Firestorm movies use Spanish subtitles; some expansion content may remain English. Android touch-settings menus remain English. About 1.69 GB to download; allow 4 GB free."
            : "English game text, voices and movies. About 1.24 GB to download; allow 2.5 GB free.";
    }

    static void recordImported(File destination, String language) throws IOException {
        packages(language);
        write(destination, ".opents-game-language", language + "\n");
    }

    static void finish(File destination, File stage, String language) throws IOException {
        packages(language);
        Set<String> current = new TreeSet<>();
        File[] files = stage.listFiles();
        if (files == null) throw new IOException("Cannot read installed language files.");
        for (File file : files)
            if (file.isFile() && file.getName().equals(GameFilePolicy.destinationName(file.getName()))) current.add(file.getName());
        File managed = new File(destination, ".opents-language-managed");
        if (managed.isFile()) {
            for (String name : Files.readAllLines(managed.toPath(), StandardCharsets.UTF_8)) {
                if (!name.equals(GameFilePolicy.destinationName(name)) || current.contains(name)) continue;
                File old = new File(destination, name);
                if (old.exists() && !old.delete()) throw new IOException("Cannot replace old language file: " + name);
            }
        }
        write(destination, ".opents-language-managed", String.join("\n", current) + "\n");
        recordImported(destination, language);
    }

    private static void write(File destination, String name, String value) throws IOException {
        File temporary = new File(destination, name + ".part");
        Files.write(temporary.toPath(), value.getBytes(StandardCharsets.UTF_8));
        try {
            Files.move(temporary.toPath(), new File(destination, name).toPath(),
                StandardCopyOption.ATOMIC_MOVE, StandardCopyOption.REPLACE_EXISTING);
        } catch (AtomicMoveNotSupportedException e) {
            Files.move(temporary.toPath(), new File(destination, name).toPath(), StandardCopyOption.REPLACE_EXISTING);
        }
    }
}
