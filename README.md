<h1 align="center">Meet the GOOGIL SEARCH</h1>

**the simple searching system for linux. We can't guarantee that it works 🤔, but you can try it now!**

**USAGE:**
- if you don't trust us, open Makefile in searcher, indexer and structs directory and use them with `make -B`
- open the indexer directory and run idexer by `./indexer.out "text directory path" *.txt`.
- then open the searcher directory and write `./search.out decom.txt`. Then write number of requests and strings that you want yo find. Or write them in input.txt and use  `./search.out decom.txt < input.txt`

**PS:**
After using indexer you can see result structure file in decom.txt in searcher ot input.txt in indexer direcotory. We use LSW algorythm to compress the file. Compressed file is in output.txt.
