#!/bin/python
import json
import sys

f = open(sys.argv[1])
j = json.load(f)

print(f)
