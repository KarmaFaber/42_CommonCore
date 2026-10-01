#producing output, should be caught by cgi timeout
import time
while True:
    print("a")
    time.sleep(1)