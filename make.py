#!/usr/bin/python3

# 1. Imports
import sys
import os
import subprocess
import hashlib
import json
import platform
import atexit

# 2. Global Constants & Variables
_CC = "gcc"
_args = "-DNDEBUG"
files = {}
named = {}
commands = {}
runs = {}
HASH_CACHE_FILE = ".build_hashes.json"

# 3. Platform Detection
system = platform.system().lower()
if system == "windows":
    file = ".wcmbdfile"
elif system == "linux":
    file = ".ucmbdfile"
elif system == "darwin":
    file = ".dcmbdfile"
else:
    raise TypeError("unsupported os")

# 4. Compiler Configuration Functions
def CC(cc):
    global _CC
    _CC = cc

def args(args):
    global _args
    if system == "linux":
        args += ["-D__linux__", "-D__unix__", "-D__UNIX__"]
    _args = " ".join(args)

# 5. Hashing Utilities
def file_hash(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        while chunk := f.read(8192):
            h.update(chunk)
    return h.hexdigest()

def load_hash_cache():
    if os.path.exists(HASH_CACHE_FILE):
        with open(HASH_CACHE_FILE, "r") as f:
            return json.load(f)
    return {}

def save_hash_cache(cache):
    with open(HASH_CACHE_FILE, "w") as f:
        json.dump(cache, f)

hash_cache = load_hash_cache()
atexit.register(lambda: save_hash_cache(hash_cache))

# 6. Build File Handling
def compile(outf, infs, type=None, name=None):
    cc = f"{_CC} {_args} "
    if type == "obj":
        cc += "-c "
    elif type == "lib":
        cc += f"-shared -Wl,--output-def,{outf}.def -Wl,--kill-at "
    elif type == "exec":
        pass
    else:
        raise TypeError("unknown type: " + str(type))

    files[outf] = {
        "run": lambda: subprocess.run(f"{cc}{' '.join(infs)} -o {outf}", shell=True, check=True),
        "infs": infs,
        "outf": outf,
        "cmd": f"{cc}{' '.join(infs)} -o {outf}"
    }

    if name:
        named[name] = files[outf]

def clean(folder):
    subprocess.run(f"rm -rf {folder}", shell=True)

def get(name):
    return named[name]

# 7. Dependency Resolution & Rebuild Logic
def needs_rebuild(output, inputs, hash_cache):
    if not os.path.exists(output):
        return True
    for inp in inputs:
        if inp in files:
            if needs_rebuild(files[inp]["outf"], files[inp]["infs"], hash_cache):
                return True
        else:
            if not os.path.exists(inp):
                return True
            if hash_cache.get(inp) != file_hash(inp):
                return True
    return False

def update_hash_cache(inputs, hash_cache):
    for inp in inputs:
        if inp in files:
            update_hash_cache(files[inp]["infs"], hash_cache)
        elif os.path.exists(inp):
            hash_cache[inp] = file_hash(inp)

def start(build, dry=False, prev=[]):
    for inf in build["infs"]:
        if inf in files:
            dep_outf = files[inf]["outf"]
            if not os.path.exists(dep_outf):
                prev = start(files[inf], dry, prev=prev)

    if needs_rebuild(build["outf"], build["infs"], hash_cache):
        if not dry:
            if "/" in build["outf"] or "\\" in build["outf"]:
                os.makedirs(os.path.dirname(build["outf"]), exist_ok=True)
            build["run"]()
        else:
            return prev + [build["cmd"]]
        update_hash_cache(build["infs"], hash_cache)
    else:
        print(f"{build['outf']} is up to date.")
    return prev + [build["cmd"]]

# 8. Build Command Management
def parsererror(message):
    print(message)
    sys.exit(0)

def parse(outf, infs, typ, name):
    if typ == "CC":
        CC(outf)
        args(infs)
    elif typ == "cmd":
        commands[outf] = infs
    elif outf == "import":
        for inf in infs:
            parseBuild(inf)
    elif typ == "run":
        runs[name] = [(f"&\"{outf}\"" if system == "windows" else outf.replace(" ", "\\ ")) + f" {inf}" for inf in infs]
    else:
        compile(outf, infs, typ, name)

# 9. Parser & Build Script Interpreter
def parseBuild(file):
    with open(file, "r") as f:
        data = "".join(line for line in f if not line.lstrip().startswith("#"))

    result = [""]
    i = 0
    while i < len(data):
        c = data[i]
        if c == ":":
            result.extend([":", ""])
        elif c == ",":
            result.extend([",", ""])
        elif c == "\n":
            result.append("")
        elif c == ";":
            result.extend([";", ""])
        elif c == "\\":
            result[-1] += data[i + 1]
            i += 1
        elif c in (" ", "\t"):
            pass
        else:
            result[-1] += c
        i += 1

    result = [r for r in result if r]

    i = 0
    while i < len(result):
        outf = result[i]
        i += 2
        infs = [result[i]]
        i += 1
        while result[i] != ",":
            if result[i] == ";":
                parsererror("expected comma, got: " + result[i])
            infs.append(result[i])
            i += 1
        i += 1
        typ = result[i]
        i += 1
        name = None
        if result[i] == ",":
            i += 1
            name = result[i]
            i += 1
        if result[i] != ";":
            parsererror("expected semicolon, got: " + result[i])
        i += 1
        parse(outf, infs, typ, name)

# 10. Entry Point / Execution Logic
def build(name, prev=None, dry=False):
    if name in commands:
        for command in commands[name]:
            build(command, (prev + " -> " + command) if prev else command, dry)
    elif name in runs:
        # if name in runs: is an endpoint
        print((prev if prev else name) + ":")
        for run in runs[name]:
            if dry:
                print(run)
            else:
                subprocess.run(run)
    else:
        # else: build : is an endpoint
        print((prev if prev else name) + ":")
        a = get(name) if name in named else None
        if a is None:
            print(f"\tmacro/run undefined: {name}")
            sys.exit(0)
        result = start(a, dry=dry)
        print("\t" + "\n\t".join(result))

parseBuild(file)

builds = sys.argv + ["clean", "all"]
if len(builds) == 1:
    print(f"\nusage: python {builds[0]} [clean] <buildname> [<buildname> ...]\n\nversion: 0.1.3")
    sys.exit(0)

builds = builds[1:]
if builds[0] == "clean":
    clean("build")
    builds = builds[1:]

# Dry run
#for b in builds:
#    build(b, dry=True)

print("\n\nstarting:\n")
# Actual run
try:
    for b in builds:
        build(b)
except:
    print("\n\ndone with errors")
    sys.exit(0)
print("\n\ndone!\n")