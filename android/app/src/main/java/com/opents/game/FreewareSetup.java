package com.opents.game;

import java.io.*;
import java.util.*;

final class FreewareSetup {
    static final String PENDING = ".opents-setup-pending";

    static int install(File destination, FreewareExtractor.Progress progress) throws IOException {
        return install(destination, "en", progress);
    }

    static int install(File destination, String language, FreewareExtractor.Progress progress) throws IOException {
        FreewarePackage[] packages = GameLanguage.packages(language);
        if (!destination.isDirectory() && !destination.mkdirs()) throw new IOException("Cannot create game storage.");
        File work = new File(destination, "en".equals(language) ? ".opents-freeware-downloads" : ".opents-freeware-downloads-" + language);
        File stage = new File(work, "stage");
        if (!stage.isDirectory() && !stage.mkdirs()) throw new IOException("Cannot create download storage.");
        for (FreewarePackage pack : packages) {
            File complete = new File(work, pack.sha256 + ".complete");
            if (complete.isFile()) continue;
            File source = new File(work, pack.name + ".part");
            long needed = Math.max(0, pack.bytes - source.length());
            for (FreewarePackage.Entry entry : pack.entries) needed += entry.bytes;
            if (destination.getUsableSpace() < needed + 128L * 1024 * 1024)
                throw new IOException("Not enough free storage. Allow about 2.5 GB for setup, then retry.");
            FreewareDownloader.download(pack, source, progress);
            try { FreewareExtractor.extract(source, stage, pack, progress); }
            catch (IOException e) {
                // Keep interrupted downloads, but discard a complete package with the wrong hash.
                if (source.length() == pack.bytes && e.getMessage() != null
                    && e.getMessage().startsWith("Source package changed")) source.delete();
                throw e;
            }
            if (!complete.createNewFile()) throw new IOException("Cannot record completed package.");
            source.delete();
        }
        if ("es".equals(language)) LanguageArchive.install(work, stage, progress);
        if ("de".equals(language) || "fr".equals(language)) LocalizedZip.install(work, stage, language, progress);
        File[] files = stage.listFiles();
        if (files == null || !new File(stage, "TIBSUN.MIX").isFile()) throw new IOException("Downloaded installation is incomplete.");
        // A killed final copy must return to setup rather than open a partial installation.
        new File(destination, PENDING).createNewFile();
        Arrays.sort(files, Comparator.comparing(File::getName));
        int count = 0;
        for (File file : files) {
            if (!file.getName().equals(GameFilePolicy.destinationName(file.getName()))) continue;
            progress.update("Installing " + file.getName() + "...");
            try (InputStream input = new FileInputStream(file)) {
                GameFilePolicy.copyAtomic(input, destination, file.getName(), GameFilePolicy.MAX_BYTES);
            }
            count++;
        }
        GameLanguage.finish(destination, stage, language);
        if (!new File(destination, PENDING).delete()) throw new IOException("Cannot finish setup. Retry once more.");
        for (File file : files) file.delete();
        File[] markers = work.listFiles();
        if (markers != null) for (File marker : markers) if (marker.getName().endsWith(".complete")) marker.delete();
        stage.delete(); work.delete();
        return count;
    }
}
