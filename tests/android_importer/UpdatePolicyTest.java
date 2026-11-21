package com.opents.game;
import java.io.IOException;
public class UpdatePolicyTest {
    static void check(boolean value) { if (!value) throw new AssertionError(); }
    public static void main(String[] args) throws Exception {
        check(UpdatePolicy.compare("v1.10.0", "1.9.9") > 0);
        check(UpdatePolicy.compare("v1.3.5", "1.3.5-preview1") > 0);
        check(UpdatePolicy.compare("v1.3.4", "1.3.5-preview1") < 0);
        check(UpdatePolicy.compare("v1.3", "1.3.0") == 0);
        boolean rejected = false;
        try { UpdatePolicy.compare("game-data", "1.3.5"); } catch (IOException e) { rejected = true; }
        check(rejected);
        String valid = "https://github.com/g0ump45/OpenTS-A/releases/download/v1.3.5/OpenTS-A.apk";
        String hash = "sha256:" + "a".repeat(64);
        UpdatePolicy.asset(valid, 1000, hash);
        for (String url : new String[]{valid.replace("https:", "http:"), valid.replace("github.com", "github.com.evil.example"),
            valid.replace("OpenTS-A/releases", "Other/releases"), valid + "?redirect=evil", valid.replace("/v1.3.5/", "/../")}) {
            rejected = false; try { UpdatePolicy.asset(url, 1000, hash); } catch (IOException e) { rejected = true; }
            check(rejected);
        }
        for (long bytes : new long[]{0, -1, UpdatePolicy.MAX_APK + 1}) {
            rejected = false; try { UpdatePolicy.asset(valid, bytes, hash); } catch (IOException e) { rejected = true; }
            check(rejected);
        }
        rejected = false; try { UpdatePolicy.asset(valid, 1000, "sha256:bad"); } catch (IOException e) { rejected = true; }
        check(rejected);
        System.out.println("PASS: version ordering, preview-to-stable updates, invalid tags, source URLs, size limits and digest metadata");
    }
}
