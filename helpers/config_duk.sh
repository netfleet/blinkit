#!/bin/bash
cd $(dirname $0)
python ../third_party/duktape/tools/configure.py --output-directory ../src/js/duktape

