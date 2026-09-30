package com.opents.game;

import java.io.*;
import java.nio.file.*;
import java.util.*;

// Import only game data; phone settings, saves and executable files are excluded.
public final class GameFilePolicy {
    public static final long MAX_BYTES = 8L * 1024 * 1024 * 1024;
    private static final Set<String> EXTENSIONS = new HashSet<>(Arrays.asList(
        "MIX", "VQA", "AUD", "INI", "PKT", "MPR", "MAP", "PAL", "PCX", "SHP", "VXL", "HVA", "TEM", "SNO"));

    public static String normalize(String path) throws IOException {
        path = path.replace('\\', '/');
        if (path.startsWith("/") || path.contains(":")) throw new IOException("Unsafe archive path.");
        for (String part : path.split("/", -1))
            if (part.equals("..") || part.equals(".") || part.indexOf('\0') >= 0)
                throw new IOException("Unsafe archive path.");
        return path;
    }

    public static String destinationName(String path) throws IOException {
        path = normalize(path);
        String name = path.substring(path.lastIndexOf('/') + 1).toUpperCase(Locale.ROOT);
        if (!name.matches("[A-Z0-9][A-Z0-9_. -]*")) return null;
        if (name.equals("SUN.INI") || name.equals("KEYBOARD.INI") || name.startsWith("SPAWN")
            || name.startsWith("QUEST_") || name.equals("DDRAW.INI")) return null;
        int dot = name.lastIndexOf('.');
        return dot > 0 && EXTENSIONS.contains(name.substring(dot + 1)) ? name : null;
    }

    public static String findRoot(Collection<String> paths) throws IOException {
        String best = null;
        Set<String> candidates = new HashSet<>();
        int depth = Integer.MAX_VALUE;
        for (String original : paths) {
            String path = normalize(original);
            if (!path.substring(path.lastIndexOf('/') + 1).equalsIgnoreCase("TIBSUN.MIX")) continue;
            String root = path.substring(0, path.lastIndexOf('/') + 1);
            int candidateDepth = root.split("/", -1).length;
            if (candidateDepth < depth) { depth = candidateDepth; best = root; candidates.clear(); }
            if (candidateDepth == depth) candidates.add(root);
        }
        if (candidates.size() > 1) throw new IOException("More than one installation found. Choose the game installation folder or a ZIP containing one installation.");
        if (best == null) throw new IOException("TIBSUN.MIX was not found. Choose the root of an installed Tiberian Sun copy, not an installer or disc image.");
        return best;
    }

    public static Map<String,String> plan(Collection<String> paths) throws IOException {
        String root = findRoot(paths);
        Map<String,String> plan = new TreeMap<>();
        for (String original : paths) {
            String path = normalize(original);
            if (!path.startsWith(root)) continue;
            String name = destinationName(path);
            if (name == null) continue;
            String previous = plan.get(name);
            if (previous == null) plan.put(name, original);
            else {
                boolean direct = path.substring(root.length()).indexOf('/') < 0;
                boolean previousDirect = normalize(previous).substring(root.length()).indexOf('/') < 0;
                if (direct && !previousDirect) plan.put(name, original);
                else if (direct == previousDirect) throw new IOException("Conflicting copies of " + name + ". Choose one installation folder.");
            }
        }
        return plan;
    }

    public static long copyAtomic(InputStream source, File directory, String name, long remaining) throws IOException {
        if (!name.equals(destinationName(name))) throw new IOException("Invalid game-data filename.");
        File temp = File.createTempFile(".opents-import-", ".tmp", directory);
        long count = 0;
        try {
            try (FileOutputStream output = new FileOutputStream(temp)) {
                byte[] bytes = new byte[65536];
                int read;
                while ((read = source.read(bytes)) != -1) {
                    count += read;
                    if (count > remaining) throw new IOException("Import is larger than the allowed size.");
                    output.write(bytes, 0, read);
                }
                if (count == 0) throw new IOException(name + " is empty.");
                output.getFD().sync();
            }
            Path target = new File(directory, name).toPath();
            try { Files.move(temp.toPath(), target, StandardCopyOption.ATOMIC_MOVE, StandardCopyOption.REPLACE_EXISTING); }
            catch (AtomicMoveNotSupportedException e) { Files.move(temp.toPath(), target, StandardCopyOption.REPLACE_EXISTING); }
            return count;
        } finally { Files.deleteIfExists(temp.toPath()); }
    }
}
