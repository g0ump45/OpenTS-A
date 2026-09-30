"""Small filesystem helpers shared by the manual generators."""

from pathlib import Path
import os
import tempfile


def atomic_write_text(path, text, *, encoding="utf-8"):
    """Replace *path* only after the complete new contents are on disk.

    Keeping the temporary file beside the destination makes ``os.replace`` an
    atomic same-volume operation on every platform supported by the manual
    tooling.  A failed serialization therefore cannot truncate tracked data.
    """

    target = Path(path)
    target.parent.mkdir(parents=True, exist_ok=True)
    temporary = None
    try:
        with tempfile.NamedTemporaryFile(
                mode="w", encoding=encoding, newline="", delete=False,
                dir=target.parent, prefix=f".{target.name}.", suffix=".tmp") as stream:
            temporary = Path(stream.name)
            stream.write(text)
            stream.flush()
            os.fsync(stream.fileno())
        os.replace(temporary, target)
    finally:
        if temporary is not None:
            temporary.unlink(missing_ok=True)
