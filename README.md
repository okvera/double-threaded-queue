# double-threaded-queue
This queue represents a buffer between sender and receiver that run from separate threads

## How to run
Launching is performed by selecting the test: just pass the number as an argument

For example, "double-threaded-queue.exe 2" runs test #2

*Possible tests:*
1. An ordinary, "normal" data. One thread sends, another one receives proper data sequence
2. Special incorrect data. Sender writes wrong data to buffer
3. Flush buffer test. Pauses sending and receiving threads until the current data will be processed, afterall continues
4. Reset buffer test. Pauses sending and receiving threads until the current data will be processed, force clears buffer and continues
