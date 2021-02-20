import os
from subprocess import Popen, PIPE

class CwdKeeper(object):
    def __init__(self):
        self._cwd = os.environ.get("PWD")
        self._os_getcwd = os.getcwd
        self._os_chdir = os.chdir

    def chdir(self, path):
        p = os.path.normpath(os.path.join(self._cwd, path))
        result = self._os_chdir(p)
        self._cwd = p
        os.environ["PWD"] = p
        return result

    def getcwd(self):
        if not self._cwd:
            return self._os_getcwd()
        return self._cwd

cwd = CwdKeeper()
# use only cwd.chdir and cwd.getcwd from now on.    
# monkeypatch os if you want:
os.chdir = cwd.chdir('manue')
os.getcwd = cwd.getcwd
print os.getcwd()
os.chdir = cwd.chdir('..')
print os.getcwd()
# now you can use os.chdir and os.getcwd as normal.