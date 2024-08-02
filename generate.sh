#/bin/bash
mkdir ./build;

LINT_FLAG="-DCHECK_TIDY=OFF"
if [ "$#" -gt 0 ]; then
    if [ $1 == "-ct" ]; then
        LINT_FLAG="-DCHECK_TIDY=ON"
    fi
fi
echo $LINT_FLAG
cmake $LINT_FLAG -S . -B ./build 
