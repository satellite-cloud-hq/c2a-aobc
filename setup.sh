#!/bin/bash
echo setup.sh
echo setting for local environment...
echo
echo [SET USER HOOKS]
git config --local core.hooksPath  src/src_user/Script/GitHooks
echo done.
echo
echo The process has been completed.
