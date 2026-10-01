#!/usr/bin/env python3
import sys

# Send headers before failing
#print("Content-Type: text/html\n")

# Simulate a critical script failure
sys.stderr.write("Critical backend error\n")
sys.exit(1) # Code 1 tells the server that the CGI failed